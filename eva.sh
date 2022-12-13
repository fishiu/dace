#!/bin/bash

#SBATCH -n 1
#SBATCH --cpus-per-task=64

#SBATCH --job-name="mandelbrot"
#SBATCH --mem-per-cpu=4096
#SBATCH --output="eva/res.out"
#SBATCH --open-mode=append

export DACE_profiling=True
export DACE_profiling_status=True   #显示profiling进度，需要安装tqdm库
export DACE_treps=50                #profiling次数

module load gcc/6.3.0 python/3.8.5
source dace_venv/bin/activate
export PYTHONUNBUFFERED=1           # instant ouput

# Modify ALPHA
# for num in {2,4,6,8,10,12,14,16}; do \
#     export ALPHA=$num && \
#     export NUM_THREADS=8 && \
#     python samples/simple/mandelbrot.py 128 128 1000;
# done

# Modify NUM_THREADS
for num in {4, 8, 16, 32}; do \
    export ALPHA=2 && \
    export NUM_THREADS=$num && \
    python samples/simple/mandelbrot.py 512 512 1000;
done

# python samples/simple/mandelbrot.py 256 256 1000