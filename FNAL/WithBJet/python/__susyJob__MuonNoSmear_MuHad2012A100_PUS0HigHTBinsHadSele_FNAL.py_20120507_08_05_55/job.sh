#!/bin/sh
source /uscmst1/prod/sw/cms/cmsset_default.sh
source /uscms_data/d3/zmeng/SUSYv2/setup.sh
cd /uscms_data/d3/zmeng/SUSYv2/../CMSSW_5_0_0/src
cmsenv
cd /uscms_data/d3/zmeng/SUSYv2/WithBJet/python
./MuonNoSmear_MuHad2012A100_PUS0HigHTBinsHadSele_FNAL.py -j __susyJob__MuonNoSmear_MuHad2012A100_PUS0HigHTBinsHadSele_FNAL.py_20120507_08_05_55/job.json -J $1 -S __susyJob__MuonNoSmear_MuHad2012A100_PUS0HigHTBinsHadSele_FNAL.py_20120507_08_05_55/status/$1
