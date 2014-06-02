#! /usr/bin/python
# coding=utf-8

### CONFIGURE #################################################################
INIT_LINE_STYLE = 'set style line 1 lw 2'
LINE_STYLE = 'w l'
IMG_SIZE = '1200,300'
RESULT_WIDTH = 1000
CSS_DIR = ''
EXTENSION = 'svg'
FONT = 'Arial,12'
###############################################################################

def IMG(img):
    return img+'.'+EXTENSION
def TXT(title, ext='txt'):
    return '%s.%s' % (title, ext)

### Plot Script
def scriptForInitSetting(f):
    """ 初期化設定
    Args:
        file
    Yields:
        initial setting for plot.
    """
    outputLine(f, INIT_LINE_STYLE)
    # outputLine(f, 'set terminal png size '+IMG_SIZE)
    outputLine(f, 'set key below right')
    #outputLine(f, 'set key box lt 0 lw 1 ')
    outputLine(f, 'set key textcolor lt 0')
    outputLine(f, 'set xl textcolor lt 0')
    outputLine(f, 'set yl textcolor lt 0')

def outputLine(f, line):
    """ Write Line To File """
    f.write(line+'\n')

def initImg(f, title, xl, yl):
    """ タイトル、ラベルを初期化 """
    outputLine(f, 'set title "%s";set xl "%s";set yl "%s";' % (title, xl, yl))

def outputImg(f, imgname, ext=EXTENSION):
    """ 出力先ファイルを指定 """
    outputLine(f, 'set output "%s.%s";' % (imgname, ext))

def outputTerminal(f, ext=EXTENSION):
    """ 出力形式を指定 """
    outputLine(f, 'set terminal %s size %s font "%s";' % (ext, IMG_SIZE, FONT))

def plot_script(f, text='notitle', title='notitle', using='1:2'):   
    """ Plot File With Title, Using """
    outputLine(f, 'plot "%s" using %s %s title "%s"' % (text, using, LINE_STYLE, title))

def replot_script(f, text='notitle', title='notitle', using='1:2'):
    """ Replot File With Title, Using """
    outputLine(f, 'replot "%s" using %s %s title "%s"' % (text, using, LINE_STYLE, title))

def outputEnd(f):
    outputLine(f, 'replot')
    outputLine(f, 'set output')

def output(f, title, xl, yl, outputname, *inputs):
    initImg(f, title, xl, yl)
    first = True
    for i in inputs:
        if len(i)==2:
            iname, ll = i[0], i[1]
            if first:
                plot_script(f, iname, ll)
                first = False
                continue
            replot_script(f, iname, ll)
        else:
            iname, ll, using = i[0], i[1], i[2]
            if first:
                plot_script(f, iname, ll, using)
                first = False
                continue
            replot_script(f, iname, ll, using)
    outputImg(f, outputname)
    outputEnd(f)

### PlotFacroty
class PlotFactory(object):
    """ Gnuplot用のファイルを出力する """
    def __init__(self, filename):
        self.file = open(filename, 'w')
    def close(self):
        self.file.close()

    def generate(self):
        scriptForInitSetting(self.file)
        outputTerminal(self.file)
        output(self.file, 'VirusVariaty', 'Term', 'Variaty', 'VirusVariaty', ('V_virusVariaty.txt', 'Variaty'))
        output(self.file, 'Population', 'Term', 'Agent', 'Population', ('A_population.txt', 'Agent'))
        output(self.file, 'IsIncubation', 'Term', 'Agent', 'IsIncubation', ('A_isIncubation.txt', 'Agent'))
        output(self.file, 'IsCrisis', 'Term', 'Agent', 'IsCrisis', (TXT('A_isCrisis'), 'Agent'))
        output(self.file, 'HasViruses', 'Term', 'Agent', 'HasViruses', (TXT('A_hasViruses'), 'Agent'))
        output(self.file, 'Removed', 'Term', 'Agent', 'Removed', (TXT('A_removed'), 'removed'))

    def info(self):
        print 'have started generating PLOT SCRIPT.'

### HtmlFactory
def setImage(f, *imgnames):
    """ 画像をセットする """
    outputLine(f, '<!-- IMAGE -->')
    outputLine(f, '<table class="graph">')
    for name in imgnames:
        outputLine(f, '    <tr><td><img src="%s" width="%d"/></td></tr>' % (name, RESULT_WIDTH))
    outputLine(f, '<tr></table>')

def outputHeader(f, htext, h):
    """ 見出しを設定する """
    outputLine(f, '<h'+str(h)+'>'+htext+'</'+str(h)+'>')

def outputSection(f, htext, h, *imgs):
    """ 見出し、画像をセットし、セクションを作る """
    outputHeader(f, htext, h)
    for img in imgs:
        setImage(f, img)

class HtmlFactory(object):
    """ 結果表示用のＨＴＭＬを出力する """
    def __init__(self, filename):
        self.file = open(filename, 'w')
    def close(self):
        self.file.close()
    def generate(self):
        # Init
        outputLine(self.file,
                '<html><link rel="stylesheet" href="'+CSS_DIR+'">'
                '<body><font color=gray><code>')
        outputHeader(self.file, '<font color=black># RESULT</font>', 1)

        # Image Section
        outputSection(self.file, 'Population', 2, IMG('Population'))
        outputSection(self.file, 'HasViruses', 2, IMG('HasViruses'))
        outputSection(self.file, 'VirusVariaty', 2, IMG('VirusVariaty'))
        outputSection(self.file, 'Incubation/Crisis', 2, IMG('IsIncubation'), IMG('IsCrisis'))
        outputSection(self.file, 'Removed', 2, IMG('Removed'))

        # End
        outputLine(self.file, '</code></body></html>')
