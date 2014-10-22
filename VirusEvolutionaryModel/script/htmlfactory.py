#! /usr/bin/python
# -*- coding: utf-8 -*-

import collections
import datetime

""" HTML生成関数
"""
def output_line(f, line):
    """ １行出力するして開業
    Args:
        f ファイルオブジェクト
        line 出力する文字列
    """
    f.write(line+'\n')

def output_img(f, *imgfnames):
    """ 画像を設定する
    Args:
        f ファイルオブジェクト
        imgfnames 画像ファイル名
    """
    output_line(f, '<!-- IMAGE -->')
    output_line(f, '<table class="graph">')
    for fname in imgfnames:
        output_line(f, '\t<tr><td><img src="%s" /></td></tr>' % fname)
    output_line(f, '</table>')

def output_header(f, htext, h):
    """ 見出しを設定する """
    output_line(f, '<h%d>%s</h%d>' % (h, htext, h))

def output_comment(f, text):
    output_line(f, '<!-- %s -->' % text)

def output_begin_legend( f, title ):
    output_comment( f, 'GRAPH FIELD' )
    output_line(f, '<fieldset><legend>%s</legend>' % title)

def output_end_legend( f ):
    output_line(f, '</fieldset>')
        

def output_section(f, htext, h, *imgs):
    """ 見出し、画像をセットし、セクションを作る """
    # output_header(f, htext, h)
    output_begin_legend(f, htext)
    for img in imgs:
        output_img(f, img)
    output_end_legend(f)

def get_date_string():
    """ 日付の文字列を取得する """
    dstring = ""

    return dstring

#def read_config( config_fname, SEP0='', SEP1=': ', SEP2='\n' ):
  #body = ""
  #f = open(config_fname, 'r')
  #for l in f:
    #ll = l.split()
    #lc = l.split(':')
    #if('=' in ll):
      #if(':' in l):
        #body += '%s%s%s%s%s' % (SEP0, lc[1], SEP1, ll[4], SEP2)
      #else:
        #body += '%s%s%s%s%s' % (SEP0, ll[2], SEP1, ll[4], SEP2)
  #return body

#def read_info( info_fname, SEP0='', SEP1=': ', SEP2='\n' ):
  #body = ""
  #f = open(info_fname, 'r')
  #for l in f:
    #ll = l.split(',')
    #if len(ll) == 3:
      #body += '%s%s%s%s%s' % (SEP0, ll[2], SEP1, ll[1], SEP2)
  #return body

class HtmlFactory(object):
    """ 結果表示用のHTMLを出力する """
    def __init__(self, filename):
        self.file = open(filename, 'w')
        self.section_list_ = []
        self.info_ = collections.OrderedDict()
        self.color_info_ = collections.OrderedDict()
        self.config_ = []
        self.css_path_ = ''

    def setSection(self, title, hlevel, *imgs):
        self.section_list_.append( (title, hlevel, imgs) )

    def setConfig(self, fname):
        fi = open(fname, 'r')
        for line in fi:
            ll = line.split()
            if '#define' in ll and len(ll)>2:
                self.info_[ll[-2]] = ll[2]
                self.color_info_[ll[-2]] = ll[-1]
        for key in self.info_:
            self.config_.append('\t<tr><td bgcolor="%s" align="center">%s</td><td align="center">%s</td></tr>'
                    % (self.color_info_[key], key, self.info_[key]))

    def setCss(self, csspath):
        self.css_path_ = csspath
    def generate(self):
        # Init
        output_line(self.file, '<html>')
        output_line(self.file, '<link rel="stylesheet" href="%s"><body>' % self.css_path_)
        output_header(self.file, '# Result <sub>%s</sub>' % datetime.datetime.now(), 1)

        if len(self.config_) > 0:
            output_header(self.file, 'Config', 2)
            output_line(self.file, '<table class="config">')
            for line in self.config_:
                output_line(self.file, line)
            output_line(self.file, '</table>')

        output_line(self.file, '<a href="../bin/log.txt">%s</a>' % '&raquo; log')

        # Image Section
        for s in self.section_list_:
            output_section(self.file, s[0], s[1], *s[2])

        # End
        output_line(self.file, '</body></html>')
