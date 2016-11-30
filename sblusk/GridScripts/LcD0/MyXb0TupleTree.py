#------------------------------------------------------------------------------
# Decay Tree Tuple Configurator
#------------------------------------------------------------------------------
from Configurables import DecayTreeTuple, LoKi__Hybrid__TupleTool, TupleToolDecay, TupleToolTrigger, TupleToolTISTOS
from Configurables import FitDecayTrees, SubstitutePID, TupleToolDecayTreeFitter, BackgroundCategory, TupleToolRecoStats
from DecayTreeTuple.Configuration import *
from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiTool


#######################################
tuple = DecayTreeTuple('MyXb0') 
tuple.Inputs = ["/Event/BhadronCompleteEvent/Phys/Lb2LcPiNoIPLc2PKPiBeauty2CharmLine/Particles"]
tuple.TupleName = "mytree"
tuple.ToolList = [                                                   
       "TupleToolPrimaries",
       "TupleToolGeometry",
       "TupleToolKinematic",
       "TupleToolEventInfo",
       "TupleToolPid",
       "TupleToolANNPID",
       "TupleToolTrackInfo",
       "TupleToolRecoStats",
       #"TupleToolPropertime",
       ]
tistos = TupleToolTISTOS("tistos")
tistos.VerboseL0   = 1
tistos.VerboseHlt1 = 1
tistos.VerboseHlt2 = 1
tistos.TriggerList = [
    'L0HadronDecision',
    'Hlt1TrackAllL0Decision',
    'Hlt2Topo2BodyBBDTDecision',
    'Hlt2Topo3BodyBBDTDecision',      
    'Hlt2Topo4BodyBBDTDecision']        
Loki_Lb0 = LoKi__Hybrid__TupleTool("Loki_Lb0")
Loki_Lb0.Variables =  {
    "LOKI_DIRA"            : "BPVDIRA" ,
    "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )",
    "LOKI_FDCHI2"           : "BPVVDCHI2",
    "Loki_Lb0PVIPCHI2"        : "BPVIPCHI2()",
    "LOKI_MASS_D0Constr"        : "DTF_FUN ( M ,                  True , strings('D0','Lambda_c+') )",
    "LOKI_VCHI2NDOF_D0Constr"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True , strings('D0','Lambda_c+'))",
    "LOKI_NDOF"   : "DTF_FUN ( VFASPF(VDOF) , True)",
    "LOKI_CHI2NDOF_D0Constr"    : "DTF_CHI2NDOF( True,strings('D0','Lambda_c+'))",
    }

####################
# Right sign ntuple
####################
tuple.Decay = '[(B+ -> ^(Lambda_c+ -> ^p+ ^K- ^pi+) ^(D0 -> ^K- ^pi+) ), (B- -> ^(Lambda_c~- -> ^p~- ^K+ ^pi-) ^(D0 -> ^K+ ^pi-) ) ]'
tuple.Branches = {
    "Xb"   :  '[(B+ -> (Lambda_c+ -> p+ K- pi+) (D0 -> K- pi+) ), (B- -> (Lambda_c~- -> p~- K+ pi-) (D0 -> K+ pi-) ) ]',
    "Lc"   :  '[(B+ -> ^(Lambda_c+ -> p+ K- pi+) (D0 -> K- pi+) ), (B- -> ^(Lambda_c~- -> p~- K+ pi-) (D0 -> K+ pi-) ) ]',
    "D0"   :  '[(B+ -> (Lambda_c+ -> p+ K- pi+) ^(D0 -> K- pi+) ), (B- -> (Lambda_c~- -> p~- K+ pi-) ^(D0 -> K+ pi-) ) ]',
    "p"   :  '[(B+ -> (Lambda_c+ -> ^p+ K- pi+) (D0 -> K- pi+) ), (B- -> (Lambda_c~- -> ^p~- K+ pi-) (D0 -> K+ pi-) ) ]',
    "k"   :  '[(B+ -> (Lambda_c+ -> p+ ^K- pi+) (D0 -> K- pi+) ), (B- -> (Lambda_c~- -> p~- ^K+ pi-) (D0 -> K+ pi-) ) ]',
    "pi"   :  '[(B+ -> (Lambda_c+ -> p+ K- ^pi+) (D0 -> K- pi+) ), (B- -> (Lambda_c~- -> p~- K+ ^pi-) (D0 -> K+ pi-) ) ]',
    "K"   :  '[(B+ -> (Lambda_c+ -> p+ K- pi+) (D0 -> ^K- pi+) ), (B- -> (Lambda_c~- -> p~- K+ pi-) (D0 -> ^K+ pi-) ) ]',
    "PI"   :  '[(B+ -> (Lambda_c+ -> p+ K- pi+) (D0 -> K- ^pi+) ), (B- -> (Lambda_c~- -> p~- K+ pi-) (D0 -> K+ ^pi-) ) ]'
    }
