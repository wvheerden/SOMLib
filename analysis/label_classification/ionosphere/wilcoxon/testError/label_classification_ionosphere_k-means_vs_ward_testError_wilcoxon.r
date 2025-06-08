## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_ionosphere_k-means_vs_ward_testError_wilcoxon.r

a <- c(9.0909090909, 18.1818181818, 0, 0, 9.0909090909, 9.0909090909, 0, 9.0909090909, 27.2727272727, 9.0909090909, 0, 9.0909090909, 9.0909090909, 0, 0, 18.1818181818, 0, 27.2727272727, 9.0909090909, 18.1818181818, 9.0909090909, 0, 0, 0, 0, 27.2727272727, 9.0909090909, 36.3636363636, 9.0909090909, 9.0909090909)
b <- c()

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)