set output "label-classification_iris_k-means_gnuplot.tex"
set terminal epslatex mono
set nokey
set noxtics
set noytics
set bmargin 0
set lmargin 0
set rmargin 0
set tmargin 0
set arrow 1 from 1,0 to 1,1 nohead front
set arrow 2 from 2,0 to 2,1 nohead front
set arrow 3 from 3,0 to 3,1 nohead front
set arrow 4 from 4,0 to 4,1 nohead front
set yrange [0:1]

# parallel axis lower label values
set label "{\\centering\\scriptsize$\\mathsf{2}$}" at 0,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 1,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 2,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 3,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 4,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{21.333}$}" at 5,-0.025 front

# parallel axis upper label values
set label "{\\centering\\scriptsize$\\mathsf{12}$}" at 0,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{10.000}$}" at 1,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{1\\,500.000}$}" at 2,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{12.000}$}" at 3,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 4,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{86.000}$}" at 5,1.025 front

# parallel axis upper labels
set label "{\\centering\\small $K$ \\textsf{and} $J$}" at 0,1.08 front
set label "{\\centering\\small $\\eta(0)$}" at 1,1.08 front
set label "{\\centering\\small $\\tau_{1}$}" at 2,1.08 front
set label "{\\centering\\small $\\sigma(0)$}" at 3,1.08 front
set label "{\\centering\\small $\\tau_{2}$}" at 4,1.08 front
set label "{\\centering\\small ${\\cal E}_{G}$}" at 5,1.08 front

# optimal value labels
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,00000.}4}$}" at -0.248,0.2 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,00}8.145}$}" at 0.752,0.814453125 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,}893.555}$}" at 1.752,0.585703125 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,00}2.633}$}" at 2.752,0.215401042 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,0}79.102}$}" at 3.752,0.801015625 front

plot [0:5] "1_generalization_label-classification_iris_k-means.error.summary" index 1:101 using 1:2 with lines linetype 1 linecolor rgb "#c1c1c1",\
           "1_generalization_label-classification_iris_k-means.error.summary" index 0 using 1:2 with lines linetype 2 linewidth 3 linecolor rgb "#000000"
