#! /usr/bin/python
# -*- coding: utf-8 -*-

""" gnuplot用出力関数
CONFIGUREを無くしたい
"""

import os

DEFAULT_EXT = 'png'
DEFAULT_IMG_SIZE = '1200,200'
DEFAULT_LINE_STYLE = 'w boxes'
DEFAULT_FONT = 'courier,11'
### CONFIGURE #################################################################
INIT_LINE_STYLE = 'set style line 1 lw 2'
LINE_STYLE = 'w boxes'
# IMG_SIZE = '1200,280'
# RESULT_WIDTH = 1000
CSS_DIR = '../template/result.css'
IMG_EXT = 'png'
FONT = 'verdana,13'

IMG_DIR = 'image/'
TXT_DIR = ''
CONFIG_FNAME = '../include/Config.h'
INFO_FNAME = 'INFO.txt'
###############################################################################

def IMG(img):
    """ 画像の拡張子を設定
    Args:
        img 画像の名前
    Returns:
        拡張子付きのファイル名
    """
    return '%s%s.%s' % (IMG_DIR, img, IMG_EXT)

def TXT(title, ext='txt'):
    """ テキストファイルの拡張子を設定
    Args:
        title テキストファイルの名前
    Returns:
        拡張子付きのファイル名
    """
    return '%s%s.%s' % (TXT_DIR, title, ext)

def output_line(f, line):
    """ １行出力するして開業
    Args:
        f ファイルオブジェクト
        line 出力する文字列
    """
    f.write(line+'\n')

def initialize_for_plot(f):
    """ 初期化設定
    Args:
        file 出力するファイルオブジェクト
    Yields:
        プロットのための初期設定
        表示形式など
        凡例
    """
    output_line(f, INIT_LINE_STYLE)
    # output_line(f, 'set terminal png size '+IMG_SIZE)
    output_line(f, 'set key top left')
    #output_line(f, 'set key box lt 0 lw 1 ')
    # output_line(f, 'set key textcolor lt 0')
    output_line(f, 'set xl textcolor lt 0')
    output_line(f, 'set yl textcolor lt 0')

def set_img_title_and_label(f, title, xl, yl):
    """ タイトル、ラベルを初期化
    Args:
        f ファイルオブジェクト
        title グラフのタイトル
        xl x座標のラベル
        yl y座標のラベル
    """
    output_line(f, 'set title "%s";set xl "%s";set yl "%s";' % (title, xl, yl))

def set_output(f, image, ext=IMG_EXT):
    """ 出力先ファイルを指定
    Args:
        imgname 画像名
        ext 拡張子
    """
    output_line(f, 'set output "%s.%s";' % (image, ext))

def set_terminal(f, ext, imgsize, font):
    """ 出力形式を指定
    画像サイズ、フォントも指定する。
    Args:
        f ファイルオブジェクト
        ext 拡張子
    """
    output_line(f, 'set terminal %s size %s font "%s";' % (ext, imgsize, font))

def plot_with_title(f, text='notitle', title='notitle', linestyle=LINE_STYLE, using='1:2'):
    """ Plot File With Title, Using """
    output_line(f, 'plot "%s" using %s %s title "%s"' % (text, using, linestyle, title))

def replot_with_title(f, text='notitle', title='notitle', linestyle=LINE_STYLE, using='1:2'):
    """ Replot File With Title, Using """
    output_line(f, 'replot "%s" using %s %s title "%s"' % (text, using, linestyle, title))

def end_plot(f):
    output_line(f, 'replot')
    output_line(f, 'set output')

def output_img(f, title, xl, yl, imgname, *inputs):
    """ 画像を出力する
    Args:

        f: ファイルオブジェクト
        title: グラフのタイトル
        xl: x軸のラベル
        yl: y軸のラベル
        imgname: 出力ファイル名
        inputs: 入力ファイル名
    """
    set_img_title_and_label(f, title, xl, yl)
    first = True
    for i in inputs:
        if len(i)==3:
            iname, ll, ls = i[0], i[1], i[2]
            if first:
                plot_with_title(f, iname, ll, ls)
                first = False
                continue
            replot_with_title(f, iname, ll, ls)
        elif len(i)==4:
            iname, ll, using, ls = i[0], i[1], i[2], i[3]
            if first:
                plot_with_title(f, iname, ll, ls, using)
                first = False
                continue
            replot_with_title(f, iname, ll, ls, using)
    set_output(f, imgname)
    end_plot(f)

def make_dir(dir_name):
    if os.path.exists(dir_name):
        return False
    os.mkdir(dir_name)
    return True;

class PlotFactory(object):
    def __init__(self, fname):
        self.fo = open(fname, 'w')

        self.extension_ = DEFAULT_EXT
        self.image_size_ = DEFAULT_IMG_SIZE
        self.font_ = DEFAULT_FONT

        self.image_list_ = []

    def generate(self):
        initialize_for_plot(self.fo)
        set_terminal(self.fo, self.extension_, self.image_size_, self.font_)
        for img in self.image_list_:
            output_img(self.fo, img[0], img[1], img[2], img[3], *img[4])

    def setImage(self, title, xlabel, ylabel, imgname,  *inputs):
        """ 画像をセット
        Args:
        title 画像のタイトル
        xlabel x軸のタイトル
        ylabel y軸のタイトル
        imgname 出力画像名
        inputs (入力ファイル名, 汎用タイトル)
        """
        self.image_list_.append( (title, xlabel, ylabel, imgname, inputs) )
        
    def setExtension(self, ext):
        self.extension_ = ext
        
    def setImageSize(self, imgsize):
        self.image_size_ = imgsize
        
    def setFont(self, font):
        self.font_ = font
