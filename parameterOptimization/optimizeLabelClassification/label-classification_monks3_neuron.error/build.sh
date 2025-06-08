gnuplot label-classification_monks3_neuron_gnuplot.plot
latex label-classification_monks3_neuron.tex
dvips -E label-classification_monks3_neuron.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps