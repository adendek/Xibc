void addGraphics(TH1F *h, TString Xtitle, TString Ytitle, int iCol = 1){
  h->SetXTitle(Xtitle);
  //h->SetFillColor(30);
  int bw = h->GetBinWidth(1);
  h->SetXTitle(Xtitle);
  h->SetYTitle(Ytitle);
  h->SetStats(kFALSE);
  h->SetMinimum(0.0);
  h->SetMaximum(1.1*h->GetMaximum());
  h->SetTitleSize(0.1);
  h->SetLineColor(iCol);
  h->SetMarkerSize(1.0);
  h->SetMarkerStyle(20);
  h->GetXaxis()->SetTitleOffset(1.0);  
  h->GetYaxis()->SetTitleOffset(1.15);
  h->GetXaxis()->SetTitleSize(0.045);  
  h->GetYaxis()->SetTitleSize(0.045);
  h->GetXaxis()->SetLabelSize(0.035);  
  h->GetYaxis()->SetLabelSize(0.035);  
  h->SetNdivisions(404,"X");
  h->SetNdivisions(505,"Y");
  h->SetLineWidth(2);
  h->SetTitle("");
  
}

void doNorm(TH1F *hd, TH1F* hmc){

  double nb = hd->GetNbinsX();
  double yd = hd->Integral(1,nb);
  double ymc = hmc->Integral(1,nb);
  hmc->Scale(yd/ymc);
  hmc->SetLineColor(2);
  hmc->SetLineWidth(2);
  hd->SetMarkerSize(0.7);

  double maxd = hd->GetMaximum();
  double maxmc = hmc->GetMaximum();
  double maxx = maxd;
  if(maxmc>maxx) maxx = maxmc;
  hd->SetMaximum(1.1*maxx);
  hd->SetStats(kFALSE);
  hmc->SetStats(kFALSE);
  


  return;

}



