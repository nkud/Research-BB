#!/usr/bin/python
# -*- coding: utf-8 -*-
import smtplib
import glob
import sys
from email.MIMEText import MIMEText
from email.MIMEImage import MIMEImage
from email.MIMEMultipart import MIMEMultipart
from email.Header import Header
from email.Utils import formatdate

def create_message(from_addr, to_addr, subject, body, encoding):
  msg = MIMEMultipart()
  msg['Subject'] = Header(subject, encoding)
  msg['From'] = from_addr
  msg['To'] = to_addr
  msg['Date'] = formatdate()

  related = MIMEMultipart('related')
  alt = MIMEMultipart('alternative')
  related.attach(alt)

  content = MIMEText(body, 'plain', encoding)
  alt.attach(content)

  # 画像を添付
  for filename in glob.glob('image/*.png'):
    print 'attached ' + filename
    fp = file('%s' % filename, 'rb')
    img = MIMEImage(fp.read(), 'png', name=filename)
    related.attach(img)
  for filename in glob.glob('AgentDataBase/*.gif'):
    print 'attached ' + filename
    fp = file('%s' % filename, 'rb')
    img = MIMEImage(fp.read(), 'gif', name=filename)
    related.attach(img)
  for filename in glob.glob('VirusDataBase/*.gif'):
    print 'attached ' + filename
    fp = file('%s' % filename, 'rb')
    img = MIMEImage(fp.read(), 'gif', name=filename)
    related.attach(img)

  msg.attach(related)
  return msg
  pass

def send_via_gmail(from_addr, to_addr, msg):
  s = smtplib.SMTP('smtp.gmail.com', 587)
  s.ehlo()
  s.starttls()
  s.ehlo()
  s.login('su104003@gmail.com', 'mustang009')
  s.sendmail(from_addr, [to_addr], msg.as_string())
  s.close()

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

if __name__ == '__main__':
  argvs = sys.argv
  argc = len(argvs)
  from_addr = 'su104003@gmail.com'
  to_addr = 'su104003@gmail.com'
  #to_addr = 's067803.f0aa8@m.evernote.com'

  title = '数値実験結果'
  if argc > 1:
    title += ': '+argvs[1]
  body = read_config( '../include/Config.h' )
  print body
  msg = create_message(from_addr, to_addr, title, body, 'utf-8')
  send_via_gmail(from_addr, to_addr, msg)

