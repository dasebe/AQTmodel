#
# OMNeT++/OMNEST Makefile for adversarialQueueing
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out
#

# Name of target to be created (-o option)
TARGET = adversarialQueueing$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -IOMNeTWorkshop \
    -IOMNeTWorkshop/bin \
    -IOMNeTWorkshop/plots \
    -IOMNeTWorkshop/topologies \
    -Iadversaries \
    -Ibuilder \
    -Idocumentation \
    -Idocumentation/IEEEtranBST \
    -Idocumentation/bin \
    -Idocumentation/plots \
    -Iicdcs2013 \
    -Iicdcs2013/IEEEtranBST \
    -Iicdcs2013/Jens-Photos \
    -Iicdcs2013/Jens-Photos13.11 \
    -Iicdcs2013/bin \
    -Iicdcs2013/cited \
    -Iicdcs2013/maxima \
    -Iicdcs2013/plots \
    -Iicdcs2013/plots/sources \
    -Iicdcs2013/topologies \
    -Iicdcs2013/topologies/bin \
    -Imessages \
    -Inetworks \
    -Inode \
    -IresultAnalysis \
    -Iresults

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/adversaries/AdvancedAdversary.o \
    $O/adversaries/CE71.o \
    $O/adversaries/CE7half.o \
    $O/adversaries/CE7.o \
    $O/adversaries/CF7.o \
    $O/adversaries/BB.o \
    $O/adversaries/CE3half.o \
    $O/adversaries/CE75.o \
    $O/adversaries/APlusMinor.o \
    $O/adversaries/CF3.o \
    $O/adversaries/QueueListener.o \
    $O/adversaries/Randomization.o \
    $O/adversaries/RandomizationDelay.o \
    $O/adversaries/Lotker1.o \
    $O/adversaries/CE3.o \
    $O/adversaries/BBhalf.o \
    $O/builder/netbuilder.o \
    $O/node/SourceRoutingApp.o \
    $O/node/L2Queue.o \
    $O/node/SourceRouting.o \
    $O/messages/AdversarialInjectionMessage_m.o \
    $O/messages/QueueLengthRequest_m.o \
    $O/messages/SourceRoutingPacket_m.o

# Message files
MSGFILES = \
    messages/AdversarialInjectionMessage.msg \
    messages/QueueLengthRequest.msg \
    messages/SourceRoutingPacket.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f adversarialQueueing adversarialQueueing.exe libadversarialQueueing.so libadversarialQueueing.a libadversarialQueueing.dll libadversarialQueueing.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f OMNeTWorkshop/*_m.cc OMNeTWorkshop/*_m.h
	-rm -f OMNeTWorkshop/bin/*_m.cc OMNeTWorkshop/bin/*_m.h
	-rm -f OMNeTWorkshop/plots/*_m.cc OMNeTWorkshop/plots/*_m.h
	-rm -f OMNeTWorkshop/topologies/*_m.cc OMNeTWorkshop/topologies/*_m.h
	-rm -f adversaries/*_m.cc adversaries/*_m.h
	-rm -f builder/*_m.cc builder/*_m.h
	-rm -f documentation/*_m.cc documentation/*_m.h
	-rm -f documentation/IEEEtranBST/*_m.cc documentation/IEEEtranBST/*_m.h
	-rm -f documentation/bin/*_m.cc documentation/bin/*_m.h
	-rm -f documentation/plots/*_m.cc documentation/plots/*_m.h
	-rm -f icdcs2013/*_m.cc icdcs2013/*_m.h
	-rm -f icdcs2013/IEEEtranBST/*_m.cc icdcs2013/IEEEtranBST/*_m.h
	-rm -f icdcs2013/Jens-Photos/*_m.cc icdcs2013/Jens-Photos/*_m.h
	-rm -f icdcs2013/Jens-Photos13.11/*_m.cc icdcs2013/Jens-Photos13.11/*_m.h
	-rm -f icdcs2013/bin/*_m.cc icdcs2013/bin/*_m.h
	-rm -f icdcs2013/cited/*_m.cc icdcs2013/cited/*_m.h
	-rm -f icdcs2013/maxima/*_m.cc icdcs2013/maxima/*_m.h
	-rm -f icdcs2013/plots/*_m.cc icdcs2013/plots/*_m.h
	-rm -f icdcs2013/plots/sources/*_m.cc icdcs2013/plots/sources/*_m.h
	-rm -f icdcs2013/topologies/*_m.cc icdcs2013/topologies/*_m.h
	-rm -f icdcs2013/topologies/bin/*_m.cc icdcs2013/topologies/bin/*_m.h
	-rm -f messages/*_m.cc messages/*_m.h
	-rm -f networks/*_m.cc networks/*_m.h
	-rm -f node/*_m.cc node/*_m.h
	-rm -f resultAnalysis/*_m.cc resultAnalysis/*_m.h
	-rm -f results/*_m.cc results/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc OMNeTWorkshop/*.cc OMNeTWorkshop/bin/*.cc OMNeTWorkshop/plots/*.cc OMNeTWorkshop/topologies/*.cc adversaries/*.cc builder/*.cc documentation/*.cc documentation/IEEEtranBST/*.cc documentation/bin/*.cc documentation/plots/*.cc icdcs2013/*.cc icdcs2013/IEEEtranBST/*.cc icdcs2013/Jens-Photos/*.cc icdcs2013/Jens-Photos13.11/*.cc icdcs2013/bin/*.cc icdcs2013/cited/*.cc icdcs2013/maxima/*.cc icdcs2013/plots/*.cc icdcs2013/plots/sources/*.cc icdcs2013/topologies/*.cc icdcs2013/topologies/bin/*.cc messages/*.cc networks/*.cc node/*.cc resultAnalysis/*.cc results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/adversaries/APlusMinor.o: adversaries/APlusMinor.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/AdvancedAdversary.o: adversaries/AdvancedAdversary.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/BB.o: adversaries/BB.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/BBhalf.o: adversaries/BBhalf.cc \
	messages/AdversarialInjectionMessage_m.h
$O/adversaries/CE3.o: adversaries/CE3.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/CE3half.o: adversaries/CE3half.cc \
	messages/AdversarialInjectionMessage_m.h
$O/adversaries/CE7.o: adversaries/CE7.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/CE71.o: adversaries/CE71.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/CE75.o: adversaries/CE75.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/CE7half.o: adversaries/CE7half.cc \
	messages/AdversarialInjectionMessage_m.h
$O/adversaries/CF3.o: adversaries/CF3.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/CF7.o: adversaries/CF7.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/Lotker1.o: adversaries/Lotker1.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/QueueListener.o: adversaries/QueueListener.cc \
	adversaries/QueueListener.h
$O/adversaries/Randomization.o: adversaries/Randomization.cc
$O/adversaries/RandomizationDelay.o: adversaries/RandomizationDelay.cc
$O/builder/netbuilder.o: builder/netbuilder.cc
$O/messages/AdversarialInjectionMessage_m.o: messages/AdversarialInjectionMessage_m.cc \
	messages/AdversarialInjectionMessage_m.h
$O/messages/QueueLengthRequest_m.o: messages/QueueLengthRequest_m.cc \
	messages/QueueLengthRequest_m.h
$O/messages/SourceRoutingPacket_m.o: messages/SourceRoutingPacket_m.cc \
	messages/SourceRoutingPacket_m.h
$O/node/L2Queue.o: node/L2Queue.cc \
	node/L2Queue.h
$O/node/SourceRouting.o: node/SourceRouting.cc
$O/node/SourceRoutingApp.o: node/SourceRoutingApp.cc

