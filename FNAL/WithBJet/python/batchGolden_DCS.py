#!/usr/bin/env python
"""
Created by Bryn Mathias on 2010-05-07.
"""
# -----------------------------------------------------------------------------
# Necessary includes
import errno
import os
import re
import setupSUSY
from libFrameworkSUSY import *
from libHadronic import *
from libWPol import *
from libOneLepton import *
from libzmeng import *
from icf.core import PSet,Analysis
from time import strftime
from icf.config import defaultConfig
from icf.utils import json_to_pset
from copy import deepcopy
# -----------------------------------------------------------------------------
# Samples
#import yours in your running script
def ensure_dir(path):
    try:
      os.makedirs(path)
    except OSError as exc: # Python >2.5
      if exc.errno == errno.EEXIST:
        pass
      else: raise



# -----------------------------------------------------------------------------
# Reading the collections from the ntuple

default_ntuple = deepcopy(defaultConfig.Ntuple)
default_ntuple.Electrons=PSet(
Prefix="electron",
Suffix="Pat",
LooseID="EIDLoose",
TightID="EIDTight",
)
default_ntuple.Muons=PSet(
Prefix="muon",
Suffix="Pat",
LooseID="IsGlobalMuon",
TightID="IDGlobalMuonPromptTight",
)
default_ntuple.SecMuons=PSet(
    Prefix="muon",
    Suffix="PF")
default_ntuple.Taus=PSet(
Prefix="tau",
Suffix="Pat",
LooseID="TauIdbyTaNCfrOnePercent",
TightID="TauIdbyTaNCfrTenthPercent"
)
default_ntuple.Jets=PSet(
Prefix="ic5Jet",
Suffix="Pat",
Uncorrected=False,
)
default_ntuple.Photons=PSet(
Prefix="photon",
Suffix="Pat",
)

ic5_calo = deepcopy(default_ntuple)
ic5_calo.Jets.Prefix="ic5Jet"

ak5_calo = deepcopy(default_ntuple)
ak5_calo.Jets.Prefix="ak5Jet"

ak5_jpt = deepcopy(default_ntuple)
ak5_jpt.Jets.Prefix="ak5JetJPT"

ak5_pf = deepcopy(default_ntuple)
ak5_pf.Jets.Prefix="ak5JetPF"
ak5_pf.TerJets.Prefix="ak5Jet"

ak7_calo = deepcopy(default_ntuple)
ak7_calo.Jets.Prefix="ak7Jet"


# -----------------------------------------------------------------------------
# Cross-cleaning settings

default_cc = deepcopy(defaultConfig.XCleaning)
default_cc.Verbose=False
default_cc.MuonJet=True
default_cc.ElectronJet=True
default_cc.PhotonJet=True
default_cc.ResolveConflicts=True
default_cc.Jets.PtCut=10.0
default_cc.Jets.EtaCut=10.0
default_cc.Muons.ModifyJetEnergy=True
default_cc.Muons.PtCut=10.0
default_cc.Muons.EtaCut=2.5
default_cc.Muons.TrkIsoCut=-1.
default_cc.Muons.CombIsoCut=0.15
default_cc.Muons.MuonJetDeltaR=0.5
default_cc.Muons.MuonIsoTypePtCutoff=0.
default_cc.Muons.RequireLooseIdForInitialFilter=False
default_cc.Electrons.PtCut=10.0
default_cc.Electrons.EtaCut=2.5
default_cc.Electrons.TrkIsoCut=-1.0
default_cc.Electrons.CombIsoCut=0.15
default_cc.Electrons.ElectronJetDeltaR=0.5
default_cc.Electrons.ElectronIsoTypePtCutoff=0.
default_cc.Electrons.ElectronLooseIdRequired=True
default_cc.Electrons.ElectronTightIdRequired=False
default_cc.Electrons.RequireLooseIdForInitialFilter=False
default_cc.Photons.EtCut=25.0
default_cc.Photons.EtaCut=2.5
default_cc.Photons.TrkIsoCut=2.0
default_cc.Photons.CaloIsoCut=0.2
default_cc.Photons.IDReq=3
default_cc.Photons.UseID=True
default_cc.Photons.PhotonJetDeltaR=0.5
default_cc.Photons.PhotonIsoTypePtCutoff=30.
# -----------------------------------------------------------------------------
# Definition of common objects
default_common = deepcopy(defaultConfig.Common)
default_common.ApplyXCleaning=True
default_common.Jets.PtCut=50.0
default_common.Jets.EtaCut=3.0
default_common.Jets.ApplyID=True
default_common.Jets.TightID=False
default_common.Electrons.PtCut=10.0
default_common.Electrons.EtaCut=2.5
default_common.Electrons.TrkIsoCut=-1.
default_common.Electrons.CombIsoCut=0.15
default_common.Electrons.ApplyID = True
default_common.Electrons.TightID = False
default_common.Electrons.RequireLooseForOdd = True
default_common.Muons.PtCut=10.0
default_common.Muons.EtaCut=2.5
default_common.Muons.TrkIsoCut=-1.
default_common.Muons.CombIsoCut=0.15
default_common.Muons.ApplyID = True
default_common.Muons.TightID = True
default_common.Muons.RequireLooseForOdd = True
default_common.Photons.EtCut=25.0
# default_common.Photons.EtaCut=2.5
default_common.Photons.UseID=True
# the photon cuts are NOT read anyway
# default_common.Photons.TrkIsoRel=0.
# default_common.Photons.TrkIsoCut=99999.
# default_common.Photons.EcalIsoRel=0.
# default_common.Photons.EcalIsoCut=99999.
# default_common.Photons.HcalIsoRel=0.
# default_common.Photons.HcalIsoCut=99999.
# default_common.Photons.HadOverEmCut=0.5
# default_common.Photons.SigmaIetaIetaCut=0.5
##default_common.Photons.CaloIsoCut=99999.
default_common.Photons.IDReq = 3
default_common.Photons.RequireLooseForOdd = True

skim_ps=PSet(
    SkimName = "myskim",
    DropBranches = False,
    Branches = [
        " keep * "
        ]
)
skim = SkimOp(skim_ps.ps())


#Plot the common plots!

genericPSet_mc = PSet(
DirName      = "275_325Gev",
MinObjects   = 2,
MaxObjects   = 15,
minDR = 0.4 ,
mCut = 2.0 ,
isData = False,
trueTau = False,
mode = "",
BTagAlgo = 5,
BTagAlgoCut = 0.679,
useBTag = True,
StandardPlots     = True,
)

genericPSet_data = PSet(
DirName      = "275_325Gev",
MinObjects   = 2,
MaxObjects   = 15,
minDR = 0.4 ,
mCut = 2.0 ,
isData = True,
trueTau = False,
mode = "",
BTagAlgo = 5,
BTagAlgoCut = 0.679,
useBTag = True,
StandardPlots     = True,
)


