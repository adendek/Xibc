
using namespace std;
using namespace RooFit;

TString lt;


TCanvas* makeRooPlot(RooAbsPdf* pdf, RooAbsData* rdh, RooRealVar *mvar, int mode, RooRealVar* nS,
                     TString tag="def",double mlow=2420, double mhi=2520, int nbin=50){
  
  TLatex *myLatex = new TLatex();
  myLatex->SetTextFont(42); myLatex->SetTextColor(1); myLatex->SetTextAlign(12); myLatex->SetNDC(kTRUE); myLatex->SetTextSize(0.045);
  double xt = 0.18;
  int bw = (mhi-mlow)/nbin;

  tag = tag.ReplaceAll("#","");
  tag = tag.ReplaceAll("^{0}","z");
  tag = tag.ReplaceAll("^{+}","");
  tag = tag.ReplaceAll("^{-}","");
  tag = tag.ReplaceAll("_{c}","c");
  

  TString comps = Form("gauss%d",mode);
  TString titleY = Form("Candidates / [%d MeV/#it{c}^{2}]",bw);

  if(mode==0 || mode==2 || mode==10 || mode==12){
    //TString titleX = "pK^{#font[122]{-}}#pi^{+} mass [MeV/#it{c}^{2}]";
     TString titleX = "J/#psi K^{#font[122]{-}}#pi^{+}#pi^{#font[122]{-}}mass [MeV/#it{c}^{2}]";
  }else if(mode==1 || mode==4 || mode==11 || mode==14){
    TString titleX = "pK^{#font[122]{-}}K^{#font[122]{-}}#pi^{+} mass [MeV/#it{c}^{2}]";
  }else if(mode==3 || mode==13){
    TString titleX = "K^{#font[122]{-}}#pi^{+}#pi^{+} mass [MeV/#it{c}^{2}]";
  }
  


  TCanvas *c = new TCanvas("c_"+tag, "Mass Plot "+tag,0,0,600,600);
  c->SetRightMargin(0.05);
  c->SetLeftMargin(0.15);
  c->SetBottomMargin(0.11);
  RooPlot* plot2 = mvar->frame(mlow,mhi,nbin);
  plot2->SetTitle("");
  rdh->plotOn(plot2,MarkerStyle(20),MarkerSize(0.75));
  pdf->plotOn(plot2,LineColor(kBlue),LineWidth(2),Name("Full")); 
  pdf->plotOn(plot2,Components(comps),LineColor(kRed),LineWidth(2),Name("Signal"));
  setFrameAtt(plot2,titleX, titleY);
  plot2->SetMinimum(0.1);
  plot2->SetMaximum(1.2*plot2->GetMaximum());
  plot2->Draw();
  //hh->SetLineColor(3);
  //hh->Draw("same");

  float ns = nS->getVal();
  float ens = nS->getError();
  TString y = Form("N_{sig} =  %4.0f #pm %2.0f",ns,ens);
  myLatex->DrawLatex(xt,0.85,y);
  myLatex->DrawLatex(xt,0.8,lt);

  //c->Print("./MassPlot_"+tag+".png");


  return c;

  
}

void addGraphics(TH1F *h, TString Xtitle){
  h->SetXTitle(Xtitle);
  //h->SetFillColor(30);
  int bw = h->GetBinWidth(1);
  h->SetYTitle("Candidates");
  h->SetStats(kFALSE);
  h->SetMinimum(0.0);
  h->SetMaximum(1.1*h->GetMaximum());
  h->SetTitleSize(0.1);
  h->SetLineColor(kBlack);
  h->SetMarkerSize(1.0);
  h->SetMarkerStyle(20);
  h->GetXaxis()->SetTitleOffset(1.0);  
  h->GetYaxis()->SetTitleOffset(1.15);
  h->GetXaxis()->SetTitleSize(0.05);  
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetLabelSize(0.04);  
  h->GetYaxis()->SetLabelSize(0.04);  
  h->SetNdivisions(404,"X");
  h->SetNdivisions(505,"Y");
  h->SetLineWidth(2);
  h->SetTitle("");
  
}

void setFrameAtt(RooPlot *frame, TString xtit, TString ytit)
{
  frame->SetMaximum(0.9*frame->GetMaximum());
  //frame->SetMaximum(35);
  frame->SetMinimum(0.1);    
  frame->SetLabelSize(0.045,"X");
  frame->SetLabelSize(0.045,"Y");
  frame->SetTitleSize(0.050,"X");
  frame->SetTitleSize(0.050,"Y");
  frame->SetTitleOffset(1.0,"X");
  frame->SetTitleOffset(1.45,"Y");
  frame->SetXTitle(xtit);
  frame->SetYTitle(ytit);
  frame->SetNdivisions(505,"X");
  frame->SetNdivisions(505,"Y");
  //frame->GetXaxis()->SetTitleFont(myconfigs->m_font);
  //frame->GetYaxis()->SetTitleFont(myconfigs->m_font);
}





double EstSigYield(TH1F* h,double m, double s=6){
  double bw = h->GetBinWidth(1);
  int iL = h->FindBin(m-3*s);
  int iH = h->FindBin(m+3*s);
  int iC = h->FindBin(m);
  double nS = h->Integral(iL,iH);
  double nL = h->Integral(1,iL-1);
  double nH = h->Integral(iH+1,h->GetNbinsX());
  double r = (iH-iL);
  r = r / (iL + (h->GetNbinsX()-iH));
  double Y = nS - (nL + nH)*r;
  cout << "Expected yield = " << Y << ", r = " << r << endl;
  //cout << "nL, nH, nS = " << nL << " " << nH << " " << nS << endl;
  
  return Y;  

}

