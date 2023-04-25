n=6
if [ $# -eq 1 ]; then
	n=$1
fi

spiff f2_mat_random $n $n > a
chpol=`spiff f2pmmatchpol 3 a`
echo "char poly = $chpol"
echo "det = " `spiff f2npmatop 3 det a`
echo "A = "
cat a
echo ""

for p in `spiff f2npdivisors 3 $chpol`
do
	single 3 $p a
done
