# HF Z-->ee Radiation Damage Calibrations
Framework to study the radiation damage of the Hadron Forward (HF) Calorimeter using Z-->ee events. There are 3 steps required to make plots, which utilize both CRAB and HTCOndor batch submission systems

# Step 0: Setup
Setup an appropriate CMSSW version. For 2022 data, use `CMSSW_12_4_11_patch3`

Clone the repository using
```
git clone https://github.com/jamesnatoli/RadDam.git
```

# Step 1: nTuplizer
- Setup CMSSW_10_2_9 and copy ggAnalysis directory in CMSSW/src
- Do a 'scram b clean' followed by 'scram b -j10'
- Code is ready to use (macros are in nTuplizer/ggAnalysis/ggNtuplizer/test): 
-- Submit CRAB jobs via crabConfig (NOTE: you can submit multiple samples at once using multiprocessing)
-- Samples of interest: (Data) SingleElectron/EGamma dataset, (MC) DYJetsToLL_M-50 MadGraph-MLM sample
-- Check the latest GlobalTag in the cmsRun macros (different for data & MC - see https://twiki.cern.ch/twiki/bin/viewauth/CMS/PdmVAnalysisSummaryTable)

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

# Step 3: Analysis & Plotting
- Add Data/MC analysisTree path to L90/92 in Analysis18.h, change the output file name in L49 accordingly and set isData bool in L45 in Analysis18.C accordingly
- Open ROOT, compile the Analysis18 class ('.L Analysis18.C+'), create a Analysis18 object ('Analysis18 t') and execute the loop-function ('t.Loop()')
- Create a 'Figures18' directory with the following subdirectories: Eta, Phi, PU, EtaPhiFit, EtaBin (and Run)
- Add the ROOT file with the histograms in the MakePlots macro and execute this with ROOT
