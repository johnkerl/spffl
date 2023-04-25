n=6
if [ $# -eq 1 ]; then
	n=$1
fi

spiff f2_mat_random $n $n > a
chpol=`spiff f2_pm_mat_ch_pol 3 a`
echo "char poly = $chpol"
echo "det = " `spiff f2n_p_mat_op 3 det a`
echo "A = "
cat a
echo ""

for p in `spiff f2n_p_divisors 3 $chpol`
do
	single 3 $p a
done
