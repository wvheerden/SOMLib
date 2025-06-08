set output "ionosphere_trainingError.tex"
set terminal epslatex standalone size 14.5cm, 9cm header "\\usepackage{sansmath}"
set tmargin 0
set bmargin 2.1
set lmargin 4.3
set rmargin 0
unset key
set format y '\scriptsize\textsf{%g}'
set grid noxtics ytics
set ylabel "\\small\\textsf{Training error}" offset 3.25
set xtics ("\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}Example-centric\\phantom{)}\\linebreak\\phantom{(}neuron\\phantom{)}}\\unsansmath}" 1, "\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}Example-centric\\phantom{)}\\linebreak\\phantom{(}cluster ($k$-means)\\phantom{)}}\\unsansmath}" 2, "\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}Example-centric\\phantom{)}\\linebreak\\phantom{(}cluster (Ward)\\phantom{)}}\\unsansmath}" 3, "\\vspace{-11pt}\\parbox{3cm}{\\sansmath\\centering\\scriptsize\\textsf{\\phantom{(}Weight-centric\\phantom{)}\\linebreak\\phantom{(}neuron\\phantom{)}}\\unsansmath}" 4)
set ytics scale 0
set bars 2.5
set xrange [0.5:4+0.5]
set yrange [6.00468317080104974:17.35728587265313294]
plot "ionosphere_trainingError.txt" using 1:2:3 ps 2.5 with errorbars
