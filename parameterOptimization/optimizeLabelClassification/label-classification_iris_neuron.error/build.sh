gnuplot label-classification_iris_neuron_gnuplot.plot
latex label-classification_iris_neuron.tex
dvips -E label-classification_iris_neuron.dvi
mv label-classification_iris_neuron.ps label-classification_iris_neuron.eps
latex sample.tex
dvips -f < sample.dvi > sample.eps
