from plot import *

AGENT_DIR = 'AgentDataBase/'

def value(v):
    ret = 0
    for i in range(len(v)):
        ret += 1
    return ret
def out(n):
    fi = open(AGENT_DIR+'%d_AgentGeneDistribution.txt' % n, 'r')
    fo = open(AGENT_DIR+'%d_AgentValueDistribution.txt' % n, 'w')

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

fo = open(AGENT_DIR+'avd.plt', 'w')
fo.write('set style line 1 lw 2;'
'set key below right;'
'set key textcolor lt 0;'
'set xl textcolor lt 0;'
'set yl textcolor lt 0;'
'set terminal png size 600,400 font "times new roman,13";'
'set xrange[0:200];'
'set yrange[0:200];\n')

def plot(n):
    fo.write('set title "AgentValueHistogram";set xl "Value";set yl "Num";'+
    'plot "%d_AgentValueDistribution.txt" using 1:2 w boxes title "num";' % n+
    'set output "%d_avd.png";' % n +
    'replot;'
    'set output;\n')

def generatePlotForAgentValueHistogram(last_term, interval):
    n = last_term/interval;
    for i in range(n):
      out((i+1)*interval)
      plot((i+1)*interval)
    fhtml = open('AgentDataBase/'+'index.html', 'w')
    outputLine(fhtml,
        '<html><link rel="stylesheet" href="%s">' % CSS_DIR +
        '<body><font color=gray><code>')
    outputHeader(fhtml, '<font color=black># RESULT</font>', 1)

    # Image Section
    for i in range(n):
      setImage( fhtml, 400, '%d_avd.png' % ((i+1)*interval) )

    # End
    outputLine(fhtml, '</code></body></html>')

def generatePlotForAgentValueAnimation(last_term, interval):
    fframe = open(AGENT_DIR+'frame.plt', 'w')
    fframe.write('title(n)=sprintf("t = %d", n);\n')
    fframe.write('file(n)=sprintf("%d_AgentValueDistribution.txt", n);\n')
    fframe.write('set yl textcolor lt 0;set xrange[0:200];set yrange[0:500];\n')
    fframe.write('set title title(n);\n')
    fframe.write('plot file(n) using 1:2 w boxes title "num";\n')
    fframe.write('if(n<%d) n=n+%d; reread;' % (last_term-1, interval))

    fanim = open(AGENT_DIR+'animation.plt', 'w')
    fanim.write('set terminal gif animate optimize size 600,240 delay 10;\n')
    fanim.write('set output "animation.gif";\n')
    # fanim.write('set title font "times new roman,12";\n')
    fanim.write('set style line 1 lw 2;\n')
    fanim.write('set key below right;\n')
    fanim.write('set key textcolor lt 0;\n')
    fanim.write('set xl textcolor lt 0;\n')

    fanim.write('n=%d;\n' % interval)
    fanim.write('load "frame.plt";\n')