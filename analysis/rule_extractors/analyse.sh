#!/bin/bash

# check for correct number of parameters
if [ -z ${1} ]; then
	echo "Usage: ./analyse.sh [table|full]"
	exit
elif [[ (${1} != "table" && ${1} != "full") ]]; then
	echo "Usage: ./analyse.sh [table|full]"
	exit
fi

dataSets=("iris" "ionosphere" "monks1" "monks2" "monks3" "pima")
dataSetNames=("Iris" "Ionosphere" "Monks 1" "Monks 2" "Monks 3" "Pima")
dataSetCaptions=("Iris plants" "ionosphere" "monk's problem~1" "monk's problem~2" "monk's problem~3" "Pima Indians diabetes")

algorithms=("cn2" "c4-5" "hybridsom-cn2" "hybridsom-c4-5" "sig")
algorithmNames=("Unmodified CN2" "Unmodified C4.5" "HybridSOM (CN2)" "HybridSOM (C4.5)" "SIG* algorithm")

measures=("trainingError" "trainingMisclassifiedError" "trainingUnclassifiedError" "testError" "testMisclassifiedError" "testUnclassifiedError" "ruleSetConditionCount" "ruleCount" "averageConditionsPerRuleCount")
measureNames=("Training error" "Training error (misclassified)" "Training error (unclassified)" "Generalization error" "Generalization error (misclassified)" "Generalization error (unclassified)" "Total conditions in rule set" "Rules in rule set" "Mean conditions per rule")

measureMeans=("{\\cal E}_{T}" "{\\cal E}_{T\!M}" "{\\cal E}_{TU}" "{\\cal E}_{G}" "{\\cal E}_{G\!M}" "{\\cal E}_{GU}" "{\\cal E}_{CT}" "{\\cal E}_{R}" "{\\cal E}_{C\!A}")
measureStdDevs=("{\\cal S}_{T}" "{\\cal S}_{T\!M}" "{\\cal S}_{TU}" "{\\cal S}_{G}" "{\\cal S}_{G\!M}" "{\\cal S}_{GU}" "{\\cal S}_{CT}" "{\\cal S}_{R}" "{\\cal S}_{C\!A}")
measureCaptions=("overall training set error" "training set error due to misclassified data examples" "training set error due to unclassified data examples" "overall test set error" "test set error due to misclassified data examples" "test set error due to unclassified data examples" "total number of conditions per rule set" "number of rules per rule set" "average number of conditions per rule")

# 95% confidence interval
criticalValue=0.05

