#! /usr/bin/python
# -*- coding: utf-8 -*-

""" gnuplot用出力関数
CONFIGUREを無くしたい
"""

import os

### CONFIGURE #################################################################
INIT_LINE_STYLE = 'set style line 1 lw 2'
LINE_STYLE = 'w l'
IMG_SIZE = '1200,300'
RESULT_WIDTH = 1000
CSS_DIR = '../template/result.css'
IMG_EXT = 'png'
FONT = 'times new roman,13'

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
    output_line(f, 'set key below right')
    #output_line(f, 'set key box lt 0 lw 1 ')
    output_line(f, 'set key textcolor lt 0')
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

def set_terminal(f, ext=IMG_EXT):
    """ 出力形式を指定
    画像サイズ、フォントも指定する。
    Args:
        f ファイルオブジェクト
        ext 拡張子
    """
    output_line(f, 'set terminal %s size %s font "%s";' % (ext, IMG_SIZE, FONT))

def plot_with_title(f, text='notitle', title='notitle', using='1:2'):
    """ Plot File With Title, Using """
    output_line(f, 'plot "%s" using %s %s title "%s"' % (text, using, LINE_STYLE, title))

def replot_with_title(f, text='notitle', title='notitle', using='1:2'):
    """ Replot File With Title, Using """
    output_line(f, 'replot "%s" using %s %s title "%s"' % (text, using, LINE_STYLE, title))

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
        if len(i)==2:
            iname, ll = i[0], i[1]
            if first:
                plot_with_title(f, iname, ll)
                first = False
                continue
            replot_with_title(f, iname, ll)
        else:
            iname, ll, using = i[0], i[1], i[2]
            if first:
                plot_with_title(f, iname, ll, using)
                first = False
                continue
            replot_with_title(f, iname, ll, using)
    set_output(f, imgname)
    end_plot(f)

def make_dir(dir_name):
    if os.path.exists(dir_name):
        return False
    os.mkdir(dir_name)
    return True;

