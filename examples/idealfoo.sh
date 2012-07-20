m=1b
f=3
for x in `spiff f2pmlist -a $m`
do
	for y in `spiff f2pmlist -m $f $m`
	do
		spiff f2pmop 1b $x . $y
	done
	echo ""
done
