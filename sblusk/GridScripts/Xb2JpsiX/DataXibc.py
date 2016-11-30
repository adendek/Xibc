#---------------------------------------------
# Author   : S Blusk
# Date     : Jan 2016
# Data     : Real Data
#---------------------------------------------

# Test
doTest = False
if doTest:
    simulation = False
    polarity = -1
    year = "2012"
    reStrip = False

#reStrip = True
#if not simulation:
#    reStrip = False
    

from Gaudi.Configuration import *
from Configurables import GaudiSequencer
from Configurables import  DecayTreeTuple, MCDecayTreeTuple, CheckPV
from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence, DataOnDemand
from Configurables import   CombineParticles, FilterDesktop,  OfflineVertexFitter
from Configurables import DaVinci

from Configurables import MCDecayTreeTuple
from Configurables import MCTupleToolReconstructed, MCReconstructed


from StrippingConf.Configuration import StrippingConf, StrippingStream, StrippingLine
from StrippingSettings.Utils import strippingConfiguration
from StrippingArchive.Utils import buildStream, cloneLinesFromStream
from StrippingArchive import strippingArchive

stripping='Stripping21'
#get the configuration dictionary from the database
config  = strippingConfiguration(stripping)
#get the line builders from the archive
archive = strippingArchive(stripping)

def quickBuild(streamName):
        '''wrap buildStream to reduce typing'''
        return buildStream(stripping=config, streamName=streamName, archive=archive)

streams = []
streams.append( quickBuild('Dimuon') )
AllStreams = StrippingStream("AllStreams")
myLines = []
print "Here are the StrippingLines"
for stream in streams:
    for line in stream.lines:
        lineName = line.name()
        if lineName.find("FullDSTDiMuonJpsi2MuMuDetached") >= 0:
            print "Appending Line: ", lineName, "to list of selected lines to run"
            myLines.append(line)
    AllStreams.appendLines(myLines)

sc = StrippingConf( Streams = [ AllStreams ],
                    MaxCandidates = 2000 )
AllStreams.sequence().IgnoreFilterPassed = True # so that we get all events written out



TrackCut = "(TRCHI2DOF < 4.0) & (MIPCHI2DV(PRIMARY)>2) & (TRGHOSTPROB < 0.4) & (PT > 200*MeV) & (ISLONG)"
DaughtCutPi = TrackCut + " &  (PROBNNpi>0.01)"
DaughtCutKa = TrackCut + " &  (PROBNNk>0.05)"
DaughtCutPr = TrackCut + " &  (PROBNNp>0.05)"
DaughtCutPiTight = TrackCut + " &  (PROBNNpi>0.01) & (MIPCHI2DV(PRIMARY)>6.25)"
DaughtCutKaTight = TrackCut + " &  (PROBNNk>0.10) & (MIPCHI2DV(PRIMARY)>6.25)"
DaughtCutPrTight = TrackCut + " &  (PROBNNp>0.10) & (MIPCHI2DV(PRIMARY)>6.25)"

#----Jpsi->mumu---------------------------------
location = "/Event/Dimuon/Phys/FullDSTDiMuonJpsi2MuMuDetachedLine/Particles"
#location = "/Event/Dimuon/Phys/FullDSTDiMuonJpsi2MuMuTOSLine/Particles"
if simulation:
    location = "/Event/AllStreams/Phys/FullDSTDiMuonJpsi2MuMuDetachedLine/Particles"
    if reStrip:
        location = "/Event/Phys/FullDSTDiMuonJpsi2MuMuDetachedLine/Particles"
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

#----------------------------------------------------
# Build Xc candidates
#----------------------------------------------------
# -----------
#   Xi_c0
# -----------
_Xicz = CombineParticles( "_Xicz",
                           DecayDescriptor = "[Xi_c0 -> p+ K- K- pi+]cc",
                           CombinationCut = "(ADAMASS('Xi_c0')<60*MeV)",
                           MotherCut       = "(ADMASS('Xi_c0')<50*MeV) & (VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0)",
                           DaughtersCuts   = { 'pi+' : DaughtCutPi
                                               ,'K-': DaughtCutKa 
                                               ,'p+': DaughtCutPr }                          
                           ,ReFitPVs        = False )
sel_Xicz = Selection( "sel_Xicz",
                      Algorithm          = _Xicz,
                      RequiredSelections = [ pions, kaons, protons ] )

