########################################################################
#
# Xb --> J/psi V n-tuple
#
# @author S Blusk
# @date Jan 2016
######
########################################################################
from Gaudi.Configuration import *
#
# DecayTreeTuple
#
from Configurables import DecayTreeTuple, LoKi__Hybrid__TupleTool, TupleToolDecay, TupleToolTrigger, TupleToolTISTOS, TupleToolTagging
from Configurables import FitDecayTrees, TupleToolGeometry, BackgroundCategory, TupleToolNeutrinoReco

tistos = TupleToolTISTOS("tistos")
tistos.VerboseL0 = 1
tistos.VerboseHlt1 = 1
tistos.VerboseHlt2 = 1
tistos.TriggerList = [
                             'L0HCALDecision',
                             'L0MuonDecision',
                         'L0MuonHighDecision',
               'Hlt1SingleMuonNoIPL0Decision',
               'Hlt1SingleMuonHighPTDecision',
                 'Hlt1SingleMuonNoIPDecision',
                     'Hlt1TrackAllL0Decision',
                      'Hlt1TrackMuonDecision',
               'Hlt1SingleMuonNoIPL0Decision',
                     'Hlt2SingleMuonDecision',
               'Hlt2SingleMuonHighPTDecision',
                'Hlt2SingleMuonLowPTDecision',
                  'Hlt2Topo2BodyBBDTDecision',
                  'Hlt2Topo3BodyBBDTDecision',      
                  'Hlt2Topo4BodyBBDTDecision',        
                'Hlt2TopoMu2BodyBBDTDecision',        
                'Hlt2TopoMu3BodyBBDTDecision',      
                'Hlt2TopoMu4BodyBBDTDecision',      
                    'Hlt2TransparentDecision' 
]


tuple = DecayTreeTuple('XiccpMu') 
tuple.Inputs = [ 'Phys/Bs2Jpsif0' ]
tuple.UseLoKiDecayFinders = False
tuple.TupleName = "mytree"
tuple.ToolList =  [
       "TupleToolGeometry",
       "TupleToolKinematic",
       "TupleToolEventInfo",
       "TupleToolVtxIsoln",
       "TupleToolPid",
       "TupleToolANNPID",
       "TupleToolTrackInfo",
       #"TupleToolTagging"
        ]


tuple.addTool(TupleToolGeometry)
tuple.TupleToolGeometry.Verbose = True
#tuple.TupleToolTISTOS.UseAutomaticTriggerList = True
#tuple.addTool(TupleToolTagging)
#tuple.TupleToolTagging.Verbose = True

#######################
# Xibc0 --> Xicc+ mu-
#######################
tuple.Decay = '[Xi_bc0  -> (^Xi_cc+ -> (^Xi_c0 -> ^p+ ^K- ^K- ^pi+) ^pi+) ^mu-]cc'
tuple.Branches = {
    "Xb"   :  "[Xi_bc0]cc : [Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> p+ K- K- pi+) pi+) mu-]cc",
    "Xcc"   :  "[Xi_bc0  -> (^Xi_cc+ -> (Xi_c0 -> p+ K- K- pi+) pi+) mu-]cc",
    "Xc"   :  "[Xi_bc0  -> (Xi_cc+ -> (^Xi_c0 -> p+ K- K- pi+) pi+) mu-]cc",
    "p"   :  "[Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> ^p+ K- K- pi+) pi+) mu-]cc",
    "k1"   :  "[Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> p+ ^K- K- pi+) pi+) mu-]cc",
    "k2"   :  "[Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> p+ K- ^K- pi+) pi+) mu-]cc",
    "pi"   :  "[Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> p+ K- K- ^pi+) pi+) mu-]cc",
    "PI"   :  "[Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> p+ K- K- pi+) ^pi+) mu-]cc",
    "mu"   :  "[Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> p+ K- K- pi+) pi+) ^mu-]cc"
   }

#neuRec = TupleToolNeutrinoReco("neuRec")

