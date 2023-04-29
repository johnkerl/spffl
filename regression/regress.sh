#!/bin/sh

# ================================================================
# * Can be invoked from wherever.
# * Needs to find data files relative to the directory the script is in.
# * Needs spiff UUT executable from the command line, defaulting to
#   a path relative to the repo base directory.
# ================================================================

# ================================================================
script_dir=`dirname $0`

if [ $# -eq 0 ]; then
  spiff=./build/cli/spiff/spiff
  if [ ! -x "$spiff" ]; then
    echo "$0: can't find $spiff -- has it been built?" 1>&2
    exit 1
  fi

elif [ $# -eq 1 ]; then
  spiff="$1"
  if [ ! -x "$spiff" ]; then
    echo "$0: can't find $spiff" 1>&2
    exit 1
  fi

else
    echo "Usage: $0 [path to spiff executable]" 1>&2
    exit 1

fi

indir=$script_dir/data/input
outdir=$script_dir/data/outact
expdir=$script_dir/data/outexp

# ================================================================
# Ready to go

mkdir -p $outdir

set -x

# ----------------------------------------------------------------
# Integer factorization

$spiff z_test_prime { z_list 0 100 } > $outdir/z_test_prime-0-100.txt
$spiff z_factor     { z_list 0 100 } > $outdir/z_factor-0-100.txt
$spiff z_divisors   { z_list 0 100 } > $outdir/z_divisors-0-100.txt

$spiff z_test_prime { z_list 1000000 100 } > $outdir/z_test_prime-1000000-100.txt
$spiff z_factor     { z_list 1000000 100 } > $outdir/z_factor-1000000-100.txt
$spiff z_divisors   { z_list 1000000 100 } > $outdir/z_divisors-1000000-100.txt

# ----------------------------------------------------------------
# Polynomial classification

$spiff f2_p_test  -ip { f2_p_list     0-8 } > $outdir/f2_p_test-0-8.txt
$spiff f2n_p_test   7 { f2n_p_list  7 0-4 } > $outdir/f2n_p_test-0-8.txt
$spiff fp_p_test    5 { fp_p_list   5 0-4 } > $outdir/fp_p_test-0-8.txt
$spiff f2_p_period    { f2_p_list     0-8 } > $outdir/f2_p_period-0-8.txt

# ----------------------------------------------------------------
# Finite field tables

$spiff   f2_pm_tbl  13        + > $outdir/f2pm-13-add.txt
$spiff   f2_pm_tbl  13        - > $outdir/f2pm-13-sub.txt
$spiff   f2_pm_tbl  13        . > $outdir/f2pm-13-mul.txt
$spiff   f2_pm_tbl  13        / > $outdir/f2pm-13-div.txt

$spiff f2n_pm_tbl 3 1:0:1:2 + > $outdir/f2npm-3-1012-add.txt
$spiff f2n_pm_tbl 3 1:0:1:2 - > $outdir/f2npm-3-1012-sub.txt
$spiff f2n_pm_tbl 3 1:0:1:2 . > $outdir/f2npm-3-1012-mul.txt
$spiff f2n_pm_tbl 3 1:0:1:2 / > $outdir/f2npm-3-1012-div.txt

$spiff   fp_pm_tbl  2 1011    + > $outdir/fppm-2-1011-add.txt
$spiff   fp_pm_tbl  2 1011    - > $outdir/fppm-2-1011-sub.txt
$spiff   fp_pm_tbl  2 1011    . > $outdir/fppm-2-1011-mul.txt
$spiff   fp_pm_tbl  2 1011    / > $outdir/fppm-2-1011-div.txt

$spiff   fp_pm_tbl  3 1021    + > $outdir/fppm-3-1021-add.txt
$spiff   fp_pm_tbl  3 1021    - > $outdir/fppm-3-1021-sub.txt
$spiff   fp_pm_tbl  3 1021    . > $outdir/fppm-3-1021-mul.txt
$spiff   fp_pm_tbl  3 1021    / > $outdir/fppm-3-1021-div.txt

# ----------------------------------------------------------------
# Polynomial factorization

$spiff f2_p_factor   { f2_p_list 0-5 } > $outdir/f2-smpols-factor.txt
$spiff f2_p_divisors { f2_p_list 0-5 } > $outdir/f2-smpols-divisors.txt
$spiff f2_p_test -ip { f2_p_list 0-5 } > $outdir/f2-smpols-test.txt
$spiff f2_p_gcd        a f             > $outdir/f2-smpols-gcd.txt
$spiff f2_p_lcm        a f             > $outdir/f2-smpols-lcm.txt

$spiff f2n_p_factor   b { f2n_p_list b 0-3 } > $outdir/f2n-smpols-factor.txt
$spiff f2n_p_divisors b { f2n_p_list b 0-3 } > $outdir/f2n-smpols-divisors.txt
$spiff f2n_p_test     b { f2n_p_list b 0-3 } > $outdir/f2n-smpols-test.txt
$spiff f2n_p_gcd      b   3:4:a 6:7:9        > $outdir/f2n-smpols-gcd.txt
$spiff f2n_p_lcm      b   3:4:a 6:7:9        > $outdir/f2n-smpols-lcm.txt

$spiff fp_p_factor   7 { fp_p_list 7 0-3 }   > $outdir/fp-smpols-factor.txt
$spiff fp_p_divisors 7 { fp_p_list 7 0-3 }   > $outdir/fp-smpols-divisors.txt
$spiff fp_p_test     7 { fp_p_list 7 0-3 }   > $outdir/fp-smpols-test.txt
$spiff fp_p_gcd      7   1,3,2,6 2,4,5       > $outdir/fp-smpols-gcd.txt
$spiff fp_p_lcm      7   1,3,2,6 2,4,5       > $outdir/fp-smpols-lcm.txt


$spiff f2_p_factor `cat $indir/f2-pols.txt` \
	> $outdir/f2-pols-factor.txt
$spiff f2_p_divisors `cat $indir/f2-pols.txt` \
	> $outdir/f2-pols-divisors.txt
$spiff f2_p_test -ip `cat $indir/f2-pols.txt` \
	> $outdir/f2-pols-test.txt
$spiff f2_p_gcd \
	`sed -n 1p $indir/f2-pols.txt` `sed -n 2p $indir/f2-pols.txt` \
	> $outdir/f2-pols-gcd.txt
$spiff f2_p_lcm \
	`sed -n 1p $indir/f2-pols.txt` `sed -n 2p $indir/f2-pols.txt` \
	> $outdir/f2-pols-lcm.txt

$spiff f2n_p_factor 13 `cat $indir/f2n-pols.txt` \
	> $outdir/f2n-pols-factor.txt
$spiff f2n_p_divisors 13 `cat $indir/f2n-pols.txt` \
	> $outdir/f2n-pols-divisors.txt
$spiff f2n_p_test 13 `cat $indir/f2n-pols.txt` \
	> $outdir/f2n-pols-test.txt
$spiff f2n_p_gcd 13 \
	`sed -n 1p $indir/f2n-pols.txt` `sed -n 2p $indir/f2n-pols.txt` \
	> $outdir/f2n-pols-gcd.txt
$spiff f2n_p_lcm 13 \
	`sed -n 1p $indir/f2n-pols.txt` `sed -n 2p $indir/f2n-pols.txt` \
	> $outdir/f2n-pols-lcm.txt

$spiff fp_p_factor 19 `cat $indir/fp-pols.txt` \
	> $outdir/fp-pols-factor.txt
$spiff fp_p_divisors 19 `cat $indir/fp-pols.txt` \
	> $outdir/fp-pols-divisors.txt
$spiff fp_p_test 19 `cat $indir/fp-pols.txt` \
	> $outdir/fp-pols-test.txt
$spiff fp_p_gcd 19 \
	`sed -n 1p $indir/fp-pols.txt` `sed -n 2p $indir/fp-pols.txt` \
	> $outdir/fp-pols-gcd.txt
$spiff fp_p_lcm 19 \
	`sed -n 1p $indir/fp-pols.txt` `sed -n 2p $indir/fp-pols.txt` \
	> $outdir/fp-pols-lcm.txt

# ----------------------------------------------------------------
# Matrix arithmetic

$spiff f2_mat_op '[[1 1 0] [0 1 1] [1 1 1]]' . '[[0 1 1] [0 1 0] [1 1 0]]' \
	> $outdir/f2-mat33.txt

$spiff f2_mat_op $indir/f2-mat1.txt . $indir/f2-mat2.txt \
	> $outdir/f2-mat-1-1.txt
$spiff f2_mat_op $indir/f2-mat3.txt . $indir/f2-mat4.txt \
	> $outdir/f2-mat-3-4.txt
$spiff f2_mat_op $indir/f2-mat5.txt . $indir/f2-mat6.txt \
	> $outdir/f2-mat-5-6.txt
$spiff f2_mat_op det $indir/f2-mat1.txt > $outdir/f2-mat-det-1.txt

$spiff f2_pm_mat_op 13 '[[6 a 9] [1 3 e] [c 7 0]]' . '[[1 f 1] [e b b] [d d 0]]' \
	> $outdir/f2pm-13-mat33.txt

$spiff f2_pm_mat_op 11b det $indir/f2pm-mat1.txt \
	> $outdir/f2pm-mat-det-1.txt
$spiff f2_pm_mat_op 11b inv $indir/f2pm-mat1.txt \
	> $outdir/f2pm-mat-inv-1.txt

$spiff f2n_pm_mat_op 43 1:0:0:2 det $indir/f2npm-mat1.txt \
	> $outdir/f2npm-mat-det-1.txt
$spiff f2n_pm_mat_op 43 1:0:0:2 inv $indir/f2npm-mat1.txt \
	> $outdir/f2npm-mat-inv-1.txt

$spiff fp_mat_op 17 det $indir/fp-mat1.txt > $outdir/fp-mat-det-1.txt
$spiff fp_mat_op 17 inv $indir/fp-mat1.txt > $outdir/fp-mat-inv-1.txt

$spiff fp_pm_mat_op 11 1,0,9 det $indir/fppm-mat1.txt \
	> $outdir/fppm-mat-det-1.txt
$spiff fp_pm_mat_op 11 1,0,9 inv $indir/fppm-mat1.txt \
	> $outdir/fppm-mat-inv-1.txt

# ----------------------------------------------------------------
diff -r $expdir $outdir > diffs
rv=$?
if [ $rv -eq 0 ]; then
	echo SPFFL REGRESSION PASSED
else
	echo SPFFL REGRESSION FAILED
fi
exit $rv
