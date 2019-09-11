{	
  gROOT->LoadMacro("xAna_mc.C+");
  
  const char* inpaths[] = {
      "file:/cms/heindl/2018/HF_calibration/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_Fall18/181127_103024/ggTree.root"
  };

  xAna_mc(inpaths, 1);
}
