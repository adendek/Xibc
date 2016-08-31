import GaudiKernel.SystemOfUnits as Units
from Gaudi.Configuration import *
from PhysSelPython.Wrappers import AutomaticData, DataOnDemand, Selection, SelectionSequence
from Configurables import  CombineParticles, FilterDesktop,  OfflineVertexFitter
from Configurables import DaVinci
from Configurables import SubstitutePID

from Configurables import MCDecayTreeTuple
from Configurables import MCTupleToolReconstructed, MCReconstructed

####################### run setting 
simulation = True
year = str(2012)
polarity = -1


#--Scaler----------------------------------------------------------------
from Configurables import TrackScaleState
scaler = TrackScaleState( 'StateScale' )
#------------------------------------------------------------------------

kaons        = DataOnDemand(Location = "Phys/StdAllNoPIDsKaons/Particles")
protons      = DataOnDemand(Location = "Phys/StdAllNoPIDsProtons/Particles")
longpions    = DataOnDemand(Location = "Phys/StdAllNoPIDsPions/Particles")

#-------------------------------------------------------------------------------------------------
locationB   = "/Event/BhadronCompleteEvent/Phys/Lb2LcKLc2PKPiBeauty2CharmLine/Particles"
if simulation:
    locationB = "/Event/AllStreams/Phys/Lb2LcKLc2PKPiBeauty2CharmLine/Particles"
Xb2LcK      = AutomaticData(Location = locationB)

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
               "NPionFromD0 = NINGENERATION(ABSID=='pi-', 2)",
               "NPim = NINGENERATION(ID=='pi-', 1)",
               "NPip = NINGENERATION(ID=='pi+', 1)",
               ]

# filter  [ Lambda_b0 -> (Lambda_c+ -> p+ ^K- pi+) K- ]CC",
selCode = "(MINTREE('K-'==ABSID,PROBNNk)>0.05)&(MINTREE('Lambda_b0'==ABSID, M)>2245*MeV)&(MAXTREE('Lambda_b0'==ABSID, M)<2325*MeV)"
_MyX2LcKFilt = FilterDesktop('_MyX2LcKFilt', Preambulo=myPreAmble, Code=selCode )
MyX2LcK = Selection("MyX2LcK", Algorithm = _MyX2LcKFilt, RequiredSelections = [Xb2LcK] )


# similar for wrong sign
locationBws   = "/Event/BhadronCompleteEvent/Phys/Lb2LcKWSLc2PKPiBeauty2CharmLine/Particles"
if simulation:
    locationBws = "/Event/AllStreams/Phys/Lb2LcKWSLc2PKPiBeauty2CharmLine/Particles"
Xb2LcK_ws      = AutomaticData(Location = locationBws)
_MyX2LcK_wsFilt = FilterDesktop('_MyX2LcK_wsFilt', Preambulo=myPreAmble, Code=selCode )
MyX2LcK_ws = Selection("MyX2LcK_ws", Algorithm = _MyX2LcK_wsFilt, RequiredSelections = [Xb2LcK_ws] )

# ---------------------------------
# Now, the final selection sequence
# ----------------------------------
SelSeqMyX2LcK = SelectionSequence('SelSeq'+'MyX2LcK', TopSelection = MyX2LcK)
seqMyX2LcK = SelSeqMyX2LcK.sequence()

SelSeqMyX2LcK_ws = SelectionSequence('SelSeq'+'MyX2LcK_ws', TopSelection = MyX2LcK_ws)
seqMyX2LcK_ws = SelSeqMyX2LcK_ws.sequence()


###########################################################################
# Configure DaVinci
###########################################################################
from Configurables import DaVinci
from Configurables import CondDB
from Configurables import  DecayTreeTuple, MCDecayTreeTuple
importOptions("DecayTreeTuple_Xibc.py")

from PhysConf.Filters import LoKi_Filters
fltrs = LoKi_Filters (STRIP_Code = " HLT_PASS_RE('Lb2LcKLc2PKPiBeauty2CharmLine') ")
fltrSeq = fltrs.sequence ( 'MyFilters' )

from Configurables import LoKi__HDRFilter   as StripFilter
if simulation == False:
    DaVinci().EventPreFilters = [fltrSeq]


tuple0  = DecayTreeTuple( "lambdab" )
tuple0.Inputs = [ MyX2LcK.outputLocation() ]
wstuple0  = DecayTreeTuple( "wsLambdab")
wstuple0.Inputs = [ MyX2LcK.outputLocation() ]

if simulation:
    tuple0.ToolList += [ "TupleToolMCTruth" ]

    # MC Truth information - filled for ALL events
    decay = "[Lambda_b0 -> ^(Lambda_c+ -> ^p+ ^K- ^pi+) ^K-]CC"
    mcTuple = MCDecayTreeTuple("MCTupleXb2D0p")
    mcTuple.Decay = decay
    mcTuple.ToolList = [ "MCTupleToolKinematic", "MCTupleToolReconstructed" ]
    mcTuple.UseLabXSyntax = True
    mcTuple.RevertToPositiveID = False

# ---------------
# Gaudi sequences
# ---------------
#MyX2D0pGauSeq = GaudiSequencer("MyX2D0pGauSeq")
#MyX2D0pGauSeq.Members += [scaler ]
#MyX2D0pGauSeq.Members += [seqMyX2D0p ]
#MyX2D0pGauSeq.Members += [ tuple0 ]

#MywsX2D0pGauSeq = GaudiSequencer("MywsX2D0pGauSeq")
#MywsX2D0pGauSeq.Members += [scaler ]
#MywsX2D0pGauSeq.Members += [seqMyX2D0p ]
#MywsX2D0pGauSeq.Members += [ tuple1 ]


#---------------------------------------------------------------

DaVinci().UserAlgorithms = [ scaler, seqMyX2LcK, tuple0, seqMyX2LcK_ws ,wstuple0 ]
if simulation:
    DaVinci().appendToMainSequence( [mcTuple] )

#
DaVinci().EvtMax     = -1
DaVinci().DataType   = year
DaVinci().TupleFile  = "tuple.root"
DaVinci().PrintFreq  = 2000

from Configurables import CondDB
if simulation:
    DaVinci().DDDBtag="Sim08-20130503-1"
    if polarity<0: DaVinci().CondDBtag="Sim08-20130503-1-vc-md100"
    if polarity>0: DaVinci().CondDBtag="Sim08-20130503-1-vc-mu100"
    DaVinci().Lumi       = False
    DaVinci().Simulation = True
else:
    CondDB( LatestGlobalTagByDataType = year )
    DaVinci().Lumi       = True
    DaVinci().InputType = 'DST'



