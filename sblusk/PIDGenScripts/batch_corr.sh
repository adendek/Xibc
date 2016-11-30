#!/bin/bash

# Name of the input tree
INPUTTREE=lb2lch_filt

PDFCORR="python PIDCorr.py"

KK_OPTIONS="-t $INPUTTREE -l 0. -p lk_V3ProbNNK_corr -m lk_pt -e lk_eta -n nTracks -s lk_V3ProbNNK -c K_V3ProbNNK -d MagDown_2012"
KPI_OPTIONS="-t $INPUTTREE -l 0.  -p lk_V3ProbNNpi_corr -m lk_pt -e lk_eta -n nTracks -s lk_V3ProbNNpi -c K_V3ProbNNpi -d MagDown_2012"
KP_OPTIONS="-t $INPUTTREE -l 0.  -p lk_V3ProbNNp_corr -m lk_pt -e lk_eta -n nTracks -s lk_V3ProbNNp -c K_V3ProbNNp -d MagDown_2012"

PIK_OPTIONS="-t $INPUTTREE -l 0. -p lpi_V3ProbNNK_corr -m lpi_pt -e lpi_eta -n nTracks -s lpi_V3ProbNNK -c pi_V3ProbNNK -d MagDown_2012"
PIPI_OPTIONS="-t $INPUTTREE -l 0.  -p lpi_V3ProbNNpi_corr -m lpi_pt -e lpi_eta -n nTracks -s lpi_V3ProbNNpi -c pi_V3ProbNNpi -d MagDown_2012"
PIP_OPTIONS="-t $INPUTTREE -l 0.  -p lpi_V3ProbNNp_corr -m lpi_pt -e lpi_eta -n nTracks -s lpi_V3ProbNNp -c pi_V3ProbNNp -d MagDown_2012"

HK_OPTIONS="-t $INPUTTREE -l 0. -p h_V3ProbNNK_corr -m h_pt -e h_eta -n nTracks -s h_V3ProbNNK -c pi_V3ProbNNK -d MagDown_2012"
HPI_OPTIONS="-t $INPUTTREE -l 0.  -p h_V3ProbNNpi_corr -m h_pt -e h_eta -n nTracks -s h_V3ProbNNpi -c pi_V3ProbNNpi -d MagDown_2012"
HP_OPTIONS="-t $INPUTTREE -l 0.  -p h_V3ProbNNp_corr -m h_pt -e h_eta -n nTracks -s h_V3ProbNNp -c pi_V3ProbNNp -d MagDown_2012"

${PDFCORR} -i ../010_tuple_filter/out/histsim12_md.root -o out/tmp1_md.root ${KK_OPTIONS}
${PDFCORR} -i out/tmp1_md.root -o out/tmp2_md.root ${KPI_OPTIONS}
${PDFCORR} -i out/tmp2_md.root -o out/tmp1_md.root ${KP_OPTIONS}
${PDFCORR} -i out/tmp1_md.root -o out/tmp2_md.root ${PIK_OPTIONS}
${PDFCORR} -i out/tmp2_md.root -o out/tmp1_md.root ${PIPI_OPTIONS}
${PDFCORR} -i out/tmp1_md.root -o out/tmp2_md.root ${PIP_OPTIONS}
${PDFCORR} -i out/tmp2_md.root -o out/tmp1_md.root ${HPI_OPTIONS}
${PDFCORR} -i out/tmp1_md.root -o out/tmp2_md.root ${HK_OPTIONS}
${PDFCORR} -i out/tmp2_md.root -o out/tmp1_md.root ${HP_OPTIONS}

${PDFCORR} -i ../010_tuple_filter/out/histsim12_mu.root -o out/tmp1_mu.root ${KK_OPTIONS}
${PDFCORR} -i out/tmp1_mu.root -o out/tmp2_mu.root ${KPI_OPTIONS}
${PDFCORR} -i out/tmp2_mu.root -o out/tmp1_mu.root ${KP_OPTIONS}
${PDFCORR} -i out/tmp1_mu.root -o out/tmp2_mu.root ${PIK_OPTIONS}
${PDFCORR} -i out/tmp2_mu.root -o out/tmp1_mu.root ${PIPI_OPTIONS}
${PDFCORR} -i out/tmp1_mu.root -o out/tmp2_mu.root ${PIP_OPTIONS}
${PDFCORR} -i out/tmp2_mu.root -o out/tmp1_mu.root ${HPI_OPTIONS}
${PDFCORR} -i out/tmp1_mu.root -o out/tmp2_mu.root ${HK_OPTIONS}
${PDFCORR} -i out/tmp2_mu.root -o out/tmp1_mu.root ${HP_OPTIONS}

hadd -f out/histsim12_corr.root out/tmp1_md.root out/tmp1_mu.root
