#!/usr/bin/env python

import os,sys
from ROOT import *
from subprocess import *
import time
import commands


printout=True


p=Popen("qstat", shell=True, stdout=PIPE)

c=p.communicate()

while c[0].split("\n")[0] != '':
    print "I can go to sleep 10mins, jobs not finished"
    time.sleep(600)

print "now go on"

exacutedir=sys.argv[1]

command=commands.getstatusoutput('ls %s' % ( exacutedir ) )
if sys.argv[2] != '':
    matchs=sys.argv[2]
    print matchs
    command=commands.getstatusoutput('ls %s | grep %s' % ( exacutedir, matchs ) )


dirs=command[1].split("\n")
print command

for idir in range( len( dirs ) ):
    fulldir=exacutedir+"/"+dirs[idir]
    c=commands.getstatusoutput('ls %s/%s*.root' % (fulldir, dirs[idir] ) )
    if c[0] == 0:
        print "already exist, so rm"
        commands.getstatusoutput( 'rm %s/%s*.root' % ( fulldir, dirs[idir] ) )

    print "hadd now"
    c=commands.getstatusoutput('hadd %s/%s.root %s/*.root' % (fulldir, dirs[idir], fulldir) )

    if printout:
        print c[1].split('\n')




