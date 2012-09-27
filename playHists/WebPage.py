#!/usr/bin/env python
from ROOT import *
import ROOT as r
import logging,itertools
import os,fnmatch,sys
import glob, errno
from time import strftime
from optparse import OptionParser
import array
import math as m


class Make_Page(object):
  print "\n       ================================" 
  print "       ======== Making Webpage ========"
  print "       ********************************\n\n"

  def __init__(self, title, MuonNum, jet_slices={}, jet_names={}, btag_slices={}, btag_names={}, HTBins={}, plotsname={}, plotsname_name={}):
    self.HTBins={'> 275 GeV (All HT Bins) ||||':"all", '275 -- 375 GeV (Low HT Bins) ||||':"lowHTBins", '> 375 GeV (High HT Bins) ||||':"highHTBins"}
    self.MuonNum={'HadSele':"HadSele", 'OneMuon':"OneMuon", 'DiMuon':"DiMuon"}
    self.title={'HadSele':"HadSele", 'OneMuon':"Muon", 'DiMuon':"Muon"}
    self.jet_slices = {'TwoJet':"TwoJet", 'ThreeJet':"ThreeJet", 'FourJet':"FourJet", 'MoreThreeJet':"MoreThreeJet", 'MoreFourJet':"MoreFourJet"}
    self.jet_names = {'TwoJet':"2-jet", 'ThreeJet':"3-jet", 'FourJet':"4-jet", 'MoreThreeJet':"> 3 -jet", 'MoreFourJet':"> 4-jet"}
    self.btag_slices = {'Inclusive':"-1To-2b", 'ZeroBtag':"0To0b", 'OneBtag':"1To1b", 'TwoBtag':"2To2b", 'MoreThanTwoBtag':"3To14b", 'MoreAndEqualOneBtag':"1To14b", 'ThreeBtag':"3To3b", 'FourBtag':"4To4b", 'MoreAndEqualFourBtag':"4To15b" }
    self.btag_names = {'Inclusive':"Inclusive", 'ZeroBtag':"0-btag", 'OneBtag':"1-btag", 'TwoBtag':"2-btag", 'MoreThanTwoBtag':"> 2-btag", 'MoreAndEqualOneBtag':">= 1 btag", 'ThreeBtag':"3-btag", 'FourBtag':"4-btag", 'MoreAndEqualFourBtag':"> 3-tag" }
    self.plotsname={'AlphaT':"AlphaT", 'HT':"HT", 'nVertex':"nVertex", 'MHT':"MHT", 'MHToverMET':"MHToverMET", 'nbjet':"nbjet", 'njet':"njet", 'muPt':"muPt", 'Zmass':"Zmass", 'MET':"MET", 'muonIso':"muonIso", 'PFMTele':"PFMTele", 'PFMTmu':"PFMTmu", 'PFMTvele':"PFMTvele", 'PFMTvmu':"PFMTvmu", 'muPt2':"muPt2", 'jetPt':"jetPt", 'jetPt2':"jetPt", 'jetEta':"jetEta", 'jetEta2':"jetEta2", 'elePt':"elePt", 'elePt2':"elePt2", 'PFMTT':"PFMTT", 'ntotalbjet':"ntotalbjet", 'nbaby30to50bjet':"nbaby30to50bjet", 'ncommjet':"ncommjet", 'nbaby30to50jet':"nbaby30to50jet" }
    self.plotsname_name={'AlphaT':"AlphaT", 'HT':"HT", 'nVertex':"nVertex", 'MHT':"MHT", 'MHToverMET':"MHToverMET", 'nbjet':"number of B-jet", 'njet':"number of common jet + baby jet", 'muPt':"muon Pt", 'Zmass':"Zmass", 'MET':"MET", 'muonIso':"muonIso", 'PFMTele':"PFMT from leading electron", 'PFMTmu':"PFMT from leading muon", 'PFMTvele':"PFMT vector sum pt of electron", 'PFMTvmu':"PFMT from vector sum pt of muon", 'muPt2':"second muon Pt2", 'jetPt':"leading jet Pt", 'jetPt2':"second leading jet Pt", 'jetEta':"leading jet Eta", 'jetEta2':"second leading jetEta", 'elePt':"leading electron Pt", 'elePt2':"second leading electron Pt", 'PFMTT':"PFMT", 'ntotalbjet':"number of common + baby B-jet", 'nbaby30to50bjet':"number of baby B-jet", 'ncommjet':"number of common jet", 'nbaby30to50jet':"number of baby jet" }

