#! /usr/bin/python
# -*- coding: utf-8 -*-

### HtmlFactory
def setImage(f, width, *imgnames):
    """ 画像をセットする """
    outputLine(f, '<!-- IMAGE -->')
    outputLine(f, '<table class="graph">')
    for name in imgnames:
        outputLine(f, '    <tr><td><img src="%s" width="%d"/></td></tr>' % (name, width))
    outputLine(f, '</table>')

def outputHeader(f, htext, h):
    """ 見出しを設定する """
    outputLine(f, '<h%d>%s</h%d>' % (h, htext, h))

def outputSection(f, htext, h, *imgs):
    """ 見出し、画像をセットし、セクションを作る """
    outputHeader(f, htext, h)
    for img in imgs:
        setImage(f, RESULT_WIDTH, img)

def read_config( config_fname, SEP0='', SEP1=': ', SEP2='\n' ):
  body = ""
  f = open(config_fname, 'r')
  for l in f:
    ll = l.split()
    lc = l.split(':')
    if('=' in ll):
      if(':' in l):
        body += '%s%s%s%s%s' % (SEP0, lc[1], SEP1, ll[4], SEP2)
      else:
        body += '%s%s%s%s%s' % (SEP0, ll[2], SEP1, ll[4], SEP2)
  return body

def read_info( info_fname, SEP0='', SEP1=': ', SEP2='\n' ):
  body = ""
  f = open(info_fname, 'r')
  for l in f:
    ll = l.split(',')
    if len(ll) == 3:
      body += '%s%s%s%s%s' % (SEP0, ll[2], SEP1, ll[1], SEP2)
  return body

class HtmlFactory(object):
    """ 結果表示用のHTMLを出力する """
    def __init__(self, filename):
        self.file = open(filename, 'w')
    def close(self):
        self.file.close()
    def generate(self):
        # Init
        outputLine(self.file,
            '<html><link rel="stylesheet" href="%s">' % CSS_DIR +
            '<body><font color=gray><code>')
        outputHeader(self.file, '<font color=black># RESULT</font>', 1)

        # 初期設定を表示
        outputHeader(self.file, 'Config', 2)
        config = '<table>'
        config += '%s' % read_info(
            INFO_FNAME, '<tr><td>', '</td><td>', '</td></tr>'
            )
        config += '</table>'
        outputLine( self.file, config )

        # Image Section
        outputSection(self.file, 'Population', 2, IMG('Population'))
        outputSection(self.file, 'HasViruses', 2, IMG('HasViruses'))
        outputSection(self.file, 'VirusVariaty', 2, IMG('VirusVariaty'))
        outputSection(self.file, 'Incubation/Crisis', 2, IMG('IsIncubation'), IMG('IsCrisis'))
        outputSection(self.file, 'Removed', 2, IMG('Removed'))
        outputSection(self.file, 'Value', 2, IMG('VirusValue'), IMG('AgentValue'))

        # End
        outputLine(self.file, '</code></body></html>')

