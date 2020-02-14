MPI_COMP = mpicc

all: run_a run_b

run_a: a.c
	$(MPI_COMP) -o run_a a.c

run_b: b.c
	$(MPI_COMP) -o run_b b.c

.PHONY: clean

clean: 
	rm -f run*
