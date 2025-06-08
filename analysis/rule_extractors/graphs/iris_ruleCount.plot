set output "iris_ruleCount.tex"
set terminal epslatex standalone size 14.5cm, 9cm header "\\usepackage{sansmath}"
set tmargin 0
set bmargin 2.1
set rmargin 0
set lmargin 4.3
unset key
set format y '\scriptsize\textsf{%g}'
set grid noxtics ytics
set ylabel "\\small\\textsf{Rules in rule set}" offset 3.25
set xtics nomirror scale 0 ("\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}Unmodified CN2\\phantom{)}}\\unsansmath}" 1, "\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}Unmodified C4.5\\phantom{)}}\\unsansmath}" 2, "\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}HybridSOM (CN2)\\phantom{)}}\\unsansmath}" 3, "\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}HybridSOM (C4.5)\\phantom{)}}\\unsansmath}" 4, "\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}SIG* algorithm\\phantom{)}}\\unsansmath}" 5)
set ytics scale 0
set xrange [0.5:5+0.5]
set yrange [1.88937937148457857:4.32303319882384773]
plot "iris_ruleCount.txt" using 1:2:3 with errorbars
