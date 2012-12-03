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

  def __init__(self, title, MuonNum, jet_slices={}, jet_names={}, btag_slices={}, btag_names={}, HTBins={}, HTBin_names={}, plotsname={}, plotsname_name={}):
#    self.HTBins={'> 275 GeV (All HT Bins) ||||':"all", '275 -- 375 GeV (Low HT Bins) ||||':"lowHTBins", '> 375 GeV (High HT Bins) ||||':"highHTBins"}
    self.HTBins={'275':"275", '325':"325", 'all':"all", 'highHTBins':"highHTBins"}
    self.HTBin_names={'275':"275-325", '325':"325-375", 'all':"Inclusive", 'highHTBins':"> 375"}
    self.MuonNum={'HadSele':"HadSele"}
    self.title={'HadSele':"HadSele"}
    self.jet_slices = {'Inclusive':"", 'TwoThreeJet':"_TwoThreeJet", 'MoreThreeJet':"_MoreThreeJet"}
    self.jet_names = {'Inclusive':"Inclusive", 'TwoThreeJet_':"2-3 jets", 'MoreThreeJet':">= 4 jets"}
    self.btag_slices = {'Inclusive':"-1To-2b", 'ZeroBtag':"0To0b", 'OneBtag':"1To1b", 'TwoBtag':"2To2b", 'MoreAndEqualOneBtag':"1To15b", 'ThreeBtag':"3To3b", 'FourBtag':"4To4b" }
    self.btag_names = {'Inclusive':"Inclusive", 'ZeroBtag':"0-btag", 'OneBtag':"1-btag", 'TwoBtag':"2-btag", 'MoreAndEqualOneBtag':">= 1 btag", 'ThreeBtag':"3-btag", 'FourBtag':"4-btag" }
    self.plotsname={'AlphaT':"AlphaT", 'HT':"HT", 'nVertex':"nVertex", 'MHT':"MHT", 'MHToverMET':"MHToverMET", 'nbjet':"nbjet", 'muPt':"muPt", 'Zmass':"Zmass", 'MET':"MET", 'muonIso':"muonIso", 'muPt2':"muPt2", 'jetPt':"jetPt", 'jetPt2':"jetPt", 'jetEta':"jetEta", 'jetEta2':"jetEta2", 'PFMTT':"PFMTT", 'ncommjet':"ncommjet", 'AlphaT_vs_HT':"AlphaT_vs_HT", 'Bmass':"Bmass" }
    self.plotsname_name={'AlphaT':"AlphaT", 'HT':"HT", 'nVertex':"nVertex", 'MHT':"MHT", 'MHToverMET':"MHToverMET", 'nbjet':"number of B-jet", 'muPt':"muon Pt", 'Zmass':"Zmass", 'MET':"MET", 'muonIso':"muonIso", 'muPt2':"second muon Pt2", 'jetPt':"leading jet Pt", 'jetPt2':"second leading jet Pt", 'jetEta':"leading jet Eta", 'jetEta2':"second leading jetEta", 'PFMTT':"PFMT", 'ncommjet':"number of common jet", 'AlphaT_vs_HT':"RA1 binned HT", 'Bmass':"Bmass" }
