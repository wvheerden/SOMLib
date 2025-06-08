## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_iris_ward_vs_weight-centric_testMisclassifiedError_wilcoxon.r

a <- c(20, 0, 0, 40, 60, 20, 0, 40, 0, 20, 40, 0, 20, 40, 0, 0, 20, 0, 0, 0, 20, 60, 0, 20, 0, 60, 0, 40, 0, 20)
b <- c(0, 0, 20, 0, 0, 0, 0, 0, 0, 20, 20, 0, 0, 20, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)