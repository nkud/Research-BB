def value(v):
	ret = 0
	for i in range(len(v)):
		ret += int(v[i])
	return ret
def out(n):
	fi = open('%d_AgentGeneDistribution.txt' % n, 'r')
	fo = open('%d_agd.txt' % n, 'w')

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

fo = open('agd.plt', 'w')
fo.write('set style line 1 lw 2;'
'set key below right;'
'set key textcolor lt 0;'
'set xl textcolor lt 0;'
'set yl textcolor lt 0;'
'set terminal png size 600,400 font "times new roman,13";'
'set xrange[0:200];'
'set yrange[0:200];\n')

def plot(n):
	fo.write('set title "AgentGeneDistribution";set xl "Value";set yl "Num";'+
	'plot "%d_agd.txt" using 1:2 w boxes title "num";' % n+
	'set output "%d_agd.png";' % n +
	'replot;'
	'set output;\n')

for i in range(20):
	out((i+1)*500)
	plot((i+1)*500)