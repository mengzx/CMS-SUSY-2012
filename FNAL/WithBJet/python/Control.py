#!/usr/bin/env python
import setupSUSY
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
import DataSet_FNAL
import DataSet_IC
#--------------------------------------------control parameters--------
def TransFromStringToOther(sTreeThr, ssample, sMuonForm, sSplitForm, sSite):
  TreeThr=100.
  sample=WJet_Sample_LowHTBins
  MuonForm=None
  SplitForm=None

    
  if sTreeThr is "100":
    TreeThr=100.
  elif sTreeThr is "86":
    TreeThr=100.*(325./375.)
  if sTreeThr is "73":
    TreeThr=100.*(275./375.)

  if ssample is "WJ":
    if sTreeThr is "86" or sTreeThr is "73":
      if sSite is "FNAL":
        sample=DataSet_FNAL.WJet_Sample_LowHTBins
      elif sSite is "IC":
        sample=DataSet_IC.WJet_Sample_LowHTBins
    elif sTreeThr is "100":
      if sSite is "FNAL":
        sample=DataSet_FNAL.WJet_Sample_HighHTBins
      elif sSite is "IC":
        sample=DataSet_IC.WJet_Sample_HighHTBins
  elif ssample is "ALL":
    if sTreeThr is "86" or sTreeThr is "73":
      sample=Summer11_MC_LowHTBins
    elif sTreeThr is "100":
      sample=Summer11_MC_HighHTBins
  elif ssample is "ALL_NoZinv":
    if sTreeThr is "86" or sTreeThr is "73":
      sample=Summer11_MC_NoZinv_LowHTBins
    elif sTreeThr is "100":
      sample=Summer11_MC_NoZinv_HighHTBins
  elif ssample is "TT":
    if sSite is "FNAL":
      sample=DataSet_FNAL.TTbar_Sample
    elif sSite is "IC":
      sample=DataSet_IC.TTbar_Sample
  elif ssample is "SingleT":
    sample=SingleT_Sample
  elif ssample is "Zinv":
    sample=Zinv_Sample
  elif ssample is "DY":
    if sSite is "FNAL":
      sample=DataSet_FNAL.DiMuon_Sample
    elif sSite is "IC":
      sample=DataSet_IC.DiMuon_Sample
  elif ssample is "DiBoson":
    sample=DiBoson_Sample
  elif ssample is "TanB10_1800_280":
    sample=Tanb10_1800_280_Sample
  elif ssample is "TanB10_320_520":
    sample=Tanb10_320_520_Sample
  elif ssample is "T2":
    sample=T2_Sample
  elif ssample is "T2tt":
    sample=T2tt_Sample
  elif ssample is "DataHT":
    sample=DataHT_Sample_2011AB
  elif ssample is "DataHT_2011A":
    sample=DataHT_Sample_2011A
  elif ssample is "DataHT_2011B":
    sample=DataHT_Sample_2011B
  elif ssample is "DataMuHad":
    sample=DataMuHad_Sample_2011AB
  elif ssample is "DataMuHad_2011A":
    sample=DataMuHad_Sample_2011A
  elif ssample is "DataMuHad_2011B":
    sample=DataMuHad_Sample_2011B
  elif ssample is "DataSingleMu":
    sample=DataSingleMu_Sample_2011AB
  elif ssample is "DataSingleMu2011A":
    sample=DataSingleMu_Sample_2011A
  elif ssample is "DataSingleMu2011B":
    sample=DataSingleMu_Sample_2011B
  elif ssample is "DataSingleMu2012A":
      if sSite is "FNAL":
        sample=DataSet_FNAL.DataSingleMu_Sample_2012A
      elif sSite is "IC":
        sample=DataSet_IC.DataSingleMu_Sample_2012A
  elif ssample is "DataPhoton2012A":
      if sSite is "FNAL":
        sample=DataSet_FNAL.DataPhoton_Sample_2012A
      elif sSite is "IC":
        sample=DataSet_IC.DataPhoton_Sample_2012A
  elif ssample is "DataMuHad2012A":
      if sSite is "FNAL":
        sample=DataSet_FNAL.DataMuHad_Sample_2012A
      elif sSite is "IC":
        sample=DataSet_IC.DataMuHad_Sample_2012A
  elif ssample is "DataDoubleMu2012A":
      if sSite is "FNAL":
        sample=DataSet_FNAL.DataDoubleMu_Sample_2012A
      elif sSite is "IC":
        sample=DataSet_IC.DataDoubleMu_Sample_2012A
  elif ssample is "DataHT2012A":
      if sSite is "FNAL":
        sample=DataSet_FNAL.DataHT_Sample_2012A
      elif sSite is "IC":
        sample=DataSet_IC.DataHT_Sample_2012A
  elif ssample is "DiMuon_1":
      if sSite is "FNAL":
        sample=DataSet_FNAL.DiMuon_1
      elif sSite is "IC":
        sample=DataSet_IC.DiMuon_1
  elif ssample is "DiMuon_2":
      if sSite is "FNAL":
        sample=DataSet_FNAL.DiMuon_2
      elif sSite is "IC":
        sample=DataSet_IC.DiMuon_2
  elif ssample is "WToENu":
      if sSite is "FNAL":
        sample=DataSet_FNAL.WToENu
      elif sSite is "IC":
        sample=DataSet_IC.WToENu
  elif ssample is "WToMuNu":
      if sSite is "FNAL":
        sample=DataSet_FNAL.WToMuNu
      elif sSite is "IC":
        sample=DataSet_IC.WToMuNu
  elif ssample is "WToTauNu":
      if sSite is "FNAL":
        sample=DataSet_FNAL.WToTauNu
      elif sSite is "IC":
        sample=DataSet_IC.WToTauNu
  elif ssample is "QCD":
      if sSite is "FNAL":
        sample=DataSet_FNAL.QCD
      elif sSite is "IC":
        sample=DataSet_IC.QCD
  else:
    sample=[]
    
  if sMuonForm is "None":
    MuonForm=None
  else:
    MuonForm=sMuonForm

  if sSplitForm is "None":
    SplitForm=None
  else:
    SplitForm=sSplitForm

  return (TreeThr, sample, MuonForm, SplitForm)