_wsXicz = CombineParticles( "_wsXicz",
                           DecayDescriptor = "[Xi_c0 -> p+ K- K- pi-]cc",
                           CombinationCut = "(ADAMASS('Xi_c0')<60*MeV)",
                           MotherCut       = "(ADMASS('Xi_c0')<50*MeV) & (VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0)",
                           DaughtersCuts   = { 'pi+' : DaughtCutPi
                                               ,'K-': DaughtCutKa 
                                               ,'p+': DaughtCutPr }                          
                           ,ReFitPVs        = False )
sel_wsXicz = Selection( "sel_wsXicz",
                      Algorithm          = _wsXicz,
                      RequiredSelections = [ pions, kaons, protons ] )

# -----------
#   Xi_c+
# -----------
_Xicp = CombineParticles( "_Xicp",
                           DecayDescriptor = "[Xi_c+ -> p+ K- pi+]cc",
                           CombinationCut = "(ADAMASS('Xi_c+')<60*MeV)",
                           MotherCut       = "(ADMASS('Xi_c+')<50*MeV) & (VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0)",
                           DaughtersCuts   = { 'pi+' : DaughtCutPi
                                               ,'K-': DaughtCutKa 
                                               ,'p+': DaughtCutPr }                          
                           ,ReFitPVs        = False )
sel_Xicp = Selection( "sel_Xicp",
                      Algorithm          = _Xicp,
                      RequiredSelections = [ pions, kaons, protons ] )

_wsXicp = CombineParticles( "_wsXicp",
                           DecayDescriptor = "[Xi_c+ -> p+ K- pi-]cc",
                           CombinationCut = "(ADAMASS('Xi_c+')<60*MeV)",
                           MotherCut       = "(ADMASS('Xi_c+')<50*MeV) & (VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0)",
                           DaughtersCuts   = { 'pi+' : DaughtCutPi
                                               ,'K-': DaughtCutKa 
                                               ,'p+': DaughtCutPr }                          
                           ,ReFitPVs        = False )
sel_wsXicp = Selection( "sel_wsXicp",
                      Algorithm          = _wsXicp,
                      RequiredSelections = [ pions, kaons, protons ] )

# --------------
#   Lambda_c+
# --------------
_Lcp = CombineParticles( "_Lcp",
                           DecayDescriptor = "[Lambda_c+ -> p+ K- pi+]cc",
                           CombinationCut = "(ADAMASS('Lambda_c+')<60*MeV)",
                           MotherCut       = "(ADMASS('Lambda_c+')<50*MeV) & (VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0)",
                           DaughtersCuts   = { 'pi+' : DaughtCutPi
                                               ,'K-': DaughtCutKa 
                                               ,'p+': DaughtCutPr }                          
                           ,ReFitPVs        = False )
sel_Lcp = Selection( "sel_Lcp",
                      Algorithm          = _Lcp,
                      RequiredSelections = [ pions, kaons, protons ] )

_wsLcp = CombineParticles( "_wsLcp",
                           DecayDescriptor = "[Lambda_c+ -> p+ K- pi-]cc",
                           CombinationCut = "(ADAMASS('Lambda_c+')<60*MeV)",
                           MotherCut       = "(ADMASS('Lambda_c+')<50*MeV) & (VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0)",
                           DaughtersCuts   = { 'pi+' : DaughtCutPi
                                               ,'K-': DaughtCutKa 
                                               ,'p+': DaughtCutPr }                          
                           ,ReFitPVs        = False )
sel_wsLcp = Selection( "sel_wsLcp",
                      Algorithm          = _wsLcp,
                      RequiredSelections = [ pions, kaons, protons ] )

# -----------------------------------------
#   Control channel B+ --> J/psi (K pi pi)
# -----------------------------------------
_LcKpipi = CombineParticles( "_LcKpipi",
                           DecayDescriptor = "[Lambda_c+ -> K+ pi- pi+]cc",
                           CombinationCut = "(AM>800*MeV) & (AM<2400*MeV)",
                           MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.9)",
                           DaughtersCuts   = { 'pi+' : DaughtCutPiTight
                                               ,'K-': DaughtCutKaTight                                                
                                               }                          
                           ,ReFitPVs        = False )
sel_LcKpipi = Selection( "sel_LcKpipi",
                      Algorithm          = _LcKpipi,
                      RequiredSelections = [ pions, kaons ] )

