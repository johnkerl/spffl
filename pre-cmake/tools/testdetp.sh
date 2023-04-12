n=9
p=11

for arg
do
	eval $arg
done

fpmatrand $p $n $n > x

#echo ""
#ind -s x

d1=`fpmatdet $p < x`
if [ $d1 -eq 0 ]; then
	echo $d1 - - | mxwprint -w 12
else
	d2=`fpmatinv $p < x | fpmatdet $p`
	d3=`fpmul $p $d1 $d2`
	echo $d1 $d2 $d3 | mxwprint -w 12
	if [ $d3 -ne 1 ]; then
		mxwprint -w 12 < x | ind -2
		exit 1
	fi
fi
