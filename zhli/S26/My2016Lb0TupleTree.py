#------------------------------------------------------------------------------
# Decay Tree Tuple Configurator
#------------------------------------------------------------------------------
from Configurables import DecayTreeTuple, LoKi__Hybrid__TupleTool, TupleToolDecay, TupleToolTrigger, TupleToolTISTOS
from Configurables import FitDecayTrees, SubstitutePID, TupleToolDecayTreeFitter, BackgroundCategory, TupleToolRecoStats
from DecayTreeTuple.Configuration import *
from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiTool


#######################################
tuple = DecayTreeTuple('MyLb0') 
#tuple.Inputs = ["/Event/BhadronCompleteEvent/Phys/Lb2LcPiNoIPLc2PKPiBeauty2CharmLine/Particles"]
tuple.Inputs = ["Phys/Lb2LcPiNoIPLc2PKPiBeauty2CharmLine/Particles"]
tuple.TupleName = "mytree"
tuple.ToolList = [                                                   
#       "TupleToolPrimaries",
       "TupleToolGeometry",
       "TupleToolKinematic",
       "TupleToolEventInfo",
       "TupleToolPid",
       "TupleToolTrackInfo",
       "TupleToolRecoStats",
       "TupleToolANNPID",
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
    "LOKI_MASS_D0Constr"        : "DTF_FUN ( M ,                  True , 'D0')",
    "LOKI_VCHI2NDOF_D0Constr"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True , 'D0')",
    "LOKI_NDOF"   : "DTF_FUN ( VFASPF(VDOF) , True)",
    "LOKI_CHI2NDOF_D0Constr"    : "DTF_CHI2NDOF( True,'D0')",
    }

####################
# Right sign ntuple D0ppi
####################
tuple.Decay = '[(Lambda_b0 -> ^(D0 -> ^K- ^pi+)  ^(Sigma0 -> ^p+ ^pi-)), (Lambda_b0 -> ^(D0 -> ^K+ ^pi-)  ^(Sigma0 -> ^p~- ^pi+)) ]'
tuple.Branches = {
    "Xb"   :  "[(Lambda_b0 -> (D0 -> K- pi+)  (Sigma0 -> p+ pi-)), (Lambda_b0 -> (D0 -> K+ pi-)  (Sigma0 -> p~- pi+)) ]",
    "D"     :  "[(Lambda_b0 -> ^(D0 -> K- pi+)  (Sigma0 -> p+ pi-)), (Lambda_b0 -> ^(D0 -> K+ pi-)  (Sigma0 -> p~- pi+)) ]",
    "R"    :  "[(Lambda_b0 -> (D0 -> K- pi+)  ^(Sigma0 -> p+ pi-)), (Lambda_b0 -> (D0 -> K+ pi-)  ^(Sigma0 -> p~- pi+)) ]",
    "K"   :  "[(Lambda_b0 -> (D0 -> ^K- pi+)  (Sigma0 -> p+ pi-)), (Lambda_b0 -> (D0 -> ^K+ pi-)  (Sigma0 -> p~- pi+)) ]",
    "Rpi"   :  "[(Lambda_b0 -> (D0 -> K- pi+)  (Sigma0 -> p+ ^pi-)), (Lambda_b0 -> (D0 -> K+ pi-)  (Sigma0 -> p~- ^pi+)) ]",
    "pi"    :  "[(Lambda_b0 -> (D0 -> K- ^pi+)  (Sigma0 -> p+ pi-)), (Lambda_b0 -> (D0 -> K+ ^pi-)  (Sigma0 -> p~- pi+)) ]",
    "Rp"     :  "[(Lambda_b0 -> (D0 -> K- pi+)  (Sigma0 -> ^p+ pi-)), (Lambda_b0 -> (D0 -> K+ pi-)  (Sigma0 -> ^p~- pi+)) ]",
    }
