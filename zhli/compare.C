
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

  TFile *fs = new TFile("test.root");
  
  TH1F *DMass = (TH1F*)fs->Get("DMass__D_M")->Clone("DMass");
  TH1F *RfdHist = (TH1F*)fs->Get("RfdHist__Rfd")->Clone("RfdHist");
  //  TH1F *DTFChisqHist = (TH1F*)fs->Get("DTFChisqHist__DTFChisq")->Clone("DTFChisqHist");
  TH1F *XbIPChisqHist = (TH1F*)fs->Get("XbIPChisqHist__XbIPChisq")->Clone("XbIPChisqHist");
  TH1F *DIPChisqHist = (TH1F*)fs->Get("DIPChisqHist__DIPChisq")->Clone("DIPChisqHist");
//  TH1F *JpsiIPChisqHist = (TH1F*)fs->Get("JpsiIPChisqHist__JpsiIPChisq")->Clone("JpsiIPChisq");
  TH1F *KIPChisqHist = (TH1F*)fs->Get("KIPChisqHist__KIPChisq")->Clone("KIPChisqHist");
  TH1F *piIPChisqHist = (TH1F*)fs->Get("piIPChisqHist__piIPChisq")->Clone("piIPChisqHist");
  TH1F *RpiIPChisqHist = (TH1F*)fs->Get("RpiIPChisqHist__RpiIPChisq")->Clone("RpiIPChisqHist");
//  TH1F *mupIPChisqHist = (TH1F*)fs->Get("mupIPChisqHist__mupIPChisq")->Clone("mupIPChisqHist");
//  TH1F *mumIPChisqHist = (TH1F*)fs->Get("mumIPChisqHist__mumIPChisq")->Clone("mumIPChisqHist");
  TH1F *XbPTHist = (TH1F*)fs->Get("XbPTHist__XbPT")->Clone("XbPTHist__XbPT");
  TH1F *RPTHist = (TH1F*)fs->Get("RPTHist__RPT")->Clone("RPTHist");
//  TH1F *R2JpsiPTHist = (TH1F*)fs->Get("R2JpsiPTHist__R2JpsiPT")->Clone("R2JpsiPTHist");
  TH1F *DVtxChisqHist = (TH1F*)fs->Get("DVtxChisqHist__DVtxChisq")->Clone("DVtxChisqHist");
  TH1F *KPHist = (TH1F*)fs->Get("KPHist__KP")->Clone("KPHist");
  TH1F *RpPHist = (TH1F*)fs->Get("RpPHist__RpP")->Clone("RpPHist");
  TH1F *piPHist = (TH1F*)fs->Get("piPHist__piP")->Clone("piPHist");
  TH1F *RpiPHist = (TH1F*)fs->Get("RpiPHist__RpiP")->Clone("RpiPHist");
  TH1F *KProbNNkHist = (TH1F*)fs->Get("KProbNNkHist__KProbNNk")->Clone("KProbNNkHist");
  TH1F *piProbNNpiHist = (TH1F*)fs->Get("piProbNNpiHist__piProbNNpi")->Clone("piProbNNpiHist");
  TH1F *RpiProbNNpiHist = (TH1F*)fs->Get("RpiProbNNpiHist__RpiProbNNpi")->Clone("RpiProbNNpiHist");
  TH1F *RpProbNNpHist = (TH1F*)fs->Get("RpProbNNpHist__RpProbNNp")->Clone("RpProbNNpHist");
  TH1F *DTAUHist = (TH1F*)fs->Get("DTAUHist__DTAU")->Clone("DTAUHist");

  TFile *fmc = new TFile("/data1/zli59/D0ppi/MC.tuned.piKppi.root");
  treeMC = (TTree*)fmc->Get("mytree");
  
  TH1F *DMassMC = new TH1F("DMassMC","",48,1834,1894);
  TH1F *RfdHistMC = new TH1F("RfdHistMC","",45,-4,4);
  //  TH1F *DTFChisqHistMC = new TH1F("DTFChisqHistMC","",50,-2.5,2.5);
  TH1F *XbIPChisqHistMC = new TH1F("XbIPChisqHistMC","",50,-6,4);
  TH1F *DIPChisqHistMC = new TH1F("DIPChisqHistMC","",80,-4,12);
  //  TH1F *JpsiIPChisqMC = new TH1F("JpsiIPChisqMC","",80,-6,10);
  TH1F *KIPChisqHistMC = new TH1F("KIPChisqHistMC","",45,0,12);
  TH1F *piIPChisqHistMC = new TH1F("piIPChisqHistMC","",45,0,12);
  TH1F *RpiIPChisqHistMC = new TH1F("RpiIPChisqHistMC","",45,0,12);
