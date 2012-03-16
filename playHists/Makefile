ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)
CXXFLAGS      =-I$(ROOTSYS)/include -O -Wall -fPIC

SOURCEDIR	=  ./

HEADERDIR	= ./


all:tdrstyle.o playHist2D.o playHist1D.o project2DHists.o getTranslationFactor.o basicPlots.o printTables.o TrueWPt.o rootdict.o main.exe

rootdict.C:    ./linkdef.h
	@echo "Generating dictionary"
	$(ROOTSYS)/bin/rootcint    -f $(BIN)rootdict.C -c $^
	@echo "OK"

rootdict.o:rootdict.C
	g++ -c rootdict.C -o $@ -I $(ROOTCFLAGS) -I . -I $(SOURCEDIR) -I $(HEADERDIR)

tdrstyle.o:tdrstyle.C
	g++ -c tdrstyle.C -o $@ -I $(ROOTCFLAGS) -I . -I $(SOURCEDIR) -I $(HEADERDIR)



playHist2D.o:playHist2D.C playHist2D.h 
	g++ -c playHist2D.C -o $@ -I $(ROOTCFLAGS) -I . -I $(SOURCEDIR) -I $(HEADERDIR)

playHist1D.o:playHist1D.C playHist1D.h 
	g++ -c playHist1D.C -o $@ -I $(ROOTCFLAGS) -I . -I $(SOURCEDIR) -I $(HEADERDIR)

project2DHists.o:project2DHists.C project2DHists.h 
	g++ -c project2DHists.C -o $@ -I $(ROOTCFLAGS) -I . -I $(SOURCEDIR) -I $(HEADERDIR)

getTranslationFactor.o:getTranslationFactor.C getTranslationFactor.h 
	g++ -c getTranslationFactor.C -o $@ -I $(ROOTCFLAGS) -I . -I $(SOURCEDIR) -I $(HEADERDIR)

basicPlots.o:basicPlots.C basicPlots.h
	g++ -c basicPlots.C -o $@ -I $(ROOTCFLAGS) -I . -I $(SOURCEDIR) -I $(HEADERDIR)

printTables.o:printTables.C printTables.h
	g++ -c printTables.C -o $@ -I $(ROOTCFLAGS) -I . -I $(SOURCEDIR) -I $(HEADERDIR)

TrueWPt.o:TrueWPt.C TrueWPt.h 
	g++ -c TrueWPt.C -o $@ -I $(ROOTCFLAGS) -I . -I $(SOURCEDIR) -I $(HEADERDIR)



main.exe:main.C
	g++ -O3 -Wall -I $(ROOTCFLAGS) $^ -o $@ tdrstyle.o playHist2D.o playHist1D.o project2DHists.o TrueWPt.o getTranslationFactor.o basicPlots.o printTables.o rootdict.o $(DQSO) -I . -I $(SOURCEDIR)  -I $(HEADERDIR) $(ROOTLIBS)


#main.exe:main.C tauperf.C file.txt
#	g++ -O3 -Wall `root-config --cflags` `root-config --libs` -o main.exe main.C tauperf.C -I $(SOURCEDIR) -I $(HEADERDIR)
echo:
	echo "ROOTCFLAGS=$(ROOTCFLAGS)"
	echo "ROOTLIBS=$(ROOTLIBS)"
	echo "ROOTSYS=$(ROOTSYS)"
	echo "PATH=$(PATH)"
	echo "LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)"
clean: 
	rm -rf main.exe *.o *~ 
deadcor.exe:



