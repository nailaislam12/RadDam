#include "Raddam.h"

void factorCalc() {
  int num = EtaMinus_RaddamCorrections.size();
  for (int i = 0; i < num; ++i)
    std::cout << "iEta -" << i+30 << ": " 
	      << EtaMinus_RaddamCorrections[i] * EtaMinus_RaddamFactors[i] << std::endl;

  for (int i = 0; i < num; ++i)
    std::cout << "iEta +" << i+30 << ": " 
	      << EtaPlus_RaddamCorrections[i] * EtaPlus_RaddamFactors[i] << std::endl;
}
