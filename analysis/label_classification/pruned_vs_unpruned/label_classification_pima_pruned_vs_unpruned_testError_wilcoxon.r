## install.packages(c("exactRankTests"))
## R CMD BATCH --no-restore --no-save label_classification_iris_k-means_vs_neuron_trainingError_wilcoxon.r

library('coin')

a <- c(40, 20, 28, 24, 16, 20, 32, 44, 32, 28, 28, 32, 36, 36, 36, 16, 48, 24, 28, 32, 8, 20, 12, 20, 12, 24, 32, 28, 12, 16)
b <- c(48, 36, 28, 20, 24, 20, 28, 28, 40, 12, 36, 44, 40, 36, 28, 24, 32, 32, 24, 28, 8, 24, 20, 8, 16, 24, 24, 16, 36, 20)

pvalue(wilcoxsign_test(a ~ b, alternative = "two.sided", distribution = exact(), zero.method = "Pratt"))
