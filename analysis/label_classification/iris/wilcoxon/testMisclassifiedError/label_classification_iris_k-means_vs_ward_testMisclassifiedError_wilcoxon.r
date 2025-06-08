## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_iris_k-means_vs_ward_testMisclassifiedError_wilcoxon.r

a <- c(20, 40, 0, 20, 60, 20, 20, 0, 0, 0, 40, 0, 0, 0, 0, 40, 20, 40, 0, 40, 20, 60, 40, 0, 0, 40, 40, 40, 20, 20)
b <- c(20, 0, 0, 40, 60, 20, 0, 40, 0, 20, 40, 0, 20, 40, 0, 0, 20, 0, 0, 0, 20, 60, 0, 20, 0, 60, 0, 40, 0, 20)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)