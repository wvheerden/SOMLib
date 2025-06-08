## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_monks1_ward_vs_weight-centric_percentageUnlabeled_wilcoxon.r

a <- c(6.640625, 10.15625, 6.25, 5.078125, 3.90625, 3.125, 7.421875, 5.46875, 5.859375, 10.9375, 4.296875, 5.859375, 7.03125, 6.25, 1.171875, 7.421875, 5.46875, 11.328125, 3.90625, 9.375, 1.171875, 13.28125, 6.640625, 11.328125, 3.515625, 7.03125, 10.15625, 11.328125, 10.546875, 8.59375)
b <- c(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)