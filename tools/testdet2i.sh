n=9
r=13

for arg
do
	eval $arg
done

f2ipmmatrand $r $n $n > x
d1=`f2ipmmatdet $r < x`
if [ $d1 == 0 ]; then
	echo $d1 - - | mxwprint -w 12
else
	d2=`f2ipmmatinv $r < x | f2ipmmatdet $r`
	d3=`f2ipmmul $r $d1 $d2`
	echo $d1 $d2 $d3 | mxwprint -w 12
	if [ $d3 != 1 ]; then
		mxwprint -w 12 < x | ind -2
		exit 1
	fi
fi
