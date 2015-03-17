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
    -IOMNeTWorkshop/includes \
    -IOMNeTWorkshop/plots \
    -IOMNeTWorkshop/presentation \
    -IOMNeTWorkshop/presentation/bin \
    -IOMNeTWorkshop/presentation/disco \
    -IOMNeTWorkshop/presentation/topologies \
    -IOMNeTWorkshop/topologies \
    -Iadversaries \
    -Ianalysis \
    -Ianalysis/documentation \
    -Ianalysis/documentation/2012-11-15-icdcs \
    -Ianalysis/documentation/2012-12-08-omnetworkshop \
    -Ianalysis/documentation/2013-05-01-disc \
    -Ianalysis/documentation/2013-05-01-disc/1 \
    -Ianalysis/documentation/2013-05-01-disc/2 \
    -Ianalysis/documentation/2013-05-01-disc/3 \
    -Ianalysis/documentation/2013-05-01-disc/4 \
    -Ianalysis/documentation/2013-05-01-disc/5 \
    -Ianalysis/documentation/2013-05-01-disc/bothRand1 \
    -Ianalysis/documentation/2013-05-01-disc/bothRand2 \
    -Ianalysis/documentation/2013-05-01-disc/testcase \
    -Ianalysis/documentation/2013-05-01-disc/testcase2 \
    -Ianalysis/documentation/2014-07-30-queueingsystems \
    -Ichannelvariation \
    -Iicdcs2013 \
    -Iicdcs2013/bin \
    -Iicdcs2013/topologies \
    -Iicdcs2013/website \
    -Imessages \
    -Inetworks \
    -Inode \
    -IoldPaperDrafts \
    -IoldPaperDrafts/bin \
    -IoldPaperDrafts/plots \
    -Iqueueingsystems2015 \
    -Iqueueingsystems2015/bin \
    -Iqueueingsystems2015/maxima \
    -Iqueueingsystems2015/plots \
    -Iqueueingsystems2015/plots/Randomization \
    -Iqueueingsystems2015/topologies \
    -Iqueueingsystems2015/topologies/bin \
    -Iresultsarchive2014 \
    -Iresultsarchive2014/results.1.test1failed \
    -Iresultsarchive2014/results.3.testtoolargemeans \
    -Iresultsarchive2014/results.5.100pc-steps_0.00001-3000 \
    -Iresultsarchive2014/results.oldas.1Sep2014 \
    -Iresultsarchive2014/results_DiazLotker_Diazok_LotkerSmallQueue \
    -Iresultsarchive2014/results_LotkerMod_broken66percentloss \
    -Iresultsarchive2014/results_LotkerMod_noloss_queue10000 \
    -Iresultsarchive2014/results_cdBBCE3CE71_r092_rep20 \
    -Iresultsarchive2014/results_infcdBBCE3CE71_r092_seeds0-29_iset100 \
    -Iresultsarchive2014/results_infcdBB_r083_seed0-499_iset100 \
    -Iresultsarchive2014/results_infcdBB_r084_seed0-499_iset100 \
    -Iresultsarchive2014/results_infiaBBCE3CE71_r089_seed0-19_iset100 \
    -Iresultsarchive2014/results_infiaBBCE3_infcdCE71_r086r088r082_s500s500s100_iset100 \
    -Iresultsarchive2014/results_infiaBBCE3_infcdCE71_r086r088r082_s500s500s100_iset100/results.no-use \
    -Iresultsarchive2014/results_infiaBBCE3_r087_seed0-19_iset100 \
    -Iresultsarchive2014/results_infiaBBCE3_r088_seed0-19_iset100 \
    -Iresultsarchive2014/results_infiaBB_r086_seed0-19_iset100 \
    -Iresultsarchive2014/results_infiaBB_r092_rep30 \
    -Iresultsarchive2014/results_infiaBB_r095_rep20 \
    -Iresultsarchive2014/results_infia_infcd_BBCE3CE71_r092_rep50 \
    -Iruns \
    -Isigmetrics2014 \
    -Isigmetrics2014/bin \
    -Isigmetrics2014/maxima \
    -Isigmetrics2014/plots \
    -Isigmetrics2014/plots/Randomization \
    -Isigmetrics2014/topologies \
    -Isigmetrics2014/topologies/bin

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
    $O/adversaries/CE7half.o \
    $O/adversaries/QueueListener.o \
    $O/adversaries/APlusMinor.o \
    $O/adversaries/CE3.o \
    $O/adversaries/Diaz.o \
    $O/adversaries/Koukopoulos.o \
    $O/adversaries/AdvancedAdversary.o \
    $O/adversaries/BBhalf.o \
    $O/adversaries/CE75.o \
    $O/adversaries/CE7.o \
    $O/adversaries/CE71.o \
    $O/adversaries/Lotker.o \
    $O/adversaries/CF3.o \
    $O/adversaries/CE3half.o \
    $O/adversaries/CF7.o \
    $O/adversaries/BB.o \
    $O/adversaries/LotkerMod.o \
    $O/channelvariation/Randomization.o \
    $O/channelvariation/VDrChannel.o \
    $O/node/L2Queue.o \
    $O/node/SourceRoutingApp.o \
    $O/node/SourceRouting.o \
    $O/messages/QueueLengthRequest_m.o \
    $O/messages/AdversarialInjectionMessage_m.o \
    $O/messages/SourceRoutingPacket_m.o

