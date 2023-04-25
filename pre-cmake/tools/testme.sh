n=40
if [ $# -eq 1 ]; then
	n=$1
fi

spiff f2_pm_mat_random 11b $n $n > a

echo "static fast:"
time spiffsf f2_pm_mat_op 11b a ^ -1 > b

#echo "static prof:"
#time spiffsprof f2_pm_mat_op 11b a ^ -1 > e

echo "static slow:"
time spiffs  f2_pm_mat_op 11b a ^ -1 > c

echo "dyn link:"
time spiff   f2_pm_mat_op 11b a ^ -1 > d

echo ""
echo "Checksums:"
csum b c d
