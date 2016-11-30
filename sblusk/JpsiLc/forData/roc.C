TChain* getBack(TString mode, TString tagCond){

  TString topdirBack = "/data1/sblusk/Xibc/JpsiX/data/"+mode+"/";
  TChain *ch = new TChain("","mytree");


  if(mode=="D0p") {
    topdirBack = "/data1/sblusk/Xibc/D0p/data/";
    TString backFile1 = "X2D0p.pkpi.ws.wMVA.def2.root";
    ch->Add(topdirBack+backFile1+"/mytree");
  }else{
    TString backFile1 = "All_2011_MAGDN.pkpi.ws.wMVA."+tagCond+".root ";
    TString backFile2 = "All_2011_MAGUP.pkpi.ws.wMVA."+tagCond+".root ";
    TString backFile3 = "All_2012_MAGDN.pkpi.ws.wMVA."+tagCond+".root ";
    TString backFile4 = "All_2012_MAGUP.pkpi.ws.wMVA."+tagCond+".root ";
    ch->Add(topdirBack+backFile1+"/mytree");
    ch->Add(topdirBack+backFile2+"/mytree");
    ch->Add(topdirBack+backFile3+"/mytree");
    ch->Add(topdirBack+backFile4+"/mytree");
  }
  
  return ch;
  

}

TChain* getSignal(TString mode, TString tagCond){

  TChain *ch = new TChain("","mytree");
  TString topdirMC = "/data1/sblusk/Xibc/JpsiX/mc/"+mode+"/";  
  TString signalFile = mode+"_mc.tuned.pkpi.wMVA."+tagCond+".root";
  if(mode == "D0p"){
    topdirMC = "/data1/sblusk/Xibc/D0p/mc/";
    signalFile = "x2d0p_mc.tuned.pkpi.wMVA."+tagCond+".root";
  }
  TString sigFile1 = topdirMC+signalFile;
  ch->Add(sigFile1+"/mytree");  
  return ch;
}



void addGraphics(TH1 *h, int marker = 20, int color = 1){
  h->SetStats(kFALSE);
  h->SetMarkerStyle(marker);
  h->SetLineColor(color);
  h->SetMarkerColor(color);
  h->SetMarkerSize(1.5);
  h->GetXaxis()->SetTitleOffset(1.2);  
  h->GetYaxis()->SetTitleOffset(1.2);
  h->GetXaxis()->SetTitleSize(0.055);  
  h->GetYaxis()->SetTitleSize(0.055);
  h->GetXaxis()->SetLabelSize(0.045);  
  h->GetYaxis()->SetLabelSize(0.045);  
  h->GetXaxis()->SetNdivisions(505);
  h->GetYaxis()->SetNdivisions(505);  
}

void addGraphics(TGraph *h, int int color = 1){
  h->SetLineColor(color);
  h->GetXaxis()->SetTitleOffset(0.9);  
  h->GetYaxis()->SetTitleOffset(1.0);
  h->GetXaxis()->SetTitleSize(0.05);  
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetLabelSize(0.045);  
  h->GetYaxis()->SetLabelSize(0.045);  
  h->GetXaxis()->SetNdivisions(505);
  h->GetYaxis()->SetNdivisions(505);  
}


