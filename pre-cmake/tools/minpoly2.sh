m=13
n=6

if [ $# -eq 1 ]; then
	n=$1
fi
if [ $# -eq 2 ]; then
	m=$1
	n=$2
fi

spiff f2pmmatrandom $m $n $n > a
chpol=`spiff f2pmmatchpol $m a`
echo "char poly = $chpol"
echo "det = " `spiff f2n_p_mat_op $m det a`
echo "A = "
cat a
echo ""

for p in `spiff f2n_p_divisors $m $chpol`
do
	single $m $p a
done
