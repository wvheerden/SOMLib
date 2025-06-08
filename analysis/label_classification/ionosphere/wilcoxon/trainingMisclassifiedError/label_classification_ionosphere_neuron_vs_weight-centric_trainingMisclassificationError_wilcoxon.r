## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_ionosphere_neuron_vs_weight-centric_trainingMisclassificationError_wilcoxon.r

a <- c()
b <- c()

wilcox.test (a, b, alternative="two.sided", paired=TRUE, conf.level=0.95)