import numpy as np
import dace
import argparse

from dace.transformation.interstate import LoopToMap
from dace.transformation.dataflow import MapFusion


N = dace.symbol('N')
N1 = dace.symbol('N1')


def genmat(n, n1):
    M = np.zeros((n, n, n1, n1))
    init_val = 1325
    for ii in range(n):
        for jj in range(n):
            #computing None entries
            None_entry = False
            if ((ii < jj) and (ii % 3 != 0)):
                None_entry = True
            if ((ii > jj) and (jj % 3 != 0)):
                None_entry = True
            if (ii % 2 == 1):
                None_entry = True
            if (jj % 2 == 1):
                None_entry = True
            if (ii == jj):
                None_entry = False
            if (ii == jj - 1):
                None_entry = False
            if (ii - 1 == jj):
                None_entry = False

            #init matrix
            if None_entry == False:
                for i in range(n1):
                    for j in range(n1):
                        init_val = (3125 * init_val) % 65536
                        M[ii][jj][i][j] = dace.float64(((init_val - 32768.0) / 16384.0))
            else:
                M[ii][jj][i][j] = 0
    return M


@dace.program
def lu0(diag: dace.float64[N1, N1]):
    for k in range(N1):
        for i in range(k + 1, N1):
            diag[i][k] = diag[i][k] / diag[k][k]
            for j in range(k + 1, N1):
                diag[i][j] = diag[i][j] - diag[i][k] * diag[k][j]


@dace.program
def bdiv(diag: dace.float64[N1, N1], row: dace.float64[N1, N1]):
    for i in range(N1):
        for k in range(N1):
            row[i][k] = row[i][k] / diag[k][k]
            for j in range(k + 1, N1):
                row[i][j] = row[i][j] - row[i][k] * diag[k][j]


@dace.program
def bmod(row: dace.float64[N1, N1], col: dace.float64[N1, N1], inner: dace.float64[N1, N1]):
    for i in range(N1):
        for j in range(N1):
            for k in range(N1):
                inner[i][j] = inner[i][j] - row[i][k] * col[k][j]


@dace.program
def fwd(diag: dace.float64[N1, N1], col: dace.float64[N1, N1]):
    for j in range(N1):
        for k in range(N1):
            for i in range(k + 1, N1):
                col[i][j] = col[i][j] - diag[i][k] * col[k][j]


@dace.program
def pred(mat: dace.float64[N1, N1]):
    # check if all elements are zero
    sum = 0
    for i in range(N1):
        for j in range(N1):
            if mat[i][j] != 0:
                sum += 1
    return sum != 0


@dace.program
def sparselu_map(BENCH: dace.float64[N, N, N1, N1]):
    for kk in range(N):
        lu0(BENCH[kk, kk])
        for jj in dace.map[kk + 1:N]:
            p = pred(BENCH[kk, jj])
            if (p[0]):
                fwd(BENCH[kk, kk], BENCH[kk, jj])
        for ii in dace.map[kk + 1:N]:
            p = pred(BENCH[ii, kk])
            if (p[0]):
                bdiv(BENCH[kk, kk], BENCH[ii, kk])
        for ii in dace.map[kk + 1:N]:
            p = pred(BENCH[ii, kk])
            if (p[0]):
                for jj in dace.map[kk + 1:N]:
                    p = pred(BENCH[kk, jj])
                    if (p[0]):
                        bmod(BENCH[ii, kk], BENCH[kk, jj], BENCH[ii, jj])

@dace.program
def sparselu_range(BENCH: dace.float64[N, N, N1, N1]):
    #print("Computing SparseLU Factorization (%dx%d matrix with %dx%d blocks) ",N,N,N1,N1)
    for kk in range(N):
        lu0(BENCH[kk, kk])
        for jj in range(kk + 1, N):
            if (pred(BENCH[kk, jj])):
                fwd(BENCH[kk, kk], BENCH[kk, jj])
        for ii in range(kk + 1, N):
            if (pred(BENCH[ii, kk])):
                bdiv(BENCH[kk, kk], BENCH[ii, kk])
        for ii in range(kk + 1, N):
            if (pred(BENCH[ii, kk])):
                for jj in range(kk + 1, N):
                    if (pred(BENCH[kk, jj])):
                        bmod(BENCH[ii, kk], BENCH[kk, jj], BENCH[ii, jj])


def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("--N", type=int, default=5)
    parser.add_argument("--N1", type=int, default=5)
    parser.add_argument("--xfrom", action="store_true", default=False)
    parser.add_argument("-p", "--print", action="store_true", default=False)
    args = parser.parse_args()
    return args


def print_BENCH(BENCH):
    N, _, N1, _ = BENCH.shape
    for i in range(N):
        for j in range(N):
            print("BENCH[", i, "][", j, "] = ")
            for k in range(N1):
                for l in range(N1):
                    print("%.6f" % BENCH[i][j][k][l], end=" ")
                print()


def main():
    args = get_args()
    
    print("Computing SparseLU Factorization (%dx%d matrix with %dx%d blocks) " % (args.N, args.N, args.N1, args.N1))

    BENCH = genmat(args.N, args.N1)
    if args.print:
        print("INIT BENCH")
        print_BENCH(BENCH)

    if args.xfrom:
        print("Using XFrom")
        sdfg = sparselu_map.to_sdfg()
        sdfg.apply_strict_transformations()
        sdfg.apply_transformations_repeated([MapFusion, LoopToMap])
        sdfg.compile()
        sdfg(BENCH, N=args.N, N1=args.N1)
    else:
        sparselu_map(BENCH)

    if args.print:
        print("RES BENCH")
        print_BENCH(BENCH)

if __name__ == "__main__":
    main()
