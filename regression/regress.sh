#!/bin/sh

# ================================================================
# Note: currently requires UUT spiff executable to be in the PATH.
# ================================================================

mkdir -p data/outact

# ----------------------------------------------------------------
# Integer factorization

spiff z_test_prime { z_list 0 100 } > data/outact/z_test_prime-0-100.txt
spiff z_factor     { z_list 0 100 } > data/outact/z_factor-0-100.txt
spiff z_divisors   { z_list 0 100 } > data/outact/z_divisors-0-100.txt

spiff z_test_prime { z_list 1000000 100 } > data/outact/z_test_prime-1000000-100.txt
spiff z_factor     { z_list 1000000 100 } > data/outact/z_factor-1000000-100.txt
spiff z_divisors   { z_list 1000000 100 } > data/outact/z_divisors-1000000-100.txt

# ----------------------------------------------------------------
# Polynomial classification

spiff   f2_p_test  -ip { f2_p_list     0-8 } > data/outact/f2_p_test-0-8.txt
spiff f2n_p_test   7 { f2n_p_list  7 0-4 } > data/outact/f2n_p_test-0-8.txt
spiff   fp_p_test    5 { fp_p_list   5 0-4 } > data/outact/fp_p_test-0-8.txt
spiff   f2_p_period    { f2_p_list     0-8 } > data/outact/f2_p_period-0-8.txt

# ----------------------------------------------------------------
# Finite field tables

spiff   f2_pm_tbl  13        + > data/outact/f2pm-13-add.txt
spiff   f2_pm_tbl  13        - > data/outact/f2pm-13-sub.txt
spiff   f2_pm_tbl  13        . > data/outact/f2pm-13-mul.txt
spiff   f2_pm_tbl  13        / > data/outact/f2pm-13-div.txt

spiff f2n_pm_tbl 3 1:0:1:2 + > data/outact/f2npm-3-1012-add.txt
spiff f2n_pm_tbl 3 1:0:1:2 - > data/outact/f2npm-3-1012-sub.txt
spiff f2n_pm_tbl 3 1:0:1:2 . > data/outact/f2npm-3-1012-mul.txt
spiff f2n_pm_tbl 3 1:0:1:2 / > data/outact/f2npm-3-1012-div.txt

spiff   fp_pm_tbl  2 1011    + > data/outact/fppm-2-1011-add.txt
spiff   fp_pm_tbl  2 1011    - > data/outact/fppm-2-1011-sub.txt
spiff   fp_pm_tbl  2 1011    . > data/outact/fppm-2-1011-mul.txt
spiff   fp_pm_tbl  2 1011    / > data/outact/fppm-2-1011-div.txt

spiff   fp_pm_tbl  3 1021    + > data/outact/fppm-3-1021-add.txt
spiff   fp_pm_tbl  3 1021    - > data/outact/fppm-3-1021-sub.txt
spiff   fp_pm_tbl  3 1021    . > data/outact/fppm-3-1021-mul.txt
spiff   fp_pm_tbl  3 1021    / > data/outact/fppm-3-1021-div.txt

# ----------------------------------------------------------------
# Polynomial factorization

spiff f2_p_factor   { f2_p_list 0-5 } > data/outact/f2-smpols-factor.txt
spiff f2_p_divisors { f2_p_list 0-5 } > data/outact/f2-smpols-divisors.txt
spiff f2_p_test -ip { f2_p_list 0-5 } > data/outact/f2-smpols-test.txt
spiff f2_p_gcd        a f           > data/outact/f2-smpols-gcd.txt
spiff f2_p_lcm        a f           > data/outact/f2-smpols-lcm.txt

spiff f2n_p_factor   b { f2n_p_list b 0-3 } > data/outact/f2n-smpols-factor.txt
spiff f2n_p_divisors b { f2n_p_list b 0-3 } > data/outact/f2n-smpols-divisors.txt
spiff f2n_p_test     b { f2n_p_list b 0-3 } > data/outact/f2n-smpols-test.txt
spiff f2n_p_gcd      b   3:4:a 6:7:9      > data/outact/f2n-smpols-gcd.txt
spiff f2n_p_lcm      b   3:4:a 6:7:9      > data/outact/f2n-smpols-lcm.txt

spiff fp_p_factor   7 { fp_p_list 7 0-3 }   > data/outact/fp-smpols-factor.txt
spiff fp_p_divisors 7 { fp_p_list 7 0-3 }   > data/outact/fp-smpols-divisors.txt
spiff fp_p_test     7 { fp_p_list 7 0-3 }   > data/outact/fp-smpols-test.txt
spiff fp_p_gcd      7   1,3,2,6 2,4,5     > data/outact/fp-smpols-gcd.txt
spiff fp_p_lcm      7   1,3,2,6 2,4,5     > data/outact/fp-smpols-lcm.txt


