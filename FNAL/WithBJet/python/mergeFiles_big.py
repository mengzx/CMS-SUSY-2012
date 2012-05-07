#!/usr/bin/env python

import os,sys
from ROOT import *
from subprocess import *
import time
import commands


printout=True


p=Popen("qstat", shell=True, stdout=PIPE)

c=p.communicate()

#while c[0].split("\n")[0] != '':
#    print "I can go to sleep 10mins, jobs not finished"
#    time.sleep(600)

print "now go on"

exacutedir=sys.argv[1]

command=commands.getstatusoutput('ls %s' % ( exacutedir ) )
if sys.argv[2] != '':
    matchs=sys.argv[2]
    print matchs
    command=commands.getstatusoutput('ls %s | grep %s' % ( exacutedir, matchs ) )


dirs=command[1].split("\n")
print command
nfilesper=(int)(sys.argv[3])


def addSepa( fileslist ):    
    itargetfile=0
    targetslistS=""
    targetslist=[]
    print "fileslen="+str(len( fileslist ))
    while len( fileslist ) >= itargetfile*nfilesper+nfilesper:
        print "itargetfile="+str(itargetfile)
        addedfiles=""
        for iadd in range( nfilesper ):
            addedfiles=addedfiles+" "+fileslist[iadd+itargetfile*nfilesper]
        hadd=commands.getstatusoutput( 'hadd %s/%s_%d.root %s' % ( fulldir, dirs[idir], itargetfile, addedfiles ) )
        targetfile="%s/%s_%d.root" % ( fulldir, dirs[idir], itargetfile )
        targetslistS=targetslistS+targetfile+" "
        targetslist=targetslist+[targetfile]
        itargetfile=itargetfile+1
        addedfiles=""
        print "iter="+str(itargetfile*nfilesper)

    tmp=itargetfile*nfilesper
    left=len(fileslist) % tmp
    print "tmp="+str(tmp)+" left="+str(left)
    if left > 0 and left < nfilesper:
        print "iter="+str((itargetfile+1)*nfilesper)
        addedfiles=""
        for iadd in range( len(fileslist)%tmp ):
            addedfiles=addedfiles+fileslist[iadd+itargetfile*nfilesper]
        hadd=commands.getstatusoutput( 'hadd %s/%s_%d.root %s' % ( fulldir, dirs[idir], itargetfile, addedfiles ) )
        targetfile="%s/%s_%d.root" % ( fulldir, dirs[idir], itargetfile )
        targetslistS=targetslistS+targetfile+" "
        targetslist=targetslist+[targetfile]
        addedfiles=""

    return (targetslistS,targetslist)


for idir in range( len( dirs ) ):
    fulldir=exacutedir+"/"+dirs[idir]
    lstargetfiles=commands.getstatusoutput('ls %s/%s*.root' % (fulldir, dirs[idir] ) )
    if lstargetfiles[0] == 0:
        print "already exist, so rm"
        commands.getstatusoutput( 'rm %s/%s*.root' % ( fulldir, dirs[idir] ) )

    print "go on with clean area: without existed target file"
    fileslist=(commands.getstatusoutput('ls %s/*.root' % ( fulldir ) ))[1].split("\n")
    targetslistS,targetslist=addSepa(fileslist)
    print "hadd now"
    c=commands.getstatusoutput('hadd %s/%s.root %s' % (fulldir, dirs[idir], targetslistS) )

    if printout:
        print c[1].split('\n')


