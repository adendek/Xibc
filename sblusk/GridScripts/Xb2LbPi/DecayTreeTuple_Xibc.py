#------------------------------------------------------------------------------
# Decay Tree Tuple Configurator
#------------------------------------------------------------------------------
from Configurables import DecayTreeTuple, LoKi__Hybrid__TupleTool, TupleToolDecay, TupleToolTrigger, TupleToolTISTOS
from Configurables import FitDecayTrees, SubstitutePID, TupleToolDecayTreeFitter, BackgroundCategory, TupleToolRecoStats
from DecayTreeTuple.Configuration import *
from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiTool


#######################################
tuple = DecayTreeTuple('lambdab') 
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
       "TupleToolPropertime",
       #
       #"TupleToolMCTruth",
       #"TupleToolMCBackgroundInfo",
       #
       ]
tistos = TupleToolTISTOS("tistos")
tistos.VerboseL0   = 1
tistos.VerboseHlt1 = 1
tistos.VerboseHlt2 = 1
tistos.TriggerList = [
    'L0DiMuonDecision',
    'L0HCALDecision',
    'L0HadronDecision',
    'L0MuonDecision',
    'L0MuonHighDecision',
    'Hlt2Topo2BodyBBDTDecision',
    'Hlt2Topo2BodySimpleDecision',      
    'Hlt2Topo3BodyBBDTDecision',      
    'Hlt2Topo3BodySimpleDecision',
    'Hlt2Topo4BodyBBDTDecision',        
    'Hlt2Topo4BodySimpleDecision',      
    ]
LoKi_lab0 = LoKi__Hybrid__TupleTool("LoKi_lab0")
LoKi_lab0.Variables =  {
    #"LOKI_ETA"             : "ETA",
    #"LV01"                 : "LV01",
    #"LV02"                 : "LV02",
    #"LOKI_DIRA"            : "BPVDIRA" ,
    "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )",
    "LOKI_FDCHI2"          : "BPVVDCHI2",
    #"LOKI_BPVIPCHI2"       : "BPVIPCHI2()",
    "LOKI_MASS_LcConstr"        : "DTF_FUN ( M ,                  True , 'Lambda_c+')",
    "LOKI_VCHI2NDOF_LcConstr"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True , 'Lambda_c+')",
    "LOKI_CHI2NDOF_LcConstr"    : "DTF_CHI2NDOF( True,'Lambda_c+')"
    }
LoKi_xib = LoKi__Hybrid__TupleTool("LoKi_xib")
LoKi_xib.Variables =  {
    #"LOKI_ETA"             : "ETA",
    "LV01"                 : "LV01",
    "LV02"                 : "LV02",
    "LOKI_DIRA"            : "BPVDIRA" ,
    "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )",
    "LOKI_FDCHI2"           : "BPVVDCHI2",
    "LOKI_BPVIPCHI2"        : "BPVIPCHI2()",
    "LOKI_MASS_LcConstr"        : "DTF_FUN ( M ,                  True , 'Lambda_c+')",
    "LOKI_VCHI2NDOF_LcConstr"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True , 'Lambda_c+')",
    "LOKI_CHI2NDOF_LcConstr"    : "DTF_CHI2NDOF( True,'Lambda_c+')",
    "LOKI_MASS_LcLbConstr"      : "DTF_FUN ( M ,                  True , strings('Lambda_c+','Lambda_b0'))",
    "LOKI_VCHI2NDOF_LcLbConstr" : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True , strings('Lambda_c+','Lambda_b0'))",
    "LOKI_CHI2NDOF_LcLbConstr"  : "DTF_CHI2NDOF( True, strings('Lambda_c+','Lambda_b0'))"
    }
#LoKi_slow = LoKi__Hybrid__TupleTool("LoKi_slow")
#LoKi_slow.Variables = {
#    "LOKI_ETA"             : "ETA",
#    "LOKI_FDCHI2"          : "BPVVDCHI2",
#    "LOKI_BPVIPCHI2"       : "BPVIPCHI2()",
#    "LOKI_TRCLONEDIST"     : "TRCLONEDIST()"
#    }
#LoKi_track = LoKi__Hybrid__TupleTool("LoKi_track")
#LoKi_track.Variables = {
#    "PX_LcConstr"          : "DTF_FUN ( PX ,                  True , 'Lambda_c+')",
#    "PY_LcConstr"          : "DTF_FUN ( PY ,                  True , 'Lambda_c+')",
#    "PZ_LcConstr"          : "DTF_FUN ( PZ ,                  True , 'Lambda_c+')",
#    "M_LcConstr"           : "DTF_FUN ( M ,                  True , 'Lambda_c+')",
#    "PX_LcLbConstr"          : "DTF_FUN ( PX ,                  True , strings('Lambda_c+','Lambda_b0'))",
#    "PY_LcLbConstr"          : "DTF_FUN ( PY ,                  True , strings('Lambda_c+','Lambda_b0'))",
#    "PZ_LcLbConstr"          : "DTF_FUN ( PZ ,                  True , strings('Lambda_c+','Lambda_b0'))",
#    "M_LcLbConstr"           : "DTF_FUN ( M ,                  True , strings('Lambda_c+','Lambda_b0'))"
#}
#######################################