# Message files
MSGFILES = \
    messages/QueueLengthRequest.msg \
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
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f adversarialQueueing adversarialQueueing.exe libadversarialQueueing.so libadversarialQueueing.a libadversarialQueueing.dll libadversarialQueueing.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f OMNeTWorkshop/*_m.cc OMNeTWorkshop/*_m.h
	$(Q)-rm -f OMNeTWorkshop/includes/*_m.cc OMNeTWorkshop/includes/*_m.h
	$(Q)-rm -f OMNeTWorkshop/plots/*_m.cc OMNeTWorkshop/plots/*_m.h
	$(Q)-rm -f OMNeTWorkshop/presentation/*_m.cc OMNeTWorkshop/presentation/*_m.h
	$(Q)-rm -f OMNeTWorkshop/presentation/bin/*_m.cc OMNeTWorkshop/presentation/bin/*_m.h
	$(Q)-rm -f OMNeTWorkshop/presentation/disco/*_m.cc OMNeTWorkshop/presentation/disco/*_m.h
	$(Q)-rm -f OMNeTWorkshop/presentation/topologies/*_m.cc OMNeTWorkshop/presentation/topologies/*_m.h
	$(Q)-rm -f OMNeTWorkshop/topologies/*_m.cc OMNeTWorkshop/topologies/*_m.h
	$(Q)-rm -f adversaries/*_m.cc adversaries/*_m.h
	$(Q)-rm -f analysis/*_m.cc analysis/*_m.h
	$(Q)-rm -f analysis/documentation/*_m.cc analysis/documentation/*_m.h
	$(Q)-rm -f analysis/documentation/2012-11-15-icdcs/*_m.cc analysis/documentation/2012-11-15-icdcs/*_m.h
	$(Q)-rm -f analysis/documentation/2012-12-08-omnetworkshop/*_m.cc analysis/documentation/2012-12-08-omnetworkshop/*_m.h
	$(Q)-rm -f analysis/documentation/2013-05-01-disc/*_m.cc analysis/documentation/2013-05-01-disc/*_m.h
	$(Q)-rm -f analysis/documentation/2013-05-01-disc/1/*_m.cc analysis/documentation/2013-05-01-disc/1/*_m.h
	$(Q)-rm -f analysis/documentation/2013-05-01-disc/2/*_m.cc analysis/documentation/2013-05-01-disc/2/*_m.h
	$(Q)-rm -f analysis/documentation/2013-05-01-disc/3/*_m.cc analysis/documentation/2013-05-01-disc/3/*_m.h
	$(Q)-rm -f analysis/documentation/2013-05-01-disc/4/*_m.cc analysis/documentation/2013-05-01-disc/4/*_m.h
	$(Q)-rm -f analysis/documentation/2013-05-01-disc/5/*_m.cc analysis/documentation/2013-05-01-disc/5/*_m.h
	$(Q)-rm -f analysis/documentation/2013-05-01-disc/bothRand1/*_m.cc analysis/documentation/2013-05-01-disc/bothRand1/*_m.h
	$(Q)-rm -f analysis/documentation/2013-05-01-disc/bothRand2/*_m.cc analysis/documentation/2013-05-01-disc/bothRand2/*_m.h
	$(Q)-rm -f analysis/documentation/2013-05-01-disc/testcase/*_m.cc analysis/documentation/2013-05-01-disc/testcase/*_m.h
	$(Q)-rm -f analysis/documentation/2013-05-01-disc/testcase2/*_m.cc analysis/documentation/2013-05-01-disc/testcase2/*_m.h
	$(Q)-rm -f analysis/documentation/2014-07-30-queueingsystems/*_m.cc analysis/documentation/2014-07-30-queueingsystems/*_m.h
	$(Q)-rm -f channelvariation/*_m.cc channelvariation/*_m.h
	$(Q)-rm -f icdcs2013/*_m.cc icdcs2013/*_m.h
	$(Q)-rm -f icdcs2013/bin/*_m.cc icdcs2013/bin/*_m.h
	$(Q)-rm -f icdcs2013/topologies/*_m.cc icdcs2013/topologies/*_m.h
	$(Q)-rm -f icdcs2013/website/*_m.cc icdcs2013/website/*_m.h
	$(Q)-rm -f messages/*_m.cc messages/*_m.h
	$(Q)-rm -f networks/*_m.cc networks/*_m.h
	$(Q)-rm -f node/*_m.cc node/*_m.h
	$(Q)-rm -f oldPaperDrafts/*_m.cc oldPaperDrafts/*_m.h
	$(Q)-rm -f oldPaperDrafts/bin/*_m.cc oldPaperDrafts/bin/*_m.h
	$(Q)-rm -f oldPaperDrafts/plots/*_m.cc oldPaperDrafts/plots/*_m.h
	$(Q)-rm -f queueingsystems2015/*_m.cc queueingsystems2015/*_m.h
	$(Q)-rm -f queueingsystems2015/bin/*_m.cc queueingsystems2015/bin/*_m.h
	$(Q)-rm -f queueingsystems2015/maxima/*_m.cc queueingsystems2015/maxima/*_m.h
	$(Q)-rm -f queueingsystems2015/plots/*_m.cc queueingsystems2015/plots/*_m.h
	$(Q)-rm -f queueingsystems2015/plots/Randomization/*_m.cc queueingsystems2015/plots/Randomization/*_m.h
	$(Q)-rm -f queueingsystems2015/topologies/*_m.cc queueingsystems2015/topologies/*_m.h
	$(Q)-rm -f queueingsystems2015/topologies/bin/*_m.cc queueingsystems2015/topologies/bin/*_m.h
	$(Q)-rm -f resultsarchive2014/*_m.cc resultsarchive2014/*_m.h
	$(Q)-rm -f resultsarchive2014/results.1.test1failed/*_m.cc resultsarchive2014/results.1.test1failed/*_m.h
	$(Q)-rm -f resultsarchive2014/results.3.testtoolargemeans/*_m.cc resultsarchive2014/results.3.testtoolargemeans/*_m.h
	$(Q)-rm -f resultsarchive2014/results.5.100pc-steps_0.00001-3000/*_m.cc resultsarchive2014/results.5.100pc-steps_0.00001-3000/*_m.h
	$(Q)-rm -f resultsarchive2014/results.oldas.1Sep2014/*_m.cc resultsarchive2014/results.oldas.1Sep2014/*_m.h
	$(Q)-rm -f resultsarchive2014/results_DiazLotker_Diazok_LotkerSmallQueue/*_m.cc resultsarchive2014/results_DiazLotker_Diazok_LotkerSmallQueue/*_m.h
	$(Q)-rm -f resultsarchive2014/results_LotkerMod_broken66percentloss/*_m.cc resultsarchive2014/results_LotkerMod_broken66percentloss/*_m.h
	$(Q)-rm -f resultsarchive2014/results_LotkerMod_noloss_queue10000/*_m.cc resultsarchive2014/results_LotkerMod_noloss_queue10000/*_m.h
	$(Q)-rm -f resultsarchive2014/results_cdBBCE3CE71_r092_rep20/*_m.cc resultsarchive2014/results_cdBBCE3CE71_r092_rep20/*_m.h
	$(Q)-rm -f resultsarchive2014/results_infcdBBCE3CE71_r092_seeds0-29_iset100/*_m.cc resultsarchive2014/results_infcdBBCE3CE71_r092_seeds0-29_iset100/*_m.h
	$(Q)-rm -f resultsarchive2014/results_infcdBB_r083_seed0-499_iset100/*_m.cc resultsarchive2014/results_infcdBB_r083_seed0-499_iset100/*_m.h
	$(Q)-rm -f resultsarchive2014/results_infcdBB_r084_seed0-499_iset100/*_m.cc resultsarchive2014/results_infcdBB_r084_seed0-499_iset100/*_m.h
	$(Q)-rm -f resultsarchive2014/results_infiaBBCE3CE71_r089_seed0-19_iset100/*_m.cc resultsarchive2014/results_infiaBBCE3CE71_r089_seed0-19_iset100/*_m.h
	$(Q)-rm -f resultsarchive2014/results_infiaBBCE3_infcdCE71_r086r088r082_s500s500s100_iset100/*_m.cc resultsarchive2014/results_infiaBBCE3_infcdCE71_r086r088r082_s500s500s100_iset100/*_m.h
	$(Q)-rm -f resultsarchive2014/results_infiaBBCE3_infcdCE71_r086r088r082_s500s500s100_iset100/results.no-use/*_m.cc resultsarchive2014/results_infiaBBCE3_infcdCE71_r086r088r082_s500s500s100_iset100/results.no-use/*_m.h
	$(Q)-rm -f resultsarchive2014/results_infiaBBCE3_r087_seed0-19_iset100/*_m.cc resultsarchive2014/results_infiaBBCE3_r087_seed0-19_iset100/*_m.h
	$(Q)-rm -f resultsarchive2014/results_infiaBBCE3_r088_seed0-19_iset100/*_m.cc resultsarchive2014/results_infiaBBCE3_r088_seed0-19_iset100/*_m.h
	$(Q)-rm -f resultsarchive2014/results_infiaBB_r086_seed0-19_iset100/*_m.cc resultsarchive2014/results_infiaBB_r086_seed0-19_iset100/*_m.h
	$(Q)-rm -f resultsarchive2014/results_infiaBB_r092_rep30/*_m.cc resultsarchive2014/results_infiaBB_r092_rep30/*_m.h
	$(Q)-rm -f resultsarchive2014/results_infiaBB_r095_rep20/*_m.cc resultsarchive2014/results_infiaBB_r095_rep20/*_m.h
	$(Q)-rm -f resultsarchive2014/results_infia_infcd_BBCE3CE71_r092_rep50/*_m.cc resultsarchive2014/results_infia_infcd_BBCE3CE71_r092_rep50/*_m.h
	$(Q)-rm -f runs/*_m.cc runs/*_m.h
	$(Q)-rm -f sigmetrics2014/*_m.cc sigmetrics2014/*_m.h
	$(Q)-rm -f sigmetrics2014/bin/*_m.cc sigmetrics2014/bin/*_m.h
	$(Q)-rm -f sigmetrics2014/maxima/*_m.cc sigmetrics2014/maxima/*_m.h
	$(Q)-rm -f sigmetrics2014/plots/*_m.cc sigmetrics2014/plots/*_m.h
	$(Q)-rm -f sigmetrics2014/plots/Randomization/*_m.cc sigmetrics2014/plots/Randomization/*_m.h
	$(Q)-rm -f sigmetrics2014/topologies/*_m.cc sigmetrics2014/topologies/*_m.h
	$(Q)-rm -f sigmetrics2014/topologies/bin/*_m.cc sigmetrics2014/topologies/bin/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc OMNeTWorkshop/*.cc OMNeTWorkshop/includes/*.cc OMNeTWorkshop/plots/*.cc OMNeTWorkshop/presentation/*.cc OMNeTWorkshop/presentation/bin/*.cc OMNeTWorkshop/presentation/disco/*.cc OMNeTWorkshop/presentation/topologies/*.cc OMNeTWorkshop/topologies/*.cc adversaries/*.cc analysis/*.cc analysis/documentation/*.cc analysis/documentation/2012-11-15-icdcs/*.cc analysis/documentation/2012-12-08-omnetworkshop/*.cc analysis/documentation/2013-05-01-disc/*.cc analysis/documentation/2013-05-01-disc/1/*.cc analysis/documentation/2013-05-01-disc/2/*.cc analysis/documentation/2013-05-01-disc/3/*.cc analysis/documentation/2013-05-01-disc/4/*.cc analysis/documentation/2013-05-01-disc/5/*.cc analysis/documentation/2013-05-01-disc/bothRand1/*.cc analysis/documentation/2013-05-01-disc/bothRand2/*.cc analysis/documentation/2013-05-01-disc/testcase/*.cc analysis/documentation/2013-05-01-disc/testcase2/*.cc analysis/documentation/2014-07-30-queueingsystems/*.cc channelvariation/*.cc icdcs2013/*.cc icdcs2013/bin/*.cc icdcs2013/topologies/*.cc icdcs2013/website/*.cc messages/*.cc networks/*.cc node/*.cc oldPaperDrafts/*.cc oldPaperDrafts/bin/*.cc oldPaperDrafts/plots/*.cc queueingsystems2015/*.cc queueingsystems2015/bin/*.cc queueingsystems2015/maxima/*.cc queueingsystems2015/plots/*.cc queueingsystems2015/plots/Randomization/*.cc queueingsystems2015/topologies/*.cc queueingsystems2015/topologies/bin/*.cc resultsarchive2014/*.cc resultsarchive2014/results.1.test1failed/*.cc resultsarchive2014/results.3.testtoolargemeans/*.cc resultsarchive2014/results.5.100pc-steps_0.00001-3000/*.cc resultsarchive2014/results.oldas.1Sep2014/*.cc resultsarchive2014/results_DiazLotker_Diazok_LotkerSmallQueue/*.cc resultsarchive2014/results_LotkerMod_broken66percentloss/*.cc resultsarchive2014/results_LotkerMod_noloss_queue10000/*.cc resultsarchive2014/results_cdBBCE3CE71_r092_rep20/*.cc resultsarchive2014/results_infcdBBCE3CE71_r092_seeds0-29_iset100/*.cc resultsarchive2014/results_infcdBB_r083_seed0-499_iset100/*.cc resultsarchive2014/results_infcdBB_r084_seed0-499_iset100/*.cc resultsarchive2014/results_infiaBBCE3CE71_r089_seed0-19_iset100/*.cc resultsarchive2014/results_infiaBBCE3_infcdCE71_r086r088r082_s500s500s100_iset100/*.cc resultsarchive2014/results_infiaBBCE3_infcdCE71_r086r088r082_s500s500s100_iset100/results.no-use/*.cc resultsarchive2014/results_infiaBBCE3_r087_seed0-19_iset100/*.cc resultsarchive2014/results_infiaBBCE3_r088_seed0-19_iset100/*.cc resultsarchive2014/results_infiaBB_r086_seed0-19_iset100/*.cc resultsarchive2014/results_infiaBB_r092_rep30/*.cc resultsarchive2014/results_infiaBB_r095_rep20/*.cc resultsarchive2014/results_infia_infcd_BBCE3CE71_r092_rep50/*.cc runs/*.cc sigmetrics2014/*.cc sigmetrics2014/bin/*.cc sigmetrics2014/maxima/*.cc sigmetrics2014/plots/*.cc sigmetrics2014/plots/Randomization/*.cc sigmetrics2014/topologies/*.cc sigmetrics2014/topologies/bin/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/adversaries/APlusMinor.o: adversaries/APlusMinor.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h
$O/adversaries/AdvancedAdversary.o: adversaries/AdvancedAdversary.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h
$O/adversaries/BB.o: adversaries/BB.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h
$O/adversaries/BBhalf.o: adversaries/BBhalf.cc \
	messages/AdversarialInjectionMessage_m.h
$O/adversaries/CE3.o: adversaries/CE3.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h
$O/adversaries/CE3half.o: adversaries/CE3half.cc \
	messages/AdversarialInjectionMessage_m.h
$O/adversaries/CE7.o: adversaries/CE7.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h
$O/adversaries/CE71.o: adversaries/CE71.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h
$O/adversaries/CE75.o: adversaries/CE75.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h
$O/adversaries/CE7half.o: adversaries/CE7half.cc \
	messages/AdversarialInjectionMessage_m.h
$O/adversaries/CF3.o: adversaries/CF3.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h
$O/adversaries/CF7.o: adversaries/CF7.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h
$O/adversaries/Diaz.o: adversaries/Diaz.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h
$O/adversaries/Koukopoulos.o: adversaries/Koukopoulos.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h
$O/adversaries/Lotker.o: adversaries/Lotker.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h \
	node/L2Queue.h
$O/adversaries/LotkerMod.o: adversaries/LotkerMod.cc \
	adversaries/AdvancedAdversary.h \
	adversaries/QueueListener.h \
	messages/AdvSchedMess.h \
	messages/AdversarialInjectionMessage_m.h \
	messages/QueueLengthRequest_m.h \
	node/L2Queue.h
$O/adversaries/QueueListener.o: adversaries/QueueListener.cc \
	adversaries/QueueListener.h
$O/channelvariation/Randomization.o: channelvariation/Randomization.cc
$O/channelvariation/VDrChannel.o: channelvariation/VDrChannel.cc
$O/messages/AdversarialInjectionMessage_m.o: messages/AdversarialInjectionMessage_m.cc \
	messages/AdversarialInjectionMessage_m.h
$O/messages/QueueLengthRequest_m.o: messages/QueueLengthRequest_m.cc \
	messages/QueueLengthRequest_m.h
$O/messages/SourceRoutingPacket_m.o: messages/SourceRoutingPacket_m.cc \
	messages/SourceRoutingPacket_m.h
$O/node/L2Queue.o: node/L2Queue.cc \
	node/L2Queue.h
$O/node/SourceRouting.o: node/SourceRouting.cc \
	messages/QueueLengthRequest_m.h \
	messages/SourceRoutingPacket_m.h
$O/node/SourceRoutingApp.o: node/SourceRoutingApp.cc \
	messages/AdversarialInjectionMessage_m.h \
	messages/SourceRoutingPacket_m.h

