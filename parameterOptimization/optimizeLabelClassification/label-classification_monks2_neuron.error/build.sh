gnuplot label-classification_monks2_neuron_gnuplot.plot
latex label-classification_monks2_neuron.tex
dvips -E label-classification_monks2_neuron.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps