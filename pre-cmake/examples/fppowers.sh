#!/bin/sh

if [ $# -lt 2 ]; then
	echo "Usage: $0 {p} {a}" 1>&2
	exit 1
fi

p=$1
shift

for a
do
	g=`spiff z_gcd $p $a`
	if [ $g -ne 1 ]; then
		echo "$0:  $a is not relatively prime to $p." 1>&2
		exit 1
	fi

	ap=$a
	while [ $ap -ne 1 ]
	do
		echo $ap
		ap=`spiff fpop $p $ap . $a`
	done
	echo $ap

done
