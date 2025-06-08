set output "sig_monks3_gnuplot_generalization.tex"
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
set arrow 11 from 11,0 to 11,1 nohead front
set yrange [0:1]

# parallel axis lower label values
set label "{\\centering\\scriptsize$\\mathsf{2}$}" at 0,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 1,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 2,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 3,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 4,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 5,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 6,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 7,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 8,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 9,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 10,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{4.762}$}" at 11,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{34.000}$}" at 12,-0.025 front

# parallel axis upper label values
set label "{\\centering\\scriptsize$\\mathsf{20}$}" at 0,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{10.000}$}" at 1,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{1\\;500.000}$}" at 2,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{20.000}$}" at 3,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 4,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 5,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{3.000}$}" at 6,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{3.000}$}" at 7,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 8,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{3.000}$}" at 9,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{3.000}$}" at 10,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 11,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{6.207\\times{10}^{118}}$}" at 12,1.025 front

# parallel axis upper labels
set label "{\\centering\\small\\textsf{\\phantom{p}}$K$ \\textsf{and} $J$\\textsf{\\phantom{p}}}" at 0,1.08 front
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
set label "{\\centering\\small ${\\cal E}_{C}$}" at 12,1.08 front

# optimal value labels
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00000.}9}$}" at -0.248,0.3888888889 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}2.070}$}" at 0.752,0.19303125 front
set label "{\\scriptsize $\\mathsf{1\\;376.953}$}" at 1.752,0.92796875 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}7.348}$}" at 2.752,0.3573828126 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}52.734}$}" at 3.752,0.54234375 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}55.078}$}" at 4.752,0.57078125 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}2.215}$}" at 5.752,0.75328125 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}2.613}$}" at 6.752,0.88809375 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}98.047}$}" at 8.139,0.98046875 front  #.119
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}1.324}$}" at 8.752,0.42640625 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}1.090}$}" at 9.752,0.34528125 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}27.143}$}" at 10.752,0.219 front
set label "{\\scriptsize $\\mathsf{\\phantom{^{0}}8.449\\times{10}^{13}}$}" at 11.665,0.0913045539 front

plot [0:12] "1_generalization_sig_monks3.error.summary" index 1:101 using 1:2 with lines linetype 1 linecolor rgb "#c1c1c1",\
            "1_generalization_sig_monks3.error.summary" index 0 using 1:2 with lines linetype 2 linewidth 3 linecolor rgb "#000000"