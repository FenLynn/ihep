# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
#usage make test
#
# Author: Fons Rademakers, 29/2/2000

#include $(ROOTSYS)/test/Makefile.arch
include /workfs/bes/lify/external/Makefile.arch
#ROOTLIBS += -lRooFit

#file path
#VPATH = /ihepbatch/bes/dusx/common
#------------------------------------------------------------------------------

TOPOLOGYO     = topology.$(ObjSuf) TopologyCategory.$(ObjSuf)\
		ParticleObject.$(ObjSuf)
TOPOLOGYS     = topology.$(SrcSuf) TopologyCategory.$(SrcSuf)\
		ParticleObject.$(SrcSuf)
TOPOLOGY      = topology$(ExeSuf)


OBJS          = $(TOPOLOGYO) 

PROGRAMS      = $(TOPOLOGY)

#------------------------------------------------------------------------------

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)
.PHONY:    clean

all:            $(PROGRAMS)


$(TOPOLOGY):    $(TOPOLOGYO)
		$(LD) $(LDFLAGS) $^ $(LIBS) $(OutPutOpt)$@
		@echo "$@ done"


clean:
		@rm -f $(OBJS) core *.err *.log mclist.txt topo.root log.txt




.SUFFIXES: .$(SrcSuf)

###

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<
