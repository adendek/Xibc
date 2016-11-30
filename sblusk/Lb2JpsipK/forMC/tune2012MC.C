void tune2012MC(int updateMode = 0){

  int iDecay = 1;   // 1 = Xib-, 2 = Xib0

  TString outdir = "/data1/sblusk/Xibc/Lb2JpsipK/mc/";
  
  TString infile, outfile,treeName;
  TString topdir = outdir;
  infile = topdir+"MC_Lb2JpsipK.root";
  outfile = outdir+"Lb2JpsipK.root";
  treeName = "X2JpsipK/mytree";
  
  cout << " -------------------------------------------------------------------------" << endl;
  cout << "Input File: " << infile << endl;
  cout << "Output file: " << outfile << endl; 
  cout << "----> Tree: " << treeName << endl;
  cout << " -------------------------------------------------------------------------" << endl;

  TFile *f = new TFile(infile);
  
  TTree *oldtree = (TTree*)f->Get(treeName);

  double p_IPCHI2_OWNPV;
  double k_IPCHI2_OWNPV;
  double Xb_IPCHI2_OWNPV;
  double Xb_FDCHI2_OWNPV;

  double Xc_IPCHI2_OWNPV;
  double p_IPCHI2_OWNPV;
  double k_IPCHI2_OWNPV;

  int Xb_BKGCAT;
  double Xb_LOKI_DTF_CHI2NDOF_massConstr;
  double Xc_M, Xb_M;

  double Xb_PT, Xc_PT;
  double Xc_PT;
  double k_PT;
  double p_PT;

  double k_ETA, Pi_ETA, p_ETA;
  double k_PZ, Pi_PZ, p_PZ;
  double k_PT, Pi_PT, p_PT;

  double nTracks;
  int nTracksI;
  

  oldtree->SetBranchAddress("Xb_IPCHI2_OWNPV", &Xb_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("Xc_IPCHI2_OWNPV", &Xc_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("k_IPCHI2_OWNPV", &k_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("p_IPCHI2_OWNPV", &p_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("Xb_FDCHI2_OWNPV", &Xb_FDCHI2_OWNPV);
  oldtree->SetBranchAddress("Xb_M", &Xb_M);
  //oldtree->SetBranchAddress("Xb_LOKI_DTF_CHI2NDOF_massConstr", &Xb_LOKI_DTF_CHI2NDOF_massConstr);
  oldtree->SetBranchAddress("Xc_M", &Xc_M);
  oldtree->SetBranchAddress("nTracks", &nTracks);
  oldtree->SetBranchAddress("Xc_PT", &Xc_PT);

  oldtree->SetBranchAddress("k_PT", &k_PT);  
  oldtree->SetBranchAddress("p_PT", &p_PT);  
  oldtree->SetBranchAddress("k_PZ", &k_PZ);  
  oldtree->SetBranchAddress("p_PZ", &p_PZ);  

  TFile *newfile = new TFile(outfile,"RECREATE");
  TTree* newtree = (TTree*) oldtree->CloneTree(0);

  //newtree->Branch("lab0_LOKI_CONE1PTASY", &lab0_LOKI_CONE1PTASY);
  newtree->Branch("p_ETA", &p_ETA);
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
          v = exp(log(p_IPCHI2_OWNPV)+voff);
          p_IPCHI2_OWNPV = v;
          
          v = exp(log(Xc_IPCHI2_OWNPV)+0.15);
          Xc_IPCHI2_OWNPV = v;
          
          
          // In sim08, the pT asymmetry looks fine as is..
          //lab0_LOKI_CONE1PTASY = lab0_LOKI_CONE1PTASY - 0.04;
          // lab0_LOKI_CONE1PTASY =  lab0_ptasy_1_50 - 0.08;
                    
      }else{
        // Scale up nTracks
        //v = 1.3*nTracks;
        v = 1.3*nTracks;
        nTracks = v;
        p_ETA = -1.0*log(tan(0.5*p_PT/p_PZ));
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
