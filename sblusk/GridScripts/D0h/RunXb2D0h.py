import GaudiKernel.SystemOfUnits as Units
from Gaudi.Configuration import *
from PhysSelPython.Wrappers import AutomaticData, DataOnDemand, Selection, SelectionSequence
from Configurables import  CombineParticles, FilterDesktop,  OfflineVertexFitter
from Configurables import DaVinci
from Configurables import SubstitutePID

from Configurables import MCDecayTreeTuple
from Configurables import MCTupleToolReconstructed, MCReconstructed
from Configurables import BackgroundCategory

doTest = True
if doTest:
    simulation = False
    polarity = -1
    year = "2012"


def createDTFInput(inputSel, outputCont):
    algName = 'SubPID_'+outputCont
    Sub = SubstitutePID ( algName ) #Code = "DECTREE('[Beauty -> Charm X- ]CC')" )

    Sub.Code = "DECTREE( '[(Beauty -> D0 pi-), (Beauty -> D0 pi+)]' )" 
    Sub.MaxChi2PerDoF = -666
    Sub.Substitutions = {' Beauty -> D0 ^pi-  ' : 'p~-',
                         ' Beauty -> D0 ^pi+  ' : 'p+'
                         }
    Sub.Inputs = [inputSel.outputLocation()]
    return Sub


#--Scaler----------------------------------------------------------------
from Configurables import TrackScaleState
scaler = TrackScaleState( 'StateScale' )
#------------------------------------------------------------------------

kaons        = DataOnDemand(Location = "Phys/StdAllNoPIDsKaons/Particles")
protons      = DataOnDemand(Location = "Phys/StdAllNoPIDsProtons/Particles")
longpions    = DataOnDemand(Location = "Phys/StdAllNoPIDsPions/Particles")

#-------------------------------------------------------------------------------------------------
locationB   = "/Event/BhadronCompleteEvent/Phys/B2D0PiD2HHBeauty2CharmLine/Particles"
locationBk   = "/Event/BhadronCompleteEvent/Phys/B2D0KD2HHBeauty2CharmLine/Particles"
if simulation:
    locationB = "/Event/AllStreams/Phys/B2D0PiD2HHBeauty2CharmLine/Particles"
B2D0h      = AutomaticData(Location = locationB)
B2D0pi      = AutomaticData(Location = locationB)

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

# First filter the B- --> (D0 -> K+- pi-+) pi- candidates
selCode = "(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('D0'==ABSID, M)>1815*MeV)&(MAXTREE('D0'==ABSID, M)<1915*MeV) & (NPionFromD0==1)"
selCode2 = "(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('pi+'==ABSID,PROBNNpi)>0.05)&(MINTREE('D0'==ABSID, M)>1815*MeV)&(MAXTREE('D0'==ABSID, M)<1915*MeV) & (NPionFromD0==1) & (M>5000*MeV) & (M<6000*MeV) & (BPVDIRA>0.9999)"
#selCode = "(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('D0'==ABSID, M)>1815*MeV)&(MAXTREE('D0'==ABSID, M)<1915*MeV)"
_MyX2D0piFilt = FilterDesktop('_MyX2D0piFilt', Preambulo=myPreAmble, Code=selCode )
_MyX2DpiFilt = FilterDesktop('_MyX2D0piFilt', Preambulo=myPreAmble, Code=selCode2 )
MyX2D0pi = Selection("MyX2D0pi", Algorithm = _MyX2D0piFilt, RequiredSelections = [B2D0h] )
MyX2D0pion = Selection("MyX2D0pion", Algorithm = _MyX2D0piFilt, RequiredSelections = [B2D0pi] )
#-------------------------------------------------------------------------------------------------
# Now, do the mass swap on the pion --> proton
# --------------------------------------------
outputCont = "MyX2D0p"
outputCont2 = "MyX2D0pi"
subpid = createDTFInput(MyX2D0pi,outputCont)
particleSwap = Selection( "particleSwap_"+outputCont, Algorithm = subpid, RequiredSelections=[MyX2D0pi])
# ------------------------------------------------------------
# Finally, make some selections on this new decay, X --> D0 p.
# ------------------------------------------------------------
selCode2 = "(MINTREE('p+'==ABSID,PROBNNp)>0.1)&(M>4000*MeV)&(M<12000*MeV)"
_MyX2D0pFilt = FilterDesktop('_MyX2D0pFilt', Preambulo=myPreAmble, Code=selCode2 )
MyX2D0p = Selection("MyX2D0p", Algorithm = _MyX2D0pFilt, RequiredSelections = [particleSwap] )
# ---------------------------------
# Now, the final selection sequence
# ----------------------------------
SelSeqMyX2D0p = SelectionSequence('SelSeq'+outputCont, TopSelection = MyX2D0p)
seqMyX2D0p = SelSeqMyX2D0p.sequence()
# Control channel (B --> D0 K)
SelSeqMyX2D0pi = SelectionSequence('SelSeq'+outputCont2, TopSelection = MyX2D0pion)
seqMyX2D0pi = SelSeqMyX2D0pi.sequence()



###########################################################################
# Configure DaVinci
###########################################################################
from Configurables import DaVinci
from Configurables import CondDB
from Configurables import  DecayTreeTuple, MCDecayTreeTuple
importOptions("DecayTreeTuple_Xibc.py")

from PhysConf.Filters import LoKi_Filters
fltrs = LoKi_Filters (STRIP_Code = " HLT_PASS_RE('StrippingB2D0PiD2HHBeauty2CharmLineDecision') ")
fltrSeq = fltrs.sequence ( 'MyFilters' )  

from Configurables import LoKi__HDRFilter   as StripFilter
if simulation == False:
    DaVinci().EventPreFilters = [fltrSeq]


tuple0  = DecayTreeTuple( "Xibc2D0p" )
tuple0.Inputs = [ SelSeqMyX2D0p.outputLocation() ]
tuplepi  = DecayTreeTuple( "B2D0pi" )
tuplepi.Inputs = [ SelSeqMyX2D0pi.outputLocation() ]
wstuple0  = DecayTreeTuple( "wsXibc2D0p")
wstuple0.Inputs = [ SelSeqMyX2D0p.outputLocation() ]

if simulation:
    tuple0.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    wstuple0.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    tuplepi.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]

    # MC Truth information - filled for ALL events
    decay = "[Xi_bc+ => ^(D0 => ^K- ^pi+) ^p+]CC"
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

DaVinci().UserAlgorithms = [ scaler, seqMyX2D0p, seqMyX2D0pi, tuple0, wstuple0, tuplepi]
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

if doTest:
    from GaudiConf import IOHelper
    IOHelper().inputFiles([
        '/afs/cern.ch/work/s/sblusk/00041836_00000335_1.bhadroncompleteevent.dst'
        ], clear=True)

#




