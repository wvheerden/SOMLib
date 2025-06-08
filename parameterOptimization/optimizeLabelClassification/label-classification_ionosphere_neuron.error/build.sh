gnuplot label-classification_ionosphere_neuron_gnuplot.plot
latex label-classification_ionosphere_neuron.tex
dvips -E label-classification_ionosphere_neuron.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps