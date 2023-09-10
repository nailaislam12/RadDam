{	
  gROOT->LoadMacro("xAna_mc.C+");
  
  const char* inpaths[] = {
    "/eos/user/j/jnatoli/HFCalib/2022HF/DYJetsToLL_M-50/ggTree_DYJetsToLL_M-50_Winter22_230427_132247_0000.root",
    "/eos/user/j/jnatoli/HFCalib/2022HF/DYJetsToLL_M-50/ggTree_DYJetsToLL_M-50_Winter22_230427_132606_0000.root"
    // "file:/cms/heindl/2018/HF_calibration/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_Fall18/181127_103024/ggTree.root"
  };

  xAna_mc(inpaths, 2);
}
