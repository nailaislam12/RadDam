# HF Z-->ee Radiation Damage Calibrations
Framework to study the radiation damage of the Hadron Forward (HF) Calorimeter using Z-->ee events. There are 3 steps required to make plots, which utilize both CRAB and HTCOndor batch submission systems

# Step 0: Setup
Checkout an appropriate CMSSW version. Below is an example for 2022:
```
cmsrel CMSSW_12_4_11_patch3
cd CMSSW_12_4_11_patch3/src
git clone https://github.com/jamesnatoli/RadDam.git
cmsenv
```

# Step 1: nTuplizer
The first step in the workflow is to process MINIAOD samples. HF sits outside of the tracker acceptance, so we need to build electron candidates ourselves from Particle Flow (PF) jets. This involves adding a module `ggNtuplizer` to CMSSW such that it can be used to process samples. To compile this module, execute the following steps, beginning from the `CMSSW_X_X_X/src` directory

```
cp -r RadDam/HFmonitoring/nTuplizer/ggAnalysis .
scram b clean
scram b -j10
```
If you make a change to the `ggNtuplizer` module, you must copy if again to `CMSSW_X_X_X/src` and recompile. The compile command can only access modules that are in `/src/`. The `scram b -j10` command must be run from `CMSSW_X_X_X/src` and should print out something similar to the following, if our additional modules were properly compiled

```
Entering library rule at src/ggAnalysis/ggNtuplizer/plugins
>> Compiling edm plugin /afs/cern.ch/work/j/jnatoli/private/HCAL/HFCalib/CMSSW_12_4_11_patch3/src/ggAnalysis/ggNtuplizer/plugins/ggNtuplizer.cc
>> Compiling edm plugin /afs/cern.ch/work/j/jnatoli/private/HCAL/HFCalib/CMSSW_12_4_11_patch3/src/ggAnalysis/ggNtuplizer/plugins/ggNtuplizer_globalEvent.cc
>> Compiling edm plugin /afs/cern.ch/work/j/jnatoli/private/HCAL/HFCalib/CMSSW_12_4_11_patch3/src/ggAnalysis/ggNtuplizer/plugins/ggNtuplizer_hfelectrons.cc
>> Compiling edm plugin /afs/cern.ch/work/j/jnatoli/private/HCAL/HFCalib/CMSSW_12_4_11_patch3/src/ggAnalysis/ggNtuplizer/plugins/ggNtuplizer_electrons.cc
>> Leaving Package RadDam/HFmonitoring
>> Leaving Package RadDam/oldHFmonitoring
>> Leaving Package oldRaddam/HFmonitoring
>> Package RadDam/HFmonitoring built
>> Package RadDam/oldHFmonitoring built
>> Package oldRaddam/HFmonitoring built
>> Subsystem RadDam built
>> Subsystem oldRaddam built
>> Building  edm plugin tmp/slc7_amd64_gcc10/src/ggAnalysis/ggNtuplizer/plugins/ggAnalysisggNtuplizerAuto/libggAnalysisggNtuplizerAuto.so
Leaving library rule at src/ggAnalysis/ggNtuplizer/plugins
```

