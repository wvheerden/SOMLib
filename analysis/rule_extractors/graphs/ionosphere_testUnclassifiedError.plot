set output "ionosphere_testUnclassifiedError.tex"
set terminal epslatex standalone size 14.5cm, 9cm header "\\usepackage{sansmath}"
set tmargin 0
set bmargin 2.1
set rmargin 0
set lmargin 4.3
unset key
set format y '\scriptsize\textsf{%g}'
set grid noxtics ytics
set ylabel "\\small\\textsf{Generalization error (unclassified)}" offset 3.25
set xtics nomirror scale 0 ("\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}Unmodified CN2\\phantom{)}}\\unsansmath}" 1, "\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}Unmodified C4.5\\phantom{)}}\\unsansmath}" 2, "\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}HybridSOM (CN2)\\phantom{)}}\\unsansmath}" 3, "\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}HybridSOM (C4.5)\\phantom{)}}\\unsansmath}" 4, "\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}SIG* algorithm\\phantom{)}}\\unsansmath}" 5)
set ytics scale 0
set xrange [0.5:5+0.5]
set yrange [-2.14219485720273939:3.96037667538455773]
plot "ionosphere_testUnclassifiedError.txt" using 1:2:3 with errorbars
