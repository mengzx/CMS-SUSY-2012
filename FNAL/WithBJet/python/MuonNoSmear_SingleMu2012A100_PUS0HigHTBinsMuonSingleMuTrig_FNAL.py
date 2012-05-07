#!/usr/bin/env python

import setupSUSY

import re

from libFrameworkSUSY import *

from libzmeng import *

from libHadronic import *

from libOneLepton import *

from icf.core import PSet,Analysis

from time import strftime

import icf.utils as Utils

from batchGolden import *

from ra1objectid.vbtfElectronId_cff import *

from ra1objectid.vbtfMuonId_cff import *

from ra1objectid.ra3PhotonId_cff import *

from Control import *





sTreeThr="100"

ssample="DataSingleMu2012A"

sMuonForm="True"

sSplitForm="Muon_SingleMuTrig"

DataSet="Data"

sSite = "FNAL"

sIllustration = "_524p1"



TreeThr,sample,MuonForm,SplitForm,DataSet,JetPtThr,PUS,SampleIndicated,ExtraInstruction,RunScriptName,judgeData, sSite = ParaControl( sTreeThr, ssample, sMuonForm, sSplitForm, DataSet, sSite )

if sSite is "FNAL":

  from DataSet_FNAL import *

elif sSite is "IC":

  from DataSet_IC import *

  

print "in MuonNoSmear"

print TreeThr,sample,MuonForm,SplitForm,DataSet,JetPtThr,PUS,SampleIndicated,ExtraInstruction,RunScriptName,judgeData, sSite

for i in range(len(sample)):

  print sample[i].Name









default_common.Jets.PtCut = JetPtThr



cutTreeMC,junkVar,l = MakeMCTree(TreeThr, Muon = MuonForm, Split = SplitForm)

if DataSet == "Data":

  cutTreeMC,junkVar,l = MakeDataTree(TreeThr, Muon = MuonForm, Split = SplitForm)

  

vbtfMuonId_cff = Muon_IDFilter( vbtfmuonidps.ps()  )

vbtfElectronIdFilter = Electron_IDFilter( vbtfelectronidWP95ps.ps() )

ra3PhotonIdFilter    = Photon_IDFilter( ra3photonidps.ps() )

CustomMuID = OL_CustomVBTFMuID(mu_id_higher.ps())



if MuonForm == None or ( MuonForm != None and SplitForm == "Muon_All" and ( TreeThr is 73. or 86. ) ):

  CustomMuID = OL_CustomVBTFMuID(mu_id_lower.ps())

else:

  CustomMuID = OL_CustomVBTFMuID(mu_id_higher.ps())

  

print TreeThr,sample,MuonForm,SplitForm,DataSet,JetPtThr,PUS,SampleIndicated,ExtraInstruction,RunScriptName,judgeData, sSite

def addCutFlowMC(b) :

  print PUS

  if PUS == "PUS4" and DataSet == "MC":

    b.AddWeightFilter("Weight", vertex_reweight_PUS4)

  elif PUS == "PUS6" and DataSet == "MC":

    b.AddWeightFilter("Weight", vertex_reweight_PUS6)

  elif DataSet == "Data":

    print "It's Data"

  elif PUS != "PUS4" and PUS != "PUS6" and DataSet == "MC":

    print "Vertex reweighting is not applied"

  b.AddMuonFilter("PreCC",CustomMuID)

  b.AddPhotonFilter("PreCC",ra3PhotonIdFilter)

  b.AddElectronFilter("PreCC",vbtfElectronIdFilter)

  b+=cutTreeMC



print "in MuonNoSmear"

print TreeThr,sample,MuonForm,SplitForm,DataSet,JetPtThr,PUS,SampleIndicated,ExtraInstruction,RunScriptName,judgeData, sSite

for i in range(len(sample)):

  print sample[i].Name



#AK5 Calo

conf_ak5_caloMC = deepcopy(defaultConfig)

conf_ak5_caloMC.Ntuple = deepcopy(ak5_calo)

conf_ak5_caloMC.XCleaning = deepcopy(default_cc)

conf_ak5_caloMC.Common = deepcopy(default_common)

conf_ak5_caloMC.Common.print_out()

anal_ak5_caloMC=Analysis("AK5Calo")

addCutFlowMC(anal_ak5_caloMC)



#outDir = "../results_"+strftime("%d_%b")+"//MuonNoSmearTT/"

outDir = "../results_"+strftime("%d_%b")+("//%s%s_%s%s%s/" % (RunScriptName, SampleIndicated, PUS, ExtraInstruction, sIllustration) )

ensure_dir(outDir)



anal_ak5_caloMC.Run(outDir,conf_ak5_caloMC,sample)



