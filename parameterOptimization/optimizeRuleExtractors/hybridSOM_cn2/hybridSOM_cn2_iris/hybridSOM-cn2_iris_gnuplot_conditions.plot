set output "hybridSOM-cn2_iris_gnuplot_conditions.tex"
set size 1.8,1
set terminal epslatex color
set nokey
set noxtics
set noytics
set bmargin 0
set lmargin 0
set rmargin 0
set tmargin 0
set arrow 1 from 1,0 to 1,1 nohead front lw 3
set arrow 2 from 2,0 to 2,1 nohead front lw 3
set arrow 3 from 3,0 to 3,1 nohead front lw 3
set arrow 4 from 4,0 to 4,1 nohead front lw 3
set arrow 5 from 5,0 to 5,1 nohead front lw 3
set arrow 6 from 6,0 to 6,1 nohead front lw 3
set arrow 7 from 7,0 to 7,1 nohead front lw 3
set arrow 8 from 8,0 to 8,1 nohead front lw 3
set arrow 9 from 9,0 to 9,1 nohead front lw 3
set yrange [0:1]

set border lw 3

# parallel axis lower label values
set label "{\\centering\\scriptsize$\\mathsf{2}$}" at 0,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 1,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 2,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 3,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 4,-0.025 front
set label "{\\centering\\scriptsize\\textsf{Na\\\"{\\i}ve}}" at 5,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{1}$}" at 6,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 7,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{11.212}$}" at 8,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{1.000}$}" at 9,-0.025 front

# parallel axis upper label values
set label "{\\centering\\scriptsize$\\mathsf{12}$}" at 0,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{10.0}$}" at 1,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{1\\;500.0}$}" at 2,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{18.0}$}" at 3,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.0}$}" at 4,1.025 front
set label "{\\centering\\scriptsize\\textsf{Laplacian}}" at 5,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{200}$}" at 6,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{200.0}$}" at 7,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{62.424}$}" at 8,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{21.333}$}" at 9,1.025 front

# parallel axis upper labels
set label "{\\centering\\small\\textsf{\\phantom{p}}$Y,X$\\textsf{\\phantom{p}}}" at 0,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\eta(0)$\\textsf{\\phantom{p}}}" at 1,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\tau_{1}$\\textsf{\\phantom{p}}}" at 2,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\sigma(0)$\\textsf{\\phantom{p}}}" at 3,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\tau_{2}$\\textsf{\\phantom{p}}}" at 4,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}$\\mathit{cn2}$\\textrm{-}$\\mathit{err}$\\phantom{p}}}" at 5,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}\\textrm{\\textit{cn2-star}}\\phantom{p}}}" at 6,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}\\textrm{\\textit{cn2-sig}}\\phantom{p}}}" at 7,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\cal E}_{G}$\\textsf{\\phantom{p}}}" at 8,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\cal E}_{FT}$\\textsf{\\phantom{p}}}" at 9,1.08 front

# optimal value labels
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}8.301}$}" at 0.742,0.815078125 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;}635.742}$}" at 1.742,0.41182812500067 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}4.711}$}" at 2.742,0.37257812558333 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}18.164}$}" at 3.742,0.16964062501 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;000.}123}$}" at 5.742,0.62206532663317 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}51.953}$}" at 6.742,0.251765625 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}34.000}$}" at 7.742,0.42352380952381 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}2.000}$}" at 8.742,0.06309004739336 front

plot [0:9] "3_conditions_hybridSOM-cn2_iris.error.summary" index 1:101 using 1:2 with lines linetype 1 linewidth 4 linecolor rgb "#cccccc",\
            "3_conditions_hybridSOM-cn2_iris.error.summary" index 0 using 1:2 with lines linetype 2 dashtype 3 linewidth 5 linecolor rgb "#000000"
