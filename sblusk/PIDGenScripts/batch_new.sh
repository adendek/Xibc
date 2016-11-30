#!/bin/bash

# Location of the simulated ROOT file (change this to your own file)
INPUTDIR=/afs/cern.ch/work/s/sblusk//XibStarStar/mc/
INPUTFILE1=$INPUTDIR/XibStar0_MC.tuned.root
INPUTFILE2=$INPUTDIR/XibStar0_MC.tuned.p.root
INPUTFILE3=$INPUTDIR/XibStar0_MC.tuned.pk.root

#INPUTFILE=/afs/cern.ch/user/p/poluekt/work/analysis/Lb2Dph/python/010_tuple_filter/out/histsim12_mu.root

# Name of the tree in your ROOT file
#INPUTTREE=lb2dph_filt
INPUTTREE=mytree

# Name of the output file
OUTFILE1=$INPUTDIR/XibStar0_MC.tuned.p.root
OUTFILE2=$INPUTDIR/XibStar0_MC.tuned.pk.root
OUTFILE3=$INPUTDIR/XibStar0_MC.tuned.pkk.root
#OUTFILE=out.root


# Variable names in the input tree (Pt, Eta and the number of tracks are needed)
PTVAR1=XicP_PT
ETAVAR1=XicP_ETA
PTVAR2=XicK1_PT
ETAVAR2=XicK1_ETA
PTVAR3=XicK2_PT
ETAVAR3=XicK2_ETA
NTRVAR=nTracks

# Lower bound on the PID variable
# Needed if the MC simulated data already have the PID cut. 
# If not specified, equals to lower limit of parametrised PID distribution. 
# Comment it out if there is no PID requirement in your ntuple. 
#
LOWPID=0.1

# Name of resulting resampled variable 
PIDVAR1=Pr_V3ProbNNp
PIDVAR2=K1_V3ProbNNk
PIDVAR3=K2_V3ProbNNk

# PID configuration to resample (in the form [particle]_[variable] )
# All available configurations can be viewed by running 'python PIDGen_new.py' without command line parameters
CONFIG1=p_V3ProbNNp
CONFIG2=K_V3ProbNNK
CONFIG3=K_V3ProbNNK

# Dataset, can be {MagUp,MagDown}_{2011,2012}
DATASET=MagUp_2012

# Variant of the parametrised PID PDF. 
# Possible values: "default", "syst_N", "stat_N"
#   "default" - default PDF, use this as a rule
#   "syst_N" - Systematic variation to estimate uncertainty due to kernel estimator used
#   "stat_N" - PDF obtained from bootstrapped sample to estimate uncertainty due to limited calibration sample
# N can vary, for some variables none of the bootstrapped samples are yet available
# If this option is omitted, "default" is used
VARIANT=default

# Run the script
python PIDGen_new.py -i $INPUTFILE1 -t $INPUTTREE -o $OUTFILE1 -p $PIDVAR1 -m $PTVAR1 -e $ETAVAR1 -n $NTRVAR -l $LOWPID -c $CONFIG1 -d $DATASET -v $VARIANT
python PIDGen_new.py -i $INPUTFILE2 -t $INPUTTREE -o $OUTFILE2 -p $PIDVAR2 -m $PTVAR2 -e $ETAVAR2 -n $NTRVAR -l $LOWPID -c $CONFIG2 -d $DATASET -v $VARIANT
python PIDGen_new.py -i $INPUTFILE3 -t $INPUTTREE -o $OUTFILE3 -p $PIDVAR3 -m $PTVAR3 -e $ETAVAR3 -n $NTRVAR -l $LOWPID -c $CONFIG3 -d $DATASET -v $VARIANT
