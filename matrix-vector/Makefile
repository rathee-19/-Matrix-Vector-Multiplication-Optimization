mat-vec-vanilla: mat-vec.c
	gcc -O0 mat-vec.c -o mat-vec-vanilla

mat-vec-opt1: mat-vec.c
	gcc -O1 mat-vec.c -o mat-vec-opt1 

mat-vec-opt2: mat-vec.c
	gcc -O2 mat-vec.c -o mat-vec-opt2 

mat-vec-opt3: mat-vec.c
	gcc -O3 mat-vec.c -o mat-vec-opt3 

mat-vec-flg: mat-vec.c
	gcc -O3 -funroll-loops -ftree-vectorize -march=native -mavx2 -fno-strict-aliasing mat-vec.c -o mat-vec-flg

mat-vec-vect: mat-vec-vect.c
	gcc -O3 -march=native -ftree-vectorize -funroll-loops -ffast-math -mavx2 -mfma mat-vec-vect.c -o out4.out

mat-vec-omp: mat-vec-omp.c
	gcc -O3 -fopenmp  mat-vec-omp.c -o mat-vec-omp	

mat-vec-omp-vect: mat-vec-omp-vect.c
	gcc -O3 -march=native -ftree-vectorize -funroll-loops -fopenmp -ffast-math -mavx2 -mfma mat-vec-omp-vect.c -o mat-vec-omp-vect
