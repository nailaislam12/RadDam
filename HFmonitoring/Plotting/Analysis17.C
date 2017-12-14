#define Analysis17_cxx
#include "Analysis17.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "CMSStyle.C"

using namespace std;
void beautify(TH1F* plot, TString xTitle, TString yTitle, int color) {
  plot->GetXaxis()->SetTitle(xTitle);
  plot->GetYaxis()->SetTitle(yTitle);
  plot->SetMarkerColor(color);
  plot->SetLineColor(color);
  return;
}
void beautify(TH2F* plot, TString xTitle, TString yTitle, int color) {
  plot->GetXaxis()->SetTitle(xTitle);
  plot->GetYaxis()->SetTitle(yTitle);
  plot->SetMarkerColor(color);
  plot->SetLineColor(color);
  return;
}

int getRunIndex(int run) {
  if ( run >= 295993 && run <= 296977 ) return 0;
  if ( run >= 296978 && run <= 297101 ) return 1;
  if ( run >= 297108 && run <= 297284 ) return 2;
  if ( run >= 297285 && run <= 297411 ) return 3;
  if ( run >= 297422 && run <= 297465 ) return 4;
  if ( run >= 297467 && run <= 297502 ) return 5;
  if ( run >= 297503 && run <= 297560 ) return 6;
  if ( run >= 297562 && run <= 297605 ) return 7;
  if ( run >= 297606 && run <= 297674 ) return 8;
  if ( run >= 297675 && run <= 299064 ) return 9;
  if ( run >= 299065 && run <= 299324 ) return 10;
  if ( run >= 299325 && run <= 299395 ) return 11;
  if ( run >= 299396 && run <= 299481 ) return 12;
  if ( run >= 299590 && run <= 299614 ) return 13;
  if ( run >= 299616 && run <= 300122 ) return 14;
  if ( run >= 300123 && run <= 300156 ) return 15;
  if ( run >= 300157 && run <= 300236 ) return 16;
  if ( run >= 300237 && run <= 300282 ) return 17;
  if ( run >= 300283 && run <= 300400 ) return 18;
  if ( run >= 300401 && run <= 300466 ) return 19;
  if ( run >= 300467 && run <= 300516 ) return 20;
  if ( run >= 300517 && run <= 300560 ) return 21;
  if ( run >= 300561 && run <= 300633 ) return 22;
  if ( run >= 300634 && run <= 300676 ) return 23;
  return -1;
}
int getEtaIndex(float eta) {
  if ( eta < 2.964 ) return -1;
  if ( eta > 2.964 && eta < 3.139 ) return 0;
  if ( eta > 3.139 && eta < 3.314 ) return 1;
  if ( eta > 3.314 && eta < 3.489 ) return 2;
  if ( eta > 3.489 && eta < 3.664 ) return 3;
  if ( eta > 3.664 && eta < 3.839 ) return 4;
  if ( eta > 3.839 && eta < 4.013 ) return 5;
  if ( eta > 4.013 && eta < 4.191 ) return 6;
  if ( eta > 4.191 && eta < 4.363 ) return 7;
  if ( eta > 4.363 && eta < 4.538 ) return 8;
  if ( eta > 4.538 && eta < 4.716 ) return 9;
  if ( eta > 4.716 && eta < 4.889 ) return 10;
  if ( eta > 4.889 && eta < 5.191 ) return 11;
  if ( eta > 5.191 ) return -1;
  return -1;
}