def makePlotOp(OP = (), cutTree = None, cut = None, label = ""):
  """docstring for makePlotOp"""
  out = []
  if OP[1] != None:
    plotpset = deepcopy(OP[1])
    plotpset.DirName = label
    print plotpset.DirName
    op = eval(OP[0]+"(plotpset.ps())")
  else:
    op = eval(OP[0])
  out.append(op)
  cutTree.TAttach(cut,op)
  alpha = OP_CommonAlphaTCut(0.55)
  dump = EventDump()
  skim_ps=PSet(
    SkimName = "myskim",
    DropBranches = False,
    Branches = [
        " keep * "
        ]
  )
  skim = SkimOp(skim_ps.ps())
  # out.append(skim)
  # out.append(skim_ps)
  cutTree.TAttach(cut,alpha)
  cutTree.TAttach(alpha,dump)
  # cutTree.TAttach(alpha,skim)
  out.append(alpha)
  out.append(dump)
  return out
  pass

def AddBinedHist(cutTree = None, OP = (), cut = None, htBins = [],TriggerDict = None,lab = "", split = None):
  """docstring for AddBinedHist"""
  out = []
  if TriggerDict is not None:
      for lower,upper in zip(htBins,htBins[1:]+[None]):
        # print "Lower , Upper =", lower , upper
        if int(lower) == 325 and upper is None: continue
        if int(lower) == 375 and upper is None : continue
        # print "continue should have happened now"
        slowerCut=""
        if re.match("Muon_Add", str(split)):
#        if split == "Muon_Add":
            slowerCut=("RECO_CommonHTTakeMuCut(%d)"%lower)
        else:
            slowerCut=("RECO_CommonHTCut(%d)"%lower)
        lowerCut = eval(slowerCut)
        triggerps = PSet(Verbose = False,
        UsePreScaledTriggers = False,
        Triggers = [])
        triggerps.Triggers = TriggerDict["%d%s"%(lower, "_%d"%upper if upper else "")]
        Trigger = OP_MultiTrigger( triggerps.ps() )
        out.append(triggerps)
        out.append(Trigger)
        out.append(lowerCut)
        cutTree.TAttach(cut,Trigger)
        cutTree.TAttach(Trigger,lowerCut)
        if upper:
          supperCut=""
          if re.match("Muon_Add", str(split)):
#          if split == "Muon_Add":
            supperCut=("RECO_CommonHTTakeMuLessThanCut(%d)"%upper)
          else:
            supperCut=("RECO_CommonHTLessThanCut(%d)"%upper)
          upperCut = eval(supperCut)
          out.append(upperCut)
          cutTree.TAttach(lowerCut,upperCut)
        pOps = makePlotOp(cutTree = cutTree, OP = OP, cut = upperCut if upper else lowerCut, label = "%s%d%s"%(lab,lower, "_%d"%upper if upper else ""))
        out.append(pOps) 
  else:
      for lower,upper in zip(htBins,htBins[1:]+[None]):
        if int(lower) == 325 and upper is None: continue
        if int(lower) == 375 and upper is None: continue
        slowerCut=""
        if re.match("Muon_Add", str(split)):
#        if split == "Muon_Add":
            slowerCut=("RECO_CommonHTTakeMuCut(%d)"%lower)
        else:
            slowerCut=("RECO_CommonHTCut(%d)"%lower)
        lowerCut = eval(slowerCut)
        out.append(lowerCut)
        cutTree.TAttach(cut,lowerCut)
        if upper:
          supperCut=""
          if re.match("Muon_Add", str(split) ):
#          if split == "Muon_Add":
            supperCut=("RECO_CommonHTTakeMuLessThanCut(%d)"%upper)
          else:
            supperCut=("RECO_CommonHTLessThanCut(%d)"%upper)
          upperCut = eval(supperCut)
          out.append(upperCut)
          cutTree.TAttach(lowerCut,upperCut)
        pOps = makePlotOp(cutTree = cutTree, OP = OP, cut = upperCut if upper else lowerCut, label = "%s%d%s"%(lab,lower, "_%d"%upper if upper else ""))
        out.append(pOps)
  return out
  pass



# Common cut definitions
#Avaiable criteria for MC and for Data are at current slightly different Hence the making of two trees
#DataOnly!

# from icf.JetCorrections import *
# corPset =  CorrectionPset("ResidualJetEnergyCorrections.txt")
# corPset =  CorrectionPset("Spring10DataV2_L2L3Residual_AK5PF.txt")
# JetCorrections = JESCorrections( corPset.ps(),True )
NoiseFilt= OP_HadronicHBHEnoiseFilter()
GoodVertexMonster = OP_GoodEventSelection()

#Standard Event Selection
LeadingJetEta = OP_FirstJetEta(2.5)
LeadingJetOrMuEta = OP_FirstJetOrMuEta(2.5)
LeadingJetPtCut = OP_FirstJetPtCut(100.)
LeadingJetOrMuPtCut = OP_FirstJetOrMuPtCut(100.)

oddMuon = OP_OddMuon()
oddElectron = OP_OddElectron()
oddPhoton = OP_OddPhoton()
oddJet = OP_OddJet()
badMuonInJet = OP_BadMuonInJet()
numComElectrons = OP_NumComElectrons("<=",0)
numComPhotons = OP_NumComPhotons("<=",0)




ht250_Trigger = RECO_CommonHTCut(250.)
htTakeMu250_Trigger = RECO_CommonHTTakeMuCut(250.)


htCut275 = RECO_CommonHTCut(275.)
htTakeMuCut275 = RECO_CommonHTTakeMuCut(275.)

DeadEcalCutData = OP_DeadECALCut(0.3,0.3,0.5,30.,10,0,"./deadRegionList_GR10_P_V10.txt")
DeadEcalCutMC =   OP_DeadECALCut(0.3,0.3,0.5,30.,10,0,"./deadRegionList_START38_V12.txt")

MHT_METCut = OP_MHToverMET(1.25,50.)
MHTTakeMu_METTakeMuCut = OP_MHTTakeMuoverMETTakeMu(1.25,50.)

DiJet5 = OP_NumComJets(">=",2)



# Define a crap load more plotting ops, for HT exclusive bins



VertexPtOverHT = OP_SumVertexPtOverHT(0.1)
eventDump = EventDump()

triggers = {
    "275_325":["HLT_HT250_AlphaT0p55_v1","HLT_HT250_AlphaT0p57_v1"],
    "325_375":["HLT_HT250_AlphaT0p55_v1","HLT_HT250_AlphaT0p57_v1","HLT_HT300_AlphaT0p53_v1"],
    "375_475":["HLT_HT250_AlphaT0p55_v1","HLT_HT250_AlphaT0p57_v1","HLT_HT300_AlphaT0p53_v1","HLT_HT350_AlphaT0p52_v1","HLT_HT350_AlphaT0p53_v12"],
    "475_575":["HLT_HT250_AlphaT0p55_v1","HLT_HT250_AlphaT0p57_v1","HLT_HT300_AlphaT0p53_v1","HLT_HT350_AlphaT0p52_v1","HLT_HT350_AlphaT0p53_v12","HLT_HT400_AlphaT0p52_v7","HLT_HT450_AlphaT0p51_v7"],
    "575_675":["HLT_HT250_AlphaT0p55_v1","HLT_HT250_AlphaT0p57_v1","HLT_HT300_AlphaT0p53_v1","HLT_HT350_AlphaT0p52_v1","HLT_HT350_AlphaT0p53_v12","HLT_HT400_AlphaT0p52_v7","HLT_HT450_AlphaT0p51_v7"],
    "675_775":["HLT_HT250_AlphaT0p55_v1","HLT_HT250_AlphaT0p57_v1","HLT_HT300_AlphaT0p53_v1","HLT_HT350_AlphaT0p52_v1","HLT_HT350_AlphaT0p53_v12","HLT_HT400_AlphaT0p52_v7","HLT_HT450_AlphaT0p51_v7"],
    "775_875":["HLT_HT250_AlphaT0p55_v1","HLT_HT250_AlphaT0p57_v1","HLT_HT300_AlphaT0p53_v1","HLT_HT350_AlphaT0p52_v1","HLT_HT350_AlphaT0p53_v12","HLT_HT400_AlphaT0p52_v7","HLT_HT450_AlphaT0p51_v7"],
    "875":["HLT_HT250_AlphaT0p55_v1","HLT_HT250_AlphaT0p57_v1","HLT_HT300_AlphaT0p53_v1","HLT_HT350_AlphaT0p52_v1","HLT_HT350_AlphaT0p53_v12","HLT_HT400_AlphaT0p52_v7","HLT_HT450_AlphaT0p51_v7"],
}


mu_triggers = {
 "275_325":["HLT_Mu5_HT200_v3","HLT_Mu5_HT200_v4","HLT_Mu8_HT200_v4","HLT_Mu15_HT200_v2","HLT_Mu15_HT200_v3","HLT_Mu15_HT200_v4","HLT_Mu30_HT200_v1","HLT_Mu30_HT200_v3","HLT_Mu40_HT200_v4","HLT_Mu40_HT300_v4","HLT_Mu40_HT300_v5",], 
 "325_375":["HLT_Mu5_HT200_v3","HLT_Mu5_HT200_v4","HLT_Mu8_HT200_v4","HLT_Mu15_HT200_v2","HLT_Mu15_HT200_v3","HLT_Mu15_HT200_v4","HLT_Mu30_HT200_v1","HLT_Mu30_HT200_v3","HLT_Mu40_HT200_v4","HLT_Mu40_HT300_v4","HLT_Mu40_HT300_v5",],
 "375_475":["HLT_Mu5_HT200_v3","HLT_Mu5_HT200_v4","HLT_Mu8_HT200_v4","HLT_Mu15_HT200_v2","HLT_Mu15_HT200_v3","HLT_Mu15_HT200_v4","HLT_Mu30_HT200_v1","HLT_Mu30_HT200_v3","HLT_Mu40_HT200_v4","HLT_Mu40_HT300_v4","HLT_Mu40_HT300_v5",],
 "475_575":["HLT_Mu5_HT200_v3","HLT_Mu5_HT200_v4","HLT_Mu8_HT200_v4","HLT_Mu15_HT200_v2","HLT_Mu15_HT200_v3","HLT_Mu15_HT200_v4","HLT_Mu30_HT200_v1","HLT_Mu30_HT200_v3","HLT_Mu40_HT200_v4","HLT_Mu40_HT300_v4","HLT_Mu40_HT300_v5",],
 "575_675":["HLT_Mu5_HT200_v3","HLT_Mu5_HT200_v4","HLT_Mu8_HT200_v4","HLT_Mu15_HT200_v2","HLT_Mu15_HT200_v3","HLT_Mu15_HT200_v4","HLT_Mu30_HT200_v1","HLT_Mu30_HT200_v3","HLT_Mu40_HT200_v4","HLT_Mu40_HT300_v4","HLT_Mu40_HT300_v5",],
 "675_775":["HLT_Mu5_HT200_v3","HLT_Mu5_HT200_v4","HLT_Mu8_HT200_v4","HLT_Mu15_HT200_v2","HLT_Mu15_HT200_v3","HLT_Mu15_HT200_v4","HLT_Mu30_HT200_v1","HLT_Mu30_HT200_v3","HLT_Mu40_HT200_v4","HLT_Mu40_HT300_v4","HLT_Mu40_HT300_v5",],
 "775_875":["HLT_Mu5_HT200_v3","HLT_Mu5_HT200_v4","HLT_Mu8_HT200_v4","HLT_Mu15_HT200_v2","HLT_Mu15_HT200_v3","HLT_Mu15_HT200_v4","HLT_Mu30_HT200_v1","HLT_Mu30_HT200_v3","HLT_Mu40_HT200_v4","HLT_Mu40_HT300_v4","HLT_Mu40_HT300_v5",],
 "875":["HLT_Mu5_HT200_v3","HLT_Mu5_HT200_v4","HLT_Mu8_HT200_v4","HLT_Mu15_HT200_v2","HLT_Mu15_HT200_v3","HLT_Mu15_HT200_v4","HLT_Mu30_HT200_v1","HLT_Mu30_HT200_v3","HLT_Mu40_HT200_v4","HLT_Mu40_HT300_v4","HLT_Mu40_HT300_v5",],
 
}

single_mu_triggers = {
  "275_325":["HLT_IsoMu24_eta2p1_v11","HLT_IsoMu30_eta2p1_v11","HLT_IsoMu34_eta2p1_v9","HLT_IsoMu40_eta2p1_v6"],
  "325_375":["HLT_IsoMu24_eta2p1_v11","HLT_IsoMu30_eta2p1_v11","HLT_IsoMu34_eta2p1_v9","HLT_IsoMu40_eta2p1_v6"],
  "375_475":["HLT_IsoMu24_eta2p1_v11","HLT_IsoMu30_eta2p1_v11","HLT_IsoMu34_eta2p1_v9","HLT_IsoMu40_eta2p1_v6"],
  "475_575":["HLT_IsoMu24_eta2p1_v11","HLT_IsoMu30_eta2p1_v11","HLT_IsoMu34_eta2p1_v9","HLT_IsoMu40_eta2p1_v6"],
  "575_675":["HLT_IsoMu24_eta2p1_v11","HLT_IsoMu30_eta2p1_v11","HLT_IsoMu34_eta2p1_v9","HLT_IsoMu40_eta2p1_v6"],
  "675_775":["HLT_IsoMu24_eta2p1_v11","HLT_IsoMu30_eta2p1_v11","HLT_IsoMu34_eta2p1_v9","HLT_IsoMu40_eta2p1_v6"],
  "775_875":["HLT_IsoMu24_eta2p1_v11","HLT_IsoMu30_eta2p1_v11","HLT_IsoMu34_eta2p1_v9","HLT_IsoMu40_eta2p1_v6"],
  "875":["HLT_IsoMu24_eta2p1_v11","HLT_IsoMu30_eta2p1_v11","HLT_IsoMu34_eta2p1_v9","HLT_IsoMu40_eta2p1_v6"],
}