void compare(){
  bool withBDT = true;  // pick up tuples with BDT

  TFile *fs = new TFile("/data1/sblusk/Xibc/JpsiX/JpsiKpipi/data/sWeightedData.root");
  
  TH1F *XcMass = (TH1F*)fs->Get("XcMass__Xc_M")->Clone("XcMass");
  TH1F *RFDHist = (TH1F*)fs->Get("RfdHist__Rfd")->Clone("XcMass");
  TH1F *DTFChisqHist = (TH1F*)fs->Get("DTFChisqHist__DTFChisq")->Clone("DTFChisqHist");
  TH1F *XbIPChisqHist = (TH1F*)fs->Get("XbIPChisqHist__XbIPChisq")->Clone("XbIPChisqHist");
  TH1F *XcIPChisqHist = (TH1F*)fs->Get("XcIPChisqHist__XcIPChisq")->Clone("XcIPChisqHist");
  TH1F *JpsiIPChisqHist = (TH1F*)fs->Get("JpsiIPChisqHist__JpsiIPChisq")->Clone("JpsiIPChisq");
  TH1F *kIPChisqHist = (TH1F*)fs->Get("kIPChisqHist__kIPChisq")->Clone("kIPChisqHist");
  TH1F *pi1IPChisqHist = (TH1F*)fs->Get("pi1IPChisqHist__pi1IPChisq")->Clone("pi1IPChisqHist");
  TH1F *pi2IPChisqHist = (TH1F*)fs->Get("pi2IPChisqHist__pi2IPChisq")->Clone("pi2IPChisqHist");
  TH1F *mupIPChisqHist = (TH1F*)fs->Get("mupIPChisqHist__mupIPChisq")->Clone("mupIPChisqHist");
  TH1F *mumIPChisqHist = (TH1F*)fs->Get("mumIPChisqHist__mumIPChisq")->Clone("mumIPChisqHist");
  TH1F *XbPTHist = (TH1F*)fs->Get("XbPTHist__XbPT")->Clone("XbPTHist__XbPT");
  TH1F *XcPTHist = (TH1F*)fs->Get("XcPTHist__XcPT")->Clone("XcPTHist");
  TH1F *Xc2JpsiPTHist = (TH1F*)fs->Get("Xc2JpsiPTHist__Xc2JpsiPT")->Clone("Xc2JpsiPTHist");
  TH1F *XcVtxChisqHist = (TH1F*)fs->Get("XcVtxChisqHist__XcVtxChisq")->Clone("XcVtxChisqHist");
  TH1F *kPHist = (TH1F*)fs->Get("kPHist__kP")->Clone("kPHist");
  TH1F *pi1PHist = (TH1F*)fs->Get("pi1PHist__pi1P")->Clone("pi1PHist");
  TH1F *pi2PHist = (TH1F*)fs->Get("pi2PHist__pi2P")->Clone("pi2PHist");
  TH1F *kProbNNkHist = (TH1F*)fs->Get("kProbNNkHist__kProbNNk")->Clone("kProbNNkHist");
  TH1F *pi1ProbNNpiHist = (TH1F*)fs->Get("pi1ProbNNpiHist__pi1ProbNNpi")->Clone("pi1ProbNNpiHist");
  TH1F *pi2ProbNNpiHist = (TH1F*)fs->Get("pi2ProbNNpiHist__pi2ProbNNpi")->Clone("pi2ProbNNpiHist");
  TH1F *XcTAUHist = (TH1F*)fs->Get("XcTAUHist__XcTAU")->Clone("XcTAUHist");
  if(withBDT) TH1F *BDTGHist = (TH1F*)fs->Get("BDTGHist__BDTG")->Clone("BDTGHist");

  if(!withBDT) TFile *fmc = new TFile("/data1/sblusk/Xibc/JpsiKpipi/mc/JpsiKpipi.kpipi.root");
  if(withBDT) TFile *fmc = new TFile("/data1/sblusk/Xibc/JpsiX/JpsiKpipi/mc/JpsiKpipi.kpipi.X2JpsiKpipi.X2Kpipi.wMVA.test3.root");
  treeMC = (TTree*)fmc->Get("mytree");
  
  TH1F *XcMassMC = new TH1F("XcMassMC","",48,1000,2200);
  TH1F *RFDHistMC = new TH1F("RFDHistMC","",45,-4,4);
  TH1F *DTFChisqHistMC = new TH1F("DTFChisqHistMC","",50,-2.5,2.5);
  TH1F *XbIPChisqHistMC = new TH1F("XbIPChisqHistMC","",50,-6,4);
  TH1F *XcIPChisqHistMC = new TH1F("XcIPChisqHistMC","",80,-4,12);
  TH1F *JpsiIPChisqHistMC = new TH1F("JpsiIPChisqHistMC","",80,-6,10);
  TH1F *kIPChisqHistMC = new TH1F("kIPChisqHistMC","",45,1.5,10.5);
  TH1F *pi1IPChisqHistMC = new TH1F("pi1IPChisqHistMC","",45,1.5,10.5);
  TH1F *pi2IPChisqHistMC = new TH1F("pi2IPChisqHistMC","",45,1.5,10.5);
  TH1F *mupIPChisqHistMC = new TH1F("mupIPChisqHistMC","",70,-2,12); 
  TH1F *mumIPChisqHistMC = new TH1F("mumIPChisqHistMC","",70,-2,12); 
  TH1F *XbPTHistMC = new TH1F("XbPTHistMC","",60,5,11); 
  TH1F *XcPTHistMC = new TH1F("XcPTHistMC","",60,5,11); 
  TH1F *Xc2JpsiPTHistMC = new TH1F("Xc2JpsiPTHistMC","",70,-3.5,3.5);
  TH1F *XcVtxChisqHistMC = new TH1F("XcVtxChisqHistMC","",80,-4,4); 
  TH1F *kPHistMC = new TH1F("kPHistMC","",60,7,13); 
  TH1F *pi1PHistMC = new TH1F("pi1PHistMC","",60,7,13);
  TH1F *pi2PHistMC = new TH1F("pi2PHistMC","",60,7,13);
  TH1F *kProbNNkHistMC = new TH1F("kProbNNkHistMC","",50,0,1);
  TH1F *pi1ProbNNpiHistMC = new TH1F("pi1ProbNNpiHistMC","",50,0,1);
  TH1F *pi2ProbNNpiHistMC = new TH1F("pi2ProbNNpiHistMC","",50,0,1);
  TH1F *XcTAUHistMC = new TH1F("XcTAUHistMC","",100,-1,1); 
  if(withBDT) TH1F *BDTGHistMC = new TH1F("BDTGHistMC","",100,-1.0,1.0);

  TCut cuts = "Xb_DIRA_OWNPV>0.99995&&abs(Jpsi_M-3097)<30&&k_V3ProbNNk>0.1&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<8&&pi1_V3ProbNNpi>0.01&&pi2_V3ProbNNpi>0.01&&abs(Xb_TRUEID)==521";
  cuts = cuts && "Xb_M>5150&&Xb_M<5350";
  cuts = cuts && "Xc_M>1500&&Xc_M<1800";  

  TCanvas *cc = new TCanvas("cc","",800,800);
  
  treeMC->Draw("Xc_M>>XcMassMC",cuts);
  treeMC->Draw("log(sqrt(pow(Xb_ENDVERTEX_X-Xb_OWNPV_X,2)+pow(Xb_ENDVERTEX_Y-Xb_OWNPV_Y,2)))>>RFDHistMC",cuts);
  treeMC->Draw("log(Xb_PT)>>XbPTHistMC",cuts);
  treeMC->Draw("log(Xc_PT)>>XcPTHistMC",cuts);
  treeMC->Draw("log(Xb_IPCHI2_OWNPV)>>XbIPChisqHistMC",cuts);
  treeMC->Draw("log(Xc_IPCHI2_OWNPV)+0.0>>XcIPChisqHistMC",cuts);
  treeMC->Draw("log(Jpsi_IPCHI2_OWNPV)+0.0>>JpsiIPChisqHistMC",cuts);
  treeMC->Draw("log(k_IPCHI2_OWNPV)+0.0>>kIPChisqHistMC",cuts);
  treeMC->Draw("log(pi1_IPCHI2_OWNPV)+0.0>>pi1IPChisqHistMC",cuts);
  treeMC->Draw("log(pi2_IPCHI2_OWNPV)+0.0>>pi2IPChisqHistMC",cuts);
  treeMC->Draw("log(mup_IPCHI2_OWNPV)>>mupIPChisqHistMC",cuts);
  treeMC->Draw("log(mum_IPCHI2_OWNPV)>>mumIPChisqHistMC",cuts);
  treeMC->Draw("log(Xc_PT/Jpsi_PT)>>Xc2JpsiPTHistMC",cuts);
  treeMC->Draw("log(Xc_ENDVERTEX_CHI2)>>XcVtxChisqHistMC",cuts);
  treeMC->Draw("log(k_P)>>kPHistMC",cuts);
  treeMC->Draw("log(pi1_P)>>pi1PHistMC",cuts);
  treeMC->Draw("log(pi2_P)>>pi2PHistMC",cuts);
  treeMC->Draw("1000*Xc_TAU>>XcTAUHistMC",cuts);
  treeMC->Draw("1-sqrt(1-k_V3ProbNNk)>>kProbNNkHistMC",cuts);
  treeMC->Draw("1-sqrt(1-pi1_V3ProbNNpi)>>pi1ProbNNpiHistMC",cuts);
  treeMC->Draw("1-sqrt(1-pi2_V3ProbNNpi)>>pi2ProbNNpiHistMC",cuts);
  if(withBDT) treeMC->Draw("BDTG>>BDTGHistMC",cuts);

  doNorm(XcMass,XcMassMC);
  doNorm(RFDHist,RFDHistMC);
  doNorm(XbPTHist,XbPTHistMC);
  doNorm(XcPTHist,XcPTHistMC);
  doNorm(XbIPChisqHist,XbIPChisqHistMC);
  doNorm(XcIPChisqHist,XcIPChisqHistMC);
  doNorm(JpsiIPChisqHist,JpsiIPChisqHistMC);
  doNorm(kIPChisqHist,kIPChisqHistMC);
  doNorm(pi1IPChisqHist,pi1IPChisqHistMC);
  doNorm(pi2IPChisqHist,pi2IPChisqHistMC);
  doNorm(mupIPChisqHist,mupIPChisqHistMC);
  doNorm(mumIPChisqHist,mumIPChisqHistMC);
  doNorm(Xc2JpsiPTHist,Xc2JpsiPTHistMC);
  doNorm(XcVtxChisqHist,XcVtxChisqHistMC);
  doNorm(kPHist, kPHistMC);
  doNorm(pi1PHist,pi1PHistMC);
  doNorm(pi2PHist,pi2PHistMC);
  doNorm(XcTAUHist,XcTAUHistMC);
  doNorm(kProbNNkHist,kProbNNkHistMC);
  doNorm(pi1ProbNNpiHist,pi1ProbNNpiHistMC);
  doNorm(pi2ProbNNpiHist,pi2ProbNNpiHistMC);
  if(withBDT) doNorm(BDTGHist,BDTGHistMC);

  int ii = 1;
  TCanvas *c1 = new TCanvas("c1","",1500,1000);  
  c1->Divide(6,4);
  c1->cd(ii++);
  RFDHist->Draw();
  RFDHistMC->Draw("same");
  c1->cd(ii++);
  XbPTHist->Draw();
  XbPTHistMC->Draw("same");
  c1->cd(ii++);
  XcPTHist->Draw();
  XcPTHistMC->Draw("same");
  c1->cd(ii++);
  Xc2JpsiPTHist->Draw();
  Xc2JpsiPTHistMC->Draw("same");
  c1->cd(ii++);
  XbIPChisqHist->Draw();
  XbIPChisqHistMC->Draw("same");
  c1->cd(ii++);
  XcIPChisqHist->Draw();
  XcIPChisqHistMC->Draw("same");
  c1->cd(ii++);
  JpsiIPChisqHist->Draw();
  JpsiIPChisqHistMC->Draw("same");
  c1->cd(ii++);
  kIPChisqHist->Draw();
  kIPChisqHistMC->Draw("same");
  c1->cd(ii++);
  pi1IPChisqHist->Draw();
  pi1IPChisqHistMC->Draw("same");
  c1->cd(ii++);
  pi2IPChisqHist->Draw();
  pi2IPChisqHistMC->Draw("same");
  c1->cd(ii++);
  mupIPChisqHist->Draw();
  mupIPChisqHistMC->Draw("same");
  c1->cd(ii++);
  mumIPChisqHist->Draw();
  mumIPChisqHistMC->Draw("same");
  c1->cd(ii++);
  XcVtxChisqHist->Draw();
  XcVtxChisqHistMC->Draw("same");
  c1->cd(ii++);
  kPHist->Draw();
  kPHistMC->Draw("same");
  c1->cd(ii++);
  pi1PHist->Draw();
  pi1PHistMC->Draw("same");
  c1->cd(ii++);
  pi2PHist->Draw();
  pi2PHistMC->Draw("same");
  c1->cd(ii++);
  XcTAUHist->Draw();
  XcTAUHistMC->Draw("same");
  c1->cd(ii++);
  kProbNNkHist->Draw();
  kProbNNkHistMC->Draw("same");
  c1->cd(ii++);
  pi1ProbNNpiHist->Draw();
  pi1ProbNNpiHistMC->Draw("same");
  c1->cd(ii++);
  pi2ProbNNpiHist->Draw();
  pi2ProbNNpiHistMC->Draw("same");
  c1->cd(ii++);
  XcMass->Draw();
  XcMassMC->Draw("same");
  
  c1->Print("InputDistributions_Comp.png");
    

  if(withBDT){
    
    BDTGHist->GetYaxis()->SetTitleOffset(1.4);
    BDTGHist->GetXaxis()->SetTitleSize(0.045);
    ii = 1;
    TCanvas *c3 = new TCanvas("c3","",1500,500);  
    c3->Divide(3,1);
    c3->cd(ii)->SetLeftMargin(0.13);
    c3->cd(ii++)->SetBottomMargin(0.1);
    BDTGHist->Draw();
    BDTGHistMC->Draw("same");

    TLegend* legend3 = new TLegend(0.18,0.68,0.43,0.88);
    legend3->SetFillStyle(0);
    legend3->SetBorderSize(0);
    legend3->SetFillStyle(0);
    legend3->SetTextSize(0.045);   
    legend3->AddEntry(BDTGHist,"Data","LEP"); 
    legend3->AddEntry(BDTGHistMC,"Simulation","L"); 
    legend3->Draw();
    
    
    
    TH1F *hd = new TH1F("hd","BDTG Eff",100,-1.0,1.0);
    TH1F *hmc = new TH1F("hmc","BDTG Eff",100,-1.0,1.0);
    TH1F *herr = new TH1F("herr","BDTG Eff",100,-1.0,1.0);
    
    double n1,f, n2, r;
    for(int i=0;i<100;i++){
      n1 = BDTGHist->Integral(i+1,100);
      f = n1/BDTGHist->Integral(1,100);
      hd->SetBinContent(i+1,f);
      n2 = BDTGHistMC->Integral(i+1,100);
      f = n2/BDTGHistMC->Integral(1,100);
      hmc->SetBinContent(i+1,f);    
      r = fabs(n2-n1)/n2;
      herr->SetBinContent(i+1,r);    
    }
    
    addGraphics(hmc,"BDT > x","Efficiency",2);
    addGraphics(hd,"BDT > x","Efficiency",1);
    addGraphics(herr,"BDT > x","Percent deviation",1);
    
    c3->cd(ii)->SetLeftMargin(0.13);
    c3->cd(ii++)->SetBottomMargin(0.12);
    hmc->Draw();
    hd->Draw("same");
    
    c3->cd(ii)->SetLeftMargin(0.13);
    c3->cd(ii++)->SetBottomMargin(0.12);
    herr->Draw();
    
    cout << "MC:   Eff @ BDTG>0: " << hmc->GetBinContent(50) << endl;
    cout << "Data: Eff @ BDTG>0: " << hd->GetBinContent(50) << endl;

    c3->Print("BDTEff_Comp.png");
  }
  




}
