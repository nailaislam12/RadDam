#!/bin/bash
# script to submit condor jobs for the Untuple step

# TODO: automatic grouping
# TODO: works for all root files under an era
# TODO: figure out procedure for if jobs fail?

RCOMP="`root-config --cflags --glibs`"
macro=xAna_data.C
bin=xanadata

if ! $(g++ $RCOMP $macro -o $bin); then
    echo "Couldn't compile ${macro}... exiting"
    exit 1
fi

era=EGamma_Run2022F_0002
url=davs://cmsxrootd.hep.wisc.edu:1094/
indir=${1}
[ ${1} ] || indir=/store/user/jnatoli/2022HF/EGamma/crab_EGamma_Run2022F/231003_155006/0002/
indir=${url}${indir}

chunk=0
counter=1
chunkdir=${era}/infiles
filesInChunk=100

if [ ! -d ${era} ]; then
    echo "creating directory ${era}..."
    mkdir ${era}
fi

if [ ! -d ${chunkdir} ]; then
    echo "creating directory ${chunkdir}..."
    mkdir ${chunkdir}
fi

if [ ! -d ${era}/jobs ]; then
    echo "creating jobs directories..."
    mkdir ${era}/jobs
fi

if [ ! -d ${era}/jobs/err ]; then
    echo "creating err directories..."
    mkdir ${era}/jobs/err
fi

if [ ! -d ${era}/jobs/out ]; then
    echo "creating out directories..."
    mkdir ${era}/jobs/out
fi

if [ ! -d ${era}/jobs/log ]; then
    echo "creating log directories..."
    mkdir ${era}/jobs/log
fi

# NB: &> redirects stderr and stdout, > just stdout
if ls ${chunkdir}/*.txt &> /dev/null; then
    echo "Old chunks exist... deleting"
    rm ${chunkdir}/*.txt
fi

if ! env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-ls ${indir} > /dev/null; then
    echo "Unable to access files: ${indir}"
    echo "Exiting..."
    exit 1
fi

echo "Creating chunk: ${chunk}"
for file in $( env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-ls ${indir}); do
    echo ${indir}/${file} >> ${chunkdir}/chunk_${chunk}.txt
    if [ $((${counter} % ${filesInChunk})) -eq 0 ]; then
	chunk=$((${chunk} + 1))
	echo "Creating chunk: ${chunk}"
    fi
    counter=$((${counter} + 1))
done

condor_submit condor_submit.sub
