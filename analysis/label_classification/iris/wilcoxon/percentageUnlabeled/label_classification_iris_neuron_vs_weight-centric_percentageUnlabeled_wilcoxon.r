## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_iris_neuron_vs_weight-centric_percentageUnlabeled_wilcoxon.r

a <- c(20, 20, 16, 24, 24, 16, 24, 20, 24, 24, 16, 20, 16, 16, 16, 20, 20, 16, 20, 16, 16, 16, 20, 20, 20, 24, 20, 24, 20, 16)
b <- c(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)