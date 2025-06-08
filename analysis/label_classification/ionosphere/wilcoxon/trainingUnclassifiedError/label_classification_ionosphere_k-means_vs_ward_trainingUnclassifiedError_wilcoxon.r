## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_ionosphere_k-means_vs_ward_trainingUnclassifiedError_wilcoxon.r

a <- c(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
b <- c()

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)