#######################################
tuple.addTool(TupleToolDecay, name="Xb")
tuple.addTool(TupleToolDecay, name="D0")
tuple.addTool(TupleToolDecay, name="Lc")
tuple.Xb.addTool(Loki_Lb0)
tuple.Xb.ToolList+=["LoKi::Hybrid::TupleTool/Loki_Lb0"]
tuple.Xb.addTool(tistos)
tuple.Xb.ToolList+=[ "TupleToolPropertime" ]
tuple.Xb.ToolList+=["TupleToolTISTOS/tistos"]
tuple.D0.ToolList+=[ "TupleToolPropertime" ]
tuple.Lc.ToolList+=[ "TupleToolPropertime" ]
#######################################
#tuple.addTool(LoKiTool , 'MyLoKiTool' )
#tuple.ToolList += [ "LoKi::Hybrid::EvtTupleTool/MyLoKiTool" ]
#tuple.MyLoKiTool.VOID_Variables = { 'nTracks' :  " CONTAINS ('Rec/Track/Best') "  ,
#                                     "nLong"  :  " TrSOURCE('Rec/Track/Best', TrLONG) >> TrSIZE "
#                                          }
#tuple.MyLoKiTool.Preambulo = [
#    "from LoKiTracks.decorators import *",
#    "from LoKiCore.functions import *"
#    ]
tuple.ReFitPVs = True
#######################################


####################
# Wrong sign ntuple
#######################################
tuplews = tuple.clone("wsMyXb0")
tuplews.Decay = '[(B+ -> ^(Lambda_c+ -> ^p+ ^K- ^pi+) ^(D0 -> ^K+ ^pi-) ), (B- -> ^(Lambda_c~- -> ^p~- ^K+ ^pi-) ^(D0 -> ^K- ^pi+) ) ]'
tuplews.Branches = {
    "Xb"   :  '[(B+ -> (Lambda_c+ -> p+ K- pi+) (D0 -> K+ pi-) ), (B- -> (Lambda_c~- -> p~- K+ pi-) (D0 -> K- pi+) ) ]',
    "Lc"   :  '[(B+ -> ^(Lambda_c+ -> p+ K- pi+) (D0 -> K+ pi-) ), (B- -> ^(Lambda_c~- -> p~- K+ pi-) (D0 -> K- pi+) ) ]',
    "D0"   :  '[(B+ -> (Lambda_c+ -> p+ K- pi+) ^(D0 -> K+ pi-) ), (B- -> (Lambda_c~- -> p~- K+ pi-) ^(D0 -> K- pi+) ) ]',
    "p"   :  '[(B+ -> (Lambda_c+ -> ^p+ K- pi+) (D0 -> K+ pi-) ), (B- -> (Lambda_c~- -> ^p~- K+ pi-) (D0 -> K- pi+) ) ]',
    "k"   :  '[(B+ -> (Lambda_c+ -> p+ ^K- pi+) (D0 -> K+ pi-) ), (B- -> (Lambda_c~- -> p~- ^K+ pi-) (D0 -> K- pi+) ) ]',
    "pi"   :  '[(B+ -> (Lambda_c+ -> p+ K- ^pi+) (D0 -> K+ pi-) ), (B- -> (Lambda_c~- -> p~- K+ ^pi-) (D0 -> K- pi+) ) ]',
    "K"   :  '[(B+ -> (Lambda_c+ -> p+ K- pi+) (D0 -> ^K+ pi-) ), (B- -> (Lambda_c~- -> p~- K+ pi-) (D0 -> ^K- pi+) ) ]',
    "PI"   :  '[(B+ -> (Lambda_c+ -> p+ K- pi+) (D0 -> K+ ^pi-) ), (B- -> (Lambda_c~- -> p~- K+ pi-) (D0 -> K- ^pi+) ) ]'
    }


#######################################


