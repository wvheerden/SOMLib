## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_monks1_k-means_vs_weight-centric_percentageUnlabeled_wilcoxon.r

a <- c(1.108033241, 0, 2.216066482, 0, 3.878116343, 0, 2.770083102, 2.493074792, 1.108033241, 3.047091413, 0.55401662, 1.385041551, 0.55401662, 1.108033241, 2.216066482, 4.432132964, 0, 1.385041551, 1.662049861, 1.385041551, 0.831024931, 1.108033241, 1.385041551, 0, 2.493074792, 3.047091413, 1.108033241, 3.601108033, 0.55401662, 2.770083102)
b <- c(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)