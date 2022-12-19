#!/bin/bash

export DACE_profiling=True
export DACE_profiling_status=True   #显示profiling进度，需要安装tqdm库
export DACE_treps=22                #profiling次数


for num in 2 2 2; do \
    export ALPHA=$num && \
    export NUM_THREADS=8 && \
    python3 samples/simple/mandelbrot.py 256 256 1000;
done

# for num in 2 4 6 8 10; do \
#     export ALPHA=$num && \
#     export NUM_THREADS=8 && \
#     python3 samples/simple/mandelbrot.py 256 256 1000;
# done

# for num in 2 4 6 8 10; do \
#     export ALPHA=$num && \
#     export NUM_THREADS=8 && \
#     python3 samples/simple/mandelbrot.py 256 256 1000;
# done

# # ================

# # ================



# for num in 4 8 12 16; do \
#     export ALPHA=$num && \
#     export NUM_THREADS=32 && \
#     python3 samples/simple/mandelbrot.py 512 512 1000;
# done

# for num in 4 8 12 16; do \
#     export ALPHA=$num && \
#     export NUM_THREADS=32 && \
#     python3 samples/simple/mandelbrot.py 512 512 1000;
# done

# for num in 4 8 12 16; do \
#     export ALPHA=$num && \
#     export NUM_THREADS=32 && \
#     python3 samples/simple/mandelbrot.py 512 512 1000;
# done

# for num in 4 8 12 16; do \
#     export ALPHA=$num && \
#     export NUM_THREADS=32 && \
#     python3 samples/simple/mandelbrot.py 512 512 1000;
# done

# ================

# for num in 16 16 16 16; do \
#     export ALPHA=2 && \
#     export NUM_THREADS=$num && \
#     python3 samples/simple/mandelbrot.py 512 512 1000;
# done

# for num in 16 32 64 128; do \
#     export ALPHA=2 && \
#     export NUM_THREADS=$num && \
#     python3 samples/simple/mandelbrot.py 512 512 1000;
# done

# for num in 16 32 64 128; do \
#     export ALPHA=2 && \
#     export NUM_THREADS=$num && \
#     python3 samples/simple/mandelbrot.py 512 512 1000;
# done


# =================

# for num in 8 16 32 64; do \
#     export ALPHA=2 && \
#     export NUM_THREADS=$num && \
#     python3 samples/simple/mandelbrot.py 512 512 1000;
# done


