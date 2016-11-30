#include <cassert>
#include <cmath>

#include "TH1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TRandom.h"

void testExpWeight(){

  /*
  TH1F *h1 = new TH1F("h1","Exp 0.4",100,0.0,4.0);
  TH1F *h2 = new TH1F("h2","Exp 0.25",100,0.0,4.0);

  for(int i=0; i<50000; i++){
    double r4 = gRandom->Exp(0.4);
    h1->Fill(r4);
    double w = exp(-r4/0.25) / exp(-r4/0.4);
    h2->Fill(r4, w);
  }
  
  TCanvas * c = new TCanvas("c","",800,800);
  c->Divide(2,1);
  c->cd(1)->SetLogy();
  h1->Draw();
  c->cd(2)->SetLogy();
  h2->Draw();
  */


  TFile *f = new TFile("/data1/sblusk/Xibc/JpsiX/mc/JpsiLc_mc.tuned.pkpi.wMVA.root");
  tree = (TTree*)f->Get("mytree");
  
  TH1* h1 = new TH1D("h1","BDT disrtibution, unweighted",200,-1.0,1.0);
  TH1* h2 = new TH1D("h2","BDT disrtibution, weighted",200,-1.0,1.0);
  TH1* h1s = new TH1D("h1s","Cumulative BDT disrtibution, unweighted",200,-1.0,1.0);
  TH1* h2s = new TH1D("h2s","Cumulative BDT disrtibution, weighted",200,-1.0,1.0);
  tree->Draw("BDTG>>h1","BDTG>-2.5");
  tree->Draw("BDTG>>h2","(exp(-1000*Xb_TAU/0.25)/exp(-1000*Xb_TAU/0.4))*(BDTG>-2.5)");

  TH1* t1 = new TH1D("t1","decay time disrtibution, unweighted",200,0.0,5.0);
  TH1* t2 = new TH1D("t2","decay time disrtibution, weighted",200,0.0,5.0);
  tree->Draw("1000*Xb_TAU>>t1","BDTG>-2.5");
  tree->Draw("1000*Xb_TAU>>t2","(exp(-1000*Xb_TAU/0.25)/exp(-1000*Xb_TAU/0.4))*(BDTG>-2.5)");

  TCanvas * c = new TCanvas("c","",800,500);
  c->Divide(2,1);
  c->cd(1);
  h1->Draw();
  c->cd(2);
  h2->Draw();

  h1->ComputeIntegral();
  h2->ComputeIntegral();
  double* integral1 = h1->GetIntegral();
  double* integral2 = h2->GetIntegral();
  h1s->SetContent(integral1);
  h2s->SetContent(integral2);
  for(int i=0; i<h1s->GetNbinsX(); i++){
    h1s->SetBinContent(i+1,1.0-h1s->GetBinContent(i+1));
    h2s->SetBinContent(i+1,1.0-h2s->GetBinContent(i+1));    
  }
  h2s->SetLineColor(kRed);

  TCanvas * c1 = new TCanvas("c1","",800,500);
  h1s->Draw();
  h2s->Draw("same");

  t2->SetLineColor(kRed);
  TCanvas * c2 = new TCanvas("c2","Decay Time Dist",800,500);
  c2->Divide(2,1);
  c2->cd(1);
  t1->Draw();
  c2->cd(2);
  t2->Draw();
  



}
