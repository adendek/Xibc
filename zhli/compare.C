
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



void compare(){

  bool withBDT = true;
  bool reweight = true;

  TFile *fs = new TFile("test.root");
  
  TH1F *DMassHist = (TH1F*)fs->Get("DMassHist__DMass")->Clone("DMassHist");
  TH1F *RfdHist = (TH1F*)fs->Get("RfdHist__Rfd")->Clone("RfdHist");
  TH1F *DOFChisqHist = (TH1F*)fs->Get("DOFChisqHist__DOFChisq")->Clone("DOFChisqHist");
  TH1F *XbIPChisqHist = (TH1F*)fs->Get("XbIPChisqHist__XbIPChisq")->Clone("XbIPChisqHist");
  TH1F *DIPChisqHist = (TH1F*)fs->Get("DIPChisqHist__DIPChisq")->Clone("DIPChisqHist");
//  TH1F *JpsiIPChisqHist = (TH1F*)fs->Get("JpsiIPChisqHist__JpsiIPChisq")->Clone("JpsiIPChisq");
  TH1F *KIPChisqHist = (TH1F*)fs->Get("KIPChisqHist__KIPChisq")->Clone("KIPChisqHist");
  TH1F *piIPChisqHist = (TH1F*)fs->Get("piIPChisqHist__piIPChisq")->Clone("piIPChisqHist");
  TH1F *RpiIPChisqHist = (TH1F*)fs->Get("RpiIPChisqHist__RpiIPChisq")->Clone("RpiIPChisqHist");
//  TH1F *mupIPChisqHist = (TH1F*)fs->Get("mupIPChisqHist__mupIPChisq")->Clone("mupIPChisqHist");
//  TH1F *mumIPChisqHist = (TH1F*)fs->Get("mumIPChisqHist__mumIPChisq")->Clone("mumIPChisqHist");
  TH1F *XbPTHist = (TH1F*)fs->Get("XbPTHist__XbPT")->Clone("XbPTHist__XbPT");
  TH1F *RpPTHist = (TH1F*)fs->Get("RpPTHist__RpPT")->Clone("RpPTHist");
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
  TH1F *nTracksHist = (TH1F*)fs->Get("nTracksHist__nTracks")->Clone("nTracksHist");
  if(withBDT)
    {
      TH1F *BDTGHist = (TH1F*)fs->Get("BDTGHist__BDTG")->Clone("BDTGHist"); 
    }
  TH1F *RMassHist = (TH1F*)fs->Get("RMassHist__RMass")->Clone("RMassHist");
  TH1F *DpHist = (TH1F*)fs->Get("DpHist__Dp")->Clone("DpHist");

  if(!reweight)
    {
      TFile *fmc = new TFile("/data1/zli59/D0ppi/MC.tuned.piKppi.wMVA.test.root");
    }
  else
    {
      TFile *fmc = new TFile("/data1/zli59/D0ppi/MC.tuned.piKppi.wMVA.test.addWeight.root");
     }
  treeMC = (TTree*)fmc->Get("mytree");
  
  //  TH1F *DMassMC = new TH1F("DMassMC","",48,1834,1894); 
  TH1F *RMassHistMC = new TH1F("RMassHistMC","",50,1000,4000); 
  TH1F *DpHistMC = new TH1F("DpHistMC","",50,2770,3070); 
  TH1F *RfdHistMC = new TH1F("RfdHistMC","",45,-4,4);
  TH1F *DOFChisqHistMC = new TH1F("DOFChisqHistMC","",50,-2.5,2.5);
  TH1F *XbIPChisqHistMC = new TH1F("XbIPChisqHistMC","",50,-6,4);
  TH1F *DIPChisqHistMC = new TH1F("DIPChisqHistMC","",80,-4,12);
  //  TH1F *JpsiIPChisqMC = new TH1F("JpsiIPChisqMC","",80,-6,10);
  TH1F *KIPChisqHistMC = new TH1F("KIPChisqHistMC","",45,0,12);
  TH1F *piIPChisqHistMC = new TH1F("piIPChisqHistMC","",45,0,12);
  TH1F *RpiIPChisqHistMC = new TH1F("RpiIPChisqHistMC","",45,0,12);
//  TH1F *mupIPChisqHistMC = new TH1F("mupIPChisqHistMC","",70,-2,12); 
//  TH1F *mumIPChisqHistMC = new TH1F("mumIPChisqHistMC","",70,-2,12); 
  TH1F *XbPTHistMC = new TH1F("XbPTHistMC","",60,7,11); 
  TH1F *RpPTHistMC = new TH1F("RpPTHistMC","",60,5,11); 
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
  TH1F *nTracksHistMC = new TH1F("nTracksHistMC","",325,0,650);
  if(withBDT)
    {
      TH1F *BDTGHistMC = new TH1F("BDTGHistMC","",100,-1,1); 
    } 



//  TCut cuts = "Xb_DIRA_OWNPV>0.99995&&abs(Jpsi_M-3097)<30&&k_ProbNNk>0.3&&R_ENDVERTEX_CHI2/R_ENDVERTEX_NDOF<8&&pi_ProbNNpi>0.1&&Rpi_ProbNNpi>0.1&&abs(Xb_TRUEID)==521";
  TCut cuts = "abs(D_M-1864)<30&&K_MC12TuneV3_ProbNNk>0.3&&Rp_PIDp>5&&K_PIDK>0&&pi_PIDK<5&&Rpi_PIDK<5&&Xb_DIRA_OWNPV>0.99995&&Xb_IPCHI2_OWNPV<16&&R_M<3400";
  cuts = cuts && "Xb_TRUEID!=0 && D_BKGCAT==0&&abs(Rp_TRUEID)==2212&&abs(K_TRUEID)==321&&abs(Rpi_TRUEID)>200&&Rp_MC12TuneV3_ProbNNp>0.1 && Rpi_MC12TuneV3_ProbNNpi>0.05 && K_MC12TuneV3_ProbNNk>0.3 && pi_MC12TuneV3_ProbNNpi>0.01 &&abs(D_M-1865)<30 &&abs(Xb_M-5620)<70&&Rp_MC12TuneV3_ProbNNp>0.1&&pi_MC12TuneV3_ProbNNpi>0.05&&Rpi_MC12TuneV3_ProbNNpi>0.05";
  if(reweight) 
    {
      TCut wCutR = "RWeight";
      TCut wCutDp = "DpWeight";
      cuts = cuts * wCutR * wCutDp;
    }

  //  TCanvas *cc = new TCanvas("cc","",800,800);
  
  treeMC->Draw("D_M>>DMassHistMC",cuts);
  treeMC->Draw("log(sqrt(pow(Xb_ENDVERTEX_X-Xb_OWNPV_X,2)+pow(Xb_ENDVERTEX_Y-Xb_OWNPV_Y,2)))>>RfdHistMC",cuts);
  treeMC->Draw("log(Xb_LOKI_CHI2NDOF_D0Constr)>>DOFChisqHistMC",cuts);
  treeMC->Draw("log(Xb_PT)-0.1>>XbPTHistMC",cuts);
  treeMC->Draw("log(Rp_PT)>>RpPTHistMC",cuts);
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
  //  treeMC->Draw("log(R_M)-0.2>>KPHistMC",cuts);
  treeMC->Draw("log(Rp_P)>>RpPHistMC",cuts);
  treeMC->Draw("log(pi_P)-0.1>>piPHistMC",cuts);
  treeMC->Draw("log(Rpi_P)+0.1>>RpiPHistMC",cuts);
  treeMC->Draw("1000*D_TAU-0.015>>DTAUHistMC",cuts);
  treeMC->Draw("1-sqrt(1-K_MC12TuneV3_ProbNNk)>>KProbNNkHistMC",cuts);
  treeMC->Draw("1-sqrt(1-pi_MC12TuneV3_ProbNNpi)>>piProbNNpiHistMC",cuts);
  treeMC->Draw("1-sqrt(1-Rpi_MC12TuneV3_ProbNNpi)-0.01>>RpiProbNNpiHistMC",cuts);
  treeMC->Draw("1-sqrt(1-Rp_MC12TuneV3_ProbNNp)>>RpProbNNpHistMC",cuts);
  treeMC->Draw("nTracks>>nTracksHistMC",cuts);
  if(withBDT) treeMC->Draw("BDTG>>BDTGHistMC",cuts);
  treeMC->Draw("R_M>>RMassHistMC",cuts);
  treeMC->Draw("sqrt(pow(D_PE+Rp_PE,2)-pow(D_PX+Rp_PX,2)-pow(D_PY+Rp_PY,2)-pow(D_PZ+Rp_PZ,2))>>DpHistMC",cuts);

  doNorm(DMassHist,DMassHistMC);
  doNorm(RfdHist,RfdHistMC);
  doNorm(DOFChisqHist,DOFChisqHistMC);
  doNorm(XbPTHist,XbPTHistMC);
  doNorm(RpPTHist,RpPTHistMC);
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
  doNorm(nTracksHist,nTracksHistMC);
  if(withBDT) doNorm(BDTGHist,BDTGHistMC);
  doNorm(RMassHist,RMassHistMC);
  doNorm(DpHist,DpHistMC);

  int ii = 1;
  TCanvas *c1 = new TCanvas("c1","",1500,1000);  
  c1->Divide(6,4);
  //c1->cd(ii++);
  //DMassHist->Draw();
  //DMassHistMC->Draw("same");
  c1->cd(ii++);
  RfdHist->Draw();
  RfdHistMC->Draw("same");
  c1->cd(ii++);
  DOFChisqHist->Draw();
  DOFChisqHistMC->Draw("same");
  c1->cd(ii++);
  XbPTHist->Draw();
  XbPTHistMC->Draw("same");
  c1->cd(ii++);
  RpPTHist->Draw();
  RpPTHistMC->Draw("same");
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
  c1->cd(ii++);
  nTracksHist->Draw();
  nTracksHistMC->Draw("same");

  c1->cd(ii++);
  RMassHist->Draw();
  RMassHistMC->Draw("same");
  c1->cd(ii++);
  DpHist->Draw();
  DpHistMC->Draw("same");

    

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
    
    double n1,totNo,f, n2,totNo2, r;
    totNo = BDTGHist->Integral(1,100);
    cout<<"totNo = "<<totNo<<endl;
    totNo2 = BDTGHistMC->Integral(1,100);
    for(int i=0;i<100;i++){
      n1 = BDTGHist->Integral(i+1,100);
      f = n1/BDTGHist->Integral(1,100);
      cout<<"BinContent = "<<BDTGHist->GetBinContent(i+1)<<"\t n1 = "<<n1<<"\t totNo = "<<totNo<<endl;
      hd->SetBinContent(i+1,f);
      n2 = BDTGHistMC->Integral(i+1,100);
      f = n2/BDTGHistMC->Integral(1,100);
      // cout<<"BinContent = "<<BDTGHistMC->GetBinContent(i+1)<<"\t n1 = "<<n2<<"\t totNo = "<<totNo2<<endl;
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

    c3->Print("BDTEff_Comp.png");
    
  }
  
    if(!reweight)
      {
	TFile *fout = new TFile("histRatio.root","RECREATE");

	TCanvas *c4 = new TCanvas("c4","",1000,700);  
	c4->Divide(2,1);
	c4->cd(1);
	TH1F *hrat = (TH1F*)RMassHist->Clone("hrat");
	hrat->Divide(RMassHistMC);
	hrat->SetMaximum(5);  
	hrat->Draw();
	//TF1 *fr = new TF1("fr","[0]+[1]*exp([2]*(x-1300))",1000,4000);
	//fr->SetParameters(0.3,7,-0.004);
	//hrat->Fit("fr","R");
	
	c4->cd(2);
	TH1F *hrat2 = (TH1F*)DpHist->Clone("hrat2");
	hrat2->Divide(DpHistMC);
	hrat2->SetMaximum(5);  
	hrat2->Draw();
	//TF1 *fr2 = new TF1("fr2","[0]*exp([1]*(x-3500))",2770,3070);
	//fr2->SetParameters(2,-0.0005);
	//hrat2->Fit("fr2","R");
    
	hrat->Write();
	hrat2->Write();
    
	fout->Close();
    
      }



}