TChain* getLum(TString name){
  TChain *ch = new TChain(name,"");
  ch->Add("/data1/sblusk/Xibc/JpsiX/All_2011_MAGDN.root/"+name);
  ch->Add("/data1/sblusk/Xibc/JpsiX/All_2011_MAGUP.root/"+name);
  ch->Add("/data1/sblusk/Xibc/JpsiX/All_2012_MAGDN.root/"+name);
  ch->Add("/data1/sblusk/Xibc/JpsiX/All_2012_MAGUP.root/"+name);
  return ch;      

}



TChain* getChain(TString name, bool withBDT = false){

  TChain *ch = new TChain(name,"");
  if(!withBDT){
    ch->Add("/data1/sblusk/Xibc/JpsiX/JpsiKpipi/data/All_2011_MAGDN.kpipi.rs.root/"+name);
    ch->Add("/data1/sblusk/Xibc/JpsiX/JpsiKpipi/data/All_2011_MAGUP.kpipi.rs.root/"+name);
    ch->Add("/data1/sblusk/Xibc/JpsiX/JpsiKpipi/data/All_2012_MAGDN.kpipi.rs.root/"+name);
    ch->Add("/data1/sblusk/Xibc/JpsiX/JpsiKpipi/data/All_2012_MAGUP.kpipi.rs.root/"+name);
  }else{
    ch->Add("/data1/sblusk/Xibc/JpsiX/JpsiKpipi/data/All_2011_MAGDN.kpipi.rs.X2JpsiKpipi.X2Kpipi.wMVA.test3.root/"+name);
    ch->Add("/data1/sblusk/Xibc/JpsiX/JpsiKpipi/data/All_2011_MAGUP.kpipi.rs.X2JpsiKpipi.X2Kpipi.wMVA.test3.root/"+name);
    ch->Add("/data1/sblusk/Xibc/JpsiX/JpsiKpipi/data/All_2012_MAGDN.kpipi.rs.X2JpsiKpipi.X2Kpipi.wMVA.test3.root/"+name);
    ch->Add("/data1/sblusk/Xibc/JpsiX/JpsiKpipi/data/All_2012_MAGUP.kpipi.rs.X2JpsiKpipi.X2Kpipi.wMVA.test3.root/"+name);
  }  

  
  return ch;    

}



