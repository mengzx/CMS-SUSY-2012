1. in menus.C
change inidir_ and subdir_

inidir_ is directory store everything in your analysis
subdir_ is the directory contains the root files.

The struction of the root files storage is:
hadronic: inidir_/rootfiles/hadronicSele/subdir_/*.root
onemuon: inidir_/rootfiles/oneMuonSele/muonpT45GeV/subdir_/*.root


2. in main.C
1) qcdk->getResults(""); the bulk is defined floated, saying the bulk is defined according to the control region. For example, if region C1 is defined as 0.54 < AT < 0.55, the bulk region is AT < 0.54; if region C2 is defined as 0.53 < AT < 0.54, the bulk region is defined as AT < 0.53 ...

1) qcdk->getResults("_LowAT0.5"); the bulk region is defined as AT < 0.5


To run: 
make clean; make; ./main.exe QCDk
