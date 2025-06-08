# Converts a raw format ionosphere data file into a CN2 format input file (see Boswell 1990)
# Usage: gawk -f convert_cn2.awk > outfile

BEGIN{
	print "**ATTRIBUTE AND EXAMPLE FILE**"
	
	print "a1_1: (INT)"
	print "a1_2: (INT)"
	print "a1_3: (INT)"
	print "a2_1: (INT)"
	print "a2_2: (INT)"
	print "a2_3: (INT)"
	print "a3_1: (INT)"
	print "a3_2: (INT)"
	print "a4_1: (INT)"
	print "a4_2: (INT)"
	print "a4_3: (INT)"
	print "a5_1: (INT)"
	print "a5_2: (INT)"
	print "a5_3: (INT)"
	print "a5_4: (INT)"
	print "a6_1: (INT)"
	print "a6_2: (INT)"
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