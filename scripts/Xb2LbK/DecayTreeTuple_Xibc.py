#------------------------------------------------------------------------------
# Decay Tree Tuple Configurator
#------------------------------------------------------------------------------
from Configurables import DecayTreeTuple, LoKi__Hybrid__TupleTool, TupleToolDecay, TupleToolTrigger, TupleToolTISTOS
from Configurables import FitDecayTrees, SubstitutePID, TupleToolDecayTreeFitter, BackgroundCategory, TupleToolRecoStats
from DecayTreeTuple.Configuration import *
from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiTool


#######################################
tuple = DecayTreeTuple('xibc')
tuple.Inputs = ["/Event/BhadronCompleteEvent/Phys/Lb2LcKLc2PKPiBeauty2CharmLine/Particles"]
tuple.TupleName = "mytree"
tuple.ToolList = [
       "TupleToolPrimaries",
       "TupleToolGeometry",
       "TupleToolKinematic",
       "TupleToolEventInfo",
       "TupleToolPid",
       "TupleToolTrackInfo",
       "TupleToolPropertime",
       #
       "TupleToolMCTruth"
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
    }


#######################################
tuple.Decay = "[ Xi_bc+ -> ^K- ^(Lambda_c+ -> ^p+ ^K- ^pi+) ]CC"
tuple.Branches = {
    "Xb"   :   "[ Xi_bc+ -> ^K- ^(Lambda_c+ -> ^p+ ^K- ^pi+) ]CC",
    "Pi"    :   "[ Xi_bc+ -> ^K- ^(Lambda_c+ -> ^p+ ^K- ^pi+) ]CC",
    "Lc"    :   "[ Xi_bc+ -> ^K- ^(Lambda_c+ -> ^p+ ^K- ^pi+) ]CC",
    "p"       :   "[ Xi_bc+ -> ^K- ^(Lambda_c+ -> ^p+ ^K- ^pi+) ]CC",
    "k"       :   "[ Xi_bc+ -> ^K- ^(Lambda_c+ -> ^p+ ^K- ^pi+) ]CC",
    "pi"      :   "[ Xi_bc+ -> ^K- ^(Lambda_c+ -> ^p+ ^K- ^pi+) ]CC"
   }
#######################################
tuple.addTool(TupleToolDecay, name="Xb")
tuple.Lb.addTool(tistos)
tuple.Lb.ToolList+=[ "TupleToolPropertime" ]
tuple.Lb.ToolList+=["TupleToolTISTOS/tistos"]
#tuple.lab2.addTool(tistos)
#tuple.lab2.ToolList+=["TupleToolTISTOS/tistos"]
#tuple.addTool(LoKi_track)
#tuple.ToolList += [ "LoKi::Hybrid::TupleTool/LoKi_track" ]
#######################################
tuple.Lb.addTool(LoKi_lab0)
tuple.Lb.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_xib"]
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


'''
May be I need that kind of code too. But right now I am not sure.
#######################################
tuplews = tupleplus.clone("wsxibc")
tuplews.Decay = "[ Xi_bc~- -> ^pi- ^(Lambda_b0 -> ^(Lambda_c+ -> ^p+ ^K- ^pi+) ^pi- ) ]CC"
tuplews.Branches = {
    "Xb"   :  "[ Xi_bc~- -> pi- (Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) pi- ) ]CC",
    "Pi"    :  "[ Xi_bc~- -> ^pi- (Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) pi- ) ]CC",
    "Lb"    :  "[ Xi_bc~- -> pi- ^(Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) pi- ) ]CC",
    "Lc"    :  "[ Xi_bc~- -> pi- (Lambda_b0 -> ^(Lambda_c+ -> p+ K- pi+) pi- ) ]CC",
    "p"       :  "[ Xi_bc~- -> pi- (Lambda_b0 -> (Lambda_c+ -> ^p+ K- pi+) pi- ) ]CC",
    "k"       :  "[ Xi_bc~- -> pi- (Lambda_b0 -> (Lambda_c+ -> p+ ^K- pi+) pi- ) ]CC",
    "pi"      :  "[ Xi_bc~- -> pi- (Lambda_b0 -> (Lambda_c+ -> p+ K- ^pi+) pi- ) ]CC",
    "LbPi"    :  "[ Xi_bc~- -> pi- (Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) ^pi- ) ]CC",
    }
#######################################
'''

