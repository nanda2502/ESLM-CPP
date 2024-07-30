library(ggplot2)

generate_beta_data <- function(mean, var, n = 1000) {
  alpha <- mean * (mean * (1 - mean) / var - 1)
  beta <- (1 - mean) * (mean * (1 - mean) / var)
  rbeta(n, alpha, beta)
}

means <- c(0.2, 0.5, 0.8)
variances <- c(0.01, 0.05, 0.1)

data <- data.frame()
for (mean in means) {
  for (var in variances) {
    values <- generate_beta_data(mean, var)
    temp <- data.frame(value = values, mean = paste0("mean=", mean), var = paste0("var=", var))
    data <- rbind(data, temp)
  }
}

ggplot(data, aes(x = value, fill = var)) +
  geom_density(alpha = 0.6) +
  facet_wrap(~mean, scales = "free_y") +
  labs(title = "Beta Distribution for Different Mean and Variance Values",
       x = "Value", y = "Density") +
  theme_minimal()

