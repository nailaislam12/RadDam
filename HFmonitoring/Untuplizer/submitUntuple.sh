#!/bin/bash
# script to submit condor jobs for the Untuple step

# TODO: adapt for using urls
# TODO: automatic grouping

indir=${1}
[ ${1} ] || indir=/hdfs/store/user/jnatoli/2022HF/EGamma/crab_EGamma_Run2022E/231003_154951/0000/
filesInChunk=100
# Dump 

counter=1
chunk=0
for file in $(ls ${indir}); do
    echo file >> test_${chunk}.txt
    if [ $((${counter} % ${filesInChunk})) -eq 0 ]; then
	chunk=$((${chunk} + 1))
	echo "Another chunk..."
    fi
    counter=$((${counter} + 1))
done