#    self.plotsname={'AlphaT':"AlphaT", 'HT':"HT", 'nVertex':"nVertex", 'MHT':"MHT", 'MHToverMET':"MHToverMET", 'nbjet':"nbjet", 'njet':"njet", 'muPt':"muPt", 'Zmass':"Zmass", 'MET':"MET", 'muonIso':"muonIso", 'muPt2':"muPt2", 'PFMTT':"PFMTT" }
#    self.Alpha_Webpage(self.btag_slices, self.plotsname,link="",outertitle=sys.argv[1],slice="",stacked = "", uselog="True")
#    self.Alpha_Webpage(self.btag_slices, self.plotsname,link="",outertitle=sys.argv[1]+"_linearScale",slice="",stacked = "", uselog="")
    self.Alpha_Webpage(self.jet_slices, self.btag_slices, self.plotsname,link="",outertitle=sys.argv[1],slice="",stacked = "Stack_", uselog="True")
    self.Alpha_Webpage(self.jet_slices, self.btag_slices, self.plotsname,link="",outertitle=sys.argv[1]+"_linearScale",slice="",stacked = "Stack_", uselog="")

  def Alpha_Webpage(self,outerjet,outer,inner,link="",outertitle="",slice="",simplified="",stacked="", uselog="True"):
    htF2 = open('./'+stacked+outertitle+'.html','w')
    htF2.write('<a href=full-colour-png_UoB.png><img width=\"10%\" src=\"full-colour-png_UoB.png\"></a> \n') 
    htF2.write('<a href=CMS_Color-Label.jpg><img width=\"10%\" src=\"CMS_Color-Label.jpg\" align = right></a> \n') 
    htF2.write('<br> \n')
    htF2.write('<br> \n')
    htF2.write('<br> \n')
    htF2.write('Author: Zhaoxia Meng <br> \n')
    htF2.write('<script language="Javascript"> \n document.write("Last Modified: " + document.lastModified + ""); \n </script> <br> \n ')
    htF2.write('<br> \n')
    htF2.write('<br> \n')
    htF2.write('Selection : ')
    htF2.write('<br> \n')
    for ititle2 in self.title:
      if not uselog:
        htF2.write('<a href=\"'+stacked+self.MuonNum[ititle2]+'_linearScale.html\">'+(stacked+self.MuonNum[ititle2])+'</a>  | ')
      else:
        htF2.write('<a href=\"'+stacked+self.MuonNum[ititle2]+'.html\">'+(stacked+self.MuonNum[ititle2])+'</a>  | ')
    htF2.write('<br> \n')
    htF2.write('<br> \n')
      
    for ititle in self.title:
      if not uselog:
        htF1 = open('./'+stacked+self.MuonNum[ititle]+'_linearScale.html','w')
      else:
        htF1 = open('./'+stacked+self.MuonNum[ititle]+'.html','w')
      htF1.write('<a href=full-colour-png_UoB.png><img width=\"10%\" src=\"full-colour-png_UoB.png\"></a> \n') 
      htF1.write('<a href=CMS_Color-Label.jpg><img width=\"10%\" src=\"CMS_Color-Label.jpg\" align = right></a> \n') 
      htF1.write('<br> \n')
      htF1.write('<br> \n')
      htF1.write('<br> \n')
      htF1.write('Author: Zhaoxia Meng <br> \n')
      htF1.write('<script language="Javascript"> \n document.write("Last Modified: " + document.lastModified + ""); \n </script> <br> \n ')
      htF1.write('<br> \n')
      htF1.write('<br> \n')
      if not uselog:
        htF1.write('<a href=\"'+'./'+stacked+outertitle+'_linearScale.html\"> Go back to parent link</a>  |  ')
      else:
        htF1.write('<a href=\"'+'./'+stacked+outertitle+'.html\"> Go back to parent link</a>  |  ')
      htF1.write('<br> \n')
      htF1.write('<br> \n')
      htF1.write('Go to selection:')
      for ititle1 in self.title:
        if not uselog:
          htF1.write('<a href=\"'+'./'+stacked+self.MuonNum[ititle1]+'_linearScale.html\"> '+stacked+self.MuonNum[ititle1]+'</a> | ')
        else:
          htF1.write('<a href=\"'+'./'+stacked+self.MuonNum[ititle1]+'.html\"> '+stacked+self.MuonNum[ititle1]+'</a> | ')
      htF1.write('<br> \n')
      htF1.write('<br> \n')
      htF1.write('You are currently at : ')
      if not uselog:
        htF1.write('<a href=\"'+'./'+stacked+self.MuonNum[ititle]+'_linearScale.html\"> '+stacked+self.MuonNum[ititle]+'</a> ')
      else:
        htF1.write('<a href=\"'+'./'+stacked+self.MuonNum[ititle]+'.html\"> '+stacked+self.MuonNum[ititle]+'</a> ')
      htF1.write('<br> \n')
      htF1.write('<br> \n')
      htF1.write('Hist Name: ')
      for kj in outerjet:
        if not uselog:
          htF1.write('<a href=\"'+stacked+kj+'_'+self.MuonNum[ititle]+'_linearScale.html\">'+(self.jet_names[kj])+'</a>  |  ')
        else:
          htF1.write('<a href=\"'+stacked+kj+'_'+self.MuonNum[ititle]+'.html\">'+(self.jet_names[kj])+'</a>  |  ')
      htF1.write('<br> \n')

      for ij in outerjet:
        if not uselog:
          htF3=open('./'+stacked+ij+'_'+self.MuonNum[ititle]+'_linearScale.html','w')
          htF3.write('<a href=\"'+'./'+stacked+self.MuonNum[ititle]+'_linearScale.html\"> Go back to parent link</a>  ')
          htF3.write('<br> \n')          
          htF3.write('<br> \n')          
          htF3.write('<br> \n')
          htF3.write('You are currently at: <br> \n')
          htF3.write('<a href=\"'+'./'+stacked+ij+'_'+self.MuonNum[ititle]+'_linearScale.html','w')
          htF3.write('<br> \n')
          htF3.write('<br> \n')
          htF3.write('Go to jet multiplicity: <br> \n')
          for ll in outerjet:
            htF3.write('<a href=\"'+'./'+stacked+ll+'_'+self.MuonNum[ititle]+'_linearScale.html','w')
          for i in outer:
            htF3.write('<a href=\"'+stacked+ij+'_'+i+'_'+self.MuonNum[ititle]+'_linearScale.html\">'+(self.btag_names[i])+'</a>  |  ')
        else:
          htF3=open('./'+stacked+ij+'_'+self.MuonNum[ititle]+'.html','w')
          htF3.write('<a href=\"'+'./'+stacked+self.MuonNum[ititle]+'.html\"> Go back to parent link</a>  ')
          htF3.write('<br> \n')          
          htF3.write('<br> \n')          
          htF3.write('<br> \n')          
          htF3.write('You are currently at: <br> \n')
          htF3.write('<a href=\"'+'./'+stacked+ij+'_'+self.MuonNum[ititle]+'.html','w')
          htF3.write('<br> \n')
          htF3.write('<br> \n')
          htF3.write('Go to jet multiplicity: <br> \n')
          for ll in outerjet:
            htF3.write('<a href=\"'+'./'+stacked+ll+'_'+self.MuonNum[ititle]+'.html','w')
          for i in outer:
            htF3.write('<a href=\"'+stacked+ij+'_'+i+'_'+self.MuonNum[ititle]+'.html\">'+(self.btag_names[i])+'</a>  |  ')

        for i in outer:
          if not uselog:
            htF = open('./'+stacked+ij+'_'+i+'_'+self.MuonNum[ititle]+'_linearScale.html','w')
          else:
            htF = open('./'+stacked+ij+'_'+i+'_'+self.MuonNum[ititle]+'.html','w')
          htF.write('<a href=full-colour-png_UoB.png><img width=\"10%\" src=\"full-colour-png_UoB.png\"></a> \n')
          htF.write('<a href=CMS_Color-Label.jpg><img width=\"10%\" src=\"CMS_Color-Label.jpg\" align = right></a> \n')
          htF.write('<br> \n')
          htF.write('<br> \n')
          htF.write('<br> \n')
          htF.write('Author: Zhaoxia Meng <br> \n')
          htF.write('<script language="Javascript"> \n document.write("Last Modified: " + document.lastModified + ""); \n </script> <br> \n ')
          htF.write('<center>\n <p> \n <font size="5"> '+self.MuonNum[ititle]+' Plots </font>\n </p>\n')
          htF.write('<font size="3">Results for '+i+' </font><br> \n')
          htF.write('<br> \n')
          htF.write('<br> \n')
          if not uselog:
            htF.write('<a href=\"'+'./'+stacked+self.MuonNum[ititle]+'_linearScale.html\"> Go back to parent link</a>  ')
            htF.write('<br> \n')
            htF.write('<br> \n')
            htF.write('Go to selection: ')
            for ititle3 in self.title:
              htF.write('<a href=\"'+'./'+stacked+self.MuonNum[ititle3]+'_linearScale.html\">'+stacked+self.MuonNum[ititle3]+'</a>  ')
          else:
            htF.write('<a href=\"'+'./'+stacked+self.MuonNum[ititle]+'.html\"> Go back to parent link</a>  ')
            htF.write('<br> \n')
            htF.write('<br> \n')
            htF.write('Go to selection: ')
            for ititle3 in self.title:
              htF.write('<a href=\"'+'./'+stacked+self.MuonNum[ititle3]+'.html\">'+stacked+self.MuonNum[ititle3]+'</a>  ')
          htF.write('<br> \n')
          htF.write('<br> \n')
          htF.write('Go to b-multiplicity:')
          for k in outer:
            if not uselog:
              htF.write('<a href=\"'+'./'+stacked+k+'_'+self.MuonNum[ititle]+'_linearScale.html\"> '+self.btag_names[k]+'</a>  |  ')
            else:
              htF.write('<a href=\"'+'./'+stacked+k+'_'+self.MuonNum[ititle]+'.html\"> '+self.btag_names[k]+'</a>  |  ')
          htF.write('<br> \n')
          htF.write('<br> \n')
          htF.write('You are currently at : ')
          if not uselog:
            htF.write('<a href=\"'+'./'+stacked+i+'_'+self.MuonNum[ititle]+'_linearScale.html\"> '+self.btag_names[i]+'</a>  ')
          else:
            htF.write('<a href=\"'+'./'+stacked+i+'_'+self.MuonNum[ititle]+'.html\"> '+self.btag_names[i]+'</a>  ')
          htF.write('<br> \n')
          htF.write('<br> \n')
          for j in inner:
            htF.write('<center>\n <p> \n <font size="5"> '+self.plotsname_name[j]+' </font>\n </p>\n')
            for root,dirs,files in os.walk('plotsAndtables/'):
              sorter = []
              test_sorter = []
              if not slice:
                if not uselog:
                  if self.title[ititle] == "HadSele":
                    tmp=''
                    for iht in self.HTBins:
                      tmp=tmp+iht+' | '
                    htF.write('<center>\n <p> \n <font size="5"> '+'HTBins:   '+tmp+' </font>\n </p>\n')
                    for iht in self.HTBins:
                      for filenames in fnmatch.filter(files,(stacked+inner[j]+"_"+self.title[ititle]+"_"+self.HTBins[iht]+"_"+outerjet[ij]+"_"+outer[i]+'.png') ):
                        sorter.append("plotsAndtables/"+filenames)
                    for plot in sorter: htF.write('<a href='+plot+'><img width=\"30%\" src=\"'+plot+'\"></a> \n') 
                  else:
                    tmp=''
                    for iht in self.HTBins:
                      tmp=tmp+iht+' | '
                    htF.write('<center>\n <p> \n <font size="5"> '+'HTBins:   '+tmp+' </font>\n </p>\n')
                    for iht in self.HTBins:
                      for filenames in fnmatch.filter(files,(stacked+inner[j]+"_"+self.title[ititle]+"_"+self.HTBins[iht]+"_"+self.MuonNum[ititle]+"_"+outerjet[ij]+"_"+outer[i]+'.png') ):
                        sorter.append("plotsAndtables/"+filenames)
                    for plot in sorter: htF.write('<a href='+plot+'><img width=\"30%\" src=\"'+plot+'\"></a> \n') 
                else:
                  if self.title[ititle] == "HadSele":
                    tmp=''
                    for iht in self.HTBins:
                      tmp=tmp+iht+'| |'
                    htF.write('<center>\n <p> \n <font size="5"> '+'HTBins:   '+tmp+' </font>\n </p>\n')
                    for iht in self.HTBins:
                      for filenames in fnmatch.filter(files,(stacked+inner[j]+"_"+self.title[ititle]+"_"+self.HTBins[iht]+"_"+outerjet[ij]+"_"+outer[i]+'_log.png') ):
                        sorter.append("plotsAndtables/"+filenames)
                    for plot in sorter: htF.write('<a href='+plot+'><img width=\"30%\" src=\"'+plot+'\"></a> \n') 
                  else:
                    tmp=''
                    for iht in self.HTBins:
                      tmp=tmp+iht+'| |'
                    htF.write('<center>\n <p> \n <font size="5"> '+'HTBins:   '+tmp+' </font>\n </p>\n')
                    for iht in self.HTBins:
                      for filenames in fnmatch.filter(files,(stacked+inner[j]+"_"+self.title[ititle]+"_"+self.HTBins[iht]+"_"+self.MuonNum[ititle]+outerjet[ij]+"_"+"_"+outer[i]+'_log.png') ):
                        sorter.append("plotsAndtables/"+filenames)
                    for plot in sorter: htF.write('<a href='+plot+'><img width=\"30%\" src=\"'+plot+'\"></a> \n') 
              else:
                print "add later"


          def print_(self):
              print self.title
              for (k,v) in  self.btag_slices.iteritems():
                  print "%s = %s" % (k,v)

        def print_(self):
            print self.title
            for (k,v) in  self.jet_slices.iteritems():
                print "%s = %s" % (k,v)



a=Make_Page(title={}, MuonNum={}, jet_slices={}, btag_slices={}, btag_names={}, HTBins={}, plotsname={}, plotsname_name={} )
#a.print_()