#single_mu_triggers = {
#    "275_325":["HLT_Mu30_v*","HLT_Mu40_eta2p1_v*"],
#    "325_375":["HLT_Mu30_v*","HLT_Mu40_eta2p1_v*"],
#    "375_475":["HLT_Mu30_v*","HLT_Mu40_eta2p1_v*"],
#    "475_575":["HLT_Mu30_v*","HLT_Mu40_eta2p1_v*"],
#    "575_675":["HLT_Mu30_v*","HLT_Mu40_eta2p1_v*"],
#    "675_775":["HLT_Mu30_v*","HLT_Mu40_eta2p1_v*"],
#    "775_875":["HLT_Mu30_v*","HLT_Mu40_eta2p1_v*"],
#    "875":["HLT_Mu30_v*","HLT_Mu40_eta2p1_v*"],
#}


#json = JSONFilter("Json Mask", json_to_pset("./Jad_Test.json"))
#json = JSONFilter("Json Mask", json_to_pset("./Golden2011.json"))
#json = JSONFilter("Json Mask", json_to_pset("./Golden29Mar2012.json"))
#json = JSONFilter("Json Mask", json_to_pset("./mergeHTSingleMuDatasets_29032012.json"))
json = JSONFilter("Json Mask", json_to_pset("./json_DCSONLY.txt") )
#json = JSONFilter("Json Mask", json_to_pset(""))
# AlphatTriggerCut(0.52414,50)#
# vertex_reweight = VertexReweighting(
# PSet(
# VertexWeights =[0.20, 0.63, 1.19, 1.57, 1.62, 1.42, 1.09, 0.80 ,0.57, 0.42, 0.30, 0.20]
# # VertexWeights = [0.0, 0.027442995662725636, 0.12682983875287387, 0.28326829632076572, 0.40618954180036759, 0.41605144586432974, 0.33147399297403923, 0.21562021576661147, 0.1140047132529971]
# ).ps())


recHitCut = OP_SumRecHitPtCut(30.)
ZeroMuon = OP_NumComMuons("<=",0)
json_ouput = JSONOutput("filtered")
OneMuon = OP_NumComMuons("==",1)
ZMassCut = RECO_2ndMuonMass(25.0, 91.2, False, "all")
PFMTCut30 = RECO_PFMTCut(30.0)
DiMuon = OP_NumComMuons("==",2)
ZMass_2Muons = RECO_2ndMuonMass(25.0, 91.2, True, "OS")
minDRMuonJetCut = RECO_MuonJetDRCut(0.5)
minDRMuonJetCutDiMuon = RECO_MuonJetDRCut(0.5)
Mu45PtCut = OP_LowerMuPtCut(45.0)
Mu50PtCut_HigHT = OP_LowerMuPtCut(50.0)
Mu50PtCut_LowHT275 = OP_LowerMuPtCut(50.0*275./375.)
Mu50PtCut_LowHT325 = OP_LowerMuPtCut(50.0*325./375.)
Mu50PtCut_HigHT_MuTrigPlateau = OP_LowerMuPtCut(50.0)
Mu50PtCut_LowHT275_MuTrigPlateau = OP_LowerMuPtCut(45.0)
Mu50PtCut_LowHT325_MuTrigPlateau = OP_LowerMuPtCut(45.0)

secondJetET = OP_SecondJetEtCut(0)

def MakeDataTree(Threshold,Muon = None,Split = None):
  out = []
  if re.match("Muon_Add", str(Split)):
#  if Split == "Muon_Add" or Split == "Muon_Add_SingleMuTrig" or Split == "Muon_Add_SingleMuTrigPlateau":
      secondJetET = OP_SecondJetOrMuEtCut(Threshold) 
  else:
      secondJetET = OP_SecondJetEtCut(Threshold)
  print "in MakeDataTree"
  print Threshold
  HTBins = []
  if int(Threshold) is 100 : HTBins = [375.+100*i for i in range(6)]
  if int(Threshold) is 73 : HTBins = [275.,325.]
  if int(Threshold) is 86 : HTBins = [325.,375.]
  # from batchGolden import *
  cutTreeData = Tree("Data")
  cutTreeData.Attach(json)
  cutTreeData.TAttach(json,json_ouput)
  cutTreeData.TAttach(json_ouput,NoiseFilt)
  cutTreeData.TAttach(NoiseFilt,GoodVertexMonster)
  cutTreeData.TAttach(GoodVertexMonster,recHitCut)