void roc(TString mode="JpsiLc", TString tagCond="test1"){
  
  TChain* ts = getSignal(mode,tagCond);
  TChain* tb = getBack(mode,tagCond);

  TString cuts = "Xb_TRUEID!=0 && abs(Xc_M-2287)<25";
  TString cutb = "abs(Xc_M-2287)<25";
  if(mode == "D0p"){
    cuts = "B_TRUEID!=0 && abs(D_M-1865)<25";
    cutb = "abs(D_M-1865)<25";
  }else if(mode=="JpsiXic"){
    cuts = "Xb_TRUEID!=0 && abs(Xc_M-2468)<25";\
    cutb = "abs(Xc_M-2468)<25";
  }
  cuts = cuts && "Xc_IPCHI2_OWNPV>4";
  cutb = cutb && "Xc_IPCHI2_OWNPV>4";
  
  
  //TString sigfile = topdirMC+signalFile;
  //TString backfile = topdirBack+backFile;

  
  /*
  TFile *fs = new TFile(sigfile);
  TFile *fb = new TFile(backfile);
  TTree *ts = fs->Get("mytree");
  TTree *tb = fb->Get("mytree");
  */
  
  //ts->Draw("BDTG");
  
  double massRes = 60.0;

  const int nbins = 401;
  double lowVal = -1.0 - (2.0/(nbins-1));

  TFile *fout = new TFile("RootFiles/ROCCurves_"+tagCond+".root","RECREATE");  

  TH1* h1 = new TH1D("h1","BDT disrtibution, signal",nbins,lowVal,1.0); h1->Sumw2();
  TH1* h2 = new TH1D("h2","BDT disrtibution, back",nbins,lowVal,1.0);h2->Sumw2();
  TH1* h2a = new TH1D("h2a","BDT disrtibution, back",nbins,lowVal,1.0); h2a->Sumw2();
  TH1* h1s = new TH1D("h1s","Cumulative BDT distribution",nbins,lowVal,1.0); h1s->Sumw2();
  TH1* h2s = new TH1D("h2s","No. back / 60 MeV ",nbins,lowVal,1.0); h2s->Sumw2();
  TH2F* h3 = new TH2F("h3","BDT output vs Mass",50,6500,7000,nbins,lowVal,1.0);
  TH2F* h4 = new TH2F("h4","Back Eff vs Signal Eff ",nbins,0.0,1.0, nbins,0.0,1.0); 
  ts->Draw("BDTG>>h1",cuts);
  tb->Draw("BDTG>>h2a",cutb);
  tb->Draw("BDTG>>h2",cutb&&"Xb_M>6500&&Xb_M<7000");
  tb->Draw("BDTG:Xb_M>>h3",cutb&&"Xb_M>6500&&Xb_M<7000");
  h1->SetBinContent(1,h1->GetBinContent(0)+h1->GetBinContent(1));
  h2->SetBinContent(1,h2->GetBinContent(0)+h2->GetBinContent(1));
  //h2->Scale(massRes/500.0);
  double nBackT = h2->Integral(1,nbins);
  TH1F *h2b = (TH1F*)h2->Clone("h2b");
  h2b->SetTitle("Cumulative BDT distribution");
  TH1F *h2c = (TH1F*)h2->Clone("h2c");
  h2c->SetTitle("sqrt(Cumulative BDT distribution)");
  

  h1->ComputeIntegral();
  h2->ComputeIntegral();
  double* integral1 = h1->GetIntegral();
  double* integral2 = h2->GetIntegral();
  h1s->SetContent(integral1);
  h2s->SetContent(integral2);
  double nBackSqrt[nbins];
  double eSig[nbins];
  double eBack[nbins];
  double nBack[nbins];

  double v;
  int numToPlot = nbins;
  for(int i=0; i<h1s->GetNbinsX(); i++){
    h1s->SetBinContent(i+1,1.0-h1s->GetBinContent(i+1));
    v = h2s->GetBinContent(i+1);
    h2s->SetBinContent(i+1,(1.0-v)*nBackT);    // Back yield
    h2b->SetBinContent(i+1,1-v); // Background Rej.
    h2c->SetBinContent(i+1,sqrt(1.0-v)); // Sqrt(back)
    h4->SetBinContent(i+1,v);
    eSig[i] = h1s->GetBinContent(i+1);
    eBack[i] = h2b->GetBinContent(i+1);
    nBackSqrt[i] = sqrt((1.0-v)*nBack)*(massRes/500.0);
    nBack[i] = (1.0-v)*nBackT;
    cout << "BDT Cut = " << h1->GetBinLowEdge(i+1) << ", Sig, Back Eff, Total back(6500-7000) = " << eSig[i] << " " 
         << eBack[i] << " " << nBack[i] << endl;
    if(nBack[i]>10) numToPlot = i;
  }
  addGraphics(h1s,20,1);
  addGraphics(h2s,22,2);
  addGraphics(h2b,22,2);

  // Get integrated Mass projections in BDT bins
  TH1F *hm[nbins];
  for(int i=0;i<nbins;i++){
    hm[i] = (TH1F*)h3->ProjectionX(Form("hm%d",i),i+1,nbins);
  }
  TH1F* ha = (TH1F*)h3->ProjectionX("ha",195,nbins);

  TH1F *h2d = (TH1F*)h2->Clone("h2c");
  h2d->SetTitle("#epsilon / sqrt{B}");

  TH1F *h2d = (TH1F*)h1s->Clone("h2d");
  h2d->SetTitle("#epsilon / sqrt{B}");
  h2d->Divide(h2c);
  
  TGraph *gr = new TGraph(numToPlot,eSig,eBack);
  gr->SetMinimum(0.000001);
  gr->SetMaximum(2.0);
  gr->SetTitle("#epsilon_{back} vs #epsilon_{sig}");
  gr->GetXaxis()->SetTitle("#epsilon_{sig}");
  gr->GetYaxis()->SetTitle("#epsilon_{back}");
  gr->SetLineWidth(2);
  gr->SetName("effSigBack");
  addGraphics(gr);
  gr->Write();
  


  TCanvas *c = new TCanvas("c","Sig eff vs Back Eff",1000,800);
  c->Divide(2,2);
  c->cd(1)->SetLogy();
  h1s->GetYaxis()->SetRangeUser(0.00001,2);
  h1s->Draw("hist");
  h2b->Draw("hist,same");
  c->cd(2)->SetLogy();
  h2s->Draw("hist");
  c->cd(3);
  h2d->Draw("hist");
  c->cd(4)->SetLogy();
  gr->Draw();
  
  c->Print("Plots/ROCCurves_"+tagCond+".png");

  fout->Write();
  

}

