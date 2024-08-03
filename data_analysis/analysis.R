setwd("D:/Onedrive/PhD/ESLM-cpp/data_analysis")
library(tidyverse)
library(ggplot2)


parameter_space <- expand.grid(
  repl = 1:5,
  t = 100,
  num_nodes = 16,
  n = 100,
  m = 10,
  edge_mean = 0.5,
  edge_var = 0.05,
  edge_threshold = 0.8,
  payoffs_mean = 0.5,
  competences_sd = 0.05,
  node_mean = 0.5,
  node_var = 0.05,
  agent_edge_sd = 0.05,
  cor_age_competence = 0.5,
  experience_bias = 0.0,
  assortment = 0:2,
  strategy = 0:1
)

construct_command <- function(params) {
  exec <- "../build/main.exe"
  args <- paste(params, collapse = " ")
  paste(exec, args)
}



num_cores <- ifelse(parallel::detectCores() > 1, parallel::detectCores() - 1, 1)
cl <- parallel::makeCluster(num_cores)
parallel::clusterExport(cl, c("parameter_space", "construct_command"))
parallel::parLapply(cl, seq_len(nrow(parameter_space)), function(i) {
  params <- parameter_space[i, ]
  command <- construct_command(params)
  system(command)
})

parallel::stopCluster(cl)

payoffs <- purrr::pmap_dfr(parameter_space, function(...) {
  params <- list(...)
  filename <- paste0("../data/payoffs_", paste(params, collapse = "_"), ".csv")
  read.csv(filename, header = FALSE) %>%
    rownames_to_column(var = "ID") %>%
    pivot_longer(-ID, names_to = "time", values_to = "payoff") %>%
    bind_cols(params)
}) %>%
  mutate(
         assortment = factor(assortment, levels = 0:2, labels = c("Age-based", "Random-Dynamic", "Random-Static")),
         strategy = factor(strategy, levels = 0:1,
                           labels = c("Random", "Payoff-Based")), time = as.numeric(sub("V", "", time)))



payoffs_means <- payoffs %>%
  group_by(time, assortment, strategy) %>%
  summarise(mean_payoff = mean(payoff, na.rm = TRUE), .groups = "drop")

p <- ggplot(payoffs_means, aes(x = time, y = mean_payoff, color = strategy, linetype = assortment)) +
  geom_line() +
  labs(x = "Time", y = "Mean Payoff", color = "Strategy", linetype = "Assortment") +
  theme_minimal()
p
#ggsave("figures/payoffs.png", p, width = 6, height = 4, dpi = 300)


aggregate_data <- payoffs %>%
  group_by(assortment, strategy) %>%
  summarise(mean_payoff = mean(payoff, na.rm = TRUE),
            ci_lower = mean(payoff, na.rm = TRUE) - qt(0.975, df = n() - 1) * sd(payoff, na.rm = TRUE) / sqrt(n()),
            ci_upper = mean(payoff, na.rm = TRUE) + qt(0.975, df = n() - 1) * sd(payoff, na.rm = TRUE) / sqrt(n()))

ggplot(aggregate_data, aes(x = strategy, y = mean_payoff, fill = assortment)) +
  geom_bar(stat = "identity", position = position_dodge()) +
  geom_errorbar(aes(ymin = ci_lower, ymax = ci_upper), width = 0.2, position = position_dodge(0.9)) +
  labs(x = "Strategy", y = "Mean Payoff", fill = "Assortment") +
  theme_minimal()
