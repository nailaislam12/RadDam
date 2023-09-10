{ 
  gROOT->LoadMacro("xAna_data.C+");
  
  const char* inpaths[] = {
    "/eos/user/j/jnatoli/HFCalib/2022HF/EGamma/ggTree_EGamma_Run2022B_0000.root",
    "/eos/user/j/jnatoli/HFCalib/2022HF/EGamma/ggTree_EGamma_Run2022C_0000.root",
    "/eos/user/j/jnatoli/HFCalib/2022HF/EGamma/ggTree_EGamma_Run2022C_0001.root",
    "/eos/user/j/jnatoli/HFCalib/2022HF/EGamma/ggTree_EGamma_Run2022D_0000.root"
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022B_230427_102334_0000.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022C_230427_133150_0000.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022C_230427_133150_0001.root",
    // "davs://cmsxrootd.hep.wisc.edu:1094//store/user/jnatoli/hadded/2022HF/EGamma/ggTree_EGamma_Run2022D_230427_133210_0000.root"
    // "/eos/user/j/jnatoli/HFCalib/2022HF/EGamma/ggTree_EGamma_Run2022B_230427_102334_0000.root"    
    // "file:/cms/heindl/2018/HF_calibration/EGamma/crab_EGamma_Run2018D/181127_130219/ggTree.root"
  };
  
  xAna_data(inpaths, 4);
}