tuple.addTool(TupleToolDecay, name="Xb")
tuple.addTool(TupleToolDecay, name="Xcc")
tuple.addTool(TupleToolDecay, name="Xc")
tuple.addTool(TupleToolDecay, name="mu")
tuple.Xb.ToolList += [ "TupleToolPropertime" ]
tuple.Xb.ToolList += [ "TupleToolNeutrinoReco" ]
tuple.Xb.addTool(TupleToolNeutrinoReco)
tuple.Xb.TupleToolNeutrinoReco.Verbose = True
tuple.Xcc.ToolList += [ "TupleToolPropertime" ]
tuple.Xc.ToolList += [ "TupleToolPropertime" ]


tuple.Xb.addTool(tistos)
tuple.Xb.ToolList+=["TupleToolTISTOS/tistos"]
tuple.mu.addTool(tistos)
tuple.mu.ToolList+=["TupleToolTISTOS/tistos"]
#tuple.ReFitPVs = True
#LoKi_Xibc=LoKi__Hybrid__TupleTool("LoKi_Xibc")
#LoKi_Xibc.Variables =  { 
####        "LOKI_FDCHI2"     : "BPVVDCHI2", 
####        "LOKI_FDS"        : "BPVDLS", 
####        "LOKI_DIRA"       : "BPVDIRA" , 
#        "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )", 
####        "LOKI_DTF_CTAUS"       : "DTF_CTAUSIGNIFICANCE( 0, True )", 
#        "LOKI_DTF_CHI2NDOF_massConstr"    : "DTF_CHI2NDOF( True, strings('J/psi(1S)','Xi_c0', 'Xi_c+', 'Lambda_c+') )" ,
###       "LOKI_DTF_CTAUERR"     : "DTF_CTAUERR( 0, True )", 
#        "LOKI_MASS_massConstr" : "DTF_FUN ( M , True , strings('J/psi(1S)','Xi_c0', 'Xi_c+', 'Lambda_c+') )" , 
#        "LOKI_DTF_CHI2NDOF"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True  )"  
#        } 
#tuple.Xb.addTool(LoKi_Xibc)         
#tuple.Xb.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_Xibc"] 

from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiTool
tuple.addTool(LoKiTool , 'MyLoKiTool' )
tuple.ToolList += [ "LoKi::Hybrid::EvtTupleTool/MyLoKiTool" ]
tuple.MyLoKiTool.VOID_Variables = {    'nTracks' :  " CONTAINS ('Rec/Track/Best') "  ,
                                        "nLong"  :   " TrSOURCE('Rec/Track/Best', TrLONG) >> TrSIZE "
                                          }
tuple.MyLoKiTool.Preambulo = [
    "from LoKiTracks.decorators import *",
    "from LoKiCore.functions import *"
    ]


#######################
# Xibc0 --> Xicc+ mu+
#######################
wstuple = tuple.clone('wsXiccpMu')
wstuple.Decay = '[Xi_bc0  -> (^Xi_cc+ -> (^Xi_c0 -> ^p+ ^K- ^K- ^pi+) ^pi+) ^mu+]cc'
wstuple.Branches = {
    "Xb"   :  "[Xi_bc0]cc : [Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> p+ K- K- pi+) pi+) mu+]cc",
    "Xcc"   :  "[Xi_bc0  -> (^Xi_cc+ -> (Xi_c0 -> p+ K- K- pi+) pi+) mu+]cc",
    "Xc"   :  "[Xi_bc0  -> (Xi_cc+ -> (^Xi_c0 -> p+ K- K- pi+) pi+) mu+]cc",
    "p"   :  "[Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> ^p+ K- K- pi+) pi+) mu+]cc",
    "k1"   :  "[Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> p+ ^K- K- pi+) pi+) mu+]cc",
    "k2"   :  "[Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> p+ K- ^K- pi+) pi+) mu+]cc",
    "pi"   :  "[Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> p+ K- K- ^pi+) pi+) mu+]cc",
    "PI"   :  "[Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> p+ K- K- pi+) ^pi+) mu+]cc",
    "mu"   :  "[Xi_bc0  -> (Xi_cc+ -> (Xi_c0 -> p+ K- K- pi+) pi+) ^mu+]cc"
   }

