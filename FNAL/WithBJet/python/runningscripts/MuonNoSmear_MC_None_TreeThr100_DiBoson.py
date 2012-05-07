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

#--------------------------------------------control parameters--------
TreeThr=100.
sample=DiBoson_Sample
SplitForm=None
DataSet="MC"

PUS="PUS4"
ExtraInstruction="LowHTBins"
RunScriptName="NoSmear"

if int(TreeThr) is 100:
  ExtraInstruction="HigHTBins"
elif int(TreeThr) is 73:
  ExtraInstruction="LowHTBins"
elif int(TreeThr) is 86:
  ExtraInstruction="LowHTBins"


if sample == WJet_Sample_HighHTBins or sample == WJet_Sample_LowHTBins:
  SampleIndicated="WJ"
  if sample == WJet_Sample_HighHTBins:
    ExtraInstruction="HigHTBins"
  elif sample == WJet_Sample_LowHTBins:
    ExtraInstruction="LowHTBins"
elif sample == TTbar_Sample:
  SampleIndicated="TT"
elif sample == SingleT_Sample:
  SampleIndicated="SingleT"
elif sample == Zinv_Sample:
  SampleIndicated="Zinv"
elif sample == DiMuon_Sample:
  SampleIndicated="DiMuon"
elif sample == Summer11_MC_HighHTBins:
  ExtraInstruction="HigHTBins"
  SampleIndicated="ALL"
elif sample == Summer11_MC_LowHTBins:
  ExtraInstruction="LowHTBins"
  SampleIndicated="ALL"
elif sample == DiBoson_Sample:
  PUS = "PUS6"
  SampleIndicated="DiBoson"
elif sample == Tanb10_1800_280_Sample:
  SampleIndicated="TanB10_1800_280"
elif sample == Tanb10_320_520_Sample:
  SampleIndicated="TanB10_320_520"
else:
  SampleIndicated=""


if DataSet == "Data":
  RunScriptName="Data"

#----- hadronic or muon
MuonForm = True
if SplitForm == None:
  ExtraInstruction=ExtraInstruction+"HadSele"
  MuonForm = None
else:
  ExtraInstruction=ExtraInstruction+"Muon"
#----- binning

JetPtThr = 50.0

if int(TreeThr) is 100:
  JetPtThr = 50.0
elif int(TreeThr) is 73:
  JetPtThr = 50.*(275./375.)
  ExtraInstruction=ExtraInstruction+"275"
elif int(TreeThr) is 86:
  JetPtThr = 50.*(325./375.)
  ExtraInstruction=ExtraInstruction+"325"

#--------------------------------------------
default_common.Jets.PtCut = JetPtThr
print "-----hihihihi"
print JetPtThr
print TreeThr
print SplitForm

cutTreeMC,junkVar,l = MakeMCTree(TreeThr, Muon = MuonForm, Split = SplitForm)

vbtfMuonId_cff = Muon_IDFilter( vbtfmuonidps.ps()  )
vbtfElectronIdFilter = Electron_IDFilter( vbtfelectronidWP95ps.ps() )
ra3PhotonIdFilter    = Photon_IDFilter( ra3photonidps.ps() )
CustomMuID = CustomVBTFMuID(mu_id_higher.ps())
if int(TreeThr) is 100:
  CustomMuID = CustomVBTFMuID(mu_id_higher.ps())
else:
  CustomMuID = CustomVBTFMuID(mu_id_lower.ps())
  
def addCutFlowMC(b) :
  print PUS
  if PUS == "PUS4" and DataSet == "MC":
    b.AddWeightFilter("Weight", vertex_reweight_PUS4)
  elif PUS == "PUS6" and DataSet == "MC":
    b.AddWeightFilter("Weight", vertex_reweight_PUS6)
  elif PUS != "PUS4" or PUS != "PUS6" or  DataSet == "Data":
    print "Vertex reweighting is applied"

  if MuonForm == None:
    b.AddMuonFilter("PreCC",vbtfMuonId_cff)
  else:
    b.AddMuonFilter("PreCC",CustomMuID)

  b.AddPhotonFilter("PreCC",ra3PhotonIdFilter)
  b.AddElectronFilter("PreCC",vbtfElectronIdFilter)
  b+=cutTreeMC

#AK5 Calo
conf_ak5_caloMC = deepcopy(defaultConfig)
conf_ak5_caloMC.Ntuple = deepcopy(ak5_calo)
conf_ak5_caloMC.XCleaning = deepcopy(default_cc)
conf_ak5_caloMC.Common = deepcopy(default_common)
conf_ak5_caloMC.Common.print_out()
anal_ak5_caloMC=Analysis("AK5Calo")
addCutFlowMC(anal_ak5_caloMC)

#outDir = "../results_"+strftime("%d_%b")+"//MuonNoSmearTT/"
outDir = "../results_"+strftime("%d_%b")+("//%s%s_%s%s/" % (RunScriptName, SampleIndicated, PUS, ExtraInstruction) )
ensure_dir(outDir)

anal_ak5_caloMC.Run(outDir,conf_ak5_caloMC,sample)

