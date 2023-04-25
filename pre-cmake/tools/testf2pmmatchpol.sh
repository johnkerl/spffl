spiff f2_pm_mat_random 13 8 8 > m
echo "M:"
cat m
echo ""

f=`spiff f2_pm_mat_ch_pol 13 m`
echo "chpol: $f"
echo ""

echo -n "factors: "
spiff f2n_p_factor 13 $f
