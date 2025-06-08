## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_monks3_ward_vs_weight-centric_percentageUnlabeled_wilcoxon.r

a <- c(7.03125, 3.125, 7.03125, 7.03125, 5.078125, 10.9375, 8.984375, 7.8125, 8.203125, 5.859375, 1.171875, 0.78125, 5.078125, 14.0625, 8.203125, 3.125, 7.421875, 8.203125, 4.296875, 10.546875, 5.859375, 12.109375, 3.125, 8.984375, 8.59375, 2.34375, 7.8125, 2.734375, 4.6875, 12.890625)
b <- c(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)