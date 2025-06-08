set output "label-classification_iris_neuron_gnuplot.tex"
set terminal epslatex color
set nokey
set noxtics
set noytics
set bmargin 0
set lmargin 0
set rmargin 0
set tmargin 0
set arrow 1 from 1,0 to 1,1 nohead front lw 2
set arrow 2 from 2,0 to 2,1 nohead front lw 2
set arrow 3 from 3,0 to 3,1 nohead front lw 2
set arrow 4 from 4,0 to 4,1 nohead front lw 2
set yrange [0:1]

set border lw 2

# parallel axis lower label values
set label "{\\centering\\scriptsize$\\mathsf{2}$}" at 0,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 1,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 2,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 3,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 4,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{4.000}$}" at 5,-0.025 front

# parallel axis upper label values
set label "{\\centering\\scriptsize$\\mathsf{12}$}" at 0,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{10.0}$}" at 1,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{1\\,500.0}$}" at 2,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{12.0}$}" at 3,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.0}$}" at 4,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{34.667}$}" at 5,1.025 front

# parallel axis upper labels
set label "{\\centering\\small $Y,X$}" at 0,1.08 front
set label "{\\centering\\small $\\eta(0)$}" at 1,1.08 front
set label "{\\centering\\small $\\tau_{1}$}" at 2,1.08 front
set label "{\\centering\\small $\\sigma(0)$}" at 3,1.08 front
set label "{\\centering\\small $\\tau_{2}$}" at 4,1.08 front
set label "{\\centering\\small ${\\cal E}_{G}$}" at 5,1.08 front

# optimal value labels
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,00000.}5}$}" at -0.248,0.3 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,00}5.488}$}" at 0.752,0.556828125 front
set label "{\\scriptsize$\\mathsf{1\\,432.617}$}" at 1.752,0.96007812500003 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,00}2.119}$}" at 2.752,0.17659505232340 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,0}77.539}$}" at 3.752,0.78139062500225 front

plot [0:5] "1_generalization_label-classification_iris_neuron.error.summary" index 1:101 using 1:2 with lines linetype 1 linewidth 3 linecolor rgb "#cccccc",\
           "1_generalization_label-classification_iris_neuron.error.summary" index 0 using 1:2 with lines linetype 2 dashtype 3 linewidth 4 linecolor rgb "#000000"
