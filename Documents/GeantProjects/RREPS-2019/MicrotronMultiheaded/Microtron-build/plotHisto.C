// ROOT macro file for plotting example B4 histograms 
// 
// Can be run from ROOT session:
// root[0] .x plotHisto.C

{

   //gROOT->Reset();

   // Open file filled by Geant4 simulation 
   //TFile f("B4.root");
   TFile *f = TFile::Open("B4.root");
   TH1D *h2 = (TH1D *)f->Get("electronSpectra");


   TCanvas * CPol = new TCanvas("C1","",500,500);

   int numberIterations = h2->GetNcells();
   int amplitudeBin = h2->GetMaximum();

   Double_t theta[1000];
   Double_t radius[1000];
   Double_t etheta[1000];
   Double_t eradius[1000];
   for (int i=0; i< numberIterations; i++) {
      theta[i]   = h2->GetXaxis()->GetBinCenter(i);//(i+1)*(TMath::Pi()/4.);
      //radius[i]   = h2->GetZaxis()->GetBinCenter(i);//(i+1)*(TMath::Pi()/4.);
      radius[i]  = h2->GetBinContent(i);//
      etheta[i]  = h2-> GetBinError(i);
      
      eradius[i] =h2->GetBinError(i);
      cout << theta[i] << "  " << radius[i] << "  " << eradius[i]<< endl;
   }
    TH1F *hnew = (TH1F*)f->Clone("hnew");
    cout << hnew <<endl;

   //TGraphPolar * hist1 = new TGraphPolar(8, theta, radius, etheta, eradius);
   TGraphPolar * hist1 = new TGraphPolar(numberIterations, theta, radius);//, etheta);//, eradius);
   //TGraphPolar* hist1 = (TGraphPolar*)f.Get("YPolar");
   hist1->SetTitle("TGraphPolar Example");
   hist1->SetMarkerStyle(20);
   hist1->SetMarkerSize(1.);
   hist1->SetMarkerColor(4);
   hist1->SetLineColor(2);
   hist1->SetLineWidth(3);
   hist1->Draw("CP SAME");
   // Update, otherwise GetPolargram returns 0
   CPol->Update();
   hist1->GetPolargram()->SetToRadian();
   return CPol;
}
