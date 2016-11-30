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
  
  hd->GetXaxis()->SetTitleSize(0.06);
  hmc->GetXaxis()->SetTitleSize(0.06);
  

  return;

}



void compare(){

  TFile *fs = new TFile("/data1/sblusk/Xibc/Lb2JpsipK/data/sWeightedData.root");
  
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

  TH1F *kPTHist = (TH1F*)fs->Get("kPTHist__kPT")->Clone("kPTHist");
  TH1F *pPTHist = (TH1F*)fs->Get("pPTHist__pPT")->Clone("pPTHist");
  TH1F *kEtaHist = (TH1F*)fs->Get("kEtaHist__kEta")->Clone("kEtaHist");
  TH1F *pEtaHist = (TH1F*)fs->Get("pEtaHist__pEta")->Clone("pEtaHist");

  TFile *fmc = new TFile("/data1/sblusk/Xibc/Lb2JpsipK/mc/Lb2JpsipK.pk.root");
  treeMC = (TTree*)fmc->Get("mytree");
  
  TH1F *XcMassMC = new TH1F("XcMassMC","",80,1000,2600);
  TH1F *RFDHistMC = new TH1F("RFDHistMC","",45,-4,4);
  TH1F *DTFChisqHistMC = new TH1F("DTFChisqHistMC","",50,-2.5,2.5);
  TH1F *XbIPChisqHistMC = new TH1F("XbIPChisqHistMC","",50,-6,4);
  TH1F *XcIPChisqHistMC = new TH1F("XcIPChisqHistMC","",80,-4,12);
  TH1F *JpsiIPChisqHistMC = new TH1F("JpsiIPChisqHistMC","",80,-6,10);
  TH1F *kIPChisqHistMC = new TH1F("kIPChisqHistMC","",45,1.5,10.5);
  TH1F *pIPChisqHistMC = new TH1F("pIPChisqHistMC","",45,1.5,10.5);
  TH1F *mupIPChisqHistMC = new TH1F("mupIPChisqHistMC","",70,-2,12); 
  TH1F *mumIPChisqHistMC = new TH1F("mumIPChisqHistMC","",70,-2,12); 
  TH1F *XbPTHistMC = new TH1F("XbPTHistMC","",60,5,11); 
  TH1F *XcPTHistMC = new TH1F("XcPTHistMC","",60,5,11); 
  TH1F *Xc2JpsiPTHistMC = new TH1F("Xc2JpsiPTHistMC","",70,-3.5,3.5);
  TH1F *XcVtxChisqHistMC = new TH1F("XcVtxChisqHistMC","",90,-6,3); 
  TH1F *kPHistMC = new TH1F("kPHistMC","",60,7,13); 
  TH1F *pPHistMC = new TH1F("pPHistMC","",60,7,13);
  TH1F *kProbNNkHistMC = new TH1F("kProbNNkHistMC","",50,0,1);
  TH1F *pProbNNpHistMC = new TH1F("pProbNNpHistMC","",50,0,1);
  TH1F *XcTAUHistMC = new TH1F("XcTAUHistMC","",100,-1,1); 
  TH1F *nTracksHistMC = new TH1F("nTracksHistMC","",100,0,500); 
  TH1F *kPTHistMC = new TH1F("kPTHistMC","",50,5,10); 
  TH1F *pPTHistMC = new TH1F("pPTHistMC","",50,5,10);
  TH1F *kEtaHistMC = new TH1F("kEtaHistMC","",40,1.5,5.5); 
  TH1F *pEtaHistMC = new TH1F("pEtaHistMC","",40,1.5,5.5);



  TCut cuts = "Xb_DIRA_OWNPV>0.99995&&abs(Jpsi_M-3097)<30&&k_V3ProbNNk>0.2&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<8&&p_V3ProbNNp>0.2&&p_ProbNNp>0.2&&k_ProbNNk>0.2";
  TCut B0Cut = "(abs(sqrt( pow(Jpsi_PE+k_PE+sqrt(p_PX**2+p_PY**2+p_PZ**2+139.57**2),2)-(Jpsi_PX+p_PX+k_PX)**2-(Jpsi_PY+p_PY+k_PY)**2-(Jpsi_PZ+p_PZ+k_PZ)**2)-5280)-Jpsi_M+3097>20 || p_V3ProbNNp>0.6)";
  cuts = cuts && B0Cut;
  cuts = cuts && "abs(Xb_M-Jpsi_M+3097-5620)<25 && (Xb_BKGCAT<=20 || Xb_BKGCAT==60)";
  cuts = cuts && "(Jpsi_L0DiMuonDecision_TOS>0)";  
  cuts = cuts && "Xc_M>1550&&Xc_M<1850";

  TCanvas *cc = new TCanvas("cc","",800,800);
  
  treeMC->Draw("Xc_M>>XcMassMC",cuts);
  treeMC->Draw("log(sqrt(pow(Xb_ENDVERTEX_X-Xb_OWNPV_X,2)+pow(Xb_ENDVERTEX_Y-Xb_OWNPV_Y,2)))>>RFDHistMC",cuts);
  treeMC->Draw("log(Xb_PT)>>XbPTHistMC",cuts);
  treeMC->Draw("log(Xc_PT)>>XcPTHistMC",cuts);
  treeMC->Draw("Xc_M>>XcMassMC",cuts);
  treeMC->Draw("log(Xb_IPCHI2_OWNPV)>>XbIPChisqHistMC",cuts);
  treeMC->Draw("log(Xc_IPCHI2_OWNPV)+0.5>>XcIPChisqHistMC",cuts);
  treeMC->Draw("log(Jpsi_IPCHI2_OWNPV)+0.5>>JpsiIPChisqHistMC",cuts);
  treeMC->Draw("log(k_IPCHI2_OWNPV)+0.0>>kIPChisqHistMC",cuts);
  treeMC->Draw("log(p_IPCHI2_OWNPV)+0.0>>pIPChisqHistMC",cuts);
  treeMC->Draw("log(mup_IPCHI2_OWNPV)>>mupIPChisqHistMC",cuts);
  treeMC->Draw("log(mum_IPCHI2_OWNPV)>>mumIPChisqHistMC",cuts);
  treeMC->Draw("log(Xc_PT/Jpsi_PT)>>Xc2JpsiPTHistMC",cuts);
  treeMC->Draw("log(Xc_ENDVERTEX_CHI2)>>XcVtxChisqHistMC",cuts);
  treeMC->Draw("log(k_P)>>kPHistMC",cuts);
  treeMC->Draw("log(p_P)-0.1>>pPHistMC",cuts);
  treeMC->Draw("1000*Xc_TAU>>XcTAUHistMC",cuts);
  treeMC->Draw("1-sqrt(1-k_V3ProbNNk)>>kProbNNkHistMC",cuts);
  treeMC->Draw("1-sqrt(1-p_V3ProbNNp)>>pProbNNpHistMC",cuts);
  treeMC->Draw("nTracks>>nTracksHistMC",cuts);
  treeMC->Draw("log(k_PT)>>kPTHistMC",cuts);
  treeMC->Draw("log(p_PT)-0.1>>pPTHistMC",cuts);
  treeMC->Draw("-log(tan(0.5*k_PT/k_PZ))>>kEtaHistMC",cuts);
  treeMC->Draw("-log(tan(0.5*p_PT/p_PZ))>>pEtaHistMC",cuts);


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
  

  int ii = 1;
  TCanvas *c1 = new TCanvas("c1","",1400,700);  
  c1->Divide(6,4);
  c1->cd(ii++)->SetBottomMargin(0.13);
  RFDHist->Draw();
  RFDHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  XbPTHist->Draw();
  XbPTHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  XcPTHist->Draw();
  XcPTHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  Xc2JpsiPTHist->Draw();
  Xc2JpsiPTHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  XbIPChisqHist->Draw();
  XbIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  XcIPChisqHist->Draw();
  XcIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  JpsiIPChisqHist->Draw();
  JpsiIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  kIPChisqHist->Draw();
  kIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  pIPChisqHist->Draw();
  pIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  mupIPChisqHist->Draw();
  mupIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  mumIPChisqHist->Draw();
  mumIPChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  XcVtxChisqHist->Draw();
  XcVtxChisqHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  kPHist->Draw();
  kPHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  pPHist->Draw();
  pPHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  XcTAUHist->Draw();
  XcTAUHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  kProbNNkHist->Draw();
  kProbNNkHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  pProbNNpHist->Draw();
  pProbNNpHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  nTracksHist->Draw();
  nTracksHistMC->Draw("same");
  
  c1->cd(ii++)->SetBottomMargin(0.13);
  pPTHist->Draw();
  pPTHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  kPTHist->Draw();
  kPTHistMC->Draw("same");

  c1->cd(ii++)->SetBottomMargin(0.13);
  pEtaHist->Draw();
  pEtaHistMC->Draw("same");
  c1->cd(ii++)->SetBottomMargin(0.13);
  kEtaHist->Draw();
  kEtaHistMC->Draw("same");

  c1->cd(ii++)->SetBottomMargin(0.13);
  XcMass->Draw();
  XcMassMC->Draw("same");

    





}