#######################
# Xibc+ --> Xicc++ mu-
#######################
tupleXiccppMu = tuple.clone('XiccppMu')
tupleXiccppMu.Decay = '[Xi_bc+  -> (^Xi_cc++ -> (^Xi_c+ -> ^p+ ^K- ^pi+) ^pi+) ^mu-]cc'
tupleXiccppMu.Branches = {
    "Xb"   :  "[Xi_bc+]cc : [Xi_bc+  -> (Xi_cc++ -> (Xi_c+ -> p+ K- pi+) pi+) mu-]cc",
    "Xcc"  :  "[Xi_bc+  -> (^Xi_cc++ -> (Xi_c+ -> p+ K- pi+) pi+) mu-]cc",
    "Xc"   :  "[Xi_bc+  -> (Xi_cc++ -> (^Xi_c+ -> p+ K- pi+) pi+) mu-]cc",
    "p"   :   "[Xi_bc+  -> (Xi_cc++ -> (Xi_c+ -> ^p+ K- pi+) pi+) mu-]cc",
    "k"   :   "[Xi_bc+  -> (Xi_cc++ -> (Xi_c+ -> p+ ^K- pi+) pi+) mu-]cc",
    "pi"   :  "[Xi_bc+  -> (Xi_cc++ -> (Xi_c+ -> p+ K- ^pi+) pi+) mu-]cc",
    "PI"   :  "[Xi_bc+  -> (Xi_cc++ -> (Xi_c+ -> p+ K- pi+) ^pi+) mu-]cc",
    "mu"   :  "[Xi_bc+  -> (Xi_cc++ -> (Xi_c+ -> p+ K- pi+) pi+) ^mu-]cc"
   }

#######################
# Xibc+ --> Xicc++ mu-
#######################
wstupleXiccppMu = tuple.clone('wsXiccppMu')
wstupleXiccppMu.Decay = '[Xi_bc+  -> (^Xi_cc++ -> (^Xi_c+ -> ^p+ ^K- ^pi+) ^pi+) ^mu+]cc'
wstupleXiccppMu.Branches = {
    "Xb"   :  "[Xi_bc+]cc : [Xi_bc+  -> (Xi_cc++ -> (Xi_c+ -> p+ K- pi+) pi+) mu+]cc",
    "Xcc"  :  "[Xi_bc+  -> (^Xi_cc++ -> (Xi_c+ -> p+ K- pi+) pi+) mu+]cc",
    "Xc"   :  "[Xi_bc+  -> (Xi_cc++ -> (^Xi_c+ -> p+ K- pi+) pi+) mu+]cc",
    "p"   :   "[Xi_bc+  -> (Xi_cc++ -> (Xi_c+ -> ^p+ K- pi+) pi+) mu+]cc",
    "k"   :   "[Xi_bc+  -> (Xi_cc++ -> (Xi_c+ -> p+ ^K- pi+) pi+) mu+]cc",
    "pi"   :  "[Xi_bc+  -> (Xi_cc++ -> (Xi_c+ -> p+ K- ^pi+) pi+) mu+]cc",
    "PI"   :  "[Xi_bc+  -> (Xi_cc++ -> (Xi_c+ -> p+ K- pi+) ^pi+) mu+]cc",
    "mu"   :  "[Xi_bc+  -> (Xi_cc++ -> (Xi_c+ -> p+ K- pi+) pi+) ^mu+]cc"
   }



#######################
# Xib0 --> Xic+ mu- & mu+
#######################
xicmutuple = tuple.clone('XicMu')
xicmutuple.Decay = '[Xi_b0  -> (^Xi_c+ -> ^p+ ^K- ^pi+) ^mu-]cc'
xicmutuple.Branches = {
    "Xb"   :  "[Xi_b0]cc : [Xi_b0  -> (Xi_c+ -> p+ K- pi+) mu-]cc",
    "Xc"   :  "[Xi_b0  -> (^Xi_c+ -> p+ K- pi+) mu-]cc",
    "p"   :   "[Xi_b0  -> (Xi_c+ -> ^p+ K- pi+) mu-]cc",
    "k"   :   "[Xi_b0  -> (Xi_c+ -> p+ ^K- pi+) mu-]cc",
    "pi"   :  "[Xi_b0  -> (Xi_c+ -> p+ K- ^pi+) mu-]cc",
    "mu"   :  "[Xi_b0  -> (Xi_c+ -> p+ K- pi+) ^mu-]cc"
   }
