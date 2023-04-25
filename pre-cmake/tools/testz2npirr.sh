n=10
d=5
m=13
if [ $# -ge 1 ]; then
	n=$1
fi
if [ $# -ge 2 ]; then
	d=$2
fi
if [ $# -ge 3 ]; then
	m=$3
fi

for i in `jot 1 $n`
do
	f=`spiff f2n_p_random $m $d`
	echo -n $f
	echo -n ": "
	spiff f2npirr $m $f
	spiff f2n_p_factor $m $f
	echo ""
done
