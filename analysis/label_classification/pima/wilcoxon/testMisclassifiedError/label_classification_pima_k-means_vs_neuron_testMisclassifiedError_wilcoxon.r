## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_pima_k-means_vs_neuron_testMisclassifiedError_wilcoxon.r

a <- c(36, 32, 32, 20, 16, 24, 20, 28, 20, 24, 24, 32, 36, 36, 24, 28, 36, 32, 12, 20, 12, 28, 16, 12, 16, 20, 28, 28, 32, 28)
b <- c(40, 20, 28, 24, 16, 20, 28, 44, 32, 28, 28, 32, 36, 36, 36, 16, 48, 20, 28, 28, 8, 20, 12, 20, 12, 20, 32, 24, 12, 16)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)