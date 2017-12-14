{	
  gROOT->LoadMacro("xAna_mc.C+");
  
  const char* inpaths[] = {
      "file:/cms/ggTree.root"
  };

  xAna_mc(inpaths, 1);
}


