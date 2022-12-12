#!/bin/bash

#SBATCH -n 1
#SBATCH --cpus-per-task=16

#SBATCH --job-name="mandelbrot"

#SBATCH --output="eva/res.out"
#SBATCH --open-mode=append

export DACE_profiling=True
export DACE_profiling_status=True   #显示profiling进度，需要安装tqdm库
export DACE_treps=50                #profiling次数

module load gcc/6.3.0 python/3.8.5
source dace_venv/bin/activate
export PYTHONUNBUFFERED=1           # instant ouput

python samples/simple/mandelbrot.py 128 128 1000