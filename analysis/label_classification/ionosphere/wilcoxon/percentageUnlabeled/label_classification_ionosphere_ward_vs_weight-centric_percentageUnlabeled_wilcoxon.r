## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_ionosphere_ward_vs_weight-centric_percentageUnlabeled_wilcoxon.r

a <- c()
b <- c()

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)