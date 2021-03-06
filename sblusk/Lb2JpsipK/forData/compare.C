void addGraphics(TH1F *h, TString Xtitle, TString Ytitle, int iCol = 1, double titleSize=0.065){
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
  h->SetMarkerSize(0.75);
  h->SetMarkerStyle(20);
  h->GetXaxis()->SetTitleOffset(1.0);  
  h->GetYaxis()->SetTitleOffset(1.35);
  h->GetXaxis()->SetTitleSize(titleSize);  
  h->GetYaxis()->SetTitleSize(titleSize);
  h->GetXaxis()->SetLabelSize(titleSize-0.005);  
  h->GetYaxis()->SetLabelSize(titleSize-0.01);  
  h->SetNdivisions(404,"X");
  h->SetNdivisions(505,"Y");
  h->SetLineWidth(2);
  h->SetTitle("");
  
}

void doNorm(TH1F *hd, TH1F* hmc){

  double nb = hd->GetNbinsX();
  double nbmc = hmc->GetNbinsX();
  double yd = hd->Integral(1,nb);
  double ymc = hmc->Integral(1,nbmc);
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
  
  hd->GetXaxis()->SetTitleSize(0.06);
  hmc->GetXaxis()->SetTitleSize(0.06);

  TString xtit = hd->GetXaxis()->GetTitle();
  TString ytit = hd->GetYaxis()->GetTitle();
  addGraphics(hd,xtit,"",1);
  addGraphics(hmc,xtit,"",2);

  double data_mean = hd->GetMean();
  double mc_mean = hmc->GetMean();
  double diff = mc_mean - data_mean;
  double reldiff = diff/mc_mean;
  TString title  = hd->GetXaxis()->GetTitle();
  cout << title << ": " << data_mean << " " << mc_mean << " " << diff << " " << reldiff << endl;
  

  return;

}



