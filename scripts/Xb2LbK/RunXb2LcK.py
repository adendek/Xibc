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
simulation = True
year = str(2012)
polarity = -1


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
locationXb2LcK   = "Phys/Lb2LcKLc2PKPiBeauty2CharmLine/Particles"
if simulation:
    locationXb2LcK = "/Event/AllStreams/Phys/Lb2LcKLc2PKPiBeauty2CharmLine/Particles"
Xb2LcK = AutomaticData(Location = locationXb2LcK)


selCode = "(MINTREE('K-'==ABSID,PROBNNk)>0.05)&(MINTREE('Lambda_b0'==ABSID, M)>2245*MeV)&(MAXTREE('Lambda_b0'==ABSID, M)<2325*MeV)"
_MyX2LcKFilt = FilterDesktop('_MyX2LcKFilt', Code=selCode )
MyX2LcK = Selection("MyX2LcK", Algorithm = _MyX2LcKFilt, RequiredSelections = [Xb2LcK] )


# similar for wrong sign
locationXb2LcK_ws   = "Phys/Lb2LcKWSLc2PKPiBeauty2CharmLine/Particles"
if simulation:
    locationXb2LcK_ws = "/Event/AllStreams/Phys/Lb2LcKWSLc2PKPiBeauty2CharmLine/Particles"
Xb2LcK_ws      = AutomaticData(Location = locationXb2LcK_ws)
_MyX2LcK_wsFilt = FilterDesktop('_MyX2LcK_wsFilt', Code=selCode )
MyX2LcK_ws = Selection("MyX2LcK_ws", Algorithm = _MyX2LcK_wsFilt, RequiredSelections = [Xb2LcK_ws] )

# ---------------------------------
# Now, the final selection sequence
# ----------------------------------
SelSeqMyX2LcK = SelectionSequence('SelSeq'+'MyX2LcK', TopSelection = MyX2LcK)
seqMyX2LcK = SelSeqMyX2LcK.sequence()

SelSeqMyX2LcK_ws = SelectionSequence('SelSeq'+'MyX2LcK_ws', TopSelection = MyX2LcK_ws)
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

fltrs = LoKi_Filters(STRIP_Code=" HLT_PASS_RE('StrippingLb2LcKLc2PKPiBeauty2CharmLineDecision') ")
fltrSeq = fltrs.sequence('MyFilters')

fltrs_ws = LoKi_Filters(STRIP_Code=" HLT_PASS_RE('StrippingLb2LcKWSLc2PKPiBeauty2CharmLineDecision') ")
fltrSeq_ws = fltrs.sequence('MyFilters_ws')




from Configurables import LoKi__HDRFilter   as StripFilter


if simulation:
    tupleMyXb0.ToolList += ["TupleToolMCTruth"]
    tupleMyXb0_ws.ToolList += ["TupleToolMCTruth"]
    tupleMyXb0.ToolList += ["TupleToolMCBackgroundInfo"]
    tupleMyXb0_ws.ToolList += ["TupleToolMCBackgroundInfo"]

    # MC Truth information - filled for ALL events
    decay = "[ Lambda_b0 -> ^(Lambda_c+ -> ^p+ ^K- ^pi+) ^K- ]CC"
    mcTuple = MCDecayTreeTuple("MCTupleXb2LcK")
    mcTuple.Decay = decay
    mcTuple.ToolList = ["MCTupleToolKinematic", "MCTupleToolReconstructed"]
    mcTuple.UseLabXSyntax = True
    mcTuple.RevertToPositiveID = False

# Gaudi sequences

gseqMyXb0 = GaudiSequencer("MyGaudiSeqMyXb0")
if simulation == False:
    gseqMyXb0.Members += [fltrSeq]
gseqMyXb0.Members += [seqMyX2LcK]
gseqMyXb0.Members += [tupleMyXb0]

wsgseqMyXb0 = GaudiSequencer("MyGaudiSeqMyXb0_ws")
if simulation == False:
    gseqMyXb0.Members += [fltrSeq_ws]
wsgseqMyXb0.Members += [seqMyX2LcK_ws]
wsgseqMyXb0.Members += [tupleMyXb0_ws]

# DaVinci().appendToMainSequence( [gseqMyXb0] )
DaVinci().appendToMainSequence([gseqMyXb0, wsgseqMyXb0])
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
