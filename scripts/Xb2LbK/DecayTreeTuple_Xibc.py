#------------------------------------------------------------------------------
# Decay Tree Tuple Configurator
#------------------------------------------------------------------------------
from Configurables import DecayTreeTuple, LoKi__Hybrid__TupleTool, TupleToolDecay, TupleToolTrigger, TupleToolTISTOS
from Configurables import FitDecayTrees, SubstitutePID, TupleToolDecayTreeFitter, BackgroundCategory, TupleToolRecoStats
from DecayTreeTuple.Configuration import *
from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiTool


#######################################
# file created by Adam Dendek
# http://cern.ch/go/8Bds
#
# I based on file Xb2LbPi/DecayTreeTuple_Xibc.py
#
#######################################

tuple = DecayTreeTuple('lambdab')
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

#######################################
tuple.Decay = '[ Lambda_b0 -> ^(Lambda_c+ -> ^p+ ^K- ^pi+) ^K- ]CC'
tuple.Branches = {
    "Xb"   :  "[ Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) K- ]CC",
    "Xc"   :  "[ Lambda_b0 -> ^(Lambda_c+ -> p+ K- pi+) K- ]CC",
    "p"      :  "[ Lambda_b0 -> (Lambda_c+ -> ^p+ K- pi+) K- ]CC",
    "k"      :  "[ Lambda_b0 -> (Lambda_c+ -> p+ ^K- pi+) K- ]CC",
    "pi"     :  "[ Lambda_b0 -> (Lambda_c+ -> p+ K- ^pi+) K- ]CC",
    "XcK"   :  "[ Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) ^K- ]CC"
    }
#######################################
tuple.addTool(TupleToolDecay, name="Xb")
tuple.addTool(TupleToolDecay, name="Xc")
tuple.Xb.addTool(tistos)
tuple.Xb.ToolList+=[ "TupleToolPropertime" ]
tuple.Xb.ToolList+=["TupleToolTISTOS/tistos"]
#######################################
tuple.Xb.addTool(LoKi_lab0)
tuple.Xb.ToolList+=["LoKi::Hybrid::TupleTool/LoKi_lab0"]
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

tuplews = tuple.clone("wsLambdab")
tuple.Inputs = ["/Event/BhadronCompleteEvent/Phys/Lb2LcKWSLc2PKPiBeauty2CharmLine/Particles"]
tuplews.Decay = '[Lambda_b0 -> ^(Lambda_c+ -> p+ K- pi+) ^K+]CC'
tuplews.Branches = {
    "Xb"   :  "[Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) K+]CC",
    "Xc"   :  "[ Lambda_b0 -> ^(Lambda_c+ -> p+ K- pi+) K+ ]CC",
    "p"      :  "[ Lambda_b0 -> (Lambda_c+ -> ^p+ K- pi+) K+ ]CC",
    "k"      :  "[ Lambda_b0 -> (Lambda_c+ -> p+ ^K- pi+) K+ ]CC",
    "pi"     :  "[ Lambda_b0 -> (Lambda_c+ -> p+ K- ^pi+) K+ ]CC",
    "XcK"   :  "[ Lambda_b0 -> (Lambda_c+ -> p+ K- pi+) ^K+ ]CC"
    }
