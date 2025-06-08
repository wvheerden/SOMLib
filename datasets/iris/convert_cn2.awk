# Converts a raw format iris data file into a CN2 format input file (see Boswell 1990)
# Usage: gawk -f convert_cn2.awk rawDataFile > outfile

BEGIN{
	print "**ATTRIBUTE AND EXAMPLE FILE**"
	print "SepalLength: (FLOAT)"
	print "SepalWidth: (FLOAT)"
	print "PetalLength: (FLOAT)"
	print "PetalWidth: (FLOAT)"
	print "class: Iris-setosa Iris-versicolor Iris-virginica;"
	print "@"
	FS = ","
}

{
	ORS = "\t"
	for (i = 1; i <= NF; i++) {
		print $i
		if (i == (NF - 1)) {
			ORS = ""
		}
		if (i == NF) {
			ORS = "\n"
			print ";"
		}
	}
}

END{
	ORS = ""
	print "@"
}