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
from Configurables import FitDecayTrees, TupleToolGeometry, BackgroundCategory

tistos = TupleToolTISTOS("tistos")
tistos.VerboseL0 = 1
tistos.VerboseHlt1 = 1
tistos.VerboseHlt2 = 1
tistos.TriggerList = [
                          'L0DiMuonDecision',
                             'L0HCALDecision',
                             'L0MuonDecision',
                         'L0MuonHighDecision',
               'Hlt1SingleMuonNoIPL0Decision',
                 'Hlt1DiMuonHighMassDecision',
                  'Hlt1DiMuonLowMassDecision',
               'Hlt1SingleMuonHighPTDecision',
                 'Hlt1SingleMuonNoIPDecision',
                     'Hlt1TrackAllL0Decision',
                      'Hlt1TrackMuonDecision',
               'Hlt1SingleMuonNoIPL0Decision',
                        'Hlt2DiMuonBDecision',
                         'Hlt2DiMuonDecision',                        
                      'Hlt2DiMuonDY1Decision',
                 'Hlt2DiMuonDetachedDecision',
            'Hlt2DiMuonDetachedHeavyDecision',
             'Hlt2DiMuonDetachedJPsiDecision',
                     'Hlt2DiMuonJPsiDecision',
               'Hlt2DiMuonJPsiHighPTDecision',
                    'Hlt2ExpressJPsiDecision',
            'Hlt2ExpressJPsiTagProbeDecision',
                     'Hlt2SingleMuonDecision',
               'Hlt2SingleMuonHighPTDecision',
                'Hlt2SingleMuonLowPTDecision',
                  'Hlt2Topo2BodyBBDTDecision',
                  'Hlt2Topo3BodyBBDTDecision',      
                  'Hlt2Topo4BodyBBDTDecision',        
                'Hlt2TopoMu2BodyBBDTDecision',        
                'Hlt2TopoMu3BodyBBDTDecision',      
                'Hlt2TopoMu4BodyBBDTDecision',      
                    'Hlt2TransparentDecision',                           
             'Hlt2DiMuonUnbiasedJPsiDecision'
]


tuple = DecayTreeTuple('X2JpsiXicz') 
tuple.Inputs = [ 'Phys/Bs2Jpsif0' ]
tuple.UseLoKiDecayFinders = False
tuple.TupleName = "mytree"
tuple.ToolList =  [
       "TupleToolGeometry",
       "TupleToolKinematic",
       "TupleToolEventInfo",
#       "TupleToolTISTOS",
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

###########################################################################################################################
# Xibc0 --> J/psi Xic0
#######################
tuple.Decay = '[Xi_bc0  -> (^J/psi(1S) -> ^mu+ ^mu-) (^Xi_c0 -> ^p+ ^K- ^K- ^pi+)]cc'

tuple.Branches = {
    "Xb"   :  "[Xi_bc0]cc : [Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ K- K- pi+) ]cc",
    "Xc"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (^Xi_c0 -> p+ K- K- pi+) ]cc",
    "Pr"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> ^p+ K- K- pi+) ]cc",
    "K1"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ ^K- K- pi+) ]cc",
    "K2"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ K- ^K- pi+) ]cc",
    "Pi"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ K- K- ^pi+) ]cc",
    "Jpsi"   :  "[Xi_bc0 -> (^J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ K- K- pi+) ]cc",
    "mup"   :  "[Xi_bc0 -> (J/psi(1S) -> ^mu+ mu-) (Xi_c0 -> p+ K- K- pi+) ]cc",
    "mum"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ ^mu-) (Xi_c0 -> p+ K- K- pi+) ]cc"
   }

tuple.addTool(TupleToolDecay, name="Xb")
tuple.addTool(TupleToolDecay, name="Jpsi")
tuple.addTool(TupleToolDecay, name="Xc")
tuple.Xb.ToolList = [ "TupleToolPropertime" ]
tuple.Xc.ToolList = [ "TupleToolPropertime" ]

#tuple.Xb.addTool(tistos)
#tuple.Xb.ToolList+=["TupleToolTISTOS/tistos"]
tuple.Jpsi.addTool(tistos)
tuple.Jpsi.ToolList+=["TupleToolTISTOS/tistos"]
#tuple.ReFitPVs = True
LoKi_Xibc=LoKi__Hybrid__TupleTool("LoKi_Xibc")
LoKi_Xibc.Variables =  { 
#        "LOKI_FDCHI2"     : "BPVVDCHI2", 
#        "LOKI_FDS"        : "BPVDLS", 
#        "LOKI_DIRA"       : "BPVDIRA" , 
        "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )", 
#        "LOKI_DTF_CTAUS"       : "DTF_CTAUSIGNIFICANCE( 0, True )", 
        "LOKI_DTF_CHI2NDOF_massConstr"    : "DTF_CHI2NDOF( True, strings('J/psi(1S)') )" ,
        #"LOKI_DTF_CTAUERR"     : "DTF_CTAUERR( 0, True )", 
        "LOKI_MASS_massConstr" : "DTF_FUN ( M , True , strings('J/psi(1S)') )" , 
        "LOKI_DTF_CHI2NDOF"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True  )"  
        } 
tuple.Xb.addTool(LoKi_Xibc)         
tuple.Xb.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_Xibc"] 

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



# Xibc+ --> J/psi Xic+
tupleX2JpsiXicp = tuple.clone('X2JpsiXicp')
tupleX2JpsiXicp.Decay = '[Xi_bc+  -> (^J/psi(1S) -> ^mu+ ^mu-) (^Xi_c+ -> ^p+ ^K- ^pi+)]cc'
tupleX2JpsiXicp.Branches = {
    "Xb"   :  "[Xi_bc+]cc : [Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Xi_c+ -> p+ K- pi+) ]cc",
    "Xc"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (^Xi_c+ -> p+ K- pi+) ]cc",
    "Pr"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Xi_c+ -> ^p+ K- pi+) ]cc",
    "K"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Xi_c+ -> p+ ^K-  pi+) ]cc",
    "Pi"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Xi_c+ -> p+ K- ^pi+) ]cc",
    "Jpsi"   :  "[Xi_bc+ -> (^J/psi(1S) -> mu+ mu-) (Xi_c+ -> p+ K- pi+) ]cc",
    "mup"   :  "[Xi_bc+ -> (J/psi(1S) -> ^mu+ mu-) (Xi_c+ -> p+ K- pi+) ]cc",
    "mum"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ ^mu-) (Xi_c+ -> p+ K- pi+) ]cc"
   }

# Xibc+ --> J/psi Lambdac+
tupleX2JpsiLcp = tuple.clone('X2JpsiLcp')
tupleX2JpsiLcp.Decay = '[Xi_bc+  -> (^J/psi(1S) -> ^mu+ ^mu-) (^Lambda_c+ -> ^p+ ^K- ^pi+)]cc'
tupleX2JpsiLcp.Branches = {
    "Xb"   :  "[Xi_bc+]cc : [Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- pi+) ]cc",
    "Xc"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (^Lambda_c+ -> p+ K- pi+) ]cc",
    "Pr"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> ^p+ K- pi+) ]cc",
    "K"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ ^K-  pi+) ]cc",
    "Pi"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- ^pi+) ]cc",
    "Jpsi"   :  "[Xi_bc+ -> (^J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- pi+) ]cc",
    "mup"   :  "[Xi_bc+ -> (J/psi(1S) -> ^mu+ mu-) (Lambda_c+ -> p+ K- pi+) ]cc",
    "mum"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ ^mu-) (Lambda_c+ -> p+ K- pi+) ]cc"
   }


tupleX2JpsiLcpK = tuple.clone('X2JpsiLcpK')
tupleX2JpsiLcpK.Decay = '[Xi_bc0  -> (^J/psi(1S) -> ^mu+ ^mu-) (^Lambda_c+ -> ^p+ ^K- ^pi+) ^K-]cc'
tupleX2JpsiLcpK.Branches = {
    "Xb"   :  "[Xi_bc0]cc : [Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- pi+) K-]cc",
    "Xc"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (^Lambda_c+ -> p+ K- pi+) K-]cc",
    "Pr"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> ^p+ K- pi+) K-]cc",
    "K"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ ^K-  pi+) K-]cc",
    "Pi"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- ^pi+) K-]cc",
    "Jpsi"   :  "[Xi_bc0 -> (^J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- pi+) K-]cc",
    "mup"   :  "[Xi_bc0 -> (J/psi(1S) -> ^mu+ mu-) (Lambda_c+ -> p+ K- pi+) K-]cc",
    "mum"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ ^mu-) (Lambda_c+ -> p+ K- pi+) K-]cc",
    "Kaon"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- pi+) ^K-]cc"
   }

