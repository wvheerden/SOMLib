# Script to convert original pima data file into standard comma-delimited format
# Usage: gawk -f convert.awk pima.data.original > pima.data

BEGIN{
	FS = ","
	ORS = ","
}
{
	# attribute values
	for (i = 1; i <= (NF - 1); i++) {
		print $i
		ORS = ","
	}
	
	if (FNR != 768) {
		ORS = "\n"
	} else {
		ORS = ""
	}
	
	# record class
	if ($NF == 0) {
		print "negative"
	}
	else
	if ($NF == 1) {
		print "positive"
	}
	
	ORS = ","
}