#  if Split == "Muon_Add" or Split == "Muon_Add_SingleMuTrig" or Split == "Muon_Add_SingleMuTrigPlateau":
  if re.match("Muon_Add", str(Split)):
      print "Matched "+Split
      cutTreeData.TAttach(recHitCut,LeadingJetOrMuEta)
      cutTreeData.TAttach(LeadingJetOrMuEta,secondJetET)
      cutTreeData.TAttach(secondJetET,oddJet)
  else:
      cutTreeData.TAttach(recHitCut,LeadingJetEta)
      cutTreeData.TAttach(LeadingJetEta,secondJetET)
      cutTreeData.TAttach(secondJetET,oddJet)
      
  cutTreeData.TAttach(oddJet,badMuonInJet)
  cutTreeData.TAttach(badMuonInJet,oddElectron)
  cutTreeData.TAttach(oddElectron,oddPhoton)
  cutTreeData.TAttach(oddPhoton,numComElectrons)
  cutTreeData.TAttach(numComElectrons,numComPhotons)
  cutTreeData.TAttach(numComPhotons,VertexPtOverHT)
  if Muon == None:
      cutTreeData.TAttach(VertexPtOverHT,htCut275)
      cutTreeData.TAttach(htCut275,DeadEcalCutData)
      cutTreeData.TAttach(DeadEcalCutData,MHT_METCut)
      cutTreeData.TAttach(MHT_METCut,ZeroMuon)
      genericPSet_data.mode="None"
      out.append(AddBinedHist(cutTree = cutTreeData,
      OP = ("TauFakeB",genericPSet_data), cut = ZeroMuon,
      htBins = HTBins,TriggerDict = triggers,lab ="", split = None) )

  else:
      if Split == "Muon_All" and int(Threshold) is 100:
          cutTreeData.TAttach(VertexPtOverHT,htCut275)
          cutTreeData.TAttach(htCut275,DeadEcalCutData)
          cutTreeData.TAttach(DeadEcalCutData,MHT_METCut)
          cutTreeData.TAttach(MHT_METCut,Mu45PtCut)
          cutTreeData.TAttach(Mu45PtCut,minDRMuonJetCut)
      elif Split == "Muon_SingleMuTrig":
          cutTreeData.TAttach(VertexPtOverHT,htCut275)
          cutTreeData.TAttach(htCut275,DeadEcalCutData)
          cutTreeData.TAttach(DeadEcalCutData,MHT_METCut)
          cutTreeData.TAttach(MHT_METCut,Mu45PtCut)
          cutTreeData.TAttach(Mu45PtCut,minDRMuonJetCut)
      elif Split == "Muon_Add" or Split == "Muon_Add_SingleMuTrig":
          if int(Threshold) is 73:
              cutTreeData.TAttach(VertexPtOverHT,htTakeMuCut275)
              cutTreeData.TAttach(htTakeMuCut275,DeadEcalCutData)
              cutTreeData.TAttach(DeadEcalCutData,MHTTakeMu_METTakeMuCut)
              cutTreeData.TAttach(MHTTakeMu_METTakeMuCut,Mu50PtCut_LowHT275)
              cutTreeData.TAttach(Mu50PtCut_LowHT275,minDRMuonJetCut)
          elif int(Threshold) is 86:
              cutTreeData.TAttach(VertexPtOverHT,htTakeMuCut275)
              cutTreeData.TAttach(htTakeMuCut275,DeadEcalCutData)
              cutTreeData.TAttach(DeadEcalCutData,MHTTakeMu_METTakeMuCut)
              cutTreeData.TAttach(MHTTakeMu_METTakeMuCut,Mu50PtCut_LowHT325)
              cutTreeData.TAttach(Mu50PtCut_LowHT325,minDRMuonJetCut)
          elif int(Threshold) is 100:
              cutTreeData.TAttach(VertexPtOverHT,htTakeMuCut275)
              cutTreeData.TAttach(htTakeMuCut275,DeadEcalCutData)
              cutTreeData.TAttach(DeadEcalCutData,MHTTakeMu_METTakeMuCut)
              cutTreeData.TAttach(MHTTakeMu_METTakeMuCut,Mu50PtCut_HigHT)
              cutTreeData.TAttach(Mu50PtCut_HigHT,minDRMuonJetCut)
      elif Split == "Muon_Add_SingleMuTrigPlateau":
          if int(Threshold) is 73:
              cutTreeData.TAttach(VertexPtOverHT,htTakeMuCut275)
              cutTreeData.TAttach(htTakeMuCut275,DeadEcalCutData)
              cutTreeData.TAttach(DeadEcalCutData,MHTTakeMu_METTakeMuCut)
              cutTreeData.TAttach(MHTTakeMu_METTakeMuCut,Mu50PtCut_LowHT275_MuTrigPlateau)
              cutTreeData.TAttach(Mu50PtCut_LowHT275_MuTrigPlateau,minDRMuonJetCut)
          elif int(Threshold) is 86:
              cutTreeData.TAttach(VertexPtOverHT,htTakeMuCut275)
              cutTreeData.TAttach(htTakeMuCut275,DeadEcalCutData)
              cutTreeData.TAttach(DeadEcalCutData,MHTTakeMu_METTakeMuCut)
              cutTreeData.TAttach(MHTTakeMu_METTakeMuCut,Mu50PtCut_LowHT325_MuTrigPlateau)
              cutTreeData.TAttach(Mu50PtCut_LowHT325_MuTrigPlateau,minDRMuonJetCut)
          elif int(Threshold) is 100:
              cutTreeData.TAttach(VertexPtOverHT,htTakeMuCut275)
              cutTreeData.TAttach(htTakeMuCut275,DeadEcalCutData)
              cutTreeData.TAttach(DeadEcalCutData,MHTTakeMu_METTakeMuCut)
              cutTreeData.TAttach(MHTTakeMu_METTakeMuCut,Mu50PtCut_HigHT_MuTrigPlateau)
              cutTreeData.TAttach(Mu50PtCut_HigHT_MuTrigPlateau,minDRMuonJetCut)
      else:
          cutTreeData.TAttach(VertexPtOverHT,htCut275)
          cutTreeData.TAttach(htCut275,DeadEcalCutData)
          cutTreeData.TAttach(DeadEcalCutData,MHT_METCut)
          cutTreeData.TAttach(MHT_METCut,minDRMuonJetCut)
      cutTreeData.TAttach(minDRMuonJetCut,OneMuon)
      cutTreeData.TAttach(OneMuon,ZMassCut)
      cutTreeData.TAttach(ZMassCut,PFMTCut30)
      if Split is None:
          genericPSet_data.mode="None"
      elif re.match("Muon_Add", str(Split)):
          genericPSet_data.mode="Muon_Add"
      else:
          genericPSet_data.mode=Split

#      if Split == "Muon_Add_SingleMuTrig" or Split == "Muon_Add_SingleMuTrigPlateau" ort Split == "Muon_SingleMuTrig":
      if re.search("SingleMuTrig", str(Split)):
          out.append(AddBinedHist(cutTree = cutTreeData,
          OP = ("TauFakeB",genericPSet_data), cut = PFMTCut30,
          htBins = HTBins,TriggerDict = (single_mu_triggers),lab = "OneMuon_", split = genericPSet_data.mode ) )
      else:
          out.append(AddBinedHist(cutTree = cutTreeData,
          OP = ("TauFakeB",genericPSet_data), cut = PFMTCut30,
          htBins = HTBins,TriggerDict = (mu_triggers if ( ( Split == "Muon_All" and int(Threshold) is 100 ) ) else triggers),lab = "OneMuon_", split = genericPSet_data.mode ) )
      print "mode="+genericPSet_data.mode

#      cutTreeData.TAttach(minDRMuonJetCut,DiMuon)
#      cutTreeData.TAttach(DiMuon,ZMass_2Muons)

      # avobe here does one big inclusive bin!
      # Now lets start binning in HT bins
      # So we can HADD the files at the end and get a chorent set to save the book keeping nightmare:
      # we arrange the HT bins so they are not repoduced though out threshold runs.

#      out.append(AddBinedHist(cutTree = cutTreeData,
#      OP = ("TauFakeB",genericPSet_data), cut = ZMass_2Muons,
#      htBins = HTBins,TriggerDict = (mu_triggers if Split == "Muon_All" else triggers),lab = "DiMuon_") ) 
    
  return (cutTreeData,secondJetET,out)

#Second MC!

def MakeMCTree(Threshold, Muon = None,Split = None):
  print "in MakeMCTree"
  print Threshold
  
  out = []

  HTBins = []
  
  if int(Threshold) is 100 : HTBins = [375.+100*i for i in range(6)]
  if int(Threshold) is 73 : HTBins = [275.,325.]
  if int(Threshold) is 86 : HTBins = [325.,375.]
  if re.match("Muon_Add", str(Split)):