# -----------------------------------------
#   Control channel Lb --> J/psi p K-
# -----------------------------------------
_pK = CombineParticles( "_pK",
                           DecayDescriptor = "[Xi_c0 -> p+ K-]cc",
                           CombinationCut = "(AM>800*MeV) & (AM<2800*MeV)",
                           MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.9)",
                           DaughtersCuts   = { 'p+' : DaughtCutPrTight
                                               ,'K-': DaughtCutKaTight                                                
                                               }                          
                           ,ReFitPVs        = False )
sel_pK = Selection( "sel_pK",
                      Algorithm          = _pK,
                      RequiredSelections = [ protons, kaons ] )

#-------------------------------------------------------------
#--- Selection Xibc -> J/psi Xc ------- RIGHT SIGN -----------
#-------------------------------------------------------------
_X2JpsiXicz = CombineParticles( "_X2JpsiXicz",
                              DecayDescriptor = "[Xi_bc0 -> J/psi(1S) Xi_c0]cc",
                              CombinationCut = "AM > 5400 *MeV",
                              MotherCut       = "(BPVDIRA>0.999) & (VFASPF(VCHI2PDOF)<10) & (BPVVD>1.0*mm) & (BPVVDCHI2>16) & (MIPCHI2DV(PRIMARY)<20) & (M>5500)",
                              ReFitPVs        = True )
sel_X2JpsiXicz  = Selection( "sel_X2JpsiXicz",
                      Algorithm          = _X2JpsiXicz,
                      RequiredSelections = [ Jpsi2MuMu, sel_Xicz ] )

_X2JpsiXicp = CombineParticles( "_X2JpsiXicp",
                              DecayDescriptor = "[Xi_bc+ -> J/psi(1S) Xi_c+]cc",
                              CombinationCut = "AM > 5400 *MeV",
                              MotherCut       = "(BPVDIRA>0.999) & (VFASPF(VCHI2PDOF)<10) & (BPVVD>1.0*mm) & (BPVVDCHI2>16) & (MIPCHI2DV(PRIMARY)<20) & (M>5500)",
                              ReFitPVs        = True )
sel_X2JpsiXicp  = Selection( "sel_X2JpsiXicp",
                      Algorithm          = _X2JpsiXicp,
                      RequiredSelections = [ Jpsi2MuMu, sel_Xicp ] )

_X2JpsiLcp = CombineParticles( "_X2JpsiLcp",
                              DecayDescriptor = "[Xi_bc+ -> J/psi(1S) Lambda_c+]cc",
                              CombinationCut = "AM > 5400 *MeV",
                              MotherCut       = "(BPVDIRA>0.999) & (VFASPF(VCHI2PDOF)<10) & (BPVVD>1.0*mm) & (BPVVDCHI2>16) & (MIPCHI2DV(PRIMARY)<20) & (M>5500)",
                              ReFitPVs        = True )
sel_X2JpsiLcp  = Selection( "sel_X2JpsiLcp",
                      Algorithm          = _X2JpsiLcp,
                      RequiredSelections = [ Jpsi2MuMu, sel_Lcp ] )


_X2JpsiLcpK = CombineParticles( "_X2JpsiLcpK",
                                DecayDescriptor = "[Xi_bc0 -> J/psi(1S) Lambda_c+ K-]cc",
                                CombinationCut = "AM > 5400 *MeV",
                                DaughtersCuts   = { 'K-': DaughtCutKa
                                                    ,'J/psi(1S)': "ALL"
                                                    ,'Lambda_c+' : "ALL"
                                                    },
                                MotherCut       = "(BPVDIRA>0.999) & (VFASPF(VCHI2PDOF)<10) & (BPVVD>1.0*mm) & (BPVVDCHI2>16) & (MIPCHI2DV(PRIMARY)<20) & (M>5500)",
                                ReFitPVs        = True )
sel_X2JpsiLcpK  = Selection( "sel_X2JpsiLcpK",
                      Algorithm          = _X2JpsiLcpK,
                      RequiredSelections = [ Jpsi2MuMu, sel_Lcp, kaons ] )

_X2JpsiLcKpipi = CombineParticles( "_X2JpsiLcKpipi",
                              DecayDescriptor = "[B+ -> J/psi(1S) Lambda_c+]cc",
                              CombinationCut = "(AM > 5000*MeV) & (AM<6000*MeV)",
                              MotherCut       = "(BPVDIRA>0.9999) & (VFASPF(VCHI2PDOF)<10) & (BPVVD>1.0*mm) & (BPVVDCHI2>16) & (MIPCHI2DV(PRIMARY)<20) & (M>5000)",
                              ReFitPVs        = True )
sel_X2JpsiLcKpipi  = Selection( "sel_X2JpsiLcKpipi",
                                Algorithm          = _X2JpsiLcKpipi,
                                RequiredSelections = [ Jpsi2MuMu, sel_LcKpipi ] )

_X2JpsipK = CombineParticles( "_X2JpsipK",
                              DecayDescriptor = "[Lambda_b0 -> J/psi(1S) Xi_c0]cc",
                              CombinationCut = "(AM > 5400*MeV) & (AM<5900*MeV)",
                              MotherCut       = "(BPVDIRA>0.9999) & (VFASPF(VCHI2PDOF)<10) & (BPVVD>1.0*mm) & (BPVVDCHI2>16) & (MIPCHI2DV(PRIMARY)<20) & (M>5000)",
                              ReFitPVs        = True )
sel_X2JpsipK  = Selection( "sel_X2JpsipK",
                                Algorithm          = _X2JpsipK,
                                RequiredSelections = [ Jpsi2MuMu, sel_pK ] )


#-------------------------------------------------------------
#--- Selection Xibc -> J/psi Xc ------- WRONG SIGN -----------
#-------------------------------------------------------------
_wsX2JpsiXicz = CombineParticles( "_wsX2JpsiXicz",
                              DecayDescriptor = "[Xi_bc0 -> J/psi(1S) Xi_c0]cc",
                              CombinationCut = "AM > 5400 *MeV",
                              MotherCut       = "(BPVDIRA>0.999) & (VFASPF(VCHI2PDOF)<10) & (BPVVD>1.0*mm) & (BPVVDCHI2>16) & (MIPCHI2DV(PRIMARY)<20) & (M>5500)",
                              ReFitPVs        = True )
sel_wsX2JpsiXicz  = Selection( "sel_wsX2JpsiXicz",
                      Algorithm          = _wsX2JpsiXicz,
                      RequiredSelections = [ Jpsi2MuMu, sel_wsXicz ] )

_wsX2JpsiXicp = CombineParticles( "_wsX2JpsiXicp",
                              DecayDescriptor = "[Xi_bc+ -> J/psi(1S) Xi_c+]cc",
                              CombinationCut = "AM > 5400 *MeV",
                              MotherCut       = "(BPVDIRA>0.999) & (VFASPF(VCHI2PDOF)<10) & (BPVVD>1.0*mm) & (BPVVDCHI2>16) & (MIPCHI2DV(PRIMARY)<20) & (M>5500)",
                              ReFitPVs        = True )
sel_wsX2JpsiXicp  = Selection( "sel_wsX2JpsiXicp",
                      Algorithm          = _wsX2JpsiXicp,
                      RequiredSelections = [ Jpsi2MuMu, sel_wsXicp ] )

_wsX2JpsiLcp = CombineParticles( "_wsX2JpsiLcp",
                              DecayDescriptor = "[Xi_bc+ -> J/psi(1S) Lambda_c+]cc",
                              CombinationCut = "AM > 5400 *MeV",
                              MotherCut       = "(BPVDIRA>0.999) & (VFASPF(VCHI2PDOF)<10) & (BPVVD>1.0*mm) & (BPVVDCHI2>16) & (MIPCHI2DV(PRIMARY)<20) & (M>5500)",
                              ReFitPVs        = True )
sel_wsX2JpsiLcp  = Selection( "sel_wsX2JpsiLcp",
                      Algorithm          = _wsX2JpsiLcp,
                      RequiredSelections = [ Jpsi2MuMu, sel_wsLcp ] )


_wsX2JpsiLcpK = CombineParticles( "_wsX2JpsiLcpK",
                                DecayDescriptor = "[Xi_bc0 -> J/psi(1S) Lambda_c+ K+]cc",
                                CombinationCut = "AM > 5400 *MeV",
                                DaughtersCuts   = { 'K-': DaughtCutKa
                                                    ,'J/psi(1S)': "ALL"
                                                    ,'Lambda_c+' : "ALL"
                                                    },
                                MotherCut       = "(BPVDIRA>0.999) & (VFASPF(VCHI2PDOF)<10) & (BPVVD>1.0*mm) & (BPVVDCHI2>16) & (MIPCHI2DV(PRIMARY)<20) & (M>5500)",
                                ReFitPVs        = True )
sel_wsX2JpsiLcpK  = Selection( "sel_wsX2JpsiLcpK",
                      Algorithm          = _wsX2JpsiLcpK,
                      RequiredSelections = [ Jpsi2MuMu, sel_Lcp, kaons ] )


#---- Refit vertices with Jpsi mass constraint----------------
#_Lb2JpsipK.addTool( OfflineVertexFitter() )
#_Lb2JpsipK.VertexFitters.update( { "" : "OfflineVertexFitter"} )
#_Lb2JpsipK.OfflineVertexFitter.applyDauMassConstraint = True


### RS sequences
SeqX2JpsiXicz = SelectionSequence("SeqX2JpsiXicz", TopSelection = sel_X2JpsiXicz)
seqX2JpsiXicz = SeqX2JpsiXicz.sequence()
SeqX2JpsiXicp = SelectionSequence("SeqX2JpsiXicp", TopSelection = sel_X2JpsiXicp)
seqX2JpsiXicp = SeqX2JpsiXicp.sequence()
SeqX2JpsiLcp = SelectionSequence("SeqX2JpsiLcp", TopSelection = sel_X2JpsiLcp)
seqX2JpsiLcp = SeqX2JpsiLcp.sequence()
SeqX2JpsiLcpK = SelectionSequence("SeqX2JpsiLcpK", TopSelection = sel_X2JpsiLcpK)
seqX2JpsiLcpK = SeqX2JpsiLcpK.sequence()

# Control modes
SeqX2JpsiLcKpipi = SelectionSequence("SeqX2JpsiLcKpipi", TopSelection = sel_X2JpsiLcKpipi)
seqX2JpsiLcKpipi = SeqX2JpsiLcKpipi.sequence()
SeqX2JpsipK = SelectionSequence("SeqX2JpsipK", TopSelection = sel_X2JpsipK)
seqX2JpsipK = SeqX2JpsipK.sequence()

### WS sequences
wsSeqX2JpsiXicz = SelectionSequence("wsSeqX2JpsiXicz", TopSelection = sel_wsX2JpsiXicz)
wsseqX2JpsiXicz = wsSeqX2JpsiXicz.sequence()
wsSeqX2JpsiXicp = SelectionSequence("wsSeqX2JpsiXicp", TopSelection = sel_wsX2JpsiXicp)
wsseqX2JpsiXicp = wsSeqX2JpsiXicp.sequence()
wsSeqX2JpsiLcp = SelectionSequence("wsSeqX2JpsiLcp", TopSelection = sel_wsX2JpsiLcp)
wsseqX2JpsiLcp = wsSeqX2JpsiLcp.sequence()
wsSeqX2JpsiLcpK = SelectionSequence("wsSeqX2JpsiLcpK", TopSelection = sel_wsX2JpsiLcpK)
wsseqX2JpsiLcpK = wsSeqX2JpsiLcpK.sequence()


#--------------------------------------------------------------------------
# Configure DaVinci
#-------------------------------------------------------------------------
#from Configurables import DaVinci
#from Configurables import  OfflineVertexFitter

importOptions("Xb2JpsiXTree.py")

# right-sign
tupleX2JpsiXicz = DecayTreeTuple( "X2JpsiXicz" )
tupleX2JpsiXicz.Inputs = [ SeqX2JpsiXicz.outputLocation() ]
tupleX2JpsiXicp = DecayTreeTuple( "X2JpsiXicp" )
tupleX2JpsiXicp.Inputs = [ SeqX2JpsiXicp.outputLocation() ]
tupleX2JpsiLcp = DecayTreeTuple( "X2JpsiLcp" )
tupleX2JpsiLcp.Inputs = [ SeqX2JpsiLcp.outputLocation() ]
tupleX2JpsiLcpK = DecayTreeTuple( "X2JpsiLcpK" )
tupleX2JpsiLcpK.Inputs = [ SeqX2JpsiLcpK.outputLocation() ]

