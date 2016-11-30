#!/bin/bash

# Location of calibrated PID PDFs
EOSDIR=root://eoslhcb.cern.ch//eos/lhcb/user/p/poluekt/PID/ProbNNp/

# Location of the simulated ROOT file (change this to your own file)
INPUTFILE=../../../../Erasmus_v9r2/Phys/Lb2Dph/python/010_tuple_filter/out/histsim12_mu.root

# Name of the tree in the ROOT file
INPUTTREE=lb2dph_filt

# Name of the output file
OUTFILE=out.root

# Variable names in the input tree (Pt, Eta and the number of tracks are needed)
PTVAR=p_PT
ETAVAR=p_ETA
NTRVAR=nTracks

# Lower bound on the PID variable
# Needed if the MC simulated data already have the PID cut. 
LOWPID=0.1

# 
PIDVAR=p_ProbNNp_gen
CALIBFILE=$EOSDIR/P_MagUp_2012_distrib.root
python PIDGen.py -i $INPUTFILE -t $INPUTTREE -o tmp1.root -p $PIDVAR -m $PTVAR -e $ETAVAR -n $NTRVAR -l $LOWPID -c $CALIBFILE

PIDVAR=p_ProbNNp_gen_syst1
CALIBFILE=$EOSDIR/P_MagUp_2012_syst_1.root
python PIDGen.py -i tmp1.root -t $INPUTTREE -o tmp2.root -p $PIDVAR -m $PTVAR -e $ETAVAR -n $NTRVAR -l $LOWPID -c $CALIBFILE
rm tmp1.root

PIDVAR=p_ProbNNp_gen_stat1
CALIBFILE=$EOSDIR/P_MagUp_2012_stat_1.root
python PIDGen.py -i tmp2.root -t $INPUTTREE -o $OUTFILE -p $PIDVAR -m $PTVAR -e $ETAVAR -n $NTRVAR -l $LOWPID -c $CALIBFILE
rm tmp2.root
