
using namespace std;
using namespace RooFit;

TString lt;



TCanvas* makeRooPlot(RooAbsPdf* pdf, RooAbsData* rdh, RooRealVar *mvar, int mode, RooRealVar* nS,
                     TString tag="def",double mlow=2420, double mhi=2520, int nbin=50){
  
  TLatex *myLatex = new TLatex();
  myLatex->SetTextFont(42); myLatex->SetTextColor(1); myLatex->SetTextAlign(12); myLatex->SetNDC(kTRUE); myLatex->SetTextSize(0.045);
  double xt = 0.6;
  int bw = (mhi-mlow)/nbin;

  tag = tag.ReplaceAll("#","");
  tag = tag.ReplaceAll("^{0}","z");
  tag = tag.ReplaceAll("^{+}","");
  tag = tag.ReplaceAll("^{-}","");
  tag = tag.ReplaceAll("_{c}","c");
  

  TString comps = Form("gauss%d",mode);
  TString titleY = Form("Candidates / [%d MeV/#it{c}^{2}]",bw);


  if(mode==0){
    TString titleX = "D^{0} p #pi mass [MeV/#it{c}^{2}]";
  }else if(mode==1 || mode==3 || mode==11 || mode==13){
    TString titleX = "pK^{#font[122]{-}}#pi^{+} mass [MeV/#it{c}^{2}]";
     TString titleX = "J/#psi K^{#font[122]{-}}#pi^{+}#pi^{#font[122]{-}}mass [MeV/#it{c}^{2}]";
  }else if(mode==2 || mode==5 || mode==12 || mode==15){
    TString titleX = "pK^{#font[122]{-}}K^{#font[122]{-}}#pi^{+} mass [MeV/#it{c}^{2}]";
  }else if(mode==4 || mode==14){
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
  h->GetXaxis()->SetTitleSize(0.045);  
  h->GetYaxis()->SetTitleSize(0.045);
  h->GetXaxis()->SetLabelSize(0.035);  
  h->GetYaxis()->SetLabelSize(0.035);  
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
  frame->SetTitleOffset(1.05,"X");
  frame->SetTitleOffset(1.25,"Y");
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


TChain* getChain(TString name){

  TChain *ch = new TChain(name,"");
  ch->Add("/data1/zli59/D0ppi/"+name+"/mytree");
//  ch->Add("/data1/zli59/D0ppi/"+name+"/MyLb0/mytree");
//  ch->Add("/data1/zli59/D0ppi/"+name+"/MyLb0/mytree");
//  ch->Add("/data1/zli59/D0ppi/"+name+"/MyLb0/mytree");
  
  return ch;    

}



void plots(){

  gStyle->SetStatH(0.28);
  
  bool withBDT = false;

  TLatex *myLatex = new TLatex();
  myLatex->SetTextFont(42); myLatex->SetTextColor(1); myLatex->SetTextAlign(12); myLatex->SetNDC(kTRUE); myLatex->SetTextSize(0.045);
   double xt = 0.6;

  TCanvas *c = new TCanvas("c","Plot",800,800);

  TFile *fl = new TFile("/data1/zli59/D0ppi/d2011.root");
  TTree* l = (TTree*)fl->Get("GetIntegratedLuminosity/LumiTuple");
  TH1F *lum = new TH1F("lum","Lumi",5,0,5);
  l->Draw("0.5>>lum","IntegratedLuminosity");
  float lumi = lum->GetBinContent(1);    
  lt = Form("Lum =  %4.0f pb^{-1}",lumi);
  TFile *f = new TFile("/data1/zli59/D0ppi/X2D0ppi.piKppi.rs.wMVA.test.root");
  TTree* tree[20];
  tree[0] = (TTree*)f->Get("mytree");
  

  
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
  TString modes[20] = {"#Xi_{bc}","J/#psiK#pi#pi", "#Xi_{c}^{0}", "#Lambda_{c}^{+}", "D^{+}", "#Omega_{c}^{0}",  
                      "", "","","","",
                      "#Xi_{c}^{+}", "#Xi_{c}^{0}", "#Lambda_{c}^{+}", "D^{+}", "#Omega_{c}^{0}", 
                      "", "","",""};
  
  TCanvas *ccc = new TCanvas("ccc","D",1200,600);
  
  int i=0;
  
  float masses[20] = {5620, 5280, 2472, 2288, 1871, 2696, 0,0,0,0,0, 2469, 2472, 2288, 1871, 2696, 0,0,0,0 };  
  double mlow[20] = {5420, 5150, 2420, 2240, 1820, 2645, 0,0,0,0,0, 2420, 2420, 2240, 1820,2645, 0,0,0,0 };
  double mhi[20]  = {5800, 5450, 2520, 2330, 1920, 2745, 0,0,0,0,0, 2520, 2520, 2330, 1920, 2745, 0,0,0,0};  
  double bw[20] = {5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,};
  int nbins[20];
  for(int j=0; j<20; j++){nbins[j] = (mhi[j]-mlow[j])/bw[j];}
  TH1F *h[20];


  TCut cuts[20];
  cuts[0] = "abs(D_M-1864)<30&&K_MC12TuneV3_ProbNNk>0.3&&Rp_MC12TuneV3_ProbNNp>0.3&&Xb_DIRA_OWNPV>0.99995&&Xb_IPCHI2_OWNPV<16&&R_M<3400&&pi_MC12TuneV3_ProbNNpi>0.05&&Rpi_MC12TuneV3_ProbNNpi>0.05&&D_TAU>0";
  TString mRangeCut = Form("Xb_M>%4.0f&&Xb_M<%4.0f",mlow[0],mhi[0]);
  cuts[0] = cuts[0] && mRangeCut;
  if(!withBDT)
    {
      cuts[0] = cuts[0] && "BDTG>-0.5";
    }

  

  TCanvas *cc[20];
  
  double sigma[20]; for(int j=0;j<20;j++){sigma[j] = 16.0;}

  RooRealVar* cbn = new RooRealVar("cbn","",10.);
  RooRealVar* cba = new RooRealVar("cba","",1.8,0,5);
  RooRealVar *moff = new RooRealVar("moff","Offset",3097);

  //------------------------------------
  // Set up fit PDF, define fit function
  //------------------------------------
  mvar[i] = new RooRealVar("Xb_M","Xb_M",mlow[i],mhi[i]);
  h[i] = new TH1F(Form("h%d",i),"Mass",nbins[i],mlow[i],mhi[i]);
  TString histExp = Form("Xb_M>>h%d",i);
  tree[i]->Draw(histExp,cuts[i]);
  
  mg[i] = new RooRealVar(Form("mg%d",i),"mean",masses[i],masses[i]-10,masses[i]+10);
  sg[i] = new RooRealVar(Form("sg%d",i),"width",sigma[i],2,25);
  sg2[i] = new RooRealVar(Form("sg2%d",i),"width",20,5,50);
  fr[i] = new RooRealVar(Form("fr%d",i),"fraction",0.8,0.3,1.0);

  CBA[i] = new RooCBShape(Form("CBA%d",i),"", *mvar[i], *mg[i], *sg[i], *cba, *cbn);

  //-----BackGround Fix for X2D0ppi------------------------------------
  RooRealVar bgm("meanofBG","meanofBG",5450,5400,5500);
  RooRealVar bgs("sigmaofBG","sigmaofBG",16,2,50);
  gaussA[i] = new RooGaussian(Form("gaussA%d",i),"BackgroundFix",*mvar[i],bgm,bgs);
  //gauss[i] = new RooAddPdf(Form("gauss%d",i),"Signal",RooArgList(*gaussA[i],*gaussB[i]),RooArgList(*fr[i]));
  RooRealVar frac ("frac","frac",0.1,0.05,1.0);
  //-----------------------------------------


  gaussB[i] = new RooGaussian(Form("gaussB%d",i),"Signal",*mvar[i],*mg[i],*sg2[i]);
  //  gauss[i] = new RooAddPdf(Form("gauss%d",i),"Signal",RooArgList(*CBA[i],*gaussB[i]),RooArgList(*fr[i]));
  gauss[i] = new RooAddPdf(Form("gauss%d",i),"Signal",RooArgList(*CBA[i],*gaussA[i],*gaussB[i]),RooArgList(*fr[i],frac));


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
  

  bool do_splot = true;
  
  if(!do_splot) return;
  
  TString fileName = "test.root";
  TFile *fout = new TFile(fileName,"RECREATE");

  TTree* treeNew1 = tree[i]->CopyTree(cuts[i]);

  //--------------------------------------------
  // Variables that are needed in the sWeighting
  //--------------------------------------------
  RooRealVar* D_M = new RooRealVar("D_M","D mass",-1.0e10,1.0e10);
  RooRealVar* Xb_ENDVERTEX_X = new RooRealVar("Xb_ENDVERTEX_X","Xb pos",-1.0e10,1.0e10);
  RooRealVar* Xb_ENDVERTEX_Y = new RooRealVar("Xb_ENDVERTEX_Y","Xb pos",-1.0e10,1.0e10);
  RooRealVar* Xb_OWNPV_X = new RooRealVar("Xb_OWNPV_X","Xb PV pos",-1.0e10,1.0e10);
  RooRealVar* Xb_OWNPV_Y = new RooRealVar("Xb_OWNPV_Y","Xb PV pos",-1.0e10,1.0e10);
  RooRealVar* Xb_LOKI_CHI2NDOF_D0Constr = new RooRealVar("Xb_LOKI_CHI2NDOF_D0Constr","Xb DOF chisq",-1.0e10,1.0e10);

  RooRealVar* Xb_IPCHI2_OWNPV = new RooRealVar("Xb_IPCHI2_OWNPV","Xb IP chisq",-1.0e10,1.0e10);
  RooRealVar* Xb_DIRA_OWNPV = new RooRealVar("Xb_DIRA_OWNPV","Xb DIRA",-1.0e10,1.0e10);
  RooRealVar* Xb_PT = new RooRealVar("Xb_PT","Xb PT",-1.0e10,1.0e10);
//  RooRealVar* Jpsi_IPCHI2_OWNPV = new RooRealVar("Jpsi_IPCHI2_OWNPV","Jpsi IP chisq",-1.0e10,1.0e10);
//  RooRealVar* Jpsi_PT = new RooRealVar("Jpsi_PT","Jpsi PT",-1.0e10,1.0e10);
  RooRealVar* Rp_PT = new RooRealVar("Rp_PT","Rp PT",-1.0e10,1.0e10);
  RooRealVar* D_IPCHI2_OWNPV = new RooRealVar("D_IPCHI2_OWNPV","D IP chisq",-1.0e10,1.0e10);
  RooRealVar* D_TAU = new RooRealVar("D_TAU","R TAU",-1.0e10,1.0e10);
//  RooRealVar* mup_IPCHI2_OWNPV = new RooRealVar("mup_IPCHI2_OWNPV","mup IP chisq",-1.0e10,1.0e10);
//  RooRealVar* mum_IPCHI2_OWNPV = new RooRealVar("mum_IPCHI2_OWNPV","mum IP chisq",-1.0e10,1.0e10);
  RooRealVar* K_IPCHI2_OWNPV = new RooRealVar("K_IPCHI2_OWNPV","k IP chisq",-1.0e10,1.0e10);
  RooRealVar* pi_IPCHI2_OWNPV = new RooRealVar("pi_IPCHI2_OWNPV","pi IP chisq",-1.0e10,1.0e10);
  RooRealVar* Rpi_IPCHI2_OWNPV = new RooRealVar("Rpi_IPCHI2_OWNPV","Rpi IP chisq",-1.0e10,1.0e10);
  RooRealVar* D_ENDVERTEX_CHI2 = new RooRealVar("D_ENDVERTEX_CHI2","D Vertex chisq",-1.0e10,1.0e10);
  RooRealVar* K_P = new RooRealVar("K_P","K^{-} momentum",-1.0e10,1.0e10);
  RooRealVar* Rp_P = new RooRealVar("Rp_P","Rp momentum",-1.0e10,1.0e10);
  RooRealVar* pi_P = new RooRealVar("pi_P","#pi momentum",-1.0e10,1.0e10);
  RooRealVar* Rpi_P = new RooRealVar("Rpi_P","#Rpi momentum",-1.0e10,1.0e10);
  RooRealVar* K_ProbNNk = new RooRealVar("K_MC12TuneV3_ProbNNk","K^{-} ProbNNk",-1.0e10,1.0e10);
  RooRealVar* pi_MC12TuneV3_ProbNNpi = new RooRealVar("pi_MC12TuneV3_ProbNNpi","#pi ProbNNpi",-1.0e10,1.0e10);
  RooRealVar* Rpi_MC12TuneV3_ProbNNpi = new RooRealVar("Rpi_MC12TuneV3_ProbNNpi","#Rpi ProbNNpi",-1.0e10,1.0e10);
  RooRealVar* Rp_MC12TuneV3_ProbNNp = new RooRealVar("Rp_MC12TuneV3_ProbNNp","#Rp ProbNNp",-1.0e10,1.0e10);
  RooRealVar* nTracks = new RooRealVar("nTracks","nTracks",-1.0e10,1.0e10);
  RooRealVar* BDTG = new RooRealVar("BDTG","BDTG",-1.0e10,1.0e10);

  //----------------------------reWeight--------------------------------------------
  RooRealVar* R_M = new RooRealVar("R_M","p #pi Mass",-1.0e10,1.0e10);
  RooRealVar* D_PX = new RooRealVar("D_PX","D0 PX",-1.0e10,1.0e10);
  RooRealVar* D_PY = new RooRealVar("D_PY","D0 PY",-1.0e10,1.0e10);
  RooRealVar* D_PZ = new RooRealVar("D_PZ","D0 PZ",-1.0e10,1.0e10);
  RooRealVar* D_PE = new RooRealVar("D_PE","D0 PE",-1.0e10,1.0e10);
  RooRealVar* Rp_PX = new RooRealVar("Rp_PX","p^{+} PX",-1.0e10,1.0e10);
  RooRealVar* Rp_PY = new RooRealVar("Rp_PY","p^{+} PY",-1.0e10,1.0e10);
  RooRealVar* Rp_PZ = new RooRealVar("Rp_PZ","p^{+} PZ",-1.0e10,1.0e10);
  RooRealVar* Rp_PE = new RooRealVar("Rp_PE","p^{+} PE",-1.0e10,1.0e10);
  //----------------------------reWeight--------------------------------------------


  RooArgSet args;
  args.add(*mvar[i]);
  args.add(*D_M);
  args.add(*Xb_ENDVERTEX_X);
  args.add(*Xb_ENDVERTEX_Y);
  args.add(*Xb_OWNPV_X);
  args.add(*Xb_OWNPV_Y);
  args.add(*Xb_LOKI_CHI2NDOF_D0Constr);
  args.add(*Xb_IPCHI2_OWNPV);
  args.add(*Xb_DIRA_OWNPV);
  args.add(*Xb_PT);
//  args.add(*Jpsi_IPCHI2_OWNPV);
//  args.add(*Jpsi_PT);
  args.add(*Rp_PT);
  args.add(*D_IPCHI2_OWNPV);
  //  args.add(*mup_IPCHI2_OWNPV);
  //  args.add(*mum_IPCHI2_OWNPV);
  args.add(*K_IPCHI2_OWNPV);
  args.add(*pi_IPCHI2_OWNPV);
  args.add(*Rpi_IPCHI2_OWNPV);
  args.add(*D_ENDVERTEX_CHI2);
  args.add(*K_P);
  args.add(*Rp_P);
  args.add(*pi_P);
  args.add(*Rpi_P);
  args.add(*K_ProbNNk);
  args.add(*pi_MC12TuneV3_ProbNNpi);
  args.add(*Rpi_MC12TuneV3_ProbNNpi);
  args.add(*Rp_MC12TuneV3_ProbNNp);
  args.add(*D_TAU);
  args.add(*nTracks);
  if(withBDT)
    {
      args.add(*BDTG);
    }
  //----------------------------reWeight--------------------------------------------
  args.add(*R_M);
  args.add(*D_PX);
  args.add(*D_PY);
  args.add(*D_PZ);
  args.add(*D_PE);
  args.add(*Rp_PX);
  args.add(*Rp_PY);
  args.add(*Rp_PZ);
  args.add(*Rp_PE);
  //----------------------------reWeight--------------------------------------------




  //----------------------------------------------
  // Variables which are functions of the raw ones
  //----------------------------------------------
  RooFormulaVar* Rfd = new RooFormulaVar("Rfd","log(Radial Flight Distance)","log(sqrt(pow(@0-@1,2)+pow(@2-@3,2)))",
                                        RooArgList(*Xb_ENDVERTEX_X,*Xb_OWNPV_X,*Xb_ENDVERTEX_Y,*Xb_OWNPV_Y)); // radial flight distance
  RooFormulaVar* DOFChisq = new RooFormulaVar("DOFChisq","X_{b} #chi^{2}_{DOF}","log(@0)",RooArgList(*Xb_LOKI_CHI2NDOF_D0Constr));
  RooFormulaVar* DMass = new RooFormulaVar("DMass","DMass","@0",RooArgList(*D_M));
  RooFormulaVar* XbIPChisq = new RooFormulaVar("XbIPChisq","X_{b} #chi^{2}_{IP}","log(@0)",RooArgList(*Xb_IPCHI2_OWNPV));
  RooFormulaVar* DIPChisq = new RooFormulaVar("DIPChisq","D #chi^{2}_{IP}","log(@0)",RooArgList(*D_IPCHI2_OWNPV));
//  RooFormulaVar* JpsiIPChisq = new RooFormulaVar("JpsiIPChisq","J/#psi #chi^{2}_{IP}","log(@0)",RooArgList(*Jpsi_IPCHI2_OWNPV));  
  RooFormulaVar* KIPChisq = new RooFormulaVar("KIPChisq","K^{-} #chi^{2}_{IP}","log(@0)",RooArgList(*K_IPCHI2_OWNPV));
  RooFormulaVar* piIPChisq = new RooFormulaVar("piIPChisq","#pi #chi^{2}_{IP}","log(@0)",RooArgList(*pi_IPCHI2_OWNPV));
  RooFormulaVar* RpiIPChisq = new RooFormulaVar("RpiIPChisq","#Rpi #chi^{2}_{IP}","log(@0)",RooArgList(*Rpi_IPCHI2_OWNPV));
//  RooFormulaVar* mupIPChisq = new RooFormulaVar("mupIPChisq","#mu^{+} #chi^{2}_{IP}","log(@0)",RooArgList(*mup_IPCHI2_OWNPV));
//  RooFormulaVar* mumIPChisq = new RooFormulaVar("mumIPChisq","#mu^{-} #chi^{2}_{IP}","log(@0)",RooArgList(*mum_IPCHI2_OWNPV));
  RooFormulaVar* XbPT = new RooFormulaVar("XbPT","X_{b} p_{T}","log(@0)",RooArgList(*Xb_PT));
  RooFormulaVar* RpPT = new RooFormulaVar("RpPT","Rp p_{T}","log(@0)",RooArgList(*Rp_PT));
//  RooFormulaVar* R2JpsiPT = new RooFormulaVar("R2JpsiPT","D/J#psi p_{T} ratio","log(@0/@1)",RooArgList(*R_PT,*Jpsi_PT));
  RooFormulaVar* DVtxChisq = new RooFormulaVar("DVtxChisq","D #chi^{2}_{vtx}","log(@0)",RooArgList(*D_ENDVERTEX_CHI2));
  RooFormulaVar* KP = new RooFormulaVar("KP","K^{-} p","log(@0)",RooArgList(*K_P));
  RooFormulaVar* RpP = new RooFormulaVar("RpP","Rp^{-} p","log(@0)",RooArgList(*Rp_P));
  RooFormulaVar* piP = new RooFormulaVar("piP","#pi p","log(@0)",RooArgList(*pi_P));
  RooFormulaVar* RpiP = new RooFormulaVar("RpiP","#Rpi p","log(@0)",RooArgList(*Rpi_P));
  RooFormulaVar* KProbNNk = new RooFormulaVar("KProbNNk","K^{-} ProbNNk","1-sqrt(1-@0)",RooArgList(*K_ProbNNk));
  RooFormulaVar* piProbNNpi = new RooFormulaVar("piProbNNpi","#pi ProbNNpi","1-sqrt(1-@0)",RooArgList(*pi_MC12TuneV3_ProbNNpi));
  RooFormulaVar* RpiProbNNpi = new RooFormulaVar("RpiProbNNpi","#Rpi ProbNNpi","1-sqrt(1-@0)",RooArgList(*Rpi_MC12TuneV3_ProbNNpi));
  RooFormulaVar* RpProbNNp = new RooFormulaVar("RpProbNNp","#Rp ProbNNp","1-sqrt(1-@0)",RooArgList(*Rp_MC12TuneV3_ProbNNp));
  RooFormulaVar* DTAU = new RooFormulaVar("DTAU","D TAU","1000*(@0)",RooArgList(*D_TAU));
  //  RooFormulaVar* NOTracks = new RooFormulaVar("nTracks","nTracks","1.000*(@0)",RooArgList(*nTracks));
  //----------------------------reWeight--------------------------------------------
  RooFormulaVar* RMass = new RooFormulaVar("RMass","RMass","@0",RooArgList(*R_M));
  RooFormulaVar* Dp = new RooFormulaVar("Dp","M(D p)","sqrt(pow(@0+@1,2)-pow(@2+@3,2)-pow(@4+@5,2)-pow(@6+@7,2))",
                                            RooArgList(*D_PE,*Rp_PE,*D_PX,*Rp_PX,*D_PY,*Rp_PY,*D_PZ,*Rp_PZ));
  //----------------------------reWeight--------------------------------------------




  RooDataSet* data_red = new RooDataSet("data_red","dataset with reduced vars",treeNew1,args);
  RooRealVar* RfdVar =  (RooRealVar*) data_red->addColumn(*Rfd);
  RooRealVar* DMassVar =  (RooRealVar*) data_red->addColumn(*DMass);    
  RooRealVar* DOFChisqVar =  (RooRealVar*) data_red->addColumn(*DOFChisq);
  RooRealVar* XbIPChisqVar =  (RooRealVar*) data_red->addColumn(*XbIPChisq);  
  RooRealVar* DIPChisqVar =  (RooRealVar*) data_red->addColumn(*DIPChisq);  
//  RooRealVar* JpsiIPChisqVar =  (RooRealVar*) data_red->addColumn(*JpsiIPChisq);  
  RooRealVar* KIPChisqVar =  (RooRealVar*) data_red->addColumn(*KIPChisq);  
  RooRealVar* piIPChisqVar =  (RooRealVar*) data_red->addColumn(*piIPChisq);  
  RooRealVar* RpiIPChisqVar =  (RooRealVar*) data_red->addColumn(*RpiIPChisq);  
  //  RooRealVar* mupIPChisqVar =  (RooRealVar*) data_red->addColumn(*mupIPChisq);  
  //  RooRealVar* mumIPChisqVar =  (RooRealVar*) data_red->addColumn(*mumIPChisq);  
  RooRealVar* XbPTVar =  (RooRealVar*) data_red->addColumn(*XbPT);  
  RooRealVar* RpPTVar =  (RooRealVar*) data_red->addColumn(*RpPT);  
 // RooRealVar* R2JpsiPTVar =  (RooRealVar*) data_red->addColumn(*R2JpsiPT);  
  RooRealVar* DVtxChisqVar =  (RooRealVar*) data_red->addColumn(*DVtxChisq);  
  RooRealVar* KPVar =  (RooRealVar*) data_red->addColumn(*KP);  
  RooRealVar* RpPVar =  (RooRealVar*) data_red->addColumn(*RpP);  
  RooRealVar* piPVar =  (RooRealVar*) data_red->addColumn(*piP);  
  RooRealVar* RpiPVar =  (RooRealVar*) data_red->addColumn(*RpiP);  
  RooRealVar* KProbNNkVar =  (RooRealVar*) data_red->addColumn(*KProbNNk);  
  RooRealVar* piProbNNpiVar =  (RooRealVar*) data_red->addColumn(*piProbNNpi);  
  RooRealVar* RpiProbNNpiVar =  (RooRealVar*) data_red->addColumn(*RpiProbNNpi);
  RooRealVar* RpProbNNpVar =  (RooRealVar*) data_red->addColumn(*RpProbNNp);
  RooRealVar* DTAUVar =  (RooRealVar*) data_red->addColumn(*DTAU);  
  //  RooRealVar* nTracksVar =  (RooRealVar*) data_red->addColumn(*nTracks);  
  //----------------------------reWeight--------------------------------------------
  RooRealVar* RMassVar = (RooRealVar*) data_red->addColumn(*RMass);
  RooRealVar* DpVar = (RooRealVar*) data_red->addColumn(*Dp);
  //----------------------------reWeight--------------------------------------------

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
  TH1F* DMassHist = dataw_signal->createHistogram("DMassHist",*DMassVar,Binning(48,1834,1894)); 
  TH1F* RfdHist = dataw_signal->createHistogram("RfdHist",*RfdVar,Binning(45,-4,4)); 
  TH1F* DOFChisqHist = dataw_signal->createHistogram("DOFChisqHist",*DOFChisqVar,Binning(50,-2.5,2.5)); 
  TH1F* XbIPChisqHist = dataw_signal->createHistogram("XbIPChisqHist",*XbIPChisqVar,Binning(50,-6,4)); 
  TH1F* DIPChisqHist = dataw_signal->createHistogram("DIPChisqHist",*DIPChisqVar,Binning(80,-4,12)); 
//  TH1F* JpsiIPChisqHist = dataw_signal->createHistogram("JpsiIPChisqHist",*JpsiIPChisqVar,Binning(80,-6,10)); 
  TH1F* KIPChisqHist = dataw_signal->createHistogram("KIPChisqHist",*KIPChisqVar,Binning(45,0,12)); 
  TH1F* piIPChisqHist = dataw_signal->createHistogram("piIPChisqHist",*piIPChisqVar,Binning(45,0,12)); 
  TH1F* RpiIPChisqHist = dataw_signal->createHistogram("RpiIPChisqHist",*RpiIPChisqVar,Binning(45,0,12)); 
  //  TH1F* mupIPChisqHist = dataw_signal->createHistogram("mupIPChisqHist",*mupIPChisqVar,Binning(70,-2,12)); 
  //  TH1F* mumIPChisqHist = dataw_signal->createHistogram("mumIPChisqHist",*mumIPChisqVar,Binning(70,-2,12)); 
  TH1F* XbPTHist = dataw_signal->createHistogram("XbPTHist",*XbPTVar,Binning(60,7,11)); 
  TH1F* RpPTHist = dataw_signal->createHistogram("RpPTHist",*RpPTVar,Binning(60,5,11)); 
//  TH1F* R2JpsiPTHist = dataw_signal->createHistogram("R2JpsiPTHist",*R2JpsiPTVar,Binning(70,-3.5,3.5)); 
  TH1F* DVtxChisqHist = dataw_signal->createHistogram("DVtxChisqHist",*DVtxChisqVar,Binning(80,-7,4)); 
  TH1F* KPHist = dataw_signal->createHistogram("KPHist",*KPVar,Binning(60,7,13)); 
  TH1F* RpPHist = dataw_signal->createHistogram("RpPHist",*RpPVar,Binning(60,7,13)); 
  TH1F* piPHist = dataw_signal->createHistogram("piPHist",*piPVar,Binning(60,7,13));
  TH1F* RpiPHist = dataw_signal->createHistogram("RpiPHist",*RpiPVar,Binning(60,7,13)); 
  TH1F* KProbNNkHist = dataw_signal->createHistogram("KProbNNkHist",*KProbNNkVar,Binning(50,0,1)); 
  TH1F* piProbNNpiHist = dataw_signal->createHistogram("piProbNNpiHist",*piProbNNpiVar,Binning(50,0,1)); 
  TH1F* RpiProbNNpiHist = dataw_signal->createHistogram("RpiProbNNpiHist",*RpiProbNNpiVar,Binning(50,0,1)); 
  TH1F* RpProbNNpHist = dataw_signal->createHistogram("RpProbNNpHist",*RpProbNNpVar,Binning(50,0,1)); 
  TH1F* DTAUHist = dataw_signal->createHistogram("DTAUHist",*DTAUVar,Binning(100,-1,1.5)); 
  TH1F* nTracksHist = dataw_signal->createHistogram("nTracksHist",*nTracks,Binning(325,0,650)); 
  if(withBDT)
    {
      TH1F* BDTGHist = dataw_signal->createHistogram("BDTGHist",*BDTG,Binning(100,-1,1));
    }
  //----------------------------reWeight--------------------------------------------
  TH1F* RMassHist = dataw_signal->createHistogram("RMassHist",*RMassVar,Binning(50,1000,4000));
 TH1F* DpHist = dataw_signal->createHistogram("DpHist",*DpVar,Binning(50,2770,3070));
  //----------------------------reWeight--------------------------------------------

  addGraphics(DMassHist, "D mass [MeV/#it{c}^{2}]");
  addGraphics(RfdHist, "log(Radial distance) of b hadron");
  addGraphics(DOFChisqHist,"log(#chi^{2}_{DOF})");
  addGraphics(XbIPChisqHist,"X_{b} log(#chi^{2}_{IP})");
  addGraphics(DIPChisqHist,"D log(#chi^{2}_{IP})");
//  addGraphics(JpsiIPChisqHist,"J/#psi log(#chi^{2}_{IP})");
  addGraphics(KIPChisqHist,"K^{-} log(#chi^{2}_{IP})");
  addGraphics(piIPChisqHist,"#pi log(#chi^{2}_{IP})");
  addGraphics(RpiIPChisqHist,"#Rpi log(#chi^{2}_{IP})");
  //  addGraphics(mupIPChisqHist,"#mu^{+} log(#chi^{2}_{IP})");
  //  addGraphics(mumIPChisqHist,"#mu^{-} log(#chi^{2}_{IP})");
  addGraphics(XbPTHist,"X_{b} log(p_{T})");
  addGraphics(RpPTHist,"Rp log(p_{T})");
//  addGraphics(R2JpsiPTHist,"log( p_{T}^{D} / p_{T}^{J/#psi} )");
  addGraphics(DVtxChisqHist,"D log((#chi^{2}_{vtx})");
  addGraphics(KPHist,"K^{-} log(p)");
  addGraphics(RpPHist,"Rp log(p)");
  addGraphics(piPHist,"#pi log(p)");
  addGraphics(RpiPHist,"#Rpi log(p)");
  addGraphics(KProbNNkHist,"K^{-} 1-#sqrt{1-ProbNNk}");
  addGraphics(piProbNNpiHist,"#pi 1-#sqrt{1-ProbNNpi}");
  addGraphics(RpiProbNNpiHist,"#Rpi 1-#sqrt{1-ProbNNpi}");
  addGraphics(RpProbNNpHist,"#Rp 1-#sqrt{1-ProbNNp}");
  addGraphics(DTAUHist,"Decay time of D");
  addGraphics(nTracksHist,"nTracks");
  if(withBDT)
    {
      addGraphics(BDTGHist,"BDTG output");
    }
  addGraphics(RMassHist,"R Mass");
  addGraphics(DpHist,"D p Mass");

  int ii = 1;
  TCanvas *cSW = new TCanvas("cSW","sWeight plots",1800,1000);
  cSW->Divide(6,4);
  cSW->cd(ii++);
  DMassHist->Draw();
  cSW->cd(ii++);
  RfdHist->Draw();
  cSW->cd(ii++);
  DOFChisqHist->Draw();
  cSW->cd(ii++);
  XbIPChisqHist->Draw();
  cSW->cd(ii++);
  DIPChisqHist->Draw();
//  cSW->cd(ii++);
//  JpsiIPChisqHist->Draw();
  cSW->cd(ii++);
  KIPChisqHist->Draw();
  cSW->cd(ii++);
  piIPChisqHist->Draw();
  cSW->cd(ii++);
  RpiIPChisqHist->Draw();
  cSW->cd(ii++);
  //  mupIPChisqHist->Draw();
  //cSW->cd(ii++);
  //  mumIPChisqHist->Draw();
  //  cSW->cd(ii++);
  XbPTHist->Draw();
  cSW->cd(ii++);
  RpPTHist->Draw();
//  cSW->cd(ii++);
//  R2JpsiPTHist->Draw();
  cSW->cd(ii++);
  DVtxChisqHist->Draw();
  cSW->cd(ii++);
  RpPHist->Draw();
  cSW->cd(ii++);
  KPHist->Draw();
  cSW->cd(ii++);
  piPHist->Draw();
  cSW->cd(ii++);
  RpiPHist->Draw();
  cSW->cd(ii++);
  KProbNNkHist->Draw();
  cSW->cd(ii++);
  piProbNNpiHist->Draw();
  cSW->cd(ii++);
  RpiProbNNpiHist->Draw();
  cSW->cd(ii++);
  RpProbNNpHist->Draw();
  cSW->cd(ii++);
  DTAUHist->Draw();
  cSW->cd(ii++);
  nTracksHist->Draw();
  if(withBDT)
    {
      cSW->cd(ii++);
      BDTGHist->Draw();
    }


  cSW->cd(ii++);
  RMassHist->Draw();
  cSW->cd(ii++);
  DpHist->Draw();

  fout->Write();


  return;
  
  
}


