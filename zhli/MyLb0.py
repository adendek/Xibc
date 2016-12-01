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


# Test                                                                                                                                                                                   
doTest = False
if doTest:
    simulation = False
    polarity = -1
    year = "2012"
 
if doTest:
    from GaudiConf import IOHelper
    IOHelper().inputFiles([
        '/afs/cern.ch/work/z/zhli/Work/00053247_00000003_2.AllStreams.dst'
                ], clear=True)

#-----------Swap Lambda0 -> Sigma0
def createDTFInput(inputSel, outputCont):
    algName = 'SubPID_'+outputCont
    Sub = SubstitutePID ( algName ) 

    Sub.Code = "DECTREE( ' Lambda_b0 -> D0 Lambda0 ' )" 
    Sub.MaxChi2PerDoF = -666
    Sub.Substitutions = {' Lambda_b0 -> D0 ^Lambda0  ' : 'Sigma0',
                         }
    Sub.Inputs = [inputSel.outputLocation()]
    return Sub

#----selection p+ and K- -------------------------
#pions = DataOnDemand(Location = "/Event/Phys/StdNoPIDsPions/Particles")
#kaons = DataOnDemand(Location = "/Event/Phys/StdNoPIDsKaons/Particles")
#protons = DataOnDemand(Location = "/Event/Phys/StdNoPIDsProtons/Particles")
#kshortLL = DataOnDemand(Location = "/Event/Phys/StdLooseKsLL/Particles")
#kshortDD = DataOnDemand(Location = "/Event/Phys/StdLooseKsDD/Particles")

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

#locationLambdab0   = "/Event/Bhadron/Phys/Lb2D0PHD02HHBeauty2CharmLine/Particles"
if simulation:
    locationLambdab0 = "/Event/AllStreams/Phys/Lb2D0PHD02HHBeauty2CharmLine/Particles"
else:
    rootInTes = '/Event/Bhadron'
    from PhysConf.MicroDST import uDstConf
    uDstConf ( rootInTes )
    locationLambdab0 = 'Phys/Lb2D0PHD02HHBeauty2CharmLine/Particles'
    
# LambdaDDCut = "(0 == NINTREE( (ABSID=='p+') & (PIDp<-10) )) & (BPVDIRA>0.999)"
# LambdaLLCut = "(0 == NINTREE( (ABSID=='p+') & (PIDp<-10) )) & (BPVDIRA>0.999)"
Lb02D0L0      = AutomaticData(Location = locationLambdab0)

#----------------------------------------------------
# Selection on Lambda_b0 
#----------------------------------------------------

selCodeLb0 = "(MINTREE('D0'==ABSID, M)>1815*MeV)&(MAXTREE('D0'==ABSID, M)<1915*MeV)&(MINTREE('p+'==ABSID, PROBNNp)>0.1)&(MINTREE('K+'==ABSID, PROBNNk)>0.05)&(MINTREE('pi+'==ABSID, PROBNNpi)>0.01)"
_Lb02D0L0Filt = FilterDesktop('_Lb02D0L0Filt', Code=selCodeLb0 )
sel_Lb02D0L0 = Selection("sel_Lb02D0L0", Algorithm = _Lb02D0L0Filt, RequiredSelections = [Lb02D0L0] )

#----------------------------------------------------
# Swap Lambda0 -> Sigma0 i.e. pK
#----------------------------------------------------

outputCont = "MyLb0"
subpid = createDTFInput(sel_Lb02D0L0,outputCont)
particleSwap = Selection( "particleSwap_"+outputCont, Algorithm = subpid, RequiredSelections=[sel_Lb02D0L0])

#----------------------------------------------------
# Final Selection
#----------------------------------------------------
selCodeFinal = "M > 5000*MeV"
_MyLb0Filt = FilterDesktop('_MyLb0Filt', Code=selCodeFinal )
sel_MyLb0 = Selection("sel_MyLb0", Algorithm = _MyLb0Filt, RequiredSelections = [particleSwap] )

### Gaudi sequences
SeqMyLb0 = SelectionSequence("SeqMyLb0", TopSelection = sel_MyLb0)
#SeqMyLb0 = SelectionSequence("SeqMyLb0", TopSelection = sel_Lb02D0L0)
seqMyLb0 = SeqMyLb0.sequence()


#--------------------------------------------------------------------------
# Configure DaVinci
#-------------------------------------------------------------------------
#from Configurables import DaVinci
#from Configurables import  OfflineVertexFitter

importOptions("MyLb0TupleTree.py")

# right-sign
tupleMyLb0 = DecayTreeTuple( "MyLb0" )
tupleMyLb0.Inputs = [ SeqMyLb0.outputLocation() ]
# wrong-sign
wstupleMyLb0 = DecayTreeTuple( "wsMyLb0" )
wstupleMyLb0.Inputs = [ SeqMyLb0.outputLocation() ]


#from PhysConf.Filters import LoKi_Filters
#fltrs = LoKi_Filters(STRIP_Code = "(HLT_PASS_RE('StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision'))" )


#from Configurables import DaVinci
from Configurables import CondDB


# Add a filter on the Stripping Lines
from PhysConf.Filters import LoKi_Filters

fltrs = LoKi_Filters (STRIP_Code = " HLT_PASS_RE('StrippingLb2D0PHD02HHBeauty2CharmLineDecision') ")
fltrSeq = fltrs.sequence ( 'MyFilters' )  
#fltrSeq.RootInTES = rootInTes

from Configurables import LoKi__HDRFilter   as StripFilter
if simulation == False:
    DaVinci().EventPreFilters = [fltrSeq]
    #DaVinci().appendToMainSequence( [ StripFilter( 'StripPassFilter', Code="HLT_PASS('StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision')", Location="/Event/Strip/Phys/DecReports" ) ])

if simulation:
    tupleMyLb0.ToolList += [ "TupleToolMCTruth" ]
    wstupleMyLb0.ToolList += [ "TupleToolMCTruth" ]
    tupleMyLb0.ToolList += [  "TupleToolMCBackgroundInfo"   ]
    wstupleMyLb0.ToolList += [ "TupleToolMCBackgroundInfo" ]

    decay = "[Xi_bc0 => ^(D0 => ^K- ^pi+) ^p+ ^pi-]CC"
    mcTuple = MCDecayTreeTuple("MCTupleXb2D0pK")
    mcTuple.Decay = decay
    mcTuple.ToolList = [ "MCTupleToolKinematic", "MCTupleToolReconstructed" ]
    mcTuple.UseLabXSyntax = True
    mcTuple.RevertToPositiveID = False





# Gaudi sequences
gseqMyLb0 =  GaudiSequencer("MyGaudiSeqMyLb0")
#gseqMyLb0.RootInTES = rootInTes
gseqMyLb0.Members += [seqMyLb0]
gseqMyLb0.Members += [tupleMyLb0]
wsgseqMyLb0 =  GaudiSequencer("wsMyGaudiSeqMyLb0")
#wsgseqMyLb0.RootInTES = rootInTes
wsgseqMyLb0.Members += [seqMyLb0]
wsgseqMyLb0.Members += [wstupleMyLb0]

    
#DaVinci().appendToMainSequence( [gseqMyLb0] )
DaVinci().appendToMainSequence( [gseqMyLb0, wsgseqMyLb0] )
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
#    DaVinci().InputType = 'DST'
    DaVinci().RootInTES = rootInTes
    DaVinci().InputType = 'MDST'




#from GaudiConf import IOHelper
#IOHelper().inputFiles([
#'/afs/cern.ch/user/l/lzhang/00020198_00001115_1.dimuon.dst'
#], clear=True)