# perform a Bonferroni correction
numberOfTests=$(./numberOfTests ${#algorithms[*]})
adjustedCriticalValue=$(echo "0.05 $numberOfTests" | awk '{printf "%f", $1 / $2}')

rm -rf summary.csv

echo ",Alpha,Corrected,,\"1st value = mean\",\"2nd value = std dev\"" >> summary.csv
echo ",$criticalValue,$adjustedCriticalValue" >> summary.csv
echo "," >> summary.csv

for ((dataSet = 0; dataSet < ${#dataSets[*]}; ++dataSet))
do
	# send means and standard deviations to data file for graphs
	for ((i = 0; i < ${#measures[*]}; ++i))
	do
		if [[ ${measures[i]} != "" ]]
		then
			plotDataFileName=$(echo "./graphs/${dataSets[dataSet]}_${measures[i]}.txt")
			plotScriptFileName=$(echo "./graphs/${dataSets[dataSet]}_${measures[i]}.plot")
			plotScriptDataFileName=$(echo "${dataSets[dataSet]}_${measures[i]}.txt")
			plotScriptOutputName=$(echo "${dataSets[dataSet]}_${measures[i]}.tex")
			rm -rf $plotDataFileName
			rm -rf $plotScriptFileName
			
			echo "set output \"$plotScriptOutputName\"" >> $plotScriptFileName
			echo "set terminal epslatex standalone size 14.5cm, 9cm header \"\\\\usepackage{sansmath}\"" >> $plotScriptFileName
			echo "set tmargin 0" >> $plotScriptFileName
			echo "set bmargin 2.1" >> $plotScriptFileName
			echo "set rmargin 0" >> $plotScriptFileName
			echo "set lmargin 4.3" >> $plotScriptFileName
			echo "unset key" >> $plotScriptFileName
			echo "set format y '\scriptsize\textsf{%g}'" >> $plotScriptFileName
			echo "set grid noxtics ytics" >> $plotScriptFileName
			echo "set ylabel \"\\\\small\\\\textsf{${measureNames[$i]}}\" offset 3.25" >> $plotScriptFileName
			
			echo -n "set xtics nomirror scale 0 (" >> $plotScriptFileName
			
			for ((j = 0; j < ${#algorithms[*]}; ++j))
			do
				fileName=$(find -name "*.error" | grep ${dataSets[dataSet]}_${algorithms[j]})
				fullMean=$(./mean $fileName $i full)
				fullStdDev=$(./stdDev $fileName $i full)
				recordNumber=$(($j+1))
				
				echo -n "\"\\\\vspace{-11pt}\\\\parbox{3cm}{\\\\sansmath\\\\centering\\\\scriptsize\\\\textsf{\\\\phantom{(}${algorithmNames[$j]}\\\\phantom{)}}\\\\unsansmath}\" $recordNumber" >> $plotScriptFileName
				
				if [[ $j -ne $((${#algorithms[*]}-1)) ]]
				then
					echo -n ", " >> $plotScriptFileName
				fi
				
				echo "$recordNumber $fullMean $fullStdDev" >> $plotDataFileName
			done
			
			echo ")" >> $plotScriptFileName
			echo "set ytics scale 0" >> $plotScriptFileName
			
			yRange=$(./yRange $plotDataFileName)
			
			echo "set xrange [0.5:${#algorithms[*]}+0.5]" >> $plotScriptFileName
			echo "set yrange $yRange" >> $plotScriptFileName
			echo "plot \"$plotScriptDataFileName\" using 1:2:3 with errorbars" >> $plotScriptFileName
		fi
	done
	
	# first row (algorithm names)
	for ((i = 0; i < ${#measures[*]}; ++i))
	do
		if [[ ${measures[i]} != "" ]]
		then
			echo -n ${dataSetNames[dataSet]}" ("${measureNames[i]}"),,," >> summary.csv
			
			latexFileName=$(echo "./tables/${dataSets[dataSet]}_${measures[i]}.tex")
			rm -rf $latexFileName
			touch $latexFileName
			
			if [[ ${1} == "full" ]]; then
				echo "\documentclass[12pt, a4paper]{report}" >> $latexFileName
				echo >> $latexFileName
				echo "\usepackage{hhline}" >> $latexFileName
				echo "\usepackage{multirow}" >> $latexFileName
				echo "\usepackage{amsfonts}" >> $latexFileName
				echo "\usepackage{color}" >> $latexFileName
				echo >> $latexFileName
				echo "\setlength{\textwidth}{158mm}" >> $latexFileName
				echo "\setlength{\hoffset}{0pt}" >> $latexFileName
				echo >> $latexFileName
				echo "\newlength{\footnotenumberspace}" >> $latexFileName
				echo "\setlength{\footnotenumberspace}{2pt}" >> $latexFileName
				echo >> $latexFileName
				echo "\definecolor{cellgray}{gray}{0.75}" >> $latexFileName
				echo "\newcommand{\sigdata}[4]{\multicolumn{2}{c||}{\multirow{3}{*}{\raisebox{#1}{\parbox{0pt}{\makebox[0pt][c]{#3}\newline\makebox[0pt][c]{\raisebox{#2}{#4}}}}}}}" >> $latexFileName
				echo "\newlength{\cellfillwidth}" >> $latexFileName
				echo "\setlength{\cellfillwidth}{84.2pt}" >> $latexFileName
				echo "\newlength{\cellfillheightsmall}" >> $latexFileName
				echo "\setlength{\cellfillheightsmall}{32.1pt}" >> $latexFileName
				echo "\newlength{\cellfillheightlarge}" >> $latexFileName
				echo "\setlength{\cellfillheightlarge}{42.1pt}" >> $latexFileName
				echo "\newcommand{\cellfillsmall}[1]{\multicolumn{2}{|l||}{\multirow{3}{*}{\begin{picture}(0,0)\put(-5.8,0){\raisebox{-21pt}{\textcolor{cellgray}{\rule{\cellfillwidth}{#1}}}}\end{picture}}}}" >> $latexFileName
				echo "\newcommand{\cellfilllarge}{\multicolumn{2}{|l||}{\multirow{3}{*}{\begin{picture}(0,0)\put(-5.6,0){\raisebox{-25.5pt}{\rule{\cellfillwidth}{\cellfillheightlarge}}}\end{picture}}}}" >> $latexFileName
				echo >> $latexFileName
				echo "\begin{document}" >> $latexFileName
				echo >> $latexFileName
			fi
			
			echo "\begin{table}[p]" >> $latexFileName
			echo "	\caption[Comparison of the ${measureCaptions[i]} for rule extraction on the ${dataSetCaptions[dataSet]} data set]{Statistical comparison of the ${measureCaptions[i]} for the rule extraction algorithms executed on the ${dataSetCaptions[dataSet]} data set.}" >> $latexFileName
			echo "	\vspace{-3.09pt}" >> $latexFileName
			echo "	\textsf{\linespread{1}\scriptsize\makebox[\textwidth][c]{" >> $latexFileName
			echo -n "		\begin{tabular}[t]{||c|c||" >> $latexFileName
			
			for ((j = 0; j < ${#algorithms[*]} - 1; ++j))
			do
				echo -n "cc||" >> $latexFileName
			done
			
			echo "}" >> $latexFileName
			
			echo -n "			\hhline{~~|t" >> $latexFileName
			
			for ((j = 0; j < ${#algorithms[*]} - 1; ++j))
			do
				echo -n ":==:t" >> $latexFileName
			done
			
			echo "|}" >> $latexFileName
			
			echo -n "			\multicolumn{2}{c||}{\rule{0pt}{8pt}} " >> $latexFileName
			
			for ((j = 0; j < ${#algorithms[*]} - 1; ++j))
			do
				echo -n ${algorithmNames[j]}",," >> summary.csv
				echo -n "& \multicolumn{2}{c||}{\raisebox{0.5pt}{\textbf{${algorithmNames[j]}}}} " >> $latexFileName
			done
			
			echo "\\\\" >> $latexFileName
			
			echo -n "			\hhline{~~|" >> $latexFileName
			
			for ((j = 0; j < ${#algorithms[*]} - 1; ++j))
			do
				echo -n ":==:" >> $latexFileName
			done
			
			echo "|}" >> $latexFileName
			echo -n "			\multicolumn{2}{c||}{\rule[-4pt]{0pt}{12pt}} " >> $latexFileName
			
			for ((j = 0; j < ${#algorithms[*]} - 1; ++j))
			do
				echo -n "& \multicolumn{1}{c|}{\rule[-4pt]{0pt}{12pt}\$${measureMeans[i]}$} & \$${measureStdDevs[i]}$ " >> $latexFileName
			done
			
			echo "\\\\" >> $latexFileName
			
			echo -n "			\hhline{~~||" >> $latexFileName
			
			for ((j = 0; j < ${#algorithms[*]} - 1; ++j))
			do
				echo -n "--||" >> $latexFileName
			done
			
			echo "}" >> $latexFileName
			
			echo -n "," >> summary.csv
		fi
	done
	
	# second row (means and standard deviations of top row)
	echo >> summary.csv
	
	for ((i = 0; i < ${#measures[*]}; ++i))
	do
		if [[ ${measures[i]} != "" ]]
		then
			latexFileName=$(echo "./tables/${dataSets[dataSet]}_${measures[i]}.tex")
			
			echo -n ",,," >> summary.csv
			echo -n "			\multicolumn{2}{c||}{\rule[-4pt]{0pt}{12pt}} " >> $latexFileName
			
			for ((j = 0; j < ${#algorithms[*]} - 1; ++j))
			do
				fileName=$(find -name "*.error" | grep ${dataSets[dataSet]}_${algorithms[j]})
				mean=$(./mean $fileName $i short)
				formattedMean=$(./formatDigit $mean)
				stdDev=$(./stdDev $fileName $i short)
				formattedStdDev=$(./formatDigit $stdDev)
				
				echo -n "$mean,$stdDev," >> summary.csv
				echo -n "& \multicolumn{1}{c|}{\makebox[30px][c]{\raisebox{-0.5pt}{\$\mathsf{$formattedMean}\$}}} & \makebox[30px][c]{\raisebox{-0.5pt}{\$\mathsf{$formattedStdDev}\$}} " >> $latexFileName
			done
			
			echo -n "," >> summary.csv
			echo "\\\\" >> $latexFileName
			
			echo -n "			\hhline{|t:==:" >> $latexFileName
			
			for ((j = 0; j < ${#algorithms[*]} - 1; ++j))
			do
				echo -n ":==:" >> $latexFileName
			done
			
			echo "|}" >> $latexFileName
		fi
	done
	
	echo >> summary.csv
	
	# subsequent rows (mean and standard deviation of subsequent row, and p-values)
	for ((i = 1; i < ${#algorithms[*]}; ++i))         # row algorithms
	do
		for ((j = 0; j < ${#measures[*]}; ++j))   # measures
		do
			if [[ ${measures[j]} != "" ]]
			then
				latexFileName=$(echo "./tables/${dataSets[dataSet]}_${measures[j]}.tex")
				
				echo -n ${algorithmNames[i]}"," >> summary.csv
				echo -n "			\multicolumn{2}{||c||}{\rule{0pt}{8pt}\raisebox{0.5pt}{\textbf{${algorithmNames[i]}}}} " >> $latexFileName
				
				fileName=$(find -name "*.error" | grep ${dataSets[dataSet]}_${algorithms[i]})
				rowMean=$(./mean $fileName $j short)
				formattedRowMean=$(./formatDigit $rowMean)
				rowStdDev=$(./stdDev $fileName $j short)
				formattedRowStdDev=$(./formatDigit $rowStdDev)
				fullRowMean=$(./mean $fileName $j full)
				#fullRowStdDev=$(./stdDev $fileName $j full)
				
				echo -n "$rowMean,$rowStdDev," >> summary.csv
				
				for ((k = 0; k < i; ++k))         # column algorithms
				do
					fileName2=$(find -name "*.error" | grep ${dataSets[dataSet]}_${algorithms[k]})
					columnMean=$(./mean $fileName2 $j short)
					fullColumnMean=$(./mean $fileName2 $j full)
					./rScriptGenerator $fileName $fileName2 $j > temp.r
					R CMD BATCH --no-restore --no-save temp.r
					
					#fullColumnStdDev=$(./stdDev $fileName2 $j full)

					pValue=$(grep '\[1\] \"' temp.r.Rout | gawk -F '"' '{print $2}')
					convertedPValue=$(./convertPValue $pValue)
					
					rm -f temp.r temp.r.Rout
					
					if [[ $pValue != "" ]]
					then
						echo -n $pValue"," >> summary.csv
						
						comparisonResult=$(echo "$pValue $adjustedCriticalValue"| awk '{ print $1 < $2 }')
						
						if [[ $comparisonResult -eq 1 ]]
						then
							comparisonResult=$(echo "$fullRowMean $fullColumnMean"| awk '{ print $1 == $2 }')
							
							if [[ $comparisonResult -eq 1 ]]
							then
								echo -n "ERROR ($rowMean $columnMean)," >> summary.csv
								echo -n "& \sigdata{-7.9pt}{-2.5pt}{\phantom{\$\uparrow\$}\$\square\$\phantom{\$\uparrow\$}}{ERROR} " >> $latexFileName
								
								echo "ERROR: Unexpected mismatch found between means of ${measureNames[j]} for"
								echo "       $fileName and"
								echo "       $fileName2"
								echo
							else
								meanEqualityComparisonResult=$(echo "$rowMean $columnMean"| awk '{ print $1 == $2 }')
								
								if [[ $meanEqualityComparisonResult -eq 1 ]]
								then
									echo "WARNING: Means of ${measureNames[j]} for"
									echo "         $fileName and"
									echo "         $fileName2"
									echo "         lack sufficient precision in table."
									echo
								fi
								
								differenceResult=$(echo "$fullRowMean $fullColumnMean"| awk '{ print $1 - $2 }')
								#echo "${dataSets[dataSet]}, ${algorithms[i]}, ${algorithms[k]}, ${measureNames[j]}, $fullRowMean, $fullRowStdDev, $fullColumnMean, $fullColumnStdDev, $differenceResult"
								
								comparisonResult=$(echo "$fullRowMean $fullColumnMean"| awk '{ print $1 < $2 }')
								
								if [[ $comparisonResult -eq 1 ]]
								then
									echo -ne "Different \xE2\x86\x90," >> summary.csv    # left arrow
									
									if [[ $meanEqualityComparisonResult -eq 1 ]]
									then
										echo -n "& \sigdata{-7.9pt}{-2.5pt}{\phantom{\$\uparrow\:\$\textsuperscript{\$\ast\$}}\$\leftarrow\:\$\textsuperscript{\$\ast\$}\phantom{\$\uparrow\$}}{\phantom{/\$\times\mathsf{0^0}\$}\$\mathsf{$convertedPValue}\$\phantom{\$\times\mathsf{0^0}\$/}} " >> $latexFileName
									else
										echo -n "& \sigdata{-7.9pt}{-2.5pt}{\phantom{\$\uparrow\$}\$\leftarrow\$\phantom{\$\uparrow\$}}{\phantom{/\$\times\mathsf{0^0}\$}\$\mathsf{$convertedPValue}\$\phantom{\$\times\mathsf{0^0}\$/}} " >> $latexFileName
									fi
								else
									echo -ne "Different \xE2\x86\x91," >> summary.csv    # up arrow
									
									if [[ $meanEqualityComparisonResult -eq 1 ]]
									then
										echo -n "& \sigdata{-7.9pt}{-2.5pt}{\phantom{~\textsuperscript{\$\ast\$}}\$\uparrow\$~\textsuperscript{\$\ast\$}}{\phantom{/\$\times\mathsf{0^0}\$}\$\mathsf{$convertedPValue}\$\phantom{\$\times\mathsf{0^0}\$/}} " >> $latexFileName
									else
										echo -n "& \sigdata{-7.9pt}{-2.5pt}{\$\uparrow\$}{\phantom{/\$\times\mathsf{0^0}\$}\$\mathsf{$convertedPValue}\$\phantom{\$\times\mathsf{0^0}\$/}} " >> $latexFileName
									fi
								fi
							fi
							
						else
							echo -ne "Similar \xE2\x96\xA1," >> summary.csv                      # square
							
							echo -n "& \sigdata{-7.9pt}{-2.5pt}{\phantom{\$\uparrow\$}\$\square\$\phantom{\$\uparrow\$}}{\phantom{/\$\times\mathsf{0^0}\$}\$\mathsf{$convertedPValue}\$\phantom{\$\times\mathsf{0^0}\$/}} " >> $latexFileName
						fi
						
					else
						echo -ne "NA,Similar \xE2\x96\xA1," >> summary.csv                           # square
						echo -n "& \sigdata{-7.9pt}{-2.5pt}{\phantom{\$\uparrow\$}\$\square\$\phantom{\$\uparrow\$}}{\phantom{$\times\mathsf{0^0}$}N/A\phantom{$\times\mathsf{0^0}$}} " >> $latexFileName
					fi
				done
				
				for ((k = i; k < ${#algorithms[*]} - 1; ++k))
				do
					echo -n ",," >> summary.csv
					echo -n "& \cellfillsmall{38.4pt} " >> $latexFileName
				done
				
				echo "\\\\" >> $latexFileName
				echo -n "," >> summary.csv
				
				echo -n "			\hhline{|:==:|" >> $latexFileName
				
				for ((k = 0; k < ${#algorithms[*]} - 1; ++k))
				do
					echo -n "~~||" >> $latexFileName
				done
				
				echo "}" >> $latexFileName
				echo -n "			\rule[-4pt]{0pt}{12pt}\$${measureMeans[j]}$ & \$${measureStdDevs[j]}$ " >> $latexFileName
				
				for ((k = 0; k < ${#algorithms[*]} - 1; ++k))
				do
					echo -n "& & " >> $latexFileName
				done
				
				echo "\\\\" >> $latexFileName
				
				echo -n "			\hhline{||--||" >> $latexFileName
				
				for ((k = 0; k < ${#algorithms[*]} - 1; ++k))
				do
					echo -n "~~||" >> $latexFileName
				done
				
				echo "}" >> $latexFileName
				
				echo -n "			\makebox[30px][c]{\rule[-4pt]{0pt}{12pt}\raisebox{-0.5pt}{\$\mathsf{$formattedRowMean}\$}} & \makebox[30px][c]{\raisebox{-0.5pt}{\$\mathsf{$formattedRowStdDev}\$}} " >> $latexFileName
				
				for ((k = 0; k < ${#algorithms[*]} - 1; ++k))
				do
					echo -n "& & " >> $latexFileName
				done
				
				echo "\\\\" >> $latexFileName
				
				if [[ $i -ne ${#algorithms[*]}-1 ]]
				then
					echo -n "			\hhline{|:==:" >> $latexFileName
					
					for ((k = 0; k < ${#algorithms[*]} - 1; ++k))
					do
						echo -n ":==:" >> $latexFileName
					done
					
					echo "|}" >> $latexFileName
				fi
				
				if [[ $i -eq ${#algorithms[*]}-1 ]]
				then
					echo -n "			\hhline{|b:==:b" >> $latexFileName
					
					for ((k = 0; k < ${#algorithms[*]} - 1; ++k))
					do
						echo -n ":==:b" >> $latexFileName
					done
					
					echo "|}" >> $latexFileName
					
					echo "		\end{tabular}" >> $latexFileName
					echo "	}" >> $latexFileName
					echo "	\phantom{" >> $latexFileName
					echo "		\begin{minipage}{\textwidth}" >> $latexFileName
					echo "			\vspace{6pt}" >> $latexFileName
					echo "			\fontsize{7}{10}\selectfont\makebox[13.5pt][r]{\textsuperscript{$\ast$}}\hspace{\footnotenumberspace}Means differ by $\mathsf{3.081\times10^{-15}}$, while standard deviations differ by $\mathsf{9.841\times10^{-16}}$, indicating practically insignificant result differences." >> $latexFileName
					echo "		\end{minipage}" >> $latexFileName
					echo "	}}" >> $latexFileName
					echo "	\label{tab:comparison_ruleExtractors_${dataSets[dataSet]}_${measures[j]}}" >> $latexFileName
					echo "\end{table}" >> $latexFileName
					
					if [[ ${1} == "full" ]]; then
						echo >> $latexFileName
						echo "\end{document}" >> $latexFileName
					fi
				fi
			fi
		done
		
		echo >> summary.csv
	done
	
	echo >> summary.csv
	echo >> summary.csv
	echo >> summary.csv
	echo >> summary.csv
	echo >> summary.csv
	echo >> summary.csv
done
