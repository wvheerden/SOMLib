## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_iris_k-means_vs_neuron_trainingError_wilcoxon.r

library('coin')

a <- c(0, 0, 0, 0, 0, 0, 0, 0, 20, 20, 20, 0, 0, 0, 0, 20, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 20, 0, 0, 0)
b <- c(0, 0, 0, 0, 0, 0, 0, 0, 20, 20, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0)

pvalue(wilcoxsign_test(a ~ b, alternative = "two.sided", distribution = exact(), zero.method = "Pratt"))