float getRaddamCorrection(int run, float eta) {

  // Measured corrections up to RunB-PRv1
  // float corr1[24] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // float corr2[24] = {1, 0.999432, 0.994644, 0.9987, 0.992452, 0.992452, 0.993519, 0.992996, 0.988326, 1.00013, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // float corr3[24] = {1, 0.996883, 0.996376, 1.00009, 0.991857, 0.991857, 0.994024, 0.993286, 0.986965, 1.00076, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // float corr4[24] = {1, 0.993696, 0.994265, 0.998387, 0.989684, 0.989684, 0.991236, 0.991103, 0.984317, 1.00071, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // float corr5[24] = {1, 0.995187, 0.993099, 0.991811, 0.983982, 0.983982, 0.984149, 0.985515, 0.977652, 0.992493, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // float corr6[24] = {1, 0.993225, 0.989112, 0.987292, 0.978632, 0.978632, 0.977965, 0.978194, 0.970512, 0.984108, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // float corr7[24] = {1, 0.995559, 0.989865, 0.986835, 0.978156, 0.978156, 0.97862, 0.978336, 0.972663, 0.985334, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // float corr8[24] = {1, 0.992978, 0.98795, 0.984141, 0.97361, 0.97361, 0.972922, 0.97262, 0.971421, 0.979623, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // float corr9[24] = {1, 0.99056, 0.986351, 0.980207, 0.969892, 0.969892, 0.969438, 0.969278, 0.963481, 0.975744, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // float corr10[24] = {1, 0.992145, 0.982474, 0.981011, 0.968087, 0.968087, 0.967918, 0.96717, 0.961699, 0.974817, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // float corr11[24] = {1, 0.993028, 0.989218, 0.982801, 0.972176, 0.972176, 0.973329, 0.971082, 0.969738, 0.980441, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // float corr12[24] = {1, 0.999928, 1.0058, 0.993237, 0.992122, 0.992122, 0.992449, 0.993087, 0.992905, 0.999619, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  
  // Projection numbers
  float corr1[24] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  float corr2[24] = {1, 0.999818, 0.999592, 0.999366, 0.999236, 0.9991, 0.998934, 0.998793, 0.998646, 0.998488, 0.99833, 0.998173, 0.998018, 0.99985, 0.9997, 0.999555, 0.999428, 0.999293, 0.999148, 0.999013, 0.998887, 0.998739, 0.998582, 0.998464};
  float corr3[24] = {1, 0.999714, 0.999358, 0.999005, 0.998801, 0.998586, 0.998327, 0.998105, 0.997873, 0.997626, 0.997379, 0.997132, 0.996889, 0.999766, 0.999529, 0.999302, 0.999102, 0.998891, 0.998664, 0.99845, 0.998252, 0.99802, 0.997774, 0.99759};
  float corr4[24] = {1, 0.999485, 0.998846, 0.998209, 0.997841, 0.997457, 0.996988, 0.99659, 0.996175, 0.995729, 0.995285, 0.994842, 0.994404, 0.999578, 0.999152, 0.998743, 0.998384, 0.998003, 0.997595, 0.99721, 0.996855, 0.996438, 0.995995, 0.995664};
  float corr5[24] = {1, 0.999324, 0.998483, 0.997645, 0.997161, 0.996656, 0.996041, 0.995517, 0.99497, 0.994385, 0.993802, 0.993219, 0.992645, 0.999445, 0.998885, 0.998347, 0.997874, 0.997374, 0.996836, 0.996331, 0.995864, 0.995315, 0.994734, 0.994298};
  float corr6[24] = {1, 0.99914, 0.998071, 0.997007, 0.996391, 0.995749, 0.994968, 0.994304, 0.993609, 0.992865, 0.992126, 0.991387, 0.990658, 0.999294, 0.998582, 0.997898, 0.997297, 0.996661, 0.995978, 0.995338, 0.994744, 0.994047, 0.993308, 0.992756};
  float corr7[24] = {1, 0.999049, 0.997867, 0.996692, 0.996014, 0.995304, 0.994441, 0.993707, 0.992941, 0.992119, 0.991303, 0.990486, 0.989682, 0.99922, 0.998433, 0.997677, 0.997014, 0.996312, 0.995557, 0.994849, 0.994194, 0.993424, 0.992609, 0.991998};
  float corr8[24] = {1, 0.998871, 0.997471, 0.996075, 0.99527, 0.994428, 0.993406, 0.992535, 0.991626, 0.990652, 0.989685, 0.988718, 0.987764, 0.999074, 0.998141, 0.997244, 0.996457, 0.995623, 0.994728, 0.993889, 0.993112, 0.992198, 0.991232, 0.990509};
  float corr9[24] = {1, 0.99872, 0.99713, 0.995549, 0.994636, 0.993683, 0.992524, 0.991537, 0.990508, 0.989404, 0.988308, 0.987213, 0.986133, 0.998951, 0.997891, 0.996874, 0.995982, 0.995038, 0.994024, 0.993072, 0.992192, 0.991156, 0.990062, 0.989242};
  float corr10[24] = {1, 0.998594, 0.996847, 0.99511, 0.994107, 0.993059, 0.991786, 0.990703, 0.989572, 0.988361, 0.987157, 0.985956, 0.984771, 0.998846, 0.997682, 0.996565, 0.995584, 0.994546, 0.993432, 0.992387, 0.99142, 0.990283, 0.989081, 0.988181};
  float corr11[24] = {1, 0.998498, 0.996635, 0.994782, 0.993711, 0.992594, 0.991237, 0.990081, 0.988875, 0.987582, 0.9863, 0.985018, 0.983754, 0.998768, 0.997527, 0.996334, 0.995288, 0.994181, 0.992993, 0.991877, 0.990846, 0.989634, 0.988352, 0.987392};
  float corr12[24] = {1, 0.998602, 0.996865, 0.995137, 0.994141, 0.993099, 0.991834, 0.990756, 0.989632, 0.988427, 0.98723, 0.986035, 0.984858, 0.998852, 0.997696, 0.996583, 0.99561, 0.994578, 0.993469, 0.99243, 0.991469, 0.990339, 0.989143, 0.988249};

  
  int runIndex = getRunIndex(run);
  int etaIndex = getEtaIndex(fabs(eta));
  if ( etaIndex ==  0 ) return corr1[runIndex];
  if ( etaIndex ==  1 ) return corr2[runIndex];
  if ( etaIndex ==  2 ) return corr3[runIndex];
  if ( etaIndex ==  3 ) return corr4[runIndex];
  if ( etaIndex ==  4 ) return corr5[runIndex];
  if ( etaIndex ==  5 ) return corr6[runIndex];
  if ( etaIndex ==  6 ) return corr7[runIndex];
  if ( etaIndex ==  7 ) return corr8[runIndex];
  if ( etaIndex ==  8 ) return corr9[runIndex];
  if ( etaIndex ==  9 ) return corr10[runIndex];
  if ( etaIndex ==  10 ) return corr11[runIndex];
  if ( etaIndex ==  11 ) return corr12[runIndex];
  cout << "Something is wrong" << endl;
  return 0;
}

