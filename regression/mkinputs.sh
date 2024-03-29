#!/bin/sh

mkdir -p data/input

# ----------------------------------------------------------------
# Matrices

spiff f2_mat_random    128 128 > data/input/f2-mat1.txt
spiff f2_mat_random    128 128 > data/input/f2-mat2.txt

spiff f2_mat_random    126 138 > data/input/f2-mat3.txt
spiff f2_mat_random    138 122 > data/input/f2-mat4.txt

spiff f2_mat_random    126 108 > data/input/f2-mat5.txt
spiff f2_mat_random    108 123 > data/input/f2-mat6.txt

spiff f2_pm_mat_random  11b         48  48 > data/input/f2pm-mat1.txt
spiff f2n_pm_mat_random 43 1:0:0:2  12  12 > data/input/f2npm-mat1.txt
spiff fp_mat_random    17         100 100 > data/input/fp-mat1.txt
spiff fp_pm_mat_random  11   1,0,9  20  20 > data/input/fppm-mat1.txt

# ----------------------------------------------------------------
# Polyomials

spiff f2_p_random     60 20 > data/input/f2-pols.txt
spiff f2n_p_random 13 20 10 > data/input/f2n-pols.txt
spiff fp_p_random  19 20 10 > data/input/fp-pols.txt