# Xibc+ --> J/psi Lambdac+
tupleX2JpsiLcKpipi = tuple.clone('X2JpsiLcKpipi')
tupleX2JpsiLcKpipi.Decay = '[B+  -> (^J/psi(1S) -> ^mu+ ^mu-) (^Lambda_c+ -> ^K+ ^pi- ^pi+)]cc'
tupleX2JpsiLcKpipi.Branches = {
    "Xb"   :  "[B+]cc : [B+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> K+ pi- pi+) ]cc",
    "Xc"   :  "[B+ -> (J/psi(1S) -> mu+ mu-) (^Lambda_c+ -> K+ pi- pi+) ]cc",
    "k"   :  "[B+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> ^K+ pi- pi+) ]cc",
    "pi1"   :  "[B+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> K+ ^pi-  pi+) ]cc",
    "pi2"   :  "[B+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> K+ pi- ^pi+) ]cc",
    "Jpsi"   :  "[B+ -> (^J/psi(1S) -> mu+ mu-) (Lambda_c+ -> K+ pi- pi+) ]cc",
    "mup"   :  "[B+ -> (J/psi(1S) -> ^mu+ mu-) (Lambda_c+ -> K+ pi- pi+) ]cc",
    "mum"   :  "[B+ -> (J/psi(1S) -> mu+ ^mu-) (Lambda_c+ -> K+ pi- pi+) ]cc"
   }

# Xibc+ --> J/psi Lambdac+
tupleX2JpsipK = tuple.clone('X2JpsipK')
tupleX2JpsipK.Decay = '[Lambda_b0  -> (^J/psi(1S) -> ^mu+ ^mu-) (^Xi_c0 -> ^p+ ^K-)]cc'
tupleX2JpsipK.Branches = {
    "Xb"   :  "[Lambda_b0]cc : [Lambda_b0  -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ K-)]cc",
    "Xc"   :  "[Lambda_b0  -> (J/psi(1S) -> mu+ mu-) (^Xi_c0 -> p+ K-)]cc",
    "k"   :  "[Lambda_b0  -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ ^K-)]cc",
    "p"   :  "[Lambda_b0  -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> ^p+ K-)]cc",
    "Jpsi"   :  "[Lambda_b0  -> (^J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ K-)]cc",
    "mup"   :  "[Lambda_b0  -> (J/psi(1S) -> ^mu+ mu-) (Xi_c0 -> p+ K-)]cc",
    "mum"   :  "[Lambda_b0  -> (J/psi(1S) -> mu+ ^mu-) (Xi_c0 -> p+ K-)]cc"
   }


#----------------------------------------------------------
#                       Wrong-sign
#----------------------------------------------------------
# Xibc+ --> J/psi Xic0
#----------------------
wstupleX2JpsiXicz = tuple.clone('wsX2JpsiXicz')
wstupleX2JpsiXicz.Decay = '[Xi_bc0  -> (^J/psi(1S) -> ^mu+ ^mu-) (^Xi_c0 -> ^p+ ^K- ^K- ^pi-)]cc'
wstupleX2JpsiXicz.Branches = {
    "Xb"   :  "[Xi_bc0]cc : [Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ K- K- pi-) ]cc",
    "Xc"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (^Xi_c0 -> p+ K- K- pi-) ]cc",
    "Pr"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> ^p+ K- K- pi-) ]cc",
    "K1"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ ^K- K- pi-) ]cc",
    "K2"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ K- ^K- pi-) ]cc",
    "Pi"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ K- K- ^pi-) ]cc",
    "Jpsi"   :  "[Xi_bc0 -> (^J/psi(1S) -> mu+ mu-) (Xi_c0 -> p+ K- K- pi-) ]cc",
    "mup"   :  "[Xi_bc0 -> (J/psi(1S) -> ^mu+ mu-) (Xi_c0 -> p+ K- K- pi-) ]cc",
    "mum"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ ^mu-) (Xi_c0 -> p+ K- K- pi-) ]cc"
   }


