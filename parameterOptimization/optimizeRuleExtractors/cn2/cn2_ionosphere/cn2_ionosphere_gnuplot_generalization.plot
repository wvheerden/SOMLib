set output "cn2_ionosphere_gnuplot_generalization.tex"
set size 0.8,1
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
set yrange [0:1]

# parallel axis lower label values
set label "{\\centering\\scriptsize\\textsf{Na\\\"{\\i}ve}}" at 0,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{1}$}" at 1,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 2,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{5.455}$}" at 3,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{1.000}$}" at 4,-0.025 front

# parallel axis upper label values
set label "{\\centering\\scriptsize\\textsf{Laplacian}}" at 0,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{200}$}" at 1,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{200.000}$}" at 2,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{36.061}$}" at 3,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{37.100}$}" at 4,1.025 front

# parallel axis upper labels
set label "{\\centering\\small\\textsf{\\phantom{p}Error\\phantom{p}}}" at 0,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}estimate\\phantom{p}}}" at 0,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Size of\\phantom{p}}}" at 1,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}the $\\mathit{star}$ set\\phantom{p}}}" at 1,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Significance\\phantom{p}}}" at 2,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}threshold\\phantom{p}}}" at 2,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\cal E}_{G}$\\textsf{\\phantom{p}}}" at 3,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\cal E}_{C}$\\textsf{\\phantom{p}}}" at 4,1.08 front

# optimal value labels
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;000.}185}$}" at 0.752,0.92462311557789 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}28.516}$}" at 1.752,0.140578125 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}7.576}$}" at 2.752,0.05230693069307 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}4.967}$}" at 3.752,0.12687996306556 front

plot [0:4] "1_generalization_cn2_ionosphere.error.summary" index 1:101 using 1:2 with lines linetype 1 linecolor rgb "#c1c1c1",\
           "1_generalization_cn2_ionosphere.error.summary" index 0 using 1:2 with lines linetype 2 linewidth 3 linecolor rgb "#000000"