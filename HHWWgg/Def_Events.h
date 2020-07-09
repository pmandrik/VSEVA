//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul  2 21:45:38 2020 by ROOT version 6.20/04
// from TTree Def_Events/Def_Events
// found on file: /afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output/hzura_2017_EFT2_v3.root
//////////////////////////////////////////////////////////

#ifndef Def_Events_h
#define Def_Events_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TLorentzVector.h"

class Def_Events {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           N_ljets;
   Int_t           N_muons;
   Int_t           N_electrons;
   Int_t           N_leptons;
   Double_t        dR_yy;
   Double_t        dR_jj;
   Double_t        dR_WL;
   Double_t        dR_WW;
   Double_t        dR_HH;
   Double_t        dPhi_nuL;
   Double_t        m_yy;
   Double_t        y1_Et_div_m_yy;
   Double_t        y2_Et_div_m_y;
   TLorentzVector  *y1_tlv;
   TLorentzVector  *y2_tlv;
   TLorentzVector  *H_yy_tlv;
   TLorentzVector  *H_WW_tlv;
   TLorentzVector  *HWl_tlv;
   TLorentzVector  *HH_tlv;
   TLorentzVector  *ljet1_tlv;
   TLorentzVector  *ljet2_tlv;
   TLorentzVector  *W_jj_tlv;
   TLorentzVector  *W_jj_tlv_leading;
   TLorentzVector  *W_elnu_tlv;
   TLorentzVector  *mu_leading_tlv;
   TLorentzVector  *el_leading_tlv;
   TLorentzVector  *lep_leading_tlv;
   TLorentzVector  *nu_reco_tlv;
   TLorentzVector  *nu_tlv;
   Int_t           muon_channel;
   Double_t        gen_dR_yy;
   Double_t        gen_dR_jj;
   Double_t        gen_dR_WL;
   Double_t        gen_dR_WW;
   Double_t        gen_dR_HH;
   Double_t        gen_dPhi_nuL;
   Double_t        gen_m_yy;
   Double_t        gen_y1_Et_div_m_yy;
   Double_t        gen_y2_Et_div_m_yy;
   TLorentzVector  *gen_y1_tlv;
   TLorentzVector  *gen_y2_tlv;
   TLorentzVector  *gen_H_yy_tlv;
   TLorentzVector  *gen_Hi_yy_tlv;
   TLorentzVector  *gen_ljet1_tlv;
   TLorentzVector  *gen_ljet2_tlv;
   TLorentzVector  *gen_W_jj_tlv;
   TLorentzVector  *gen_lep_leading_tlv;
   TLorentzVector  *gen_W_elnu_tlv;
   TLorentzVector  *gen_H_WW_tlv;
   TLorentzVector  *gen_Hi_WW_tlv;
   TLorentzVector  *gen_nu_tlv;
   TLorentzVector  *gen_HHi_tlv;
   TLorentzVector  *gen_HHf_tlv;
   TLorentzVector  *gen_HWl_tlv;
   Int_t           gen_muon_channel;
   Double_t        dR_genreco_H_yy;
   Double_t        dR_genreco_H_WW;
   Double_t        dR_genreco_nu;
   Double_t        dR_genreco_W_jj;
   Double_t        dR_genreco_W_elnu;
   Double_t        dP_genreco_H_yy;
   Double_t        dP_genreco_H_WW;
   Double_t        dP_genreco_nu;
   Double_t        dP_genreco_W_jj;
   Double_t        dP_genreco_W_elnu;
   Double_t        weight;
   Double_t        lumiWeight;
   Double_t        weight_sf_photons_down;
   Double_t        weight_sf_photons_up;
   Double_t        weight_sf_electrons_down;
   Double_t        weight_sf_electrons_up;
   Double_t        weight_sf_muons_id_down;
   Double_t        weight_sf_muons_id_up;
   Double_t        weight_sf_muons_iso_down;
   Double_t        weight_sf_muons_iso_up;
   Double_t        weight_sf_ljets_id_down;
   Double_t        weight_sf_ljets_id_up;
   Double_t        weight_sf_ljets_btag_down;
   Double_t        weight_sf_ljets_btag_up;
   Double_t        weight_sf_bjets_id_down;
   Double_t        weight_sf_bjets_id_up;
   Double_t        weight_sf_bjets_btag_down;
   Double_t        weight_sf_bjets_btag_up;
   Double_t        weight_sf_pileup_down;
   Double_t        weight_sf_pileup_up;
   Double_t        weight_FracRV_down;
   Double_t        weight_FracRV_up;
   Double_t        weight_LooseMvaSF_down;
   Double_t        weight_LooseMvaSF_up;
   Double_t        weight_PreselSF_down;
   Double_t        weight_PreselSF_up;
   Double_t        weight_Trigger_down;
   Double_t        weight_Trigger_up;
   Double_t        weight_electronVetoSF_down;
   Double_t        weight_electronVetoSF_up;

