// ROOT macro file for plotting example B4 histograms 
// 
// Can be run from ROOT session:
// root[0] .x plotHisto.C

{
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  // Draw histos filled by Geant4 simulation 
  //   

  // Open file filled by Geant4 simulation 
  TFile f("B4.root");

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "c1", 900,900);
  gStyle->SetOptStat(0);
  c1->Divide(1,1);
  
 
  // Draw Lgap histogram in the pad 4
  // with logaritmic scale for y
  c1->cd(1);
  //gPad->SetLogy(1);
  TH1D* hist1 = (TH1D*)f.Get("XY");
  //hist1->Draw("HIST");
  hist1->Draw("cont4z");
}  