def ParaControl( sTreeThr, ssample, sMuonForm, sSplitForm, DataSet, sSite ):
  TreeThr,sample,MuonForm,SplitForm=TransFromStringToOther(sTreeThr, ssample, sMuonForm, sSplitForm, sSite)
  print "in ParaControl"
  print TreeThr,sample,MuonForm,SplitForm
  for i in range(len(sample)):
    print sample[i].Name

  PUS="PUS7"
  ExtraInstruction=""
  RunScriptName="NoSmear"
  SampleIndicated=""

  if int(TreeThr) is 100:
    ExtraInstruction="HigHTBins"
  elif int(TreeThr) is 73:
    ExtraInstruction="LowHTBins"
  elif int(TreeThr) is 86:
    ExtraInstruction="LowHTBins"


  if sample == DataSet_FNAL.WJet_Sample_HighHTBins or sample == DataSet_FNAL.WJet_Sample_LowHTBins or sample == DataSet_IC.WJet_Sample_HighHTBins or sample == DataSet_IC.WJet_Sample_LowHTBins:
    SampleIndicated="WJ"
  elif sample == DataSet_FNAL.TTbar_Sample or sample == DataSet_IC.TTbar_Sample:
    SampleIndicated="TT"
  elif sample == SingleT_Sample:
    SampleIndicated="SingleT"
  elif sample == Zinv_Sample:
    SampleIndicated="Zinv"
  elif sample == DataSet_FNAL.DiMuon_Sample or sample == DataSet_IC.DiMuon_Sample:
    SampleIndicated="DY"
  elif sample == Summer11_MC_HighHTBins:
    SampleIndicated="ALL"
  elif sample == Summer11_MC_LowHTBins:
    SampleIndicated="ALL"
  elif sample == Summer11_MC_NoZinv_HighHTBins:
    SampleIndicated="ALL_NoZinv"
  elif sample == Summer11_MC_NoZinv_LowHTBins:
    SampleIndicated="ALL_NoZinv"
  elif sample == DiBoson_Sample:
    PUS = "PUS6"
    SampleIndicated="DiBoson"
  elif sample == Tanb10_1800_280_Sample:
    SampleIndicated="TanB10_1800_280"
  elif sample == Tanb10_320_520_Sample:
    SampleIndicated="TanB10_320_520"
  elif sample == T2_Sample:
    SampleIndicated="T2"
    PUS = "PUS0"
  elif sample == T2tt_Sample:
    SampleIndicated="T2tt"
    PUS = "PUS0"
  elif sample == DataHT_Sample_2011AB:
    PUS = "PUS0"
    SampleIndicated="HT2011AB"
  elif sample == DataHT_Sample_2011A:
    PUS = "PUS0"
    SampleIndicated="HT2011A"
  elif sample == DataHT_Sample_2011B:
    PUS = "PUS0"
    SampleIndicated="HT2011B"
  elif sample == DataMuHad_Sample_2011AB:
    PUS = "PUS0"
    SampleIndicated="MuHad2011AB"
  elif sample == DataMuHad_Sample_2011A:
    PUS = "PUS0"
    SampleIndicated="MuHad2011A"
  elif sample == DataMuHad_Sample_2011B:
    PUS = "PUS0"
    SampleIndicated="MuHad2011B"
  elif sample == DataSingleMu_Sample_2011AB:
    PUS = "PUS0"
    SampleIndicated="SingleMu2011AB"
  elif sample == DataSingleMu_Sample_2011A:
    PUS = "PUS0"
    SampleIndicated="SingleMu2011A"
  elif sample == DataSingleMu_Sample_2011B:
    PUS = "PUS0"
    SampleIndicated="SingleMu2011B"
  elif sample == DataSet_FNAL.DataSingleMu_Sample_2012A or  sample == DataSet_IC.DataSingleMu_Sample_2012A:
    PUS = "PUS0"
    SampleIndicated="SingleMu2012A"
  elif sample == DataSet_FNAL.DataPhoton_Sample_2012A or sample == DataSet_IC.DataPhoton_Sample_2012A:
    PUS = "PUS0"
    SampleIndicated="Photon2012A"
  elif sample == DataSet_FNAL.DataMuHad_Sample_2012A or sample == DataSet_IC.DataMuHad_Sample_2012A:
    PUS = "PUS0"
    SampleIndicated="MuHad2012A"
  elif sample == DataSet_FNAL.DataDoubleMu_Sample_2012A or sample == DataSet_IC.DataDoubleMu_Sample_2012A:
    PUS = "PUS0"
    SampleIndicated="DoubleMu2012A"
  elif sample == DataSet_FNAL.DataHT_Sample_2012A or sample == DataSet_IC.DataHT_Sample_2012A:
    PUS = "PUS0"
    SampleIndicated="HT2012A"
  elif sample == DataSet_FNAL.DiMuon_1 or sample == DataSet_IC.DiMuon_1:
    SampleIndicated="DiMuon_1"
  elif sample == DataSet_FNAL.DiMuon_2 or sample == DataSet_IC.DiMuon_2:
    SampleIndicated="DiMuon_2"
  elif sample == DataSet_FNAL.WToENu or sample == DataSet_IC.WToENu:
    SampleIndicated="WToENu"
  elif sample == DataSet_FNAL.WToMuNu or sample == DataSet_IC.WToMuNu:
    SampleIndicated="WToMuNu"
  elif sample == DataSet_FNAL.WToTauNu or sample == DataSet_IC.WToTauNu:
    SampleIndicated="WToTauNu"
  elif sample == DataSet_FNAL.QCD or sample == DataSet_IC.QCD:
    SampleIndicated="QCD"
  else:
    SampleIndicated=""


  judgeData=False
  if DataSet == "Data":
    RunScriptName="Data"
    judgeData=True

