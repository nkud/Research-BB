#! /usr/bin/python
# -*- coding: utf-8 -*-

### CONFIGURE #################################################################
INIT_LINE_STYLE = 'set style line 1 lw 2'
LINE_STYLE = 'w l'
IMG_SIZE = '1200,300'
RESULT_WIDTH = 1000
CSS_DIR = '../template/result.css'
IMG_EXT = 'png'
FONT = 'times new roman,13'

IMG_DIR = ''
TXT_DIR = ''
CONFIG_FNAME = '../include/Config.hpp'
INFO_FNAME = 'INFO.txt'
###############################################################################

""" HTML生成関数
"""

def IMG(img):
    """ 画像の拡張子を設定
    Args:
        img 画像の名前
    Returns:
        拡張子付きのファイル名
    """
    return '%s%s.%s' % (IMG_DIR, img, IMG_EXT)

def output_line(f, line):
    """ １行出力するして開業
    Args:
        f ファイルオブジェクト
        line 出力する文字列
    """
    f.write(line+'\n')

def output_img(f, width, *imgfnames):
    """ 画像を設定する
    Args:
        f ファイルオブジェクト
        width 画像の幅
        imgfnames 画像ファイル名
    """
    output_line(f, '<!-- IMAGE -->')
    output_line(f, '<table class="graph">')
    for fname in imgfnames:
        output_line(f, '\t<tr><td><img src="%s" width="%d"/></td></tr>' % (fname, width))
    output_line(f, '</table>')

def output_header(f, htext, h):
    """ 見出しを設定する """
    output_line(f, '<h%d>%s</h%d>' % (h, htext, h))

def output_section(f, htext, h, *imgs):
    """ 見出し、画像をセットし、セクションを作る """
    output_header(f, htext, h)
    for img in imgs:
        output_img(f, RESULT_WIDTH, img)

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
        self.section_list_ = []

    def setSection(self, title, hlevel, *imgs):
        self.section_list_.append( (title, hlevel, imgs) )

    def setConfig(self):
        pass
    def setCss(self):
        pass
    def generate(self):
        # Init
        output_line(self.file, '<html>')
        output_line(self.file, '<link rel="stylesheet" href="%s"><body>' % CSS_DIR)
        output_header(self.file, '<font color=black># RESULT</font>', 1)

        # 初期設定を表示
        # output_header(self.file, 'Config', 2)
        # config = '<table>'
        # config += '%s' % read_info(
        #     INFO_FNAME, '<tr><td>', '</td><td>', '</td></tr>'
        #     )
        # config += '</table>'
        # output_line( self.file, config )
        self.setConfig()

        # Image Section
        for s in self.section_list_:
            output_section(self.file, s[0], s[1], *s[2])

        # End
        output_line(self.file, '</body></html>')
