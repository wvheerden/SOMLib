set output "hybridSOM-c4-5_monks3_gnuplot_conditions.tex"
set size 2.2,1
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
set arrow 6 from 6,0 to 6,1 nohead front
set arrow 7 from 7,0 to 7,1 nohead front
set arrow 8 from 8,0 to 8,1 nohead front
set arrow 9 from 9,0 to 9,1 nohead front
set arrow 10 from 10,0 to 10,1 nohead front
set yrange [0:1]

# parallel axis lower label values
set label "{\\centering\\scriptsize$\\mathsf{2}$}" at 0,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 1,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 2,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 3,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 4,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{1}$}" at 5,-0.025 front
set label "{\\centering\\scriptsize\\textsf{Gain}}" at 6,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 7,-0.025 front
set label "{\\centering\\scriptsize\\textsf{Unused}}" at 8,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 9,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{2.857}$}" at 10,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{1.000}$}" at 11,-0.025 front

# bar for lowest Fisher confidence value
set arrow 11 from 7.965,0.090909091 to 8.035,0.090909091 nohead front
set label "{\\centering\\scriptsize $\\mathsf{\\phantom{0\\;00}0.000}$}" at 8.185,0.090909091 front	# x is usually 2.720

# parallel axis upper label values
set label "{\\centering\\scriptsize$\\mathsf{20}$}" at 0,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{10.000}$}" at 1,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{1\\;500.000}$}" at 2,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{20.000}$}" at 3,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 4,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{400}$}" at 5,1.025 front
set label "{\\centering\\scriptsize\\textsf{Gain Ratio}}" at 6,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 7,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 8,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{10\\;000.000}$}" at 9,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{53.333}$}" at 10,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{21.600}$}" at 11,1.025 front

# parallel axis upper labels
set label "{\\centering\\small\\textsf{\\phantom{p}}$K$ \\textsf{and} $J$\\textsf{\\phantom{p}}}" at 0,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\eta(0)$\\textsf{\\phantom{p}}}" at 1,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\tau_{1}$\\textsf{\\phantom{p}}}" at 2,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\sigma(0)$\\textsf{\\phantom{p}}}" at 3,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\tau_{2}$\\textsf{\\phantom{p}}}" at 4,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Minimum\\phantom{p}}}" at 5,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}examples\\phantom{p}}}" at 5,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Test\\phantom{p}}}" at 6,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}heuristic\\phantom{p}}}" at 6,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Pessimistic\\phantom{p}}}" at 7,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}confidence\\phantom{p}}}" at 7,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Fisher's\\phantom{p}}}" at 8,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}confidence\\phantom{p}}}" at 8,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Attribute\\phantom{p}}}" at 9,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}redundancy\\phantom{p}}}" at 9,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\cal E}_{G}$\\textsf{\\phantom{p}}}" at 10,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\cal E}_{C}$\\textsf{\\phantom{p}}}" at 11,1.08 front

# optimal value labels
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0000.}16}$}" at -0.248,0.77777777777778 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}0.156}$}" at 0.752,0.015625 front
set label "{\\scriptsize $\\mathsf{1\\;429.688}$}" at 1.752,0.960125 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}12.750}$}" at 2.752,0.629500000165 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}89.063}$}" at 3.752,0.905625 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0000.}44}$}" at 4.752,0.0967694235589 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}42.188}$}" at 6.752,0.431875 front
set label "{\\scriptsize $\\mathsf{7\\;968.750}$}" at 8.752,0.801875 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}19.048}$}" at 9.752,0.31275471923885 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}3.067}$}" at 10.752,0.08532362459547 front

plot [0:11] "3_conditions_hybridSOM-c4-5_monks3.error.summary" index 1:101 using 1:2 with lines linetype 1 linecolor rgb "#c1c1c1",\
            "3_conditions_hybridSOM-c4-5_monks3.error.summary" index 0 using 1:2 with lines linetype 2 linewidth 3 linecolor rgb "#000000"