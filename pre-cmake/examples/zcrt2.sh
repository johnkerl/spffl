#!/bin/sh

# ----------------------------------------------------------------
do_once () {
	m=$1
	n=$2
	a=$3
	b=$4

	c=`spiff z_op  $m . { fp_op $n $b / $m } + $n . { fp_op $m $a / $n }`
	d=`spiff fp_op $m $c . 1`
	e=`spiff fp_op $n $c . 1`
	echo $a $b $c $d $e
}

# ----------------------------------------------------------------
if [ $# -eq 4 ]; then
	m=$1
	n=$2
	a=$3
	b=$4
	do_once $m $n $a $b
elif [ $# -eq 2 ]; then
	m=$1
	n=$2
	for a in `spiff fp_list -a $m`
	do
	    for b in `spiff fp_list -a $n`
	    do
			do_once $m $n $a $b
	    done
	    echo ""
	done
else
	echo "Usage: $0 {m} {n} [a] [b]" 1>&2
	exit 1
fi
