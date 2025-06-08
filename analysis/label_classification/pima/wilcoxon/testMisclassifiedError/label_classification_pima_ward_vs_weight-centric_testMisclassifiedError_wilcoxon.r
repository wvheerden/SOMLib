## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_pima_ward_vs_weight-centric_testMisclassifiedError_wilcoxon.r

a <- c(36, 32, 16, 28, 24, 24, 20, 28, 28, 28, 20, 40, 28, 32, 32, 20, 28, 24, 16, 28, 4, 32, 20, 16, 24, 20, 36, 24, 16, 24)
b <- c(24, 24, 20, 20, 24, 28, 40, 44, 48, 40, 32, 36, 20, 28, 28, 32, 36, 20, 28, 28, 32, 36, 16, 16, 16, 28, 40, 36, 28, 36)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)