The code is now ready to use, and can be executed with the macros in the `RadDam/HFmonitoring/nTuplizer/ggAnalysis/ggNtuplizer/test` directory. Global Tag information can be found at the [PdmVRun3Analysis](https://twiki.cern.ch/twiki/bin/view/CMS/PdmVRun3Analysis) site. To process a single file, add the path to the file from DAS in the line
```
process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('/store/data/path/to/file.root'))
```
and then use `cmsRun` to run the appropriate python script.
```
cmsRun run_data.py
```

This will create a new root file in the directory called `ggTree.root`, which can be inspected. It is a good idea to check that the code works with a single file from the dataset you plan to process before submitting to CRAB, to avoid all of the jobs failing. 

Jobs are submitted to CRAB via `crabConfig_data.py` and `crabConfig_mc.py`. The datasets to be processed must be specificed with their DAS paths. We typically use the EGamma datasets and the DYJetsToLL_M-50 MadGraph-MLM mc samples in this analysis. A luminosity mask is specified with the variable `config.Data.lumiMask` and can be found in `/eos/user/c/cmsdqm/www/CAF/certification/` or (online)[https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions23/], but the path specific must be accessible from lxplus. The CRAB environment must be setup prior to submission with `source /cvmfs/cms.cern.ch/common/crab-setup.sh` (you will need to do this every time you log in)

The CRAB jobs are submitted with 
```
python3 crabConfig_data.py
```
which crates a directory `DataJobs` with a subdirectory named according to the variable `config.General.requestName`. The jobs can be monitored with `crab status DataJobs/RequestName` which also provides a grafana link.

# Step 2: Untuplizer
This step can proceed either interactively or via jobs with Condor. The interactive script can take a long time to run (5-10 hours, or more) and so it can be more convenient to use jobs. Both methods are described below

## Running Interactively
- Use hadd to combine the nTuple trees (recommended to have one final MC file and one final data file for each run range)
- Compare the EGamma cut-based ID for ECAL electrons in xAna macros (~L220) with latest recommendations (https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2)
  **NOTE:** usually we have to use the ID from the year before or very preliminary IDs
- Add hadded nTuple paths in run macros and execute these with ROOT

## Using Condor Jobs
Rather than hadding the all of the ggTree.root output files from the nTuplizer step, we will group them in to more manageable chunks and then run one job per chunk. 

Condor jobs require a submission script, `condor_submit.sub` and executable, `for_condor_xanadata.sh`. A bash script has also been created to help with submission, `submitUntuple.sh`. This helper script compiles the c++ code, creates necessary directories (if not present), and prepares a list of files for which to use as inputs for the condor jobs. The number of files per chunk defaults to 100 and is set by `filesInChunk`.

In order to submit jobs, the user must have a valid VOMS proxy and a way to access the storage location of the ggTree.root files, as well as the storage location for the output of this step. Currently, the `gfal` protocal is used for accessing data at different sites, and copying the job outputs from condor to the storage location.

The bash helper script `submitUntuple.sh` contains three lines at the top which must be changed for your specifications. 
```
export url=""
export era=EGamma0_Run2023B_0000
export copydir=${url}/eos/user/j/jnatoli/Untuplizer/${era}
```

- `url`: used if your storage site is not where you are running the code from. For example, if you are submitting from lxplus but the data is stored on the University of Wisconsin T3 cluster, the url will be `davs://cmsxrootd.hep.wisc.edu:1094`
- `era`: a unique name for the job, ideally descriptive of the task
- `copydir`: the storage location for the output, must be accessible from condor

Once these variables are set, the jobs can be submitted with 
```
./submitUntuple.sh [path to input files]
```
The following are examples for passing in input files located on `eos` and the Wisconsin T3 cluster
```
./submitUntuple.sh /eos/user/j/jnatoli/2023HF/EGamma0/crab_EGamma0_Run2023B_test/231105_135940/0000/
./submitUntuple.sh /store/user/jnatoli/2022HF/EGamma/crab_EGamma_Run2022F/231003_155006/0002/
```

### Useful Condor Links
- [Condor submit file documentation](https://htcondor.readthedocs.io/en/latest/users-manual/submitting-a-job.html)
- [Advanced Commands](https://indico.cern.ch/event/611296/contributions/2604401/attachments/1472675/2279456/TJs_Did_You_Know_Condor_Week_Madison_2017.pdf)

# Step 3: Analysis & Plotting
- Add Data/MC analysisTree path to L90/92 in Analysis18.h, change the output file name in L49 accordingly and set isData bool in L45 in Analysis18.C accordingly
- Open ROOT, compile the Analysis18 class ('.L Analysis18.C+'), create a Analysis18 object ('Analysis18 t') and execute the loop-function ('t.Loop()')
- Create a 'Figures18' directory with the following subdirectories: Eta, Phi, PU, EtaPhiFit, EtaBin (and Run)
- Add the ROOT file with the histograms in the MakePlots macro and execute this with ROOT
