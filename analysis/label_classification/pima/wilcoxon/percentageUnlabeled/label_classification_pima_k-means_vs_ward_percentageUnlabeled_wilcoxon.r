## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_pima_k-means_vs_ward_percentageUnlabeled_wilcoxon.r

a <- c(1.038062284, 0, 0, 0.692041522, 0, 1.038062284, 0.692041522, 0, 0.692041522, 0.692041522, 0.692041522, 0, 0, 0, 0, 0, 0, 0, 0, 1.730103806, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
b <- c(0, 0, 0, 1.388888889, 1.388888889, 0, 0, 0, 0, 0, 0, 1.388888889, 0, 0, 0, 0, 0, 0, 0, 2.083333333, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)