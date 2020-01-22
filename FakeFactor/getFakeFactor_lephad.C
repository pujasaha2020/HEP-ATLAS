#include "TFile.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TLegend.h"
#include "TDirectory.h"
#include "TAxis.h"

#include <iostream>
#include <sstream>

void getFakeFactor_lephad()
{
  gROOT->SetBatch(1);

  //std::vector<std::string> samples={"data","ttbar","singletop_s","singletop_t","singletop_Wt","WW","WZ","ZZ","WtaunuL_v221","WtaunuC_v221","WtaunuB_v221","ZtautauL_v221","ZtautauC_v221","ZtautauB_v221"};
  //std::vector<std::string> histname={"data","ttbar","stops","stopt","stopWt","WW_improved","WZ_improved","ZZ_improved","W","W","W","Z","Z","Z"};

  std::vector<std::string> samples={"data","singletop","ttbar","WtaunuL","WtaunuC","WtaunuB","Wtaunu","WmunuL","WmunuC","WmunuB","Wmunu","WenuL","WenuC","WenuB","Wenu","ZtautauL","ZtautauC","ZtautauB","Ztautau","ZmumuL","ZmumuC","ZmumuB","Zmumu","ZeeL","ZeeC","ZeeB","Zee","ZqqZll","WplvWmqq","WpqqWmlv","WqqZll","WqqZvv","WlvZqq"};//,"ShDYtautau","ShDYmumu","ShDYee"};


  std::vector<std::string> histname={"data","singletop","ttbar","Wt","Wt","Wt","Wt","W","W","W","W","W","W","W","W",
				     "Ztt","Ztt","Ztt","Ztt","Z","Z","Z","Z","Z","Z","Z","Z","ZZ","WW","WW","WZ","WZ","WZ"};//,"stopt","stops","stopWt","ZZ","ZZ","WW","WW","WZ","WZ"};//"Zmumu","Zee"};


  std::vector<std::string> hflavour={"l","cl","cc","bl","bc","bb"};
  std::vector<std::string> htop={"stopt","stops","stopWt"};
  TFile *f_SR[100];
  TFile *f_CR[100];
  std::string root_CR="/usatlas/u/psaha/usatlasdata/2018_analysis/run/23rdJuly_CR/fetch/hist-";
  //"/usatlas/u/psaha/usatlasdata/VBF_bbtautau_lephad_Rel21_v5/run/27thMay_CR_85WP/fetch/hist-";
  std::string root_SR="/usatlas/u/psaha/usatlasdata/2018_analysis/run/23rdJuly_SR/fetch/hist-";
  //"/usatlas/u/psaha/usatlasdata/VBF_bbtautau_lephad_Rel21_v5/run/27thMay_SR_85WP/fetch/hist-";

  
  std::string temp_str1="";
  std::string temp_str2="";
  for(unsigned int i=0;i<samples.size();i++){
    temp_str1=root_CR+samples.at(i)+"-0.root";
    std::cout << "Opening: " << temp_str1 << " hist_name " << histname.at(i) << std::endl;
    f_CR[i] = TFile::Open(temp_str1.c_str(),"READ");
    temp_str1=root_SR+samples.at(i)+"-0.root";
    std::cout << "Opening: " << temp_str1 << " hist_name " << histname.at(i) << std::endl;
    f_SR[i] = TFile::Open(temp_str1.c_str(),"READ");
  }

 
  TH1F *hSR[300];
  TH1F *hCR[300];
  
  TH1F *hSRFakes[100];
  TH1F *hCRFakes[100];

  int asSR=0,asCR=0;
  int nSR=0,nCR=0;
  int nSRFakes=0,nCRFakes=0;
  bool hasZ;
  bool hasW;
  bool hasSingleTop;
  TH1F* hist2;
  std:: cout << " ############### REAL TAU CONTRIBUTION IN SR AND CR #######################" << std:: endl;
  for(unsigned int i=0;i<samples.size();i++){
         
      std::cout<< "SAMPLE NAME"<< samples.at(i)<<std::endl;       
      if(samples.at(i).find("Wtaunu") != std::string::npos || samples.at(i).find("Wmunu") != std::string::npos || samples.at(i).find("Wenu") != std::string::npos)hasW=1;
      else hasW =0;

      if(samples.at(i).find("Ztautau") != std::string::npos || samples.at(i).find("Zmumu") != std::string::npos || samples.at(i).find("Zee") != std::string::npos) hasZ=1;
      else hasZ =0;
      
      if(samples.at(i).find("singletop") != std::string::npos ) hasSingleTop=1;
      else hasSingleTop =0;

      std::cout << "hasW ? " << hasW << " hasZ ? " << hasZ << " i " << i << std::endl;
      if(!hasZ && !hasW && !hasSingleTop){
        
       
        temp_str1=histname.at(i)+"_2tag0pjet_0ptv_OS_WtCR_FakeFactor_1prongElectron_tauPt";
        temp_str2=histname.at(i)+"_2tag0pjet_0ptv_OS_WtCR_FakeFactor_1prongmuon_tauPt";
        std::cout << "temp str1" << temp_str1 << std::endl;
        std::cout << "temp str2" << temp_str2 << std::endl;
        if(f_SR[i]->GetListOfKeys()->Contains(temp_str1.c_str())&& f_SR[i]->GetListOfKeys()->Contains(temp_str2.c_str()) ){
          hSR[nSR]= (TH1F*) f_SR[i]->Get(temp_str1.c_str());
          hist2= (TH1F*) f_SR[i]->Get(temp_str2.c_str());
          hSR[nSR]->Add(hist2);//->Add(f_SR[i]->Get(temp_str2.c_str()));
          std::cout << "hSR->Integral: " << hSR[nSR]->Integral(0,11) << std::endl;
          nSR++;
        }
        else{ std::cout << "not found" << std::endl;}

        temp_str1=histname.at(i)+"_2tag0pjet_0ptv_OS_WtAntitauCR_FakeFactor_1prongElectron_tauPt";
       	temp_str2=histname.at(i)+"_2tag0pjet_0ptv_OS_WtAntitauCR_FakeFactor_1prongmuon_tauPt";
        std::cout << "temp str1" << temp_str1 << std::endl;
        std::cout << "temp str2" << temp_str2 << std::endl;
        if(f_CR[i]->GetListOfKeys()->Contains(temp_str1.c_str())&& f_CR[i]->GetListOfKeys()->Contains(temp_str2.c_str()) ){
          hCR[nCR]=(TH1F*)f_CR[i]->Get(temp_str1.c_str());
          hist2= (TH1F*)f_CR[i]->Get(temp_str2.c_str());
          hCR[nCR]->Add(hist2);
          std::cout << "hCR->Integral: " << hCR[nCR]->Integral() << std::endl;
          nCR++;
        }
        else{ std::cout << "not found" << std::endl;}
        }
       else if(hasSingleTop){
         for(unsigned int k=0;k<3;k++){

           temp_str1=htop.at(k)+"_2tag0pjet_0ptv_OS_WtCR_FakeFactor_1prongElectron_tauPt";
           temp_str2=htop.at(k)+"_2tag0pjet_0ptv_OS_WtCR_FakeFactor_1prongmuon_tauPt";
           std::cout << "temp str1" << temp_str1 << std::endl;
           std::cout << "temp str1" << temp_str2 << std::endl;
           if(f_SR[i]->GetListOfKeys()->Contains(temp_str2.c_str())){   //||f_SR[i]->GetListOfKeys()->Contains(temp_str2.c_str())){
              hSR[nSR]=(TH1F*)f_SR[i]->Get(temp_str2.c_str());
              //hist2= (TH1F*)f_SR[i]->Get(temp_str2.c_str());
              //hSR[nSR]->Add(hist2);
              std::cout << "hSR->Integral: " << hSR[nSR]->Integral() << " flv: " << htop.at(k)  << std::endl;
              nSR++;
              
           }
           else{ std::cout << "not found" << std::endl;}
           temp_str1=htop.at(k)+"_2tag0pjet_0ptv_OS_WtAntitauCR_FakeFactor_1prongElectron_tauPt";
           temp_str2=htop.at(k)+"_2tag0pjet_0ptv_OS_WtAntitauCR_FakeFactor_1prongmuon_tauPt";
           std::cout << "temp str1" << temp_str1 << std::endl;
           std::cout << "temp str2" << temp_str2 << std::endl;
           if(f_CR[i]->GetListOfKeys()->Contains(temp_str2.c_str())){  // || f_CR[i]->GetListOfKeys()->Contains(temp_str2.c_str()) ){
              hCR[nCR]=(TH1F*)f_CR[i]->Get(temp_str2.c_str());
              //hist2= (TH1F*)f_CR[i]->Get(temp_str2.c_str());
              //hCR[nCR]->Add(hist2);
              std::cout << "hCR->Integral: " << hCR[nCR]->Integral() << " flv: " << htop.at(k)  << std::endl;
              nCR++;
           }
           else{ std::cout << "not found" << std::endl;}

         }
         }
     else{
        
        int shiftSR=asSR;
        int shiftCR=asCR;
        for(unsigned int j=0;j<6;j++){
           
           temp_str1=histname.at(i)+hflavour.at(j)+"_2tag0pjet_0ptv_OS_WtCR_FakeFactor_1prongElectron_tauPt";
           temp_str2=histname.at(i)+hflavour.at(j)+"_2tag0pjet_0ptv_OS_WtCR_FakeFactor_1prongmuon_tauPt";
           std::cout << "temp str1" << temp_str1 << std::endl;
           std::cout << "temp str2" << temp_str2 << std::endl;
           if(f_SR[i]->GetListOfKeys()->Contains(temp_str1.c_str())&&f_SR[i]->GetListOfKeys()->Contains(temp_str2.c_str())){
           hSR[nSR]=(TH1F*)f_SR[i]->Get(temp_str1.c_str());
           hist2= (TH1F*)f_SR[i]->Get(temp_str2.c_str());
              hSR[nSR]->Add(hist2);
              std::cout << "hSR->Integral: " << hSR[nSR]->Integral() << " flv: " << hflavour.at(j) << " i (+shift) " << i+shiftSR << std::endl;
              shiftSR++;
              nSR++;
           }else{ std::cout << "not found" << std::endl;}
           if(f_SR[i]->GetListOfKeys()->Contains(temp_str1.c_str())&& !f_SR[i]->GetListOfKeys()->Contains(temp_str2.c_str())){
             hSR[nSR]=(TH1F*)f_SR[i]->Get(temp_str1.c_str());
             std::cout << "hSR->Integral: " << hSR[nSR]->Integral() << " flv: " << hflavour.at(j) << " i (+shift) " << i+shiftSR << std::endl;
             shiftSR++;
             nSR++;
             }else{ std::cout << "not found" << std::endl;}
           if(!f_SR[i]->GetListOfKeys()->Contains(temp_str1.c_str())&& f_SR[i]->GetListOfKeys()->Contains(temp_str2.c_str())){
             hSR[nSR]=(TH1F*)f_SR[i]->Get(temp_str2.c_str());
             std::cout << "hSR->Integral: " << hSR[nSR]->Integral() << " flv: " << hflavour.at(j) << " i (+shift) " << i+shiftSR << std::endl;
             shiftSR++;
      	      nSR++;
             }
           else{ std::cout << "not found" << std::endl;}
           temp_str1=histname.at(i)+hflavour.at(j)+"_2tag0pjet_0ptv_OS_WtAntitauCR_FakeFactor_1prongElectron_tauPt";
           temp_str2=histname.at(i)+hflavour.at(j)+"_2tag0pjet_0ptv_OS_WtAntitauCR_FakeFactor_1prongmuon_tauPt";
           std::cout << "temp str1" << temp_str1 << std::endl;
           std::cout << "temp str2" << temp_str2 << std::endl;
           if(f_CR[i]->GetListOfKeys()->Contains(temp_str1.c_str()) && f_CR[i]->GetListOfKeys()->Contains(temp_str2.c_str())){
              hCR[nCR]=(TH1F*)f_CR[i]->Get(temp_str1.c_str());
              hist2= (TH1F*)f_CR[i]->Get(temp_str2.c_str());
              hCR[nCR]->Add(hist2);
              std::cout << "hCR->Integral: " << hCR[nCR]->Integral() << " flv: " << hflavour.at(j) << " i (+shift) " << i+shiftCR << std::endl;
              shiftCR++;
              nCR++;
           }else{ std::cout << "not found" << std::endl;}
           if(f_CR[i]->GetListOfKeys()->Contains(temp_str1.c_str()) && !f_CR[i]->GetListOfKeys()->Contains(temp_str2.c_str())){
              hCR[nCR]=(TH1F*)f_CR[i]->Get(temp_str1.c_str());
              std::cout << "hCR->Integral: " << hCR[nCR]->Integral() << " flv: " << hflavour.at(j) << " i (+shift) " << i+shiftCR << std::endl;
              shiftCR++;
              nCR++;
           }else{ std::cout << "not found" << std::endl;}
           if(!f_CR[i]->GetListOfKeys()->Contains(temp_str1.c_str()) && f_CR[i]->GetListOfKeys()->Contains(temp_str2.c_str())){
              hCR[nCR]=(TH1F*)f_CR[i]->Get(temp_str2.c_str());
              std::cout << "hCR->Integral: " << hCR[nCR]->Integral() << " flv: " << hflavour.at(j) << " i (+shift) " << i+shiftCR << std::endl;
              shiftCR++;
              nCR++;
           }
           else{ std::cout << "not found" << std::endl;}
        }
        
        
        asSR=shiftSR-1;
        asCR=shiftCR-1;
     }
  }


  std:: cout << "in REAL TAU " << "nSR" << nSR << "nCR" << nCR <<std::endl;


  std::	cout <<	" ############### FAKE FACTOR CALCULATION  #######################" << std:: endl;


  TFile *g = TFile::Open("FF_1prong_ttbar_23rdJuly_MC16e.root","RECREATE");
  
  //TLegend *l=new TLegend(0.7,0.7,0.9,0.9);

  int nBinsX= 9;      
  
  std::cout << "nBinsX: " << nBinsX  << std::endl;

  float fakeFactorsWjets[nBinsX];

  
 
  float FF_pT1_Edges[10]={20.0, 25.0, 30.0, 35.0, 40.0, 50.0, 60.0, 70.0, 120.0, 200.0};


  stringstream hname;

  TCanvas *c=new TCanvas("c","",800,600);

  
  float nMCBKGSR[nBinsX];
  float nMCBKGCR[nBinsX];

    std::cout << "Data SR integral: " << hSR[0]->Integral() << std::endl;
    std::cout << "Data CR integral: " << hCR[0]->Integral() << std::endl;

    
  TH1F *mcBkgSR = (TH1F*)hSR[0]->Clone();
  mcBkgSR->Reset();
  TH1F *mcBkgCR = (TH1F*)hCR[0]->Clone();
  mcBkgCR->Reset();

  std::cout << " nSR " << nSR << std::endl;
  
  for(unsigned int i=1;i<nSR;i++){
     if(hSR[i] != NULL) mcBkgSR->Add(hSR[i]);
  }
  
  for(unsigned int i=1;i<nCR;i++){
     if(hCR[i] != NULL) mcBkgCR->Add(hCR[i]);
  }

 std::cout << "***DIRCT ADDING*** Background  SR integral: " << mcBkgSR->Integral() << std::endl;
 std::cout << "***DIRCT ADDING*** Background  CR integral: " << mcBkgCR ->Integral() << std::endl;


  
  for(unsigned int j=1;j<nBinsX+1; j++){
    
        
        nMCBKGSR[j]=0;
        nMCBKGCR[j]=0;
        
        std::cout << "*******COMPARING DIRECT AND BIN-BY-BIN ADDING RESULT******"<<std::endl;
        std::cout << "mcbkgSR: " << mcBkgSR->GetBinContent(j) << std::endl;
        std::cout << "mcbkgCR: " << mcBkgCR->GetBinContent(j) << std::endl;
        

        std::cout << "data SR: " << hSR[0]->GetBinContent(j) << std::endl;
        std::cout << "data CR: " << hCR[0]->GetBinContent(j) << std::endl;
        for(unsigned int i=1;i<nSR;i++){
           nMCBKGSR[j]+=hSR[i]->GetBinContent(j);
        }
        for(unsigned int i=1;i<nCR;i++){
           nMCBKGCR[j]+=hCR[i]->GetBinContent(j);
        }
        std::cout << "nMBBKGSR= " << nMCBKGSR[j] << " nMBBKGCR= " << nMCBKGCR[j] << std::endl;
        std::cout << "*******COMPARISON ENDS HERE******"<<std::endl;
        
     }
  





  float nDataSubSR[nBinsX];
  float nDataSubCR[nBinsX];

  //TH1F *fakes_Wt = (TH1F*)hSR[0]->Clone();
  //fakes_Wt->Reset();

     hSR[0]->Sumw2();
     mcBkgSR->Sumw2();
     TH1F* nu=(TH1F*)hSR[0]->Clone();
     nu->Add(mcBkgSR,-1);
     nu->Sumw2();
     TH1F* di=(TH1F*)hCR[0]->Clone();
     di->Add(mcBkgCR,-1);
     TH1F *fakes_Wt = (TH1F*)nu->Clone();
     fakes_Wt->Sumw2();  
     fakes_Wt->Divide(di);
  

 // l->Draw();

 // c->SaveAs("FF2.png");
  //std::cout << "out loop" << std::endl;

  g->cd();
  //hname.str("");
  fakes_Wt->Draw();
  fakes_Wt->Write("combineFF");
  c->SaveAs("FF_1prong_ttbar_23rdJuly_MC16e.png");
  std::cout << "out loop" << std::endl;
  g->Close();

}
