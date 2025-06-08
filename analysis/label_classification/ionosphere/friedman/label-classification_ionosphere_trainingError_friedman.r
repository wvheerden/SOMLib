## R CMD BATCH --no-restore --no-save label-classification_ionosphere_trainingError_friedman.r

data <-
matrix(c(),
nrow = 30,
byrow = TRUE,
dimnames = list(1 : 30, c("K-means", "Neuron", "Ward", "Weight-centric")))
friedman.test(data)