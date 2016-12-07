import GaudiKernel.SystemOfUnits as Units
from Gaudi.Configuration import *
from PhysSelPython.Wrappers import AutomaticData, DataOnDemand, Selection, SelectionSequence
from Configurables import  CombineParticles, FilterDesktop,  OfflineVertexFitter
from Configurables import DaVinci
from Configurables import SubstitutePID

from Configurables import MCDecayTreeTuple
from Configurables import MCTupleToolReconstructed, MCReconstructed
from Configurables import DecayTreeTuple

####################### run setting 
doTest = False
if doTest:
    simulation = True
    year = "2012"
    polarity = -1
#################################
    
TrackCut = "(TRCHI2DOF < 4.0) & (MIPCHI2DV(PRIMARY)>2) & (TRGHOSTPROB < 0.4) & (PT > 200*MeV) & (ISLONG)"
DaughtCutPi = TrackCut + " &  (PROBNNpi>0.01)"
DaughtCutKa = TrackCut + " &  (PROBNNk>0.05)"
DaughtCutPr = TrackCut + " &  (PROBNNp>0.05)"


pionsLong = DataOnDemand(Location = "Phys/StdAllNoPIDsPions/Particles")
pionsDown = DataOnDemand(Location = "Phys/StdNoPIDsDownPions/Particles")
pions = DataOnDemand(Location = "Phys/StdNoPIDsPions/Particles")
kaons = DataOnDemand(Location = "Phys/StdNoPIDsKaons/Particles")
protons = DataOnDemand(Location = "Phys/StdNoPIDsProtons/Particles")
kshortLL = DataOnDemand(Location = "Phys/StdLooseKsLL/Particles")
kshortDD = DataOnDemand(Location = "Phys/StdLooseKsDD/Particles")
kshortLD = DataOnDemand(Location = "Phys/StdLooseKsLD/Particles")
LambdaDD = DataOnDemand(Location = "Phys/StdLooseLambdaDD/Particles")
LambdaLL = DataOnDemand(Location = "Phys/StdLooseLambdaLL/Particles")

rootInTes = '/Event/Bhadron'
locationXb2LcKpi   = "Phys/X2LcKPiOSLc2PKPiBeauty2CharmLine/Particles"
locationXb2LcKpi_ws   = "Phys/X2LcPiKOSLc2PKPiBeauty2CharmLine/Particles"
if simulation:
    locationXb2LcKpi = "/Event/AllStreams/Phys/X2LcKPiOSLc2PKPiBeauty2CharmLine/Particles"
    locationXb2LcKpi_ws = "/Event/AllStreams/Phys/X2LcPiKOSLc2PKPiBeauty2CharmLine/Particles"
Xb2LcKpi = AutomaticData(Location = locationXb2LcKpi)
Xb2LcKpi_ws = AutomaticData(Location = locationXb2LcKpi_ws)


selCode = "(MINTREE('K-'==ABSID,PROBNNk)>0.1)&(MINTREE('p+'==ABSID,PROBNNp)>0.1)&(MINTREE('pi-'==ABSID,PROBNNpi)>0.05)&(MINTREE('Lambda_c+'==ABSID, M)>2235*MeV)&(MAXTREE('Lambda_c+'==ABSID, M)<2335*MeV) & (M>5500*MeV) & (BPVIPCHI2()<16)"
#selCode ="(MINTREE('K-'==ABSID,PROBNNk)>0.05)&(MINTREE('p+'==ABSID,PROBNNp)>0.05)"
_MyX2LcKFilt = FilterDesktop('_MyX2LcKFilt', Code=selCode )
MyX2LcK = Selection("MyX2LcK", Algorithm = _MyX2LcKFilt, RequiredSelections = [Xb2LcKpi] )


# similar for wrong sign
_MyX2LcK_wsFilt = FilterDesktop('_MyX2LcK_wsFilt', Code=selCode )
MyX2LcK_ws = Selection("MyX2LcK_ws", Algorithm = _MyX2LcK_wsFilt, RequiredSelections = [Xb2LcKpi_ws] )

# ---------------------------------
# Now, the final selection sequence
# ----------------------------------
SelSeqMyX2LcK = SelectionSequence('SelSeqMyX2LcK', TopSelection = MyX2LcK)
seqMyX2LcK = SelSeqMyX2LcK.sequence()

SelSeqMyX2LcK_ws = SelectionSequence('SelSeqMyX2LcK_ws', TopSelection = MyX2LcK_ws)
seqMyX2LcK_ws = SelSeqMyX2LcK_ws.sequence()

# --------------------------------------------------------------------------
# Configure DaVinci
# -------------------------------------------------------------------------
# from Configurables import DaVinci
# from Configurables import  OfflineVertexFitter

