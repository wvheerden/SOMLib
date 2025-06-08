set output "label-classification_pima_k-means_gnuplot.tex"
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
set label "{\\centering\\scriptsize$\\mathsf{25.200}$}" at 5,-0.025 front

# parallel axis upper label values
set label "{\\centering\\scriptsize$\\mathsf{27}$}" at 0,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{10.000}$}" at 1,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{1\\,500.000}$}" at 2,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{27.000}$}" at 3,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 4,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{36.667}$}" at 5,1.025 front

# parallel axis upper labels
set label "{\\centering\\small $K$ \\textsf{and} $J$}" at 0,1.08 front
set label "{\\centering\\small $\\eta(0)$}" at 1,1.08 front
set label "{\\centering\\small $\\tau_{1}$}" at 2,1.08 front
set label "{\\centering\\small $\\sigma(0)$}" at 3,1.08 front
set label "{\\centering\\small $\\tau_{2}$}" at 4,1.08 front
set label "{\\centering\\small ${\\cal E}_{G}$}" at 5,1.08 front

# optimal value labels
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,0000.}17}$}" at -0.248,0.6 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,00}9.688}$}" at 0.752,0.96875 front
set label "{\\scriptsize$\\mathsf{1\\,453.125}$}" at 1.752,0.94875 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,00}2.656}$}" at 2.752,0.09837963 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,0}78.125}$}" at 3.752,0.78125 front

plot [0:5] "1_generalization_label-classification_pima_k-means.error.summary" index 1:101 using 1:2 with lines linetype 1 linecolor rgb "#c1c1c1",\
           "1_generalization_label-classification_pima_k-means.error.summary" index 0 using 1:2 with lines linetype 2 linewidth 3 linecolor rgb "#000000"
