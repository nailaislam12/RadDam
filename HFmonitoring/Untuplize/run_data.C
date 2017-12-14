{ 
  gROOT->LoadMacro("xAna_data.C+");
  
  const char* inpaths[] = {
     "file:/cms/ggTree.root",
     };
  
     xAna_data(inpaths, 1);
}