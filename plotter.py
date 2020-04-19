#!/usr/bin/python

import matplotlib.pyplot as plt
import sys
import re
import getopt

x = []
y = []
f = open("cache/points.txt", "r")
for i in f:
    line = i.split()
    x.append(float(line[0]))
    y.append(float(line[1]))

plt.plot(x, y)
plt.minorticks_on()
plt.grid(which='both', color='#aaaaaa')
plt.savefig("cache/output.png", format='png')