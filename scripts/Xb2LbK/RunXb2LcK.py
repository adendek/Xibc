import GaudiKernel.SystemOfUnits as Units
from Gaudi.Configuration import *
from PhysSelPython.Wrappers import AutomaticData, DataOnDemand, Selection, SelectionSequence
from Configurables import  CombineParticles, FilterDesktop,  OfflineVertexFitter
from Configurables import DaVinci


#--Scaler----------------------------------------------------------------
from Configurables import TrackScaleState
scaler = TrackScaleState( 'StateScale' )
#------------------------------------------------------------------------


kaons        = DataOnDemand(Location = "Phys/StdAllNoPIDsKaons/Particles")
protons      = DataOnDemand(Location = "Phys/StdAllNoPIDsProtons/Particles")
longpions    = DataOnDemand(Location = "Phys/StdAllNoPIDsPions/Particles")



#-------------------------------------------------------------------------------------------------
locationLb   = "/Event/BhadronCompleteEvent/Phys/Phys/Lb2LcKLc2PKPiBeauty2CharmLine/Particles"
if simulation:
    locationLb = "/Event/AllStreams/Phys/Lb2LcKLc2PKPiBeauty2CharmLine/Particles"
Lb2LcK      = AutomaticData(Location = locationLb)

_MyXb2XcK = FilterDesktop('_MyXb2XcK')
_MyXb2XcK.Code = "(MAXTREE('p+'==ABSID,PROBNNp)>0.1)&(MAXTREE('K+'==ABSID,PROBNNk)>0.05)&(MAXTREE('Lambda_b0'==ABSID,M)>5350*MeV)&(MAXTREE('Lambda_b0'==ABSID,M)<6000*MeV)&(MAXTREE('Lambda_c+'==ABSID, M)>2260*MeV)&(MAXTREE('Lambda_c+'==ABSID, M)<2315*MeV)"
MyLb2Lcpi = Selection("MyLb2Lcpi", Algorithm = _MyXb2XcK, RequiredSelections = [Lb2LcK] )
#-------------------------------------------------------------------------------------------------


#BPVVDCHI2: chi2 separation from related PV
#BPVIPCHI2(): Computes the chi2-IP on the related PV


#----Selection Xibb -> /\b pi+/-----------------------------------------------------------------
_Sigb2Lbpi = CombineParticles( "_Sigb2Lbpi",
                              DecayDescriptors = ["[Xi_bc+ -> Lambda_b0 pi+]cc"],
                              CombinationCut   = "(AM-AM1-AM2>450*MeV) & (APT>2*GeV)",
                              DaughtersCuts    = { "pi+"      : "(PT > 200*MeV) & (P > 2000*MeV) & (TRCHI2DOF < 4.0) & (MIPCHI2DV(PRIMARY)>4)"},
                              MotherCut        = "(M-M1-M2>500*MeV) & (PT>1*GeV) & (VFASPF(VCHI2/VDOF)<10) & (MIPCHI2DV(PRIMARY)<16)",
                              ReFitPVs         = True )
Sigb2Lbpi  = Selection( "Sigb2Lbpi ",
                      Algorithm          = _Sigb2Lbpi ,
                      RequiredSelections = [ MyLb2Lcpi,  longpions] )

_wsSigb2Lbpi = CombineParticles( "_wsSigb2Lbpi",
                              DecayDescriptors = ["[Xi_bc+ -> Lambda_b~0 pi+]cc"],
                              CombinationCut   = "(AM-AM1-AM2>450*MeV) & (APT>2*GeV)",
                              DaughtersCuts    = { "pi+"      : "(PT > 200*MeV) & (P > 2000*MeV) & (TRCHI2DOF < 4.0) & (MIPCHI2DV(PRIMARY)>4)"},
                              MotherCut        = "(M-M1-M2>500*MeV) & (PT>1*GeV) & (VFASPF(VCHI2/VDOF)<10) & (MIPCHI2DV(PRIMARY)<16)",
                              ReFitPVs         = True )
wsSigb2Lbpi  = Selection( "wsSigb2Lbpi ",
                      Algorithm          = _wsSigb2Lbpi ,
                      RequiredSelections = [ MyLb2Lcpi,  longpions] )


#-------------------------------------------------------------------------------------------------


### Gaudi sequences ----------------------------------------------
SeqLb2Lcpi = SelectionSequence("SeqLb2Lcpi", TopSelection = MyLb2Lcpi)
seqLb = SeqLb2Lcpi.sequence()
SeqSigb2Lbpi = SelectionSequence("SeqSigb2Lbpi", TopSelection = Sigb2Lbpi)
seqXib = SeqSigb2Lbpi.sequence()
wsSeqSigb2Lbpi = SelectionSequence("wsSeqSigb2Lbpi", TopSelection = wsSigb2Lbpi)
wsseqXib = wsSeqSigb2Lbpi.sequence()
#---------------------------------------------------------------



###########################################################################
# Configure DaVinci
###########################################################################
from Configurables import DaVinci
from Configurables import CondDB
from Configurables import  DecayTreeTuple, MCDecayTreeTuple
importOptions("DecayTreeTuple_Xibc.py")

from PhysConf.Filters import LoKi_Filters
fltrs = LoKi_Filters (STRIP_Code = " HLT_PASS_RE('StrippingLb2LcPiNoIPLc2PKPiBeauty2CharmLineDecision') ")
fltrSeq = fltrs.sequence ( 'MyFilters' )

from Configurables import LoKi__HDRFilter   as StripFilter
if simulation == False:
    DaVinci().EventPreFilters = [fltrSeq]


tuple0  = DecayTreeTuple( "xibc" )
tuple0.Inputs = [ SeqSigb2Lbpi.outputLocation() ]
tuple1  = DecayTreeTuple( "wsxibc")
tuple1.Inputs = [ wsSeqSigb2Lbpi.outputLocation() ]
tupleLb = DecayTreeTuple( "lambdab" )
tupleLb.Inputs = [ SeqLb2Lcpi.outputLocation() ]


if simulation:
    tuple0.ToolList += [ "TupleToolMCTruth" ]
    tuple1.ToolList += [ "TupleToolMCTruth" ]
    tupleLb.ToolList += [ "TupleToolMCTruth" ]



#DaVinci().appendToMainSequence( [scaler] )
DaVinci().UserAlgorithms = [ scaler, seqLb, seqXib, wsseqXib, tuple0, tuple1, tupleLb]

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

#