void plots(){

  gStyle->SetStatH(0.28);

  bool withBDT = true;  // pick up tuples with BDT
  bool phaseSpaceCuts = false;
  TString suffix = "all";
  if(phaseSpaceCuts) suffix = "phaseSpaceCut";

  bool do_splot = false;


  TLatex *myLatex = new TLatex();
  myLatex->SetTextFont(42); myLatex->SetTextColor(1); myLatex->SetTextAlign(12); myLatex->SetNDC(kTRUE); myLatex->SetTextSize(0.045);
   double xt = 0.6;

  TCanvas *c = new TCanvas("c","Plot",800,800);

  TChain *l = getLum("GetIntegratedLuminosity/LumiTuple");  
  TH1F *lum = new TH1F("lum","Lumi",5,0,5);
  l->Draw("0.5>>lum","IntegratedLuminosity");
  float lumi = lum->GetBinContent(1);    
  lt = Form("Lum =  %4.0f pb^{-1}",lumi);
  TTree* tree[20];
  TChain *ch = getChain("mytree", withBDT);//new TChain("mytree","");
  tree[0] = ch;  

  
  RooRealVar* mvar[20];
  RooRealVar* mg[20];
  RooRealVar* fr[20];
  RooRealVar* sg[20];
  RooRealVar* sg2[20];
  RooRealVar* b1[20];
  RooCBShape* CBA[20];
  RooGaussian* gaussA[20];
  RooGaussian* gaussB[20];
  RooAbsPdf* gauss[20];
  RooExponential* comb[20];
  RooRealVar* nsig[20];
  RooRealVar* ncomb[20];
  RooRealVar* nsig0;
  RooRealVar* ncomb0;
  RooAbsPdf* pdf[20];
  RooDataHist *rdh[20];
  double sy[20], by[20];
  TString modes[20] = {"J/#psiK#pi#pi", "#Xi_{c}^{0}", "#Lambda_{c}^{+}", "D^{+}", "#Omega_{c}^{0}",  
                      "", "","","","",
                      "#Xi_{c}^{+}", "#Xi_{c}^{0}", "#Lambda_{c}^{+}", "D^{+}", "#Omega_{c}^{0}", 
                      "", "","","",""};
  
  TCanvas *ccc = new TCanvas("ccc","Xic",1200,600);
  
  int i=0;
  
  float masses[20] = {5280, 2472, 2288, 1871, 2696, 0,0,0,0,0, 2469, 2472, 2288, 1871, 2696, 0,0,0,0,0 };  
  double mlow[20] = {5180, 2420, 2240, 1820, 2645, 0,0,0,0,0, 2420, 2420, 2240, 1820,2645, 0,0,0,0,0 };
  double mhi[20]  = {5380, 2520, 2330, 1920, 2745, 0,0,0,0,0, 2520, 2520, 2330, 1920, 2745, 0,0,0,0,0};  
  double bw[20] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,};
  int nbins[20];
  for(int j=0; j<20; j++){nbins[j] = (mhi[j]-mlow[j])/bw[j];}
  TH1F *h[20];


  TCut cuts[20];
  cuts[0] = "Xb_DIRA_OWNPV>0.99995&&abs(Jpsi_M-3097)<30&&k_V3ProbNNk>0.1&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<8&&pi1_V3ProbNNpi>0.01&&pi2_V3ProbNNpi>0.01";
  TString mRangeCut = Form("Xb_LOKI_MASS_massConstr>%4.0f&&Xb_LOKI_MASS_massConstr<%4.0f",mlow[0],mhi[0]);
  cuts[0] = cuts[0] && mRangeCut;
  cuts[0] = cuts[0] && "abs(sqrt( pow(Jpsi_PE+pi1_PE+pi2_PE,2)-pow(Jpsi_PX+pi1_PX+pi2_PX,2)-pow(Jpsi_PY+pi1_PY+pi2_PY,2)-pow(Jpsi_PZ+pi1_PZ+pi2_PZ,2) )-Jpsi_M - 590)>20";
  if(phaseSpaceCuts){
    cuts[0] = cuts[0] && "Xc_M>1500&&Xc_M<1800";
    // remove psi'K, just for this comparson, which will be quite different kineamtically than J/psi K pi pi
  }
  

  TCanvas *cc[20];
  
  double sigma[20]; for(int j=0;j<20;j++){sigma[j] = 8.0;}

  RooRealVar* cbn = new RooRealVar("cbn","",10.);
  RooRealVar* cba = new RooRealVar("cba","",1.8,0,5);
  RooRealVar *moff = new RooRealVar("moff","Offset",3097);

  //------------------------------------
  // Set up fit PDF, define fit function
  //------------------------------------
  mvar[i] = new RooRealVar("Xb_LOKI_MASS_massConstr","Xb_LOKI_MASS_massConstr",mlow[i],mhi[i]);
  h[i] = new TH1F(Form("h%d",i),"Mass",nbins[i],mlow[i],mhi[i]);
  TString histExp = Form("Xb_LOKI_MASS_massConstr>>h%d",i);
  tree[i]->Draw(histExp,cuts[i]);
  
  mg[i] = new RooRealVar(Form("mg%d",i),"mean",masses[i],masses[i]-10,masses[i]+10);
  sg[i] = new RooRealVar(Form("sg%d",i),"width",sigma[i],2,25);
  sg2[i] = new RooRealVar(Form("sg2%d",i),"width",10,2,50);
  fr[i] = new RooRealVar(Form("fr%d",i),"fraction",0.99,0.5,1.0);

  CBA[i] = new RooCBShape(Form("CBA%d",i),"", *mvar[i], *mg[i], *sg[i], *cba, *cbn);
  //gaussA[i] = new RooGaussian(Form("gaussA%d",i),"Signal",*mvar[i],*mg[i],*sg[i]);
  //gauss[i] = new RooAddPdf(Form("gauss%d",i),"Signal",RooArgList(*gaussA[i],*gaussB[i]),RooArgList(*fr[i]));
  gaussB[i] = new RooGaussian(Form("gaussB%d",i),"Signal",*mvar[i],*mg[i],*sg2[i]);
  gauss[i] = new RooAddPdf(Form("gauss%d",i),"Signal",RooArgList(*CBA[i],*gaussB[i]),RooArgList(*fr[i]));
  b1[i]  = new RooRealVar(Form("b%d",i), "b1", -0.0003,-0.05,0.05);//0.002,-0.005,0.000001);
  comb[i] = new RooExponential(Form("comb%d",i),"f_{back}",*mvar[i],*b1[i]);
  sy[i] = EstSigYield(h[i], masses[i], sigma[i]);
  by[i] = h[i]->GetEntries()-sy[i];
  nsig[i] = new RooRealVar(Form("nsig%d",i),"",sy[i],0,30000000);
  ncomb[i] = new RooRealVar(Form("ncomb%d",i),"",by[i],0,30000000);
  rdh[i] = new RooDataHist(Form("rdh%d",i),"", *mvar[i], h[i]);
  pdf[i] = new RooAddPdf(Form("pdf%d",i),"",RooArgList(*gauss[i],*comb[i]),RooArgList(*nsig[i],*ncomb[i]));

  //--------
  // Do fit
  //--------
  pdf[i]->fitTo(*rdh[i],Hesse(kTRUE),Strategy(1));
  cc[i] = makeRooPlot(pdf[i],rdh[i],mvar[i],i,nsig[i],modes[i],mlow[i],mhi[i],nbins[i]);
  cc[i]->Update();
  cc[i]->Print("./massPlot_"+suffix+".png");
  
  

  
  if(!do_splot) return;
  
  TString fileName = "/data1/sblusk/Xibc/JpsiX/JpsiKpipi/data/sWeightedData_"+suffix+".root";
  TFile *fout = new TFile(fileName,"RECREATE");

  TTree* treeNew1 = tree[i]->CopyTree(cuts[i]);

  //--------------------------------------------
  // Variables that are needed in the sWeighting
  //--------------------------------------------
  RooRealVar* Xc_M = new RooRealVar("Xc_M","Xc mass",-1.0e10,1.0e10);
  RooRealVar* Xb_ENDVERTEX_X = new RooRealVar("Xb_ENDVERTEX_X","Xb pos",-1.0e10,1.0e10);
  RooRealVar* Xb_ENDVERTEX_Y = new RooRealVar("Xb_ENDVERTEX_Y","Xb pos",-1.0e10,1.0e10);
  RooRealVar* Xb_OWNPV_X = new RooRealVar("Xb_OWNPV_X","Xb PV pos",-1.0e10,1.0e10);
  RooRealVar* Xb_OWNPV_Y = new RooRealVar("Xb_OWNPV_Y","Xb PV pos",-1.0e10,1.0e10);
  RooRealVar* Xb_LOKI_DTF_CHI2NDOF = new RooRealVar("Xb_LOKI_DTF_CHI2NDOF","Xb DTF chisq",-1.0e10,1.0e10);
  RooRealVar* Xb_ENDVERTEX_CHI2 = new RooRealVar("Xb_ENDVERTEX_CHI2","Xb Vtx chisq",-1.0e10,1.0e10);
  RooRealVar* Xb_ENDVERTEX_NDOF = new RooRealVar("Xb_ENDVERTEX_NDOF","Xb Vtx ndof",-1.0e10,1.0e10);

  RooRealVar* Xb_IPCHI2_OWNPV = new RooRealVar("Xb_IPCHI2_OWNPV","Xb IP chisq",-1.0e10,1.0e10);
  RooRealVar* Xb_DIRA_OWNPV = new RooRealVar("Xb_DIRA_OWNPV","Xb DIRA",-1.0e10,1.0e10);
  RooRealVar* Xb_PT = new RooRealVar("Xb_PT","Xb PT",-1.0e10,1.0e10);
  RooRealVar* Jpsi_IPCHI2_OWNPV = new RooRealVar("Jpsi_IPCHI2_OWNPV","Jpsi IP chisq",-1.0e10,1.0e10);
  RooRealVar* Jpsi_PT = new RooRealVar("Jpsi_PT","Jpsi PT",-1.0e10,1.0e10);
  RooRealVar* Xc_PT = new RooRealVar("Xc_PT","Xc PT",-1.0e10,1.0e10);
  RooRealVar* Xc_IPCHI2_OWNPV = new RooRealVar("Xc_IPCHI2_OWNPV","Xc IP chisq",-1.0e10,1.0e10);
  RooRealVar* Xc_TAU = new RooRealVar("Xc_TAU","Xc TAU",-1.0e10,1.0e10);
  RooRealVar* mup_IPCHI2_OWNPV = new RooRealVar("mup_IPCHI2_OWNPV","mup IP chisq",-1.0e10,1.0e10);
  RooRealVar* mum_IPCHI2_OWNPV = new RooRealVar("mum_IPCHI2_OWNPV","mum IP chisq",-1.0e10,1.0e10);
  RooRealVar* k_IPCHI2_OWNPV = new RooRealVar("k_IPCHI2_OWNPV","k IP chisq",-1.0e10,1.0e10);
  RooRealVar* pi1_IPCHI2_OWNPV = new RooRealVar("pi1_IPCHI2_OWNPV","pi1 IP chisq",-1.0e10,1.0e10);
  RooRealVar* pi2_IPCHI2_OWNPV = new RooRealVar("pi2_IPCHI2_OWNPV","pi2 IP chisq",-1.0e10,1.0e10);
  RooRealVar* Xc_ENDVERTEX_CHI2 = new RooRealVar("Xc_ENDVERTEX_CHI2","Xc Vertex chisq",-1.0e10,1.0e10);
  RooRealVar* k_P = new RooRealVar("k_P","K^{-} momentum",-1.0e10,1.0e10);
  RooRealVar* pi1_P = new RooRealVar("pi1_P","#pi^{+} momentum",-1.0e10,1.0e10);
  RooRealVar* pi2_P = new RooRealVar("pi2_P","#pi^{-} momentum",-1.0e10,1.0e10);
  RooRealVar* k_V3ProbNNk = new RooRealVar("k_V3ProbNNk","K^{-} ProbNNk",-1.0e10,1.0e10);
  RooRealVar* pi1_V3ProbNNpi = new RooRealVar("pi1_V3ProbNNpi","#pi^{+} ProbNNk",-1.0e10,1.0e10);
  RooRealVar* pi2_V3ProbNNpi = new RooRealVar("pi2_V3ProbNNpi","#pi^{-} ProbNNk",-1.0e10,1.0e10);


  RooRealVar* k_PX = new RooRealVar("k_PX","K^{-} px",-1.0e10,1.0e10);
  RooRealVar* k_PY = new RooRealVar("k_PY","K^{-} py",-1.0e10,1.0e10);
  RooRealVar* k_PZ = new RooRealVar("k_PZ","K^{-} pz",-1.0e10,1.0e10);
  RooRealVar* k_PE = new RooRealVar("k_PE","K^{-} pE",-1.0e10,1.0e10);
  RooRealVar* pi1_PX = new RooRealVar("pi1_PX","#pi^{+} px",-1.0e10,1.0e10);
  RooRealVar* pi1_PY = new RooRealVar("pi1_PY","#pi^{+} py",-1.0e10,1.0e10);
  RooRealVar* pi1_PZ = new RooRealVar("pi1_PZ","#pi^{+} pz",-1.0e10,1.0e10);
  RooRealVar* pi1_PE = new RooRealVar("pi1_PE","#pi^{+} pE",-1.0e10,1.0e10);
  RooRealVar* pi2_PX = new RooRealVar("pi2_PX","#pi^{+} px",-1.0e10,1.0e10);
  RooRealVar* pi2_PY = new RooRealVar("pi2_PY","#pi^{+} py",-1.0e10,1.0e10);
  RooRealVar* pi2_PZ = new RooRealVar("pi2_PZ","#pi^{+} pz",-1.0e10,1.0e10);
  RooRealVar* pi2_PE = new RooRealVar("pi2_PE","#pi^{+} pE",-1.0e10,1.0e10);


  RooRealVar* nTracks = new RooRealVar("nTracks","nTracks",-1.0e10,1.0e10);
  RooRealVar* BDTG = new RooRealVar("BDTG","BDTG",-1.0e10,1.0e10);

  RooArgSet args;
  args.add(*Xb_ENDVERTEX_CHI2);
  args.add(*Xb_ENDVERTEX_NDOF);
  args.add(*mvar[i]);
  args.add(*Xc_M);
  args.add(*Xb_ENDVERTEX_X);
  args.add(*Xb_ENDVERTEX_Y);
  args.add(*Xb_OWNPV_X);
  args.add(*Xb_OWNPV_Y);
  args.add(*Xb_LOKI_DTF_CHI2NDOF);
  args.add(*Xb_IPCHI2_OWNPV);
  args.add(*Xb_DIRA_OWNPV);
  args.add(*Xb_PT);
  args.add(*Jpsi_IPCHI2_OWNPV);
  args.add(*Jpsi_PT);
  args.add(*Xc_PT);
  args.add(*Xc_IPCHI2_OWNPV);
  args.add(*mup_IPCHI2_OWNPV);
  args.add(*mum_IPCHI2_OWNPV);
  args.add(*k_IPCHI2_OWNPV);
  args.add(*pi1_IPCHI2_OWNPV);
  args.add(*pi2_IPCHI2_OWNPV);
  args.add(*Xc_ENDVERTEX_CHI2);
  args.add(*k_P);
  args.add(*pi1_P);
  args.add(*pi2_P);
  args.add(*k_V3ProbNNk);
  args.add(*pi1_V3ProbNNpi);
  args.add(*pi2_V3ProbNNpi);
  args.add(*Xc_TAU);
  args.add(*nTracks);
  args.add(*k_PX);
  args.add(*k_PY);
  args.add(*k_PZ);
  args.add(*k_PE);
  args.add(*pi1_PX);  
  args.add(*pi1_PY);  
  args.add(*pi1_PZ);  
  args.add(*pi1_PE);  
  args.add(*pi2_PX);  
  args.add(*pi2_PY);  
  args.add(*pi2_PZ);  
  args.add(*pi2_PE);  

  if(withBDT) args.add(*BDTG);

  //----------------------------------------------
  // Variables which are functions of the raw ones
  //----------------------------------------------
  RooFormulaVar* Rfd = new RooFormulaVar("Rfd","log(Radial Flight Distance)","log(sqrt(pow(@0-@1,2)+pow(@2-@3,2)))",
                                        RooArgList(*Xb_ENDVERTEX_X,*Xb_OWNPV_X,*Xb_ENDVERTEX_Y,*Xb_OWNPV_Y)); // radial flight distance
  RooFormulaVar* XbVtxChisq = new RooFormulaVar("XbVtxChisq","X_{b} #chi^{2}_{vtx}","log(@0/@1)",RooArgList(*Xb_ENDVERTEX_CHI2,*Xb_ENDVERTEX_NDOF));
  RooFormulaVar* DTFChisq = new RooFormulaVar("DTFChisq","X_{b} #chi^{2}_{DTF}","log(@0)",RooArgList(*Xb_LOKI_DTF_CHI2NDOF));
  RooFormulaVar* XbIPChisq = new RooFormulaVar("XbIPChisq","X_{b} #chi^{2}_{IP}","log(@0)",RooArgList(*Xb_IPCHI2_OWNPV));
  RooFormulaVar* XcIPChisq = new RooFormulaVar("XcIPChisq","X_{c} #chi^{2}_{IP}","log(@0)",RooArgList(*Xc_IPCHI2_OWNPV));
  RooFormulaVar* JpsiIPChisq = new RooFormulaVar("JpsiIPChisq","J/#psi #chi^{2}_{IP}","log(@0)",RooArgList(*Jpsi_IPCHI2_OWNPV));  
  RooFormulaVar* kIPChisq = new RooFormulaVar("kIPChisq","K^{-} #chi^{2}_{IP}","log(@0)",RooArgList(*k_IPCHI2_OWNPV));
  RooFormulaVar* pi1IPChisq = new RooFormulaVar("pi1IPChisq","#pi^{+} #chi^{2}_{IP}","log(@0)",RooArgList(*pi1_IPCHI2_OWNPV));
  RooFormulaVar* pi2IPChisq = new RooFormulaVar("pi2IPChisq","#pi^{-} #chi^{2}_{IP}","log(@0)",RooArgList(*pi2_IPCHI2_OWNPV));
  RooFormulaVar* mupIPChisq = new RooFormulaVar("mupIPChisq","#mu^{+} #chi^{2}_{IP}","log(@0)",RooArgList(*mup_IPCHI2_OWNPV));
  RooFormulaVar* mumIPChisq = new RooFormulaVar("mumIPChisq","#mu^{-} #chi^{2}_{IP}","log(@0)",RooArgList(*mum_IPCHI2_OWNPV));
  RooFormulaVar* XbPT = new RooFormulaVar("XbPT","X_{b} p_{T}","log(@0)",RooArgList(*Xb_PT));
  RooFormulaVar* XcPT = new RooFormulaVar("XcPT","X_{c} p_{T}","log(@0)",RooArgList(*Xc_PT));
  RooFormulaVar* Xc2JpsiPT = new RooFormulaVar("Xc2JpsiPT","X_{c}/J#psi p_{T} ratio","log(@0/@1)",RooArgList(*Xc_PT,*Jpsi_PT));
  RooFormulaVar* XcVtxChisq = new RooFormulaVar("XcVtxChisq","X_{c} #chi^{2}_{vtx}","log(@0)",RooArgList(*Xc_ENDVERTEX_CHI2));
  RooFormulaVar* kP = new RooFormulaVar("kP","K^{-} p","log(@0)",RooArgList(*k_P));
  RooFormulaVar* pi1P = new RooFormulaVar("pi1P","#pi^{+} p","log(@0)",RooArgList(*pi1_P));
  RooFormulaVar* pi2P = new RooFormulaVar("pi2P","#pi^{-} p","log(@0)",RooArgList(*pi2_P));
  RooFormulaVar* kProbNNk = new RooFormulaVar("kProbNNk","K^{-} ProbNNk","1-sqrt(1-@0)",RooArgList(*k_V3ProbNNk));
  RooFormulaVar* pi1ProbNNpi = new RooFormulaVar("pi1ProbNNpi","#pi^{+} ProbNNpi","1-sqrt(1-@0)",RooArgList(*pi1_V3ProbNNpi));
  RooFormulaVar* pi2ProbNNpi = new RooFormulaVar("pi2ProbNNpi","#pi^{-} ProbNNpi","1-sqrt(1-@0)",RooArgList(*pi2_V3ProbNNpi));
  RooFormulaVar* XcTAU = new RooFormulaVar("XcTAU","X_{c} TAU","1000*(@0)",RooArgList(*Xc_TAU));
  RooFormulaVar* mKpi = new RooFormulaVar("mKpi","M(K^{-}#pi^{+})","sqrt(pow(@0+@1,2)-pow(@2+@3,2)-pow(@4+@5,2)-pow(@6+@7,2))",
                                            RooArgList(*k_PE,*pi1_PE,*k_PX,*pi1_PX,*k_PY,*pi1_PY,*k_PZ,*pi1_PZ));
  RooFormulaVar* mpipi = new RooFormulaVar("mpipi","M(K^{-}#pi^{+})","sqrt(pow(@0+@1,2)-pow(@2+@3,2)-pow(@4+@5,2)-pow(@6+@7,2))",
                                            RooArgList(*pi2_PE,*pi1_PE,*pi2_PX,*pi1_PX,*pi2_PY,*pi1_PY,*pi2_PZ,*pi1_PZ));

  RooDataSet* data_red = new RooDataSet("data_red","dataset with reduced vars",treeNew1,args);
  RooRealVar* RfdVar =  (RooRealVar*) data_red->addColumn(*Rfd);  
  RooRealVar* DTFChisqVar =  (RooRealVar*) data_red->addColumn(*DTFChisq);  
  RooRealVar* XbIPChisqVar =  (RooRealVar*) data_red->addColumn(*XbIPChisq);  
  RooRealVar* XcIPChisqVar =  (RooRealVar*) data_red->addColumn(*XcIPChisq);  
  RooRealVar* JpsiIPChisqVar =  (RooRealVar*) data_red->addColumn(*JpsiIPChisq);  
  RooRealVar* kIPChisqVar =  (RooRealVar*) data_red->addColumn(*kIPChisq);  
  RooRealVar* pi1IPChisqVar =  (RooRealVar*) data_red->addColumn(*pi1IPChisq);  
  RooRealVar* pi2IPChisqVar =  (RooRealVar*) data_red->addColumn(*pi2IPChisq);  
  RooRealVar* mupIPChisqVar =  (RooRealVar*) data_red->addColumn(*mupIPChisq);  
  RooRealVar* mumIPChisqVar =  (RooRealVar*) data_red->addColumn(*mumIPChisq);  
  RooRealVar* XbPTVar =  (RooRealVar*) data_red->addColumn(*XbPT);  
  RooRealVar* XcPTVar =  (RooRealVar*) data_red->addColumn(*XcPT);  
  RooRealVar* Xc2JpsiPTVar =  (RooRealVar*) data_red->addColumn(*Xc2JpsiPT);  
  RooRealVar* XbVtxChisqVar =  (RooRealVar*) data_red->addColumn(*XbVtxChisq);  
  RooRealVar* XcVtxChisqVar =  (RooRealVar*) data_red->addColumn(*XcVtxChisq);  
  RooRealVar* kPVar =  (RooRealVar*) data_red->addColumn(*kP);  
  RooRealVar* pi1PVar =  (RooRealVar*) data_red->addColumn(*pi1P);  
  RooRealVar* pi2PVar =  (RooRealVar*) data_red->addColumn(*pi2P);  
  RooRealVar* kProbNNkVar =  (RooRealVar*) data_red->addColumn(*kProbNNk);  
  RooRealVar* pi1ProbNNpiVar =  (RooRealVar*) data_red->addColumn(*pi1ProbNNpi);  
  RooRealVar* pi2ProbNNpiVar =  (RooRealVar*) data_red->addColumn(*pi2ProbNNpi);  
  RooRealVar* XcTAUVar =  (RooRealVar*) data_red->addColumn(*XcTAU);  
  RooRealVar* mKpiVar =  (RooRealVar*) data_red->addColumn(*mKpi);  
  RooRealVar* mpipiVar =  (RooRealVar*) data_red->addColumn(*mpipi);  

  TString wsig = "nsig0_sw";

  RooArgSet *myVars1;
  myVars1 = pdf[i]->getParameters(*rdh[i]) ;
  myVars1->Print("v") ;
  myVars1->setAttribAll("Constant",kTRUE) ;
  nsig[i]->setConstant(kFALSE);
  ncomb[i]->setConstant(kFALSE);
  pdf[i]->fitTo(*rdh[i],Extended(),Hesse(kTRUE));
  //--------------
  // Get sWeights
  //--------------
  RooStats::SPlot* sDataA1 = new RooStats::SPlot("sDataA1","An SPlot", *data_red, pdf[i] , RooArgList(*nsig[i],*ncomb[i]) );

  data_red->Print("v") ; 
  gStyle->SetOptStat(011000);
  //--------------------------
  // create weighted data set 
  //--------------------------
  RooDataSet * dataw_signal = new RooDataSet(data_red->GetName(),data_red->GetTitle(),data_red,*data_red->get(),0,wsig) ;
  dataw_signal->Print("v") ; 
  //-------------------------------------------
  // Project out weighted data onto histograms
  //-------------------------------------------
  TH1F* XcMass = dataw_signal->createHistogram("XcMass",*Xc_M,Binning(48,1000,2200)); 
  TH1F* RfdHist = dataw_signal->createHistogram("RfdHist",*RfdVar,Binning(45,-4,4)); 
  TH1F* DTFChisqHist = dataw_signal->createHistogram("DTFChisqHist",*DTFChisqVar,Binning(50,-2.5,2.5)); 
  TH1F* XbIPChisqHist = dataw_signal->createHistogram("XbIPChisqHist",*XbIPChisqVar,Binning(50,-6,4)); 
  TH1F* XcIPChisqHist = dataw_signal->createHistogram("XcIPChisqHist",*XcIPChisqVar,Binning(80,-4,12)); 
  TH1F* JpsiIPChisqHist = dataw_signal->createHistogram("JpsiIPChisqHist",*JpsiIPChisqVar,Binning(80,-6,10)); 
  TH1F* kIPChisqHist = dataw_signal->createHistogram("kIPChisqHist",*kIPChisqVar,Binning(45,1.5,10.5)); 
  TH1F* pi1IPChisqHist = dataw_signal->createHistogram("pi1IPChisqHist",*pi1IPChisqVar,Binning(45,1.5,10.5)); 
  TH1F* pi2IPChisqHist = dataw_signal->createHistogram("pi2IPChisqHist",*pi2IPChisqVar,Binning(45,1.5,10.5)); 
  TH1F* mupIPChisqHist = dataw_signal->createHistogram("mupIPChisqHist",*mupIPChisqVar,Binning(70,-2,12)); 
  TH1F* mumIPChisqHist = dataw_signal->createHistogram("mumIPChisqHist",*mumIPChisqVar,Binning(70,-2,12)); 
  TH1F* XbPTHist = dataw_signal->createHistogram("XbPTHist",*XbPTVar,Binning(60,5,11)); 
  TH1F* XcPTHist = dataw_signal->createHistogram("XcPTHist",*XcPTVar,Binning(60,5,11)); 
  TH1F* Xc2JpsiPTHist = dataw_signal->createHistogram("Xc2JpsiPTHist",*Xc2JpsiPTVar,Binning(70,-3.5,3.5)); 
  TH1F* XcVtxChisqHist = dataw_signal->createHistogram("XcVtxChisqHist",*XcVtxChisqVar,Binning(80,-4,4)); 
  TH1F* XbVtxChisqHist = dataw_signal->createHistogram("XbVtxChisqHist",*XbVtxChisqVar,Binning(90,-5,4)); 
  TH1F* kPHist = dataw_signal->createHistogram("kPHist",*kPVar,Binning(60,7,13)); 
  TH1F* pi1PHist = dataw_signal->createHistogram("pi1PHist",*pi1PVar,Binning(60,7,13));
  TH1F* pi2PHist = dataw_signal->createHistogram("pi2PHist",*pi2PVar,Binning(60,7,13)); 
  TH1F* kProbNNkHist = dataw_signal->createHistogram("kProbNNkHist",*kProbNNkVar,Binning(50,0,1)); 
  TH1F* pi1ProbNNpiHist = dataw_signal->createHistogram("pi1ProbNNpiHist",*pi1ProbNNpiVar,Binning(50,0,1)); 
  TH1F* pi2ProbNNpiHist = dataw_signal->createHistogram("pi2ProbNNpiHist",*pi2ProbNNpiVar,Binning(50,0,1)); 
  TH1F* XcTAUHist = dataw_signal->createHistogram("XcTAUHist",*XcTAUVar,Binning(100,-1,1)); 
  TH1F* nTracksHist = dataw_signal->createHistogram("nTracksHist",*nTracks,Binning(100,0,500)); 
  TH1F* mKpiHist = dataw_signal->createHistogram("mKpiHist",*mKpiVar,Binning(70,600,2000));
  TH1F* mpipiHist = dataw_signal->createHistogram("mpipiHist",*mpipiVar,Binning(50,200,1700));
  if(withBDT) TH1F* BDTGHist = dataw_signal->createHistogram("BDTGHist",*BDTG,Binning(100,-1,1)); 

  addGraphics(XcMass, "K^{-}#pi^{+}#pi^{-} mass [MeV/#it{c}^{2}]");
  addGraphics(RfdHist, "log(Radial distance) of b hadron");
  addGraphics(DTFChisqHist,"log(#chi^{2}_{DTF})");
  addGraphics(XbIPChisqHist,"X_{b} log(#chi^{2}_{IP})");
  addGraphics(XcIPChisqHist,"X_{c} log(#chi^{2}_{IP})");
  addGraphics(JpsiIPChisqHist,"J/#psi log(#chi^{2}_{IP})");
  addGraphics(kIPChisqHist,"K^{-} log(#chi^{2}_{IP})");
  addGraphics(pi1IPChisqHist,"#pi^{+} log(#chi^{2}_{IP})");
  addGraphics(pi2IPChisqHist,"#pi^{-} log(#chi^{2}_{IP})");
  addGraphics(mupIPChisqHist,"#mu^{+} log(#chi^{2}_{IP})");
  addGraphics(mumIPChisqHist,"#mu^{-} log(#chi^{2}_{IP})");
  addGraphics(XbPTHist,"X_{b} log(p_{T})");
  addGraphics(XcPTHist,"X_{c} log(p_{T})");
  addGraphics(Xc2JpsiPTHist,"log( p_{T}^{X_{c}} / p_{T}^{J/#psi} )");
  addGraphics(XcVtxChisqHist,"X_{c} log((#chi^{2}_{vtx})");
  addGraphics(XbVtxChisqHist,"X_{b} log((#chi^{2}_{vtx})");
  addGraphics(kPHist,"K^{-} log(p)");
  addGraphics(pi1PHist,"#pi^{+} log(p)");
  addGraphics(pi2PHist,"#pi^{-} log(p)");
  addGraphics(kProbNNkHist,"K^{-} 1-#sqrt{1-ProbNNk}");
  addGraphics(pi1ProbNNpiHist,"#pi^{+} 1-#sqrt{1-ProbNNpi}");
  addGraphics(pi2ProbNNpiHist,"#pi^{-} 1-#sqrt{1-ProbNNpi}");
  addGraphics(XcTAUHist,"Decay time of K^{-}#pi^{+}#pi^{-} vertex");
  addGraphics(nTracksHist,"# Tracks");
  addGraphics(mKpiHist,"m(K^{-}#pi^{+})");
  addGraphics(mpipiHist,"m(#pi^{-}#pi^{+})");
  if(withBDT) addGraphics(BDTGHist,"BDTG output");

  int ii = 1;
  TCanvas *cSW = new TCanvas("cSW","sWeight plots",1800,1000);
  cSW->Divide(6,5);
  cSW->cd(ii++);
  RfdHist->Draw();
  cSW->cd(ii++);
  DTFChisqHist->Draw();
  cSW->cd(ii++);
  XbIPChisqHist->Draw();
  cSW->cd(ii++);
  XcIPChisqHist->Draw();
  cSW->cd(ii++);
  JpsiIPChisqHist->Draw();
  cSW->cd(ii++);
  kIPChisqHist->Draw();
  cSW->cd(ii++);
  pi1IPChisqHist->Draw();
  cSW->cd(ii++);
  pi2IPChisqHist->Draw();
  cSW->cd(ii++);
  mupIPChisqHist->Draw();
  cSW->cd(ii++);
  mumIPChisqHist->Draw();
  cSW->cd(ii++);
  XbPTHist->Draw();
  cSW->cd(ii++);
  XcPTHist->Draw();
  cSW->cd(ii++);
  Xc2JpsiPTHist->Draw();
  cSW->cd(ii++);
  XcVtxChisqHist->Draw();
  cSW->cd(ii++);
  XbVtxChisqHist->Draw();
  cSW->cd(ii++);
  kPHist->Draw();
  cSW->cd(ii++);
  pi1PHist->Draw();
  cSW->cd(ii++);
  pi2PHist->Draw();
  cSW->cd(ii++);
  kProbNNkHist->Draw();
  cSW->cd(ii++);
  pi1ProbNNpiHist->Draw();
  cSW->cd(ii++);
  pi2ProbNNpiHist->Draw();
  cSW->cd(ii++);
  XcTAUHist->Draw();
  cSW->cd(ii++);
  XcMass->Draw();
  cSW->cd(ii++);
  mKpiHist->Draw();
  cSW->cd(ii++);
  mpipiHist->Draw();

  cSW->cd(ii++);
  nTracksHist->Draw();
  if(withBDT){
    cSW->cd(ii++);
    BDTGHist->Draw();
  }
  
  fout->Write();


  return;
  
  
}


