m=13
if [ $# -eq 1 ]; then
	m=$1
fi

spiff f2_p_comp_mx $m > a
chpol=`spiff f2_pm_mat_ch_pol 3 a`
echo "char poly = $chpol"
echo "A = "
cat a
echo ""

for p in `spiff f2n_p_divisors 3 $chpol`
do
	single 3 $p a
done
