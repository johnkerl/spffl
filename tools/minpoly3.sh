m=13
if [ $# -eq 1 ]; then
	m=$1
fi

spiff f2pcompmx $m > a
chpol=`spiff f2pmmatchpol 3 a`
echo "char poly = $chpol"
echo "A = "
cat a
echo ""

for p in `spiff f2npdivisors 3 $chpol`
do
	single 3 $p a
done
