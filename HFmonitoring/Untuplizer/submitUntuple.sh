#!/bin/bash
# script to submit condor jobs for the Untuple step

# TODO: works for all root files under an era
# TODO: figure out procedure for if jobs fail?

# Make these vars available to the condor submission script

url="" 
# url=davs://cmsxrootd.hep.wisc.edu:1094
export copydir=${url}/eos/user/j/jnatoli/Untuplizer/${era}
export era=EGamma0_Run2023B_0000

RCOMP="`root-config --cflags --glibs`"
macro=xAna_data.C
bin=xanadata

# Check if environment is clean
if [ ! -z ${CMSSW_BASE} ]; then
  echo -e "\tError: This script must be run in a clean environment. You already have a CMSSW environment set up for ${CMSSW_VERSION}."
  echo -e "\tPlease try again from a clean shell."
  exit 1
fi

# Compile the code
echo ">>> Compiling macro: ${macro}" 
if ! $(g++ $RCOMP $macro -o $bin); then
    echo -e "\tCouldn't compile ${macro}... exiting"
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
echo ">>> Checking directories: ${era}" 
if [ ! -d ${era} ]; then
    echo -e "\tcreating directory ${era}..."
    mkdir ${era}
fi

if [ ! -d ${chunkdir} ]; then
    echo -e "\tcreating directory ${chunkdir}..."
    mkdir ${chunkdir}
fi

if [ ! -d ${era}/jobs ]; then
    echo -e "\tcreating jobs directories..."
    mkdir ${era}/jobs
fi

if [ ! -d ${era}/jobs/err ]; then
    echo -e "\tcreating err directories..."
    mkdir ${era}/jobs/err
fi

if [ ! -d ${era}/jobs/out ]; then
    echo -e "\tcreating out directories..."
    mkdir ${era}/jobs/out
fi

if [ ! -d ${era}/jobs/log ]; then
    echo -e "\tcreating log directories..."
    mkdir ${era}/jobs/log
fi

# Check for existing chunks
echo ">>> Checking for chunks: ${chunkdir}" 
# NB: &> redirects stderr and stdout, > just stdout
if ls ${chunkdir}/*.txt &> /dev/null; then
    echo -e "\tOld chunks exist... deleting"
    rm ${chunkdir}/*.txt
fi

# Look for the files
echo ">>> Looking for files: ${indir}" 
if ! env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-ls ${indir} > /dev/null; then
    echo -e "\tUnable to access files: ${indir}"
    echo -e "\tExiting..."
    exit 1
fi

# Make the chunks
echo ">>> Creating chunk: ${chunk}"
for file in $( env -i X509_USER_PROXY=${X509_USER_PROXY} gfal-ls ${indir}); do
    echo ${indir}/${file} >> ${chunkdir}/chunk_${chunk}.txt
    if [ $((${counter} % ${filesInChunk})) -eq 0 ]; then
	chunk=$((${chunk} + 1))
	echo ">>> Creating chunk: ${chunk}"
    fi
    counter=$((${counter} + 1))
done

# Submit jobs!
echo ">>> Submitting jobs: condor_submit era=${era} condor_submit.sub"
condor_submit era=${era} condor_submit.sub
