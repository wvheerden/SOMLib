## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_iris_k-means_vs_neuron_percentageUnlabeled_wilcoxon.r

library(coin)

wilcox_test.default <- function(x, y, ...) {
          data <-
              data.frame(values = c(x, y),
                         group = rep(c("x", "y"), c(length(x), length(y))))
          wilcox_test(values ~ group, data = data, ...)
     }

a <- c(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
b <- c(20, 20, 16, 24, 24, 16, 24, 20, 24, 24, 16, 20, 16, 16, 16, 20, 20, 16, 20, 16, 16, 16, 20, 20, 20, 24, 20, 24, 20, 16)

wilcox_test(a, b, distribution = "exact")

##wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)