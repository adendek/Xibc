void addWeight()
{

  TFile *fh = new TFile("./histRatio.root");
  TH1F *h1 = (TH1F*)fh->Get("hrat")->Clone("h1");
  TH1F *h2 = (TH1F*)fh->Get("hrat2")->Clone("h2");



  TString outdir = "/data1/sblusk/Xibc/JpsiX/Lb2JpsipK/mc/";
  
  TString infile, outfile,treeName;
  TString topdir = outdir;
  infile = topdir+"Lb2JpsipK_mc.pk.X2JpsipK.Xc2pK.wMVA.def.root";
  outfile = outdir+"Lb2JpsipK_mc.pk.X2JpsipK.Xc2pK.wMVA.def.addweight.root";
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
  double Jpsi_PE;
  double Jpsi_PX;
  double Jpsi_PY;
  double Jpsi_PZ;
  double k_PX;
  double k_PY;
  double k_PZ;
  double k_PE;

  oldtree->SetBranchAddress("Xc_M", &Xc_M);  
  oldtree->SetBranchAddress("k_PX", &k_PX);  
  oldtree->SetBranchAddress("k_PY", &k_PY);  
  oldtree->SetBranchAddress("k_PZ", &k_PZ);  
  oldtree->SetBranchAddress("k_PE", &k_PE);  
  oldtree->SetBranchAddress("Jpsi_PE", &Jpsi_PE);  
  oldtree->SetBranchAddress("Jpsi_PX", &Jpsi_PX);  
  oldtree->SetBranchAddress("Jpsi_PY", &Jpsi_PY);  
  oldtree->SetBranchAddress("Jpsi_PZ", &Jpsi_PZ);  

  TFile *newfile = new TFile(outfile,"RECREATE");
  TTree* newtree = (TTree*) oldtree->CloneTree(0);

  double XcWeight, XkWeight;
  //newtree->Branch("lab0_LOKI_CONE1PTASY", &lab0_LOKI_CONE1PTASY);
  newtree->Branch("XcWeight", &XcWeight);
  newtree->Branch("XkWeight", &XkWeight);

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

      double mJpsiK = sqrt(pow(Jpsi_PE+k_PE,2)-pow(Jpsi_PX+k_PX,2)-pow(Jpsi_PY+k_PY,2)-pow(Jpsi_PZ+k_PZ,2));
      iB = h2->FindBin(mJpsiK);
      XkWeight = h2->GetBinContent(iB);
      if(XkWeight<0) XcWeight = 0.001;
      if(XkWeight>10) XcWeight = 10;

      /*
      XcWeight = 0.0505 + 7.82*exp(-0.004*(Xc_M-1300));
      double mJpsiK = sqrt(pow(Jpsi_PE+k_PE,2)-pow(Jpsi_PX+k_PX,2)-pow(Jpsi_PY+k_PY,2)-pow(Jpsi_PZ+k_PZ,2));
      if(mJpsiK<3600) mJpsiK = 3600;
      if(mJpsiK>4800) mJpsiK = 4800;
      XkWeight = 2.213*exp(0.002078*(mJpsiK-3500));
      */

      // Scale up nTracks

      
      newtree->Fill();
      
      //event->Clear();
   }
   //newtree->Print();
   newtree->AutoSave();
   delete f;
   delete newfile;

}
