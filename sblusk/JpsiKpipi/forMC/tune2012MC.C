void tune2012MC(int updateMode = 0){

  int iDecay = 1;   // 1 = Xib-, 2 = Xib0

  TString outdir = "/data1/sblusk/Xibc/JpsiKpipi/mc/";
  
  TString infile, outfile,treeName;
  TString topdir = outdir;
  infile = topdir+"MC_JpsiKpipi.root";
  outfile = outdir+"JpsiKpipi.root";
  treeName = "X2JpsiLcKpipi/mytree";
  
  cout << " -------------------------------------------------------------------------" << endl;
  cout << "Input File: " << infile << endl;
  cout << "Output file: " << outfile << endl; 
  cout << "----> Tree: " << treeName << endl;
  cout << " -------------------------------------------------------------------------" << endl;

  TFile *f = new TFile(infile);
  
  TTree *oldtree = (TTree*)f->Get(treeName);

  double pi1_IPCHI2_OWNPV;
  double pi2_IPCHI2_OWNPV;
  double k_IPCHI2_OWNPV;
  double Xb_IPCHI2_OWNPV;
  double Xb_FDCHI2_OWNPV;

  double Xc_IPCHI2_OWNPV;

  int Xb_BKGCAT;
  double Xb_LOKI_DTF_CHI2NDOF_massConstr;
  double Xc_M, Xb_M;

  double Xb_PT, Xc_PT;
  double Xc_PT;

  double k_ETA, pi1_ETA, pi2_ETA;
  double k_PZ,  pi1_PZ, pi2_PZ;
  double k_PT,  pi1_PT, pi2_PT;

  double nTracks;
  int nTracksI;
  

  oldtree->SetBranchAddress("Xb_IPCHI2_OWNPV", &Xb_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("Xc_IPCHI2_OWNPV", &Xc_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("k_IPCHI2_OWNPV", &k_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("pi1_IPCHI2_OWNPV", &pi1_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("pi2_IPCHI2_OWNPV", &pi2_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("Xb_FDCHI2_OWNPV", &Xb_FDCHI2_OWNPV);
  oldtree->SetBranchAddress("Xb_M", &Xb_M);
  //oldtree->SetBranchAddress("Xb_LOKI_DTF_CHI2NDOF_massConstr", &Xb_LOKI_DTF_CHI2NDOF_massConstr);
  oldtree->SetBranchAddress("Xc_M", &Xc_M);
  oldtree->SetBranchAddress("nTracks", &nTracks);
  oldtree->SetBranchAddress("Xc_PT", &Xc_PT);

  oldtree->SetBranchAddress("k_PT", &k_PT);  
  oldtree->SetBranchAddress("pi1_PT", &pi1_PT);  
  oldtree->SetBranchAddress("pi2_PT", &pi2_PT);  
  oldtree->SetBranchAddress("k_PZ", &k_PZ);  
  oldtree->SetBranchAddress("pi1_PZ", &pi1_PZ);  
  oldtree->SetBranchAddress("pi2_PZ", &pi2_PZ);  

  TFile *newfile = new TFile(outfile,"RECREATE");
  TTree* newtree = (TTree*) oldtree->CloneTree(0);

  //newtree->Branch("lab0_LOKI_CONE1PTASY", &lab0_LOKI_CONE1PTASY);
  newtree->Branch("pi1_ETA", &pi1_ETA);
  newtree->Branch("pi2_ETA", &pi2_ETA);
  newtree->Branch("k_ETA", &k_ETA);
  newtree->Branch("nTracksI", &nTracksI);

  Long64_t nentries = oldtree->GetEntriesFast();
  cout << "Looping over " << nentries << " entries" << endl;
   
   //nentries = 1000;
   
   double v;
   for (Long64_t i=0;i<nentries; i++) {
      oldtree->GetEntry(i);
      if(i%10000 == 0) cout << "At entry = " << i << endl;
 
      if(updateMode > 0){
          double voff = 0.08; 
          if(Xb_LOKI_DTF_CHI2NDOF_massConstr>=0){
            v = exp(log(Xb_LOKI_DTF_CHI2NDOF_massConstr)+voff);
            Xb_LOKI_DTF_CHI2NDOF_massConstr = v;
          }
          
          if(Xb_IPCHI2_OWNPV<0){
            cout << "Negative IPCHI2, skipping this ... " << Xb_IPCHI2_OWNPV << endl;
          }else{
            v = exp(log(Xb_IPCHI2_OWNPV)+0.05);
            Xb_IPCHI2_OWNPV = v;
          }
          voff = 0.15*(1.0+0.05*gRandom->Gaus());
          v = exp(log(k_IPCHI2_OWNPV)+voff);
          k_IPCHI2_OWNPV = v;
          voff = 0.15*(1.0+0.05*gRandom->Gaus());
          v = exp(log(pi1_IPCHI2_OWNPV)+voff);
          pi1_IPCHI2_OWNPV = v;
          voff = 0.15*(1.0+0.05*gRandom->Gaus());
          v = exp(log(pi2_IPCHI2_OWNPV)+voff);
          pi2_IPCHI2_OWNPV = v;
          
          v = exp(log(Xc_IPCHI2_OWNPV)+0.15);
          Xc_IPCHI2_OWNPV = v;
          
          
          // In sim08, the pT asymmetry looks fine as is..
          //lab0_LOKI_CONE1PTASY = lab0_LOKI_CONE1PTASY - 0.04;
          // lab0_LOKI_CONE1PTASY =  lab0_ptasy_1_50 - 0.08;
                    
      }else{
        // Scale up nTracks
        v = 1.3*nTracks;
        nTracks = v;
        pi1_ETA = -1.0*log(tan(0.5*pi1_PT/pi1_PZ));
        pi2_ETA = -1.0*log(tan(0.5*pi2_PT/pi2_PZ));
        k_ETA = -1.0*log(tan(0.5*k_PT/k_PZ)); 
        nTracksI = nTracks;        
      }
      
      newtree->Fill();
      
      //event->Clear();
   }
   //newtree->Print();
   newtree->AutoSave();
   delete f;
   delete newfile;

}
