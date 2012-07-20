if [ $# -lt 2 ] ; then
	a=`randx 8`
	b=`randx 5`
else
	a=$1
	b=$2
fi

f2ipdiv $a $b
f2pdiv $a $b
echo ""
