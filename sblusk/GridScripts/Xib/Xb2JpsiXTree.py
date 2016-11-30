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


tuple = DecayTreeTuple('X2JpsipKK') 
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
# Xib- --> J/psi p K- K-
###########################
tuple.Decay = '[Xi_b-  -> (^J/psi(1S) -> ^mu+ ^mu-) ^p+ ^K- ^K-]cc'

tuple.Branches = {
    "Xib"   :  "[Xi_b-]cc : [Xi_b-  -> (J/psi(1S) -> mu+ mu-) p+ K- K-]cc",
    "Jpsi"   :  "[Xi_b-  -> (^J/psi(1S) -> mu+ mu-) p+ K- K-]cc",
    "mup"   :  "[Xi_b-  -> (J/psi(1S) -> ^mu+ mu-) p+ K- K-]cc",
    "mum"   :  "[Xi_b-  -> (J/psi(1S) -> mu+ ^mu-) p+ K- K-]cc",
    "p"   :  "[Xi_b-  -> (J/psi(1S) -> mu+ mu-) ^p+ K- K-]cc",
    "K1"   :  "[Xi_b-  -> (J/psi(1S) -> mu+ mu-) p+ ^K- K-]cc",
    "K2"   :  "[Xi_b-  -> (J/psi(1S) -> mu+ mu-) p+ K- ^K-]cc"
   }



tuple.addTool(TupleToolDecay, name="Xib")
tuple.addTool(TupleToolDecay, name="Jpsi")
tuple.Xib.ToolList = [ "TupleToolPropertime" ]
#tuple.Xb.addTool(tistos)
#tuple.Xb.ToolList+=["TupleToolTISTOS/tistos"]
tuple.Jpsi.addTool(tistos)
tuple.Jpsi.ToolList+=["TupleToolTISTOS/tistos"]
#tuple.ReFitPVs = True
LoKi_Xib=LoKi__Hybrid__TupleTool("LoKi_Xib")
LoKi_Xib.Variables =  { 
    "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )", 
    "LOKI_DTF_CHI2NDOF_massConstr"    : "DTF_CHI2NDOF( True, strings('J/psi(1S)','Xi_c0', 'Xi_c+', 'Lambda_c+') )" ,
    "LOKI_MASS_massConstr" : "DTF_FUN ( M , True , strings('J/psi(1S)','Xi_c0', 'Xi_c+', 'Lambda_c+') )" , 
    "LOKI_DTF_CHI2NDOF"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True  )"  
        } 
tuple.Xib.addTool(LoKi_Xib)         
tuple.Xib.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_Xib"] 

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

tupleX2JpsipKKpi = tuple.clone('X2JpsipKKpi')
tupleX2JpsipKKpi.Decay = '[Xi_b0  -> (^J/psi(1S) -> ^mu+ ^mu-) ^p+ ^K- ^K- ^pi+]cc'
tupleX2JpsipKKpi.Branches = {
    "Xib"   :  "[Xi_b0]cc : [Xi_b0  -> (J/psi(1S) -> mu+ mu-) p+ K- K- pi+]cc",
    "Jpsi"   :  "[Xi_b0  -> (^J/psi(1S) -> mu+ mu-) p+ K- K- pi+]cc",
    "mup"   :  "[Xi_b0  -> (J/psi(1S) -> ^mu+ mu-) p+ K- K- pi+]cc",
    "mum"   :  "[Xi_b0  -> (J/psi(1S) -> mu+ ^mu-) p+ K- K- pi+]cc",
    "p"   :  "[Xi_b0  -> (J/psi(1S) -> mu+ mu-) ^p+ K- K- pi+]cc",
    "K1"   :  "[Xi_b0  -> (J/psi(1S) -> mu+ mu-) p+ ^K- K- pi+]cc",
    "K2"   :  "[Xi_b0  -> (J/psi(1S) -> mu+ mu-) p+ K- ^K- pi+]cc",
    "pi"   :  "[Xi_b0  -> (J/psi(1S) -> mu+ mu-) p+ K- K- ^pi+]cc"
   }










