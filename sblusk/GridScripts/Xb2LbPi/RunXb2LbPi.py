import GaudiKernel.SystemOfUnits as Units
from Gaudi.Configuration import *
from PhysSelPython.Wrappers import AutomaticData, DataOnDemand, Selection, SelectionSequence
from Configurables import  CombineParticles, FilterDesktop,  OfflineVertexFitter
from Configurables import DaVinci

from Configurables import MCDecayTreeTuple
from Configurables import MCTupleToolReconstructed, MCReconstructed

#--Scaler----------------------------------------------------------------
from Configurables import TrackScaleState
scaler = TrackScaleState( 'StateScale' )
#------------------------------------------------------------------------


kaons        = DataOnDemand(Location = "Phys/StdAllNoPIDsKaons/Particles")
protons      = DataOnDemand(Location = "Phys/StdAllNoPIDsProtons/Particles")
longpions    = DataOnDemand(Location = "Phys/StdAllNoPIDsPions/Particles")



#-------------------------------------------------------------------------------------------------
locationLb   = "/Event/BhadronCompleteEvent/Phys/Lb2LcPiNoIPLc2PKPiBeauty2CharmLine/Particles"
if simulation:
    locationLb = "/Event/AllStreams/Phys/Lb2LcPiNoIPLc2PKPiBeauty2CharmLine/Particles"
Lb2Lcpi      = AutomaticData(Location = locationLb)

_MyLb2Lcpi = FilterDesktop('_MyLb2Lcpi')
_MyLb2Lcpi.Code = "(MAXTREE('p+'==ABSID,PROBNNp)>0.05)&(MAXTREE('K+'==ABSID,PROBNNk)>0.05)&(MAXTREE('Lambda_b0'==ABSID,M)>5350*MeV)&(MAXTREE('Lambda_b0'==ABSID,M)<6000*MeV)&(MAXTREE('Lambda_c+'==ABSID, M)>2260*MeV)&(MAXTREE('Lambda_c+'==ABSID, M)<2315*MeV)"
MyLb2Lcpi = Selection("MyLb2Lcpi", Algorithm = _MyLb2Lcpi, RequiredSelections = [Lb2Lcpi] )
#-------------------------------------------------------------------------------------------------


#BPVVDCHI2: chi2 separation from related PV 
#BPVIPCHI2(): Computes the chi2-IP on the related PV 


#----Selection Xibb -> /\b pi+/-----------------------------------------------------------------
_Sigb2Lbpi = CombineParticles( "_Sigb2Lbpi",
                              DecayDescriptors = ["[Xi_bc+ -> Lambda_b0 pi+]cc"],
                              CombinationCut   = "(AM>5800*MeV) & (APT>2*GeV)",
                              DaughtersCuts    = { "pi+"      : "(PT > 200*MeV) & (P > 2000*MeV) & (TRCHI2DOF < 4.0) & (MIPCHI2DV(PRIMARY)>4)"},
                              MotherCut        = "(VFASPF(VCHI2/VDOF)<10) & (MIPCHI2DV(PRIMARY)<16) & (BPVDIRA>0.999) & (BPVVDCHI2>16)", 
                              ReFitPVs         = True )
Sigb2Lbpi  = Selection( "Sigb2Lbpi ",
                      Algorithm          = _Sigb2Lbpi ,
                      RequiredSelections = [ MyLb2Lcpi,  longpions] )

_wsSigb2Lbpi = CombineParticles( "_wsSigb2Lbpi",
                              DecayDescriptors = ["[Xi_bc+ -> Lambda_b~0 pi+]cc"],
                              CombinationCut   = "(AM>5800*MeV) & (APT>2*GeV)",
                              DaughtersCuts    = { "pi+"      : "(PT > 200*MeV) & (P > 2000*MeV) & (TRCHI2DOF < 4.0) & (MIPCHI2DV(PRIMARY)>4)"},
                              MotherCut        = "(VFASPF(VCHI2/VDOF)<10) & (MIPCHI2DV(PRIMARY)<16) & (BPVDIRA>0.999) & (BPVVDCHI2>16)", 
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
    tuple0.ToolList += [  "TupleToolMCBackgroundInfo"   ]
    tupleLb.ToolList += [ "TupleToolMCTruth" ]
    tupleLb.ToolList += [  "TupleToolMCBackgroundInfo"   ]
        

    # MC Truth information - filled for ALL events
    decay1 = "[Xi_bc+ => ^(Lambda_b0 => ^pi- ^(Lambda_c+ ==> ^p+ ^K- ^pi+) ) ^pi+]CC"
    mcTuple1 = MCDecayTreeTuple("MCTupleXb2LbPi")
    mcTuple1.Decay = decay1
    mcTuple1.ToolList = [ "MCTupleToolKinematic", "MCTupleToolReconstructed" ] 
    mcTuple1.UseLabXSyntax = True
    mcTuple1.RevertToPositiveID = False   



#DaVinci().appendToMainSequence( [scaler] )
DaVinci().appendToMainSequence( [seqLb, seqXib, wsseqXib, tuple0, tuple1, tupleLb] )
if simulation:
    DaVinci().appendToMainSequence( [mcTuple1] )

#
DaVinci().EvtMax     = -1
DaVinci().DataType   = year
DaVinci().TupleFile  = "tuple.root"
DaVinci().PrintFreq  = 2000

from Configurables import CondDB
if simulation:
    sim08_CondDB = "Sim08-20130503-1-vc-" #md100"
    sim09_CondDB = "sim-20160321-2-vc-" #md100"
    sim08_DDDB = "Sim08-20130503-1"
    sim09_DDDB = "dddb-20150928"

    sim_DDDB = sim09_DDDB
    sim_CondDB = sim09_CondDB 
    DaVinci().DDDBtag = sim_DDDB
    if polarity<0: DaVinci().CondDBtag = sim_CondDB+"md100"
    if polarity>0: DaVinci().CondDBtag = sim_CondDB+"mu100"
    DaVinci().Lumi       = False
    DaVinci().Simulation = True
else:
    CondDB( LatestGlobalTagByDataType = year )
    DaVinci().Lumi       = True
    DaVinci().InputType = 'DST'

#




