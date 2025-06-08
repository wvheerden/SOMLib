#!/bin/bash

for ((position = 1; position <= 32; ++position))
	do
		if [ $position == 1 ]; then
			cat Label_Classification_monks3_neuron_pruning_$position/label-classification_monks3_neuron.error.summary >> label-classification_monks3_neuron.error.summary
			cat Label_Classification_monks3_neuron_pruning_$position/label-classification_monks3_neuron.accuracy.summary >> label-classification_monks3_neuron.accuracy.summary
			sed -n 1,206p Label_Classification_monks3_neuron_pruning_$position/label-classification_monks3_neuron_pruning.runOutput >> label-classification_monks3_neuron_pruning.runOutput
		else
			tail -n+2 Label_Classification_monks3_neuron_pruning_$position/label-classification_monks3_neuron.error.summary >> label-classification_monks3_neuron.error.summary
			tail -n+2 Label_Classification_monks3_neuron_pruning_$position/label-classification_monks3_neuron.accuracy.summary >> label-classification_monks3_neuron.accuracy.summary
			sed -n 31,206p Label_Classification_monks3_neuron_pruning_$position/label-classification_monks3_neuron_pruning.runOutput >> label-classification_monks3_neuron_pruning.runOutput
		fi
		
		echo "" >> label-classification_monks3_neuron.error.summary
		echo "" >> label-classification_monks3_neuron.accuracy.summary
		
		mv Label_Classification_monks3_neuron_pruning_$position/*.error Label_Classification_monks3_neuron_pruning
		mv Label_Classification_monks3_neuron_pruning_$position/*.accuracy Label_Classification_monks3_neuron_pruning
	done
	
	mv label-classification_* Label_Classification_monks3_neuron_pruning