# if Split == "Muon_Add" or Split == "Muon_Add_SingleMuTrig" or Split == "Muon_Add_SingleMuTrigPlateau":
      secondJetET = OP_SecondJetOrMuEtCut(Threshold)
  else:
      secondJetET = OP_SecondJetEtCut(Threshold)

  cutTreeMC = Tree("MC")

  if re.match("Muon_Add", str(Split)):
#  if Split == "Muon_Add" or Split == "Muon_Add_SingleMuTrig" or Split == "Muon_Add_SingleMuTrigPlateau":
      cutTreeMC.Attach(htTakeMu250_Trigger)
      cutTreeMC.TAttach(htTakeMu250_TriggerNoiseFilt)
      cutTreeMC.TAttach(NoiseFilt,GoodVertexMonster) #Need to take back for normal MC
      cutTreeMC.TAttach(GoodVertexMonster,recHitCut) #Need to take back for normal MC
#      cutTreeMC.TAttach(NoiseFilt,recHitCut) #for MC Summer12 produced under 51X and 522
      cutTreeMC.TAttach(recHitCut,LeadingJetOrMuEta)
      cutTreeMC.TAttach(LeadingJetOrMuEta,secondJetET)
      cutTreeMC.TAttach(secondJetET,oddJet)
  else:
      cutTreeMC.Attach(ht250_Trigger)
      cutTreeMC.TAttach(ht250_Trigger,NoiseFilt)
      cutTreeMC.TAttach(NoiseFilt,GoodVertexMonster) #Need to take back for normal MC
      cutTreeMC.TAttach(GoodVertexMonster,recHitCut) #Need to take back for normal MC
#      cutTreeMC.TAttach(NoiseFilt,recHitCut) #for MC Summer12 produced under 51X and 522
      cutTreeMC.TAttach(recHitCut,LeadingJetEta)
      cutTreeMC.TAttach(LeadingJetEta,secondJetET)
      cutTreeMC.TAttach(secondJetET,oddJet)

  cutTreeMC.TAttach(oddJet,badMuonInJet)
  cutTreeMC.TAttach(badMuonInJet,oddElectron)
  cutTreeMC.TAttach(oddElectron,oddPhoton)
  cutTreeMC.TAttach(oddPhoton,numComElectrons)
  cutTreeMC.TAttach(numComElectrons,numComPhotons)
  cutTreeMC.TAttach(numComPhotons,VertexPtOverHT)
 
  #Here be plots after all the cuts!!
  if Muon == None:
      cutTreeMC.TAttach(VertexPtOverHT,htCut275)
      cutTreeMC.TAttach(htCut275,DeadEcalCutMC)
      cutTreeMC.TAttach(DeadEcalCutMC,MHT_METCut)
      cutTreeMC.TAttach(MHT_METCut,ZeroMuon)
      out.append(AddBinedHist(cutTree = cutTreeMC,
      OP = ("TauFakeB",genericPSet_mc), cut = ZeroMuon,
      htBins = HTBins,TriggerDict = None,lab ="", split = None) )

  else:
      if Split == "Muon_All" and int(Threshold) is 100:
          cutTreeMC.TAttach(VertexPtOverHT,htCut275)
          cutTreeMC.TAttach(htCut275,DeadEcalCutMC)
          cutTreeMC.TAttach(DeadEcalCutMC,MHT_METCut)
          cutTreeMC.TAttach(MHT_METCut,Mu45PtCut)
          cutTreeMC.TAttach(Mu45PtCut,minDRMuonJetCut)
      elif Split == "Muon_SingleMuTrig":
          cutTreeMC.TAttach(VertexPtOverHT,htCut275)
          cutTreeMC.TAttach(htCut275,DeadEcalCutMC)
          cutTreeMC.TAttach(DeadEcalCutMC,MHT_METCut)
          cutTreeMC.TAttach(MHT_METCut,Mu45PtCut)
          cutTreeMC.TAttach(Mu45PtCut,minDRMuonJetCut)
      elif Split == "Muon_Add" or Split == "Muon_Add_SingleMuTrig":
          if int(Threshold) is 73:
              cutTreeMC.TAttach(VertexPtOverHT,htTakeMuCut275)
              cutTreeMC.TAttach(htTakeMuCut275,DeadEcalCutMC)
              cutTreeMC.TAttach(DeadEcalCutMC,MHTTakeMu_METTakeMuCut)
              cutTreeMC.TAttach(MHTTakeMu_METTakeMuCut,Mu50PtCut_LowHT275)
              cutTreeMC.TAttach(Mu50PtCut_LowHT275,minDRMuonJetCut)
          elif int(Threshold) is 86:
              cutTreeMC.TAttach(VertexPtOverHT,htTakeMuCut275)
              cutTreeMC.TAttach(htTakeMuCut275,DeadEcalCutMC)
              cutTreeMC.TAttach(DeadEcalCutMC,MHTTakeMu_METTakeMuCut)
              cutTreeMC.TAttach(MHTTakeMu_METTakeMuCut,Mu50PtCut_LowHT325)
              cutTreeMC.TAttach(Mu50PtCut_LowHT325,minDRMuonJetCut)
          elif int(Threshold) is 100:
              cutTreeMC.TAttach(VertexPtOverHT,htTakeMuCut275)
              cutTreeMC.TAttach(htTakeMuCut275,DeadEcalCutMC)
              cutTreeMC.TAttach(DeadEcalCutMC,MHTTakeMu_METTakeMuCut)
              cutTreeMC.TAttach(MHTTakeMu_METTakeMuCut,Mu50PtCut_HigHT)
              cutTreeMC.TAttach(Mu50PtCut_HigHT,minDRMuonJetCut)
      elif Split == "Muon_Add_SingleMuTrigPlateau":
          if int(Threshold) is 73:
              cutTreeMC.TAttach(VertexPtOverHT,htTakeMuCut275)
              cutTreeMC.TAttach(htTakeMuCut275,DeadEcalCutMC)
              cutTreeMC.TAttach(DeadEcalCutMC,MHTTakeMu_METTakeMuCut)
              cutTreeMC.TAttach(MHTTakeMu_METTakeMuCut,Mu50PtCut_LowHT275_MuTrigPlateau)
              cutTreeMC.TAttach(Mu50PtCut_LowHT275_MuTrigPlateau,minDRMuonJetCut)
          elif int(Threshold) is 86:
              cutTreeMC.TAttach(VertexPtOverHT,htTakeMuCut275)
              cutTreeMC.TAttach(htTakeMuCut275,DeadEcalCutMC)
              cutTreeMC.TAttach(DeadEcalCutMC,MHTTakeMu_METTakeMuCut)
              cutTreeMC.TAttach(MHTTakeMu_METTakeMuCut,Mu50PtCut_LowHT325_MuTrigPlateau)
              cutTreeMC.TAttach(Mu50PtCut_LowHT325_MuTrigPlateau,minDRMuonJetCut)
          elif int(Threshold) is 100:
              cutTreeMC.TAttach(VertexPtOverHT,htTakeMuCut275)
              cutTreeMC.TAttach(htTakeMuCut275,DeadEcalCutMC)
              cutTreeMC.TAttach(DeadEcalCutMC,MHTTakeMu_METTakeMuCut)
              cutTreeMC.TAttach(MHTTakeMu_METTakeMuCut,Mu50PtCut_HigHT_MuTrigPlateau)
              cutTreeMC.TAttach(Mu50PtCut_HigHT_MuTrigPlateau,minDRMuonJetCut)
      else:
          cutTreeMC.TAttach(VertexPtOverHT,htCut275)
          cutTreeMC.TAttach(htCut275,DeadEcalCutMC)
          cutTreeMC.TAttach(DeadEcalCutMC,MHT_METCut)
          cutTreeMC.TAttach(MHT_METCut,minDRMuonJetCut)
      cutTreeMC.TAttach(minDRMuonJetCut,OneMuon)
      cutTreeMC.TAttach(OneMuon,ZMassCut)
      cutTreeMC.TAttach(ZMassCut,PFMTCut30)
      if Split is None:
          genericPSet_mc.mode="None"
      elif re.match("Muon_Add", str(Split)):
          genericPSet_mc.mode="Muon_Add"
      else:
          genericPSet_mc.mode=Split

      out.append(AddBinedHist(cutTree = cutTreeMC,
      OP = ("TauFakeB",genericPSet_mc), cut = PFMTCut30,
      htBins = HTBins,TriggerDict = None, lab = "OneMuon_", split = genericPSet_mc.mode) )
      print "mode="+genericPSet_mc.mode


