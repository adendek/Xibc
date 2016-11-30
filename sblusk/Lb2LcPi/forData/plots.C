
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

  if(mode==0 || mode==2 || mode==10 || mode==12){
    //TString titleX = "pK^{#font[122]{-}}#pi^{+} mass [MeV/#it{c}^{2}]";
     TString titleX = "#Lambda_{c}^{+} K^{#font[122]{-}} mass [MeV/#it{c}^{2}]";
  }else if(mode==1 || mode==4 || mode==11 || mode==14){
    TString titleX = "pK^{#font[122]{-}}K^{#font[122]{-}}#pi^{+} mass [MeV/#it{c}^{2}]";
  }else if(mode==3 || mode==13){
    TString titleX = "pK^{#font[122]{-}} [MeV/#it{c}^{2}]";
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
  frame->SetTitleOffset(0.95,"X");
  frame->SetTitleOffset(1.40,"Y");
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
  ch->Add("/data1/sblusk/Xibc/Lb2JpsipK/data/All_2011_MAGDN.root/"+name);
  ch->Add("/data1/sblusk/Xibc/Lb2JpsipK/data/All_2011_MAGUP.root/"+name);
  ch->Add("/data1/sblusk/Xibc/Lb2JpsipK/data/All_2012_MAGDN.root/"+name);
  ch->Add("/data1/sblusk/Xibc/Lb2JpsipK/data/All_2012_MAGUP.root/"+name);
  
  return ch;    

}



