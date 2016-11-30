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

from Configurables import MCDecayTreeTuple
from Configurables import MCTupleToolReconstructed, MCReconstructed

TrackCutShort = "(TRCHI2DOF < 4.0) & (MIPCHI2DV(PRIMARY)>2) & (TRGHOSTPROB < 0.4) & (PT > 200*MeV) & (ISLONG)"

TrackCut = "(TRCHI2DOF < 4.0) & (MIPCHI2DV(PRIMARY)>4) & (TRGHOSTPROB < 0.4) & (PT > 200*MeV) & (ISLONG)"
DaughtCutPi = TrackCut + " &  (PROBNNpi>0.01)"
DaughtCutKa = TrackCut + " &  (PROBNNk>0.1)"
DaughtCutPr = TrackCut + " &  (PROBNNp>0.1)"

#----Jpsi->mumu---------------------------------
location = "/Event/Dimuon/Phys/FullDSTDiMuonJpsi2MuMuDetachedLine/Particles"
#location = "/Event/Dimuon/Phys/FullDSTDiMuonJpsi2MuMuTOSLine/Particles"
if simulation:
    location = "/Event/AllStreams/Phys/FullDSTDiMuonJpsi2MuMuDetachedLine/Particles"
    #location = "/Event/AllStreams/Phys/FullDSTDiMuonJpsi2MuMuTOSLine/Particles"
Jpsi2MuMu = AutomaticData(Location = location)

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

LambdaDDCut = "(0 == NINTREE( (ABSID=='p+') & (PIDp<-10) )) & (BPVDIRA>0.999)"
LambdaLLCut = "(0 == NINTREE( (ABSID=='p+') & (PIDp<-10) )) & (BPVDIRA>0.999)"

#-------------------------------------------------------------
#--- Selection Xib- -> J/psi p K-K- ------- RIGHT SIGN -----------
#-------------------------------------------------------------
_X2JpsipKK = CombineParticles( "_X2JpsipKK",
                               DecayDescriptor = "[Xi_b- -> J/psi(1S) p+ K- K-]cc",
                               DaughtersCuts   = { 'K-': DaughtCutKa 
                                                   ,'p+': DaughtCutPr },                                                         
                               CombinationCut = "AM > 5400 *MeV",
                               MotherCut       = "(BPVDIRA>0.9999) & (VFASPF(VCHI2PDOF)<10) & (BPVVD>1.0*mm) & (BPVVDCHI2>16) & (MIPCHI2DV(PRIMARY)<20) & (M>5500)",
                               ReFitPVs        = False )
sel_X2JpsipKK  = Selection( "sel_X2JpsipKK",
                            Algorithm          = _X2JpsipKK,
                            RequiredSelections = [ Jpsi2MuMu, protons, kaons ] )


_X2JpsipKKpi = CombineParticles( "_X2JpsipKKpi",
                               DecayDescriptor = "[Xi_b0 -> J/psi(1S) p+ K- K- pi+]cc",
                               DaughtersCuts   = { 'K-': DaughtCutKa 
                                                   ,'pi+': DaughtCutPi                                                          
                                                   ,'p+': DaughtCutPr },                                                         
                               CombinationCut = "AM > 5400 *MeV",
                               MotherCut       = "(BPVDIRA>0.9999) & (VFASPF(VCHI2PDOF)<10) & (BPVVD>1.0*mm) & (BPVVDCHI2>16) & (MIPCHI2DV(PRIMARY)<20) & (M>5500)",
                               ReFitPVs        = False )
sel_X2JpsipKKpi  = Selection( "sel_X2JpsipKKpi",
                              Algorithm          = _X2JpsipKKpi,
                              RequiredSelections = [ Jpsi2MuMu, protons, kaons, pions ] )


#---- Refit vertices with Jpsi mass constraint----------------
#_Lb2JpsipK.addTool( OfflineVertexFitter() )
#_Lb2JpsipK.VertexFitters.update( { "" : "OfflineVertexFitter"} )
#_Lb2JpsipK.OfflineVertexFitter.applyDauMassConstraint = True