#----- hadronic or muon

  if MuonForm == None:
    ExtraInstruction=ExtraInstruction+"HadSele"
  elif MuonForm != None and SplitForm == None:
    ExtraInstruction=ExtraInstruction+"MuonHTATTrig"
  elif MuonForm != None and SplitForm == "Muon_All":
    ExtraInstruction=ExtraInstruction+"MuonMuHTTrig"
  elif MuonForm != None and SplitForm == "Muon_Add_SingleMuTrig":
    ExtraInstruction=ExtraInstruction+"MuonAddedSingleMuTrig"
  elif MuonForm != None and SplitForm == "Muon_SingleMuTrig":
    ExtraInstruction=ExtraInstruction+"MuonSingleMuTrig"
  elif MuonForm != None and SplitForm == "Muon_Add_SingleMuTrigPlateau":
    ExtraInstruction=ExtraInstruction+"MuonAddedSingleMuTrigPlateau"
  elif MuonForm != None and SplitForm == "Muon_Add":
    ExtraInstruction=ExtraInstruction+"MuonAddedHTATTrig"

#----- jet pT cut
  JetPtThr = 50.0
  if int(TreeThr) is 100:
    JetPtThr = 50.0
  elif int(TreeThr) is 73:
    JetPtThr = 50.*(275./375.)
    ExtraInstruction=ExtraInstruction+"275"
  elif int(TreeThr) is 86:
    JetPtThr = 50.*(325./375.)
    ExtraInstruction=ExtraInstruction+"325"

  return ( TreeThr, sample, MuonForm, SplitForm, DataSet, JetPtThr, PUS, SampleIndicated, ExtraInstruction, RunScriptName, judgeData, sSite )


