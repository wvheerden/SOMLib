## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_pima_k-means_vs_weight-centric_testError_wilcoxon.r

a <- c(36, 32, 32, 20, 16, 24, 24, 28, 20, 24, 24, 32, 36, 36, 24, 28, 36, 32, 12, 20, 12, 28, 16, 12, 16, 20, 28, 28, 32, 28)
b <- c(24, 24, 20, 20, 24, 28, 40, 44, 48, 40, 32, 36, 20, 28, 28, 32, 36, 20, 28, 28, 32, 36, 16, 16, 16, 28, 40, 36, 28, 36)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)