# control modes
tupleX2JpsiLcKpipi = DecayTreeTuple( "X2JpsiLcKpipi" )
tupleX2JpsiLcKpipi.Inputs = [ SeqX2JpsiLcKpipi.outputLocation() ]
tupleX2JpsipK = DecayTreeTuple( "X2JpsipK" )
tupleX2JpsipK.Inputs = [ SeqX2JpsipK.outputLocation() ]
#wrong-sign
wstupleX2JpsiXicz = DecayTreeTuple( "wsX2JpsiXicz" )
wstupleX2JpsiXicz.Inputs = [ wsSeqX2JpsiXicz.outputLocation() ]
wstupleX2JpsiXicp = DecayTreeTuple( "wsX2JpsiXicp" )
wstupleX2JpsiXicp.Inputs = [ wsSeqX2JpsiXicp.outputLocation() ]
wstupleX2JpsiLcp = DecayTreeTuple( "wsX2JpsiLcp" )
wstupleX2JpsiLcp.Inputs = [ wsSeqX2JpsiLcp.outputLocation() ]
wstupleX2JpsiLcpK = DecayTreeTuple( "wsX2JpsiLcpK" )
wstupleX2JpsiLcpK.Inputs = [ wsSeqX2JpsiLcpK.outputLocation() ]


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
    if not reStrip:
        DaVinci().EventPreFilters = [fltrSeq]
    #DaVinci().appendToMainSequence( [ StripFilter( 'StripPassFilter', Code="HLT_PASS('StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision')", Location="/Event/Strip/Phys/DecReports" ) ])

if simulation:
    tupleX2JpsiXicz.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    tupleX2JpsiXicp.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    tupleX2JpsiLcp.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo"  ]
    tupleX2JpsiLcpK.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo"  ]
    tupleX2JpsiLcKpipi.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo"  ]
    tupleX2JpsipK.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo"  ]
    wstupleX2JpsiXicz.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo"  ]
    wstupleX2JpsiXicp.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo"  ]
    wstupleX2JpsiLcp.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo"  ]
    wstupleX2JpsiLcpK.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo"  ]

    # MC Truth information - filled for ALL events
    decay1 = "[Xi_bc+ => ^(Xi_c+ ==> ^p+ ^K- ^pi+) ^(J/psi(1S) => ^mu+ ^mu-) ]CC"
    decay2 = "[Xi_bc+ => ^(Lambda_c+ ==> ^p+ ^K- ^pi+) ^(J/psi(1S) => ^mu+ ^mu-)]CC"
    decay3 = "[Xi_bc0 => ^(Xi_c0 ==> ^p+ ^K- ^K- ^pi+) ^(J/psi(1S) => ^mu+ ^mu-) ]CC"
    decay4 = "[Xi_bc0 => ^(Lambda_c+ ==> ^p+ ^K- ^pi+) ^(J/psi(1S) => ^mu+ ^mu-) ^K-]CC"
    decay5 = "[B+ => ^(J/psi(1S) => ^mu+ ^mu-) ^K+ ^pi- ^pi+]CC"
    decay6 = "[Lambda_b0 => ^(J/psi(1S) => ^mu+ ^mu-) ^p+ ^K-]CC"

    mcTuple1 = MCDecayTreeTuple("MCTupleXb2JpsiXicp")
    mcTuple1.Decay = decay1
    mcTuple1.ToolList = [ "MCTupleToolKinematic", "MCTupleToolReconstructed" ] 
    mcTuple1.UseLabXSyntax = True
    mcTuple1.RevertToPositiveID = False   
    mcTuple2 = mcTuple1.clone("MCTupleXb2JpsiLcp")
    mcTuple2.Decay = decay2
    mcTuple3 = mcTuple1.clone("MCTupleXb2JpsiXicz")
    mcTuple3.Decay = decay3
    mcTuple4 = mcTuple1.clone("MCTupleXb2JpsiLcK")
    mcTuple4.Decay = decay4
    mcTuple5 = mcTuple1.clone("MCTupleXb2JpsiLcKpipi")
    mcTuple5.Decay = decay5
    mcTuple6 = mcTuple1.clone("MCTupleXb2JpsipK")
    mcTuple6.Decay = decay6


from Configurables import EventNodeKiller
eventNodeKiller = EventNodeKiller('Stripkiller')
eventNodeKiller.Nodes = [ '/Event/AllStreams', '/Event/Strip' ]