wsxicmutuple = tuple.clone('wsXicMu')
wsxicmutuple.Decay = '[Xi_b0  -> (^Xi_c+ -> ^p+ ^K- ^pi+) ^mu+]cc'
wsxicmutuple.Branches = {
    "Xb"   :  "[Xi_b0]cc : [Xi_b0  -> (Xi_c+ -> p+ K- pi+) mu+]cc",
    "Xc"   :  "[Xi_b0  -> (^Xi_c+ -> p+ K- pi+) mu+]cc",
    "p"   :   "[Xi_b0  -> (Xi_c+ -> ^p+ K- pi+) mu+]cc",
    "k"   :   "[Xi_b0  -> (Xi_c+ -> p+ ^K- pi+) mu+]cc",
    "pi"   :  "[Xi_b0  -> (Xi_c+ -> p+ K- ^pi+) mu+]cc",
    "mu"   :  "[Xi_b0  -> (Xi_c+ -> p+ K- pi+) ^mu+]cc"
   }

#######################
# Lb0 --> Lc+ mu- & mu+
#######################
lcmutuple = tuple.clone('LcMu')
lcmutuple.Decay = '[Lambda_b0  -> (^Lambda_c+ -> ^p+ ^K- ^pi+) ^mu-]cc'
lcmutuple.Branches = {
    "Xb"   :  "[Lambda_b0]cc : [Lambda_b0  -> (Xi_c+ -> p+ K- pi+) mu-]cc",
    "Xc"   :  "[Lambda_b0  -> (^Lambda_c+ -> p+ K- pi+) mu-]cc",
    "p"   :   "[Lambda_b0  -> (Lambda_c+ -> ^p+ K- pi+) mu-]cc",
    "k"   :   "[Lambda_b0  -> (Lambda_c+ -> p+ ^K- pi+) mu-]cc",
    "pi"   :  "[Lambda_b0  -> (Lambda_c+ -> p+ K- ^pi+) mu-]cc",
    "mu"   :  "[Lambda_b0  -> (Lambda_c+ -> p+ K- pi+) ^mu-]cc"
   }

wslcmutuple = tuple.clone('wsLcMu')
wslcmutuple.Decay = '[Lambda_b0  -> (^Lambda_c+ -> ^p+ ^K- ^pi+) ^mu+]cc'
wslcmutuple.Branches = {
    "Xb"   :  "[Lambda_b0]cc : [Lambda_b0  -> (Xi_c+ -> p+ K- pi+) mu+]cc",
    "Xc"   :  "[Lambda_b0  -> (^Lambda_c+ -> p+ K- pi+) mu+]cc",
    "p"   :   "[Lambda_b0  -> (Lambda_c+ -> ^p+ K- pi+) mu+]cc",
    "k"   :   "[Lambda_b0  -> (Lambda_c+ -> p+ ^K- pi+) mu+]cc",
    "pi"   :  "[Lambda_b0  -> (Lambda_c+ -> p+ K- ^pi+) mu+]cc",
    "mu"   :  "[Lambda_b0  -> (Lambda_c+ -> p+ K- pi+) ^mu+]cc"
   }


#######################
# B0 --> D+ mu- & mu+
#######################
dmutuple = tuple.clone('DMu')
dmutuple.Decay = '[B0  -> (^D- -> ^K+ ^pi- ^pi-) ^mu+]cc'
dmutuple.Branches = {
    "Xb"   :  "[B0]cc : [B0  -> (D- -> K+ pi- pi-) mu+]cc",
    "Xc"   :  "[B0  -> (^D- -> K+ pi- pi-) mu+]cc",
    "k"   :   "[B0  -> (D- -> ^K+ pi- pi-) mu+]cc",
    "pi1"  :  "[B0  -> (D- -> K+ ^pi- pi-) mu+]cc",
    "pi2"  :  "[B0  -> (D- -> K+ pi- ^pi-) mu+]cc",
    "mu"   :  "[B0  -> (D- -> K+ pi- pi-) ^mu+]cc",
   }