#      cutTreeMC.TAttach(minDRMuonJetCut,DiMuon)
#      cutTreeMC.TAttach(DiMuon,ZMass_2Muons)
    
#      out.append(AddBinedHist(cutTree = cutTreeMC,
#      OP = ("TauFakeB",genericPSet_mc), cut = ZMass_2Muons,
#      htBins = HTBins,TriggerDict = None ,lab = "DiMuon_") )

  
  return (cutTreeMC,secondJetET,out)


# Define the custom muon ID

mu_id_higher = PSet(
    doJetLoop = False,
    MuID = "Tight",
    MinPt = 10.,
    MaxEta = 2.1,
    MaxIsolation = 0.1,
    DRMuJet = 0.3,
    MaxGlbTrkDxy = 0.02,
    MinGlbTrkNumOfValidHits = 11,
    SegMatch2GlbMu = 1,
    PixelHitsOnInrTrk = 1,
    MaxInrTrkDz = 1.
        )


mu_id_lower = PSet(
    doJetLoop = False,
    MuID = "Tight",
    MinPt = 10.,
    MaxEta = 2.5,
    MaxIsolation = 0.15,
    DRMuJet = 0.3,
    MaxGlbTrkDxy = 0.02,
    MinGlbTrkNumOfValidHits = 11,
    SegMatch2GlbMu = 1,
    PixelHitsOnInrTrk = 1,
    MaxInrTrkDz = 1.
        )



vertex_reweight_PUS4 = GoodVertexReweighting(
PSet(GoodVertexWeights = [1.0, 0.071182041228993354, 0.3788533298983548, 0.70212224756460717, 0.95912926863057879,
 1.1063323506805849, 1.1826257455177471, 1.2297382718782017, 1.2772830447358376, 1.4266446590805815, 1.5732065775636328, 
 1.8401056375971667, 2.1784909215394999, 2.506266882602076, 3.3335988825191176, 4.687787057503483, 6.8602191807881647, 
 11.198474011060968, 14.883466002768214, 20.878255333866864, 1.0, 1.0, 1.0, 1.0, 1.0]).ps())

vertex_reweight_PUS6 = GoodVertexReweighting(
PSet(GoodVertexWeights =[1.0, 0.6747792521746856, 1.0448420078821972, 1.3055015002285708, 1.3983895957384924, 1.4093911155782819, 1.3850308438481276, 1.3018072225453758, 1.1623455679439036, 1.0517773707737472, 0.89838694986924372, 0.76765214151467354, 0.63185640954246791, 0.49262105848611853, 0.42787145593782405, 0.3847054078776958, 0.35778382190253444, 0.34148368315539618, 0.28535617241618649, 0.24963682196802897, 0.15231738209843554, 0.10766396055685283, 0.066294358386045707, 0.039350814964675719, 0.071293966061105704] ).ps())


#Here are the Data samples!!!!

from data.Run2011.HT_Run2011AB import *
from data.Run2011.HT_Run2011A import *

from data.Run2011.HT_Run2011A_05Aug2011_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.HT_Run2011A_May10ReReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.HT_Run2011A_PromptReco_v6_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.HT_Run2011A_PromptReco_v4_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.HT_Run2011B_PromptReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *

from data.Run2011.MuHad_Run2011A_PromptReco_v4_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.MuHad_Run2011A_May10ReReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.MuHad_Run2011A_05Aug2011_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.MuHad_Run2011A_PromptReco_v6_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.MuHad_Run2011B_PromptReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *

from data.Run2011.SingleMu_Run2011A_05Aug2011_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.SingleMu_Run2011A_PromptReco_v6_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.SingleMu_Run2011A_PromptReco_v4_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.SingleMu_Run2011A_May10ReReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from data.Run2011.SingleMu_Run2011B_PromptReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *


DataHT_Sample_2011AB = [ HT_Run2011A_05Aug2011_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, HT_Run2011A_May10ReReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, HT_Run2011A_PromptReco_v6_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, HT_Run2011A_PromptReco_v4_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, HT_Run2011B_PromptReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 ]

DataHT_Sample_2011A = [ HT_Run2011A_05Aug2011_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, HT_Run2011A_May10ReReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, HT_Run2011A_PromptReco_v6_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, HT_Run2011A_PromptReco_v4_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1]

DataHT_Sample_2011B = [ HT_Run2011B_PromptReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 ]



DataMuHad_Sample_2011AB = [ MuHad_Run2011A_PromptReco_v4_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, MuHad_Run2011A_May10ReReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, MuHad_Run2011A_05Aug2011_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, MuHad_Run2011A_PromptReco_v6_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, MuHad_Run2011B_PromptReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 ]

DataMuHad_Sample_2011A = [ MuHad_Run2011A_PromptReco_v4_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, MuHad_Run2011A_May10ReReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, MuHad_Run2011A_05Aug2011_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, MuHad_Run2011A_PromptReco_v6_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 ]

DataMuHad_Sample_2011B = [ MuHad_Run2011B_PromptReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 ]


DataSingleMu_Sample_2011AB = [ SingleMu_Run2011A_05Aug2011_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, SingleMu_Run2011A_PromptReco_v6_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, SingleMu_Run2011A_PromptReco_v4_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, SingleMu_Run2011A_May10ReReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, SingleMu_Run2011B_PromptReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 ]