//  TH1F *mupIPChisqHistMC = new TH1F("mupIPChisqHistMC","",70,-2,12); 
//  TH1F *mumIPChisqHistMC = new TH1F("mumIPChisqHistMC","",70,-2,12); 
  TH1F *XbPTHistMC = new TH1F("XbPTHistMC","",60,7,11); 
  TH1F *RPTHistMC = new TH1F("RPTHistMC","",60,5,11); 
//  TH1F *R2JpsiPTHistMC = new TH1F("R2JpsiPTHistMC","",70,-3.5,3.5);
  TH1F *DVtxChisqHistMC = new TH1F("DVtxChisqHistMC","",80,-7,4); 
  TH1F *KPHistMC = new TH1F("KPHistMC","",60,7,13); 
  TH1F *RpPHistMC = new TH1F("RpPHistMC","",60,7,13); 
  TH1F *piPHistMC = new TH1F("piPHistMC","",60,7,13);
  TH1F *RpiPHistMC = new TH1F("RpiPHistMC","",60,7,13);
  TH1F *KProbNNkHistMC = new TH1F("KProbNNkHistMC","",50,0,1);
  TH1F *piProbNNpiHistMC = new TH1F("piProbNNpiHistMC","",50,0,1);
  TH1F *RpiProbNNpiHistMC = new TH1F("RpiProbNNpiHistMC","",50,0,1);
  TH1F *RpProbNNpHistMC = new TH1F("RpProbNNpHistMC","",50,0,1);
  TH1F *DTAUHistMC = new TH1F("DTAUHistMC","",100,-1,1.5); 


//  TCut cuts = "Xb_DIRA_OWNPV>0.99995&&abs(Jpsi_M-3097)<30&&k_ProbNNk>0.3&&R_ENDVERTEX_CHI2/R_ENDVERTEX_NDOF<8&&pi_ProbNNpi>0.1&&Rpi_ProbNNpi>0.1&&abs(Xb_TRUEID)==521";
  TCut cuts = "abs(D_M-1864)<30&&K_ProbNNk>0.3&&Rp_PIDp>5&&K_PIDK>0&&pi_PIDK<5&&Rpi_PIDK<5&&Xb_DIRA_OWNPV>0.99995&&Xb_IPCHI2_OWNPV<16&&R_M<3400";
  cuts = cuts && "Xb_TRUEID!=0 && D_BKGCAT==0&&abs(Rp_TRUEID)==2212&&abs(K_TRUEID)==321&&abs(Rpi_TRUEID)>200&&Pr_V3ProbNNp>0.1 && RPi_V3ProbNNpi>0.05 && K_V3ProbNNk>0.3 && Pi_V3ProbNNpi>0.01 &&abs(D_M-1865)<30 &&abs(Xb_M-5620)<70";
  

  TCanvas *cc = new TCanvas("cc","",800,800);
  
  treeMC->Draw("D_M>>DMassMC",cuts);
  treeMC->Draw("log(sqrt(pow(Xb_ENDVERTEX_X-Xb_OWNPV_X,2)+pow(Xb_ENDVERTEX_Y-Xb_OWNPV_Y,2)))>>RfdHistMC",cuts);
  treeMC->Draw("log(Xb_PT)-0.1>>XbPTHistMC",cuts);
  treeMC->Draw("log(R_PT)-0.1>>RPTHistMC",cuts);
  treeMC->Draw("log(Xb_IPCHI2_OWNPV)+0.1>>XbIPChisqHistMC",cuts);
  treeMC->Draw("log(D_IPCHI2_OWNPV)+0.3>>DIPChisqHistMC",cuts);
//  treeMC->Draw("log(Jpsi_IPCHI2_OWNPV)>>JpsiIPChisqHistMC",cuts);
//  treeMC->Draw("log(K_IPCHI2_OWNPV)+0.4>>KIPChisqHistMC",cuts);
  treeMC->Draw("log(K_IPCHI2_OWNPV)+0.2>>KIPChisqHistMC",cuts);
  treeMC->Draw("log(pi_IPCHI2_OWNPV)>>piIPChisqHistMC",cuts);
  treeMC->Draw("log(Rpi_IPCHI2_OWNPV)+0.6>>RpiIPChisqHistMC",cuts);
