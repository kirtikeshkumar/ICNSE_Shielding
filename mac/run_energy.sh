#!/bin/bash

range(){
    for x in $(seq "$1" "$3" "$2"); do
        echo "$x"
    done
}

#NUMOFTHREADS=15
ENERGIES="$(range 10 90 10)"
ENERGIES+=" $(range 100 1000 20)"
ENERGIES+=" $(range 1050 10000 50)"
#PARTICLES=("e+" "e-" "neutron" "gamma")
NUMOFEVENTS=10000000
#MATERIALS=("HDPE" "Pb" "BP")
#THICKNESSES=(2 5 10 15 20)
#ORDERING=("HHBBLLHH" "HHBLHBLH")
#ORDER="HHBLHBLH"
#ORDER="HHBBLLHH"

PARTICLE="gamma"
#THICKNESS="2.5_7.5"
#MATERIAL="HDPE_BP"

for ENERGY in $ENERGIES; do
    sed -e "s|ENERGY|$ENERGY|g" \
    -e "s|PARTICLE|$PARTICLE|g" \
    -e "s|NUMOFEVENTS|$NUMOFEVENTS|g" \
    run.template.mac > run.mac
    ./sim run.mac
    DIR="../outputs/DetEff/${PARTICLE}"
    mkdir -p "$DIR"
    hadd "${DIR}"/output_DetEff_"${PARTICLE}"_"${ENERGY}"keV_${NUMOFEVENTS}evt.root output0.root
    rm output0*
done