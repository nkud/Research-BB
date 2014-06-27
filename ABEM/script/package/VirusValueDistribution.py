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
      setImage( fhtml, 400, '%d_vvd.png' % ((i+1)*interval) )

    # End
    outputLine(fhtml, '</code></body></html>')

def generatePlotForVirusValueAnimation(last_term, interval):
    fframe = open(VIDRUS_DIR+'frame.plt', 'w')
    fframe.write('title(n)=sprintf("t = %d", n);\n')
    fframe.write('file(n)=sprintf("%d_VirusValueDistribution.txt", n);\n')
    fframe.write('set yl textcolor lt 0;set xrange[0:60];set yrange[0:500];\n')
    fframe.write('set title title(n);\n')
    fframe.write('plot file(n) using 1:2 w boxes title "num";\n')
    fframe.write('if(n<%d) n=n+%d; reread;' % (last_term-1, interval))

    fanim = open(VIDRUS_DIR+'animation.plt', 'w')
    fanim.write('set terminal gif animate optimize size 600,240 delay 10;\n')
    fanim.write('set output "animation.gif";\n')
    fanim.write('set title font "times new roman,12";\n')
    fanim.write('set style line 1 lw 2;\n')
    fanim.write('set key below right;\n')
    fanim.write('set key textcolor lt 0;\n')
    fanim.write('set xl textcolor lt 0;\n')

    fanim.write('n=%d;\n' % interval)
    fanim.write('load "frame.plt";\n')