#######################################
tuple.Decay = '[ Lambda_b0 -> ^(Lambda_c+ -> ^p+ ^K- ^pi+) ^pi- ]CC'
tuple.Branches = {
    "Lb"   :  "[ Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) pi- ]CC",
    "Xc"   :  "[ Lambda_b0 -> ^(Lambda_c+ -> p+ K- pi+) pi- ]CC",
    "p"      :  "[ Lambda_b0 -> (Lambda_c+ -> ^p+ K- pi+) pi- ]CC",
    "k"      :  "[ Lambda_b0 -> (Lambda_c+ -> p+ ^K- pi+) pi- ]CC",
    "pi"     :  "[ Lambda_b0 -> (Lambda_c+ -> p+ K- ^pi+) pi- ]CC",
    "Pi"   :  "[ Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) ^pi- ]CC"    
    }
#######################################
tuple.addTool(TupleToolDecay, name="Lb")
tuple.addTool(TupleToolDecay, name="Xc")
tuple.Lb.addTool(tistos)
tuple.Lb.ToolList+=[ "TupleToolPropertime" ]
tuple.Lb.ToolList+=["TupleToolTISTOS/tistos"]
tuple.Xc.ToolList+=[ "TupleToolPropertime" ]
#tuple.Xc.addTool(tistos)
#tuple.Xc.ToolList+=["TupleToolTISTOS/tistos"]
#tuple.addTool(LoKi_track)
#tuple.ToolList += [ "LoKi::Hybrid::TupleTool/LoKi_track" ]
#######################################
tuple.Lb.addTool(LoKi_lab0)         
tuple.Lb.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_lab0"] 
tuple.addTool(LoKiTool , 'MyLoKiTool' )
tuple.ToolList += [ "LoKi::Hybrid::EvtTupleTool/MyLoKiTool" ]
#######################################
tuple.MyLoKiTool.VOID_Variables = { 'nTracks' :  " CONTAINS ('Rec/Track/Best') "  ,
                                     "nLong"  :  " TrSOURCE('Rec/Track/Best', TrLONG) >> TrSIZE "
                                          }
tuple.MyLoKiTool.Preambulo = [
    "from LoKiTracks.decorators import *",
    "from LoKiCore.functions import *"
    ]
#######################################
tuple.ReFitPVs = True
#######################################




#######################################
tupleplus = tuple.clone("xibc")
tupleplus.Decay = "[ Xi_bc+ -> ^pi+ ^(Lambda_b0 -> ^(Lambda_c+ -> ^p+ ^K- ^pi+) ^pi- ) ]CC"
tupleplus.Branches = {
    "Xb"   :  "[ Xi_bc+ -> pi+ (Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) pi- ) ]CC",
    "XbPi"    :  "[ Xi_bc+ -> ^pi+ (Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) pi- ) ]CC",
    "Lb"    :  "[ Xi_bc+ -> pi+ ^(Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) pi- ) ]CC",
    "Xc"    :  "[ Xi_bc+ -> pi+ (Lambda_b0 -> ^(Lambda_c+ -> p+ K- pi+) pi- ) ]CC",
    "p"       :  "[ Xi_bc+ -> pi+ (Lambda_b0 -> (Lambda_c+ -> ^p+ K- pi+) pi- ) ]CC",
    "k"       :  "[ Xi_bc+ -> pi+ (Lambda_b0 -> (Lambda_c+ -> p+ ^K- pi+) pi- ) ]CC",
    "pi"      :  "[ Xi_bc+ -> pi+ (Lambda_b0 -> (Lambda_c+ -> p+ K- ^pi+) pi- ) ]CC",
    "Pi"    :  "[ Xi_bc+ -> pi+ (Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) ^pi- ) ]CC",
   }
#######################################
tupleplus.addTool(TupleToolDecay, name="Xb")
tupleplus.Xb.addTool(LoKi_xib)
tupleplus.Xb.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_xib"]
tupleplus.addTool(LoKiTool , 'MyLoKiTool' )
tupleplus.ToolList += [ "LoKi::Hybrid::EvtTupleTool/MyLoKiTool" ]
#######################################



#######################################
tuplews = tupleplus.clone("wsxibc")
tuplews.Decay = "[ Xi_bc~- -> ^pi- ^(Lambda_b0 -> ^(Lambda_c+ -> ^p+ ^K- ^pi+) ^pi- ) ]CC"
tuplews.Branches = {
    "Xb"   :  "[ Xi_bc~- -> pi- (Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) pi- ) ]CC",
    "XbPi"    :  "[ Xi_bc~- -> ^pi- (Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) pi- ) ]CC",
    "Lb"    :  "[ Xi_bc~- -> pi- ^(Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) pi- ) ]CC",
    "Xc"    :  "[ Xi_bc~- -> pi- (Lambda_b0 -> ^(Lambda_c+ -> p+ K- pi+) pi- ) ]CC",
    "p"       :  "[ Xi_bc~- -> pi- (Lambda_b0 -> (Lambda_c+ -> ^p+ K- pi+) pi- ) ]CC",
    "k"       :  "[ Xi_bc~- -> pi- (Lambda_b0 -> (Lambda_c+ -> p+ ^K- pi+) pi- ) ]CC",
    "pi"      :  "[ Xi_bc~- -> pi- (Lambda_b0 -> (Lambda_c+ -> p+ K- ^pi+) pi- ) ]CC",
    "Pi"    :  "[ Xi_bc~- -> pi- (Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) ^pi- ) ]CC",
    }
#######################################


