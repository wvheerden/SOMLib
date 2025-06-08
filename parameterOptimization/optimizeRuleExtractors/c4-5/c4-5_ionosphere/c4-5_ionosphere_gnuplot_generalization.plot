set output "c4-5_ionosphere_gnuplot_generalization.tex"
set size 1.2,1
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
set arrow 5 from 5,0 to 5,1 nohead front
set yrange [0:1]

# parallel axis lower label values
set label "{\\centering\\scriptsize$\\mathsf{1}$}" at 0,-0.025 front
set label "{\\centering\\scriptsize\\textsf{Gain}}" at 1,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 2,-0.025 front
set label "{\\centering\\scriptsize\\textsf{Unused}}" at 3,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 4,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{8.788}$}" at 5,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{1.000}$}" at 6,-0.025 front

# bar for lowest Fisher confidence value
set arrow 6 from 2.965,0.090909091 to 3.035,0.090909091 nohead front
set label "{\\centering\\scriptsize $\\mathsf{\\phantom{0\\;00}0.000}$}" at 2.720,0.090909091 front	# x is usually 2.720

# parallel axis upper label values
set label "{\\centering\\scriptsize$\\mathsf{340}$}" at 0,1.025 front
set label "{\\centering\\scriptsize\\textsf{Gain ratio}}" at 1,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 2,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 3,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{10\\;000.000}$}" at 4,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{39.394}$}" at 5,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{42.700}$}" at 6,1.025 front

# parallel axis upper labels
set label "{\\centering\\small\\textsf{\\phantom{p}Minimum\\phantom{p}}}" at 0,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}examples\\phantom{p}}}" at 0,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Test\\phantom{p}}}" at 1,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}heuristic\\phantom{p}}}" at 1,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Pessimistic\\phantom{p}}}" at 2,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}confidence\\phantom{p}}}" at 2,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Fisher's\\phantom{p}}}" at 3,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}confidence\\phantom{p}}}" at 3,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Attribute\\phantom{p}}}" at 4,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}redundancy\\phantom{p}}}" at 4,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\cal E}_{G}$\\textsf{\\phantom{p}}}" at 5,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\cal E}_{C}$\\textsf{\\phantom{p}}}" at 6,1.08 front

# optimal value labels
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0000.}42}$}" at -0.248,0.12094395280236 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}43.359}$}" at 1.752,0.44359375 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}85.156}$}" at 2.752,0.87205681818182 front
set label "{\\scriptsize $\\mathsf{4\\;492.188}$}" at 3.752,0.44221875 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}9.697}$}" at 4.752,0.02270297124313 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}5.000}$}" at 5.752,0.11092326139089 front

plot [0:6] "1_generalization_c4-5_ionosphere.error.summary" index 1:101 using 1:2 with lines linetype 1 linecolor rgb "#c1c1c1",\
           "1_generalization_c4-5_ionosphere.error.summary" index 0 using 1:2 with lines linetype 2 linewidth 3 linecolor rgb "#000000"