# Converts a raw format monks data file into a test file with IDs stripped and class last
# Usage: gawk -f strip.awk monks-3.train > stripped_train

BEGIN{
	FS = " "
}

{
	ORS = " "
	for (i = 2; i < NF; i++) {
		print $i
	}
	print $1
	ORS = "\n"
	print $NF
}