#----------------------
# Xibc+ --> J/psi Xic+
#----------------------
wstupleX2JpsiXicp = tuple.clone('wsX2JpsiXicp')
wstupleX2JpsiXicp.Decay = '[Xi_bc+  -> (^J/psi(1S) -> ^mu+ ^mu-) (^Xi_c+ -> ^p+ ^K- ^pi-)]cc'
wstupleX2JpsiXicp.Branches = {
    "Xb"   :  "[Xi_bc+]cc : [Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Xi_c+ -> p+ K- pi-) ]cc",
    "Xc"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (^Xi_c+ -> p+ K- pi-) ]cc",
    "Pr"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Xi_c+ -> ^p+ K- pi-) ]cc",
    "K"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Xi_c+ -> p+ ^K-  pi-) ]cc",
    "Pi"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Xi_c+ -> p+ K- ^pi-) ]cc",
    "Jpsi"   :  "[Xi_bc+ -> (^J/psi(1S) -> mu+ mu-) (Xi_c+ -> p+ K- pi-) ]cc",
    "mup"   :  "[Xi_bc+ -> (J/psi(1S) -> ^mu+ mu-) (Xi_c+ -> p+ K- pi-) ]cc",
    "mum"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ ^mu-) (Xi_c+ -> p+ K- pi-) ]cc"
   }

#---------------------------
# Xibc+ --> J/psi Lambdac+
#---------------------------
wstupleX2JpsiLcp = tuple.clone('wsX2JpsiLcp')
wstupleX2JpsiLcp.Decay = '[Xi_bc+  -> (^J/psi(1S) -> ^mu+ ^mu-) (^Lambda_c+ -> ^p+ ^K- ^pi-)]cc'
wstupleX2JpsiLcp.Branches = {
    "Xb"   :  "[Xi_bc+]cc : [Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- pi-) ]cc",
    "Xc"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (^Lambda_c+ -> p+ K- pi-) ]cc",
    "Pr"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> ^p+ K- pi-) ]cc",
    "K"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ ^K-  pi-) ]cc",
    "Pi"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- ^pi-) ]cc",
    "Jpsi"   :  "[Xi_bc+ -> (^J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- pi-) ]cc",
    "mup"   :  "[Xi_bc+ -> (J/psi(1S) -> ^mu+ mu-) (Lambda_c+ -> p+ K- pi-) ]cc",
    "mum"   :  "[Xi_bc+ -> (J/psi(1S) -> mu+ ^mu-) (Lambda_c+ -> p+ K- pi-) ]cc"
   }


wstupleX2JpsiLcpK = tuple.clone('wsX2JpsiLcpK')
wstupleX2JpsiLcpK.Decay = '[Xi_bc0  -> (^J/psi(1S) -> ^mu+ ^mu-) (^Lambda_c+ -> ^p+ ^K- ^pi+) ^K+]cc'
wstupleX2JpsiLcpK.Branches = {
    "Xb"   :  "[Xi_bc0]cc : [Xi_bc+ -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- pi+) K+]cc",
    "Xc"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (^Lambda_c+ -> p+ K- pi+) K+]cc",
    "Pr"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> ^p+ K- pi+) K+]cc",
    "K"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ ^K-  pi+) K+]cc",
    "Pi"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- ^pi+) K+]cc",
    "Jpsi"   :  "[Xi_bc0 -> (^J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- pi+) K+]cc",
    "mup"   :  "[Xi_bc0 -> (J/psi(1S) -> ^mu+ mu-) (Lambda_c+ -> p+ K- pi+) K+]cc",
    "mum"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ ^mu-) (Lambda_c+ -> p+ K- pi+) K+]cc",
    "Kaon"   :  "[Xi_bc0 -> (J/psi(1S) -> mu+ mu-) (Lambda_c+ -> p+ K- pi+) ^K+]cc"
   }








