spiff f2pmmatrandom 13 8 8 > m
echo "M:"
cat m
echo ""

f=`spiff f2pmmatchpol 13 m`
echo "chpol: $f"
echo ""

echo -n "factors: "
spiff f2npfactor 13 $f