wsdmutuple = tuple.clone('wsDMu')
wsdmutuple.Decay = '[B0  -> (^D- -> ^K+ ^pi- ^pi-) ^mu-]cc'
wsdmutuple.Branches = {
    "Xb"   :  "[B0]cc : [B0  -> (D- -> K+ pi- pi-) mu-]cc",
    "Xc"   :  "[B0  -> (^D- -> K+ pi- pi-) mu-]cc",
    "k"   :   "[B0  -> (D- -> ^K+ pi- pi-) mu-]cc",
    "pi1"  :  "[B0  -> (D- -> K+ ^pi- pi-) mu-]cc",
    "pi2"  :  "[B0  -> (D- -> K+ pi- ^pi-) mu-]cc",
    "mu"   :  "[B0  -> (D- -> K+ pi- pi-) ^mu-]cc",
   }


######
#######################
# Xib- --> Xic0 mu- & mu+
#######################
xiczmutuple = tuple.clone('XiczMu')
xiczmutuple.Decay = '[Xi_b-  -> (^Xi_c0 -> ^p+ ^K- ^K- ^pi+) ^mu-]cc'
xiczmutuple.Branches = {
    "Xb"   :  "[Xi_b-]cc : [Xi_b0  -> (Xi_c0 -> p+ K- K- pi+) mu-]cc",
    "Xc"   :  "[Xi_b-  -> (^Xi_c0 -> p+ K- K- pi+) mu-]cc",
    "p"   :   "[Xi_b-  -> (Xi_c0 -> ^p+ K- K- pi+) mu-]cc",
    "k1"   :   "[Xi_b-  -> (Xi_c0 -> p+ ^K- K- pi+) mu-]cc",
    "k2"   :   "[Xi_b-  -> (Xi_c0 -> p+  K- ^K- pi+) mu-]cc",
    "pi"   :  "[Xi_b-  -> (Xi_c0 -> p+ K- K- ^pi+) mu-]cc",
    "mu"   :  "[Xi_b-  -> (Xi_c0 -> p+ K- K- pi+) ^mu-]cc"
   }

wsxiczmutuple = tuple.clone('wsXiczMu')
wsxiczmutuple.Decay = '[Xi_b-  -> (^Xi_c0 -> ^p+ ^K- ^K- ^pi+) ^mu+]cc'
wsxiczmutuple.Branches = {
    "Xb"   :  "[Xi_b-]cc : [Xi_b0  -> (Xi_c0 -> p+ K- K- pi+) mu+]cc",
    "Xc"   :  "[Xi_b-  -> (^Xi_c0 -> p+ K- K- pi+) mu+]cc",
    "p"   :   "[Xi_b-  -> (Xi_c0 -> ^p+ K- K- pi+) mu+]cc",
    "k1"   :   "[Xi_b-  -> (Xi_c0 -> p+ ^K- K- pi+) mu+]cc",
    "k2"   :   "[Xi_b-  -> (Xi_c0 -> p+  K- ^K- pi+) mu+]cc",
    "pi"   :  "[Xi_b-  -> (Xi_c0 -> p+ K- K- ^pi+) mu+]cc",
    "mu"   :  "[Xi_b-  -> (Xi_c0 -> p+ K- K- pi+) ^mu+]cc"
   }

##################################
# Omegab- --> Omegac0 mu- & mu+
##################################
omczmutuple = tuple.clone('OmczMu')
omczmutuple.Decay = '[Omega_b-  -> (^Omega_c0 -> ^p+ ^K- ^K- ^pi+) ^mu-]cc'
omczmutuple.Branches = {
    "Xb"   :  "[Omega_b-]cc : [Omega_b-  -> (Omega_c0 -> p+ K- K- pi+) mu-]cc",
    "Xc"   :  "[Omega_b-  -> (^Omega_c0 -> p+ K- K- pi+) mu-]cc",
    "p"   :   "[Omega_b-  -> (Omega_c0 -> ^p+ K- K- pi+) mu-]cc",
    "k1"   :   "[Omega_b-  -> (Omega_c0 -> p+ ^K- K- pi+) mu-]cc",
    "k2"   :   "[Omega_b-  -> (Omega_c0 -> p+  K- ^K- pi+) mu-]cc",
    "pi"   :  "[Omega_b-  -> (Omega_c0 -> p+ K- K- ^pi+) mu-]cc",
    "mu"   :  "[Omega_b-  -> (Omega_c0 -> p+ K- K- pi+) ^mu-]cc"
   }

