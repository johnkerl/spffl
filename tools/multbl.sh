#!/bin/sh

type=f2pm
m=13
elts=`spiff ${type}list -u $m`
for a in $elts
do
	for b in $elts
	do
		echo -n " " `spiff ${type}op $m $a . $b`
	done
	echo ""
done
