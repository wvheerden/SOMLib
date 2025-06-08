## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_pima_neuron_vs_weight-centric_testError_wilcoxon.r

a <- c(40, 20, 28, 24, 16, 20, 32, 44, 32, 28, 28, 32, 36, 36, 36, 16, 48, 24, 28, 32, 8, 20, 12, 20, 12, 24, 32, 28, 12, 16)
b <- c(24, 24, 20, 20, 24, 28, 40, 44, 48, 40, 32, 36, 20, 28, 28, 32, 36, 20, 28, 28, 32, 36, 16, 16, 16, 28, 40, 36, 28, 36)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)