wsomczmutuple = tuple.clone('wsOmczMu')
wsomczmutuple.Decay = '[Omega_b-  -> (^Omega_c0 -> ^p+ ^K- ^K- ^pi+) ^mu+]cc'
wsomczmutuple.Branches = {
    "Xb"   :  "[Omega_b-]cc : [Omega_b-  -> (Omega_c0 -> p+ K- K- pi+) mu+]cc",
    "Xc"   :  "[Omega_b-  -> (^Omega_c0 -> p+ K- K- pi+) mu+]cc",
    "p"   :   "[Omega_b-  -> (Omega_c0 -> ^p+ K- K- pi+) mu+]cc",
    "k1"   :   "[Omega_b-  -> (Omega_c0 -> p+ ^K- K- pi+) mu+]cc",
    "k2"   :   "[Omega_b-  -> (Omega_c0 -> p+  K- ^K- pi+) mu+]cc",
    "pi"   :  "[Omega_b-  -> (Omega_c0 -> p+ K- K- ^pi+) mu+]cc",
    "mu"   :  "[Omega_b-  -> (Omega_c0 -> p+ K- K- pi+) ^mu+]cc"
   }


#######################
# Xibc+ --> Xicc+ mu-
#######################
tupleXiccpMu1 = tuple.clone('XiccpMu1')
tupleXiccpMu1.Decay = '[Xi_bc0  -> (^Xi_cc+ -> (^Lambda_c+ -> ^p+ ^K- ^pi+) ^K- ^pi+) ^mu-]cc'
tupleXiccpMu1.Branches = {
    "Xb"   :  "[Xi_bc0]cc : [Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> p+ K- pi+) K- pi+) mu-]cc",
    "Xcc"  :  "[Xi_bc0  -> (^Xi_cc+ -> (Lambda_c+ -> p+ K- pi+) K- pi+) mu-]cc",
    "Xc"   :  "[Xi_bc0  -> (Xi_cc+ -> (^Lambda_c+ -> p+ K- pi+) K- pi+) mu-]cc",
    "p"   :   "[Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> ^p+ K- pi+) K- pi+) mu-]cc",
    "k"   :   "[Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> p+ ^K- pi+) K- pi+) mu-]cc",
    "pi"   :  "[Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> p+ K- ^pi+) K- pi+) mu-]cc",
    "K"   :  "[Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> p+ K- pi+) ^K- pi+) mu-]cc",
    "PI"   :  "[Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> p+ K- pi+) K- ^pi+) mu-]cc",
    "mu"   :  "[Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> p+ K- pi+) K- pi+) ^mu-]cc"
   }

#######################
# Xibc+ --> Xicc+ mu+
#######################
wstupleXiccpMu1 = tuple.clone('wsXiccpMu1')
wstupleXiccpMu1.Decay = '[Xi_bc0  -> (^Xi_cc+ -> (^Lambda_c+ -> ^p+ ^K- ^pi+) ^K- ^pi+) ^mu+]cc'
wstupleXiccpMu1.Branches = {
    "Xb"   :  "[Xi_bc0]cc : [Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> p+ K- pi+) K- pi+) mu+]cc",
    "Xcc"  :  "[Xi_bc0  -> (^Xi_cc+ -> (Lambda_c+ -> p+ K- pi+) K- pi+) mu+]cc",
    "Xc"   :  "[Xi_bc0  -> (Xi_cc+ -> (^Lambda_c+ -> p+ K- pi+) K- pi+) mu+]cc",
    "p"   :   "[Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> ^p+ K- pi+) K- pi+) mu+]cc",
    "k"   :   "[Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> p+ ^K- pi+) K- pi+) mu+]cc",
    "pi"   :  "[Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> p+ K- ^pi+) K- pi+) mu+]cc",
    "K"   :  "[Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> p+ K- pi+) ^K- pi+) mu+]cc",
    "PI"   :  "[Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> p+ K- pi+) K- ^pi+) mu+]cc",
    "mu"   :  "[Xi_bc0  -> (Xi_cc+ -> (Lambda_c+ -> p+ K- pi+) K- pi+) ^mu+]cc"
   }

