## R CMD BATCH --no-restore --no-save label-classification_monks2_testUnclassifiedError_friedman.r

data <-
matrix(c(0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 7.142857143, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 7.142857143, 0,
0, 7.142857143, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 7.142857143, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 7.142857143, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0),
nrow = 30,
byrow = TRUE,
dimnames = list(1 : 30, c("K-means", "Neuron", "Ward", "Weight-centric")))
friedman.test(data)