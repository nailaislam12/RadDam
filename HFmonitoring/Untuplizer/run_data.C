{ 
  gROOT->LoadMacro("xAna_data.C+");
  
  const char* inpaths[] = {
     "file:/cms/heindl/2018/HF_calibration/EGamma/crab_EGamma_Run2018A/181127_103957/ggTree.root",
     "file:/cms/heindl/2018/HF_calibration/EGamma/crab_EGamma_Run2018B/181127_104024/ggTree.root",
     "file:/cms/heindl/2018/HF_calibration/EGamma/crab_EGamma_Run2018C/181127_104055/ggTree.root",
     "file:/cms/heindl/2018/HF_calibration/EGamma/crab_EGamma_Run2018D/181127_130219/ggTree.root"
     };
  
     xAna_data(inpaths, 4);
}