void Analysis17::Loop()
{
   CMSStyle();
   if (fChain == 0) return;

   TFile* out = TFile::Open("outplots_dataRunBC_withPU.root", "RECREATE");

   TH1F* h_mass = new TH1F("h_mass", "", 140, 20, 160);
   beautify(h_mass, "M_{e, hf} (GeV)", "Events / 1 GeV", 2);
   TH1F* h_nvtx = new TH1F("h_nvtx", "", 60, 0, 60);
   beautify(h_nvtx, "nVtx", "Events", 2);
 
   TH1F* etaPlus30  = new TH1F("etaPlus30", "", 140, 20, 160);
   TH1F* etaPlus31  = new TH1F("etaPlus31", "", 140, 20, 160);
   TH1F* etaPlus32  = new TH1F("etaPlus32", "", 140, 20, 160);
   TH1F* etaPlus33  = new TH1F("etaPlus33", "", 140, 20, 160);
   TH1F* etaPlus34  = new TH1F("etaPlus34", "", 140, 20, 160);
   TH1F* etaPlus35  = new TH1F("etaPlus35", "", 140, 20, 160);
   TH1F* etaPlus36  = new TH1F("etaPlus36", "", 140, 20, 160);
   TH1F* etaPlus37  = new TH1F("etaPlus37", "", 140, 20, 160);
   TH1F* etaPlus38  = new TH1F("etaPlus38", "", 140, 20, 160);
   TH1F* etaPlus39  = new TH1F("etaPlus39", "", 140, 20, 160);
   TH1F* etaPlus40  = new TH1F("etaPlus40", "", 140, 20, 160);
   TH1F* etaPlus41  = new TH1F("etaPlus41", "", 140, 20, 160);
   TH1F* etaMinus30  = new TH1F("etaMinus30", "", 140, 20, 160);
   TH1F* etaMinus31  = new TH1F("etaMinus31", "", 140, 20, 160);
   TH1F* etaMinus32  = new TH1F("etaMinus32", "", 140, 20, 160);
   TH1F* etaMinus33  = new TH1F("etaMinus33", "", 140, 20, 160);
   TH1F* etaMinus34  = new TH1F("etaMinus34", "", 140, 20, 160);
   TH1F* etaMinus35  = new TH1F("etaMinus35", "", 140, 20, 160);
   TH1F* etaMinus36  = new TH1F("etaMinus36", "", 140, 20, 160);
   TH1F* etaMinus37  = new TH1F("etaMinus37", "", 140, 20, 160);
   TH1F* etaMinus38  = new TH1F("etaMinus38", "", 140, 20, 160);
   TH1F* etaMinus39  = new TH1F("etaMinus39", "", 140, 20, 160);
   TH1F* etaMinus40  = new TH1F("etaMinus40", "", 140, 20, 160);
   TH1F* etaMinus41  = new TH1F("etaMinus41", "", 140, 20, 160);

   TH1F* phi1  = new TH1F("phi1", "", 140, 20, 160);
   TH1F* phi3  = new TH1F("phi3", "", 140, 20, 160);
   TH1F* phi5  = new TH1F("phi5", "", 140, 20, 160);
   TH1F* phi7  = new TH1F("phi7", "", 140, 20, 160);
   TH1F* phi9  = new TH1F("phi9", "", 140, 20, 160);
   TH1F* phi11  = new TH1F("phi11", "", 140, 20, 160);
   TH1F* phi13  = new TH1F("phi13", "", 140, 20, 160);
   TH1F* phi15  = new TH1F("phi15", "", 140, 20, 160);
   TH1F* phi17  = new TH1F("phi17", "", 140, 20, 160);
   TH1F* phi19  = new TH1F("phi19", "", 140, 20, 160);
   TH1F* phi21  = new TH1F("phi21", "", 140, 20, 160);
   TH1F* phi23  = new TH1F("phi23", "", 140, 20, 160);
   TH1F* phi25  = new TH1F("phi25", "", 140, 20, 160);
   TH1F* phi27  = new TH1F("phi27", "", 140, 20, 160);
   TH1F* phi29  = new TH1F("phi29", "", 140, 20, 160);
   TH1F* phi31  = new TH1F("phi31", "", 140, 20, 160);
   TH1F* phi33  = new TH1F("phi33", "", 140, 20, 160);
   TH1F* phi35  = new TH1F("phi35", "", 140, 20, 160);
   TH1F* phi37  = new TH1F("phi37", "", 140, 20, 160);
   TH1F* phi39  = new TH1F("phi39", "", 140, 20, 160);
   TH1F* phi41  = new TH1F("phi41", "", 140, 20, 160);
   TH1F* phi43  = new TH1F("phi43", "", 140, 20, 160);
   TH1F* phi45  = new TH1F("phi45", "", 140, 20, 160);
   TH1F* phi47  = new TH1F("phi47", "", 140, 20, 160);
   TH1F* phi49  = new TH1F("phi49", "", 140, 20, 160);
   TH1F* phi51  = new TH1F("phi51", "", 140, 20, 160);
   TH1F* phi53  = new TH1F("phi53", "", 140, 20, 160);
   TH1F* phi55  = new TH1F("phi55", "", 140, 20, 160);
   TH1F* phi57  = new TH1F("phi57", "", 140, 20, 160);
   TH1F* phi59  = new TH1F("phi59", "", 140, 20, 160);
   TH1F* phi61  = new TH1F("phi61", "", 140, 20, 160);
   TH1F* phi63  = new TH1F("phi63", "", 140, 20, 160);
   TH1F* phi65  = new TH1F("phi65", "", 140, 20, 160);
   TH1F* phi67  = new TH1F("phi67", "", 140, 20, 160);
   TH1F* phi69  = new TH1F("phi69", "", 140, 20, 160);
   TH1F* phi71  = new TH1F("phi71", "", 140, 20, 160);
   
   TH1F* nVtx1  = new TH1F("nVtx1", "", 140, 20, 160);
   TH1F* nVtx2  = new TH1F("nVtx2", "", 140, 20, 160);
   TH1F* nVtx3  = new TH1F("nVtx3", "", 140, 20, 160);
   TH1F* nVtx4  = new TH1F("nVtx4", "", 140, 20, 160);
   TH1F* nVtx5  = new TH1F("nVtx5", "", 140, 20, 160);
   TH1F* nVtx6  = new TH1F("nVtx6", "", 140, 20, 160);
   TH1F* nVtx7  = new TH1F("nVtx7", "", 140, 20, 160);
   TH1F* nVtx8  = new TH1F("nVtx8", "", 140, 20, 160);
   TH1F* nVtx9  = new TH1F("nVtx9", "", 140, 20, 160);
   
   TH1F* eta30nvtx = new TH1F("eta30nvtx", "", 60, 0, 60);
   beautify(eta30nvtx, "nVtx (i#eta30)", "Events", 2);
   TH1F* eta31nvtx = new TH1F("eta31nvtx", "", 60, 0, 60);
   beautify(eta31nvtx, "nVtx (i#eta31)", "Events", 2);
   TH1F* eta32nvtx = new TH1F("eta32nvtx", "", 60, 0, 60);
   beautify(eta32nvtx, "nVtx (i#eta32)", "Events", 2);
   TH1F* eta33nvtx = new TH1F("eta33nvtx", "", 60, 0, 60);
   beautify(eta33nvtx, "nVtx (i#eta33)", "Events", 2);
   TH1F* eta34nvtx = new TH1F("eta34nvtx", "", 60, 0, 60);
   beautify(eta34nvtx, "nVtx (i#eta34)", "Events", 2);
   TH1F* eta35nvtx = new TH1F("eta35nvtx", "", 60, 0, 60);
   beautify(eta35nvtx, "nVtx (i#eta35)", "Events", 2);
   TH1F* eta36nvtx = new TH1F("eta36nvtx", "", 60, 0, 60);
   beautify(eta36nvtx, "nVtx (i#eta36)", "Events", 2);
   TH1F* eta37nvtx = new TH1F("eta37nvtx", "", 60, 0, 60);
   beautify(eta37nvtx, "nVtx (i#eta37)", "Events", 2);
   TH1F* eta38nvtx = new TH1F("eta38nvtx", "", 60, 0, 60);
   beautify(eta38nvtx, "nVtx (i#eta38)", "Events", 2);
   TH1F* eta39nvtx = new TH1F("eta39nvtx", "", 60, 0, 60);
   beautify(eta39nvtx, "nVtx (i#eta39)", "Events", 2);
   TH1F* eta40nvtx = new TH1F("eta40nvtx", "", 60, 0, 60);
   beautify(eta40nvtx, "nVtx (i#eta40)", "Events", 2);
   TH1F* eta41nvtx = new TH1F("eta41nvtx", "", 60, 0, 60);
   beautify(eta41nvtx, "nVtx (i#eta41)", "Events", 2);
   
   TH1F* eta30phi = new TH1F("eta30phi", "eta30", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta30phi, "#phi_{HF}", "Events", 2);
   TH1F* eta31phi = new TH1F("eta31phi", "eta31", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta31phi, "#phi_{HF}", "Events", 2);
   TH1F* eta32phi = new TH1F("eta32phi", "eta32", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta32phi, "#phi_{HF}", "Events", 2);
   TH1F* eta33phi = new TH1F("eta33phi", "eta33", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta33phi, "#phi_{HF}", "Events", 2);
   TH1F* eta34phi = new TH1F("eta34phi", "eta34", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta34phi, "#phi_{HF}", "Events", 2);
   TH1F* eta35phi = new TH1F("eta35phi", "eta35", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta35phi, "#phi_{HF}", "Events", 2);
   TH1F* eta36phi = new TH1F("eta36phi", "eta36", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta36phi, "#phi_{HF}", "Events", 2);
   TH1F* eta37phi = new TH1F("eta37phi", "eta37", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta37phi, "#phi_{HF}", "Events", 2);
   TH1F* eta38phi = new TH1F("eta38phi", "eta38", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta38phi, "#phi_{HF}", "Events", 2);
   TH1F* eta39phi = new TH1F("eta39phi", "eta39", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta39phi, "#phi_{HF}", "Events", 2);
   TH1F* eta40phi = new TH1F("eta40phi", "eta40", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta40phi, "#phi_{HF}", "Events", 2);
   TH1F* eta41phi = new TH1F("eta41phi", "eta41", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta41phi, "#phi_{HF}", "Events", 2);
   
   TH1F* eta30etaEE = new TH1F("eta30etaEE", "eta30", 126, -3.15, 3.15);
   beautify(eta30etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta31etaEE = new TH1F("eta31etaEE", "eta31", 126, -3.15, 3.15);
   beautify(eta31etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta32etaEE = new TH1F("eta32etaEE", "eta32", 126, -3.15, 3.15);
   beautify(eta32etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta33etaEE = new TH1F("eta33etaEE", "eta33", 126, -3.15, 3.15);
   beautify(eta33etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta34etaEE = new TH1F("eta34etaEE", "eta34", 126, -3.15, 3.15);
   beautify(eta34etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta35etaEE = new TH1F("eta35etaEE", "eta35", 126, -3.15, 3.15);
   beautify(eta35etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta36etaEE = new TH1F("eta36etaEE", "eta36", 126, -3.15, 3.15);
   beautify(eta36etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta37etaEE = new TH1F("eta37etaEE", "eta37", 126, -3.15, 3.15);
   beautify(eta37etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta38etaEE = new TH1F("eta38etaEE", "eta38", 126, -3.15, 3.15);
   beautify(eta38etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta39etaEE = new TH1F("eta39etaEE", "eta39", 126, -3.15, 3.15);
   beautify(eta39etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta40etaEE = new TH1F("eta40etaEE", "eta40", 126, -3.15, 3.15);
   beautify(eta40etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta41etaEE = new TH1F("eta41etaEE", "eta41", 126, -3.15, 3.15);
   beautify(eta41etaEE, "#eta_{ECAL}", "Events", 2);
   
   TH1F* eta30phiEE = new TH1F("eta30phiEE", "eta30", 126, -3.15, 3.15);
   beautify(eta30phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta31phiEE = new TH1F("eta31phiEE", "eta31", 126, -3.15, 3.15);
   beautify(eta31phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta32phiEE = new TH1F("eta32phiEE", "eta32", 126, -3.15, 3.15);
   beautify(eta32phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta33phiEE = new TH1F("eta33phiEE", "eta33", 126, -3.15, 3.15);
   beautify(eta33phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta34phiEE = new TH1F("eta34phiEE", "eta34", 126, -3.15, 3.15);
   beautify(eta34phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta35phiEE = new TH1F("eta35phiEE", "eta35", 126, -3.15, 3.15);
   beautify(eta35phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta36phiEE = new TH1F("eta36phiEE", "eta36", 126, -3.15, 3.15);
   beautify(eta36phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta37phiEE = new TH1F("eta37phiEE", "eta37", 126, -3.15, 3.15);
   beautify(eta37phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta38phiEE = new TH1F("eta38phiEE", "eta38", 126, -3.15, 3.15);
   beautify(eta38phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta39phiEE = new TH1F("eta39phiEE", "eta39", 126, -3.15, 3.15);
   beautify(eta39phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta40phiEE = new TH1F("eta40phiEE", "eta40", 126, -3.15, 3.15);
   beautify(eta40phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta41phiEE = new TH1F("eta41phiEE", "eta41", 126, -3.15, 3.15);
   beautify(eta41phiEE, "#phi_{ECAL}", "Events", 2);
   
   TH1F* eta30dphi = new TH1F("eta30dphi", "eta30", 252, -6.3, 6.3);
   beautify(eta30dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta31dphi = new TH1F("eta31dphi", "eta31", 252, -6.3, 6.3);
   beautify(eta31dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta32dphi = new TH1F("eta32dphi", "eta32", 252, -6.3, 6.3);
   beautify(eta32dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta33dphi = new TH1F("eta33dphi", "eta33", 252, -6.3, 6.3);
   beautify(eta33dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta34dphi = new TH1F("eta34dphi", "eta34", 252, -6.3, 6.3);
   beautify(eta34dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta35dphi = new TH1F("eta35dphi", "eta35", 252, -6.3, 6.3);
   beautify(eta35dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta36dphi = new TH1F("eta36dphi", "eta36", 252, -6.3, 6.3);
   beautify(eta36dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta37dphi = new TH1F("eta37dphi", "eta37", 252, -6.3, 6.3);
   beautify(eta37dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta38dphi = new TH1F("eta38dphi", "eta38", 252, -6.3, 6.3);
   beautify(eta38dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta39dphi = new TH1F("eta39dphi", "eta39", 252, -6.3, 6.3);
   beautify(eta39dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta40dphi = new TH1F("eta40dphi", "eta40", 252, -6.3, 6.3);
   beautify(eta40dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta41dphi = new TH1F("eta41dphi", "eta41", 252, -6.3, 6.3);
   beautify(eta41dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   
   TH1F* eta30en = new TH1F("eta30en", "eta30", 60, 0, 150);
   beautify(eta30en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta31en = new TH1F("eta31en", "eta31", 60, 0, 150);
   beautify(eta31en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta32en = new TH1F("eta32en", "eta32", 60, 0, 150);
   beautify(eta32en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta33en = new TH1F("eta33en", "eta33", 60, 0, 150);
   beautify(eta33en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta34en = new TH1F("eta34en", "eta34", 60, 0, 150);
   beautify(eta34en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta35en = new TH1F("eta35en", "eta35", 60, 0, 150);
   beautify(eta35en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta36en = new TH1F("eta36en", "eta36", 60, 0, 150);
   beautify(eta36en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta37en = new TH1F("eta37en", "eta37", 60, 0, 150);
   beautify(eta37en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta38en = new TH1F("eta38en", "eta38", 60, 0, 150);
   beautify(eta38en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta39en = new TH1F("eta39en", "eta39", 60, 0, 150);
   beautify(eta39en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta40en = new TH1F("eta40en", "eta40", 60, 0, 150);
   beautify(eta40en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta41en = new TH1F("eta41en", "eta41", 60, 0, 150);
   beautify(eta41en, "E_{T}^{HF} [GeV]", "Events", 2);
   
   TH1F* eta30enEE = new TH1F("eta30enEE", "eta30", 60, 0, 150);
   beautify(eta30enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta31enEE = new TH1F("eta31enEE", "eta31", 60, 0, 150);
   beautify(eta31enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta32enEE = new TH1F("eta32enEE", "eta32", 60, 0, 150);
   beautify(eta32enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta33enEE = new TH1F("eta33enEE", "eta33", 60, 0, 150);
   beautify(eta33enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta34enEE = new TH1F("eta34enEE", "eta34", 60, 0, 150);
   beautify(eta34enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta35enEE = new TH1F("eta35enEE", "eta35", 60, 0, 150);
   beautify(eta35enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta36enEE = new TH1F("eta36enEE", "eta36", 60, 0, 150);
   beautify(eta36enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta37enEE = new TH1F("eta37enEE", "eta37", 60, 0, 150);
   beautify(eta37enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta38enEE = new TH1F("eta38enEE", "eta38", 60, 0, 150);
   beautify(eta38enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta39enEE = new TH1F("eta39enEE", "eta39", 60, 0, 150);
   beautify(eta39enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta40enEE = new TH1F("eta40enEE", "eta40", 60, 0, 150);
   beautify(eta40enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta41enEE = new TH1F("eta41enEE", "eta41", 60, 0, 150);
   beautify(eta41enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);   
     
   double alpha = 1;
   double beta = 1;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( jentry%1000 == 0 ) cout << "Processed " << jentry << " events" << endl;
      
      // PU bins
      bool PU1 = nvtx <= 6; 
      bool PU2 = nvtx > 6 && nvtx <= 12; 
      bool PU3 = nvtx > 12 && nvtx <= 18; 
      bool PU4 = nvtx > 18 && nvtx <= 24; 
      bool PU5 = nvtx > 24 && nvtx <= 30; 
      bool PU6 = nvtx > 30 && nvtx <= 36; 
      bool PU7 = nvtx > 36 && nvtx <= 42;
      bool PU8 = nvtx > 42 && nvtx <= 48;
      bool PU9 = nvtx > 48;
      
      vector<TLorentzVector> electrons;
      for(int i = 0; i != nele; ++i ) {
	int id = ele_id->at(i);
	if ( ele_mediumID->at(i) == 0 ) continue;
	if ( ele_pt->at(i) < 25.0 ) continue; // energetic to fire trigger
	TLorentzVector e;
	e.SetPtEtaPhiM(ele_pt->at(i), ele_eta->at(i), ele_phi->at(i), 0);
	electrons.push_back(e);
      }

      vector<TLorentzVector> hf;
      int firstIndex = -1;
      for(int i = 0; i != nhf; ++i) {
	if ( hf_pt->at(i) < 15.0 ) continue;
	if ( fabs(hf_eta->at(i)) < 2.964 ) continue;
	if ( fabs(hf_eta->at(i)) > 5.191 ) continue;
	if ( hf_hcal->at(i)/hf_ecal->at(i) > 1.2 ) continue;
	if ( hf_iso->at(i)/hf_en->at(i) > 0.55 ) continue;
	
	// L - S = ecal
	// 2S = hcal
	double L = hf_ecal->at(i) + 0.5*hf_hcal->at(i);
	double S = hf_hcal->at(i)/2;
	if ( L == 0 && S == 0 ) continue;

	// Raddam correction - only data
	// double corrL = L/getRaddamCorrection(run, fabs(hf_eta->at(i)));
	double corrL = L;
	// double corrS = S/getRaddamCorrection(run, fabs(hf_eta->at(i)));
	double corrS = S;
	double corrpT = hf_pt->at(i)*(corrL + corrS)/(L + S);
	
	// Use only long fiber energy
	alpha = 1;
	beta = 0;
	
	TLorentzVector e;
	double newpT = corrpT*(corrL*alpha + corrS*beta)/(corrL + corrS);
	newpT *= 1.00; // cross check
	e.SetPtEtaPhiM(newpT, hf_eta->at(i), hf_phi->at(i), 0);
	hf.push_back(e);
	
	if ( firstIndex == -1 ) firstIndex = i;
      }
      if ( electrons.size() > 1 || electrons.size() == 0 ) continue;
      if ( hf.size() == 0 ) continue;

      TLorentzVector e1, e2;
      e1 = electrons[0];
      e2 = hf[0];
      
      double L = hf_ecal->at(firstIndex) + 0.5*hf_hcal->at(firstIndex);
      double S = hf_hcal->at(firstIndex)/2;
      L *= alpha;
      S *= beta;

      double Mass = (e1+e2).M();

      // PU corrected mass
      TLorentzVector e1pu;
      TLorentzVector e2pu;
      double puCorrection = 1;
      //puCorrection = 1./(1.0 + 0.067/74.664*nvtx); // MC
      puCorrection = 1./(1.0 + 0.087/73.758*nvtx); // Data RunBC - no raddam
      e1pu.SetPtEtaPhiM(e1.Pt()*puCorrection, e1.Eta(), e1.Phi(), 0);
      e2pu.SetPtEtaPhiM(e2.Pt()*puCorrection, e2.Eta(), e2.Phi(), 0);
      double MassPUCorrected = (e1pu + e2pu).M();
      Mass = MassPUCorrected;
      
      h_mass->Fill(Mass);

      if ( PU1 ) nVtx1->Fill(Mass);
      if ( PU2 ) nVtx2->Fill(Mass);
      if ( PU3 ) nVtx3->Fill(Mass);
      if ( PU4 ) nVtx4->Fill(Mass);
      if ( PU5 ) nVtx5->Fill(Mass);
      if ( PU6 ) nVtx6->Fill(Mass);
      if ( PU7 ) nVtx7->Fill(Mass);
      if ( PU8 ) nVtx8->Fill(Mass);
      if ( PU9 ) nVtx9->Fill(Mass);
             
      float phi = e2pu.Phi();
      
      // iPhi bins
      bool iPhi1 = phi > 0*TMath::Pi()/18 && phi < 1*TMath::Pi()/18;
      bool iPhi3 = phi > 1*TMath::Pi()/18 && phi < 2*TMath::Pi()/18;
      bool iPhi5 = phi > 2*TMath::Pi()/18 && phi < 3*TMath::Pi()/18;
      bool iPhi7 = phi > 3*TMath::Pi()/18 && phi < 4*TMath::Pi()/18;
      bool iPhi9 = phi > 4*TMath::Pi()/18 && phi < 5*TMath::Pi()/18;
      bool iPhi11 = phi > 5*TMath::Pi()/18 && phi < 6*TMath::Pi()/18;
      bool iPhi13 = phi > 6*TMath::Pi()/18 && phi < 7*TMath::Pi()/18;
      bool iPhi15 = phi > 7*TMath::Pi()/18 && phi < 8*TMath::Pi()/18;
      bool iPhi17 = phi > 8*TMath::Pi()/18 && phi < 9*TMath::Pi()/18;
      bool iPhi19 = phi > 9*TMath::Pi()/18 && phi < 10*TMath::Pi()/18;
      bool iPhi21 = phi > 10*TMath::Pi()/18 && phi < 11*TMath::Pi()/18;
      bool iPhi23 = phi > 11*TMath::Pi()/18 && phi < 12*TMath::Pi()/18;
      bool iPhi25 = phi > 12*TMath::Pi()/18 && phi < 13*TMath::Pi()/18;
      bool iPhi27 = phi > 13*TMath::Pi()/18 && phi < 14*TMath::Pi()/18;
      bool iPhi29 = phi > 14*TMath::Pi()/18 && phi < 15*TMath::Pi()/18;
      bool iPhi31 = phi > 15*TMath::Pi()/18 && phi < 16*TMath::Pi()/18;
      bool iPhi33 = phi > 16*TMath::Pi()/18 && phi < 17*TMath::Pi()/18;
      bool iPhi35 = phi > 17*TMath::Pi()/18 && phi < 18*TMath::Pi()/18;
      bool iPhi37 = phi > -18*TMath::Pi()/18 && phi < -17*TMath::Pi()/18;
      bool iPhi39 = phi > -17*TMath::Pi()/18 && phi < -16*TMath::Pi()/18;
      bool iPhi41 = phi > -16*TMath::Pi()/18 && phi < -15*TMath::Pi()/18;
      bool iPhi43 = phi > -15*TMath::Pi()/18 && phi < -14*TMath::Pi()/18;
      bool iPhi45 = phi > -14*TMath::Pi()/18 && phi < -13*TMath::Pi()/18;
      bool iPhi47 = phi > -13*TMath::Pi()/18 && phi < -12*TMath::Pi()/18;
      bool iPhi49 = phi > -12*TMath::Pi()/18 && phi < -11*TMath::Pi()/18;
      bool iPhi51 = phi > -11*TMath::Pi()/18 && phi < -10*TMath::Pi()/18;
      bool iPhi53 = phi > -10*TMath::Pi()/18 && phi < -9*TMath::Pi()/18;
      bool iPhi55 = phi > -9*TMath::Pi()/18 && phi < -8*TMath::Pi()/18;
      bool iPhi57 = phi > -8*TMath::Pi()/18 && phi < -7*TMath::Pi()/18;
      bool iPhi59 = phi > -7*TMath::Pi()/18 && phi < -6*TMath::Pi()/18;
      bool iPhi61 = phi > -6*TMath::Pi()/18 && phi < -5*TMath::Pi()/18;
      bool iPhi63 = phi > -5*TMath::Pi()/18 && phi < -4*TMath::Pi()/18;
      bool iPhi65 = phi > -4*TMath::Pi()/18 && phi < -3*TMath::Pi()/18;
      bool iPhi67 = phi > -3*TMath::Pi()/18 && phi < -2*TMath::Pi()/18;
      bool iPhi69 = phi > -2*TMath::Pi()/18 && phi < -1*TMath::Pi()/18;
      bool iPhi71 = phi > -1*TMath::Pi()/18 && phi < 0*TMath::Pi()/18;
      
     
      if ( iPhi1 ) phi1->Fill(Mass);
      if ( iPhi3 ) phi3->Fill(Mass);
      if ( iPhi5 ) phi5->Fill(Mass);
      if ( iPhi7 ) phi7->Fill(Mass);
      if ( iPhi9 ) phi9->Fill(Mass);
      if ( iPhi11 ) phi11->Fill(Mass);
      if ( iPhi13 ) phi13->Fill(Mass);
      if ( iPhi15 ) phi15->Fill(Mass);
      if ( iPhi17 ) phi17->Fill(Mass);
      if ( iPhi19 ) phi19->Fill(Mass);
      if ( iPhi21 ) phi21->Fill(Mass);
      if ( iPhi23 ) phi23->Fill(Mass);
      if ( iPhi25 ) phi25->Fill(Mass);
      if ( iPhi27 ) phi27->Fill(Mass);
      if ( iPhi29 ) phi29->Fill(Mass);
      if ( iPhi31 ) phi31->Fill(Mass);
      if ( iPhi33 ) phi33->Fill(Mass);
      if ( iPhi35 ) phi35->Fill(Mass);
      if ( iPhi37 ) phi37->Fill(Mass);
      if ( iPhi39 ) phi39->Fill(Mass);
      if ( iPhi41 ) phi41->Fill(Mass);
      if ( iPhi43 ) phi43->Fill(Mass);
      if ( iPhi45 ) phi45->Fill(Mass);
      if ( iPhi47 ) phi47->Fill(Mass);
      if ( iPhi49 ) phi49->Fill(Mass);
      if ( iPhi51 ) phi51->Fill(Mass);
      if ( iPhi53 ) phi53->Fill(Mass);
      if ( iPhi55 ) phi55->Fill(Mass);
      if ( iPhi57 ) phi57->Fill(Mass);
      if ( iPhi59 ) phi59->Fill(Mass);
      if ( iPhi61 ) phi61->Fill(Mass);
      if ( iPhi63 ) phi63->Fill(Mass);
      if ( iPhi65 ) phi65->Fill(Mass);
      if ( iPhi67 ) phi67->Fill(Mass);
      if ( iPhi69 ) phi69->Fill(Mass);
      if ( iPhi71 ) phi71->Fill(Mass);
      
      double eta = e2pu.Eta();
      
      // iEta bins
      bool iEta30Plus = eta > 2.964 && eta < 3.139;
      bool iEta31Plus = eta > 3.139 && eta < 3.314;
      bool iEta32Plus = eta > 3.314 && eta < 3.489;
      bool iEta33Plus = eta > 3.489 && eta < 3.664;
      bool iEta34Plus = eta > 3.664 && eta < 3.839;
      bool iEta35Plus = eta > 3.839 && eta < 4.013;
      bool iEta36Plus = eta > 4.013 && eta < 4.191;
      bool iEta37Plus = eta > 4.191 && eta < 4.363;
      bool iEta38Plus = eta > 4.363 && eta < 4.538;
      bool iEta39Plus = eta > 4.538 && eta < 4.716;
      bool iEta40Plus = eta > 4.716 && eta < 4.889;
      bool iEta41Plus = eta > 4.889 && eta < 5.191;
      bool iEta30Minus = eta < -2.964 && eta > -3.139;
      bool iEta31Minus = eta < -3.139 && eta > -3.314;
      bool iEta32Minus = eta < -3.314 && eta > -3.489;
      bool iEta33Minus = eta < -3.489 && eta > -3.664;
      bool iEta34Minus = eta < -3.664 && eta > -3.839;
      bool iEta35Minus = eta < -3.839 && eta > -4.013;
      bool iEta36Minus = eta < -4.013 && eta > -4.191;
      bool iEta37Minus = eta < -4.191 && eta > -4.363;
      bool iEta38Minus = eta < -4.363 && eta > -4.538;
      bool iEta39Minus = eta < -4.538 && eta > -4.716;
      bool iEta40Minus = eta < -4.716 && eta > -4.889;
      bool iEta41Minus = eta < -4.889 && eta > -5.191;
      
      if ( iEta30Plus ) etaPlus30->Fill(Mass);
      if ( iEta31Plus ) etaPlus31->Fill(Mass);
      if ( iEta32Plus ) etaPlus32->Fill(Mass);
      if ( iEta33Plus ) etaPlus33->Fill(Mass);
      if ( iEta34Plus ) etaPlus34->Fill(Mass);
      if ( iEta35Plus ) etaPlus35->Fill(Mass);
      if ( iEta36Plus ) etaPlus36->Fill(Mass);
      if ( iEta37Plus ) etaPlus37->Fill(Mass);
      if ( iEta38Plus ) etaPlus38->Fill(Mass);
      if ( iEta39Plus ) etaPlus39->Fill(Mass);
      if ( iEta40Plus ) etaPlus40->Fill(Mass);
      if ( iEta41Plus ) etaPlus41->Fill(Mass);
      if ( iEta30Minus ) etaMinus30->Fill(Mass);
      if ( iEta31Minus ) etaMinus31->Fill(Mass);
      if ( iEta32Minus ) etaMinus32->Fill(Mass);
      if ( iEta33Minus ) etaMinus33->Fill(Mass);
      if ( iEta34Minus ) etaMinus34->Fill(Mass);
      if ( iEta35Minus ) etaMinus35->Fill(Mass);
      if ( iEta36Minus ) etaMinus36->Fill(Mass);
      if ( iEta37Minus ) etaMinus37->Fill(Mass);
      if ( iEta38Minus ) etaMinus38->Fill(Mass);
      if ( iEta39Minus ) etaMinus39->Fill(Mass);
      if ( iEta40Minus ) etaMinus40->Fill(Mass);
      if ( iEta41Minus ) etaMinus41->Fill(Mass);
      
      h_nvtx->Fill(nvtx);
      
      if ( iEta30Plus || iEta30Minus ) {
	eta30nvtx->Fill(nvtx);
	eta30phi->Fill(e2.Phi());
	eta30etaEE->Fill(e1.Eta());
	eta30phiEE->Fill(e1.Phi());
	eta30dphi->Fill(e1.Phi()-e2.Phi());
	eta30en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta30enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta31Plus || iEta31Minus ) {
	eta31nvtx->Fill(nvtx);
	eta31phi->Fill(e2.Phi());
	eta31etaEE->Fill(e1.Eta());
	eta31phiEE->Fill(e1.Phi());
	eta31dphi->Fill(e1.Phi()-e2.Phi());
	eta31en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta31enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta32Plus || iEta32Minus ) {
	eta32nvtx->Fill(nvtx);
	eta32phi->Fill(e2.Phi());
	eta32etaEE->Fill(e1.Eta());
	eta32phiEE->Fill(e1.Phi());
	eta32dphi->Fill(e1.Phi()-e2.Phi());
	eta32en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta32enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta33Plus || iEta33Minus ) {
	eta33nvtx->Fill(nvtx);
	eta33phi->Fill(e2.Phi());
	eta33etaEE->Fill(e1.Eta());
	eta33phiEE->Fill(e1.Phi());
	eta33dphi->Fill(e1.Phi()-e2.Phi());
	eta33en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta33enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta34Plus || iEta34Minus ) {
	eta34nvtx->Fill(nvtx);
	eta34phi->Fill(e2.Phi());
	eta34etaEE->Fill(e1.Eta());
	eta34phiEE->Fill(e1.Phi());
	eta34dphi->Fill(e1.Phi()-e2.Phi());
	eta34en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta34enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta35Plus || iEta35Minus ) {
	eta35nvtx->Fill(nvtx);
	eta35phi->Fill(e2.Phi());
	eta35etaEE->Fill(e1.Eta());
	eta35phiEE->Fill(e1.Phi());
	eta35dphi->Fill(e1.Phi()-e2.Phi());
	eta35en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta35enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta36Plus || iEta36Minus ) {
	eta36nvtx->Fill(nvtx);
	eta36phi->Fill(e2.Phi());
	eta36etaEE->Fill(e1.Eta());
	eta36phiEE->Fill(e1.Phi());
	eta36dphi->Fill(e1.Phi()-e2.Phi());
	eta36en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta36enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta37Plus || iEta37Minus ) {
	eta37nvtx->Fill(nvtx);
	eta37phi->Fill(e2.Phi());
	eta37etaEE->Fill(e1.Eta());
	eta37phiEE->Fill(e1.Phi());
	eta37dphi->Fill(e1.Phi()-e2.Phi());
	eta37en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta37enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta38Plus || iEta38Minus ) {
	eta38nvtx->Fill(nvtx);
	eta38phi->Fill(e2.Phi());
	eta38etaEE->Fill(e1.Eta());
	eta38phiEE->Fill(e1.Phi());
	eta38dphi->Fill(e1.Phi()-e2.Phi());
	eta38en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta38enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta39Plus || iEta39Minus ) {
	eta39nvtx->Fill(nvtx);
	eta39phi->Fill(e2.Phi());
	eta39etaEE->Fill(e1.Eta());
	eta39phiEE->Fill(e1.Phi());
	eta39dphi->Fill(e1.Phi()-e2.Phi());
	eta39en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta39enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta40Plus || iEta40Minus ) {
	eta40nvtx->Fill(nvtx);
	eta40phi->Fill(e2.Phi());
	eta40etaEE->Fill(e1.Eta());
	eta40phiEE->Fill(e1.Phi());
	eta40dphi->Fill(e1.Phi()-e2.Phi());
	eta40en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta40enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta41Plus || iEta41Minus ) {
	eta41nvtx->Fill(nvtx);
	eta41phi->Fill(e2.Phi());
	eta41etaEE->Fill(e1.Eta());
	eta41phiEE->Fill(e1.Phi());
	eta41dphi->Fill(e1.Phi()-e2.Phi());
	eta41en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta41enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      
   }

   h_mass->Write();
   h_nvtx->Write();
 
   etaPlus30->Write();
   etaPlus31->Write();
   etaPlus32->Write();
   etaPlus33->Write();
   etaPlus34->Write();
   etaPlus35->Write();
   etaPlus36->Write();
   etaPlus37->Write();
   etaPlus38->Write();
   etaPlus39->Write();
   etaPlus40->Write();
   etaPlus41->Write();
   etaMinus30->Write();
   etaMinus31->Write();
   etaMinus32->Write();
   etaMinus33->Write();
   etaMinus34->Write();
   etaMinus35->Write();
   etaMinus36->Write();
   etaMinus37->Write();
   etaMinus38->Write();
   etaMinus39->Write();
   etaMinus40->Write();
   etaMinus41->Write();

   phi1->Write();
   phi3->Write();
   phi5->Write();
   phi7->Write();
   phi9->Write();
   phi11->Write();
   phi13->Write();
   phi15->Write();
   phi17->Write();
   phi19->Write();
   phi21->Write();
   phi23->Write();
   phi25->Write();
   phi27->Write();
   phi29->Write();
   phi31->Write();
   phi33->Write();
   phi35->Write();
   phi37->Write();
   phi39->Write();
   phi41->Write();
   phi43->Write();
   phi45->Write();
   phi47->Write();
   phi49->Write();
   phi51->Write();
   phi53->Write();
   phi55->Write();
   phi57->Write();
   phi59->Write();
   phi61->Write();
   phi63->Write();
   phi65->Write();
   phi67->Write();
   phi69->Write();
   phi71->Write();
   
   nVtx1->Write();
   nVtx2->Write();
   nVtx3->Write();
   nVtx4->Write();
   nVtx5->Write();
   nVtx6->Write();
   nVtx7->Write();
   nVtx8->Write();
   nVtx9->Write();
   
   eta30nvtx->Write();
   eta31nvtx->Write();
   eta32nvtx->Write();
   eta33nvtx->Write();
   eta34nvtx->Write();
   eta35nvtx->Write();
   eta36nvtx->Write();
   eta37nvtx->Write();
   eta38nvtx->Write();
   eta39nvtx->Write();
   eta40nvtx->Write();
   eta41nvtx->Write();
   
   eta30phi->Write();
   eta31phi->Write();
   eta32phi->Write();
   eta33phi->Write();
   eta34phi->Write();
   eta35phi->Write();
   eta36phi->Write();
   eta37phi->Write();
   eta38phi->Write();
   eta39phi->Write();
   eta40phi->Write();
   eta41phi->Write();
   
   eta30etaEE->Write();
   eta31etaEE->Write();
   eta32etaEE->Write();
   eta33etaEE->Write();
   eta34etaEE->Write();
   eta35etaEE->Write();
   eta36etaEE->Write();
   eta37etaEE->Write();
   eta38etaEE->Write();
   eta39etaEE->Write();
   eta40etaEE->Write();
   eta41etaEE->Write();
   
   eta30phiEE->Write();
   eta31phiEE->Write();
   eta32phiEE->Write();
   eta33phiEE->Write();
   eta34phiEE->Write();
   eta35phiEE->Write();
   eta36phiEE->Write();
   eta37phiEE->Write();
   eta38phiEE->Write();
   eta39phiEE->Write();
   eta40phiEE->Write();
   eta41phiEE->Write();
   
   eta30dphi->Write();
   eta31dphi->Write();
   eta32dphi->Write();
   eta33dphi->Write();
   eta34dphi->Write();
   eta35dphi->Write();
   eta36dphi->Write();
   eta37dphi->Write();
   eta38dphi->Write();
   eta39dphi->Write();
   eta40dphi->Write();
   eta41dphi->Write();
   
   eta30en->Write();
   eta31en->Write();
   eta32en->Write();
   eta33en->Write();
   eta34en->Write();
   eta35en->Write();
   eta36en->Write();
   eta37en->Write();
   eta38en->Write();
   eta39en->Write();
   eta40en->Write();
   eta41en->Write();
   
   eta30enEE->Write();
   eta31enEE->Write();
   eta32enEE->Write();
   eta33enEE->Write();
   eta34enEE->Write();
   eta35enEE->Write();
   eta36enEE->Write();
   eta37enEE->Write();
   eta38enEE->Write();
   eta39enEE->Write();
   eta40enEE->Write();
   eta41enEE->Write();
     
}