   // List of branches
   TBranch        *b_N_ljets;   //!
   TBranch        *b_N_muons;   //!
   TBranch        *b_N_electrons;   //!
   TBranch        *b_N_leptons;   //!
   TBranch        *b_dR_yy;   //!
   TBranch        *b_dR_jj;   //!
   TBranch        *b_dR_WL;   //!
   TBranch        *b_dR_WW;   //!
   TBranch        *b_dR_HH;   //!
   TBranch        *b_dPhi_nuL;   //!
   TBranch        *b_m_yy;   //!
   TBranch        *b_y1_Et_div_m_yy;   //!
   TBranch        *b_y2_Et_div_m_y;   //!
   TBranch        *b_y1_tlv;   //!
   TBranch        *b_y2_tlv;   //!
   TBranch        *b_H_yy_tlv;   //!
   TBranch        *b_H_WW_tlv;   //!
   TBranch        *b_HWl_tlv;   //!
   TBranch        *b_HH_tlv;   //!
   TBranch        *b_ljet1_tlv;   //!
   TBranch        *b_ljet2_tlv;   //!
   TBranch        *b_W_jj_tlv;   //!
   TBranch        *b_W_jj_tlv_leading;   //!
   TBranch        *b_W_elnu_tlv;   //!
   TBranch        *b_mu_leading_tlv;   //!
   TBranch        *b_el_leading_tlv;   //!
   TBranch        *b_lep_leading_tlv;   //!
   TBranch        *b_nu_reco_tlv;   //!
   TBranch        *b_nu_tlv;   //!
   TBranch        *b_muon_channel;   //!
   TBranch        *b_gen_dR_yy;   //!
   TBranch        *b_gen_dR_jj;   //!
   TBranch        *b_gen_dR_WL;   //!
   TBranch        *b_gen_dR_WW;   //!
   TBranch        *b_gen_dR_HH;   //!
   TBranch        *b_gen_dPhi_nuL;   //!
   TBranch        *b_gen_m_yy;   //!
   TBranch        *b_gen_y1_Et_div_m_yy;   //!
   TBranch        *b_gen_y2_Et_div_m_yy;   //!
   TBranch        *b_gen_y1_tlv;   //!
   TBranch        *b_gen_y2_tlv;   //!
   TBranch        *b_gen_H_yy_tlv;   //!
   TBranch        *b_gen_Hi_yy_tlv;   //!
   TBranch        *b_gen_ljet1_tlv;   //!
   TBranch        *b_gen_ljet2_tlv;   //!
   TBranch        *b_gen_W_jj_tlv;   //!
   TBranch        *b_gen_lep_leading_tlv;   //!
   TBranch        *b_gen_W_elnu_tlv;   //!
   TBranch        *b_gen_H_WW_tlv;   //!
   TBranch        *b_gen_Hi_WW_tlv;   //!
   TBranch        *b_gen_nu_tlv;   //!
   TBranch        *b_gen_HHi_tlv;   //!
   TBranch        *b_gen_HHf_tlv;   //!
   TBranch        *b_gen_HWl_tlv;   //!
   TBranch        *b_gen_muon_channel;   //!
   TBranch        *b_dR_genreco_H_yy;   //!
   TBranch        *b_dR_genreco_H_WW;   //!
   TBranch        *b_dR_genreco_nu;   //!
   TBranch        *b_dR_genreco_W_jj;   //!
   TBranch        *b_dR_genreco_W_elnu;   //!
   TBranch        *b_dP_genreco_H_yy;   //!
   TBranch        *b_dP_genreco_H_WW;   //!
   TBranch        *b_dP_genreco_nu;   //!
   TBranch        *b_dP_genreco_W_jj;   //!
   TBranch        *b_dP_genreco_W_elnu;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_lumiWeight;   //!
   TBranch        *b_weight_sf_photons_down;   //!
   TBranch        *b_weight_sf_photons_up;   //!
   TBranch        *b_weight_sf_electrons_down;   //!
   TBranch        *b_weight_sf_electrons_up;   //!
   TBranch        *b_weight_sf_muons_id_down;   //!
   TBranch        *b_weight_sf_muons_id_up;   //!
   TBranch        *b_weight_sf_muons_iso_down;   //!
   TBranch        *b_weight_sf_muons_iso_up;   //!
   TBranch        *b_weight_sf_ljets_id_down;   //!
   TBranch        *b_weight_sf_ljets_id_up;   //!
   TBranch        *b_weight_sf_ljets_btag_down;   //!
   TBranch        *b_weight_sf_ljets_btag_up;   //!
   TBranch        *b_weight_sf_bjets_id_down;   //!
   TBranch        *b_weight_sf_bjets_id_up;   //!
   TBranch        *b_weight_sf_bjets_btag_down;   //!
   TBranch        *b_weight_sf_bjets_btag_up;   //!
   TBranch        *b_weight_sf_pileup_down;   //!
   TBranch        *b_weight_sf_pileup_up;   //!
   TBranch        *b_weight_FracRV_down;   //!
   TBranch        *b_weight_FracRV_up;   //!
   TBranch        *b_weight_LooseMvaSF_down;   //!
   TBranch        *b_weight_LooseMvaSF_up;   //!
   TBranch        *b_weight_PreselSF_down;   //!
   TBranch        *b_weight_PreselSF_up;   //!
   TBranch        *b_weight_Trigger_down;   //!
   TBranch        *b_weight_Trigger_up;   //!
   TBranch        *b_weight_electronVetoSF_down;   //!
   TBranch        *b_weight_electronVetoSF_up;   //!

