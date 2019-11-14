if [ $# -eq 0 ]
then
	echo "Usage: phone searchfor [...searchfor]"
	echo "(You didn't tell me what you want to search for.)"
else
	for letter in $@
	do
		if [ -z "$string" ]
		then
			string="egrep -i $letter mydata"
		else
			string="$string|egrep $letter"
		fi
	done
	
	eval $string | awk -f display.awk
fi
