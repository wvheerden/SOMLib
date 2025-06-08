## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_pima_neuron_vs_ward_testMisclassifiedError_wilcoxon.r

a <- c(40, 20, 28, 24, 16, 20, 28, 44, 32, 28, 28, 32, 36, 36, 36, 16, 48, 20, 28, 28, 8, 20, 12, 20, 12, 20, 32, 24, 12, 16)
b <- c(36, 32, 16, 28, 24, 24, 20, 28, 28, 28, 20, 40, 28, 32, 32, 20, 28, 24, 16, 28, 4, 32, 20, 16, 24, 20, 36, 24, 16, 24)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)