spiff f2_p_factor `cat data/input/f2-pols.txt` \
	> data/outact/f2-pols-factor.txt
spiff f2_p_divisors `cat data/input/f2-pols.txt` \
	> data/outact/f2-pols-divisors.txt
spiff f2_p_test -ip `cat data/input/f2-pols.txt` \
	> data/outact/f2-pols-test.txt
spiff f2_p_gcd \
	`sed -n 1p data/input/f2-pols.txt` `sed -n 2p data/input/f2-pols.txt` \
	> data/outact/f2-pols-gcd.txt
spiff f2_p_lcm \
	`sed -n 1p data/input/f2-pols.txt` `sed -n 2p data/input/f2-pols.txt` \
	> data/outact/f2-pols-lcm.txt

spiff f2n_p_factor 13 `cat data/input/f2n-pols.txt` \
	> data/outact/f2n-pols-factor.txt
spiff f2n_p_divisors 13 `cat data/input/f2n-pols.txt` \
	> data/outact/f2n-pols-divisors.txt
spiff f2n_p_test 13 `cat data/input/f2n-pols.txt` \
	> data/outact/f2n-pols-test.txt
spiff f2n_p_gcd 13 \
	`sed -n 1p data/input/f2n-pols.txt` `sed -n 2p data/input/f2n-pols.txt` \
	> data/outact/f2n-pols-gcd.txt
spiff f2n_p_lcm 13 \
	`sed -n 1p data/input/f2n-pols.txt` `sed -n 2p data/input/f2n-pols.txt` \
	> data/outact/f2n-pols-lcm.txt

spiff fp_p_factor 19 `cat data/input/fp-pols.txt` \
	> data/outact/fp-pols-factor.txt
spiff fp_p_divisors 19 `cat data/input/fp-pols.txt` \
	> data/outact/fp-pols-divisors.txt
spiff fp_p_test 19 `cat data/input/fp-pols.txt` \
	> data/outact/fp-pols-test.txt
spiff fp_p_gcd 19 \
	`sed -n 1p data/input/fp-pols.txt` `sed -n 2p data/input/fp-pols.txt` \
	> data/outact/fp-pols-gcd.txt
spiff fp_p_lcm 19 \
	`sed -n 1p data/input/fp-pols.txt` `sed -n 2p data/input/fp-pols.txt` \
	> data/outact/fp-pols-lcm.txt

# ----------------------------------------------------------------
# Matrix arithmetic

spiff f2_mat_op '[[1 1 0] [0 1 1] [1 1 1]]' . '[[0 1 1] [0 1 0] [1 1 0]]' \
	> data/outact/f2-mat33.txt

spiff f2_mat_op data/input/f2-mat1.txt . data/input/f2-mat2.txt \
	> data/outact/f2-mat-1-1.txt
spiff f2_mat_op data/input/f2-mat3.txt . data/input/f2-mat4.txt \
	> data/outact/f2-mat-3-4.txt
spiff f2_mat_op data/input/f2-mat5.txt . data/input/f2-mat6.txt \
	> data/outact/f2-mat-5-6.txt
spiff f2_mat_op det data/input/f2-mat1.txt > data/outact/f2-mat-det-1.txt

spiff f2_pm_mat_op 13 '[[6 a 9] [1 3 e] [c 7 0]]' . '[[1 f 1] [e b b] [d d 0]]' \
	> data/outact/f2pm-13-mat33.txt

spiff f2_pm_mat_op 11b det data/input/f2pm-mat1.txt \
	> data/outact/f2pm-mat-det-1.txt
spiff f2_pm_mat_op 11b inv data/input/f2pm-mat1.txt \
	> data/outact/f2pm-mat-inv-1.txt

spiff f2n_pm_mat_op 43 1:0:0:2 det data/input/f2npm-mat1.txt \
	> data/outact/f2npm-mat-det-1.txt
spiff f2n_pm_mat_op 43 1:0:0:2 inv data/input/f2npm-mat1.txt \
	> data/outact/f2npm-mat-inv-1.txt

spiff fp_mat_op 17 det data/input/fp-mat1.txt > data/outact/fp-mat-det-1.txt
spiff fp_mat_op 17 inv data/input/fp-mat1.txt > data/outact/fp-mat-inv-1.txt

spiff fp_pm_mat_op 11 1,0,9 det data/input/fppm-mat1.txt \
	> data/outact/fppm-mat-det-1.txt
spiff fp_pm_mat_op 11 1,0,9 inv data/input/fppm-mat1.txt \
	> data/outact/fppm-mat-inv-1.txt

# ----------------------------------------------------------------
diff -r data/outexp data/outact > diffs
rv=$?
if [ $rv -eq 0 ]; then
	echo SPFFL REGRESSION PASSED
else
	echo SPFFL REGRESSION FAILED
fi
exit $rv
