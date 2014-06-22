from plot import *

VIDRUS_DIR = 'VirusDataBase/'

def value(v):
    ret = 0
    for i in range(len(v)):
        ret += int(v[i])
    return ret
def out(n):
    fi = open('%s%d_VirusGeneDistribution.txt' % (VIDRUS_DIR, n), 'r')
    fo = open('%s%d_VirusValueDistribution.txt' % (VIDRUS_DIR, n), 'w')

    data = {}

    for line in fi:
        sum = 0
        line = line.split(' ')
        val = value(line[0])
        if(data.has_key(str(val))):
            data[ str(val) ] += int(line[1])
        else:
            data[ str(val) ] = 0

    for i in sorted(data.items(), key=lambda x: int(x[0])):
        fo.write('%s %s\n' % (i[0], i[1]))

fo = open(VIDRUS_DIR+'vvd.plt', 'w')
fo.write('set style line 1 lw 2;'
'set key below right;'
'set key textcolor lt 0;'
'set xl textcolor lt 0;'
'set yl textcolor lt 0;'
'set terminal png size 600,400 font "times new roman,13";'
'set xrange[0:60];'
'set yrange[0:500];\n')

def plot(n):
    fo.write('set title "VirusValueHistogram";set xl "Value";set yl "Num";'+
    'plot "%d_VirusValueDistribution.txt" using 1:2 w boxes title "num";' % n+
    'set output "%d_vvd.png";' % n +
    'replot;'
    'set output;\n')

def generatePlotForVirusValueHistogram(last_term, interval):
    n = last_term/interval;
    for i in range(n):
      out((i+1)*interval)
      plot((i+1)*interval)
    fhtml = open('VirusDataBase/'+'index.html', 'w')
    outputLine(fhtml,
        '<html><link rel="stylesheet" href="%s">' % CSS_DIR +
        '<body><font color=gray><code>')
    outputHeader(fhtml, '<font color=black># RESULT</font>', 1)

    # Image Section
    for i in range(n):
      setImage( fhtml, 300, '%d_vvd.png' % ((i+1)*interval) )

    # End
    outputLine(fhtml, '</code></body></html>')
