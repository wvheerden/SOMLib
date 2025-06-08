set output "label-classification_monks1_k-means_gnuplot.tex"
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
set label "{\\centering\\scriptsize$\\mathsf{33.571}$}" at 5,-0.025 front

# parallel axis upper label values
set label "{\\centering\\scriptsize$\\mathsf{20}$}" at 0,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{10.000}$}" at 1,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{1\\,500.000}$}" at 2,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{20.000}$}" at 3,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 4,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{73.333}$}" at 5,1.025 front

# parallel axis upper labels
set label "{\\centering\\small $K$ \\textsf{and} $J$}" at 0,1.08 front
set label "{\\centering\\small $\\eta(0)$}" at 1,1.08 front
set label "{\\centering\\small $\\tau_{1}$}" at 2,1.08 front
set label "{\\centering\\small $\\sigma(0)$}" at 3,1.08 front
set label "{\\centering\\small $\\tau_{2}$}" at 4,1.08 front
set label "{\\centering\\small ${\\cal E}_{G}$}" at 5,1.08 front

# optimal value labels
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,0000.}19}$}" at -0.248,0.944444444 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,00}0.625}$}" at 0.752,0.0625 front
set label "{\\scriptsize$\\mathsf{1\\,031.250}$}" at 1.752,0.6875 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,00}3.563}$}" at 2.752,0.178125001 front
set label "{\\scriptsize$\\mathsf{\\phantom{0\\,0}31.250}$}" at 3.752,0.3275 front

plot [0:5] "1_generalization_label-classification_monks1_k-means.error.summary" index 1:101 using 1:2 with lines linetype 1 linecolor rgb "#c1c1c1",\
           "1_generalization_label-classification_monks1_k-means.error.summary" index 0 using 1:2 with lines linetype 2 linewidth 3 linecolor rgb "#000000"