void compare(){

  bool withBDT = true;  // pick up tuples with BDT
  bool phaseSpaceCuts = false;
  bool reWeight = false;
  
  TString suffix = "all";
  if(phaseSpaceCuts) suffix = "phaseSpaceCut";
  TString suffix2 = suffix;
  if(reWeight) suffix2 = suffix2 + "_reweight";

  TFile *fs = new TFile("/data1/sblusk/Xibc/JpsiX/Lb2JpsipK/data/sWeightedData_"+suffix+".root");
  
  TH1F *XcMass = (TH1F*)fs->Get("XcMass__Xc_M")->Clone("XcMass");
  TH1F *RFDHist = (TH1F*)fs->Get("RfdHist__Rfd")->Clone("XcMass");
  TH1F *DTFChisqHist = (TH1F*)fs->Get("DTFChisqHist__DTFChisq")->Clone("DTFChisqHist");
  TH1F *XbIPChisqHist = (TH1F*)fs->Get("XbIPChisqHist__XbIPChisq")->Clone("XbIPChisqHist");
  TH1F *XcIPChisqHist = (TH1F*)fs->Get("XcIPChisqHist__XcIPChisq")->Clone("XcIPChisqHist");
  TH1F *JpsiIPChisqHist = (TH1F*)fs->Get("JpsiIPChisqHist__JpsiIPChisq")->Clone("JpsiIPChisq");
  TH1F *kIPChisqHist = (TH1F*)fs->Get("kIPChisqHist__kIPChisq")->Clone("kIPChisqHist");
  TH1F *pIPChisqHist = (TH1F*)fs->Get("pIPChisqHist__pIPChisq")->Clone("pIPChisqHist");
  TH1F *mupIPChisqHist = (TH1F*)fs->Get("mupIPChisqHist__mupIPChisq")->Clone("mupIPChisqHist");
  TH1F *mumIPChisqHist = (TH1F*)fs->Get("mumIPChisqHist__mumIPChisq")->Clone("mumIPChisqHist");
  TH1F *XbPTHist = (TH1F*)fs->Get("XbPTHist__XbPT")->Clone("XbPTHist__XbPT");
  TH1F *XcPTHist = (TH1F*)fs->Get("XcPTHist__XcPT")->Clone("XcPTHist");
  TH1F *Xc2JpsiPTHist = (TH1F*)fs->Get("Xc2JpsiPTHist__Xc2JpsiPT")->Clone("Xc2JpsiPTHist");
  TH1F *XcVtxChisqHist = (TH1F*)fs->Get("XcVtxChisqHist__XcVtxChisq")->Clone("XcVtxChisqHist");
  TH1F *kPHist = (TH1F*)fs->Get("kPHist__kP")->Clone("kPHist");
  TH1F *pPHist = (TH1F*)fs->Get("pPHist__pP")->Clone("pPHist");
  TH1F *kProbNNkHist = (TH1F*)fs->Get("kProbNNkHist__kProbNNk")->Clone("kProbNNkHist");
  TH1F *pProbNNpHist = (TH1F*)fs->Get("pProbNNpHist__pProbNNp")->Clone("pProbNNpHist");
  TH1F *XcTAUHist = (TH1F*)fs->Get("XcTAUHist__XcTAU")->Clone("XcTAUHist");
  TH1F *nTracksHist = (TH1F*)fs->Get("nTracksHist__nTracks")->Clone("nTracksHist");

  TH1F *mJpsiPHist = (TH1F*)fs->Get("mJpsiPHist__mJpsiP")->Clone("mJpsiPHist");
  TH1F *mJpsiKHist = (TH1F*)fs->Get("mJpsiKHist__mJpsiK")->Clone("mJpsiKHist");

  TH1F *kPTHist = (TH1F*)fs->Get("kPTHist__kPT")->Clone("kPTHist");
  TH1F *pPTHist = (TH1F*)fs->Get("pPTHist__pPT")->Clone("pPTHist");
  TH1F *kEtaHist = (TH1F*)fs->Get("kEtaHist__kEta")->Clone("kEtaHist");
  TH1F *pEtaHist = (TH1F*)fs->Get("pEtaHist__pEta")->Clone("pEtaHist");
  if(withBDT) TH1F *BDTGHist = (TH1F*)fs->Get("BDTGHist__BDTG")->Clone("BDTGHist");


  if(withBDT){
    if(reWeight) TFile *fmc = new TFile("/data1/sblusk/Xibc/JpsiX/Lb2JpsipK/mc/Lb2JpsipK_mc.pk.X2JpsipK.Xc2pK.wMVA.def.addweight.root");
    if(!reWeight) TFile *fmc = new TFile("/data1/sblusk/Xibc/JpsiX/Lb2JpsipK/mc/Lb2JpsipK_mc.pk.X2JpsipK.Xc2pK.wMVA.def.root");
  }else{
    TFile *fmc = new TFile("/data1/sblusk/Xibc/JpsiX/mc/Lb2JpsipK/Lb2JpsipK_mc.pk.root");
  }
  
  

  treeMC = (TTree*)fmc->Get("mytree");
  
  int bf = 1;
  
  TH1F *XcMassMC = new TH1F("XcMassMC","",80/bf,1000,2600);
  TH1F *RFDHistMC = new TH1F("RFDHistMC","",40/bf,-4,4);
  TH1F *DTFChisqHistMC = new TH1F("DTFChisqHistMC","",50/bf,-2.5,2.5);
  TH1F *XbIPChisqHistMC = new TH1F("XbIPChisqHistMC","",50/bf,-6,4);
  TH1F *XcIPChisqHistMC = new TH1F("XcIPChisqHistMC","",80/bf,-4,12);
  TH1F *JpsiIPChisqHistMC = new TH1F("JpsiIPChisqHistMC","",80/bf,-6,10);
  TH1F *kIPChisqHistMC = new TH1F("kIPChisqHistMC","",50/bf,1.,11);
  TH1F *pIPChisqHistMC = new TH1F("pIPChisqHistMC","",50/bf,1.,11);
  TH1F *mupIPChisqHistMC = new TH1F("mupIPChisqHistMC","",70/bf,-2,12); 
  TH1F *mumIPChisqHistMC = new TH1F("mumIPChisqHistMC","",70/bf,-2,12); 
  TH1F *XbPTHistMC = new TH1F("XbPTHistMC","",60/bf,5,11); 
  TH1F *XcPTHistMC = new TH1F("XcPTHistMC","",60/bf,5,11); 
  TH1F *Xc2JpsiPTHistMC = new TH1F("Xc2JpsiPTHistMC","",70/bf,-3.5,3.5);
  TH1F *XcVtxChisqHistMC = new TH1F("XcVtxChisqHistMC","",90/bf,-6,3); 
  TH1F *kPHistMC = new TH1F("kPHistMC","",60/bf,7,13); 
  TH1F *pPHistMC = new TH1F("pPHistMC","",60/bf,7,13);
  TH1F *kProbNNkHistMC = new TH1F("kProbNNkHistMC","",50/bf,0,1);
  TH1F *pProbNNpHistMC = new TH1F("pProbNNpHistMC","",50/bf,0,1);
  TH1F *XcTAUHistMC = new TH1F("XcTAUHistMC","",100/bf,-1,1); 
  TH1F *nTracksHistMC = new TH1F("nTracksHistMC","",100/bf,0,500); 
  TH1F *kPTHistMC = new TH1F("kPTHistMC","",50/bf,5,10); 
  TH1F *pPTHistMC = new TH1F("pPTHistMC","",50/bf,5,10);
  TH1F *kEtaHistMC = new TH1F("kEtaHistMC","",40/bf,1.5,5.5); 
  TH1F *pEtaHistMC = new TH1F("pEtaHistMC","",40/bf,1.5,5.5);
  TH1F *mJpsiPHistMC = new TH1F("mJpsiPHistMC","",60/bf,4000,5200);
  TH1F *mJpsiKHistMC = new TH1F("mJpsiKHistMC","",70/bf,3400,4800);
  if(withBDT) TH1F *BDTGHistMC = new TH1F("BDTGHistMC","",100/bf,-1.0,1.0);



  TCut cuts = "Xb_DIRA_OWNPV>0.99995&&abs(Jpsi_M-3097)<30&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<8&&p_V3ProbNNp>0.1&&k_V3ProbNNk>0.1";
  TCut B0Cut = "(abs(sqrt( pow(Jpsi_PE+k_PE+sqrt(p_PX**2+p_PY**2+p_PZ**2+139.57**2),2)-(Jpsi_PX+p_PX+k_PX)**2-(Jpsi_PY+p_PY+k_PY)**2-(Jpsi_PZ+p_PZ+k_PZ)**2)-5280)-Jpsi_M+3097>20 || p_V3ProbNNp>0.6)";
  //cuts = cuts && B0Cut;
  cuts = cuts && "abs(Xb_M-Jpsi_M+3097-5620)<25 && (Xb_BKGCAT<=20 || Xb_BKGCAT==60)";
  //cuts = cuts && "(Jpsi_L0DiMuonDecision_TOS>0)";  
  if(phaseSpaceCuts){  
    cuts = cuts && "Xc_M>1950&&Xc_M<2250";
    //cuts = cuts && "sqrt(pow(Jpsi_PE+p_PE,2)-pow(Jpsi_PX+p_PX,2)-pow(Jpsi_PY+p_PY,2)-pow(Jpsi_PZ+p_PZ,2))<4400";
  }
  
  TCut wCutXc = "XcWeight";
  TCut wCutXk = "XkWeight";
  if(reWeight) cuts = cuts * wCutXc * wCutXk;
  

  TCanvas *cc = new TCanvas("cc","",800,800);
  
  treeMC->Draw("Xc_M>>XcMassMC",cuts);
  treeMC->Draw("log(sqrt(pow(Xb_ENDVERTEX_X-Xb_OWNPV_X,2)+pow(Xb_ENDVERTEX_Y-Xb_OWNPV_Y,2)))>>RFDHistMC",cuts);
  treeMC->Draw("log(Xb_PT)>>XbPTHistMC",cuts);
  treeMC->Draw("log(Xc_PT)>>XcPTHistMC",cuts);
  treeMC->Draw("Xc_M>>XcMassMC",cuts);
  treeMC->Draw("log(Xb_IPCHI2_OWNPV)>>XbIPChisqHistMC",cuts);
  treeMC->Draw("log(Xc_IPCHI2_OWNPV)>>XcIPChisqHistMC",cuts);
  treeMC->Draw("log(Jpsi_IPCHI2_OWNPV)>>JpsiIPChisqHistMC",cuts);
  treeMC->Draw("log(k_IPCHI2_OWNPV)>>kIPChisqHistMC",cuts);
  treeMC->Draw("log(p_IPCHI2_OWNPV)>>pIPChisqHistMC",cuts);
  treeMC->Draw("log(mup_IPCHI2_OWNPV)>>mupIPChisqHistMC",cuts);
  treeMC->Draw("log(mum_IPCHI2_OWNPV)>>mumIPChisqHistMC",cuts);
  treeMC->Draw("log(Xc_PT/Jpsi_PT)>>Xc2JpsiPTHistMC",cuts);
  treeMC->Draw("log(Xc_ENDVERTEX_CHI2)>>XcVtxChisqHistMC",cuts);
  treeMC->Draw("log(k_P)>>kPHistMC",cuts);
  treeMC->Draw("log(p_P)>>pPHistMC",cuts);
  treeMC->Draw("1000*Xc_TAU>>XcTAUHistMC",cuts);
  treeMC->Draw("1-sqrt(1-k_V3ProbNNk)>>kProbNNkHistMC",cuts);
  treeMC->Draw("1-sqrt(1-p_V3ProbNNp)>>pProbNNpHistMC",cuts);
  treeMC->Draw("nTracks>>nTracksHistMC",cuts);
  treeMC->Draw("log(k_PT)>>kPTHistMC",cuts);
  treeMC->Draw("log(p_PT)>>pPTHistMC",cuts);
  treeMC->Draw("-log(tan(0.5*k_PT/k_PZ))>>kEtaHistMC",cuts);
  treeMC->Draw("-log(tan(0.5*p_PT/p_PZ))>>pEtaHistMC",cuts);
  treeMC->Draw("sqrt(pow(Jpsi_PE+p_PE,2)-pow(Jpsi_PX+p_PX,2)-pow(Jpsi_PY+p_PY,2)-pow(Jpsi_PZ+p_PZ,2))>>mJpsiPHistMC",cuts);
  treeMC->Draw("sqrt(pow(Jpsi_PE+k_PE,2)-pow(Jpsi_PX+k_PX,2)-pow(Jpsi_PY+k_PY,2)-pow(Jpsi_PZ+k_PZ,2))>>mJpsiKHistMC",cuts);
  if(withBDT) treeMC->Draw("BDTG>>BDTGHistMC",cuts);

  doNorm(RFDHist,RFDHistMC);
  doNorm(XbPTHist,XbPTHistMC);
  doNorm(XcPTHist,XcPTHistMC);
  doNorm(XbIPChisqHist,XbIPChisqHistMC);
  doNorm(XcIPChisqHist,XcIPChisqHistMC);
  doNorm(JpsiIPChisqHist,JpsiIPChisqHistMC);
  doNorm(kIPChisqHist,kIPChisqHistMC);
  doNorm(pIPChisqHist,pIPChisqHistMC);
  doNorm(mupIPChisqHist,mupIPChisqHistMC);
  doNorm(mumIPChisqHist,mumIPChisqHistMC);
  doNorm(Xc2JpsiPTHist,Xc2JpsiPTHistMC);
  doNorm(XcVtxChisqHist,XcVtxChisqHistMC);
  doNorm(kPHist, kPHistMC);
  doNorm(pPHist,pPHistMC);
  doNorm(XcTAUHist,XcTAUHistMC);
  doNorm(kProbNNkHist,kProbNNkHistMC);
  doNorm(pProbNNpHist,pProbNNpHistMC);
  doNorm(nTracksHist,nTracksHistMC);
  doNorm(kPTHist, kPTHistMC);
  doNorm(pPTHist,pPTHistMC);
  doNorm(kEtaHist, kEtaHistMC);
  doNorm(pEtaHist,pEtaHistMC);
  doNorm(XcMass,XcMassMC);
  doNorm(mJpsiPHist,mJpsiPHistMC);
  doNorm(mJpsiKHist,mJpsiKHistMC);
  if(withBDT) doNorm(BDTGHist,BDTGHistMC);
  

  int ii = 1;
  TCanvas *c2 = new TCanvas("c2","",1000,700);  
  c2->Divide(2,2);
  c2->cd(ii++)->SetBottomMargin(0.15);
  kPHist->Draw();
  kPHistMC->Draw("same");
  c2->cd(ii++)->SetBottomMargin(0.15);
  pPHist->Draw();
  pPHistMC->Draw("same");

  c2->cd(ii++)->SetBottomMargin(0.15);
  kProbNNkHist->Draw();
  kProbNNkHistMC->Draw("same");
  c2->cd(ii++)->SetBottomMargin(0.15);
  pProbNNpHist->Draw();
  pProbNNpHistMC->Draw("same");

  //c2->Print("forAnton.png");
  

  //return;
  XcTAUHist->GetXaxis()->SetTitle("Decay time of pK^{-} vertex");
  

  int ii = 1;
  TCanvas *c1 = new TCanvas("c1","",1600,1000);  
  c1->Divide(7,4);
  c1->cd(ii++)->SetBottomMargin(0.15);
  RFDHist->Draw();
  RFDHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  XbPTHist->Draw();
  XbPTHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  XcPTHist->Draw();
  XcPTHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  Xc2JpsiPTHist->Draw();
  Xc2JpsiPTHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  XbIPChisqHist->Draw();
  XbIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  XcIPChisqHist->Draw();
  XcIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  JpsiIPChisqHist->Draw();
  JpsiIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  kIPChisqHist->Draw();
  kIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  pIPChisqHist->Draw();
  pIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  mupIPChisqHist->Draw();
  mupIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  mumIPChisqHist->Draw();
  mumIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  XcVtxChisqHist->Draw();
  XcVtxChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  kPHist->Draw();
  kPHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  pPHist->Draw();
  pPHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  XcTAUHist->Draw();
  XcTAUHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  kProbNNkHist->Draw();
  kProbNNkHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  pProbNNpHist->Draw();
  pProbNNpHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  nTracksHist->Draw();
  nTracksHistMC->Draw("same");
  
  c1->cd(ii++)->SetBottomMargin(0.15);
  pPTHist->Draw();
  pPTHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  kPTHist->Draw();
  kPTHistMC->Draw("same");

  c1->cd(ii++)->SetBottomMargin(0.15);
  pEtaHist->Draw();
  pEtaHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  kEtaHist->Draw();
  kEtaHistMC->Draw("same");

  c1->cd(ii++)->SetBottomMargin(0.15);
  XcMass->Draw();
  XcMassMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  mJpsiPHist->Draw();
  mJpsiPHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.15);
  mJpsiKHist->Draw();
  mJpsiKHistMC->Draw("same");

  c1->Print("InputDistributions_Comp_"+suffix2+".png");

  if(withBDT){
    addGraphics(BDTGHist,"BDTG Output","Number",1, 0.05);
    addGraphics(BDTGHistMC,"BDTG Output","Number",2,0.05);
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
      r = (n2-n1)/n2;
      herr->SetBinContent(i+1,r);    
    }
    
    addGraphics(hmc,"BDT > x","Efficiency",2,0.05);
    addGraphics(hd,"BDT > x","Efficiency",1,0.05);
    addGraphics(herr,"BDT > x","(MC-Data) Relative Difference",1,0.05);
    
    c3->cd(ii)->SetLeftMargin(0.13);
    c3->cd(ii++)->SetBottomMargin(0.12);
    hmc->Draw();
    hd->Draw("same");
    
    c3->cd(ii)->SetLeftMargin(0.13);
    c3->cd(ii++)->SetBottomMargin(0.12);
    herr->GetYaxis()->SetRangeUser(-0.4,0.4);
    herr->Draw();
    TLine *l = new TLine(-1,0,1,0);
    l->SetLineStyle(kDashed);
    l->Draw();
    

    cout << "MC:   Eff @ BDTG>0: " << hmc->GetBinContent(50) << endl;
    cout << "Data: Eff @ BDTG>0: " << hd->GetBinContent(50) << endl;

    c3->Print("BDTEff_Comp_"+suffix2+".png");
    
  }
  
  if(!reWeight){
    TFile *fout = new TFile("histRatio.root","RECREATE");

    TCanvas *c4 = new TCanvas("c4","",1000,700);  
    c4->Divide(2,1);
    c4->cd(1);
    TH1F *hrat = (TH1F*)XcMass->Clone("hrat");
    hrat->Divide(XcMassMC);
    hrat->SetMaximum(5);  
    hrat->Draw();
    TF1 *fr = new TF1("fr","[0]+[1]*exp([2]*(x-1300))",1450,2400);
    fr->SetParameters(0.3,7,-0.004);
    hrat->Fit("fr","R");
    
    c4->cd(2);
    TH1F *hrat2 = (TH1F*)mJpsiKHist->Clone("hrat2");
    hrat2->Divide(mJpsiKHistMC);
    hrat2->SetMaximum(5);  
    hrat2->Draw();
    
    TF1 *fr2 = new TF1("fr2","[0]*exp([1]*(x-3500))",3600,4800);
    fr2->SetParameters(-8,0.002);
    hrat2->Fit("fr2","R");
    
    hrat->Write();
    hrat2->Write();
    
    fout->Close();
    
  }
  

}
