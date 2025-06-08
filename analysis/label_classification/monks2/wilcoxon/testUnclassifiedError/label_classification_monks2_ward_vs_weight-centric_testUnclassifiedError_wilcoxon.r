## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_monks2_ward_vs_weight-centric_testUnclassifiedError_wilcoxon.r

a <- c(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7.142857143, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7.142857143, 0, 0, 0)
b <- c(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)