importOptions("DecayTreeTuple_Xibc.py")

# right-sign
tupleMyXb0 = DecayTreeTuple("MyXb0")
tupleMyXb0.Inputs = [SelSeqMyX2LcK.outputLocation()]
# wrong-sign
tupleMyXb0_ws = DecayTreeTuple("MyXb0_ws")
tupleMyXb0_ws.Inputs = [SelSeqMyX2LcK_ws.outputLocation()]

from Configurables import CondDB

# Add a filter on the Stripping Lines
from PhysConf.Filters import LoKi_Filters

fltrs = LoKi_Filters(STRIP_Code=" HLT_PASS_RE('StrippingX2LcKPiOSLc2PKPiBeauty2CharmLineDecision') ")
fltrSeq = fltrs.sequence('MyFilters')

fltrs_ws = LoKi_Filters(STRIP_Code=" HLT_PASS_RE('StrippingX2LcPiKOSLc2PKPiBeauty2CharmLineDecision') ")
fltrSeq_ws = fltrs.sequence('MyFilters_ws')

from Configurables import LoKi__HDRFilter   as StripFilter


if simulation:
    tupleMyXb0.ToolList += ["TupleToolMCTruth"]
    tupleMyXb0_ws.ToolList += ["TupleToolMCTruth"]
    tupleMyXb0.ToolList += ["TupleToolMCBackgroundInfo"]
    tupleMyXb0_ws.ToolList += ["TupleToolMCBackgroundInfo"]

    # MC Truth information - filled for ALL events
    decay = "[ Lambda_b0 => ^(Lambda_c+ ==> ^p+ ^K- ^pi+) ^K- ^pi+]CC"
    mcTuple = MCDecayTreeTuple("MCTupleXb2LcKpi")
    mcTuple.Decay = decay
    mcTuple.ToolList = ["MCTupleToolKinematic", "MCTupleToolReconstructed"]
    mcTuple.UseLabXSyntax = True
    mcTuple.RevertToPositiveID = False

# Gaudi sequences

gseqMyXb0 = GaudiSequencer("MyGaudiSeqMyXb0")
#if simulation == False:
#    gseqMyXb0.Members += [fltrSeq]
gseqMyXb0.Members += [seqMyX2LcK]
gseqMyXb0.Members += [tupleMyXb0]

wsgseqMyXb0 = GaudiSequencer("MyGaudiSeqMyXb0_ws")
#if simulation == False:
#    wsgseqMyXb0.Members += [fltrSeq_ws]
wsgseqMyXb0.Members += [seqMyX2LcK_ws]
wsgseqMyXb0.Members += [tupleMyXb0_ws]

#DaVinci().appendToMainSequence( [gseqMyXb0] )
DaVinci().appendToMainSequence([gseqMyXb0, wsgseqMyXb0])
#if simulation == False:
#    DaVinci().appendToMainSequence([wsgseqMyXb0])                                                                                                                                                                                                                  
if simulation:
    DaVinci().appendToMainSequence([mcTuple])

#
from Configurables import CondDB

#
DaVinci().EvtMax = -1
DaVinci().DataType = year
DaVinci().TupleFile = "tuple.root"
DaVinci().PrintFreq = 2000

if simulation:
    sim08_CondDB = "Sim08-20130503-1-vc-"  # md100"
    sim09_CondDB = "sim-20160321-2-vc-"  # md100"
    sim08_DDDB = "Sim08-20130503-1"
    sim09_DDDB = "dddb-20150928"

    sim_DDDB = sim09_DDDB
    sim_CondDB = sim09_CondDB
    # sim_DDDB = sim08_DDDB
    # sim_CondDB = sim08_CondDB

    DaVinci().DDDBtag = sim_DDDB
    if polarity < 0: DaVinci().CondDBtag = sim_CondDB + "md100"
    if polarity > 0: DaVinci().CondDBtag = sim_CondDB + "mu100"
    DaVinci().Lumi = False
    DaVinci().Simulation = True
else:
    CondDB(LatestGlobalTagByDataType=year)
    DaVinci().Lumi = True
    from PhysConf.MicroDST import uDstConf

    uDstConf(rootInTes)
    DaVinci().InputType = 'MDST'
    DaVinci().RootInTES = rootInTes


if doTest:
    from GaudiConf import IOHelper
    #IOHelper().inputFiles(['/afs/cern.ch/work/s/sblusk//public/Xibc/LcKpi/00038996_00000020_2.AllStreams.dst'],clear=True)  #Xib -> Lc+ k+ pi- signal MC
    IOHelper().inputFiles(['/afs/cern.ch/work/s/sblusk//public/Xibc/LcKpi/00053263_00000001_2.AllStreams.dst'],clear=True)  #Xibc -> Lc+ k- pi+ signal MC



