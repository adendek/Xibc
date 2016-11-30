void tune2012MC()
{

  int iDecay = 1;   

  TString outdir = "/data1/sblusk/Xibc/LcD0/mc/";
  
  TString infile, outfile,treeName;
  TString topdir = outdir;
  infile = topdir+"/x2LcD0_mc.root";
  outfile = outdir+"/x2LcD0_mc.tuned.root";
  treeName = "MyXb0/mytree";  

  TFile *f = new TFile(infile);
  
  TTree *oldtree = (TTree*)f->Get(treeName);

  double p_IPCHI2_OWNPV;
  double k_IPCHI2_OWNPV;
  double pi_IPCHI2_OWNPV;
  double K_IPCHI2_OWNPV;
  double PI_IPCHI2_OWNPV;
  double Xb_IPCHI2_OWNPV;
  double Xb_FDCHI2_OWNPV;

  double D0_IPCHI2_OWNPV;
  double Lc_IPCHI2_OWNPV;

  int Xb_BKGCAT;
  double Xb_LOKI_CHI2NDOF_D0Constr;
  double D0_M, Xb_M;

  double Xb_PT;
  double p_PT;
  double k_PT;
  double pi_PT;
  double D0_PT;
  double K_PT;
  double PI_PT;

  double K_ETA, PI_ETA, k_ETA, pi_ETA, p_ETA;
  double K_PZ, PI_PZ, k_PZ, pi_PZ, p_PZ;
  double K_PT, PI_PT, k_PT, pi_PT, p_PT;

  int nTracks;
  int nTracksI;
  

  oldtree->SetBranchAddress("Xb_IPCHI2_OWNPV", &Xb_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("p_IPCHI2_OWNPV", &p_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("k_IPCHI2_OWNPV", &k_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("pi_IPCHI2_OWNPV", &pi_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("D0_IPCHI2_OWNPV", &D0_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("Lc_IPCHI2_OWNPV", &Lc_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("K_IPCHI2_OWNPV", &K_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("PI_IPCHI2_OWNPV", &PI_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("Xb_FDCHI2_OWNPV", &Xb_FDCHI2_OWNPV);
  oldtree->SetBranchAddress("Xb_M", &Xb_M);
  oldtree->SetBranchAddress("Xb_LOKI_CHI2NDOF_D0Constr", &Xb_LOKI_CHI2NDOF_D0Constr);
  oldtree->SetBranchAddress("D0_M", &D0_M);
  oldtree->SetBranchAddress("nTracks", &nTracks);


  oldtree->SetBranchAddress("D0_PT", &D0_PT);

  oldtree->SetBranchAddress("p_PT", &p_PT);  
  oldtree->SetBranchAddress("k_PT", &k_PT);  
  oldtree->SetBranchAddress("pi_PT", &pi_PT);  
  oldtree->SetBranchAddress("K_PT", &K_PT);  
  oldtree->SetBranchAddress("PI_PT", &PI_PT);  
  oldtree->SetBranchAddress("p_PZ", &p_PZ);    
  oldtree->SetBranchAddress("k_PZ", &k_PZ);    
  oldtree->SetBranchAddress("pi_PZ", &pi_PZ);    
  oldtree->SetBranchAddress("K_PZ", &K_PZ);  
  oldtree->SetBranchAddress("PI_PZ", &PI_PZ);  

  TFile *newfile = new TFile(outfile,"RECREATE");
  TTree* newtree = (TTree*) oldtree->CloneTree(0);

  //newtree->Branch("lab0_LOKI_CONE1PTASY", &lab0_LOKI_CONE1PTASY);
  newtree->Branch("p_ETA", &p_ETA);
  newtree->Branch("k_ETA", &k_ETA);
  newtree->Branch("pi_ETA", &pi_ETA);
  newtree->Branch("K_ETA", &K_ETA);
  newtree->Branch("PI_ETA", &PI_ETA);
  newtree->Branch("nTracksI", &nTracksI);

  Long64_t nentries = oldtree->GetEntriesFast();
  cout << "Looping over " << nentries << " entries" << endl;
   
  cout << " -------------------------------------------------------------------------" << endl;
  cout << "Input File: " << infile << endl;
  cout << "Output file: " << outfile << endl; 
  cout << "----> Tree: " << treeName << endl;
  cout << " -------------------------------------------------------------------------" << endl;

   //nentries = 1000;
   
   double v;
   for (Long64_t i=0;i<nentries; i++) {
      oldtree->GetEntry(i);
      if(i%10000 == 0) cout << "At entry = " << i << endl;
      
      double voff = 0.08; 
      if(Xb_LOKI_CHI2NDOF_D0Constr>=0)
        v = exp(log(Xb_LOKI_CHI2NDOF_D0Constr)+voff);
      Xb_LOKI_CHI2NDOF_D0Constr = v;
      //voff = 0.0;
      //if(lab0_DTF_CHI2NDOF>=0)
      //  v = exp(log(lab0_DTF_CHI2NDOF)+voff);
      //lab0_DTF_CHI2NDOF = v;

      v = exp(log(Xb_IPCHI2_OWNPV)+0.05);
      Xb_IPCHI2_OWNPV = v;
      
      //D0 daughters
      voff = 0.15*(1.0+0.05*gRandom->Gaus());
      v = exp(log(K_IPCHI2_OWNPV)+voff);
      K_IPCHI2_OWNPV = v;
      voff = 0.15*(1.0+0.05*gRandom->Gaus());
      v = exp(log(PI_IPCHI2_OWNPV)+voff);
      PI_IPCHI2_OWNPV = v;
      // Lc daughters
      voff = 0.15*(1.0+0.05*gRandom->Gaus());
      v = exp(log(p_IPCHI2_OWNPV)+voff);
      p_IPCHI2_OWNPV = v;
      voff = 0.15*(1.0+0.05*gRandom->Gaus());
      v = exp(log(k_IPCHI2_OWNPV)+voff);
      k_IPCHI2_OWNPV = v;
      voff = 0.15*(1.0+0.05*gRandom->Gaus());
      v = exp(log(pi_IPCHI2_OWNPV)+voff);
      pi_IPCHI2_OWNPV = v;


      v = exp(log(D0_IPCHI2_OWNPV)+0.15);
      D0_IPCHI2_OWNPV = v;
      v = exp(log(Lc_IPCHI2_OWNPV)+0.15);
      Lc_IPCHI2_OWNPV = v;


      // In sim08, the pT asymmetry looks fine as is..
      //lab0_LOKI_CONE1PTASY = lab0_LOKI_CONE1PTASY - 0.04;
      // lab0_LOKI_CONE1PTASY =  lab0_ptasy_1_50 - 0.08;


      // Scale up nTracks
      v = 1.3*nTracks;
      nTracks = v;


      p_ETA = -1.0*log(tan(0.5*p_PT/p_PZ));
      k_ETA = -1.0*log(tan(0.5*k_PT/k_PZ));
      pi_ETA = -1.0*log(tan(0.5*pi_PT/pi_PZ));
      K_ETA = -1.0*log(tan(0.5*K_PT/K_PZ));
      PI_ETA = -1.0*log(tan(0.5*PI_PT/PI_PZ));
      
      nTracksI = nTracks;

      newtree->Fill();
      
      //event->Clear();
   }
   //newtree->Print();
   newtree->AutoSave();
   delete f;
   delete newfile;

}
