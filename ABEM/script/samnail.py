#coding=utf-8
import os

FNAME = 'samnail.html'
FNAME_VIRUSVALUE = 'samnail-virusvalue.html'
BR = '<br />\n'
IMAGE = 'VirusValue.png'

f = open( FNAME, 'w' )

body = '<html><body>'

def imageTag(img, width, dirname=''):
  tag = '<a href="%s/index.html"><img src="%s" width="%s"></img></a>' % (dirname, img, width)
  return tag

body += '<table border=5>'
body += '<tr><td>ディレクトリ</td><td>ウイルス平均値</td><td>ウイルス種類</td></tr>'
for dirname in os.listdir('.'):
  if dirname[:6] != 'result': continue
  body += '<tr><td>'
  body += dirname
  body += '</td><td>'
  body += imageTag('%s/image/%s'  % (dirname, IMAGE), '300px', dirname)
  body += '</td><td>'
  body += imageTag('%s/image/%s'  % (dirname, 'VirusVariaty.png'), '300px', dirname)
  body += '</td></tr>'
body += '</table>'

body += '</body></html>'
f.write( body )
f.close()

# file 2
f_virusvalue = open( FNAME_VIRUSVALUE, 'w' )

body = '<html><body>'
body += '<table border=5>'

body += '<tr><td></td><td colspan="21">症候性期間</td></tr>\n'


body += '<tr><td rowspan="21">潜伏期間</td><td></td>'
for i in range(20):
  body += '<td>%d</td>' % i
body += '</tr>\n'

for i in range(20):
  body += '<tr>'
  body += '<td>%d</td>' % i
  for dirname in os.listdir('.'):
    if dirname[:6] != 'result': continue
    if 'IN'+str(i)+'SY' in dirname:
      body += '<td>'
      body += imageTag('%s/image/%s'  % (dirname, IMAGE), '300px', dirname)
      body += '</td>'
  body += '</tr>\n'


body += '</table>'
body += '</body></html>'

f_virusvalue.write( body )
f_virusvalue.close()
