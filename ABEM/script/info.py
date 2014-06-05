LEN = 12
NUM = 20

def calcDataBase(fi, fo):
	data = []
	for i in range(LEN):
		data.append(0)

	num = 0
	for tag in fi:
		num += 1
		for i in range(len(tag)-1):
			data[i] += int(tag[i])

	print data,
	print num

	for i in range(LEN):
		fo.write('%d %f\n' % (i+1, float(data[i])/num))

for i in range(NUM):
	fi = open('%s_VirusDataBase.txt' % str(i+1), 'r')
	fo = open('%s_statics.txt' % str(i+1), 'w')
	calcDataBase(fi, fo)

fplot = open('info.plt', 'w')
fplot.write('set style line 1 lw 2\n')
fplot.write('set key below right\n')
fplot.write('set key textcolor lt 0\n')
fplot.write('set xl textcolor lt 0\n')
fplot.write('set yl textcolor lt 0\n')
fplot.write('set terminal png size 600,300 font "times new roman,12";\n')

for i in range(NUM):
	fplot.write('set title "%s000";set xl "Value";set yl "Average";\n' % str(i+1))
	fplot.write('plot "%s_statics.txt" using 1:2 w boxes title "value"\n' % str(i+1))
	fplot.write('set output "%s_boxes.png";\n' % str(i+1))
	fplot.write('replot\n')
	fplot.write('set output\n')
