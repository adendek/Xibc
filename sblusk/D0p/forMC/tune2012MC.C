void tune2012MC()
{

  int iDecay = 1;   

  TString outdir = "/data1/sblusk/Xibc/D0p/mc/";
  
  TString infile, outfile,treeName;
  TString topdir = outdir;
  infile = topdir+"/x2d0p_mc.root";
  outfile = outdir+"/x2d0p_mc.tuned.root";
  treeName = "Xibc2D0p/mytree";  

  TFile *f = new TFile(infile);
  
  TTree *oldtree = (TTree*)f->Get(treeName);

  double p_IPCHI2_OWNPV;
  double K_IPCHI2_OWNPV;
  double B_IPCHI2_OWNPV;
  double B_FDCHI2_OWNPV;

  double D_IPCHI2_OWNPV;
  double pi_IPCHI2_OWNPV;
  double K_IPCHI2_OWNPV;

  int B_BKGCAT;
  double B_LOKI_CHI2NDOF_D0Constr;
  double D_M, B_M;

  double B_PT;
  double p_PT;
  double D_PT;
  double K_PT;
  double pi_PT;

  double K_ETA, pi_ETA, p_ETA;
  double K_PZ, pi_PZ, p_PZ;
  double K_PT, pi_PT, p_PT;

  double nTracks;
  int nTracksI;
  

  oldtree->SetBranchAddress("B_IPCHI2_OWNPV", &B_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("p_IPCHI2_OWNPV", &p_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("D_IPCHI2_OWNPV", &D_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("K_IPCHI2_OWNPV", &K_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("pi_IPCHI2_OWNPV", &pi_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("B_FDCHI2_OWNPV", &B_FDCHI2_OWNPV);
  oldtree->SetBranchAddress("B_M", &B_M);
  oldtree->SetBranchAddress("B_LOKI_CHI2NDOF_D0Constr", &B_LOKI_CHI2NDOF_D0Constr);
  oldtree->SetBranchAddress("D_M", &D_M);
  oldtree->SetBranchAddress("nTracks", &nTracks);


  oldtree->SetBranchAddress("D_PT", &D_PT);

  oldtree->SetBranchAddress("p_PT", &p_PT);  
  oldtree->SetBranchAddress("K_PT", &K_PT);  
  oldtree->SetBranchAddress("pi_PT", &pi_PT);  
  oldtree->SetBranchAddress("p_PZ", &p_PZ);    
  oldtree->SetBranchAddress("K_PZ", &K_PZ);  
  oldtree->SetBranchAddress("pi_PZ", &pi_PZ);  

  TFile *newfile = new TFile(outfile,"RECREATE");
  TTree* newtree = (TTree*) oldtree->CloneTree(0);

  //newtree->Branch("lab0_LOKI_CONE1PTASY", &lab0_LOKI_CONE1PTASY);
  newtree->Branch("p_ETA", &p_ETA);
  newtree->Branch("K_ETA", &K_ETA);
  newtree->Branch("pi_ETA", &pi_ETA);
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
      if(B_LOKI_CHI2NDOF_D0Constr>=0)
        v = exp(log(B_LOKI_CHI2NDOF_D0Constr)+voff);
      B_LOKI_CHI2NDOF_D0Constr = v;
      //voff = 0.0;
      //if(lab0_DTF_CHI2NDOF>=0)
      //  v = exp(log(lab0_DTF_CHI2NDOF)+voff);
      //lab0_DTF_CHI2NDOF = v;

      v = exp(log(B_IPCHI2_OWNPV)+0.05);
      B_IPCHI2_OWNPV = v;


      voff = 0.15*(1.0+0.05*gRandom->Gaus());
      v = exp(log(K_IPCHI2_OWNPV)+voff);
      K_IPCHI2_OWNPV = v;
      voff = 0.15*(1.0+0.05*gRandom->Gaus());
      v = exp(log(pi_IPCHI2_OWNPV)+voff);
      pi_IPCHI2_OWNPV = v;


      v = exp(log(p_IPCHI2_OWNPV)+0.25);
      p_IPCHI2_OWNPV = v;

      v = exp(log(D_IPCHI2_OWNPV)+0.15);
      D_IPCHI2_OWNPV = v;


      // In sim08, the pT asymmetry looks fine as is..
      //lab0_LOKI_CONE1PTASY = lab0_LOKI_CONE1PTASY - 0.04;
      // lab0_LOKI_CONE1PTASY =  lab0_ptasy_1_50 - 0.08;


      // Scale up nTracks
      v = 1.3*nTracks;
      nTracks = v;


      p_ETA = -1.0*log(tan(0.5*p_PT/p_PZ));
      K_ETA = -1.0*log(tan(0.5*K_PT/K_PZ));
      pi_ETA = -1.0*log(tan(0.5*pi_PT/pi_PZ));
      
      nTracksI = nTracks;

      newtree->Fill();
      
      //event->Clear();
   }
   //newtree->Print();
   newtree->AutoSave();
   delete f;
   delete newfile;

}
