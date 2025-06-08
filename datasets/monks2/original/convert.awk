# Script to convert original monks data file into standard comma-delimited format
# Usage: gawk -f convert.awk monks1.data.original > monks1.data

BEGIN{
	FS = " "
	ORS = ","
}
{
	# attribute values (discarding record label)
	# attribute a1
	if ($2 == 1) {
		print "1,0,0"
	} else
	if ($2 == 2) {
		print "0,1,0"
	} else
	if ($2 == 3) {
		print "0,0,1"
	}
	
	# attribute a2
	if ($3 == 1) {
		print "1,0,0"
	} else
	if ($3 == 2) {
		print "0,1,0"
	} else
	if ($3 == 3) {
		print "0,0,1"
	}
	
	# attribute a3
	if ($4 == 1) {
		print "1,0"
	} else
	if ($4 == 2) {
		print "0,1"
	}
	
	# attribute a4
	if ($5 == 1) {
		print "1,0,0"
	} else
	if ($5 == 2) {
		print "0,1,0"
	} else
	if ($5 == 3) {
		print "0,0,1"
	}
	
	# attribute a5
	if ($6 == 1) {
		print "1,0,0,0"
	} else
	if ($6 == 2) {
		print "0,1,0,0"
	} else
	if ($6 == 3) {
		print "0,0,1,0"
	} else
	if ($6 == 4) {
		print "0,0,0,1"
	}
	
	# attribute a6
	if ($7 == 1) {
		print "1,0"
	} else
	if ($7 == 2) {
		print "0,1"
	}
	
	if (FNR != 432) {
		ORS = "\n"
	} else {
		ORS = ""
	}
	
	# record class
	if ($1 == 0) {
		print "not_monk"
	}
	else
	if ($1 == 1) {
		print "monk"
	}
	
	ORS = ","
}