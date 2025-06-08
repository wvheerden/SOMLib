## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_iris_k-means_vs_neuron_trainingError_wilcoxon.r

library('coin')

a <- c(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
b <- c(40, 44, 28, 40, 40, 28, 28, 36, 28, 36, 40, 28, 40, 40, 28, 28, 28, 28, 32, 32, 36, 40, 32, 28, 28, 28, 36, 36, 32, 44)

pvalue(wilcoxsign_test(a ~ b, alternative = "two.sided", distribution = exact(), zero.method = "Pratt"))
