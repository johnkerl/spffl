#!/bin/sh

m=70e
if [ $# -eq 1 ] ; then
	m=$1
fi

deg=`f2deg $m`
for h in `lfe2 $deg`
do
	h2=`f2pmmul $m $h $h`
	if [ `f2pmeq $m $h2 $h` -eq 1 ]; then
		echo $h
	fi
done
