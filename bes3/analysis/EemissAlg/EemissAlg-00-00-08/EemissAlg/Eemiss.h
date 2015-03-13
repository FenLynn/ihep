#ifndef Physics_Analysis_Eemiss_H
#define Physics_Analysis_Eemiss_H 

#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/NTuple.h"
//#include "VertexFit/ReadBeamParFromDb.h"


#include <string>
#include <TTree.h>
#include <TROOT.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TClonesArray.h>
//#include "DTagTool/DTagTool.h"


class Eemiss:public Algorithm{

	public:
		Eemiss(const std::string& name, ISvcLocator* pSvcLocator);
		StatusCode initialize();
		StatusCode execute();
		StatusCode finalize();  

	private:

		Double_t m_Ecms;
		Double_t m_EnergySpread;

		std::string m_OutputFileName;
		TFile *saveFile;
		TTree *TreeAna;
		TTree *genTree;
		TTree *TopoTree;
		TTree *NbInfo;

		int m_saveTopo;
		int m_saveMCTruth;
		int m_saveTopoTree;
		int m_saveNbInfo;
		int m_nbTrk;

		int runid;
		int evtid;
		int nevt;
		int nNEUTRAL;
		int nCHARGED;
		int nTRACKS;
		int nGamma;

		//below is origin variable
		// Declare r0, z0 cut for charged tracks
		double m_vr0cut;
		double m_vz0cut;
		double m_trkAngCut;
		double m_gammaAngleCut;
		double m_barrelEnergyThreshold;
		double m_endEnergyThreshold;
		int m_checkRatio;
		int m_checkMuc;
		int m_check4C;
		int check_tof;
		
		int chk1C;
		int chk4C;

		int m_idxmc;
		int m_drank[500];
		int m_pdgid[500];
		int m_motheridx[500];
		int m_motherpid[500];
		int isSigee;
		int numgam;
		int numep;
		int numem;
		TLorentzVector *xp;
		TLorentzVector *xm;
		TClonesArray *mcgam; 	

		double vx[3],Evx[3];
		double costheta_chrgd[2];
		double Rxy[2];
		double Rz[2];
		double Rvxy[2];
		double Rvz[2];
		
		//for miss ET
		double mmiss;
		double mmiss2;
		double umiss;
		double emiss;
		double pmiss;
		double ptr;
		double ptr2;
		double ptg2;
		double costhe_u;
		
		double costhe_ee;
		double sinthe_ee;
		double ee_ivm;

		//pid info.
		double chiDeDx[2][5];
		double chiTof[2][5];
		double chiTof1[2][5];
		double chiTof2[2][5];
		double chisq_pid[2][5];
		double prob[2][5];
		
		double vtxchisq;	
		
		//double vtxchisq[2];
		//double chi4C[2];
		
		TClonesArray *p_all; 	
		TClonesArray *p_e1; 	
		TClonesArray *p_e2; 	
		TClonesArray *p_u; 	
		

		double tof[2];
		double dtof;

		//e/p info
		int m_hitsTrk[2];
		double m_deTrk[2];
		double m_pTrk[2];
		double m_epTrk[2];
		


		//for sys uncertainties
		int stat1C;
		double chi1C;
		
		
		double p_lphotonang;
		double p_hphotonang;
		int f_cktpang;
		double p_emiss;
		double p_missang;
		double epcut;

		//muc info
		/*
		int m_mucstat[4];
		int m_kalbrLastLayer[4];
		int m_kalecLastLayer[4];
		int m_layerMuc[4];
		int m_kaldof[4];
		double m_depMuc[4];
		double m_kalrechi2[4];
		double m_kaldep[4];
		double m_angMuc[4];
		*/

};

#endif 