### RS SelectionSequences
SeqX2JpsipKK = SelectionSequence("SeqX2JpsipKK", TopSelection = sel_X2JpsipKK)
seqX2JpsipKK = SeqX2JpsipKK.sequence()
SeqX2JpsipKKpi = SelectionSequence("SeqX2JpsipKKpi", TopSelection = sel_X2JpsipKKpi)
seqX2JpsipKKpi = SeqX2JpsipKKpi.sequence()


#--------------------------------------------------------------------------
# Configure DaVinci
#-------------------------------------------------------------------------
#from Configurables import DaVinci
#from Configurables import  OfflineVertexFitter

importOptions("Xb2JpsiXTree.py")

# right-sign
tupleX2JpsipKK = DecayTreeTuple( "X2JpsipKK" )
tupleX2JpsipKK.Inputs = [ SeqX2JpsipKK.outputLocation() ]
tupleX2JpsipKKpi = DecayTreeTuple( "X2JpsipKKpi" )
tupleX2JpsipKKpi.Inputs = [ SeqX2JpsipKKpi.outputLocation() ]


#from PhysConf.Filters import LoKi_Filters
#fltrs = LoKi_Filters(STRIP_Code = "(HLT_PASS_RE('StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision'))" )


#from Configurables import DaVinci
from Configurables import CondDB


# Add a filter on the Stripping Lines
from PhysConf.Filters import LoKi_Filters

fltrs = LoKi_Filters (STRIP_Code = " HLT_PASS_RE('StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision') ")
fltrSeq = fltrs.sequence ( 'MyFilters' )  


from Configurables import LoKi__HDRFilter   as StripFilter
if simulation == False:
    DaVinci().EventPreFilters = [fltrSeq]
    #DaVinci().appendToMainSequence( [ StripFilter( 'StripPassFilter', Code="HLT_PASS('StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision')", Location="/Event/Strip/Phys/DecReports" ) ])

if simulation:
    tupleX2JpsipKK.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    tupleX2JpsipKKpi.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]

    # MC Truth information - filled for ALL events
    #decay1 = "[Xi_bc+ => ^(Xi_c+ ==> ^p+ ^K- ^pi+) ^(J/psi(1S) => ^mu+ ^mu-) ]CC"
    #decay2 = "[Xi_bc+ => ^(Lambda_c+ ==> ^p+ ^K- ^pi+) ^(J/psi(1S) => ^mu+ ^mu-)]CC"

    #mcTuple1 = MCDecayTreeTuple("MCTupleXb2JpsiXicp")
    #mcTuple1.Decay = decay1
    #mcTuple1.ToolList = [ "MCTupleToolKinematic", "MCTupleToolReconstructed" ] 
    #mcTuple1.UseLabXSyntax = True
    #mcTuple1.RevertToPositiveID = False   
    #mcTuple2 = mcTuple1.clone("MCTupleXb2JpsiLcp")
    #mcTuple2.Decay = decay2



# Gaudi sequences
gseqX2JpsipKK =  GaudiSequencer("MyGaudiSeqX2JpsipKK")
gseqX2JpsipKK.Members += [seqX2JpsipKK]
gseqX2JpsipKK.Members += [tupleX2JpsipKK]
gseqX2JpsipKKpi =  GaudiSequencer("MyGaudiSeqX2JpsipKKpi")
gseqX2JpsipKKpi.Members += [seqX2JpsipKKpi]
gseqX2JpsipKKpi.Members += [tupleX2JpsipKKpi]
    
DaVinci().appendToMainSequence( [gseqX2JpsipKK, gseqX2JpsipKKpi] )

#if simulation:
#    DaVinci().appendToMainSequence( [mcTuple1, mcTuple2, mcTuple3, mcTuple4] )

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
    DaVinci().InputType = 'DST'




#from GaudiConf import IOHelper
#IOHelper().inputFiles([
#'/afs/cern.ch/user/l/lzhang/00020198_00001115_1.dimuon.dst'
#], clear=True)

