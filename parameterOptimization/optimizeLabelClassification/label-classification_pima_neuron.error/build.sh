gnuplot label-classification_pima_neuron_gnuplot.plot
latex label-classification_pima_neuron.tex
dvips -E label-classification_pima_neuron.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps