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
from Configurables import DeterministicPrescaler

# for tests
#simulation = False
#polarity = -1
#year = "2012"

PRESCALER =  DeterministicPrescaler("PRESCALER", AcceptFraction = 0.1)

pions = DataOnDemand(Location = "Phys/StdAllNoPIDsPions/Particles")
kaons = DataOnDemand(Location = "Phys/StdAllNoPIDsKaons/Particles")
protons = DataOnDemand(Location = "Phys/StdAllNoPIDsProtons/Particles")
muons = DataOnDemand(Location = "Phys/StdLooseMuons/Particles")

TrackCut = "(TRCHI2DOF < 4.0) & (MIPCHI2DV(PRIMARY)>4) & (TRGHOSTPROB < 0.4) & (PT > 200*MeV) & (ISLONG)"
DaughtCutPi = TrackCut + " &  (PROBNNpi>0.01)"
DaughtCutKa = TrackCut + " &  (PROBNNk>0.05)"
DaughtCutPr = TrackCut + " &  (PROBNNp>0.1)"

#----Jpsi->mumu---------------------------------
location_LcMu = "/Event/Semileptonic/Phys/B2DMuNuX_Lc/Particles"
location_DMu = "/Event/Semileptonic/Phys/B2DMuNuX_Dp/Particles"
location_XicMu = "/Event/Semileptonic/Phys/B2DMuNuX_Xic/Particles"
location_Xic0Mu = "/Event/Semileptonic/Phys/B2DMuNuX_Xic0/Particles"
location_Omc0Mu = "/Event/Semileptonic/Phys/B2DMuNuX_Omegac/Particles"

location_D = "/Event/Semileptonic/Phys/CharmSelForDpB2DMuNuX/Particles"
location_Lc = "/Event/Semileptonic/Phys/CharmSelForLcB2DMuNuX/Particles"
location_Xic = "/Event/Semileptonic/Phys/CharmSelForXicB2DMuNuX/Particles"
location_Xic0 = "/Event/Semileptonic/Phys/CharmSelForXic0B2DMuNuX/Particles"
location_Omc0 = "/Event/Semileptonic/Phys/CharmSelForOmegacB2DMuNuX/Particles"
if simulation:
    location_XicMu = "/Event/AllStreams/Phys/B2DMuNuX_Xic/Particles"
    location_Xic0Mu = "/Event/AllStreams/Phys/B2DMuNuX_Xic0/Particles"
    location_Omc0Mu = "/Event/AllStreams/Phys/B2DMuNuX_Omegac/Particles"
    location_Xic = "/Event/AllStreams/Phys/CharmSelForXicB2DMuNuX/Particles"
    location_Xic0 = "/Event/AllStreams/Phys/CharmSelForXic0B2DMuNuX/Particles"
    location_Omc0 = "/Event/AllStreams/Phys/CharmSelForOmegacB2DMuNuX/Particles"
    location_D = "/Event/AllStreams/Phys/CharmSelForDpB2DMuNuX/Particles"
    location_Lc = "/Event/AllStreams/Phys/CharmSelForLcB2DMuNuX/Particles"

# charm hadron from SL line
_D = AutomaticData(Location = location_D)
_Lc = AutomaticData(Location = location_Lc)
_Xic = AutomaticData(Location = location_Xic)
_Xic0 = AutomaticData(Location = location_Xic0)
_Omegac0 = AutomaticData(Location = location_Omc0)
# full b-baryon candidate
_DMu = AutomaticData(Location = location_DMu)
_LcMu = AutomaticData(Location = location_LcMu)
_XicMu = AutomaticData(Location = location_XicMu)
_Xic0Mu = AutomaticData(Location = location_Xic0Mu)
_Omegac0Mu = AutomaticData(Location = location_Omc0Mu)

#---- pre-selection of charm baryons ---
selCode_D = "(ADMASS('D+') < 60.0)&(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('pi+'==ABSID,PROBNNpi)>0.01)"
selCode_Lc = "(ADMASS('Lambda_c+') < 60.0)&(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('p+'==ABSID,PROBNNp)>0.1)"
selCode_Xic = "(ADMASS('Xi_c+') < 60.0)&(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('p+'==ABSID,PROBNNp)>0.1)"
selCode_Xic0 = "(ADMASS('Xi_c0') < 60.0)&(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('p+'==ABSID,PROBNNp)>0.1)"
selCode_Omc0 = "(ADMASS('Omega_c0') < 60.0)&(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('p+'==ABSID,PROBNNp)>0.1)"
selCode_mu = "(PT > 1000.0 ) & (P> 6000.0)& (TRCHI2DOF < 3.0)& (TRGHOSTPROB < 0.35)& (MIPCHI2DV(PRIMARY)> 4.0) & (PIDmu > 0.0)"

# Basically take all here (just for tests)
#selCode_Xic0 = "(ADMASS('Xi_c0') < 100.0)"
#selCode_Xic = "(ADMASS('Xi_c+') < 100.0)"
#selCode_Omc0 = "(ADMASS('Omega_c0') < 100.0)"
#selCode_mu = "(PT>10.0 )"

#----------------------------------------------
# Filters on charm hadrons from stripping lines
#----------------------------------------------
_DFilt = FilterDesktop('_DFilt', Code=selCode_D )
_LcFilt = FilterDesktop('_LcFilt', Code=selCode_Lc )
_XicFilt = FilterDesktop('_XicFilt', Code=selCode_Xic )
_XiczFilt = FilterDesktop('_Xic0Filt', Code=selCode_Xic0 )
_OmczFilt = FilterDesktop('_OmczFilt', Code=selCode_Omc0 )
_muFilt = FilterDesktop('_muFilt', Code=selCode_mu )
sel_D = Selection( "sel_D", Algorithm = _DFilt, RequiredSelections = [ _D ] )
sel_Lc = Selection( "sel_Lc", Algorithm = _LcFilt, RequiredSelections = [ _Lc ] )
sel_Xic = Selection( "sel_Xic", Algorithm = _XicFilt, RequiredSelections = [ _Xic ] )
sel_Xicz = Selection( "sel_Xicz", Algorithm = _XiczFilt, RequiredSelections = [ _Xic0 ] )
sel_Omegac = Selection( "sel_Omegac", Algorithm = _OmczFilt, RequiredSelections = [ _Omegac0 ] )
sel_mu = Selection( "sel_mu", Algorithm = _muFilt, RequiredSelections = [ muons ] )

#----------------------------------------------
# Select Xic mu-, Xic^0 mu-, Omega_c mu- decays
#----------------------------------------------
selCode_DMu = "(MINTREE('D+'==ABSID, M)>1820*MeV)&(MAXTREE('D+'==ABSID, M)<1920*MeV)&(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('pi+'==ABSID,PROBNNpi)>0.01)"
selCode_LcMu = "(MINTREE('Lambda_c+'==ABSID, M)>2235*MeV)&(MAXTREE('Lambda_c+'==ABSID, M)<2335*MeV)&(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('p+'==ABSID,PROBNNp)>0.1)"
selCode_XicMu = "(MINTREE('Xi_c+'==ABSID, M)>2420*MeV)&(MAXTREE('Xi_c+'==ABSID, M)<2520*MeV)&(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('p+'==ABSID,PROBNNp)>0.1)"
selCode_Xic0Mu = "(MINTREE('Xi_c0'==ABSID, M)>2420*MeV)&(MAXTREE('Xi_c0'==ABSID, M)<2520*MeV)&(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('p+'==ABSID,PROBNNp)>0.1)"
selCode_Omc0Mu = "(MINTREE('Omega_c0'==ABSID, M)>2645*MeV)&(MAXTREE('Omega_c0'==ABSID, M)<2745*MeV)&(MINTREE('K+'==ABSID,PROBNNk)>0.05)&(MINTREE('p+'==ABSID,PROBNNp)>0.1)"
_DMuFilt = FilterDesktop('_DMuFilt', Code=selCode_DMu )
_LcMuFilt = FilterDesktop('_LcMuFilt', Code=selCode_LcMu )
_XicMuFilt = FilterDesktop('_XicMuFilt', Code=selCode_XicMu )
_XiczMuFilt = FilterDesktop('_Xic0MuFilt', Code=selCode_Xic0Mu )
_OmczMuFilt = FilterDesktop('_OmczMuFilt', Code=selCode_Omc0Mu )
sel_DMu = Selection( "sel_DMu", Algorithm = _DMuFilt, RequiredSelections = [ _DMu ] )
sel_LcMu = Selection( "sel_LcMu", Algorithm = _LcMuFilt, RequiredSelections = [ _LcMu ] )
sel_XicMu = Selection( "sel_XicMu", Algorithm = _XicMuFilt, RequiredSelections = [ _XicMu ] )
sel_XiczMu = Selection( "sel_XiczMu", Algorithm = _XiczMuFilt, RequiredSelections = [ _Xic0Mu ] )
sel_OmczMu = Selection( "sel_OmczMu", Algorithm = _OmczMuFilt, RequiredSelections = [ _Omegac0Mu ] )


SeqDMu = SelectionSequence("SeqDMu", TopSelection = sel_DMu, EventPreSelector = [ PRESCALER ])
seqDMu = SeqDMu.sequence()
SeqLcMu = SelectionSequence("SeqLcMu", TopSelection = sel_LcMu, EventPreSelector = [ PRESCALER ])
seqLcMu = SeqLcMu.sequence()
SeqXicMu = SelectionSequence("SeqXicMu", TopSelection = sel_XicMu)
seqXicMu = SeqXicMu.sequence()
SeqXiczMu = SelectionSequence("SeqXiczMu", TopSelection = sel_XiczMu)
seqXiczMu = SeqXiczMu.sequence()
SeqOmczMu = SelectionSequence("SeqOmczMu", TopSelection = sel_OmczMu)
seqOmczMu = SeqOmczMu.sequence()



# ==============
# -- Form Xi_cc+
# ==============
_Xiccp = CombineParticles( "_Xiccp",
                           DecayDescriptor = "[Xi_cc+ -> Xi_c0 pi+]cc",
                           CombinationCut = "(AM>2000*MeV) & (AM<4500*MeV) & (ADOCACHI2CUT( 16,''))",
                           MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.90) & (MINTREE(((ABSID=='Omega_c0')|(ABSID=='Xi_c+')|(ABSID=='Xi_c0')), VFASPF(VZ))-VFASPF(VZ) > -1.0 )",
                           DaughtersCuts   = { 'pi+' : DaughtCutPi
                                               ,'Xi_c0': "ALL" }
                           ,ReFitPVs        = False )
sel_Xiccp = Selection( "sel_Xiccp",
                      Algorithm          = _Xiccp,
                      RequiredSelections = [ pions, sel_Xicz ] )

_Xiccp1 = CombineParticles( "_Xiccp1",
                           DecayDescriptor = "[Xi_cc+ -> Lambda_c+ K- pi+]cc",
                           CombinationCut = "(AM>2000*MeV) & (AM<4500*MeV) & (ADOCACHI2CUT( 16,''))",
                           MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.90) & (MINTREE(ABSID=='Lambda_c+', VFASPF(VZ))-VFASPF(VZ) > -1.0 )",
                           DaughtersCuts   = { 'pi+' : DaughtCutPi
                                               ,'K-': DaughtCutKa 
                                               ,'Lambda_c+': "ALL" }
                           ,ReFitPVs        = False )
sel_Xiccp1 = Selection( "sel_Xiccp1",
                      Algorithm          = _Xiccp1,
                      RequiredSelections = [ pions, kaons, sel_Lc ] )

_Xiccp2 = CombineParticles( "_Xiccp2",
                           DecayDescriptor = "[Xi_cc+ -> D+ p+ K-]cc",
                           CombinationCut = "(AM>2000*MeV) & (AM<4500*MeV) & (ADOCACHI2CUT( 16,''))",
                           MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.90) & (MINTREE(ABSID=='D+', VFASPF(VZ))-VFASPF(VZ) > -1.0 )",
                           DaughtersCuts   = { 'p+' : DaughtCutPr
                                               ,'K-': DaughtCutKa 
                                               ,'D+': "ALL" }
                           ,ReFitPVs        = False )
sel_Xiccp2 = Selection( "sel_Xiccp2",
                      Algorithm          = _Xiccp2,
                      RequiredSelections = [ protons, kaons, sel_D ] )

# =====================================
# -- Form Xi_cc++, and then Xi_cc+ mu-
# =====================================
_Xiccpp = CombineParticles( "_Xiccpp",
                           DecayDescriptor = "[Xi_cc++ -> Xi_c+ pi+]cc",
                           CombinationCut = "(AM>2000*MeV) & (AM<4500*MeV) & (ADOCACHI2CUT( 16,''))",
                           MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.90) & (MINTREE(((ABSID=='Omega_c0')|(ABSID=='Xi_c+')|(ABSID=='Xi_c0')), VFASPF(VZ))-VFASPF(VZ) > -1.0 )",
                           DaughtersCuts   = { 'pi+' : DaughtCutPi
                                               ,'Xi_c+': "ALL" }
                           ,ReFitPVs        = False )
sel_Xiccpp = Selection( "sel_Xiccpp",
                      Algorithm          = _Xiccpp,
                      RequiredSelections = [ pions, sel_Xic ] )

# -------------------------
# Xi_bc^+ --> Xi_cc++ mu-
# -------------------------
_Xibcp = CombineParticles( "_Xibcp",
                           DecayDescriptor = "[Xi_bc+ -> Xi_cc++ mu-]cc",
                           CombinationCut = "(AM>3300*MeV) & (AM<8000*MeV) & (ADOCACHI2CUT( 16,''))",
                           MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.98) & (MINTREE(((ABSID=='Xi_cc+')|(ABSID=='Xi_cc++')), VFASPF(VZ))-VFASPF(VZ) > -1.0 )",
                           DaughtersCuts   = { 'mu-' : "ALL"
                                               ,'Xi_cc++': "ALL" }
                           ,ReFitPVs        = False )
sel_Xibcp = Selection( "sel_Xibcp",
                      Algorithm          = _Xibcp,
                      RequiredSelections = [ sel_mu, sel_Xiccpp ] )

SeqX2XiccppMu = SelectionSequence("SeqX2XiccppMu", TopSelection = sel_Xibcp)
seqX2XiccppMu = SeqX2XiccppMu.sequence()

#---------------------------------------
# Xi_bc^0 --> (Xicc+ -> Xic0 pi+) mu-
#--------------------------------------
_Xibcz = CombineParticles( "_Xibcz",
                           DecayDescriptor = "[Xi_bc0 -> Xi_cc+ mu-]cc",
                           CombinationCut = "(AM>3300*MeV) & (AM<8000*MeV) & (ADOCACHI2CUT( 16,''))",
                           MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.98) & (MINTREE(((ABSID=='Xi_cc+')|(ABSID=='Xi_cc++')), VFASPF(VZ))-VFASPF(VZ) > -1.0 )",
                           DaughtersCuts   = { 'mu-' : "ALL"
                                               ,'Xi_cc+': "ALL" }
                           ,ReFitPVs        = False )
sel_Xibcz = Selection( "sel_Xibcz",
                      Algorithm          = _Xibcz,
                      RequiredSelections = [ sel_mu, sel_Xiccp ] )

SeqX2XiccpMu = SelectionSequence("SeqX2XiccpMu", TopSelection = sel_Xibcz)
seqX2XiccpMu = SeqX2XiccpMu.sequence()

#-------------------------------------
#  Xi_bc^0 ->  (Xicc+ -> Lc K pi) mu-
#-------------------------------------
_Xibcz1 = CombineParticles( "_Xibcz1",
                           DecayDescriptor = "[Xi_bc0 -> Xi_cc+ mu-]cc",
                           CombinationCut = "(AM>3300*MeV) & (AM<8000*MeV) & (ADOCACHI2CUT( 16,''))",
                           MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.98) & (MINTREE(((ABSID=='Xi_cc+')|(ABSID=='Xi_cc++')), VFASPF(VZ))-VFASPF(VZ) > -1.0 )",
                           DaughtersCuts   = { 'mu-' : "ALL"
                                               ,'Xi_cc+': "ALL" }
                           ,ReFitPVs        = False )
sel_Xibcz1 = Selection( "sel_Xibcz1",
                      Algorithm          = _Xibcz1,
                      RequiredSelections = [ sel_mu, sel_Xiccp1 ] )

SeqX2XiccpMu1 = SelectionSequence("SeqX2XiccpMu1", TopSelection = sel_Xibcz1)
seqX2XiccpMu1 = SeqX2XiccpMu1.sequence()

#----------------------------------------
#     Xi_bc^0 -> (Xicc+ -> D p K ) mu-
#----------------------------------------
_Xibcz2 = CombineParticles( "_Xibcz2",
                           DecayDescriptor = "[Xi_bc0 -> Xi_cc+ mu-]cc",
                           CombinationCut = "(AM>3300*MeV) & (AM<8000*MeV) & (ADOCACHI2CUT( 16,''))",
                           MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.98) & (MINTREE(((ABSID=='Xi_cc+')|(ABSID=='Xi_cc++')), VFASPF(VZ))-VFASPF(VZ) > -1.0 )",
                           DaughtersCuts   = { 'mu-' : "ALL"
                                               ,'Xi_cc+': "ALL" }
                           ,ReFitPVs        = False )
sel_Xibcz2 = Selection( "sel_Xibcz2",
                      Algorithm          = _Xibcz2,
                      RequiredSelections = [ sel_mu, sel_Xiccp2 ] )

SeqX2XiccpMu2 = SelectionSequence("SeqX2XiccpMu2", TopSelection = sel_Xibcz2)
seqX2XiccpMu2 = SeqX2XiccpMu2.sequence()

#-----------------------------------------------------
#  Xibc+ -->   (Xicc++ -> Xic+ pi+) mu+    WRONG SIGN
#----------------------------------------------------

_wsXibcp = CombineParticles( "_wsXibcp",
                             DecayDescriptor = "[Xi_bc+ -> Xi_cc++ mu+]cc",
                             CombinationCut = "(AM>3300*MeV) & (AM<8000*MeV) & (ADOCACHI2CUT( 16,''))",
                             MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.98) & (MINTREE(((ABSID=='Xi_cc+')|(ABSID=='Xi_cc++')), VFASPF(VZ))-VFASPF(VZ) > -1.0 )",
                             DaughtersCuts   = { 'mu+' : "ALL"
                                                 ,'Xi_cc++': "ALL" }
                             ,ReFitPVs        = False )
sel_wsXibcp = Selection( "sel_wsXibcp",
                         Algorithm          = _wsXibcp,
                         RequiredSelections = [ sel_mu, sel_Xiccpp ] )

wsSeqX2XiccppMu = SelectionSequence("wsSeqX2XiccppMu", TopSelection = sel_wsXibcp)
wsseqX2XiccppMu = wsSeqX2XiccppMu.sequence()


#-------------------------------------------
#  Xibc0 ->   (Xicc+ -> Xic0 pi+) mu+
#-------------------------------------------
_wsXibcz = CombineParticles( "_wsXibcz",
                             DecayDescriptor = "[Xi_bc0 -> Xi_cc+ mu+]cc",
                             CombinationCut = "(AM>3300*MeV) & (AM<8000*MeV) & (ADOCACHI2CUT( 16,''))",
                             MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.98) & (MINTREE(((ABSID=='Xi_cc+')|(ABSID=='Xi_cc++')), VFASPF(VZ))-VFASPF(VZ) > -1.0 )",
                             DaughtersCuts   = { 'mu+' : "ALL"
                                                 ,'Xi_cc+': "ALL" }
                             ,ReFitPVs        = False )
sel_wsXibcz = Selection( "sel_wsXibcz",
                         Algorithm          = _wsXibcz,
                         RequiredSelections = [ sel_mu, sel_Xiccp ] )

wsSeqX2XiccpMu = SelectionSequence("wsSeqX2XiccpMu", TopSelection = sel_wsXibcz)
wsseqX2XiccpMu = wsSeqX2XiccpMu.sequence()

#--------------------------------------------
#  Xi_bc^0 ->   (Xicc+ -> Lc K pi) mu+
#---------------------------------------------
_wsXibcz1 = CombineParticles( "_wsXibcz1",
                           DecayDescriptor = "[Xi_bc0 -> Xi_cc+ mu+]cc",
                           CombinationCut = "(AM>3300*MeV) & (AM<8000*MeV) & (ADOCACHI2CUT( 16,''))",
                           MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.98) & (MINTREE(((ABSID=='Xi_cc+')|(ABSID=='Xi_cc++')), VFASPF(VZ))-VFASPF(VZ) > -1.0 )",
                           DaughtersCuts   = { 'mu+' : "ALL"
                                               ,'Xi_cc+': "ALL" }
                           ,ReFitPVs        = False )
sel_wsXibcz1 = Selection( "sel_wsXibcz1",
                      Algorithm          = _wsXibcz1,
                      RequiredSelections = [ sel_mu, sel_Xiccp1 ] )

wsSeqX2XiccpMu1 = SelectionSequence("wsSeqX2XiccpMu1", TopSelection = sel_wsXibcz1)
wsseqX2XiccpMu1 = wsSeqX2XiccpMu1.sequence()

#--------------------------------------------
# Xi_bc^0 ->    (Xicc+ -> Lc K pi) mu+
#--------------------------------------------
_wsXibcz2 = CombineParticles( "_wsXibcz2",
                           DecayDescriptor = "[Xi_bc0 -> Xi_cc+ mu+]cc",
                           CombinationCut = "(AM>3300*MeV) & (AM<8000*MeV) & (ADOCACHI2CUT( 16,''))",
                           MotherCut       = "(VFASPF(VCHI2/VDOF) < 10) & (BPVVDCHI2>16) & (BPVDIRA>0.98) & (MINTREE(((ABSID=='Xi_cc+')|(ABSID=='Xi_cc++')), VFASPF(VZ))-VFASPF(VZ) > -1.0 )",
                           DaughtersCuts   = { 'mu+' : "ALL"
                                               ,'Xi_cc+': "ALL" }
                           ,ReFitPVs        = False )
sel_wsXibcz2 = Selection( "sel_wsXibcz2",
                      Algorithm          = _wsXibcz2,
                      RequiredSelections = [ sel_mu, sel_Xiccp2 ] )

wsSeqX2XiccpMu2 = SelectionSequence("wsSeqX2XiccpMu2", TopSelection = sel_wsXibcz2)
wsseqX2XiccpMu2 = wsSeqX2XiccpMu2.sequence()



#--------------------------------------------------------------------------
# Configure DaVinci
#-------------------------------------------------------------------------

importOptions("Xb2JpsiXTree.py")

#-----------
# right-sign
#-----------
tupleXiccpMu = DecayTreeTuple( "XiccpMu" )
tupleXiccpMu.Inputs = [ SeqX2XiccpMu.outputLocation() ]
tupleXiccpMu1 = DecayTreeTuple( "XiccpMu1" )
tupleXiccpMu1.Inputs = [ SeqX2XiccpMu1.outputLocation() ]
tupleXiccpMu2 = DecayTreeTuple( "XiccpMu2" )
tupleXiccpMu2.Inputs = [ SeqX2XiccpMu2.outputLocation() ]
tupleXiccppMu = DecayTreeTuple( "XiccppMu" )
tupleXiccppMu.Inputs = [ SeqX2XiccppMu.outputLocation() ]
#-----------
# wrong-sign
#-----------
wstupleXiccpMu = DecayTreeTuple( "wsXiccpMu" )
wstupleXiccpMu.Inputs = [ wsSeqX2XiccpMu.outputLocation() ]
wstupleXiccpMu1 = DecayTreeTuple( "wsXiccpMu1" )
wstupleXiccpMu1.Inputs = [ wsSeqX2XiccpMu1.outputLocation() ]
wstupleXiccpMu2 = DecayTreeTuple( "wsXiccpMu2" )
wstupleXiccpMu2.Inputs = [ wsSeqX2XiccpMu2.outputLocation() ]
wstupleXiccppMu = DecayTreeTuple( "wsXiccppMu" )
wstupleXiccppMu.Inputs = [ wsSeqX2XiccppMu.outputLocation() ]

#-------------------------------
# (Xic, Xic0, Omegac) mu- tuples
#-------------------------------
# right-sign
#-----------
tupleDMu = DecayTreeTuple( "DMu" )
tupleDMu.Inputs = [ SeqDMu.outputLocation() ]
tupleLcMu = DecayTreeTuple( "LcMu" )
tupleLcMu.Inputs = [ SeqLcMu.outputLocation() ]
tupleXicMu = DecayTreeTuple( "XicMu" )
tupleXicMu.Inputs = [ SeqXicMu.outputLocation() ]
tupleXiczMu = DecayTreeTuple( "XiczMu" )
tupleXiczMu.Inputs = [ SeqXiczMu.outputLocation() ]
tupleOmczMu = DecayTreeTuple( "OmczMu" )
tupleOmczMu.Inputs = [ SeqOmczMu.outputLocation() ]
#-----------
# wrong-sign
#-----------
wstupleXiccpMu = DecayTreeTuple( "wsXiccpMu" )
wstupleXiccpMu.Inputs = [ wsSeqX2XiccpMu.outputLocation() ]

wstupleDMu = DecayTreeTuple( "wsDMu" )
wstupleDMu.Inputs = [ SeqDMu.outputLocation() ]
wstupleLcMu = DecayTreeTuple( "wsLcMu" )
wstupleLcMu.Inputs = [ SeqLcMu.outputLocation() ]
wstupleXicMu = DecayTreeTuple( "wsXicMu" )
wstupleXicMu.Inputs = [ SeqXicMu.outputLocation() ]
wstupleXiczMu = DecayTreeTuple( "wsXiczMu" )
wstupleXiczMu.Inputs = [ SeqXiczMu.outputLocation() ]
wstupleOmczMu = DecayTreeTuple( "wsOmczMu" )
wstupleOmczMu.Inputs = [ SeqOmczMu.outputLocation() ]


#from PhysConf.Filters import LoKi_Filters
#fltrs = LoKi_Filters(STRIP_Code = "(HLT_PASS_RE('StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision'))" )

#from Configurables import DaVinci
from Configurables import CondDB


# Add a filter on the Stripping Lines
#from PhysConf.Filters import LoKi_Filters
#fltrs = LoKi_Filters (STRIP_Code = " HLT_PASS_RE('StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision') ")
#fltrSeq = fltrs.sequence ( 'MyFilters' )  

#from Configurables import LoKi__HDRFilter   as StripFilter
#if simulation == False:
    #DaVinci().EventPreFilters = [fltrSeq]
    #DaVinci().appendToMainSequence( [ StripFilter( 'StripPassFilter', Code="HLT_PASS('StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision')", Location="/Event/Strip/Phys/DecReports" ) ])

if simulation:
    tupleXiccpMu.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    wstupleXiccpMu.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    tupleXiccppMu.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    wstupleXiccppMu.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    tupleXiccpMu1.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    wstupleXiccpMu1.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    tupleXiccpMu2.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    wstupleXiccpMu2.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    tupleDMu.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    tupleLcMu.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    tupleXicMu.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    tupleXiczMu.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]
    tupleOmczMu.ToolList += [ "TupleToolMCTruth", "TupleToolMCBackgroundInfo" ]    

    # MC Truth information - filled for ALL events
    #decay1 = "[Xi_bc+ => ^(Xi_c+ ==> ^p+ ^K- ^pi+) ^(J/psi(1S) => ^mu+ ^mu-) ]CC"
    #mcTuple1 = MCDecayTreeTuple("MCTupleXb2JpsiXicp")
    #mcTuple1.Decay = decay1
    #mcTuple1.ToolList = [ "MCTupleToolKinematic", "MCTupleToolReconstructed" ] 
    #mcTuple1.UseLabXSyntax = True
    #mcTuple1.RevertToPositiveID = False   


