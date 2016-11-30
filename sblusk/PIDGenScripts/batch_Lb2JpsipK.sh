#!/bin/bash

# Location of the simulated ROOT file (change this to your own file)
INPUTDIR=/afs/cern.ch/work/s/sblusk/public/Xibc/mc/
FILEBASE=Lb2JpsipK
INPUTFILE1=$INPUTDIR/$FILEBASE.root
INPUTFILE2=$INPUTDIR/$FILEBASE.p.root

# Name of the tree in your ROOT file
INPUTTREE=mytree

# Name of the output file
OUTFILE1=$INPUTDIR/$FILEBASE.p.root
OUTFILE2=$INPUTDIR/$FILEBASE.pk.root
#OUTFILE=out.root


# Variable names in the input tree (Pt, Eta and the number of tracks are needed)
PTVAR1=p_PT
ETAVAR1=p_ETA
PTVAR2=k_PT
ETAVAR2=k_ETA

NTRVAR=nTracks

# Lower bound on the PID variable
# Needed if the MC simulated data already have the PID cut. 
# If not specified, equals to lower limit of parametrised PID distribution. 
# Comment it out if there is no PID requirement in your ntuple. 
#
LOWPID1=0.1
LOWPID2=0.1

# Name of resulting resampled variable 
PIDVAR1=p_V3ProbNNp
PIDVAR2=k_V3ProbNNk
#PIDVAR3=pi_V3ProbNNpi

# PID configuration to resample (in the form [particle]_[variable] )
# All available configurations can be viewed by running 'python PIDGen_new.py' without command line parameters
CONFIG1=p_V3ProbNNp
CONFIG2=K_V3ProbNNK
#CONFIG3=pi_V3ProbNNpi
#CONFIG4=K_V3ProbNNK
#CONFIG5=pi_V3ProbNNpi

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
python PIDGen_new.py -i $INPUTFILE1 -t $INPUTTREE -o $OUTFILE1 -p $PIDVAR1 -m $PTVAR1 -e $ETAVAR1 -n $NTRVAR -l $LOWPID1 -c $CONFIG1 -d $DATASET -v $VARIANT
python PIDGen_new.py -i $INPUTFILE2 -t $INPUTTREE -o $OUTFILE2 -p $PIDVAR2 -m $PTVAR2 -e $ETAVAR2 -n $NTRVAR -l $LOWPID2 -c $CONFIG2 -d $DATASET -v $VARIANT
#python PIDGen_new.py -i $INPUTFILE3 -t $INPUTTREE -o $OUTFILE3 -p $PIDVAR3 -m $PTVAR3 -e $ETAVAR3 -n $NTRVAR -l $LOWPID3 -c $CONFIG3 -d $DATASET -v $VARIANT
#python PIDGen_new.py -i $INPUTFILE4 -t $INPUTTREE -o $OUTFILE4 -p $PIDVAR4 -m $PTVAR4 -e $ETAVAR4 -n $NTRVAR -l $LOWPID4 -c $CONFIG4 -d $DATASET -v $VARIANT
#python PIDGen_new.py -i $INPUTFILE5 -t $INPUTTREE -o $OUTFILE5 -p $PIDVAR5 -m $PTVAR5 -e $ETAVAR5 -n $NTRVAR -l $LOWPID5 -c $CONFIG5 -d $DATASET -v $VARIANT