# Gaudi sequences
gseqX2JpsiXicz =  GaudiSequencer("MyGaudiSeqX2JpsiXicz")
gseqX2JpsiXicz.Members += [seqX2JpsiXicz]
gseqX2JpsiXicz.Members += [tupleX2JpsiXicz]
gseqX2JpsiXicp =  GaudiSequencer("MyGaudiSeqX2JpsiXicp")
gseqX2JpsiXicp.Members += [seqX2JpsiXicp]
gseqX2JpsiXicp.Members += [tupleX2JpsiXicp]
gseqX2JpsiLcp =  GaudiSequencer("MyGaudiSeqX2JpsiLcp")
gseqX2JpsiLcp.Members += [seqX2JpsiLcp]
gseqX2JpsiLcp.Members += [tupleX2JpsiLcp]
gseqX2JpsiLcpK =  GaudiSequencer("MyGaudiSeqX2JpsiLcpK")
gseqX2JpsiLcpK.Members += [seqX2JpsiLcpK]
gseqX2JpsiLcpK.Members += [tupleX2JpsiLcpK]
gseqX2JpsiLcKpipi =  GaudiSequencer("MyGaudiSeqX2JpsiLcKpipi")
gseqX2JpsipK =  GaudiSequencer("MyGaudiSeqX2JpsipK")
if reStrip:
    gseqX2JpsiLcKpipi.Members += [ eventNodeKiller ]
    gseqX2JpsiLcKpipi.Members += [ sc.sequence() ]
    gseqX2JpsipK.Members += [ eventNodeKiller ]
    gseqX2JpsipK.Members += [ sc.sequence() ]

gseqX2JpsiLcKpipi.Members += [seqX2JpsiLcKpipi]
gseqX2JpsiLcKpipi.Members += [tupleX2JpsiLcKpipi]

gseqX2JpsipK.Members += [seqX2JpsipK]
gseqX2JpsipK.Members += [tupleX2JpsipK]

wsgseqX2JpsiXicz =  GaudiSequencer("wsMyGaudiSeqX2JpsiXicz")
wsgseqX2JpsiXicz.Members += [wsseqX2JpsiXicz]
wsgseqX2JpsiXicz.Members += [wstupleX2JpsiXicz]
wsgseqX2JpsiXicp =  GaudiSequencer("wsMyGaudiSeqX2JpsiXicp")
wsgseqX2JpsiXicp.Members += [wsseqX2JpsiXicp]
wsgseqX2JpsiXicp.Members += [wstupleX2JpsiXicp]
wsgseqX2JpsiLcp =  GaudiSequencer("wsMyGaudiSeqX2JpsiLcp")
wsgseqX2JpsiLcp.Members += [wsseqX2JpsiLcp]
wsgseqX2JpsiLcp.Members += [wstupleX2JpsiLcp]
wsgseqX2JpsiLcpK =  GaudiSequencer("wsMyGaudiSeqX2JpsiLcpK")
wsgseqX2JpsiLcpK.Members += [wsseqX2JpsiLcpK]
wsgseqX2JpsiLcpK.Members += [wstupleX2JpsiLcpK]


    
DaVinci().appendToMainSequence( [gseqX2JpsiXicz, gseqX2JpsiXicp, gseqX2JpsiLcp, gseqX2JpsiLcpK, wsgseqX2JpsiXicz, wsgseqX2JpsiXicp, wsgseqX2JpsiLcp, wsgseqX2JpsiLcpK] )
DaVinci().appendToMainSequence( [gseqX2JpsiLcKpipi] )
DaVinci().appendToMainSequence( [gseqX2JpsipK] )
                                

if simulation:
    DaVinci().appendToMainSequence( [mcTuple1, mcTuple2, mcTuple3, mcTuple4] )

#
from Configurables import CondDB
#
DaVinci().EvtMax     = -1 
DaVinci().DataType   = year
DaVinci().TupleFile  = "tuple.root"
DaVinci().PrintFreq  = 2000
if doTest:
    DaVinci().EvtMax     = 2000

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



if doTest:
    from GaudiConf import IOHelper
    IOHelper().inputFiles([
        '/afs/cern.ch/work/s/sblusk//00041836_00000122_1.dimuon.dst'
        #'/afs/cern.ch/work/s/sblusk/00054065_00000002_2.AllStreams.dst'
        ], clear=True)

