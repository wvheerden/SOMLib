# Converts a column of parameter values into a space-separated row
# Usage : gawk -f convert_to_row.awk rawParameterFile > outputParameterFile

BEGIN{
	ORS = " "
}

{
	print $i
}