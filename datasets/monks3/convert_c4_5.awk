# Converts a raw format monks data file into a C4.5 format input file (see Quinlan 1993)
# Usage : gawk -f convert_c4_5.awk rawDataFile > outputDataFile

BEGIN{
	FS = ","
}

{
	if (FNR != 1) {
		ORS = "\n"
	}
	ORS = ","
	for (i = 1; i <= NF; i++) {
		if (i == NF) {
			ORS = ".\n"
		}
		print $i
	}
}