//  treeMC->Draw("log(mup_IPCHI2_OWNPV)>>mupIPChisqHistMC",cuts);
//  treeMC->Draw("log(mum_IPCHI2_OWNPV)>>mumIPChisqHistMC",cuts);
//  treeMC->Draw("log(R_PT/Jpsi_PT)>>R2JpsiPTHistMC",cuts);
  treeMC->Draw("log(D_ENDVERTEX_CHI2)>>DVtxChisqHistMC",cuts);
  treeMC->Draw("log(K_P)-0.2>>KPHistMC",cuts);
  treeMC->Draw("log(Rp_P)>>RpPHistMC",cuts);
  treeMC->Draw("log(pi_P)-0.1>>piPHistMC",cuts);
  treeMC->Draw("log(Rpi_P)+0.1>>RpiPHistMC",cuts);
  treeMC->Draw("1000*D_TAU-0.015>>DTAUHistMC",cuts);
  treeMC->Draw("1-sqrt(1-K_V3ProbNNk)>>KProbNNkHistMC",cuts);
  treeMC->Draw("1-sqrt(1-Pi_V3ProbNNpi)>>piProbNNpiHistMC",cuts);
  treeMC->Draw("1-sqrt(1-RPi_V3ProbNNpi)-0.01>>RpiProbNNpiHistMC",cuts);
  treeMC->Draw("1-sqrt(1-Pr_V3ProbNNp)>>RpProbNNpHistMC",cuts);

  doNorm(DMass,DMassMC);
 doNorm(RfdHist,RfdHistMC);
  doNorm(XbPTHist,XbPTHistMC);
  doNorm(RPTHist,RPTHistMC);
  doNorm(XbIPChisqHist,XbIPChisqHistMC);
  doNorm(DIPChisqHist,DIPChisqHistMC);
//  doNorm(JpsiIPChisqHist,JpsiIPChisqHistMC);
  doNorm(KIPChisqHist,KIPChisqHistMC);
  doNorm(piIPChisqHist,piIPChisqHistMC);
  doNorm(RpiIPChisqHist,RpiIPChisqHistMC);
//  doNorm(mupIPChisqHist,mupIPChisqHistMC);
//  doNorm(mumIPChisqHist,mumIPChisqHistMC);
//  doNorm(R2JpsiPTHist,R2JpsiPTHistMC);
  doNorm(DVtxChisqHist,DVtxChisqHistMC);
  doNorm(KPHist, KPHistMC);
  doNorm(RpPHist, RpPHistMC);
  doNorm(piPHist,piPHistMC);
  doNorm(RpiPHist,RpiPHistMC);
  doNorm(DTAUHist,DTAUHistMC);
  doNorm(KProbNNkHist,KProbNNkHistMC);
  doNorm(piProbNNpiHist,piProbNNpiHistMC);
  doNorm(RpiProbNNpiHist,RpiProbNNpiHistMC);
  doNorm(RpProbNNpHist,RpProbNNpHistMC);
  

  int ii = 1;
  TCanvas *c1 = new TCanvas("c1","",1500,1000);  
  c1->Divide(6,4);
  c1->cd(ii++);
  DMass->Draw();
  DMassMC->Draw("same");
  c1->cd(ii++);
  RfdHist->Draw();
  RfdHistMC->Draw("same");
  c1->cd(ii++);
  XbPTHist->Draw();
  XbPTHistMC->Draw("same");
  c1->cd(ii++);
  RPTHist->Draw();
  RPTHistMC->Draw("same");
  c1->cd(ii++);
//  R2JpsiPTHist->Draw();
//  R2JpsiPTHistMC->Draw("same");
//  c1->cd(ii++);
  XbIPChisqHist->Draw();
  XbIPChisqHistMC->Draw("same");
  c1->cd(ii++);
  DIPChisqHist->Draw();
  DIPChisqHistMC->Draw("same");
  c1->cd(ii++);
//  JpsiIPChisqHist->Draw();
//  JpsiIPChisqHistMC->Draw("same");
//  c1->cd(ii++);
  KIPChisqHist->Draw();
  KIPChisqHistMC->Draw("same");
  c1->cd(ii++);
  piIPChisqHist->Draw();
  piIPChisqHistMC->Draw("same");
  c1->cd(ii++);
  RpiIPChisqHist->Draw();
  RpiIPChisqHistMC->Draw("same");
  c1->cd(ii++);
//  mupIPChisqHist->Draw();
//  mupIPChisqHistMC->Draw("same");
//  c1->cd(ii++);
//  mumIPChisqHist->Draw();
//  mumIPChisqHistMC->Draw("same");
//  c1->cd(ii++);
  DVtxChisqHist->Draw();
  DVtxChisqHistMC->Draw("same");
  c1->cd(ii++);
  RpPHist->Draw();
  RpPHistMC->Draw("same");
  c1->cd(ii++);
  KPHist->Draw();
  KPHistMC->Draw("same");
  c1->cd(ii++);
  piPHist->Draw();
  piPHistMC->Draw("same");
  c1->cd(ii++);
  RpiPHist->Draw();
  RpiPHistMC->Draw("same");
  c1->cd(ii++);
  KProbNNkHist->Draw();
  KProbNNkHistMC->Draw("same");
  c1->cd(ii++);
  piProbNNpiHist->Draw();
  piProbNNpiHistMC->Draw("same");
  c1->cd(ii++);
  RpiProbNNpiHist->Draw();
  RpiProbNNpiHistMC->Draw("same");
  c1->cd(ii++);
  RpProbNNpHist->Draw();
  RpProbNNpHistMC->Draw("same");
  c1->cd(ii++);
  DTAUHist->Draw();
  DTAUHistMC->Draw("same");

    





}