DataSingleMu_Sample_2011A = [ SingleMu_Run2011A_05Aug2011_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, SingleMu_Run2011A_PromptReco_v6_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, SingleMu_Run2011A_PromptReco_v4_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1, SingleMu_Run2011A_May10ReReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 ]

DataSingleMu_Sample_2011B = [ SingleMu_Run2011B_PromptReco_v1_V15_04_00_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 ]



# Here are the Summer 11 MC samples!!!

from montecarlo.Summer11.DYJetsToLL_TuneZ2_M_50_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from montecarlo.Summer11.ZJetsToNuNu_50_HT_100_7TeV_madgraph_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.ZJetsToNuNu_100_HT_200_7TeV_madgraph_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.ZJetsToNuNu_200_HT_inf_7TeV_madgraph_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.QCD_Summer11_madgraph_All import *
from montecarlo.Summer11.TTJets_TuneZ2_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.WJetsToLNu_TuneZ2_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.WJetsToLNu_250_HT_300_TuneZ2_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.WJetsToLNu_300_HT_inf_TuneZ2_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1_V15_03_19_jetCorrections_L1FastJet_L2Relative_L3Absolute_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from montecarlo.Summer11.T_TuneZ2_t_channel_7TeV_powheg_tauola_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.T_TuneZ2_tW_channel_DR_7TeV_powheg_tauola_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.Tbar_TuneZ2_t_channel_7TeV_powheg_tauola_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.Tbar_TuneZ2_tW_channel_DR_7TeV_powheg_tauola_Summer11_PU_S4_START42_V11_v1 import *

# PU S6
from montecarlo.Summer11FNAL.WW_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1 import *
from montecarlo.Summer11.WZ_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1 import *
from montecarlo.Summer11.ZZ_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1 import *

# Signal samples

from montecarlo.Summer11.CMSSM_Tanb10_1800_280 import *
from montecarlo.Summer11.CMSSM_Tanb10_1800_280_NoWeight import *
from montecarlo.Summer11.CMSSM_Tanb10_320_520 import *
from montecarlo.Summer11.CMSSM_1800_280_Hadronic_Selection import *
from SUSYSignalScan.SMS_T2tt_Mstop_225to1200_mLSP_50to1025_7TeV_Pythia6Z_Summer11_PU_START42_V11_FastSim_v1_V15_03_18_scan_T2tt import *
from SUSYSignalScan.SMS_T2_Mgluino_100to1200_mLSP_50to1150_7TeV_Pythia6Z_Summer11_PU_START42_V11_FastSim_v1_V15_03_14_02 import *

Tanb10_1800_280_Sample = [ CMSSM_Tanb10_1800_280 ]
Tanb10_320_520_Sample = [ CMSSM_Tanb10_320_520 ]
Tanb10_1800_280_Sample_NoWeight = [ CMSSM_Tanb10_1800_280_NoWeight ]
T2_Sample = [ SMS_T2_Mgluino_100to1200_mLSP_50to1150_7TeV_Pythia6Z_Summer11_PU_START42_V11_FastSim_v1_V15_03_14_02 ]
T2tt_Sample = [ SMS_T2tt_Mstop_225to1200_mLSP_50to1025_7TeV_Pythia6Z_Summer11_PU_START42_V11_FastSim_v1_V15_03_18_scan_T2tt ]

# QCD_Summer11_madgraph_All +
from montecarlo.Summer11.QCD_BLepEnriched_TuneZ2_7TeV_pythia6_evtgen_Summer11_PU_S3_START42_V11_v1 import *

PU_S3_Sample = [ QCD_BLepEnriched_TuneZ2_7TeV_pythia6_evtgen_Summer11_PU_S3_START42_V11_v1]


#DiBoson_Sample = [ WW_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1, 
#                WZ_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1,
#                 ZZ_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1]

DiBoson_Sample = [ WW_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1 ]


WJet_Sample_HighHTBins =[ WJetsToLNu_250_HT_300_TuneZ2_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1, WJetsToLNu_300_HT_inf_TuneZ2_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1_V15_03_19_jetCorrections_L1FastJet_L2Relative_L3Absolute_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 ]


WJet_Sample_LowHTBins =[ WJetsToLNu_TuneZ2_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1 ]


TTbar_Sample = [ TTJets_TuneZ2_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1 ]


SingleT_Sample = [ T_TuneZ2_t_channel_7TeV_powheg_tauola_Summer11_PU_S4_START42_V11_v1, T_TuneZ2_tW_channel_DR_7TeV_powheg_tauola_Summer11_PU_S4_START42_V11_v1,Tbar_TuneZ2_t_channel_7TeV_powheg_tauola_Summer11_PU_S4_START42_V11_v1,Tbar_TuneZ2_tW_channel_DR_7TeV_powheg_tauola_Summer11_PU_S4_START42_V11_v1]

Zinv_Sample = [ ZJetsToNuNu_50_HT_100_7TeV_madgraph_Summer11_PU_S4_START42_V11_v1, ZJetsToNuNu_100_HT_200_7TeV_madgraph_Summer11_PU_S4_START42_V11_v1, ZJetsToNuNu_200_HT_inf_7TeV_madgraph_Summer11_PU_S4_START42_V11_v1 ]


DiMuon_Sample = [ DYJetsToLL_TuneZ2_M_50_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 ]




Summer11_MC_HighHTBins = WJet_Sample_HighHTBins + TTbar_Sample + SingleT_Sample + Zinv_Sample + DiMuon_Sample

Summer11_MC_LowHTBins = WJet_Sample_LowHTBins + TTbar_Sample + SingleT_Sample + Zinv_Sample + DiMuon_Sample


Summer11_MC_NoZinv_HighHTBins = WJet_Sample_HighHTBins + TTbar_Sample + SingleT_Sample + DiMuon_Sample

Summer11_MC_NoZinv_LowHTBins = WJet_Sample_LowHTBins + TTbar_Sample + SingleT_Sample + DiMuon_Sample



""" READ ME """
""" Split/split == Muon_All: using mu_had trigger but only for high HT bins (> 375 GeV), low HT bins trigger are ht_alphaT, so the Split/split == else actually (normally None)"""
""" Split/split == Muon_Add: treat muon as a jet, but using ht_alphaT trigger for all the HT bins"""
""" Split/split == Muon_Add_SingleMuTrig: treat muon as a jet, but using single muon trigger for all the HT bins to avoid the shift in HT for the ht_alphaT trigger"""
""" Split/split == Muon_Add_SingleMutrigPlateau: treat muon as a jet and using single muon trigger. However, to avoid the inefficiency for the tow low HT bins, the common muon (which is treated a jet) pT cut is 45 GeV instead of 50.0*275./375. and 50.0*325./375. GeV. at 45 GeV, as studied the trigger efficienty is at 95%"""

