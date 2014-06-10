def value(v):
	ret = 0
	for i in range(len(v)):
		ret += int(v[i])
	return ret
def out(n):
	fi = open('%d_VirusDataBase.txt' % n, 'r')
	fo = open('%d_VirusValueDistribution.txt' % n, 'w')

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

fo = open('vd.plt', 'w')
fo.write('set style line 1 lw 2;'
'set key below right;'
'set key textcolor lt 0;'
'set xl textcolor lt 0;'
'set yl textcolor lt 0;'
'set terminal png size 600,400 font "times new roman,13";'
'set xrange[0:60];'
'set yrange[0:500];\n')

def plot(n):
	fo.write('set title "VirusValueGraph";set xl "Value";set yl "Num";'+
	'plot "%d_VirusValueDistribution.txt" using 1:2 w boxes title "num";' % n+
	'set output "%d_vvd.png";' % n +
	'replot;'
	'set output;\n')

for i in range(20):
	out((i+1)*500)
	plot((i+1)*500)