#!/bin/sh
echo "working directory:"
read dir
if [ !  "$dir" = "" ]
then
if [ ! -d dir ]
then
echo "error"
exit
elif [ ! -z dir ]
then
echo "error"
else
cd $dir
fi
fi

for i in *
do
	name=""
	nch=`echo $i | wc -m`
	count=`expr $nch - 1`
	n=1
	while [ $n -le $count ]
	do
		ch=`echo $i | cut -c$n-$n`
		case "$ch" in
			[A-Z] ) newch=`echo $ch | tr [A-Z] [a-z]`;;
			[a-z] ) newch=`echo $ch | tr [a-z] [A-Z]`;;
			* ) newch=`echo $ch`;;
		esac
		name=$name$newch
		n=`expr $n + 1`
	done
	mv $i $name
done
