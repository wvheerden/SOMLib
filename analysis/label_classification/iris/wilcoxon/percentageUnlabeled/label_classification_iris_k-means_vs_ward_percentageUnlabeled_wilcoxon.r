## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_iris_k-means_vs_ward_percentageUnlabeled_wilcoxon.r

a <- c(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
b <- c(0, 0, 0, 44.44444444, 0, 0, 0, 0, 4.938271605, 4.938271605, 0, 27.16049383, 0, 28.39506173, 0, 4.938271605, 38.27160494, 16.04938272, 6.172839506, 0, 0, 55.55555556, 4.938271605, 0, 17.28395062, 0, 39.50617284, 0, 25.92592593, 25.92592593)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)