#! /usr/bin/python
# coding=utf-8
import os

CONFIG_PATH = 'include/Config.h'

def sed( command, fname ):
  line = 'sed -i -e "%s" %s' % ( command, fname )
  os.system( line )

def configure(inc, sym):
  sed( command_generator( "V_NONINFECTIOUS_PERIOD", "int", str(inc), "潜伏期間") )
  sed( command_generator( "V_INFECTIOUS_PERIOD", "int", str(sym), "症候性期間") )

def command_generator(var, type, value, comment):
  cmd = '/%s/c const %s %s = %s ; /* :%s: */' % (var, type, var, value, comment)
  return cmd

def run(inc, sym):
  command = 'cd ~/workspace/AgentBasedEpidemicModel/ABEM;make build run gene pack mail R="IN%dSY%d"' \
      % ( int(inc), int(sym) )
  os.system( command );


def main():
  inc_range = 20
  sym_range = 20

  for inc in range(inc_range):
    for sym in range(sym_range):
      configure(inc, sym)
      run(inc, sym)

if __name__ == "__main__":
  main();