void plots(){

  gStyle->SetStatH(0.28);
  

  TLatex *myLatex = new TLatex();
  myLatex->SetTextFont(42); myLatex->SetTextColor(1); myLatex->SetTextAlign(12); myLatex->SetNDC(kTRUE); myLatex->SetTextSize(0.045);
   double xt = 0.6;

  TCanvas *c = new TCanvas("c","Plot",800,800);

  /*
  TFile *f = new TFile("/data1/sblusk/Xibc/Lb2JpsipK/data/All_2012_MAGUP.root");
  TChain *l = getChain("GetIntegratedLuminosity/LumiTuple");  
  //TTree* l = (TTree*)f->Get("GetIntegratedLuminosity/LumiTuple");
  TH1F *lum = new TH1F("lum","Lumi",5,0,5);
  l->Draw("0.5>>lum","IntegratedLuminosity");
  float lumi = lum->GetBinContent(1);    
  lt = Form("Lum =  %4.0f pb^{-1}",lumi);
  */
  TTree* tree[20];
  TChain *ch = new TChain("DecayTree","");
  ch->Add("/data2/sblusk/Xib/Mar2014/2012/Merged/Merged_Lb2LcPi.signalsel.addBranch.wMVA.root/DecayTree");
  
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
  
  float masses[20] = {5620, 2472, 2288, 1871, 2696, 0,0,0,0,0, 2469, 2472, 2288, 1871, 2696, 0,0,0,0,0 };  
  double mlow[20] = {5540, 2420, 2240, 1820, 2645, 0,0,0,0,0, 2420, 2420, 2240, 1820,2645, 0,0,0,0,0 };
  double mhi[20]  = {5800, 2520, 2330, 1920, 2745, 0,0,0,0,0, 2520, 2520, 2330, 1920, 2745, 0,0,0,0,0};  
  double bw[20] = {5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,};
  int nbins[20];
  for(int j=0; j<20; j++){nbins[j] = (mhi[j]-mlow[j])/bw[j];}
  TH1F *h[20];


  TCut cuts[20];
  cuts[0] = "lab0_DIRA_OWNPV>0.99995&&abs(lab2_M-2287)<20&&lab1_ProbNNpi>0.2&&lab4_ProbNNk>0.2";
  TString mRangeCut = Form("lab0_M>%4.0f&&lab0_M<%4.0f",mlow[0],mhi[0]);
  cuts[0] = cuts[0] && mRangeCut;
  

  TCanvas *cc[20];
  
  double sigma[20]; for(int j=0;j<20;j++){sigma[j] = 16.0;}

  RooRealVar* cbn = new RooRealVar("cbn","",10.);
  RooRealVar* cba = new RooRealVar("cba","",1.8,0,5);
  RooRealVar *moff = new RooRealVar("moff","Offset",3097);

  //------------------------------------
  // Set up fit PDF, define fit function
  //------------------------------------
  mvar[i] = new RooRealVar("lab0_M","lab0_M",mlow[i],mhi[i]);
  h[i] = new TH1F(Form("h%d",i),"Mass",nbins[i],mlow[i],mhi[i]);
  TString histExp = Form("lab0_M>>h%d",i);
  tree[i]->Draw(histExp,cuts[i]);
  
  mg[i] = new RooRealVar(Form("mg%d",i),"mean",masses[i],masses[i]-10,masses[i]+10);
  sg[i] = new RooRealVar(Form("sg%d",i),"width",sigma[i],2,15);
  sg2[i] = new RooRealVar(Form("sg2%d",i),"width",18,5,25);
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
  

  bool do_splot = true;
  
  if(!do_splot) return;
  
  //TTree* treeNew1 = tree[i]->CopyTree(cuts[i]);
  TString fileName = "/data1/sblusk/Xibc/Lb2LcPi/data/sWeightedData.root";
  TFile *fout = new TFile(fileName,"RECREATE");

  TTree* treeNew1 = tree[i]->CopyTree(cuts[i]);

  //--------------------------------------------
  // Variables that are needed in the sWeighting
  //--------------------------------------------
  RooRealVar* lab2_M = new RooRealVar("lab2_M","Xc mass",-1.0e10,1.0e10);
  RooRealVar* lab0_ENDVERTEX_X = new RooRealVar("lab0_ENDVERTEX_X","lab0 pos",-1.0e10,1.0e10);
  RooRealVar* lab0_ENDVERTEX_Y = new RooRealVar("lab0_ENDVERTEX_Y","lab0 pos",-1.0e10,1.0e10);
  RooRealVar* lab0_OWNPV_X = new RooRealVar("lab0_OWNPV_X","lab0 PV pos",-1.0e10,1.0e10);
  RooRealVar* lab0_OWNPV_Y = new RooRealVar("lab0_OWNPV_Y","lab0 PV pos",-1.0e10,1.0e10);
  RooRealVar* lab0_ENDVERTEX_CHI2 = new RooRealVar("lab0_ENDVERTEX_CHI2","lab0 Vertex chisq",-1.0e10,1.0e10);

  RooRealVar* lab0_IPCHI2_OWNPV = new RooRealVar("lab0_IPCHI2_OWNPV","lab0 IP chisq",-1.0e10,1.0e10);
  RooRealVar* lab0_DIRA_OWNPV = new RooRealVar("lab0_DIRA_OWNPV","lab0 DIRA",-1.0e10,1.0e10);
  RooRealVar* lab0_PT = new RooRealVar("lab0_PT","lab0 PT",-1.0e10,1.0e10);
  RooRealVar* lab1_IPCHI2_OWNPV = new RooRealVar("lab1_IPCHI2_OWNPV","lab1 IP chisq",-1.0e10,1.0e10);
  RooRealVar* lab1_PT = new RooRealVar("lab1_PT","lab1 PT",-1.0e10,1.0e10);
  RooRealVar* lab2_PT = new RooRealVar("lab2_PT","lab2 PT",-1.0e10,1.0e10);
  RooRealVar* lab2_IPCHI2_OWNPV = new RooRealVar("lab2_IPCHI2_OWNPV","lab2 IP chisq",-1.0e10,1.0e10);
  RooRealVar* lab2_TAU = new RooRealVar("lab2_TAU","lab2 TAU",-1.0e10,1.0e10);
  RooRealVar* lab4_IPCHI2_OWNPV = new RooRealVar("lab4_IPCHI2_OWNPV","k IP chisq",-1.0e10,1.0e10);
  RooRealVar* lab5_IPCHI2_OWNPV = new RooRealVar("lab5_IPCHI2_OWNPV","p IP chisq",-1.0e10,1.0e10);
  RooRealVar* lab2_ENDVERTEX_CHI2 = new RooRealVar("lab2_ENDVERTEX_CHI2","lab2 Vertex chisq",-1.0e10,1.0e10);
  RooRealVar* lab4_P = new RooRealVar("lab4_P","K^{-} momentum",-1.0e10,1.0e10);
  RooRealVar* lab5_P = new RooRealVar("lab5_P","p^{+} momentum",-1.0e10,1.0e10);
  RooRealVar* lab4_ProbNNk = new RooRealVar("lab4_ProbNNk","K^{-} ProbNNk",-1.0e10,1.0e10);
  RooRealVar* lab5_ProbNNp = new RooRealVar("lab5_ProbNNp","p^{+} ProbNNk",-1.0e10,1.0e10);
  RooRealVar* lab4_PT = new RooRealVar("lab4_PT","K^{-} pT",-1.0e10,1.0e10);
  RooRealVar* lab5_PT = new RooRealVar("lab5_PT","p^{+} pT",-1.0e10,1.0e10);
  RooRealVar* lab4_PZ = new RooRealVar("lab4_PZ","K^{-} pZ",-1.0e10,1.0e10);
  RooRealVar* lab5_PZ = new RooRealVar("lab5_PZ","p^{+} pZ",-1.0e10,1.0e10);
  //RooRealVar* lab4_ETA = new RooRealVar("lab4_ETA","K^{-} pseudorapidity",-1.0e10,1.0e10);
  //RooRealVar* lab5_ETA = new RooRealVar("lab5_ETA","p^{+} pseudorapidity",-1.0e10,1.0e10);

  RooRealVar* nTracks = new RooRealVar("nTracks","nTracks",-1.0e10,1.0e10);
  RooRealVar* nSPDHits = new RooRealVar("nSPDHits","nSPDHits",-1.0e10,1.0e10);


  RooArgSet args;
  args.add(*mvar[i]);
  args.add(*lab2_M);
  args.add(*lab0_ENDVERTEX_X);
  args.add(*lab0_ENDVERTEX_Y);
  args.add(*lab0_OWNPV_X);
  args.add(*lab0_OWNPV_Y);
  args.add(*lab0_IPCHI2_OWNPV);
  args.add(*lab0_DIRA_OWNPV);
  args.add(*lab0_PT);
  args.add(*lab1_IPCHI2_OWNPV);
  args.add(*lab1_PT);
  args.add(*lab2_PT);
  args.add(*lab2_IPCHI2_OWNPV);
  args.add(*lab4_IPCHI2_OWNPV);
  args.add(*lab5_IPCHI2_OWNPV);
  args.add(*lab0_ENDVERTEX_CHI2);
  args.add(*lab2_ENDVERTEX_CHI2);
  args.add(*lab4_P);
  args.add(*lab5_P);
  args.add(*lab4_PT);
  args.add(*lab5_PT);
  args.add(*lab4_PZ);
  args.add(*lab5_PZ);
  args.add(*lab4_ProbNNk);
  args.add(*lab5_ProbNNp);
  args.add(*lab2_TAU);
  args.add(*nTracks);
  args.add(*nSPDHits);

  //----------------------------------------------
  // Variables which are functions of the raw ones
  //----------------------------------------------
  RooFormulaVar* Rfd = new RooFormulaVar("Rfd","log(Radial Flight Distance)","log(sqrt(pow(@0-@1,2)+pow(@2-@3,2)))",
                                        RooArgList(*lab0_ENDVERTEX_X,*lab0_OWNPV_X,*lab0_ENDVERTEX_Y,*lab0_OWNPV_Y)); // radial flight distance
  RooFormulaVar* DTFChisq = new RooFormulaVar("DTFChisq","X_{b} #chi^{2}_{DTF}","log(@0)",RooArgList(*lab0_ENDVERTEX_CHI2));
  RooFormulaVar* lab0IPChisq = new RooFormulaVar("lab0IPChisq","X_{b} #chi^{2}_{IP}","log(@0)",RooArgList(*lab0_IPCHI2_OWNPV));
  RooFormulaVar* lab2IPChisq = new RooFormulaVar("lab2IPChisq","X_{c} #chi^{2}_{IP}","log(@0)",RooArgList(*lab2_IPCHI2_OWNPV));
  RooFormulaVar* lab1IPChisq = new RooFormulaVar("lab1IPChisq","J/#psi #chi^{2}_{IP}","log(@0)",RooArgList(*lab1_IPCHI2_OWNPV));  
  RooFormulaVar* kIPChisq = new RooFormulaVar("kIPChisq","K^{-} #chi^{2}_{IP}","log(@0)",RooArgList(*lab4_IPCHI2_OWNPV));
  RooFormulaVar* pIPChisq = new RooFormulaVar("pIPChisq","p^{+} #chi^{2}_{IP}","log(@0)",RooArgList(*lab5_IPCHI2_OWNPV));
  RooFormulaVar* lab0PT = new RooFormulaVar("lab0PT","X_{b} lab5_{T}","log(@0)",RooArgList(*lab0_PT));
  RooFormulaVar* lab2PT = new RooFormulaVar("lab2PT","X_{c} lab5_{T}","log(@0)",RooArgList(*lab2_PT));
  RooFormulaVar* lab22lab1PT = new RooFormulaVar("lab22lab1PT","X_{c}/J#psi lab5_{T} ratio","log(@0/@1)",RooArgList(*lab2_PT,*lab1_PT));
  RooFormulaVar* lab2VtxChisq = new RooFormulaVar("lab2VtxChisq","X_{c} #chi^{2}_{vtx}","log(@0)",RooArgList(*lab2_ENDVERTEX_CHI2));
  RooFormulaVar* kP = new RooFormulaVar("kP","K^{-} p","log(@0)",RooArgList(*lab4_P));
  RooFormulaVar* pP = new RooFormulaVar("pP","p^{+} p","log(@0)",RooArgList(*lab5_P));
  RooFormulaVar* kProbNNk = new RooFormulaVar("kProbNNk","K^{-} ProbNNk","1-sqrt(1-@0)",RooArgList(*lab4_ProbNNk));
  RooFormulaVar* pProbNNp = new RooFormulaVar("pProbNNp","p ProbNNp","1-sqrt(1-@0)",RooArgList(*lab5_ProbNNp));
  RooFormulaVar* lab2TAU = new RooFormulaVar("lab2TAU","X_{c} TAU","1000*(@0)",RooArgList(*lab2_TAU));
  RooFormulaVar* kEta = new RooFormulaVar("kEta","K^{-} eta","-log(tan(0.5*@0/@1))",RooArgList(*lab4_PT,*lab4_PZ));
  RooFormulaVar* pEta = new RooFormulaVar("pEta","p^{+} eta","-log(tan(0.5*@0/@1))",RooArgList(*lab5_PT,*lab5_PZ));
  RooFormulaVar* kPT = new RooFormulaVar("kPT","K^{-} pT","log(@0)",RooArgList(*lab4_PT));
  RooFormulaVar* pPT = new RooFormulaVar("pPT","p^{+} pT","log(@0)",RooArgList(*lab5_PT));


  RooDataSet* data_red = new RooDataSet("data_red","dataset with reduced vars",treeNew1,args);

  RooRealVar* RfdVar =  (RooRealVar*) data_red->addColumn(*Rfd);  
  RooRealVar* DTFChisqVar =  (RooRealVar*) data_red->addColumn(*DTFChisq);  
  RooRealVar* lab0IPChisqVar =  (RooRealVar*) data_red->addColumn(*lab0IPChisq);  
  RooRealVar* lab2IPChisqVar =  (RooRealVar*) data_red->addColumn(*lab2IPChisq);  
  RooRealVar* lab1IPChisqVar =  (RooRealVar*) data_red->addColumn(*lab1IPChisq);  
  RooRealVar* kIPChisqVar =  (RooRealVar*) data_red->addColumn(*kIPChisq);  
  RooRealVar* pIPChisqVar =  (RooRealVar*) data_red->addColumn(*pIPChisq);  
  RooRealVar* lab0PTVar =  (RooRealVar*) data_red->addColumn(*lab0PT);  
  RooRealVar* lab2PTVar =  (RooRealVar*) data_red->addColumn(*lab2PT);  
  RooRealVar* lab22lab1PTVar =  (RooRealVar*) data_red->addColumn(*lab22lab1PT);  
  RooRealVar* lab2VtxChisqVar =  (RooRealVar*) data_red->addColumn(*lab2VtxChisq);  
  RooRealVar* kPVar =  (RooRealVar*) data_red->addColumn(*kP);  
  RooRealVar* pPVar =  (RooRealVar*) data_red->addColumn(*pP);  
  RooRealVar* kProbNNkVar =  (RooRealVar*) data_red->addColumn(*kProbNNk);  
  RooRealVar* pProbNNpVar =  (RooRealVar*) data_red->addColumn(*pProbNNp);  
  RooRealVar* lab2TAUVar =  (RooRealVar*) data_red->addColumn(*lab2TAU);  
  RooRealVar* kEtaVar =  (RooRealVar*) data_red->addColumn(*kEta);  
  RooRealVar* pEtaVar =  (RooRealVar*) data_red->addColumn(*pEta);  
  RooRealVar* kPTVar =  (RooRealVar*) data_red->addColumn(*kPT);  
  RooRealVar* pPTVar =  (RooRealVar*) data_red->addColumn(*pPT);  

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
  TH1F* lab2Mass = dataw_signal->createHistogram("lab2Mass",*lab2_M,Binning(50,2250,2300)); 
  TH1F* RfdHist = dataw_signal->createHistogram("RfdHist",*RfdVar,Binning(45,-4,4)); 
  TH1F* DTFChisqHist = dataw_signal->createHistogram("DTFChisqHist",*DTFChisqVar,Binning(80,-5,3)); 
  TH1F* lab0IPChisqHist = dataw_signal->createHistogram("lab0IPChisqHist",*lab0IPChisqVar,Binning(50,-6,4)); 
  TH1F* lab2IPChisqHist = dataw_signal->createHistogram("lab2IPChisqHist",*lab2IPChisqVar,Binning(80,-4,12)); 
  TH1F* lab1IPChisqHist = dataw_signal->createHistogram("lab1IPChisqHist",*lab1IPChisqVar,Binning(80,-6,10)); 
  TH1F* kIPChisqHist = dataw_signal->createHistogram("kIPChisqHist",*kIPChisqVar,Binning(45,1.5,10.5)); 
  TH1F* pIPChisqHist = dataw_signal->createHistogram("pIPChisqHist",*pIPChisqVar,Binning(45,1.5,10.5)); 
  TH1F* lab0PTHist = dataw_signal->createHistogram("lab0PTHist",*lab0PTVar,Binning(60,5,11)); 
  TH1F* lab2PTHist = dataw_signal->createHistogram("lab2PTHist",*lab2PTVar,Binning(60,5,11)); 
  TH1F* lab22lab1PTHist = dataw_signal->createHistogram("lab22lab1PTHist",*lab22lab1PTVar,Binning(70,-3.5,3.5)); 
  TH1F* lab2VtxChisqHist = dataw_signal->createHistogram("lab2VtxChisqHist",*lab2VtxChisqVar,Binning(90,-6,3)); 
  TH1F* kPHist = dataw_signal->createHistogram("kPHist",*kPVar,Binning(60,7,13)); 
  TH1F* pPHist = dataw_signal->createHistogram("pPHist",*pPVar,Binning(60,7,13));
  TH1F* kProbNNkHist = dataw_signal->createHistogram("kProbNNkHist",*kProbNNkVar,Binning(50,0,1)); 
  TH1F* pProbNNpHist = dataw_signal->createHistogram("pProbNNpHist",*pProbNNpVar,Binning(50,0,1)); 
  TH1F* lab2TAUHist = dataw_signal->createHistogram("lab2TAUHist",*lab2TAUVar,Binning(100,-1,1)); 
  TH1F* nTracksHist = dataw_signal->createHistogram("nTracksHist",*nTracks,Binning(100,0,500)); 
  TH1F* kEtaHist = dataw_signal->createHistogram("kEtaHist",*kEtaVar,Binning(40,1.5,5.5)); 
  TH1F* pEtaHist = dataw_signal->createHistogram("pEtaHist",*pEtaVar,Binning(40,1.5,5.5));
  TH1F* kPTHist = dataw_signal->createHistogram("kPTHist",*kPTVar,Binning(50,5,10)); 
  TH1F* pPTHist = dataw_signal->createHistogram("pPTHist",*pPTVar,Binning(50,5,10));


  addGraphics(lab2Mass, "p K^{-}#pi^{+} mass [MeV/#it{c}^{2}]");
  addGraphics(RfdHist, "log(Radial distance) of b hadron");
  addGraphics(DTFChisqHist,"log(#chi^{2}_{DTF})");
  addGraphics(lab0IPChisqHist,"X_{b} log(#chi^{2}_{IP})");
  addGraphics(lab2IPChisqHist,"X_{c} log(#chi^{2}_{IP})");
  addGraphics(lab1IPChisqHist,"#pi^{-} log(#chi^{2}_{IP})");
  addGraphics(kIPChisqHist,"K^{-} log(#chi^{2}_{IP})");
  addGraphics(pIPChisqHist,"p^{+} log(#chi^{2}_{IP})");
  addGraphics(lab0PTHist,"X_{b} log(lab5_{T})");
  addGraphics(lab2PTHist,"X_{c} log(lab5_{T})");
  addGraphics(lab22lab1PTHist,"log( lab5_{T}^{X_{c}} / lab5_{T}^{#pi} )");
  addGraphics(lab2VtxChisqHist,"X_{c} log((#chi^{2}_{vtx})");
  addGraphics(kPHist,"K^{-} log(p)");
  addGraphics(pPHist,"p^{+} log(p)");
  addGraphics(kProbNNkHist,"K^{-} 1-#sqrt{1-ProbNNk}");
  addGraphics(pProbNNpHist,"p^{+} 1-#sqrt{1-ProbNNp}");
  addGraphics(lab2TAUHist,"Decay time of #Lambda_{c}^{+} ");
  addGraphics(nTracksHist,"# Tracks");
  addGraphics(kPTHist,"K^{-} log(pT)");
  addGraphics(pPTHist,"p^{+} log(pT)");
  addGraphics(kEtaHist,"K^{-} #eta");
  addGraphics(pEtaHist,"p^{+} #eta");

  int ii = 1;
  TCanvas *cSW = new TCanvas("cSW","sWeight plots",1400,700);
  cSW->Divide(6,4);
  cSW->cd(ii++);
  lab2Mass->Draw();
  cSW->cd(ii++);
  RfdHist->Draw();
  cSW->cd(ii++);
  DTFChisqHist->Draw();
  cSW->cd(ii++);
  lab0IPChisqHist->Draw();
  cSW->cd(ii++);
  lab2IPChisqHist->Draw();
  cSW->cd(ii++);
  lab1IPChisqHist->Draw();
  cSW->cd(ii++);
  kIPChisqHist->Draw();
  cSW->cd(ii++);
  pIPChisqHist->Draw();
  cSW->cd(ii++);
  lab0PTHist->Draw();
  cSW->cd(ii++);
  lab2PTHist->Draw();
  cSW->cd(ii++);
  lab22lab1PTHist->Draw();
  cSW->cd(ii++);
  lab2VtxChisqHist->Draw();
  cSW->cd(ii++);
  kPHist->Draw();
  cSW->cd(ii++);
  pPHist->Draw();
  cSW->cd(ii++);
  kProbNNkHist->Draw();
  cSW->cd(ii++);
  pProbNNpHist->Draw();
  cSW->cd(ii++);
  lab2TAUHist->Draw();

  cSW->cd(ii++);
  pPTHist->Draw();
  cSW->cd(ii++);
  pEtaHist->Draw();
  cSW->cd(ii++);
  kPTHist->Draw();
  cSW->cd(ii++);
  kEtaHist->Draw();


  cSW->cd(ii++);
  nTracksHist->Draw();

  TTree *newtree2 = dataw_signal->tree();
  newtree2->SetName("TreeWithWeight");
  newtree2->Write();
  

  fout->Write();


  return;
  
  
}


