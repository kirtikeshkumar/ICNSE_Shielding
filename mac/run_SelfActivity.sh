#!/bin/bash

DIR="../outputs/SelfActivity"
mkdir -p "$DIR"

NUMOFTHREADS=15
NUMOFEVENTS=1000000
#ORDER and THICKNESSES to be provided from inside out
#ORDER="Cu_BP_HDPE_SS_Pb_SS"
#THICKNESSES="2.0_12.5_2.5_0.5_10.0_0.5" 
ORDER="W_Pb"
THICKNESSES="2.0_2.0"

sed -e "s|NUMOFTHREADS|$NUMOFTHREADS|g" \
            -e "s|ORDER|$ORDER|g" \
            -e "s|THICKNESSES|$THICKNESSES|g" \
            -e "s|NUMOFEVENTS|$NUMOFEVENTS|g" \
            run.template_Mod.mac > run.mac

./sim run.mac
hadd "${DIR}"/output_SelfActivity_"${ORDER}"_"${THICKNESSES}"cm_${NUMOFEVENTS}evt.root output0_t*.root
rm output0*