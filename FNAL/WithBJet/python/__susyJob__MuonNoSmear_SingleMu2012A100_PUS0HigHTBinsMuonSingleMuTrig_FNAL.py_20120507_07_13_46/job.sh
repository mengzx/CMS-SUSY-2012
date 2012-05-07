#!/bin/sh
source /uscmst1/prod/sw/cms/cmsset_default.sh
source /uscms_data/d3/zmeng/SUSYv2/setup.sh
cd /uscms_data/d3/zmeng/SUSYv2/../CMSSW_5_0_0/src
cmsenv
cd /uscms_data/d3/zmeng/SUSYv2/WithBJet/python
./MuonNoSmear_SingleMu2012A100_PUS0HigHTBinsMuonSingleMuTrig_FNAL.py -j __susyJob__MuonNoSmear_SingleMu2012A100_PUS0HigHTBinsMuonSingleMuTrig_FNAL.py_20120507_07_13_46/job.json -J $1 -S __susyJob__MuonNoSmear_SingleMu2012A100_PUS0HigHTBinsMuonSingleMuTrig_FNAL.py_20120507_07_13_46/status/$1
