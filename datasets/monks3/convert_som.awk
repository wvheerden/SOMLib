# Converts a raw format monks data file into a SOM_PAK format input file (see Kohonen 1996a)
# Usage: gawk -f convert_som.awk rawDataFile > outfile

BEGIN{
	ORS = ""
	print "17"
	FS = ","
}

{
	ORS = "\n"
	print ""
	ORS = " "
	for (i = 1; i <= NF; i++) {
		if (i == NF) {
			ORS = ""
		}
		print $i
	}
}