####################
# Right sign ntuple
####################
# tuple.Decay = '[(Lambda_b0 -> ^(D0 -> ^K- ^pi+)  ^(Sigma0 -> ^p+ ^K-)), (Lambda_b0 -> ^(D0 -> ^K+ ^pi-)  ^(Sigma0 -> ^p~- ^K+)) ]'
# tuple.Branches = {
#     "Xb"   :  "[(Lambda_b0 -> (D0 -> K- pi+)  (Sigma0 -> p+ K-)), (Lambda_b0 -> (D0 -> K+ pi-)  (Sigma0 -> p~- K+)) ]",
#     "D"     :  "[(Lambda_b0 -> ^(D0 -> K- pi+)  (Sigma0 -> p+ K-)), (Lambda_b0 -> ^(D0 -> K+ pi-)  (Sigma0 -> p~- K+)) ]",
#     "R"    :  "[(Lambda_b0 -> (D0 -> K- pi+)  ^(Sigma0 -> p+ K-)), (Lambda_b0 -> (D0 -> K+ pi-)  ^(Sigma0 -> p~- K+)) ]",
#     "K"   :  "[(Lambda_b0 -> (D0 -> ^K- pi+)  (Sigma0 -> p+ K-)), (Lambda_b0 -> (D0 -> ^K+ pi-)  (Sigma0 -> p~- K+)) ]",
#     "RK"   :  "[(Lambda_b0 -> (D0 -> K- pi+)  (Sigma0 -> p+ ^K-)), (Lambda_b0 -> (D0 -> K+ pi-)  (Sigma0 -> p~- ^K+)) ]",
#     "pi"    :  "[(Lambda_b0 -> (D0 -> K- ^pi+)  (Sigma0 -> p+ K-)), (Lambda_b0 -> (D0 -> K+ ^pi-)  (Sigma0 -> p~- K+)) ]",
#     "Rp"     :  "[(Lambda_b0 -> (D0 -> K- pi+)  (Sigma0 -> ^p+ K-)), (Lambda_b0 -> (D0 -> K+ pi-)  (Sigma0 -> ^p~- K+)) ]",
#     }
#######################################
tuple.addTool(TupleToolDecay, name="Xb")
tuple.addTool(TupleToolDecay, name="D")
tuple.Xb.addTool(Loki_Lb0)
tuple.Xb.ToolList+=["LoKi::Hybrid::TupleTool/Loki_Lb0"]
tuple.Xb.addTool(tistos)
tuple.Xb.ToolList+=[ "TupleToolPropertime" ]
tuple.Xb.ToolList+=["TupleToolTISTOS/tistos"]
tuple.D.ToolList+=[ "TupleToolPropertime" ]
# tuple.L0.ToolList+=[ "TupleToolPropertime" ]
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
# Wrong sign ntuple D0ppi
#######################################
tuplews = tuple.clone("wsMyLb0")
tuplews.Decay = '[(Lambda_b0 -> ^(D0 -> ^K- ^pi+)  ^(Sigma0 -> ^p~- ^pi+)), (Lambda_b0 -> ^(D0 -> ^K+ ^pi-)  ^(Sigma0 -> ^p+ ^pi-)) ]'
tuplews.Branches = {
    "Xb"   :  "[(Lambda_b0 -> (D0 -> K- pi+)  (Sigma0 -> p~- pi+)), (Lambda_b0 -> (D0 -> K+ pi-)  (Sigma0 -> p+ pi-)) ]",
    "D"     :  "[(Lambda_b0 -> ^(D0 -> K- pi+)  (Sigma0 -> p~- pi+)), (Lambda_b0 -> ^(D0 -> K+ pi-)  (Sigma0 -> p+ pi-)) ]",
    "R"    :  "[(Lambda_b0 -> (D0 -> K- pi+)  ^(Sigma0 -> p~- pi+)), (Lambda_b0 -> (D0 -> K+ pi-)  ^(Sigma0 -> p+ pi-)) ]",
    "K"   :  "[(Lambda_b0 -> (D0 -> ^K- pi+)  (Sigma0 -> p~- pi+)), (Lambda_b0 -> (D0 -> ^K+ pi-)  (Sigma0 -> p+ pi-)) ]",
    "Rpi"   :  "[(Lambda_b0 -> (D0 -> K- pi+)  (Sigma0 -> p~- ^pi+)), (Lambda_b0 -> (D0 -> K+ pi-)  (Sigma0 -> p+ ^pi-)) ]",
    "pi"    :  "[(Lambda_b0 -> (D0 -> K- ^pi+)  (Sigma0 -> p~- pi+)), (Lambda_b0 -> (D0 -> K+ ^pi-)  (Sigma0 -> p+ pi-)) ]",
    "Rp"     :  "[(Lambda_b0 -> (D0 -> K- pi+)  (Sigma0 -> ^p~- pi+)), (Lambda_b0 -> (D0 -> K+ pi-)  (Sigma0 -> ^p+ pi-)) ]",
    }
####################
# Wrong sign ntuple D0pK
#######################################
# tuplews = tuple.clone("wsMyLb0")
# tuplews.Decay = '[(Lambda_b0 -> ^(D0 -> ^K- ^pi+)  ^(Sigma0 -> ^p~- ^K+)), (Lambda_b0 -> ^(D0 -> ^K+ ^pi-)  ^(Sigma0 -> ^p+ ^K-)) ]'
# tuplews.Branches = {
#     "Xb"   :  "[(Lambda_b0 -> (D0 -> K- pi+)  (Sigma0 -> p~- K+)), (Lambda_b0 -> (D0 -> K+ pi-)  (Sigma0 -> p+ K-)) ]",
#     "D"     :  "[(Lambda_b0 -> ^(D0 -> K- pi+)  (Sigma0 -> p~- K+)), (Lambda_b0 -> ^(D0 -> K+ pi-)  (Sigma0 -> p+ K-)) ]",
#     "R"    :  "[(Lambda_b0 -> (D0 -> K- pi+)  ^(Sigma0 -> p~- K+)), (Lambda_b0 -> (D0 -> K+ pi-)  ^(Sigma0 -> p+ K-)) ]",
#     "K"   :  "[(Lambda_b0 -> (D0 -> ^K- pi+)  (Sigma0 -> p~- K+)), (Lambda_b0 -> (D0 -> ^K+ pi-)  (Sigma0 -> p+ K-)) ]",
#     "RK"   :  "[(Lambda_b0 -> (D0 -> K- pi+)  (Sigma0 -> p~- ^K+)), (Lambda_b0 -> (D0 -> K+ pi-)  (Sigma0 -> p+ ^K-)) ]",
#     "pi"    :  "[(Lambda_b0 -> (D0 -> K- ^pi+)  (Sigma0 -> p~- K+)), (Lambda_b0 -> (D0 -> K+ ^pi-)  (Sigma0 -> p+ K-)) ]",
#     "Rp"     :  "[(Lambda_b0 -> (D0 -> K- pi+)  (Sigma0 -> ^p~- K+)), (Lambda_b0 -> (D0 -> K+ pi-)  (Sigma0 -> ^p+ K-)) ]",
#     }
#######################################