#    self.Alpha_Webpage(self.btag_slices, self.plotsname,link="",outertitle=sys.argv[1],slice="",stacked = "", uselog="True")
#    self.Alpha_Webpage(self.btag_slices, self.plotsname,link="",outertitle=sys.argv[1]+"_linearScale",slice="",stacked = "", uselog="")
    self.Alpha_Webpage(self.HTBins, self.btag_slices, self.plotsname,link="",outertitle=sys.argv[1],slice="",stacked = "Stack_", uselog="True", scale="")
    self.Alpha_Webpage(self.HTBins, self.btag_slices, self.plotsname,link="",outertitle=sys.argv[1]+"_linearScale",slice="",stacked = "Stack_", uselog="", scale="_linearScale")

  def Alpha_Webpage(self,HTbins,Btag,inner,link="",outertitle="",slice="",simplified="",stacked="", uselog="True", scale=""):
    htF2 = open('./'+stacked+outertitle+'.html','w')
    htF2.write('<a href=full-colour-png_UoB.png><img width=\"10%\" src=\"full-colour-png_UoB.png\"></a> \n') 
    htF2.write('<a href=CMS_Color-Label.jpg><img width=\"10%\" src=\"CMS_Color-Label.jpg\" align = right></a> \n') 
    htF2.write('<br> \n <br> \n <br> \n')
    htF2.write('Author: Zhaoxia Meng <br> \n')
    htF2.write('<script language="Javascript"> \n document.write("Last Modified: " + document.lastModified + ""); \n </script> <br> \n ')
    htF2.write('<br> \n <br> \n')
    htF2.write('Selection : ')
    htF2.write('<br> \n')
    for jtitle in self.title:
      htF2.write('<a href=\"'+stacked+self.MuonNum[jtitle]+scale+'.html\">'+(stacked+self.MuonNum[jtitle])+'</a>  | ')
    htF2.write('<a href=\"./\"> Go back to parent link</a>  |  ')
    htF2.write('<br> \n')
    htF2.write('<br> \n')
      
    for ititle in self.title:
      htF1 = open('./'+stacked+self.MuonNum[ititle]+scale+'.html','w')
      htF1.write('<a href=full-colour-png_UoB.png><img width=\"10%\" src=\"full-colour-png_UoB.png\"></a> \n') 
      htF1.write('<a href=CMS_Color-Label.jpg><img width=\"10%\" src=\"CMS_Color-Label.jpg\" align = right></a> \n') 
      htF1.write('<br> \n <br> \n <br> \n')
      htF1.write('Author: Zhaoxia Meng <br> \n')
      htF1.write('<script language="Javascript"> \n document.write("Last Modified: " + document.lastModified + ""); \n </script> <br> \n ')
      htF1.write('<br> \n <br> \n')
      htF1.write('<a href=\"'+'./'+stacked+outertitle+scale+'.html\"> Go back to parent link</a>  |  ')
      htF1.write('<br> \n <br> \n')
      htF1.write('Go to selection:')
      for jtitle in self.title:
        htF1.write('<a href=\"'+'./'+stacked+self.MuonNum[jtitle]+scale+'.html\"> '+stacked+self.MuonNum[jtitle]+'</a> | ')
      htF1.write('<br> \n <br> \n')
      htF1.write('You are currently at : ')
      htF1.write('<a href=\"'+'./'+stacked+self.MuonNum[ititle]+scale+'.html\"> '+stacked+self.MuonNum[ititle]+'</a> ')
      htF1.write('<br> \n <br> \n')
      htF1.write('Hist Name: ')
      for iHT in HTbins:
        htF1.write('<a href=\"'+stacked+iHT+'_'+self.MuonNum[ititle]+scale+'.html\">'+(self.HTBin_names[iHT])+'</a>  |  ')
      htF1.write('<br> \n')

      for iHT in HTbins:
        htF3=open('./'+stacked+iHT+'_'+self.MuonNum[ititle]+scale+'.html','w')
        htF3.write('<a href=\"'+'./'+stacked+self.MuonNum[ititle]+scale+'.html\"> Go back to parent link</a>  ')
        htF3.write('<br> \n <br> \n <br> \n')          
        htF3.write('Go to HT bin:')
        for jHT in HTbins:
          htF3.write('<a href=\"'+'./'+stacked+jHT+'_'+self.MuonNum[ititle]+scale+'.html\">'+(self.HTBin_names[jHT])+'</a>  |  ')
        htF3.write('You are currently at HT bin:')
        htF3.write('<a href=\"'+'./'+stacked+iHT+'_'+self.MuonNum[ititle]+scale+'.html\">'+(self.HTBin_names[iHT])+'</a>')
        htF3.write('<br> \n <br> \n')
        htF3.write('B-tag:')
        for ib in Btag:
          htF3.write('<a href=\"'+stacked+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\">'+(self.btag_names[ib])+'</a>  |  ')
        htF3.write('<br> \n <br> \n')

        for ib in Btag:
          htF = open('./'+stacked+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html','w')
          htF.write('<a href=full-colour-png_UoB.png><img width=\"10%\" src=\"full-colour-png_UoB.png\"></a> \n')
          htF.write('<a href=CMS_Color-Label.jpg><img width=\"10%\" src=\"CMS_Color-Label.jpg\" align = right></a> \n')
          htF.write('<br> \n <br> \n <br> \n')
          htF.write('Author: Zhaoxia Meng <br> \n')
          htF.write('<script language="Javascript"> \n document.write("Last Modified: " + document.lastModified + ""); \n </script> <br> \n ')
          htF.write('<center>\n <p> \n <font size="5"> Selection: '+self.MuonNum[ititle]+' Plots </font>\n </p>\n')
#          htF.write('<font size="3"> HT: '+self.HTBin_names[iHT]+' </font><br> \n')
#          htF.write('<font size="3"> b-multiplicty:: '+self.btag_names[ib]+' </font><br> \n')
          htF.write('<br> \n <br> \n')
          htF.write('<a href=\"'+'./'+stacked+iHT+'_'+self.MuonNum[ititle]+scale+'.html\"> Go back to parent link</a>  ')
          htF.write('<br> \n <br> \n')
          htF.write('Go to selection: ')
          for jtitle in self.title:
            htF.write('<a href=\"'+'./'+stacked+iHT+'_'+ib+'_'+self.MuonNum[jtitle]+scale+'.html\">'+stacked+self.MuonNum[jtitle]+'</a>  ')
          htF.write('You are currently at Selection:  ')
          htF.write('<a href=\"'+'./'+stacked+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\" >'+stacked+self.MuonNum[ititle]+'</a>  ')
          htF.write('<br> \n <br> \n')
          htF.write('Go to HT bin:')
          for jHT in HTbins:
            htF.write('<a href=\"'+'./'+stacked+jHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\">'+(self.HTBin_names[jHT])+'</a>  |  ')
          htF.write('You are currently at HT bin:')
          htF.write('<a href=\"'+'./'+stacked+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\">'+(self.HTBin_names[iHT])+'</a>  |  ')
          htF.write('<br> \n')
          htF.write('<br> \n')
          htF.write('Go to b-multiplicity:')
          for jb in Btag:
            htF.write('<a href=\"'+'./'+stacked+iHT+'_'+jb+'_'+self.MuonNum[ititle]+scale+'.html\"> '+self.btag_names[jb]+'</a>  |  ')
          htF.write('You are currently at b-multiplicty: ')
          htF.write('<a href=\"'+'./'+stacked+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\"> '+self.btag_names[ib]+'</a>  ')
          htF.write('<br> \n')
          htF.write('<br> \n')
          htF.write('<br> \n')
          htF.write('Plot:')
          for jplot in inner:
            htF.write('<a href=\"./'+stacked+self.plotsname[jplot]+'_'+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\">'+(self.plotsname_name[jplot])+'</a>  ')
          log='_log'
          if not uselog:
            log=''
          for iplot in inner:
            htFplot=open('./'+stacked+self.plotsname[iplot]+'_'+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html','w')            
            htFplot.write('<a href=full-colour-png_UoB.png><img width=\"10%\" src=\"full-colour-png_UoB.png\"></a> \n')
            htFplot.write('<a href=CMS_Color-Label.jpg><img width=\"10%\" src=\"CMS_Color-Label.jpg\" align = right></a> \n')
            htFplot.write('<br> \n <br> \n <br> \n')
            htFplot.write('Author: Zhaoxia Meng <br> \n')
            htFplot.write('<script language="Javascript"> \n document.write("Last Modified: " + document.lastModified + ""); \n </script> <br> \n ')
            htFplot.write('<br> \n <br> \n')
            htFplot.write('<a href=\"./'+stacked+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\"> Go back to parent link</a>  ')
            htFplot.write('<br> \n')
            htFplot.write('<br> \n')
            htFplot.write('Go to selection: ')
            for jtitle in self.title:
              htFplot.write('<a href=\"'+'./'+stacked+self.plotsname[iplot]+'_'+iHT+'_'+ib+'_'+self.MuonNum[jtitle]+scale+'.html\">'+stacked+self.MuonNum[jtitle]+'</a>  ')
            htFplot.write('    You are currently at selection: ')
            htFplot.write('<a href=\"'+'./'+stacked+self.plotsname[iplot]+'_'+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\" >'+stacked+self.MuonNum[ititle]+'</a>  ')
            htFplot.write('<br> \n <br> \n')
            htFplot.write('Go to HT bin:')
            for jHT in HTbins:
              htFplot.write('<a href=\"'+'./'+stacked+self.plotsname[iplot]+'_'+jHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\">'+(self.HTBin_names[jHT])+'</a>  |  ')
            htFplot.write('You are currently at HT bin: ')
            htFplot.write('<a href=\"'+'./'+stacked+self.plotsname[iplot]+'_'+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\">'+(self.HTBin_names[iHT])+'</a>  |  ')
            htFplot.write('<br> \n')
            htFplot.write('<br> \n')
            htFplot.write('Go to b-multiplicity: ')
            for jb in Btag:
              htFplot.write('<a href=\"'+'./'+stacked+self.plotsname[iplot]+'_'+iHT+'_'+jb+'_'+self.MuonNum[ititle]+scale+'.html\"> '+self.btag_names[jb]+'</a>  |  ')
            htFplot.write('You are currently at b-multiplicty: ')
            htFplot.write('<a href=\"'+'./'+stacked+self.plotsname[iplot]+'_'+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\"> '+self.btag_names[ib]+'</a>  ')
            htFplot.write('<br> \n')
            htFplot.write('<br> \n')
            htFplot.write('Go to plot: ')
            for jplot in inner:
              htFplot.write('<a href=\"./'+stacked+self.plotsname[jplot]+'_'+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\">'+(self.plotsname_name[jplot])+'</a>  ')
            htFplot.write('You are currently at plot: ')
            htFplot.write('<a href=\"./'+stacked+self.plotsname[iplot]+'_'+iHT+'_'+ib+'_'+self.MuonNum[ititle]+scale+'.html\">'+(self.plotsname_name[iplot])+'</a>  ')
            htFplot.write('<br> \n')
            htFplot.write('<br> \n')
            for root,dirs,files in os.walk('plotsAndtables'+scale+'/'):
              sorter = []
              if self.title[ititle] == "HadSele":
                tmp=''
                for iht in self.jet_names:
                  tmp=tmp+iht+' | '
                htFplot.write('<center>\n <p> \n <font size="5"> '+ tmp + ' </font>\n </p>\n')
                for ijet in self.jet_slices:
                  for filenames in fnmatch.filter(files,(stacked+inner[iplot]+"_"+self.title[ititle]+"_"+HTbins[iHT]+self.jet_slices[ijet]+"_"+Btag[ib]+log+'.png') ):
                    sorter.append("plotsAndtables"+scale+"/"+filenames)
                for plot in sorter: htFplot.write('<a href='+plot+'><img width=\"30%\" src=\"'+plot+'\"></a> \n')
                htFplot.write('<br> \n')
                htFplot.write('<br> \n')
                
              else:
                tmp=''
                for iht in self.jet_names:
                  tmp=tmp+iht+' | '
                htFplot.write('<center>\n <p> \n <font size="5"> '+ tmp + ' </font>\n </p>\n')
                for ijet in self.jet_slices:
                  for filenames in fnmatch.filter(files,(stacked+inner[iplot]+"_"+self.title[ititle]+"_"+HTbins[iHT]+"_"+self.MuonNum[ititle]+self.jet_slices[ijet]+"_"+Btag[ib]+log+'.png') ):
                    sorter.append("plotsAndtables"+scale+"/"+filenames)
                for plot in sorter: htFplot.write('<a href='+plot+'><img width=\"30%\" src=\"'+plot+'\"></a> \n')
                htFplot.write('<br> \n')
                htFplot.write('<br> \n')
                
          def print_(self):
              print self.title
              for (k,v) in  self.btag_slices.iteritems():
                  print "%s = %s" % (k,v)

        def print_(self):
            print self.title
            for (k,v) in  self.HTBins.iteritems():
                print "%s = %s" % (k,v)



a=Make_Page(title={}, MuonNum={}, jet_slices={}, btag_slices={}, btag_names={}, HTBins={}, HTBin_names={}, plotsname={}, plotsname_name={} )
#a.print_()