#------------------------
#   Gaudi sequences
#------------------------
# Xicc+(+) mu-
#-------------------
gseqXiccpMu =  GaudiSequencer("gseqXiccpMu")
gseqXiccpMu.Members += [seqX2XiccpMu]
gseqXiccpMu.Members += [tupleXiccpMu]
gseqXiccpMu1 =  GaudiSequencer("gseqXiccpMu1")
gseqXiccpMu1.Members += [seqX2XiccpMu1]
gseqXiccpMu1.Members += [tupleXiccpMu1]
gseqXiccpMu2 =  GaudiSequencer("gseqXiccpMu2")
gseqXiccpMu2.Members += [seqX2XiccpMu2]
gseqXiccpMu2.Members += [tupleXiccpMu2]
gseqXiccppMu =  GaudiSequencer("gseqXiccppMu")
gseqXiccppMu.Members += [seqX2XiccppMu]
gseqXiccppMu.Members += [tupleXiccppMu]
#-------------------
# Xicc+(+) mu+  (WS)
#-------------------
wsgseqXiccpMu =  GaudiSequencer("wsgseqXiccpMu")
wsgseqXiccpMu.Members += [wsseqX2XiccpMu]
wsgseqXiccpMu.Members += [wstupleXiccpMu]
wsgseqXiccpMu1 =  GaudiSequencer("wsgseqXiccpMu1")
wsgseqXiccpMu1.Members += [wsseqX2XiccpMu1]
wsgseqXiccpMu1.Members += [wstupleXiccpMu1]
wsgseqXiccpMu2 =  GaudiSequencer("wsgseqXiccpMu2")
wsgseqXiccpMu2.Members += [wsseqX2XiccpMu2]
wsgseqXiccpMu2.Members += [wstupleXiccpMu2]
wsgseqXiccppMu =  GaudiSequencer("wsgseqXiccppMu")
wsgseqXiccppMu.Members += [wsseqX2XiccppMu]
wsgseqXiccppMu.Members += [wstupleXiccppMu]

#-----------------
# Xc mu+/mu-
#-------------------
# B0 ->D- mu+ X
#-------------------
gseqDMu =  GaudiSequencer("gseqDMu")
gseqDMu.Members += [seqDMu]
gseqDMu.Members += [tupleDMu]
wsgseqDMu =  GaudiSequencer("wsgseqDMu")
wsgseqDMu.Members += [seqDMu]
wsgseqDMu.Members += [wstupleDMu]
#------------------
# Lb - >Lc+ mu- X
#------------------
gseqLcMu =  GaudiSequencer("gseqLcMu")
gseqLcMu.Members += [seqLcMu]
gseqLcMu.Members += [tupleLcMu]
wsgseqLcMu =  GaudiSequencer("wsgseqLcMu")
wsgseqLcMu.Members += [seqLcMu]
wsgseqLcMu.Members += [wstupleLcMu]
#------------------
# Xib -> Xic+ mu- X
#------------------
gseqXicMu =  GaudiSequencer("gseqXicMu")
gseqXicMu.Members += [seqXicMu]
gseqXicMu.Members += [tupleXicMu]
wsgseqXicMu =  GaudiSequencer("wsgseqXicMu")
wsgseqXicMu.Members += [seqXicMu]
wsgseqXicMu.Members += [wstupleXicMu]
#------------------
# Xib- -> Xic0 mu- X
#------------------
gseqXiczMu =  GaudiSequencer("gseqXiczMu")
gseqXiczMu.Members += [seqXiczMu]
gseqXiczMu.Members += [tupleXiczMu]
wsgseqXiczMu =  GaudiSequencer("wsgseqXiczMu")
wsgseqXiczMu.Members += [seqXiczMu]
wsgseqXiczMu.Members += [wstupleXiczMu]
#--------------------------------
# Omega_b- -> Omega_c0 mu- X
#--------------------------------
gseqOmczMu =  GaudiSequencer("gseqOmczMu")
gseqOmczMu.Members += [seqOmczMu]
gseqOmczMu.Members += [tupleOmczMu]
wsgseqOmczMu =  GaudiSequencer("wsgseqOmczMu")
wsgseqOmczMu.Members += [seqOmczMu]
wsgseqOmczMu.Members += [wstupleOmczMu]

# Full DaVinci sequence    
DaVinci().appendToMainSequence( [gseqXiccpMu, gseqXiccpMu1, gseqXiccpMu2, wsgseqXiccpMu, wsgseqXiccpMu1, wsgseqXiccpMu2, gseqXiccppMu, wsgseqXiccppMu, gseqXicMu, wsgseqXicMu, gseqLcMu, wsgseqLcMu, gseqDMu, wsgseqDMu,  gseqXiczMu, wsgseqXiczMu,  gseqOmczMu, wsgseqOmczMu] )

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
#'/afs/cern.ch/work/s/sblusk//00051181_00000264_1.semileptonic.dst'
#], clear=True)

