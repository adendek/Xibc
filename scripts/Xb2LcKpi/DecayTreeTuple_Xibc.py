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

tuple = DecayTreeTuple('MyXb0')
tuple.Inputs = ["/Event/BhadronCompleteEvent/Phys/Lb2LcKLc2PKPiBeauty2CharmLine/Particles"]
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
    'L0MuonHighDecision'
    ]
LoKi_lab0 = LoKi__Hybrid__TupleTool("LoKi_lab0")
LoKi_lab0.Variables =  {
    "LOKI_DIRA"            : "BPVDIRA" ,
    "LOKI_DTF_CTAU"        : "DTF_CTAU( 0, True )",
    "LOKI_FDCHI2"          : "BPVVDCHI2",
    "LOKI_MASS_massConstr"        : "DTF_FUN ( M ,                  True , 'Lambda_c+')",
    "LOKI_VCHI2NDOF_LcConstr"   : "DTF_FUN ( VFASPF(VCHI2/VDOF) , True , 'Lambda_c+')",
    "LOKI_CHI2NDOF_LcConstr"    : "DTF_CHI2NDOF( True,'Lambda_c+')"
    }

#######################################
tuple.Decay = '[ B+ -> ^(Lambda_c+ -> ^p+ ^K- ^pi+) ^K- ^pi+]CC'
tuple.Branches = {
    "Xb"   :  "[ B+ -> (Lambda_c+ -> p+ K- pi+) K- pi+]CC",
    "Xc"   :  "[ B+ -> ^(Lambda_c+ -> p+ K- pi+) K- pi+]CC",
    "p"      :  "[ B+ -> (Lambda_c+ -> ^p+ K- pi+) K- pi+]CC",
    "k"      :  "[ B+ -> (Lambda_c+ -> p+ ^K- pi+) K- pi+]CC",
    "pi"     :  "[ B+ -> (Lambda_c+ -> p+ K- ^pi+) K- pi+]CC",
    "K"   :  "[ B+ -> (Lambda_c+ -> p+ K- pi+) ^K- pi+]CC",
    "PI"   :  "[ B+ -> (Lambda_c+ -> p+ K- pi+) K- ^pi+]CC"
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
tuple.Xc.ToolList+= ["TupleToolPropertime"]
#######################################
tuple.ReFitPVs = True
#######################################

tuplews = tuple.clone("MyXb0_ws")
tuplews.Inputs = ["/Event/BhadronCompleteEvent/Phys/Lb2LcKWSLc2PKPiBeauty2CharmLine/Particles"]
tuplews.Decay = '[ B- -> ^(Lambda_c+ -> ^p+ ^K- ^pi+) ^K- ^pi-]CC'
tuplews.Branches = {
    "Xb"   :   "[ B- -> (Lambda_c+ -> p+ K- pi+) K- pi-]CC",
    "Xc"   :   "[ B- -> ^(Lambda_c+ -> p+ K- pi+) K- pi-]CC",
    "p"      : "[ B- -> (Lambda_c+ -> ^p+ K- pi+) K- pi-]CC",
    "k"      : "[ B- -> (Lambda_c+ -> p+ ^K- pi+) K- pi-]CC",
    "pi"     : "[ B- -> (Lambda_c+ -> p+ K- ^pi+) K- pi-]CC",
    "K"   :    "[ B- -> (Lambda_c+ -> p+ K- pi+) ^K- pi-]CC",
    "PI"   :   "[ B- -> (Lambda_c+ -> p+ K- pi+) K- ^pi-]CC"
    }