   Def_Events(TTree *tree=0);
   virtual ~Def_Events();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Def_Events_cxx
Def_Events::Def_Events(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output/hzura_2017_EFT2_v3.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/afs/cern.ch/work/p/pmandrik/dihiggs/3_hzura/output/hzura_2017_EFT2_v3.root");
      }
      f->GetObject("Def_Events",tree);

   }
   Init(tree);
}

Def_Events::~Def_Events()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Def_Events::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Def_Events::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Def_Events::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   y1_tlv = 0;
   y2_tlv = 0;
   H_yy_tlv = 0;
   H_WW_tlv = 0;
   HWl_tlv = 0;
   HH_tlv = 0;
   ljet1_tlv = 0;
   ljet2_tlv = 0;
   W_jj_tlv = 0;
   W_jj_tlv_leading = 0;
   W_elnu_tlv = 0;
   mu_leading_tlv = 0;
   el_leading_tlv = 0;
   lep_leading_tlv = 0;
   nu_reco_tlv = 0;
   nu_tlv = 0;
   gen_y1_tlv = 0;
   gen_y2_tlv = 0;
   gen_H_yy_tlv = 0;
   gen_Hi_yy_tlv = 0;
   gen_ljet1_tlv = 0;
   gen_ljet2_tlv = 0;
   gen_W_jj_tlv = 0;
   gen_lep_leading_tlv = 0;
   gen_W_elnu_tlv = 0;
   gen_H_WW_tlv = 0;
   gen_Hi_WW_tlv = 0;
   gen_nu_tlv = 0;
   gen_HHi_tlv = 0;
   gen_HHf_tlv = 0;
   gen_HWl_tlv = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("N_ljets", &N_ljets, &b_N_ljets);
   fChain->SetBranchAddress("N_muons", &N_muons, &b_N_muons);
   fChain->SetBranchAddress("N_electrons", &N_electrons, &b_N_electrons);
   fChain->SetBranchAddress("N_leptons", &N_leptons, &b_N_leptons);
   fChain->SetBranchAddress("dR_yy", &dR_yy, &b_dR_yy);
   fChain->SetBranchAddress("dR_jj", &dR_jj, &b_dR_jj);
   fChain->SetBranchAddress("dR_WL", &dR_WL, &b_dR_WL);
   fChain->SetBranchAddress("dR_WW", &dR_WW, &b_dR_WW);
   fChain->SetBranchAddress("dR_HH", &dR_HH, &b_dR_HH);
   fChain->SetBranchAddress("dPhi_nuL", &dPhi_nuL, &b_dPhi_nuL);
   fChain->SetBranchAddress("m_yy", &m_yy, &b_m_yy);
   fChain->SetBranchAddress("y1_Et_div_m_yy", &y1_Et_div_m_yy, &b_y1_Et_div_m_yy);
   fChain->SetBranchAddress("y2_Et_div_m_y", &y2_Et_div_m_y, &b_y2_Et_div_m_y);
   fChain->SetBranchAddress("y1_tlv", &y1_tlv, &b_y1_tlv);
   fChain->SetBranchAddress("y2_tlv", &y2_tlv, &b_y2_tlv);
   fChain->SetBranchAddress("H_yy_tlv", &H_yy_tlv, &b_H_yy_tlv);
   fChain->SetBranchAddress("H_WW_tlv", &H_WW_tlv, &b_H_WW_tlv);
   fChain->SetBranchAddress("HWl_tlv", &HWl_tlv, &b_HWl_tlv);
   fChain->SetBranchAddress("HH_tlv", &HH_tlv, &b_HH_tlv);
   fChain->SetBranchAddress("ljet1_tlv", &ljet1_tlv, &b_ljet1_tlv);
   fChain->SetBranchAddress("ljet2_tlv", &ljet2_tlv, &b_ljet2_tlv);
   fChain->SetBranchAddress("W_jj_tlv", &W_jj_tlv, &b_W_jj_tlv);
   fChain->SetBranchAddress("W_jj_tlv_leading", &W_jj_tlv_leading, &b_W_jj_tlv_leading);
   fChain->SetBranchAddress("W_elnu_tlv", &W_elnu_tlv, &b_W_elnu_tlv);
   fChain->SetBranchAddress("mu_leading_tlv", &mu_leading_tlv, &b_mu_leading_tlv);
   fChain->SetBranchAddress("el_leading_tlv", &el_leading_tlv, &b_el_leading_tlv);
   fChain->SetBranchAddress("lep_leading_tlv", &lep_leading_tlv, &b_lep_leading_tlv);
   fChain->SetBranchAddress("nu_reco_tlv", &nu_reco_tlv, &b_nu_reco_tlv);
   fChain->SetBranchAddress("nu_tlv", &nu_tlv, &b_nu_tlv);
   fChain->SetBranchAddress("muon_channel", &muon_channel, &b_muon_channel);
   fChain->SetBranchAddress("gen_dR_yy", &gen_dR_yy, &b_gen_dR_yy);
   fChain->SetBranchAddress("gen_dR_jj", &gen_dR_jj, &b_gen_dR_jj);
   fChain->SetBranchAddress("gen_dR_WL", &gen_dR_WL, &b_gen_dR_WL);
   fChain->SetBranchAddress("gen_dR_WW", &gen_dR_WW, &b_gen_dR_WW);
   fChain->SetBranchAddress("gen_dR_HH", &gen_dR_HH, &b_gen_dR_HH);
   fChain->SetBranchAddress("gen_dPhi_nuL", &gen_dPhi_nuL, &b_gen_dPhi_nuL);
   fChain->SetBranchAddress("gen_m_yy", &gen_m_yy, &b_gen_m_yy);
   fChain->SetBranchAddress("gen_y1_Et_div_m_yy", &gen_y1_Et_div_m_yy, &b_gen_y1_Et_div_m_yy);
   fChain->SetBranchAddress("gen_y2_Et_div_m_yy", &gen_y2_Et_div_m_yy, &b_gen_y2_Et_div_m_yy);
   fChain->SetBranchAddress("gen_y1_tlv", &gen_y1_tlv, &b_gen_y1_tlv);
   fChain->SetBranchAddress("gen_y2_tlv", &gen_y2_tlv, &b_gen_y2_tlv);
   fChain->SetBranchAddress("gen_H_yy_tlv", &gen_H_yy_tlv, &b_gen_H_yy_tlv);
   fChain->SetBranchAddress("gen_Hi_yy_tlv", &gen_Hi_yy_tlv, &b_gen_Hi_yy_tlv);
   fChain->SetBranchAddress("gen_ljet1_tlv", &gen_ljet1_tlv, &b_gen_ljet1_tlv);
   fChain->SetBranchAddress("gen_ljet2_tlv", &gen_ljet2_tlv, &b_gen_ljet2_tlv);
   fChain->SetBranchAddress("gen_W_jj_tlv", &gen_W_jj_tlv, &b_gen_W_jj_tlv);
   fChain->SetBranchAddress("gen_lep_leading_tlv", &gen_lep_leading_tlv, &b_gen_lep_leading_tlv);
   fChain->SetBranchAddress("gen_W_elnu_tlv", &gen_W_elnu_tlv, &b_gen_W_elnu_tlv);
   fChain->SetBranchAddress("gen_H_WW_tlv", &gen_H_WW_tlv, &b_gen_H_WW_tlv);
   fChain->SetBranchAddress("gen_Hi_WW_tlv", &gen_Hi_WW_tlv, &b_gen_Hi_WW_tlv);
   fChain->SetBranchAddress("gen_nu_tlv", &gen_nu_tlv, &b_gen_nu_tlv);
   fChain->SetBranchAddress("gen_HHi_tlv", &gen_HHi_tlv, &b_gen_HHi_tlv);
   fChain->SetBranchAddress("gen_HHf_tlv", &gen_HHf_tlv, &b_gen_HHf_tlv);
   fChain->SetBranchAddress("gen_HWl_tlv", &gen_HWl_tlv, &b_gen_HWl_tlv);
   fChain->SetBranchAddress("gen_muon_channel", &gen_muon_channel, &b_gen_muon_channel);
   fChain->SetBranchAddress("dR_genreco_H_yy", &dR_genreco_H_yy, &b_dR_genreco_H_yy);
   fChain->SetBranchAddress("dR_genreco_H_WW", &dR_genreco_H_WW, &b_dR_genreco_H_WW);
   fChain->SetBranchAddress("dR_genreco_nu", &dR_genreco_nu, &b_dR_genreco_nu);
   fChain->SetBranchAddress("dR_genreco_W_jj", &dR_genreco_W_jj, &b_dR_genreco_W_jj);
   fChain->SetBranchAddress("dR_genreco_W_elnu", &dR_genreco_W_elnu, &b_dR_genreco_W_elnu);
   fChain->SetBranchAddress("dP_genreco_H_yy", &dP_genreco_H_yy, &b_dP_genreco_H_yy);
   fChain->SetBranchAddress("dP_genreco_H_WW", &dP_genreco_H_WW, &b_dP_genreco_H_WW);
   fChain->SetBranchAddress("dP_genreco_nu", &dP_genreco_nu, &b_dP_genreco_nu);
   fChain->SetBranchAddress("dP_genreco_W_jj", &dP_genreco_W_jj, &b_dP_genreco_W_jj);
   fChain->SetBranchAddress("dP_genreco_W_elnu", &dP_genreco_W_elnu, &b_dP_genreco_W_elnu);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
   fChain->SetBranchAddress("weight_sf_photons_down", &weight_sf_photons_down, &b_weight_sf_photons_down);
   fChain->SetBranchAddress("weight_sf_photons_up", &weight_sf_photons_up, &b_weight_sf_photons_up);
   fChain->SetBranchAddress("weight_sf_electrons_down", &weight_sf_electrons_down, &b_weight_sf_electrons_down);
   fChain->SetBranchAddress("weight_sf_electrons_up", &weight_sf_electrons_up, &b_weight_sf_electrons_up);
   fChain->SetBranchAddress("weight_sf_muons_id_down", &weight_sf_muons_id_down, &b_weight_sf_muons_id_down);
   fChain->SetBranchAddress("weight_sf_muons_id_up", &weight_sf_muons_id_up, &b_weight_sf_muons_id_up);
   fChain->SetBranchAddress("weight_sf_muons_iso_down", &weight_sf_muons_iso_down, &b_weight_sf_muons_iso_down);
   fChain->SetBranchAddress("weight_sf_muons_iso_up", &weight_sf_muons_iso_up, &b_weight_sf_muons_iso_up);
   fChain->SetBranchAddress("weight_sf_ljets_id_down", &weight_sf_ljets_id_down, &b_weight_sf_ljets_id_down);
   fChain->SetBranchAddress("weight_sf_ljets_id_up", &weight_sf_ljets_id_up, &b_weight_sf_ljets_id_up);
   fChain->SetBranchAddress("weight_sf_ljets_btag_down", &weight_sf_ljets_btag_down, &b_weight_sf_ljets_btag_down);
   fChain->SetBranchAddress("weight_sf_ljets_btag_up", &weight_sf_ljets_btag_up, &b_weight_sf_ljets_btag_up);
   fChain->SetBranchAddress("weight_sf_bjets_id_down", &weight_sf_bjets_id_down, &b_weight_sf_bjets_id_down);
   fChain->SetBranchAddress("weight_sf_bjets_id_up", &weight_sf_bjets_id_up, &b_weight_sf_bjets_id_up);
   fChain->SetBranchAddress("weight_sf_bjets_btag_down", &weight_sf_bjets_btag_down, &b_weight_sf_bjets_btag_down);
   fChain->SetBranchAddress("weight_sf_bjets_btag_up", &weight_sf_bjets_btag_up, &b_weight_sf_bjets_btag_up);
   fChain->SetBranchAddress("weight_sf_pileup_down", &weight_sf_pileup_down, &b_weight_sf_pileup_down);
   fChain->SetBranchAddress("weight_sf_pileup_up", &weight_sf_pileup_up, &b_weight_sf_pileup_up);
   fChain->SetBranchAddress("weight_FracRV_down", &weight_FracRV_down, &b_weight_FracRV_down);
   fChain->SetBranchAddress("weight_FracRV_up", &weight_FracRV_up, &b_weight_FracRV_up);
   fChain->SetBranchAddress("weight_LooseMvaSF_down", &weight_LooseMvaSF_down, &b_weight_LooseMvaSF_down);
   fChain->SetBranchAddress("weight_LooseMvaSF_up", &weight_LooseMvaSF_up, &b_weight_LooseMvaSF_up);
   fChain->SetBranchAddress("weight_PreselSF_down", &weight_PreselSF_down, &b_weight_PreselSF_down);
   fChain->SetBranchAddress("weight_PreselSF_up", &weight_PreselSF_up, &b_weight_PreselSF_up);
   fChain->SetBranchAddress("weight_Trigger_down", &weight_Trigger_down, &b_weight_Trigger_down);
   fChain->SetBranchAddress("weight_Trigger_up", &weight_Trigger_up, &b_weight_Trigger_up);
   fChain->SetBranchAddress("weight_electronVetoSF_down", &weight_electronVetoSF_down, &b_weight_electronVetoSF_down);
   fChain->SetBranchAddress("weight_electronVetoSF_up", &weight_electronVetoSF_up, &b_weight_electronVetoSF_up);
   Notify();
}

Bool_t Def_Events::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Def_Events::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Def_Events::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Def_Events_cxx
