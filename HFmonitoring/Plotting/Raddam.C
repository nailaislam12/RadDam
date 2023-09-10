// Should I make these arrays instead?
// that's a little more dangerous, in case we try to access outside the range
std::vector<Float_t> EtaMinus_RaddamCorrections = {
  1.12056,
  1.12285,
  1.11277,
  1.14827,
  1.21182,
  1.24013,
  1.26913,
  1.27133,
  1.24048,
  1.09554
};

std::vector<Float_t> EtaMinus_RaddamFactors = {
  1.44244,
  1.47573,
  1.32429,
  1.2823,
  1.224,
  1.18842,
  1.08006,
  1.0683,
  1.12877,
  1.11282
};

std::vector<Float_t> EtaMinus_RaddamCorrectionsError = {
  0.127265,
  0.123839,
  0.12449,
  0.128502,
  0.1338,
  0.137083,
  0.140567,
  0.141248,
  0.139228,
  0.310287
};

std::vector<Float_t> EtaPlus_RaddamCorrections = {
  1.13093,
  1.12563,
  1.12833,
  1.164,
  1.20923,
  1.24541,
  1.25277,
  1.26739,
  1.22058,
  1.14205
};

std::vector<Float_t> EtaPlus_RaddamFactors = {
  1.12318,
  1.11248,
  1.08407,
  1.11315,
  1.17516,
  1.24775,
  1.25259,
  1.34533,
  1.31489,
  1.42504
};

std::vector<Float_t> EtaPlus_RaddamCorrectionsError = {
  0.128441,
  0.124145,
  0.12623,
  0.130262,
  0.133513,
  0.137666,
  0.138751,
  0.14082,
  0.136473,
  0.175312
};

void Raddam() {
  int num = EtaMinus_RaddamCorrections.size();
  for (int i = 0; i < num; ++i)
    std::cout << "iEta -" << i+30 << ": " 
	      << EtaMinus_RaddamCorrections[i] * EtaMinus_RaddamFactors[i] << std::endl;

  for (int i = 0; i < num; ++i)
    std::cout << "iEta +" << i+30 << ": " 
	      << EtaPlus_RaddamCorrections[i] * EtaPlus_RaddamFactors[i] << std::endl;
}
