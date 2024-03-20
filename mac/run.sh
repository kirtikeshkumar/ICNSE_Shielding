#!/bin/bash

range(){
     for x in $(seq $1 $3 $2); do
          echo $x
     done
}

NUMOFTHREADS=15
ENERGIES=$(range 100 10000 100)
PARTICLES=("neutron" "gamma")
NUMOFEVENTS=10000000
ORDERING=("HHBBLLHH" "HHBLHBLH")
ORDER="HHBLHBLH"
#ORDER="HHBBLLHH"

for PARTICLE in $PARTICLES;do
    for ENERGY in $ENERGIES;do
        sed -e "s|NUMOFTHREADS|$NUMOFTHREADS|g" \
            -e "s|ENERGY|$ENERGY|g" \
            -e "s|PARTICLE|$PARTICLE|g" \
            -e "s|NUMOFEVENTS|$NUMOFEVENTS|g" \
            run.template.mac > run.mac
    	./sim run.mac $ORDER
    	hadd output_${PARTICLE}_${ENERGY}keV_${ORDER}_${NUMOFEVENTS}evt.root output0_t*.root
    	rm output0_t*
    done
done
