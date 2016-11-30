#------------------------------------------------------------------------------
# Decay Tree Tuple Configurator
#------------------------------------------------------------------------------
from Configurables import DecayTreeTuple, LoKi__Hybrid__TupleTool, TupleToolDecay, TupleToolTrigger, TupleToolTISTOS
from Configurables import FitDecayTrees, SubstitutePID, TupleToolDecayTreeFitter, BackgroundCategory, TupleToolRecoStats
from DecayTreeTuple.Configuration import *
from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiTool


#######################################
tuple = DecayTreeTuple('Xibc2D0p') 
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
       "TupleToolVtxIsoln",
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
LoKi_B = LoKi__Hybrid__TupleTool("LoKi_B")
LoKi_B.Variables =  {
    "LOKI_DIRA"            : "BPVDIRA" ,
    "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )",
    "LOKI_FDCHI2"           : "BPVVDCHI2",
    "LOKI_BPVIPCHI2"        : "BPVIPCHI2()",
    "LOKI_MASS_D0Constr"        : "DTF_FUN ( M ,                  True , 'D0')",
    "LOKI_VCHI2NDOF_D0Constr"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True , 'D0')",
    "LOKI_CHI2NDOF_D0Constr"    : "DTF_CHI2NDOF( True,'D0')",
    }

####################
# Right sign ntuple
####################
tuple.Decay = '[(B+ -> ^(D0 -> ^K- ^pi+) ^p+), (B- -> ^(D0 -> ^K+ ^pi-) ^p~-) ]'
tuple.Branches = {
    "Xb"   :  "[(B+ -> (D0 -> K- pi+) p+), (B- -> (D0 -> K+ pi-) p~-) ]",
    "Xc"   :  "[(B+ -> ^(D0 -> K- pi+) p+), (B- -> ^(D0 -> K+ pi-) p~-) ]",
    "k"   :  "[(B+ -> (D0 -> ^K- pi+) p+), (B- -> (D0 -> ^K+ pi-) p~-) ]",
    "pi"   :  "[(B+ -> (D0 -> K- ^pi+) p+), (B- -> (D0 -> K+ ^pi-) p~-) ]",
    "p"   :  "[(B+ -> (D0 -> K- pi+) ^p+), (B- -> (D0 -> K+ pi-) ^p~-) ]"
    }
#######################################
tuple.addTool(TupleToolDecay, name="Xb")
tuple.addTool(TupleToolDecay, name="Xc")
tuple.Xb.addTool(LoKi_B)
tuple.Xb.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_B"]
tuple.Xb.addTool(tistos)
tuple.Xb.ToolList+=[ "TupleToolPropertime" ]
tuple.Xb.ToolList+=["TupleToolTISTOS/tistos"]
tuple.Xc.ToolList+=[ "TupleToolPropertime" ]
#######################################
tuple.addTool(LoKiTool , 'MyLoKiTool' )
tuple.ToolList += [ "LoKi::Hybrid::EvtTupleTool/MyLoKiTool" ]
tuple.MyLoKiTool.VOID_Variables = { 'nTracks' :  " CONTAINS ('Rec/Track/Best') "  ,
                                     "nLong"  :  " TrSOURCE('Rec/Track/Best', TrLONG) >> TrSIZE "
                                          }
tuple.MyLoKiTool.Preambulo = [
    "from LoKiTracks.decorators import *",
    "from LoKiCore.functions import *"
    ]
tuple.ReFitPVs = True
#######################################

#
# Control channel
#
tupleD0pi = tuple.clone("B2D0pi")
tupleD0pi.Decay = '[(B- -> ^(D0 -> ^K- ^pi+) ^pi-), (B+ -> ^(D0 -> ^K+ ^pi-) ^pi+) ]'
tupleD0pi.Branches = {
    "Xb"   :  "[(B- -> (D0 -> K- pi+) pi-), (B+ -> (D0 -> K+ pi-) pi+) ]",
    "Xc"   :  "[(B- -> ^(D0 -> K- pi+) pi-), (B+ -> ^(D0 -> K+ pi-) pi+) ]",
    "k"   :  "[(B- -> (D0 -> ^K- pi+) pi-), (B+ -> (D0 -> ^K+ pi-) pi+) ]",
    "pi"   :  "[(B- -> (D0 -> K- ^pi+) pi-), (B+ -> (D0 -> K+ ^pi-) pi+) ]",
    "PI"   :  "[(B- -> (D0 -> K- pi+) ^pi-), (B+ -> (D0 -> K+ pi-) ^pi+) ]"
    }


####################
# Wrong sign ntuple
#######################################
tuplews = tuple.clone("wsXibc2D0p")
tuplews.Decay = '[(B- -> ^(D0 -> ^K- ^pi+) ^p~-), (B+ -> ^(D0 -> ^K+ ^pi-) ^p+) ]'
tuplews.Branches = {
    "Xb"   :  "[(B- -> (D0 -> K- pi+) p~-), (B+ -> (D0 -> K+ pi-) p+) ]",
    "Xc"   :  "[(B- -> ^(D0 -> K- pi+) p~-), (B+ -> ^(D0 -> K+ pi-) p+) ]",
    "k"   :  "[(B- -> (D0 -> ^K- pi+) p~-), (B+ -> (D0 -> ^K+ pi-) p+) ]",
    "pi"   :  "[(B- -> (D0 -> K- ^pi+) p~-), (B+ -> (D0 -> K+ ^pi-) p+) ]",
    "p"   :  "[(B- -> (D0 -> K- pi+) ^p~-), (B+ -> (D0 -> K+ pi-) ^p+) ]"
    }


#######################################


