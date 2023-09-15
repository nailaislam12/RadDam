#include <sys/stat.h>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include "setTDRStyle.C"
#include "TError.h"

// Need to define these here
TF1 *fInter1, *fInter2;
// Define the functions here too for ease
double FindIntercept(TF1*, TF1*);
double finter( double *, double*);
void MarkAndText( double, double);

double finter( double *x, double*par) {
   return TMath::Abs(fInter1->EvalPar(x,par) - fInter2->EvalPar(x,par));
}

double FindIntercept(TF1* f1, TF1* f2) {
  fInter1 = f1;
  fInter2 = f2;
  TF1 *fint = new TF1( "fint", finter, -10, 10, 0);
  double xint = fint->GetMinimumX(); 
  MarkAndText( xint, f1->Eval( xint));
  return xint;
}

void MarkAndText( double xpos, double ypos) {
  TMarker *m = new TMarker( xpos, ypos, 24);
  m->SetMarkerColor(kBlack);
  m->SetMarkerSize(3);
  m->Draw();
  
  TString xIntString = TString::Format("Intercept =  %.3f", xpos);
  TLatex TextXint = TLatex();
  TextXint.SetTextFont(42);
  TextXint.SetNDC();
  TextXint.SetTextSize(0.04);
  TextXint.DrawLatex( 0.62, 0.4, xIntString);
}

void CalcRaddamFactors() {
  gErrorIgnoreLevel = kWarning;
  setTDRStyle();
  TString figdir = "FactorFigures22_noPU/";
  // idk man...
  TCanvas* pcanvas = new TCanvas("canvasPlus"); 
  TCanvas* mcanvas = new TCanvas("canvasMinus");
  TCanvas* gcanvas = new TCanvas("canvasGraph");

  TFile *fMC = new TFile("outplots/outplots2022_mc_noPU.root");
  TFile *fData = new TFile("outplots/outplots2022_data_noPU_radFactors_test.root");
  TF1 *funcGaus = new TF1("fitGaus","gaus",0,100);
  funcGaus->SetLineWidth(2);
  TLatex CMSlabel = TLatex(); 
  CMSlabel.SetTextFont(42);     
  CMSlabel.SetNDC();     
  CMSlabel.SetTextSize(0.04);
  gStyle->SetPalette(0);
  gStyle->SetPadLeftMargin(0.13);

  if ((!fData) || (!fData->IsOpen())) {
    std::cout << "Data file didn't exist!" << std::endl;
    return;
  } else if ((!fMC) || (!fMC->IsOpen())){
    std::cout << "MC file didn't exist!" << std::endl;
    return;
  }    
  
  // For extracting the factor
  Double_t meansPlus[11] = {0};
  Double_t errorsPlus[11] = {0};
  Double_t meansMinus[11] = {0};
  Double_t errorsMinus[11] = {0};
  Double_t factors[11] = {0};
  Double_t ferrors[11] = {0};
  std::map< int, double> RaddamFactors;
  for (int i = 10; i <= 20; ++i)
    factors[i-10] = i / 10.0;

  // Get the MC / Data ratio
  std::map< int, double> RaddamRatios;
  TH1F* pRatio = new TH1F("pRatio", "", 10, 29.5, 39.5);
  TH1F* mRatio = new TH1F("mRatio", "", 10, 29.5, 39.5);
  // Double_t ietas[10] = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
  // Double_t xErrors[10] = {0};
  // Double_t pRatio[10] = {0};
  // Double_t mRatio[10] = {0};
  // Double_t pRatioErrors[10] = {0};
  // Double_t mRatioErrors[10] = {0};

  // canvas->cd();
  // Loop over Etas
  for (int i = 30; i <= 39; ++i) { 
    std::cout << ">> iEta: " << i << std::endl;
    // First MC PLUS
    TString EtaPlusNum = TString::Format("etaPlus%i", i);
    TH1F *hEtaPlusMC = (TH1F*)fMC->Get(EtaPlusNum);
    funcGaus->SetRange(hEtaPlusMC->GetMaximumBin()+5,hEtaPlusMC->GetMaximumBin()+35);
    TFitResultPtr FitResultEtaPlusMC = hEtaPlusMC->Fit("fitGaus","QRS");
    double mcMeanPlus = funcGaus->GetParameter(1);
    
    // Now MC MINUS
    TString EtaMinusNum = TString::Format("etaMinus%i", i);
    TH1F *hEtaMinusMC = (TH1F*)fMC->Get(EtaMinusNum);
    funcGaus->SetRange(hEtaMinusMC->GetMaximumBin()+5,hEtaMinusMC->GetMaximumBin()+35);
    TFitResultPtr FitResultEtaMinusMC = hEtaMinusMC->Fit("fitGaus","QRS");
    double mcMeanMinus = funcGaus->GetParameter(1);

    // Data Starts Here
    TString EtaPlusNameData = TString::Format( figdir + "EtaPlus%i_data.png", i);
    TString EtaMinusNameData = TString::Format( figdir + "EtaMinus%i_data.png", i);

    // Loop over 10 factors
    for (int f = 0; f <= 10; ++f) {
      pcanvas->cd(0);
      TString EtaPlusNum = TString::Format("h_mass_etaPlus%i_Xn%i", i, f);

      TH1F *hEtaPlusData = (TH1F*)fData->Get(EtaPlusNum);
      if (!hEtaPlusData) {
	std::cout << "Histogram: " << EtaPlusNum << " not found :(" << std::endl;
	// continue;
	return;
      }

      if (f == 0) {
	hEtaPlusData->Draw( "PLC");
	hEtaPlusData->GetXaxis()->SetTitle("M_{e, hf} (GeV)");
	hEtaPlusData->GetYaxis()->SetTitle("Events");
	CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
      } else {
	hEtaPlusData->Draw("same PLC");
      } // end Plus Draw
      
      funcGaus->SetRange(hEtaPlusData->GetMaximumBin()+5,hEtaPlusData->GetMaximumBin()+35);
      TFitResultPtr FitResultEtaPlusData = hEtaPlusData->Fit("fitGaus","QRS");
      meansPlus[f] = funcGaus->GetParameter(1);
      errorsPlus[f] = funcGaus->GetParError(1);
      
      mcanvas->cd(0);
      EtaMinusNum = TString::Format("h_mass_etaMinus%i_Xn%i", i, f);
      TH1F *hEtaMinusData = (TH1F*)fData->Get(EtaMinusNum);
      if (!hEtaMinusData) {
	std::cout << "Histogram: " << EtaMinusNum << " not found :(" << std::endl;
	continue;
      }
      
      if (f == 0) {
	hEtaMinusData->Draw( "PLC"); 
	hEtaMinusData->GetXaxis()->SetTitle("M_{e, hf} (GeV)");
	hEtaMinusData->GetYaxis()->SetTitle("Events");
	CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
      } else {
	hEtaMinusData->Draw("same PLC");
      } // end Minus Draw

      funcGaus->SetRange(hEtaMinusData->GetMaximumBin()+5,hEtaMinusData->GetMaximumBin()+35);
      TFitResultPtr FitResultEtaMinusData = hEtaMinusData->Fit("fitGaus","QRS");
      meansMinus[f] = funcGaus->GetParameter(1);
      errorsMinus[f] = funcGaus->GetParError(1);
		
    } // end factors loop

    // Print them all together...
    pcanvas->cd(0);
    pcanvas->Print(EtaPlusNameData);
    pcanvas->Clear();
    mcanvas->cd(0);
    mcanvas->Print(EtaMinusNameData);
    mcanvas->Clear();

    // Get the nominal means
    RaddamRatios[ i] = mcMeanPlus / meansPlus[0];
    RaddamRatios[-i] = mcMeanMinus / meansMinus[0];
    pRatio->SetBinContent( i - 30, RaddamRatios[ i]);
    mRatio->SetBinContent( i - 30, RaddamRatios[-i]);
    pRatio->SetBinError( i - 30, errorsPlus[0]);
    mRatio->SetBinError( i - 30, errorsMinus[0]);

    // Plot the factors
    gStyle->SetOptFit(0);
    gcanvas->cd();
    auto graphPlus = new TGraphErrors( 11, factors, meansPlus, ferrors, errorsPlus);
    graphPlus->SetTitle(TString::Format("Factor vs Z Peak EtaPlus%i", i));
    graphPlus->GetXaxis()->SetTitle("#alpha Factor");
    graphPlus->GetYaxis()->SetTitle("M_{e, hf} (GeV)");
    graphPlus->SetLineColor( kBlue);
    graphPlus->SetLineWidth( 2);
    graphPlus->Draw();

    // Fit the points to a line
    TF1* factorFitPlus = new TF1( "factorFitPlus", "[0]*x + [1]");
    graphPlus->Fit( factorFitPlus, "Q");

    // Draw the MC Mean as a constant line
    TF1 *mcMeanPlusLine = new TF1( "mcMeanPlus", "[0]", -10, 10);
    mcMeanPlusLine->SetParameter( 0, mcMeanPlus);
    mcMeanPlusLine->SetLineWidth( 2);
    mcMeanPlusLine->SetLineColor( kBlack);
    mcMeanPlusLine->SetLineStyle( kDashed);
    mcMeanPlusLine->Draw("same");

    // Add a Legend
    auto legPlus = new TLegend( 0.2, 0.7, 0.5, 0.9);
    legPlus->AddEntry( graphPlus, "Corr Z Peak (data)");
    legPlus->AddEntry( mcMeanPlusLine, "MC Z Peak Mean");
    legPlus->Draw();

    // Now get the point of intersection
    RaddamFactors[i] = FindIntercept( mcMeanPlusLine, factorFitPlus);
    std::cout << ">>> XINT (+): " << RaddamFactors[i] << std::endl;
    gcanvas->Print( TString::Format( figdir + "EtaPlus%i_factorgraph.png", i));
    gcanvas->Clear();

    // Now EtaMinus
    auto graphMinus = new TGraphErrors( 11, factors, meansMinus, ferrors, errorsMinus);
    graphMinus->SetTitle(TString::Format("Factor vs Z Peak EtaMinus%i", i));
    graphMinus->GetXaxis()->SetTitle("#alpha Factor");
    graphMinus->GetYaxis()->SetTitle("M_{e, hf} (GeV)");
    graphMinus->SetLineColor( kBlue);
    graphMinus->SetLineWidth( 2);
    graphMinus->Draw();
    TF1* factorFitMinus = new TF1( "factorFitMinus", "[0]*x + [1]");
    graphMinus->Fit( factorFitMinus, "Q");
    TF1 *mcMeanMinusLine = new TF1( "mcMeanMinus", "[0]", -10, 10);
    mcMeanMinusLine->SetParameter( 0, mcMeanMinus);
    mcMeanMinusLine->SetLineWidth( 2);
    mcMeanMinusLine->SetLineColor( kBlack);
    mcMeanMinusLine->SetLineStyle( kDashed);
    mcMeanMinusLine->Draw("same");
    auto legMinus = new TLegend( 0.2, 0.7, 0.5, 0.9);
    legMinus->AddEntry( graphMinus, "Corr Z Peak (data)");
    legMinus->AddEntry( mcMeanMinusLine, "MC Z Peak Mean");
    legMinus->Draw();

    // Now get the point of intersection
    RaddamFactors[-i] = FindIntercept( mcMeanMinusLine, factorFitMinus);
    std::cout << ">>> XINT (-): " << RaddamFactors[-i] << std::endl;

    gcanvas->Print( TString::Format( figdir + "EtaMinus%i_factorgraph.png", i));
    
  } // end Eta loop

  // Plot the nominal ratios
  /*
  TCanvas* r = new TCanvas("ratio", "", 700, 900);
  pRatio->SetMarkerColor(kRed);
  pRatio->Draw();
  mRatio->SetMarkerColor(kBlue);
  mRatio->Draw("same");
  auto legRatio = new TLegend( 0.2, 0.2, 0.5, 0.4);
  legRatio->AddEntry( pRatio, "HF+ Ratio");
  legRatio->AddEntry( mRatio, "HF- Ratio");
  legRatio->Draw();
  r->Print( TString(figdir + "MCData_ratio.png"));
  r->SaveAs( TString(figdir + "MCData_ratio.C"));
  */

  // Now print (or save some fun way) the Raddam Factors (alpha)
  std::cout << "\n" << std::endl;
  std::cout << "*** RADDAM FACTORS for iEtas *** " << std::endl;
  for (auto ele : RaddamFactors) {
    std::cout << "iEta " << setw(3) << ele.first << ": " << ele.second << std::endl;
  }

  // Now print (or save some fun way) the Raddam Ratios (mc/data)
  std::cout << "\n" << std::endl;
  std::cout << "*** RADDAM RATIOS for iEtas *** " << std::endl;
  for (auto ele : RaddamRatios) {
    std::cout << "iEta " << setw(3) << ele.first << ": " << ele.second << std::endl;
  }

  std::cout << "All Done :)" << std::endl;
  return;  
}
