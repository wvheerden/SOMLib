# Converts a raw format monks data file into a CN2 format input file (see Boswell 1990)
# Usage: gawk -f convert_cn2.awk > outfile

BEGIN{
	print "**ATTRIBUTE AND EXAMPLE FILE**"
	
	print "a1_1: (FLOAT)"
	print "a1_2: (FLOAT)"
	print "a1_3: (FLOAT)"
	print "a2_1: (FLOAT)"
	print "a2_2: (FLOAT)"
	print "a2_3: (FLOAT)"
	print "a3_1: (FLOAT)"
	print "a3_2: (FLOAT)"
	print "a4_1: (FLOAT)"
	print "a4_2: (FLOAT)"
	print "a4_3: (FLOAT)"
	print "a5_1: (FLOAT)"
	print "a5_2: (FLOAT)"
	print "a5_3: (FLOAT)"
	print "a5_4: (FLOAT)"
	print "a6_1: (FLOAT)"
	print "a6_2: (FLOAT)"
	print "class: monk not_monk;"
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