#######################
# Xibc+ --> Xicc+ mu-
#######################
tupleXiccpMu2 = tuple.clone('XiccpMu2')
tupleXiccpMu2.Decay = '[Xi_bc0  -> (^Xi_cc+ -> (^D+ -> ^K- ^pi+ ^pi+) ^p+ ^K-) ^mu-]cc'
tupleXiccpMu2.Branches = {
    "Xb"   :  "[Xi_bc0]cc : [Xi_bc0  -> (Xi_cc+ -> (D+ -> K- pi+ pi+) p+ K-) mu-]cc",   
    "Xcc"  :  "[Xi_bc0  -> (^Xi_cc+ -> (D+ -> K- pi+ pi+) p+ K-) mu-]cc",
    "Xc"   :  "[Xi_bc0  -> (Xi_cc+ -> (^D+ -> K- pi+ pi+) p+ K-) mu-]cc",
    "k"   :   "[Xi_bc0  -> (Xi_cc+ -> (D+ -> ^K- pi+ pi+) p+ K-) mu-]cc",
    "pi1"   :   "[Xi_bc0  -> (Xi_cc+ -> (D+ -> K- ^pi+ pi+) p+ K-) mu-]cc",
    "pi2"   :  "[Xi_bc0  -> (Xi_cc+ -> (D+ -> K- pi+ ^pi+) p+ K-) mu-]cc",
    "P"   :  "[Xi_bc0  -> (Xi_cc+ -> (D+ -> K- pi+ pi+) ^p+ K-) mu-]cc",
    "K"   :  "[Xi_bc0  -> (Xi_cc+ -> (D+ -> K- pi+ pi+) p+ ^K-) mu-]cc",
    "mu"   :  "[Xi_bc0  -> (Xi_cc+ -> (D+ -> K- pi+ pi+) p+ K-) ^mu-]cc"
   }

#######################
# Xibc+ --> Xicc+ mu+
#######################
wstupleXiccpMu2 = tuple.clone('wsXiccpMu2')
wstupleXiccpMu2.Decay = '[Xi_bc0  -> (^Xi_cc+ -> (^D+ -> ^K- ^pi+ ^pi+) ^p+ ^K-) ^mu+]cc'
wstupleXiccpMu2.Branches = {
    "Xb"   :  "[Xi_bc0]cc : [Xi_bc0  -> (Xi_cc+ -> (D+ -> K- pi+ pi+) p+ K-) mu+]cc",   
    "Xcc"  :  "[Xi_bc0  -> (^Xi_cc+ -> (D+ -> K- pi+ pi+) p+ K-) mu+]cc",
    "Xc"   :  "[Xi_bc0  -> (Xi_cc+ -> (^D+ -> K- pi+ pi+) p+ K-) mu+]cc",
    "k"   :   "[Xi_bc0  -> (Xi_cc+ -> (D+ -> ^K- pi+ pi+) p+ K-) mu+]cc",
    "pi1"   : "[Xi_bc0  -> (Xi_cc+ -> (D+ -> K- ^pi+ pi+) p+ K-) mu+]cc",
    "pi2"   : "[Xi_bc0  -> (Xi_cc+ -> (D+ -> K- pi+ ^pi+) p+ K-) mu+]cc",
    "P"   :   "[Xi_bc0  -> (Xi_cc+ -> (D+ -> K- pi+ pi+) ^p+ K-) mu+]cc",
    "K"   :   "[Xi_bc0  -> (Xi_cc+ -> (D+ -> K- pi+ pi+) p+ ^K-) mu+]cc",
    "mu"   :  "[Xi_bc0  -> (Xi_cc+ -> (D+ -> K- pi+ pi+) p+ K-) ^mu+]cc"
   }


