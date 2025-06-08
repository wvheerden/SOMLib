#!/bin/bash

./rScriptGenerator neuron_pima.edited.txt 6 0 > neuron_pima_meanUnlabeledNeuronPercentage_vs_meanGeneralizationError.R
R CMD BATCH --no-restore --no-save neuron_pima_meanUnlabeledNeuronPercentage_vs_meanGeneralizationError.R
./rScriptGenerator neuron_pima.edited.txt 6 1 > neuron_pima_meanUnlabeledNeuronPercentage_vs_stdDevGeneralizationError.R
R CMD BATCH --no-restore --no-save neuron_pima_meanUnlabeledNeuronPercentage_vs_stdDevGeneralizationError.R
./rScriptGenerator neuron_pima.edited.txt 6 2 > neuron_pima_meanUnlabeledNeuronPercentage_vs_meanGeneralizationMisclassifiedError.R
R CMD BATCH --no-restore --no-save neuron_pima_meanUnlabeledNeuronPercentage_vs_meanGeneralizationMisclassifiedError.R
./rScriptGenerator neuron_pima.edited.txt 6 3 > neuron_pima_meanUnlabeledNeuronPercentage_vs_stdDevGeneralizationMisclassifiedError.R
R CMD BATCH --no-restore --no-save neuron_pima_meanUnlabeledNeuronPercentage_vs_stdDevGeneralizationMisclassifiedError.R
./rScriptGenerator neuron_pima.edited.txt 6 4 > neuron_pima_meanUnlabeledNeuronPercentage_vs_meanGeneralizationUnclassifiedError.R
R CMD BATCH --no-restore --no-save neuron_pima_meanUnlabeledNeuronPercentage_vs_meanGeneralizationUnclassifiedError.R
./rScriptGenerator neuron_pima.edited.txt 6 5 > neuron_pima_meanUnlabeledNeuronPercentage_vs_stdDevGeneralizationUnclassifiedError.R
R CMD BATCH --no-restore --no-save neuron_pima_meanUnlabeledNeuronPercentage_vs_stdDevGeneralizationUnclassifiedError.R
