#!/bin/bash

range(){
     for x in $(seq "$1" "$3" "$2"); do
          echo "$x"
     done
}

NUMOFTHREADS=15
ENERGIES=$(range 0.025 5000 100)
PARTICLES=("e+" "e-" "neutron" "gamma")
NUMOFEVENTS=10000000
MATERIALS=("HDPE" "Pb" "BP")
THICKNESSES=(2 5 10 15 20)
#ORDERING=("HHBBLLHH" "HHBLHBLH")
#ORDER="HHBLHBLH"
#ORDER="HHBBLLHH"

PARTICLE="neutron"
THICKNESS="2.5_7.5"
MATERIAL="HDPE_BP"

for ENERGY in $ENERGIES; do
    sed -e "s|WIDTH|$THICKNESS|g"\
        -e "s|MATERIAL|$MATERIAL|g"\
        -e "s|NUMOFTHREADS|$NUMOFTHREADS|g" \
        -e "s|ENERGY|$ENERGY|g" \
        -e "s|PARTICLE|$PARTICLE|g" \
        -e "s|NUMOFEVENTS|$NUMOFEVENTS|g" \
        run.template.mac > run.mac
        ./sim run.mac
        DIR="../outputs/SingleLayer/MixHDPE1inBP3in/${PARTICLE}"           
        mkdir -p "$DIR"
    	hadd "${DIR}"/output_"${MATERIAL}"_"${THICKNESS}"cm_"${PARTICLE}"_"${ENERGY}"keV_${NUMOFEVENTS}evt.root output0_t*.root
    	rm output0_t*
done

