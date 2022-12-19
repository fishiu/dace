import csv
import os
import matplotlib.pyplot as plt

dirpath = ".dacecache/mandelbrot/profiling/"
files = os.listdir(dirpath)
i = 1

for file in files:
    csvfile = open(dirpath + file)
    reader = csv.reader(csvfile)    
    data = list(reader)
    
    fig = plt.figure()
    x = list(range(1, 21))
    y = list()

    for j in range(1, len(data)-2):
        y.append(float(data[j][3]))

    plt.plot(x, y)

    fig.savefig("eva/"+file+".png")

    i = i + 1

