// pass this code your tree, allcuts you want to make, and some dummy string
void setRange(TString hh){
  TH1F *h = (TH1F*)gDirectory->Get(hh);
  double xlow = 0.0;
  double xhi = 8000.0;
  for(int i=0;i<h->GetNbinsX();i++){
    int n = h->GetBinContent(i+1);
    if(n>0) xlow = h->GetBinLowEdge(i)-2*h->GetBinWidth(i);
    if(xlow > 0) break;
  }

  for(int i=h->GetNbinsX();i>0;i--){
    int n = h->GetBinContent(i);
    if(n>0) xhi = h->GetBinLowEdge(i)+2*h->GetBinWidth(i);
    if(xhi < 8000) break;
  }
  cout << "xlow, xhi = " << xlow << " " << xhi << endl;
  


  h->GetXaxis()->SetRangeUser(xlow,xhi);
  
  return;
  
}



int factorial(int n){
    if (n == 1 || n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

void doComb(TString mode, TChain *tree1, TCut allCut, TString projMass = "Xb_M", TString name = "XXX"){
  

  gStyle->SetNdivisions(505,"X");
  gStyle->SetTitleSize(0.04,"X");
  
  bool hardcopy = false; // make a PDF output file

  bool doDstar = false; // do D*->D0pi deltaM plots
  TString mlow = "4700";
  TString mhi = "8000";
  TString range =  projMass+">"+mlow+"&&"+projMass+"<"+mhi;  //put your top-level mass name here.
  TCut massRange = range;
  TCut allCut2 = massRange && allCut;

  cout << "Mode  = " << mode << endl;
  

  int n1 = tree1->GetEntries();
  cout << "===========================================" << endl;
  cout << "Number of entries/tree = " << n1 << endl;
  cout << "===========================================" << endl;

  int doit[4]={1, 1, 1, 1};   // These are switches to run the 2, or 3-body or 4-body  massess 

  if(mode=="JpsiLc" || mode=="JpsiXic"){
    const int nPart = 4;
    TString PE[nPart];
    TString PX[nPart];
    TString PY[nPart];
    TString PZ[nPart];
    TString PID[nPart];
    TString CH[nPart];
    // This corresponds to your 4 particles, e.g.   Jpsi, proton, kaon, pion
    TString pfx[nPart]={"Jpsi","Pi","K","Pr"}; // prefix for your particles
    int swapPion[nPart] = {0, 0, 0, 0};  // These are switches to assign particle the pion mass
    int swapKaon[nPart] = {0, 0, 0, 0};  // These are switches to assign particle the kaon mass
    int swapProton[nPart] = {0, 0, 0, 0};//, 0, 0}; // These are switches to assign particle the proton mass
  }else if(mode=="LcD0"){
    const int nPart = 5;
    TString PE[nPart];
    TString PX[nPart];
    TString PY[nPart];
    TString PZ[nPart];
    TString PID[nPart];
    TString CH[nPart];
    // This corresponds to your 4 particles, e.g.   Jpsi, proton, kaon, pion
    TString pfx[nPart]={"p","k","pi","K", "PI"}; // prefix for your particles
    int swapPion[nPart] = {0, 0, 0, 0, 0};  // These are switches to assign particle the pion mass
    int swapKaon[nPart] = {0, 0, 0, 0, 0};  // These are switches to assign particle the kaon mass
    int swapProton[nPart] = {0, 0, 0, 0, 0};//, 0, 0}; // These are switches to assign particle the proton mass
  }else if(mode=="D0p"){
    const int nPart = 3;
    TString PE[nPart];
    TString PX[nPart];
    TString PY[nPart];
    TString PZ[nPart];
    TString PID[nPart];
    TString CH[nPart];
    // This corresponds to your 4 particles, e.g.   Jpsi, proton, kaon, pion
    TString pfx[nPart]={"K","pi","p"}; // prefix for your particles
    int swapPion[nPart] = {0, 0, 1};  // These are switches to assign particle the pion mass
    int swapKaon[nPart] = {0, 0, 0};  // These are switches to assign particle the kaon mass
    int swapProton[nPart] = {0, 0, 0};//, 0, 0}; // These are switches to assign particle the proton mass
  }

  

  // Form Eneergy and momentum TStrings
  TString swapStatus = "noSwap";
  for(int i=0; i<nPart; i++){
    PE[i] = pfx[i]+"_PE";
    PX[i] = pfx[i]+"_PX";
    PY[i] = pfx[i]+"_PY";
    PZ[i] = pfx[i]+"_PZ";
    PID[i] = pfx[i]+"_ID";
    CH[i] = pfx[i]+"_ID/abs("+pfx[i]+"_ID)";    
    TString chi = Form("%d",i);
    if(swapKaon[i]>0){
      PE[i] = "sqrt("+PX[i]+"**2 + "+PY[i]+"**2 + "+PZ[i]+"**2 + 493.67**2)";
      swapStatus = "swapPionWithKaonMass_Part"+chi;
    }    
    if(swapPion[i]>0){
      PE[i] = "sqrt("+PX[i]+"**2 + "+PY[i]+"**2 + "+PZ[i]+"**2 + 139.57**2)";
      swapStatus = "swapKaonWithPionMass_Part"+chi;
    }    
    if(swapProton[i]>0){
      PE[i] = "sqrt("+PX[i]+"**2 + "+PY[i]+"**2 + "+PZ[i]+"**2 + 938.27**2)";
      swapStatus = "swapPionWithProtonMass_Part"+chi;
    }    
  }
  

  int nbinx = 1000;
  double low = 0.0;
  double hi = 8000.0;
  int ncomb;

  // Do 2-body combinations
  if(doit[0]>0){
    // Book histos
    TH1F *h2[15];
    int ic = 0;
    for(int i=0; i<nPart-1; i++){
      for(int j=i+1; j<nPart; j++){
        TString chi = Form("%d",i);
        TString chj = Form("%d",j);
        TString title = "Mass, Comb  " + chi + chj;
        TString hid = "h2_"+chi+chj;
        h2[ic] = new TH1F(hid,title,nbinx,low,hi);
        cout << "Booking histogram: " << hid << endl;
        ic++;
      }
    }
    // Fill histos
    name = "2_body";
    TCanvas *c = new TCanvas("c_"+name,"Plots " + name, 1200,700);
    ncomb = factorial(nPart) / (factorial(nPart-2)*factorial(2));
    cout << "ncomb = " << ncomb << " " << factorial(nPart-2)*factorial(2) << endl;
    if(ncomb<=4) c->Divide(2,2);
    if(ncomb>4&&ncomb<=6) c->Divide(3,2);
    if(ncomb>6&&ncomb<=9) c->Divide(3,3);
    if(ncomb>9) c->Divide(4,3);
    int ic = 0;
    for(int i=0; i<nPart-1; i++){
      for(int j=i+1; j<nPart; j++){
        TString chi = Form("%d",i);
        TString chj = Form("%d",j);
        TString E2 = "("+PE[i]+"+"+PE[j]+")**2";
        TString PX2 = "("+PX[i]+"+"+PX[j]+")**2";
        TString PY2 = "("+PY[i]+"+"+PY[j]+")**2";
        TString PZ2 = "("+PZ[i]+"+"+PZ[j]+")**2";
        TString P2 = "("+PX2+"+"+PY2+"+"+PZ2+")";
        TString mass = "sqrt("+E2+"-"+P2+")";
        TString fillh = mass+">>+h2_"+chi+chj;
        cout << "Histo Fill Stream: " << fillh << endl;
        ic++;
        c->cd(ic);
        // Only take charge 0 or +-1
        //TString chCuts = "(!("+PID[i] + ">0 &&" + PID[j] + ">0) && !("+PID[i] + "<0 &&" + PID[j] + "<0 ))";
        //TCut chCut = chCuts;
        TCut allCut3 = allCut2;// && chCut;            
        tree1->Draw(fillh,allCut3);
        TString hh = "h2_"+chi+chj;
        setRange(hh);
        c->Update();
      }
    }
    //TString canvasName = "Twobody_"+swapStatus+"_"+mlow+"_"+mhi;
    //if(hardcopy) c->Print("./"+canvasName+"_"+mode+".pdf");
  }
  
  // Threee-body masses
  if(doit[1]>0 && nPart>=3){
    // Book histos
    TString hbase = "h3";
    TH1F *h3[20];
    TH1F *h3_12[20];
    TH1F *h3_13[20];
    TH1F *h3_23[20];
    int ic = 0;
    for(int i=0; i<nPart-2; i++){
      for(int j=i+1; j<nPart-1; j++){
        for(int k=j+1; k<nPart; k++){
          TString chi = Form("%d",i);
          TString chj = Form("%d",j);
          TString chk = Form("%d",k);
          TString title = "Mass, Comb  " + chi + chj + chk;
          TString hid = hbase+"_"+chi+chj+chk;
          h3[ic] = new TH1F(hid,title,nbinx,low,hi);
          h3_12[ic] = new TH1F(hid+"_"+chi+chj,title,600,100,700);
          h3_13[ic] = new TH1F(hid+"_"+chi+chk,title,600,100,700);
          h3_23[ic] = new TH1F(hid+"_"+chj+chk,title,600,100,700);
          cout << "Booking histogram: " << hid << endl;
          ic++;
        }  
      }  
    }
    // Fill histos
    name = "3_body";
    TCanvas *c1 = new TCanvas("c1_"+name,"Plots " + name, 1200,1000);
    ncomb = factorial(nPart) / (factorial(nPart-3)*factorial(3));
    if(ncomb<=4) c1->Divide(2,2);
    if(ncomb>4&&ncomb<=6) c1->Divide(3,2);
    if(ncomb>6&&ncomb<=9) c1->Divide(3,3);
    if(ncomb>9) c1->Divide(4,3);
    int ic = 0;
    for(int i=0; i<nPart-2; i++){
      for(int j=i+1; j<nPart-1; j++){
        for(int k=j+1; k<nPart; k++){
          TString chi = Form("%d",i);
          TString chj = Form("%d",j);
          TString chk = Form("%d",k);
          TString E2 = "("+PE[i]+"+"+PE[j]+"+"+PE[k]+")**2";
          TString PX2 = "("+PX[i]+"+"+PX[j]+"+"+PX[k]+")**2";
          TString PY2 = "("+PY[i]+"+"+PY[j]+"+"+PY[k]+")**2";
          TString PZ2 = "("+PZ[i]+"+"+PZ[j]+"+"+PZ[k]+")**2";
          TString P2 = "("+PX2+"+"+PY2+"+"+PZ2+")";
          TString hid = hbase+"_"+chi+chj+chk;
          TString mass = "sqrt("+E2+"-"+P2+")";
          TString fillh = mass+">>+"+hid;
          cout << "Histo Fill Stream: " << fillh << endl;
          ic++;
          c1->cd(ic);
          //TString chCuts = "abs("+PID[i]+") > 0";
          //chCuts = "(!("+PID[i]+">0 && " + PID[j] + ">0 && " + PID[k] + ">0) && !("+PID[i]+"<0 && " + PID[j] + "<0 && " + PID[k] + "<0 ))";
          //cout << chCuts << endl;
          //TCut chCut = chCuts;
          TCut allCut3 = allCut2;// && chCut;            
          tree1->Draw(fillh,allCut3);
          TString hh = "h3_"+chi+chj+chk;
          setRange(hh);
          
          c1->Update();          
        }
      }
    }
    //TString canvasName = "Threebody_"+swapStatus+"_"+mlow+"_"+mhi;
    //if(hardcopy) c1->Print("./"+canvasName+"_"+mode+".pdf");
  }  


  // Four-body masses
  if(doit[2]>0 && nPart>=4){
    // Book histos
    TString hbase = "h4";
    TH1F *h4[20];
    TH1F *h4_12[20];
    TH1F *h4_13[20];
    TH1F *h4_23[20];
    int ic = 0;
    for(int i=0; i<nPart-3; i++){
      for(int j=i+1; j<nPart-2; j++){
        for(int k=j+1; k<nPart-1; k++){
          for(int l=k+1; l<nPart; l++){
            TString chi = Form("%d",i);
            TString chj = Form("%d",j);
            TString chk = Form("%d",k);
            TString chl = Form("%d",l);
            TString title = "Mass, Comb  " + chi + chj + chk + chl;
            TString hid = hbase+"_"+chi+chj+chk+chl;
            h4[ic] = new TH1F(hid,title,nbinx,low,hi);
            cout << "Booking histogram: " << hid << endl;
            ic++;
          }  
        }  
      }
    }
    
    // Fill histos
    name = "4_body";
    TCanvas *c2 = new TCanvas("c2_"+name,"Plots " + name, 1000,700);
    ncomb = factorial(nPart) / (factorial(nPart-4)*factorial(4));
    if(ncomb<=4 && ncomb>1) c2->Divide(2,2);
    if(ncomb>4&&ncomb<=6) c2->Divide(3,2);
    if(ncomb>6&&ncomb<=9) c2->Divide(3,3);
    if(ncomb>9) c2->Divide(4,3);
    cout << "ncomb = " << ncomb << endl;
    
    int ic = 0;
    for(int i=0; i<nPart-3; i++){
      for(int j=i+1; j<nPart-2; j++){
        for(int k=j+1; k<nPart-1; k++){
          for(int l=k+1; l<nPart; l++){
            TString chi = Form("%d",i);
            TString chj = Form("%d",j);
            TString chk = Form("%d",k);
            TString chl = Form("%d",l);
            TString E2 = "("+PE[i]+"+"+PE[j]+"+"+PE[k]+"+"+PE[l]+")**2";
            TString PX2 = "("+PX[i]+"+"+PX[j]+"+"+PX[k]+"+"+PX[l]+")**2";
            TString PY2 = "("+PY[i]+"+"+PY[j]+"+"+PY[k]+"+"+PY[l]+")**2";
            TString PZ2 = "("+PZ[i]+"+"+PZ[j]+"+"+PZ[k]+"+"+PZ[l]+")**2";
            TString P2 = "("+PX2+"+"+PY2+"+"+PZ2+")";
            TString hid = hbase+"_"+chi+chj+chk+chl;
            TString mass = "sqrt("+E2+"-"+P2+")";
            TString fillh = mass+">>+"+hid;
            cout << "Histo Fill Stream: " << fillh << endl;
            ic++;
            c2->cd(ic);
            //TString chCuts = "abs("+PID[i]+") > 0";
            //chCuts = "(!("+PID[i]+">0 && " + PID[j] + ">0 && " + PID[k] + ">0) && !("+PID[i]+"<0 && " + PID[j] + "<0 && " + PID[k] + "<0 ))";
            //cout << chCuts << endl;
            //TCut chCut = chCuts;
            TCut allCut3 = allCut2;// && chCut;            
            tree1->Draw(fillh,allCut3);
            TString hh = "h4_"+chi+chj+chk+chl;
            setRange(hh);
            c2->Update();          
          }
        }
      }
    }

  }
  

  if(doit[3]>0 && nPart>=5){
    // Book histos
    TString hbase = "h5";
    TH1F *h5[20];
    TH1F *h5_12[20];
    TH1F *h5_13[20];
    TH1F *h5_23[20];
    int ic = 0;
    for(int ii=0; ii<nPart-4; ii++){
      for(int i=ii+1; i<nPart-3; i++){
        for(int j=i+1; j<nPart-2; j++){
          for(int k=j+1; k<nPart-1; k++){
            for(int l=k+1; l<nPart; l++){
              TString chi = Form("%d",i);
              TString chj = Form("%d",j);
              TString chk = Form("%d",k);
              TString chl = Form("%d",l);
              TString chm = Form("%d",ii);
              TString title = "Mass, Comb  " + chi + chj + chk + chl+chm;
              TString hid = hbase+"_"+chm+chi+chj+chk+chl;
              h4[ic] = new TH1F(hid,title,nbinx,low,hi);
              cout << "Booking histogram: " << hid << endl;
              ic++;
            }  
          }  
        }
      }
    }
    
    // Fill histos
    name = "5_body";
    TCanvas *c2 = new TCanvas("c2_"+name,"Plots " + name, 1000,700);
    ncomb = factorial(nPart) / (factorial(nPart-4)*factorial(4));
    if(ncomb<=4 && ncomb>1) c2->Divide(2,2);
    if(ncomb>4&&ncomb<=6) c2->Divide(3,2);
    if(ncomb>6&&ncomb<=9) c2->Divide(3,3);
    if(ncomb>9) c2->Divide(4,3);
    cout << "ncomb = " << ncomb << endl;
    
    int ic = 0;
    for(int ii=0; ii<nPart-4; ii++){
      for(int i=ii+1; i<nPart-3; i++){
        for(int j=i+1; j<nPart-2; j++){
          for(int k=j+1; k<nPart-1; k++){
            for(int l=k+1; l<nPart; l++){
              TString chi = Form("%d",i);
              TString chj = Form("%d",j);
              TString chk = Form("%d",k);
              TString chl = Form("%d",l);
              TString chm = Form("%d",ii);
              TString E2 = "("+PE[i]+"+"+PE[j]+"+"+PE[k]+"+"+PE[l]+"+"+PE[ii]+")**2";
              TString PX2 = "("+PX[i]+"+"+PX[j]+"+"+PX[k]+"+"+PX[l]+"+"+PX[ii]+")**2";
              TString PY2 = "("+PY[i]+"+"+PY[j]+"+"+PY[k]+"+"+PY[l]+"+"+PY[ii]+")**2";
              TString PZ2 = "("+PZ[i]+"+"+PZ[j]+"+"+PZ[k]+"+"+PZ[l]+"+"+PZ[ii]+")**2";
              TString P2 = "("+PX2+"+"+PY2+"+"+PZ2+")";
              TString hid = hbase+"_"+chm+chi+chj+chk+chl;
              TString mass = "sqrt("+E2+"-"+P2+")";
              TString fillh = mass+">>+"+hid;
              cout << "Histo Fill Stream: " << fillh << endl;
              ic++;
              c2->cd(ic);
              //TString chCuts = "abs("+PID[i]+") > 0";
              //chCuts = "(!("+PID[i]+">0 && " + PID[j] + ">0 && " + PID[k] + ">0) && !("+PID[i]+"<0 && " + PID[j] + "<0 && " + PID[k] + "<0 ))";
              //cout << chCuts << endl;
              //TCut chCut = chCuts;
              TCut allCut3 = allCut2;// && chCut;            
              tree1->Draw(fillh,allCut3);
              TString hh = "h5_"+chm+chi+chj+chk+chl;
              setRange(hh);
              c2->Update();          
            }
          }
        }
      }
    }
    
    //TString canvasName = "Threebody_"+swapStatus+"_"+mlow+"_"+mhi;
    //if(hardcopy) c1->Print("./"+canvasName+"_"+mode+".pdf");
  }  

  
  return;

}
