# Converts a raw format pima data file into a CN2 format input file (see Boswell 1990)
# Usage: gawk -f convert_cn2.awk > outfile

BEGIN{
	print "**ATTRIBUTE AND EXAMPLE FILE**"
	
	
	print "Attribute1: (FLOAT)"
	print "Attribute2: (FLOAT)"
	print "Attribute3: (FLOAT)"
	print "Attribute4: (FLOAT)"
	print "Attribute5: (FLOAT)"
	print "Attribute6: (FLOAT)"
	print "Attribute7: (FLOAT)"
	print "Attribute8: (FLOAT)"
	print "class: positive negative;"
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