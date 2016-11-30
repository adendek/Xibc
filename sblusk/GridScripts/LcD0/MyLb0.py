#---------------------------------------------
# Author   : S Blusk
# Date     : Jan 2016
# Data     : Real Data
#---------------------------------------------
from Gaudi.Configuration import *
from Configurables import GaudiSequencer
from Configurables import  DecayTreeTuple, MCDecayTreeTuple, CheckPV
from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence, DataOnDemand
from Configurables import   CombineParticles, FilterDesktop,  OfflineVertexFitter
from Configurables import DaVinci
from Configurables import SubstitutePID

from Configurables import MCDecayTreeTuple
from Configurables import MCTupleToolReconstructed, MCReconstructed

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
locationX2LcD0   = "Phys/X2LcD0D02KPiBeauty2CharmLine/Particles"
if simulation:
    locationX2LcD0 = "/Event/AllStreams/Phys/X2LcD0D02KPiBeauty2CharmLine/Particles"
X2LcD0      = AutomaticData(Location = locationX2LcD0)

myPreAmble = [ "Z  = VFASPF(VZ)"   ,
               "DZ1 = CHILD(Z,1)-Z",
               "DZ2 = CHILD(Z,2)-Z",
               "VCHISQDOF = VFASPF(VCHI2/VDOF)",
               "MIPCHI2 = MIPCHI2DV(PRIMARY)",
               "MIP = MIPDV(PRIMARY)",
               "NKaon = NINGENERATION(ABSID=='K-', 1)",
               "NKaonFailPID = NINTREE( ((ABSID=='K+') & (PIDK<0) ) )",
               "NKaonFail = CHILD(NKaonFailPID, 2)",
               "NPion = NINGENERATION(ABSID=='pi-', 1)",
               "NPionInTree = NINTREE(ABSID=='pi-')",
               "NPim = NINGENERATION(ID=='pi-', 1)",
               "NPip = NINGENERATION(ID=='pi+', 1)",
               ]

#----------------------------------------------------
# Selection on parent particle
#----------------------------------------------------

#selCode = "M > 5000*MeV"
selCode = "(M > 5800*MeV) & (MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('p+'==ABSID,PROBNNp)>0.05)&(MINTREE('D0'==ABSID, M)>1815*MeV)&(MAXTREE('D0'==ABSID, M)<1915*MeV) & (MINTREE('Lambda_c+'==ABSID, M)>2245*MeV)&(MAXTREE('Lambda_c+'==ABSID, M)<2325*MeV)"
_X2LcD0Filt = FilterDesktop('_X2LcD0Filt', Preambulo=myPreAmble, Code=selCode )
sel_X2LcD0 = Selection("sel_X2LcD0", Algorithm = _X2LcD0Filt, RequiredSelections = [X2LcD0] )


### Gaudi sequences
SeqMyXb0 = SelectionSequence("SeqMyXb0", TopSelection = sel_X2LcD0)
seqMyXb0 = SeqMyXb0.sequence()


#--------------------------------------------------------------------------
# Configure DaVinci
#-------------------------------------------------------------------------
#from Configurables import DaVinci
#from Configurables import  OfflineVertexFitter

importOptions("MyXb0TupleTree.py")

# right-sign
tupleMyXb0 = DecayTreeTuple( "MyXb0" )
tupleMyXb0.Inputs = [ SeqMyXb0.outputLocation() ]
# wrong-sign
wstupleMyXb0 = DecayTreeTuple( "wsMyXb0" )
wstupleMyXb0.Inputs = [ SeqMyXb0.outputLocation() ]

from Configurables import CondDB


# Add a filter on the Stripping Lines
from PhysConf.Filters import LoKi_Filters

fltrs = LoKi_Filters (STRIP_Code = " HLT_PASS_RE('StrippingX2LcD0D02KPiBeauty2CharmLineDecision') ")
fltrSeq = fltrs.sequence ( 'MyFilters' )  


from Configurables import LoKi__HDRFilter   as StripFilter
if simulation == False:
    DaVinci().EventPreFilters = [fltrSeq]

if simulation:
    tupleMyXb0.ToolList += [ "TupleToolMCTruth" ]
    wstupleMyXb0.ToolList += [ "TupleToolMCTruth" ]
    tupleMyXb0.ToolList += [  "TupleToolMCBackgroundInfo"   ]
    wstupleMyXb0.ToolList += [ "TupleToolMCBackgroundInfo" ]


    # MC Truth information - filled for ALL events
    decay = "[Xi_bc+ => ^(Lambda_c+ ==> ^p+ ^K- ^pi+) ^(D0 => ^K- ^pi+) ]CC"
    mcTuple = MCDecayTreeTuple("MCTupleXb2LcD0")
    mcTuple.Decay = decay
    mcTuple.ToolList = [ "MCTupleToolKinematic", "MCTupleToolReconstructed" ] 
    mcTuple.UseLabXSyntax = True
    mcTuple.RevertToPositiveID = False

# Gaudi sequences
gseqMyXb0 =  GaudiSequencer("MyGaudiSeqMyXb0")
gseqMyXb0.Members += [seqMyXb0]
gseqMyXb0.Members += [tupleMyXb0]
wsgseqMyXb0 =  GaudiSequencer("wsMyGaudiSeqMyXb0")
wsgseqMyXb0.Members += [seqMyXb0]
wsgseqMyXb0.Members += [wstupleMyXb0]

    
#DaVinci().appendToMainSequence( [gseqMyXb0] )
DaVinci().appendToMainSequence( [gseqMyXb0, wsgseqMyXb0] )
if simulation:
    DaVinci().appendToMainSequence( [mcTuple] )

#
from Configurables import CondDB
#
DaVinci().EvtMax     = -1
DaVinci().DataType   = year
DaVinci().TupleFile  = "tuple.root"
DaVinci().PrintFreq  = 2000


if simulation:
    sim08_CondDB = "Sim08-20130503-1-vc-" #md100"
    sim09_CondDB = "sim-20160321-2-vc-" #md100"
    sim08_DDDB = "Sim08-20130503-1"
    sim09_DDDB = "dddb-20150928"

    sim_DDDB = sim09_DDDB
    sim_CondDB = sim09_CondDB 
    #sim_DDDB = sim08_DDDB
    #sim_CondDB = sim08_CondDB 

    DaVinci().DDDBtag = sim_DDDB
    if polarity<0: DaVinci().CondDBtag = sim_CondDB+"md100"
    if polarity>0: DaVinci().CondDBtag = sim_CondDB+"mu100"
    DaVinci().Lumi       = False
    DaVinci().Simulation = True
else:
    CondDB( LatestGlobalTagByDataType = year )
    DaVinci().Lumi       = True
    from PhysConf.MicroDST import uDstConf
    uDstConf ( rootInTes )
    DaVinci().InputType = 'MDST'
    DaVinci().RootInTES = rootInTes



#from GaudiConf import IOHelper
#IOHelper().inputFiles([
#'/afs/cern.ch/user/l/lzhang/00020198_00001115_1.dimuon.dst'
#], clear=True)

