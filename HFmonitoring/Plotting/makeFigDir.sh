#!/bin/bash
# quick script to create a figures directory...

NEWDIR=${1}
mkdir ${NEWDIR} || echo "Directory ${NEWDIR} already exists!"; exit
for i in Eta EtaBin EtaPhiFit PU Phi; do 
    if [[ -d ${NEWDIR}/${i} ]]; then 
	mkdir ${NEWDIR}/${i}; 
    else
	echo "Directory ${NEWDIR}/${i} already exists!"
    fi
done
