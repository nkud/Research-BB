#! /usr/bin/python

from plot_module import *

info_data = {}

# Read data file
for line in open('bin/assets/INFO.txt', 'r'):
    item = line[:-1].split(' ')
    info_data[item[0]] = float(item[1])

def generatePngPlot(f, d):
    " generate plot script for gnuplot "
    v_num = int(d['NUM_V'])
    scriptForInitSetting(f)
    scriptForHasVirusPng(f, d)
    scriptForHasImmunityPng(f, d)
    scriptForSIR(f, d)
    for i in range(v_num):
        scriptForEachSIR(f, d, i)
    scriptForContact(f, d)

def main():
    f = open('auto.plt', 'w')
    generatePngPlot(f, info_data)

if __name__ == "__main__":
    print '>>> INFO...'
    for i in info_data.items():
        print '\t', i
    main()
    print '>>> finished creating "auto.plt"'
