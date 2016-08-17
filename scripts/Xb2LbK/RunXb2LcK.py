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
pions    = DataOnDemand(Location = "Phys/StdAllNoPIDsPions/Particles")

#----Selection Xibb -> /\b pi+/-----------------------------------------------------------------
_Sigb2LcK = CombineParticles( "_Sigb2LcK",
                              DecayDescriptors = ["[ Xi_bc+ -> ^K- ^(Lambda_c+ -> ^p+ ^K- ^pi+) ]CC"],
                              CombinationCut   = "(AM-AM1-AM2>450*MeV) & (APT>2*GeV)",
                              DaughtersCuts    = { "K-"      : "(PT > 200*MeV) & (P > 2000*MeV) & (TRCHI2DOF < 4.0) & (MIPCHI2DV(PRIMARY)>4)"},
                              MotherCut        = "(M-M1-M2>500*MeV) & (PT>1*GeV) & (VFASPF(VCHI2/VDOF)<10) & (MIPCHI2DV(PRIMARY)<16)", 
                              ReFitPVs         = True )
Sigb2Lbpi  = Selection( "Sigb2Lbpi ",
                      Algorithm          = _Sigb2LcK ,
                      RequiredSelections = [ MyLb2LbK,  kaons] )


#-------------------------------------------------------------------------------------------------


### Gaudi sequences ----------------------------------------------
SeqSigb2LcK = SelectionSequence("SeqSigb2LcK", TopSelection = MyLb2LbK)
seqXib = SeqSigb2LcK.sequence()
#---------------------------------------------------------------



###########################################################################
# Configure DaVinci
###########################################################################
from Configurables import DaVinci
from Configurables import CondDB
from Configurables import  DecayTreeTuple, MCDecayTreeTuple
importOptions("DecayTreeTuple_Xibc.py")

from PhysConf.Filters import LoKi_Filters
fltrs = LoKi_Filters (STRIP_Code = " HLT_PASS_RE('StrippingLb2LcKLc2PKPiBeauty2CharmLine') ")
fltrSeq = fltrs.sequence ( 'MyFilters' )  

from Configurables import LoKi__HDRFilter   as StripFilter
if simulation == False:
    DaVinci().EventPreFilters = [fltrSeq]


tuple0  = DecayTreeTuple( "xibc" )
tuple0.Inputs = [ SeqSigb2LcK.outputLocation() ]


if simulation:
    tuple0.ToolList += [ "TupleToolMCTruth" ]



#DaVinci().appendToMainSequence( [scaler] )
DaVinci().UserAlgorithms = [ scaler, seqXib, tuple0]

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




