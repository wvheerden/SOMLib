# Converts a raw format ionosphere data file into a CN2 format input file (see Boswell 1990)
# Usage: gawk -f convert_cn2.awk rawDataFile > outputDataFile

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
	print "Attribute9: (FLOAT)"
	print "Attribute10: (FLOAT)"
	print "Attribute11: (FLOAT)"
	print "Attribute12: (FLOAT)"
	print "Attribute13: (FLOAT)"
	print "Attribute14: (FLOAT)"
	print "Attribute15: (FLOAT)"
	print "Attribute16: (FLOAT)"
	print "Attribute17: (FLOAT)"
	print "Attribute18: (FLOAT)"
	print "Attribute19: (FLOAT)"
	print "Attribute20: (FLOAT)"
	print "Attribute21: (FLOAT)"
	print "Attribute22: (FLOAT)"
	print "Attribute23: (FLOAT)"
	print "Attribute24: (FLOAT)"
	print "Attribute25: (FLOAT)"
	print "Attribute26: (FLOAT)"
	print "Attribute27: (FLOAT)"
	print "Attribute28: (FLOAT)"
	print "Attribute29: (FLOAT)"
	print "Attribute30: (FLOAT)"
	print "Attribute31: (FLOAT)"
	print "Attribute32: (FLOAT)"
	print "Attribute33: (FLOAT)"
	print "Attribute34: (FLOAT)"
	print "class: good bad;"
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