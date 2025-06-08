set output "sig_iris_gnuplot_conditions.tex"
set size 2.2,1
set terminal epslatex color
set nokey
set noxtics
set noytics
set bmargin 0
set lmargin 0
set rmargin 0
set tmargin 0
set arrow 1 from 1,0 to 1,1 nohead front lw 4
set arrow 2 from 2,0 to 2,1 nohead front lw 4
set arrow 3 from 3,0 to 3,1 nohead front lw 4
set arrow 4 from 4,0 to 4,1 nohead front lw 4
set arrow 5 from 5,0 to 5,1 nohead front lw 4
set arrow 6 from 6,0 to 6,1 nohead front lw 4
set arrow 7 from 7,0 to 7,1 nohead front lw 4
set arrow 8 from 8,0 to 8,1 nohead front lw 4
set arrow 9 from 9,0 to 9,1 nohead front lw 4
set arrow 10 from 10,0 to 10,1 nohead front lw 4
set arrow 11 from 11,0 to 11,1 nohead front lw 4
set yrange [0:1]

set border lw 4

# parallel axis lower label values
set label "{\\centering\\scriptsize$\\mathsf{2}$}" at 0,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 1,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 2,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 3,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 4,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 5,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 6,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 7,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 8,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 9,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.0}$}" at 10,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{18.667}$}" at 11,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{8.000}$}" at 12,-0.025 front

# parallel axis upper label values
set label "{\\centering\\scriptsize$\\mathsf{12}$}" at 0,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{10.0}$}" at 1,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{1\\;500.0}$}" at 2,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{12.0}$}" at 3,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.0}$}" at 4,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.0}$}" at 5,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{3.0}$}" at 6,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{3.0}$}" at 7,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.0}$}" at 8,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{3.0}$}" at 9,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{3.0}$}" at 10,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 11,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{7.010\\times{10}^{11}}$}" at 12,1.025 front

# parallel axis upper labels
set label "{\\centering\\small\\textsf{\\phantom{p}}$Y,X$\\textsf{\\phantom{p}}}" at 0,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\eta(0)$\\textsf{\\phantom{p}}}" at 1,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\tau_{1}$\\textsf{\\phantom{p}}}" at 2,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\sigma(0)$\\textsf{\\phantom{p}}}" at 3,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\tau_{2}$\\textsf{\\phantom{p}}}" at 4,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\theta}_{\\mathit{char}}$\\textsf{\\phantom{p}}}" at 5,1.08 front        # threshold
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\phi}_{\\mathit{char}}$\\textsf{\\phantom{p}}}" at 6,1.08 front          # low
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\psi}_{\\mathit{char}}$\\textsf{\\phantom{p}}}" at 7,1.08 front          # high
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\theta}_{\\mathit{diff}}$\\textsf{\\phantom{p}}}" at 8,1.08 front        # threshold
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\phi}_{\\mathit{diff}}$\\textsf{\\phantom{p}}}" at 9,1.08 front          # low
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\psi}_{\\mathit{diff}}$\\textsf{\\phantom{p}}}" at 10,1.08 front         # high
set label "{\\centering\\small ${\\cal E}_{G}$}" at 11,1.08 front
set label "{\\centering\\small ${\\cal E}_{FT}$}" at 12,1.08 front

# optimal value labels
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00000.}3}$}" at -0.288,0.1 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}0.391}$}" at 0.712,0.0220625 front
set label "{\\scriptsize $\\mathsf{1\\;394.531}$}" at 1.712,0.9416875 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}1.523}$}" at 2.712,0.1199531251 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}35.156}$}" at 3.712,0.3665625 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}21.094}$}" at 4.712,0.1959375 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}1.852}$}" at 5.712,0.6321875 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}2.086}$}" at 6.712,0.7123125 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}78.906}$}" at 7.712,0.8060625 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}1.242}$}" at 8.712,0.4010625 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}0.727}$}" at 9.712,0.2271875 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}42.000}$}" at 10.712,0.3038852459 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}16.000}$}" at 11.712,0.0180612259 front

plot [0:12] "3_conditions_sig_iris.error.summary" index 1:101 using 1:2 with lines linetype 1 linewidth 5 linecolor rgb "#cccccc",\
            "3_conditions_sig_iris.error.summary" index 0 using 1:2 with lines linetype 2 dashtype 3 linewidth 6 linecolor rgb "#000000"
