#!/bin/bash
# script to submit condor jobs for the Untuple step

# TODO: works for all root files under an era
# TODO: figure out procedure for if jobs fail?

# Make these vars available to the condor submission script
# export url=davs://cmsxrootd.hep.wisc.edu:1094
export url="" 
export era=EGamma0_Run2023B_0000
# export copydir=${url}/store/user/jnatoli/Untuplizer/${era}
export copydir=${url}/eos/user/j/jnatoli/Untuplizer/${era}

RCOMP="`root-config --cflags --glibs`"
macro=xAna_data.C
bin=xanadata

# compile the code
if ! $(g++ $RCOMP $macro -o $bin); then
    echo "Couldn't compile ${macro}... exiting"
    exit 1
fi

# Pass in a path to the root files
indir=${1}
[ ${1} ] || indir=/store/user/jnatoli/2022HF/EGamma/crab_EGamma_Run2022F/231003_155006/0002/
indir=${url}${indir}

chunk=0
counter=1
chunkdir=${era}/infiles
filesInChunk=100

# Create directories as necessary
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

# Check for existing chunks
# NB: &> redirects stderr and stdout, > just stdout
if ls ${chunkdir}/*.txt &> /dev/null; then
    echo "Old chunks exist... deleting"
    rm ${chunkdir}/*.txt
fi

# Look for the files
if ! env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-ls ${indir} > /dev/null; then
    echo "Unable to access files: ${indir}"
    echo "Exiting..."
    exit 1
fi

# Make the chunks
echo "Creating chunk: ${chunk}"
for file in $( env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-ls ${indir}); do
    echo ${indir}/${file} >> ${chunkdir}/chunk_${chunk}.txt
    if [ $((${counter} % ${filesInChunk})) -eq 0 ]; then
	chunk=$((${chunk} + 1))
	echo "Creating chunk: ${chunk}"
    fi
    counter=$((${counter} + 1))
done

# Submit jobs!
condor_submit era=${era} condor_submit.sub
