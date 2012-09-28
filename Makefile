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
    -Iadversaries \
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
    $O/adversaries/CE7Adversary.o \
    $O/adversaries/AdvancedAdversary.o \
    $O/adversaries/BBAdversary.o \
    $O/adversaries/CE7Advanced.o \
    $O/adversaries/CE3Adversary.o \
    $O/adversaries/CE3Advanced.o \
    $O/adversaries/QueueListener.o \
    $O/node/SourceRoutingApp.o \
    $O/node/L2Queue.o \
    $O/node/SourceRouting.o \
    $O/messages/AdversarialInjectionMessage_m.o \
    $O/messages/SourceRoutingPacket_m.o

# Message files
MSGFILES = \
    messages/AdversarialInjectionMessage.msg \
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
	-rm -f adversaries/*_m.cc adversaries/*_m.h
	-rm -f messages/*_m.cc messages/*_m.h
	-rm -f networks/*_m.cc networks/*_m.h
	-rm -f node/*_m.cc node/*_m.h
	-rm -f resultAnalysis/*_m.cc resultAnalysis/*_m.h
	-rm -f results/*_m.cc results/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc adversaries/*.cc messages/*.cc networks/*.cc node/*.cc resultAnalysis/*.cc results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/adversaries/AdvancedAdversary.o: adversaries/AdvancedAdversary.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/BBAdversary.o: adversaries/BBAdversary.cc \
	messages/AdversarialInjectionMessage_m.h
$O/adversaries/CE3Advanced.o: adversaries/CE3Advanced.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/CE3Adversary.o: adversaries/CE3Adversary.cc \
	messages/AdversarialInjectionMessage_m.h
$O/adversaries/CE7Advanced.o: adversaries/CE7Advanced.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h
$O/adversaries/CE7Adversary.o: adversaries/CE7Adversary.cc \
	messages/AdversarialInjectionMessage_m.h
$O/adversaries/QueueListener.o: adversaries/QueueListener.cc \
	adversaries/QueueListener.h
$O/messages/AdversarialInjectionMessage_m.o: messages/AdversarialInjectionMessage_m.cc \
	messages/AdversarialInjectionMessage_m.h
$O/messages/SourceRoutingPacket_m.o: messages/SourceRoutingPacket_m.cc \
	messages/SourceRoutingPacket_m.h
$O/node/L2Queue.o: node/L2Queue.cc
$O/node/SourceRouting.o: node/SourceRouting.cc
$O/node/SourceRoutingApp.o: node/SourceRoutingApp.cc

