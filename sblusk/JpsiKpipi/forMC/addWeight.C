void addWeight(){

  TFile *fh = new TFile("./histRatio.root");
  TH1F *h1 = (TH1F*)fh->Get("hrat")->Clone("h1");
  TH1F *h2 = (TH1F*)fh->Get("hrat2")->Clone("h2");
  TH1F *h3 = (TH1F*)fh->Get("hrat3")->Clone("h3");
  //fh->Close();

  //return;
  

  TString outdir = "/data1/sblusk/Xibc/JpsiX/JpsiKpipi/mc/";
  
  TString infile, outfile,treeName;
  TString topdir = outdir;
  infile = topdir+"JpsiKpipi.kpipi.X2JpsiKpipi.X2Kpipi.wMVA.test3.root";
  outfile = outdir+"JpsiKpipi.kpipi.X2JpsiKpipi.X2Kpipi.wMVA.test3.addweight.root";
  treeName = "mytree";
  
  
  
  cout << " -------------------------------------------------------------------------" << endl;
  //cout << "Running tuning of input MC variables, Decay.= " << decay << endl;
  cout << "Input File: " << infile << endl;
  cout << "Output file: " << outfile << endl; 
  cout << "----> Tree: " << treeName << endl;
  cout << " -------------------------------------------------------------------------" << endl;

  TFile *f = new TFile(infile);
  
  TTree *oldtree = (TTree*)f->Get(treeName);

  double Xc_M;
  double k_PX;
  double k_PY;
  double k_PZ;
  double k_PE;
  double pi1_PX;
  double pi1_PY;
  double pi1_PZ;
  double pi1_PE;
  double pi2_PX;
  double pi2_PY;
  double pi2_PZ;
  double pi2_PE;

  oldtree->SetBranchAddress("Xc_M", &Xc_M);  
  oldtree->SetBranchAddress("k_PX", &k_PX);
  oldtree->SetBranchAddress("k_PY", &k_PY);  
  oldtree->SetBranchAddress("k_PZ", &k_PZ);  
  oldtree->SetBranchAddress("k_PE", &k_PE);  
  oldtree->SetBranchAddress("pi1_PX", &pi1_PX);  
  oldtree->SetBranchAddress("pi1_PY", &pi1_PY);  
  oldtree->SetBranchAddress("pi1_PZ", &pi1_PZ);  
  oldtree->SetBranchAddress("pi1_PE", &pi1_PE);  
  oldtree->SetBranchAddress("pi2_PX", &pi2_PX);  
  oldtree->SetBranchAddress("pi2_PY", &pi2_PY);  
  oldtree->SetBranchAddress("pi2_PZ", &pi2_PZ);  
  oldtree->SetBranchAddress("pi2_PE", &pi2_PE);  


  TFile *newfile = new TFile(outfile,"RECREATE");
  TTree* newtree = (TTree*) oldtree->CloneTree(0);

  double XcWeight, XkWeight, XpWeight;
  //newtree->Branch("lab0_LOKI_CONE1PTASY", &lab0_LOKI_CONE1PTASY);
  newtree->Branch("XcWeight", &XcWeight);
  newtree->Branch("XkWeight", &XkWeight);
  newtree->Branch("XpWeight", &XpWeight);

  Long64_t nentries = oldtree->GetEntriesFast();
  cout << "Looping over " << nentries << " entries" << endl;
   
   //nentries = 1000;
   
   double v;
   for (Long64_t i=0;i<nentries; i++) {
      oldtree->GetEntry(i);
      if(i%10000 == 0) cout << "At entry = " << i << endl;
      
      int iB = h1->FindBin(Xc_M);
      
      XcWeight = h1->GetBinContent(iB);
      if(XcWeight<0) XcWeight = 0.001;
      if(XcWeight>10) XcWeight = 10;

      double mKpi = sqrt(pow(pi1_PE+k_PE,2)-pow(pi1_PX+k_PX,2)-pow(pi1_PY+k_PY,2)-pow(pi1_PZ+k_PZ,2));
      iB = h2->FindBin(mKpi);
      XkWeight = h2->GetBinContent(iB);
      if(XkWeight<0) XcWeight = 0.001;
      if(XkWeight>10) XcWeight = 10;

      double mpipi = sqrt(pow(pi1_PE+pi2_PE,2)-pow(pi1_PX+pi2_PX,2)-pow(pi1_PY+pi2_PY,2)-pow(pi1_PZ+pi2_PZ,2));
      iB = h3->FindBin(mpipi);
      XpWeight = h3->GetBinContent(iB);
      if(XpWeight<0) XpWeight = 0.001;
      if(XpWeight>10) XpWeight = 10;

      newtree->Fill();
   }
   //newtree->Print();
   newtree->AutoSave();
   delete f;
   delete newfile;

}
