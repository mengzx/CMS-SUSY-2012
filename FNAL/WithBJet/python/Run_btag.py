#!/usr/bin/env python
import sys, os
import subprocess
import setupSUSY
from libFrameworkSUSY import *
from libzmeng import *
from libHadronic import *
from libOneLepton import *
from icf.core import PSet,Analysis
from time import strftime
import time
import icf.utils as Utils
from batchGolden import *
from ra1objectid.vbtfElectronId_cff import *
from ra1objectid.vbtfMuonId_cff import *
from ra1objectid.ra3PhotonId_cff import *
import commands
import subprocess
from subprocess import *
from Control import *

def getnewFile( sDataSet, sMuonForm, sSplitForm, sTreeThr, ssample, sFileName ):
    output = open( "MuonNoSmear_"+FileName+".py", "w" )
    for line in open( "MuonNoSmearinvar.py" ):
        line = line.replace( "DATASET", sDataSet )
        line = line.replace( "SMUONFORM", sMuonForm )
        line = line.replace( "SSPLITFORM", sSplitForm )
        line = line.replace( "STREETHR", sTreeThr )
        line = line.replace( "SSAMPLE", ssample )
        output.write(line+"\n")
    output.close()
    return (output, "MuonNoSmear_"+FileName+".py")

    
timesleep=10
list_DataSet=[ "Data", "MC" ]
list_Muon=[ "None" ]
list_SplitForm_o = [ "Muon_Add_SingleMuTrigPlateau" ]
list_TreeThr=[ "73","86", "100" ]
#list_sample_mc = ["Zinv", "WJ", "TT", "SingleT","DiBoson", "DY", "ALL", "TanB10_320_520", "TanB10_1800_280", "T2", "T2tt"]
list_sample_mc = [ "ALL_NoZinv", "DiBoson", "ALL" ]
#list_sample_data = [ "DataHT", "DataHT_2011A", "DataHT_2011B", "DataSingleMu", "DataSingleMu_2011A", "DataSingleMu_2011B"]
list_sample_data = [ "DataHT" ]
list_sample=[]


for idataset in range ( len( list_DataSet ) ):

    for imuon in range( len( list_Muon ) ):

        if list_Muon[imuon] is "None":
            list_SplitForm = [ "None" ]
        else:
            list_SplitForm = list_SplitForm_o

        for isplit in range( len( list_SplitForm ) ):

            for itreethr in range( len( list_TreeThr ) ):

                if list_DataSet[ idataset ] == "MC":

                    list_sample = list_sample_mc
                
                if list_DataSet[ idataset ] == "Data":

                    list_sample = list_sample_data

                for isample in range( len( list_sample ) ):

                    TreeThr,sample,MuonForm,SplitForm,DataSet,JetPtThr,PUS,SampleIndicated,ExtraInstruction,RunScriptName,judgeData = ParaControl( list_TreeThr[itreethr], list_sample[isample], list_Muon[imuon], list_SplitForm[isplit], list_DataSet[idataset] )


                    FileName = "%s%s_%s%s" % (SampleIndicated, list_TreeThr[itreethr], PUS, ExtraInstruction )
                    (output,newFile) = getnewFile( list_DataSet[idataset], list_Muon[imuon], list_SplitForm[isplit], list_TreeThr[itreethr], list_sample[isample] , FileName )
                    print "in Run.py"
                    print list_DataSet[idataset], list_Muon[imuon], list_SplitForm[isplit], list_TreeThr[itreethr], list_sample[isample] , FileName
                    
                    subprocess.call( ["chmod", "+x", "%s" % (newFile) ] )

                    subprocess.call( ["./%s" % (newFile), "-b", "-n50" ] )

                    if idataset != len(list_DataSet)-1 or imuon != len(list_Muon)-1 or isplit != len(list_SplitForm)-1 or itreethr != len(list_TreeThr)-1 or isample != len(list_sample)-1:
                        p=subprocess.Popen("qstat", shell=True, stdout=PIPE)
                        c=p.communicate()
                        while c[0].split("\n")[0] != '':
                            print "job is not finished"
                            time.sleep(30)
                            p=subprocess.Popen("qstat", shell=True, stdout=PIPE)
                            c=p.communicate()
                        print "job is finished"
                        print list_DataSet[idataset], list_Muon[imuon], list_SplitForm[isplit], list_TreeThr[itreethr], list_sample[isample] , FileName
















#                    if list_DataSet[ idataset ] == "Data":
#                        if idataset != len(list_DataSet)-1 or imuon != len(list_Muon)-1 or isplit != len(list_SplitForm)-1 or itreethr != len(list_TreeThr)-1 or isample != len(list_sample)-1:
#                            print "I am data, to avoid incompelet process, sleep 30 mins now:"
#                            p=Popen("qstat", shell=True, stdout=PIPE)
#                            c=p.communicate()
#                            while c[0].split("\n")[0] != '':
#                                print "I can go to sleep 10mins, jobs not finished"
#                                time.sleep(30)
#                            print list_DataSet[idataset], list_Muon[imuon], list_SplitForm[isplit], list_TreeThr[itreethr], list_sample[isample] , FileName
#                            print "Awake now, and submit next one"
                        
#                    if list_DataSet[ idataset ] == "MC":
#                        if idataset != len(list_DataSet)-1 or imuon != len(list_Muon)-1 or isplit != len(list_SplitForm)-1 or itreethr != len(list_TreeThr)-1 or isample != len(list_sample)-1:
#                            print "I am MC, to avoid incompelet process, sleep several mins now:"
#                            p=Popen("qstat", shell=True, stdout=PIPE)
#                            c=p.communicate()
#                            while c[0].split("\n")[0] != '':
#                                print "I can go to sleep 10mins, jobs not finished"
#                                time.sleep(30)
#                            print "Awake now, and submit next one"

                        

                    


                    



