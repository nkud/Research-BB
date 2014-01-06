#! /usr/bin/python

import sys
import os
import glob

result_list = glob.glob("1*")
result_list.reverse()
of = open("Master.html", "w")

of.write( '<html><head><link rel="stylesheet" href="master.css"></head><body>' )
of.write( '<table>\n' )
for result in result_list:
    of.write( '<tr><td>' )
    of.write( '<a href="'+result+'/RESULT.html">' )
    of.write( result )
    of.write( '</a></td></tr>\n' )
of.write( '</table>\n' )
of.write( '<body><html>' )

