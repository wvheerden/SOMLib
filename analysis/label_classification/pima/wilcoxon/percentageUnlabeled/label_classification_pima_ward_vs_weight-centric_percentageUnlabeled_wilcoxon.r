## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_pima_ward_vs_weight-centric_percentageUnlabeled_wilcoxon.r

a <- c(0, 0, 0, 1.388888889, 1.388888889, 0, 0, 0, 0, 0, 0, 1.388888889, 0, 0, 0, 0, 0, 0, 0, 2.083333333, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
b <- c(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)