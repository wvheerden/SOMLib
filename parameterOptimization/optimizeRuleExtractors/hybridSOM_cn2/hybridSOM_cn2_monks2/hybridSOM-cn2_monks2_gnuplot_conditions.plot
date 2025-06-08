set output "hybridSOM-cn2_monks2_gnuplot_conditions.tex"
set size 1.8,1
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
set yrange [0:1]

# parallel axis lower label values
set label "{\\centering\\scriptsize$\\mathsf{2}$}" at 0,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 1,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 2,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 3,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 4,-0.025 front
set label "{\\centering\\scriptsize\\textsf{Na\\\"{\\i}ve}}" at 5,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{1}$}" at 6,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{0.000}$}" at 7,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{32.857}$}" at 8,-0.025 front
set label "{\\centering\\scriptsize$\\mathsf{1.000}$}" at 9,-0.025 front

# parallel axis upper label values
set label "{\\centering\\scriptsize$\\mathsf{20}$}" at 0,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{10.000}$}" at 1,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{1\\;500.000}$}" at 2,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{20.000}$}" at 3,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{100.000}$}" at 4,1.025 front
set label "{\\centering\\scriptsize\\textsf{Laplacian}}" at 5,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{200}$}" at 6,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{200.000}$}" at 7,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{53.333}$}" at 8,1.025 front
set label "{\\centering\\scriptsize$\\mathsf{59.100}$}" at 9,1.025 front

# parallel axis upper labels
set label "{\\centering\\small\\textsf{\\phantom{p}}$K$ \\textsf{and} $J$\\textsf{\\phantom{p}}}" at 0,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\eta(0)$\\textsf{\\phantom{p}}}" at 1,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\tau_{1}$\\textsf{\\phantom{p}}}" at 2,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\sigma(0)$\\textsf{\\phantom{p}}}" at 3,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}$\\tau_{2}$\\textsf{\\phantom{p}}}" at 4,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Error\\phantom{p}}}" at 5,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}estimate\\phantom{p}}}" at 5,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Size of\\phantom{p}}}" at 6,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}the $\\mathit{star}$ set\\phantom{p}}}" at 6,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}Significance\\phantom{p}}}" at 7,1.123 front
set label "{\\centering\\small\\textsf{\\phantom{p}threshold\\phantom{p}}}" at 7,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\cal E}_{G}$\\textsf{\\phantom{p}}}" at 8,1.08 front
set label "{\\centering\\small\\textsf{\\phantom{p}}${\\cal E}_{C}$\\textsf{\\phantom{p}}}" at 9,1.08 front

# optimal value labels
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0000.}11}$}" at -0.248,0.5 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}5.000}$}" at 0.752,0.521 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;}750.000}$}" at 1.752,0.52100000000067 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;00}5.500}$}" at 2.752,0.263000000275 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;0}50.000}$}" at 3.752,0.51000000001 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;000.}101}$}" at 5.752,0.50851256281407 front
set label "{\\scriptsize $\\mathsf{\\phantom{0\\;}100.000}$}" at 6.752,0.479 front

plot [0:9] "3_conditions_hybridSOM-cn2_monks2.error.summary" index 1:101 using 1:2 with lines linetype 1 linecolor rgb "#c1c1c1",\
            "3_conditions_hybridSOM-cn2_monks2.error.summary" index 0 using 1:2 with lines linetype 2 linewidth 3 linecolor rgb "#000000"