#!/bin/bash
# condor executable for xAna_data.C

# Collect arguments
CLUSTERID=${1}
PROCID=${2}
ERA=${3}
CHUNKLIST=$(basename ${4})

OUTFILE=output_data.root
COPYDIR=${5}

# Run executable
echo "Executing xanadata"
./xanadata ${CHUNKLIST}

# Copy Output
if [ -f ${OUTFILE} ]; then
    echo "Copying output: ${URL}/${COPYDIR}/${OUTFILE}_${ERA}_${PROCID}.root"
    echo ">>> env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-copy -pf ${OUTFILE} ${COPYDIR}/output_data_${ERA}_${CLUSTERID}_${PROCID}.root"
    env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-copy -pf ${OUTFILE} ${COPYDIR}/output_data_${ERA}_${CLUSTERID}_${PROCID}.root

else
    echo "ERROR: No outfile created!!!" 
fi
