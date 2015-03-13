#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "VertexFit/IVertexDbSvc.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/IHistogramSvc.h"

#include "EventModel/EventModel.h"
#include "EventModel/Event.h"
#include "McTruth/McParticle.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "DstEvent/TofHitStatus.h"
#include "EventModel/EventHeader.h"

#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"

#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
//#include "SimplePIDSvc/ISimplePIDSvc.h"
//#include "DTagTool/DTagTool.h"

using CLHEP::Hep3Vector;
using CLHEP::Hep2Vector;
using CLHEP::HepLorentzVector;
#include "CLHEP/Geometry/Point3D.h"
#ifndef ENABLE_BACKWARDS_COMPATIBILITY
typedef HepGeom::Point3D<double> HepPoint3D;
#endif

#include "EemissAlg/Eemiss.h"
#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/Helix.h"
#include "ParticleID/ParticleID.h"

#include "TMath.h"
#include <vector>
#include <iostream>
#include <fstream>

//const double twopi = 6.2831853;
//const double pi = 3.1415927;
const double mpi = 0.13957;
const double mmu = 0.105658;
const double me = 0.000511;
const double xmass[5] = {0.000511, 0.105658, 0.139570,0.493677, 0.938272};

//const double velc = 29.9792458;  tof_path unit in cm.
const double velc = 299.792458;   // tof path unit in mm

typedef std::vector<int> Vint;
typedef std::vector<HepLorentzVector> Vp4;

//int Ncut0,Ncut1,Ncut2,Ncut3,Ncut4,Ncut5,Ncut6,Ncut7,Ncut8,Ncut9,Ng1,Ng2,Ng3;
int Ncut0 = 0;		//total event
int Ncut1 = 0;		//Pass good charged tracks cut
int Ncut2 = 0;		//Pass good photon
int Ncut3 = 0;	
int Ncut4 = 0;		
int Ncut5 = 0;	
int Ncut6 = 0;		
int Ncut7 = 0;
int Ncut8 = 0;
int Ncut9 = 0;
int Ncut10 = 0;

int vfit_stat=1;


int NGam1 = 0;
int NGam2 = 0;
int NGamA2 = 0;

/////////////////////////////////////////////////////////////////////////////

Eemiss::Eemiss(const std::string& name, ISvcLocator* pSvcLocator) :
	Algorithm(name, pSvcLocator) {

		//Declare the properties
		declareProperty("OutputFileName",  m_OutputFileName = "Eemiss_test.root");
		declareProperty("Ecms",  m_Ecms = 3.097);
		//declareProperty("EnergySpread",  m_EnergySpread = 0.0011);
		declareProperty("saveTopo", m_saveTopo = 1);//need to be re-evaluated when running different samples(1 for MC)
		declareProperty("saveTopoTree", m_saveTopoTree = 0);//need to be re-evaluated when running different samples(1 for MC)
		declareProperty("saveMCTruth", m_saveMCTruth = 1);//need to be re-evaluated when running different samples(only 1 for exclusiveMC)
		declareProperty("saveNbInfo", m_saveNbInfo = 1);//need to be re-evaluated when running different samples(1 for MC)
		declareProperty("nbOfTrack",m_nbTrk = 2);//need to re-eevaluated when the number of tracks has changed.
		//charged track
		declareProperty("Vr0cut", m_vr0cut=1.0);
		declareProperty("Vz0cut", m_vz0cut=10.0);
		declareProperty("TrkAngCut", m_trkAngCut=0.93);
		//good photon
		declareProperty("GammaAngleCut", m_gammaAngleCut=10.0);
		declareProperty("BarrelEnergyThreshold", m_barrelEnergyThreshold=0.025);
		declareProperty("EndEnergyThreshold",m_endEnergyThreshold=0.050);

		declareProperty("CheckRatio",m_checkRatio = 1);
		declareProperty("Check4C",m_check4C = 0);
		declareProperty("CheckMuc",m_checkMuc = 0);
		declareProperty("Check_tof",check_tof = 0);
		declareProperty("chk1C",chk1C = 1);
		declareProperty("chk4C",chk4C = 0);

		//for sys uncertainties
		declareProperty("p_lphotonang",p_lphotonang=0.86);
		declareProperty("p_hphotonang",p_hphotonang=0.93);
		declareProperty("f_cktpang",f_cktpang=0);
		declareProperty("p_emiss",p_emiss=0.025);
		declareProperty("p_missang",p_missang=0.8);
		declareProperty("epcut",p_missang=0.8);
	}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Eemiss::initialize(){
	MsgStream log(msgSvc(), name());
	std::cout<<"initialize has started!"<<std::endl;
	log << MSG::INFO << "in initialize()" << endmsg;
	StatusCode status;

	//Output name
	TString s_OutputFileName(m_OutputFileName);

	//Tree and File Modified
	saveFile = new TFile(s_OutputFileName, "recreate");
	TreeAna = new TTree("save", "save");
	NbInfo = new TTree("nbinfo","nbinfo");
	TopoTree = new TTree("topoall","topoall");

	//lorentz vector
	p_all=new TClonesArray("TVector3");
	p_e1=new TClonesArray("TLorentzVector");
	p_e2=new TClonesArray("TLorentzVector");
	p_u=new TClonesArray("TLorentzVector");
	mcgam=new TClonesArray("TLorentzVector");

	xp=new TLorentzVector();
	xm=new TLorentzVector();

	//mc info
	if(m_saveTopo == 1)
	{
		TreeAna->Branch("indexmc", &m_idxmc, "indexmc/I");
		TreeAna->Branch("pdgid", m_pdgid, "pdgid[indexmc]/I");
		TreeAna->Branch("drank", m_drank, "drank[indexmc]/I");
		TreeAna->Branch("motheridx", m_motheridx, "motheridx[indexmc]/I");
		TreeAna->Branch("motherpid", m_motherpid, "motherpid[indexmc]/I");
	}
	
	if(m_saveTopoTree == 1)
	{
		TopoTree->Branch("indexmc", &m_idxmc, "indexmc/I");
		TopoTree->Branch("pdgid", m_pdgid, "pdgid[indexmc]/I");
		TopoTree->Branch("drank", m_drank, "drank[indexmc]/I");
		TopoTree->Branch("motheridx", m_motheridx, "motheridx[indexmc]/I");
		TopoTree->Branch("motherpid", m_motherpid, "motherpid[indexmc]/I");
	}

	//track info
	TreeAna->Branch("runid", &runid, "runid/I");
	TreeAna->Branch("evtid", &evtid, "evtid/I");
	TreeAna->Branch("nevt", &nevt, "nevt/I");
	TreeAna->Branch("nNEUTRAL", &nNEUTRAL, "nNEUTRAL/I");
	TreeAna->Branch("nCHARGED",&nCHARGED,"nCHARGED/I");
	TreeAna->Branch("nTRACKS",&nTRACKS,"nTRACKS/I");
	TreeAna->Branch("nGamma", &nGamma, "nGamma/I");

	TreeAna->Branch("vx", vx, "vx[3]/D");
	TreeAna->Branch("Evx", Evx, "Evx[3]/D");
	TreeAna->Branch("costheta_chrgd", costheta_chrgd, "costheta_chrgd[2]/D");
	TreeAna->Branch("Rxy", Rxy, "Rxy[2]/D");
	TreeAna->Branch("Rz", Rz, "Rz[2]/D");
	TreeAna->Branch("Rvxy", Rvxy, "Rvxy[2]/D");
	TreeAna->Branch("Rvz", Rvz, "Rvz[2]/D");

	TreeAna->Branch("mmiss2", &mmiss2, "mmiss2/D");
	TreeAna->Branch("umiss", &umiss, "umiss/D");
	TreeAna->Branch("mmiss", &mmiss, "mmiss/D");
	TreeAna->Branch("pmiss", &pmiss, "pmiss/D");   
	TreeAna->Branch("emiss", &emiss, "emiss/D");	//				--Fengyun LI @ 2015-01-27
	TreeAna->Branch("ptr", &ptr, "ptr/D");
	TreeAna->Branch("ptr2", &ptr2, "ptr2/D");
	TreeAna->Branch("ptg2", &ptg2, "ptg2/D");
	TreeAna->Branch("costhe_ee", &costhe_ee, "costhe_ee/D");
	TreeAna->Branch("costhe_u", &costhe_u, "costhe_u/D");
	TreeAna->Branch("sinthe_ee", &sinthe_ee, "sinthe_ee/D");
	TreeAna->Branch("ee_ivm", &ee_ivm, "ee_ivm/D");

	TreeAna->Branch("chiDeDx", chiDeDx, "chiDeDx[2][5]/D");
	TreeAna->Branch("chiTof", chiTof,"chiTof[2][5]/D");
	TreeAna->Branch("chiTof1", chiTof1, "chiTof1[2][5]/D");
	TreeAna->Branch("chiTof2", chiTof2, "chiTof2[2][5]/D");		//				--Fengyun LI @ 2015-01-27
	TreeAna->Branch("chisq_pid", chisq_pid, "chisq_pid[2][5]/D");
	TreeAna->Branch("prob", prob, "prob[2][5]/D");
	TreeAna->Branch("vtxchisq", &vtxchisq, "vtxchisq/D");
	TreeAna->Branch("stat1C",&stat1C,"stat1C/I");
	TreeAna->Branch("chi1C",&chi1C,"chi1C/D");

	TreeAna->Branch("pTrk", m_pTrk, "pTrk[2]/D");
	TreeAna->Branch("deTrk", m_deTrk, "deTrk[2]/D");
	TreeAna->Branch("epTrk", m_epTrk, "epTrk[2]/D");
	TreeAna->Branch("hitsTrk", m_hitsTrk, "hitsTrk[2]/I");
	TreeAna->Branch("tof", tof, "tof[2]/D");
	TreeAna->Branch("dtof", &dtof, "dtof/D");

	TreeAna->Branch("p_all","TClonesArray",&p_all,256000,0);
	TreeAna->Branch("p_e1","TClonesArray",&p_e1,256000,0);
	TreeAna->Branch("p_e2","TClonesArray",&p_e2,256000,0);
	TreeAna->Branch("p_u","TClonesArray",&p_u,256000,0);


	//for number of events passing every cut
	if(m_saveNbInfo == 1)
	{
		NbInfo->Branch("Ncut0", &Ncut0, "Ncut0/I");
		NbInfo->Branch("Ncut1", &Ncut1, "Ncut1/I");
		NbInfo->Branch("Ncut2", &Ncut2, "Ncut2/I");
		NbInfo->Branch("Ncut3", &Ncut3, "Ncut3/I");
		NbInfo->Branch("Ncut4", &Ncut4, "Ncut4/I");
		NbInfo->Branch("Ncut5", &Ncut5, "Ncut5/I");
		NbInfo->Branch("Ncut6", &Ncut6, "Ncut6/I");
		NbInfo->Branch("Ncut7", &Ncut7, "Ncut7/I");
		NbInfo->Branch("Ncut8", &Ncut8, "Ncut8/I");
		NbInfo->Branch("Ncut9", &Ncut9, "Ncut9/I");
		NbInfo->Branch("Ncut10", &Ncut10, "Ncut10/I");
	}

	if(m_saveMCTruth == 1)
	{
		TreeAna->Branch("xp",&xp,32000,0);
		TreeAna->Branch("xm",&xp,32000,0);
		TreeAna->Branch("numep", &numep, "numep/I");
		TreeAna->Branch("numem", &numem, "numem/I");
		TreeAna->Branch("isSigee",&isSigee,"isSigee/I");
		TreeAna->Branch("numgam",&numgam,"numgam/I");
		TreeAna->Branch("mcgam","TClonesArray",&mcgam,256000,0);
	}



	p_all->BypassStreamer();
	p_e1->BypassStreamer();
	p_e2->BypassStreamer();
	p_u->BypassStreamer();
	mcgam->BypassStreamer();	

	log << MSG::INFO << "successfully return from initialize()" <<endmsg;
	std::cout<<"success initialize completed!"<<std::endl;
	return StatusCode::SUCCESS;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Eemiss::execute() {


	//std::cout << "execute()" << std::endl;

	MsgStream log(msgSvc(), name());
	log << MSG::INFO << "in execute()" << endreq;

	SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
	int runNo=eventHeader->runNumber();
	int event=eventHeader->eventNumber();
	runid=runNo;
	evtid=event;
	nGamma=0;
	nevt=0;
	isSigee = -1;
	numgam= 0 ;

	Ncut0++;  //total events
	log << MSG::DEBUG <<"run, evtnum = "
		<< runNo << " , "
		<< event <<endreq;
	//cout<<"event "<<event<<endl;

	if(!(Ncut0%10000))
	{
		cout<<"Processing "<<Ncut0<<"th event:   "<<" Run Id = "<<runNo<<", Event Id = "<<event<<endl;
		cout<<"Total =  "<<Ncut0<<", after good charged tracks cut = "<<Ncut1<<endl;
	}

	SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(), EventModel::EvtRec::EvtRecEvent);
	SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(),  EventModel::EvtRec::EvtRecTrackCol);

	//active simplePID service

//	ISimplePIDSvc* m_simplePIDSvc;
//	Gaudi::svcLocator()->service("SimplePIDSvc",m_simplePIDSvc);

	nCHARGED = evtRecEvent->totalCharged();
	nNEUTRAL = evtRecEvent->totalNeutral();
	nTRACKS = evtRecEvent->totalTracks();

	log << MSG::DEBUG <<"ncharg, nneu, tottks = " 
		<< nCHARGED << " , "
		<< nNEUTRAL << " , "
		<< nTRACKS <<endreq;

	//*************************************************************MC Info.***************************************************************************

	if (eventHeader->runNumber()<0)
	{
		if(m_saveTopoTree == 1) TopoTree->Fill();
	
		SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");

		if (!mcParticleCol)
		{
			std::cout << "Could not retrieve McParticelCol" << std::endl;
			return StatusCode::FAILURE;
		}

		else
		{
			Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
			Event::McParticle temp;
			m_idxmc=0;

			bool jpsiDecay = false;
			int jpsiIndex = -1;
			bool strange = false;

			for (; iter_mc != mcParticleCol->end(); iter_mc++)
			{
				if((*iter_mc)->primaryParticle()&&(*iter_mc)->particleProperty()==11&&((*iter_mc)->mother()).particleProperty()==11) {strange = true;}
				if ((*iter_mc)->primaryParticle()) continue;
				if (!(*iter_mc)->decayFromGenerator()) continue;
				//if ( ((*iter_mc)->mother()).trackIndex()<3 ) continue;
				if ((*iter_mc)->particleProperty() == 443) 
				{
					jpsiDecay = true;
					jpsiIndex = (*iter_mc)->trackIndex();
				}
				if (!jpsiDecay) continue;

				//int trkidx = (*iter_mc)->trackIndex() - rootIndex;

				int mcidx = ((*iter_mc)->mother()).trackIndex() - jpsiIndex;
				int pdgid = (*iter_mc)->particleProperty();
				if(strange &&((*iter_mc)->mother()).particleProperty()!=443) mcidx--; 
				//		if(pdgid == -22) continue;
				m_pdgid[m_idxmc] = pdgid;
				m_motheridx[m_idxmc] = mcidx;
				temp=(*iter_mc)->mother();
				m_motherpid[m_idxmc] = temp.particleProperty();

				if(pdgid == 443) m_drank[m_idxmc]=0;
				else
				{
					for(int i=1;i<100;i++)
					{
						if(temp.particleProperty()==443)
						{
							m_drank[m_idxmc]=i;
							break;
						}
						temp = temp.mother();
					}
				}

				m_idxmc++;    
			}

			int numep = 0;
			int numem = 0;

			if(m_saveMCTruth == 1)
			{
				xp->SetE(-1);
				xm->SetE(-1);

				TLorentzVector p_mcgam;
				if(jpsiIndex > 0)
				{
					for(iter_mc = mcParticleCol->begin(); iter_mc != mcParticleCol->end(); iter_mc++)
					{
						if((*iter_mc)->primaryParticle())
						{
							continue;
						}
						if(!(*iter_mc)->decayFromGenerator()) 
						{
							continue;
						}
						if(((*iter_mc)->mother()).trackIndex() !=jpsiIndex)
						{
							continue;
						}

						int pid = (*iter_mc)->particleProperty();
						//if(pid == -22) 	continue;

						HepLorentzVector p = (*iter_mc)->initialFourMomentum();
						if(pid == 11)
						{
							xm->SetPxPyPzE(p.px(),p.py(),p.pz(),p.e());
							numem++;
						}
						else if(pid == -11)
						{
							xp->SetPxPyPzE(p.px(),p.py(),p.pz(),p.e());
							numep++;
						}
						else if(pid == -22)
						{
							p_mcgam.SetPxPyPzE(p.px(),p.py(),p.pz(),p.e());
							new ((*mcgam)[numgam]) TLorentzVector(p_mcgam);
							numgam++;

						}
						else continue;

					}
					if( numem == 1 && numep== 1 )	isSigee=1;		

				}

			}
		}
	}


	//************************************************************************************************************************************************

	//*************************************************************Global Event Parameters************************************************************
	Vint iGood;
	iGood.clear();
	int checkVtx=0;

	Vint iChrgp,iChrgn;
	iChrgp.clear();
	iChrgn.clear();
	int nChrgp=0,nChrgn=0;
	int nGood = 0;
	int nCharge = 0;
	//************************************************************************************************************************************************

	//*************************************************************Primary Vertex*********************************************************************
	HepLorentzVector p4_cms(0.011*m_Ecms,0.,0.,m_Ecms);
	HepLorentzVector p4_mis(0.,0.,0.,0.);

	Hep3Vector xorigin(0,0,0);
	HepPoint3D vx_avg(0,0,0);
	HepSymMatrix Evx_avg(3,0);

	IVertexDbSvc*  vtxsvc;
	Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
	if(vtxsvc->isVertexValid())
	{
		double* dbv = vtxsvc->PrimaryVertex(); 
		double*  vv = vtxsvc->SigmaPrimaryVertex();  
		xorigin.setX(dbv[0]);
		xorigin.setY(dbv[1]);
		xorigin.setZ(dbv[2]);
		vx_avg.setX(dbv[0]);
		vx_avg.setY(dbv[1]);
		vx_avg.setZ(dbv[2]);

		Evx_avg[0][0] = vv[0]*vv[0];
		Evx_avg[1][1] = vv[0]*vv[0];
		Evx_avg[2][2] = vv[2]*vv[2];

		vx[0] = dbv[0];
		vx[1] = dbv[1];
		vx[2] = dbv[2];
		Evx[0] = vv[0];
		Evx[1] = vv[1];
		Evx[2] = vv[2];
	}
	VertexParameter vxpar_init;
	vxpar_init.setVx(vx_avg);
	vxpar_init.setEvx(Evx_avg);
	//************************************************************************************************************************************************

	//*************************************************************Good charged track*****************************************************************
	//cout<<"Start good track selection"<<endl;
	for(int i = 0; i < evtRecEvent->totalCharged(); i++)
	{
		if(i>= evtRecTrkCol->size()) break;
		EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
		if(!(*itTrk)->isMdcTrackValid()) continue;
		if(!(*itTrk)->isMdcKalTrackValid()) continue;

		RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
		RecMdcKalTrack *mdcKalTrk = (*itTrk)->mdcKalTrack();

		if(mdcKalTrk->charge()==0) continue;

		double theta = mdcTrk->theta();
		if(fabs(cos(theta)) > m_trkAngCut) continue;

		HepVector a = mdcTrk->helix();
		HepSymMatrix Ea = mdcTrk->err();
		HepPoint3D point0(0.,0.,0.);   // the initial point for MDC recosntruction
		HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]); 
		VFHelix helixip(point0,a,Ea); 
		helixip.pivot(IP);
		HepVector vecipa = helixip.a();
		double  Rvxy0=fabs(vecipa[0]);  //the nearest distance to IP in xy plane
		double  Rvz0=vecipa[3];         //the nearest distance to IP in z direction
		double  Rvphi0=vecipa[1];
		if(fabs(Rvz0) >= m_vz0cut) continue;
		if(fabs(Rvxy0) >= m_vr0cut) continue;

		iGood.push_back(i);
		nCharge += mdcKalTrk->charge();

		if(mdcKalTrk->charge() == 1) iChrgp.push_back(i);
		else if(mdcKalTrk->charge() == -1) iChrgn.push_back(i);
		else continue;
	}

	nGood = iGood.size();
	nChrgp = iChrgp.size();
	nChrgn = iChrgn.size();

	log << MSG::DEBUG << "ngood, totcharge = " << nGood << " , " << nCharge << endreq;
	if((nGood != 2) || (nCharge!=0) || (nChrgp != 1) || (nChrgn != 1) )
	{
		return StatusCode::SUCCESS;
	}
	Ncut1++;		//after good track selection

	//cout<<"Finish good track selection"<<endl;
	//************************************************************************************************************************************************

	//*************************************************************Store PID Info ********************************************************************
	//cout<<"begin PID info."<<endl;

	ParticleID *pid = ParticleID::instance();
	for(int i = 0; i < nChrgp; i++)
	{
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iChrgp[i];

		pid->init();
		pid->setMethod(pid->methodProbability());

		pid->setChiMinCut(4);
		pid->setRecTrack(*itTrk);
		pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2()); // use PID sub-system
		//pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2() | pid->useTofCorr()); // use PID sub-system
		pid->identify( pid->onlyElectron() | pid->onlyMuon() | pid->onlyPion() | pid->onlyKaon() | pid->onlyProton());    // seperater Pion/Kaon/Proton/Muon/Electron
		//pid->identify( pid->onlyElectron() | pid->onlyPion() | pid->onlyKaon() | pid->onlyProton());    // seperater Pion/Kaon/Proton/Muon/Electron
		//0=electron,1=muon,2=pion,3=kaon,4=proton
		pid->calculate();
		if(!(pid->IsPidInfoValid()))
		{
			chiDeDx[i][0] = -99;
			chiDeDx[i][1] = -99;
			chiDeDx[i][2] = -99;
			chiDeDx[i][3] = -99;
			chiDeDx[i][4] = -99;

			chiTof[i][0] = -99;
			chiTof[i][1] = -99;
			chiTof[i][2] = -99;
			chiTof[i][3] = -99;
			chiTof[i][4] = -99;

			chiTof1[i][0] = -99;
			chiTof1[i][1] = -99;
			chiTof1[i][2] = -99;
			chiTof1[i][3] = -99;
			chiTof1[i][4] = -99;

			chiTof2[i][0] = -99;
			chiTof2[i][1] = -99;
			chiTof2[i][2] = -99;
			chiTof2[i][3] = -99;
			chiTof2[i][4] = -99;

			chisq_pid[i][0] = -99;
			chisq_pid[i][1] = -99;
			chisq_pid[i][2] = -99;
			chisq_pid[i][3] = -99;
			chisq_pid[i][4] = -99;

			prob[i][0] = -99;
			prob[i][1] = -99;
			prob[i][2] = -99;
			prob[i][3] = -99;
			prob[i][4] = -99;
		}
		else
		{
			chiDeDx[i][0] = pid->chiDedx(0);
			chiDeDx[i][1] = pid->chiDedx(1);
			chiDeDx[i][2] = pid->chiDedx(2);
			chiDeDx[i][3] = pid->chiDedx(3);
			chiDeDx[i][4] = pid->chiDedx(4);

			chiTof[i][0] = pid->chiTof(0);
			chiTof[i][1] = pid->chiTof(1);
			chiTof[i][2] = pid->chiTof(2);
			chiTof[i][3] = pid->chiTof(3);
			chiTof[i][4] = pid->chiTof(4);

			chiTof1[i][0] = pid->chiTof1(0);
			chiTof1[i][1] = pid->chiTof1(1);
			chiTof1[i][2] = pid->chiTof1(2);
			chiTof1[i][3] = pid->chiTof1(3);
			chiTof1[i][4] = pid->chiTof1(4);

			chiTof2[i][0] = pid->chiTof2(0);
			chiTof2[i][1] = pid->chiTof2(1);
			chiTof2[i][2] = pid->chiTof2(2);
			chiTof2[i][3] = pid->chiTof2(3);
			chiTof2[i][4] = pid->chiTof2(4);

			chisq_pid[i][0] = chiDeDx[i][0]*chiDeDx[i][0] + chiTof1[i][0]*chiTof1[i][0] + chiTof2[i][0]*chiTof2[i][0];
			chisq_pid[i][1] = chiDeDx[i][1]*chiDeDx[i][1] + chiTof1[i][1]*chiTof1[i][1] + chiTof2[i][1]*chiTof2[i][1];
			chisq_pid[i][2] = chiDeDx[i][2]*chiDeDx[i][2] + chiTof1[i][2]*chiTof1[i][2] + chiTof2[i][2]*chiTof2[i][2];
			chisq_pid[i][3] = chiDeDx[i][3]*chiDeDx[i][3] + chiTof1[i][3]*chiTof1[i][3] + chiTof2[i][3]*chiTof2[i][3];
			chisq_pid[i][4] = chiDeDx[i][4]*chiDeDx[i][4] + chiTof1[i][4]*chiTof1[i][4] + chiTof2[i][4]*chiTof2[i][4];

			prob[i][0] = pid->probElectron();
			prob[i][1] = pid->probMuon();
			prob[i][2] = pid->probPion();
			prob[i][3] = pid->probKaon();
			prob[i][4] = pid->probProton();
		}
	}

	for(int i = 0; i < nChrgn; i++)
	{
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iChrgn[i];

		pid->init();
		pid->setMethod(pid->methodProbability());

		pid->setChiMinCut(4);
		pid->setRecTrack(*itTrk);
		pid->usePidSys(pid->useDedx() | pid->useTof1() | pid->useTof2()); // use PID sub-system
		pid->identify( pid->onlyElectron() | pid->onlyMuon() | pid->onlyPion() | pid->onlyKaon() | pid->onlyProton());    // seperater Pion/Kaon/Proton/Muon/Electron
		//0=electron,1=muon,2=pion,3=kaon,4=proton
		pid->calculate();
		if(!(pid->IsPidInfoValid()))
		{
			chiDeDx[i+nChrgp][0] = -99;
			chiDeDx[i+nChrgp][1] = -99;
			chiDeDx[i+nChrgp][2] = -99;
			chiDeDx[i+nChrgp][3] = -99;
			chiDeDx[i+nChrgp][4] = -99;

			chiTof[i+nChrgp][0] = -99;
			chiTof[i+nChrgp][1] = -99;
			chiTof[i+nChrgp][2] = -99;
			chiTof[i+nChrgp][3] = -99;
			chiTof[i+nChrgp][4] = -99;

			chiTof1[i+nChrgp][0] = -99;
			chiTof1[i+nChrgp][1] = -99;
			chiTof1[i+nChrgp][2] = -99;
			chiTof1[i+nChrgp][3] = -99;
			chiTof1[i+nChrgp][4] = -99;

			chiTof2[i+nChrgp][0] = -99;
			chiTof2[i+nChrgp][1] = -99;
			chiTof2[i+nChrgp][2] = -99;
			chiTof2[i+nChrgp][3] = -99;
			chiTof2[i+nChrgp][4] = -99;

			chisq_pid[i+nChrgp][0] = -99;
			chisq_pid[i+nChrgp][1] = -99;
			chisq_pid[i+nChrgp][2] = -99;
			chisq_pid[i+nChrgp][3] = -99;
			chisq_pid[i+nChrgp][4] = -99;

			prob[i+nChrgp][0] = -99;
			prob[i+nChrgp][1] = -99;
			prob[i+nChrgp][2] = -99;
			prob[i+nChrgp][3] = -99;
			prob[i+nChrgp][4] = -99;
		}
		else
		{
			chiDeDx[i+nChrgp][0] = pid->chiDedx(0);
			chiDeDx[i+nChrgp][1] = pid->chiDedx(1);
			chiDeDx[i+nChrgp][2] = pid->chiDedx(2);
			chiDeDx[i+nChrgp][3] = pid->chiDedx(3);
			chiDeDx[i+nChrgp][4] = pid->chiDedx(4);

			chiTof[i+nChrgp][0] = pid->chiTof(0);
			chiTof[i+nChrgp][1] = pid->chiTof(1);
			chiTof[i+nChrgp][2] = pid->chiTof(2);
			chiTof[i+nChrgp][3] = pid->chiTof(3);
			chiTof[i+nChrgp][4] = pid->chiTof(4);

			chiTof1[i+nChrgp][0] = pid->chiTof1(0);
			chiTof1[i+nChrgp][1] = pid->chiTof1(1);
			chiTof1[i+nChrgp][2] = pid->chiTof1(2);
			chiTof1[i+nChrgp][3] = pid->chiTof1(3);
			chiTof1[i+nChrgp][4] = pid->chiTof1(4);

			chiTof2[i+nChrgp][0] = pid->chiTof2(0);
			chiTof2[i+nChrgp][1] = pid->chiTof2(1);
			chiTof2[i+nChrgp][2] = pid->chiTof2(2);
			chiTof2[i+nChrgp][3] = pid->chiTof2(3);
			chiTof2[i+nChrgp][4] = pid->chiTof2(4);

			chisq_pid[i+nChrgp][0] = chiDeDx[i+nChrgp][0]*chiDeDx[i+nChrgp][0] + chiTof1[i+nChrgp][0]*chiTof1[i+nChrgp][0] + chiTof2[i+nChrgp][0]*chiTof2[i+nChrgp][0];
			chisq_pid[i+nChrgp][1] = chiDeDx[i+nChrgp][1]*chiDeDx[i+nChrgp][1] + chiTof1[i+nChrgp][1]*chiTof1[i+nChrgp][1] + chiTof2[i+nChrgp][1]*chiTof2[i+nChrgp][1];
			chisq_pid[i+nChrgp][2] = chiDeDx[i+nChrgp][2]*chiDeDx[i+nChrgp][2] + chiTof1[i+nChrgp][2]*chiTof1[i+nChrgp][2] + chiTof2[i+nChrgp][2]*chiTof2[i+nChrgp][2];
			chisq_pid[i+nChrgp][3] = chiDeDx[i+nChrgp][3]*chiDeDx[i+nChrgp][3] + chiTof1[i+nChrgp][3]*chiTof1[i+nChrgp][3] + chiTof2[i+nChrgp][3]*chiTof2[i+nChrgp][3];
			chisq_pid[i+nChrgp][4] = chiDeDx[i+nChrgp][4]*chiDeDx[i+nChrgp][4] + chiTof1[i+nChrgp][4]*chiTof1[i+nChrgp][4] + chiTof2[i+nChrgp][4]*chiTof2[i+nChrgp][4];

			prob[i+nChrgp][0] = pid->probElectron();
			prob[i+nChrgp][1] = pid->probMuon();
			prob[i+nChrgp][2] = pid->probPion();
			prob[i+nChrgp][3] = pid->probKaon();
			prob[i+nChrgp][4] = pid->probProton();
		}
	}

	//cout<<"Finish PID info."<<endl;	
	//************************************************************************************************************************************************


	//***********************************************************Good Gamma Selection*****************************************************************
	//cout<<"begin good gamma selection"<<endl;
	//Veto gamma,0-0.92,0.86

	Vint iGamma;
	iGamma.clear();
	for(int i = evtRecEvent->totalCharged(); i< evtRecEvent->totalTracks(); i++) 
	{
		if(i >= evtRecTrkCol->size()) break;

		EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
		if(!(*itTrk)->isEmcShowerValid()) continue;
		RecEmcShower *emcTrk = (*itTrk)->emcShower();

		double eraw=emcTrk->energy();
		double the=emcTrk->theta();
		double time=emcTrk->time();
		if(time < 0||time >14) continue;							//time cut
		Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());

		double e_threshold=100.0;

		if(fabs(cos(the))<p_lphotonang)	e_threshold=m_barrelEnergyThreshold;
		
		else if((fabs(cos(the))>0.86) && (fabs(cos(the)) < p_hphotonang)) e_threshold=m_endEnergyThreshold;
		else continue;
		if(eraw < e_threshold) continue;

		// find the nearest charged track
		//double dthe = 200.;
		//double dphi = 200.;
		double dang = 200.; 
		if(f_cktpang==1)
		{
		   for(int j = 0; j < evtRecEvent->totalCharged(); j++)
		   {
		   if(j>=evtRecTrkCol->size()) break;
		   EvtRecTrackIterator jtTrk = evtRecTrkCol->begin() + j;

		   if(!(*jtTrk)->isExtTrackValid()) continue;
		   RecExtTrack *extTrk = (*jtTrk)->extTrack();

		   if(extTrk->emcVolumeNumber() == -1) continue;
		   Hep3Vector extpos = extTrk->emcPosition();

		   double angd = extpos.angle(emcpos);
		//	double thed = extpos.theta() - emcpos.theta();
		//	double phid = extpos.deltaPhi(emcpos);
		//	thed = fmod(thed+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;
		//	phid = fmod(phid+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;

		if(angd < dang) dang = angd;
		}
		if(dang>=200) continue;
		dang = dang * 180 / (CLHEP::pi);
		}	
		//				--Fengyun LI @ 2014-12-16		
		if(fabs(dang) < m_gammaAngleCut) continue;
	
		iGamma.push_back(i);
	}
	nGamma = iGamma.size();
	log << MSG::DEBUG << "num Good Photon " << nGamma  << " , " <<evtRecEvent->totalNeutral()<<endreq;

	int showGam=1;
	if(showGam==1)  
	{
		if(nGamma==1) NGam1++;
		if(nGamma==2) NGam2++;
		if(nGamma>2) NGamA2++;
	}
	if(nGamma!=0) return StatusCode::SUCCESS; 
	Ncut2++;	//after good gamma cut
	//cout<<"finish good gamma selection"<<endl;
	//************************************************************************************************************************************************

	//*************************************************************Store track  info *****************************************************************
	//cout<<"begin track info "<<endl;
	for(int i = 0; i < nChrgp; i++)
	{
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iChrgp[i];
		RecMdcTrack *imdcTrk = (*itTrk)->mdcTrack();
		RecMdcKalTrack *imdcKalTrk = (*itTrk)->mdcKalTrack();

		HepVector ia = imdcTrk->helix();
		HepSymMatrix iEa = imdcTrk->err();

		HepPoint3D point0(0.,0.,0.);   // the initial point for MDC recosntruction
		HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]); 

		VFHelix ihelixip(point0,ia,iEa); 
		ihelixip.pivot(IP);
		HepVector ivecipa = ihelixip.a();
		double  Rvxy0=fabs(ivecipa[0]);  //the nearest distance to IP in xy plane
		double  Rvz0=ivecipa[3];         //the nearest distance to IP in z direction
		double  Rvphi0=ivecipa[1];

		costheta_chrgd[i]=cos(imdcTrk->theta());
		Rxy[i]=imdcTrk->r();
		Rz[i]=imdcTrk->z();
		Rvxy[i]=Rvxy0;
		Rvz[i]=Rvz0;	


		if((*itTrk)->isEmcShowerValid()) 
		{
			RecEmcShower *emcTrk=(*itTrk)->emcShower();
			m_deTrk[i]= emcTrk->energy();
			m_hitsTrk[i]=emcTrk->numHits();
			m_pTrk[i]=imdcKalTrk->p();
			m_epTrk[i]=m_deTrk[i]/m_pTrk[i];
			//for track have emc deposit,use eop to require  eop > 0.8
			if(m_epTrk[i]<epcut) return StatusCode::SUCCESS;
		}
		else
		{
			//		--Fengyun LI @ 2015-01-27
			return StatusCode::SUCCESS;	
			/*
			//for track have no emc deposit,use PID info to identify.
			//require P(e)>0.001 & P(e) > P(mu,pi,k,p)
			if((prob[i][0]<0.001)||(prob[i][0]<prob[i][1])||(prob[i][0]<prob[i][2])||(prob[i][0]<prob[i][3])||(prob[i][0]<prob[i][4]))
				return StatusCode::SUCCESS;

			m_deTrk[i]= -1;
			m_hitsTrk[i]= -1;
			m_pTrk[i]=imdcKalTrk->p();
			m_epTrk[i]=-1;
			*/
		}


		//simplePID
		//only identify electron from (e,Pi,K)

		//m_simplePIDSvc->preparePID(*itTrk);							//	--Fengyun LI @ 2014-12-09
		//if(!m_simplePIDSvc->iselectron(true)) return StatusCode::SUCCESS;

		/*
		   for(int k=0;k<5;k++)
		   {
		   chiDeDx[i][k]=m_simplePIDSvc->getdEdxChi(k);
		   chiTof[i][k]=m_simplePIDSvc->getTOFChi(k);
		   }
		   */
		TVector3 p_p(imdcKalTrk->px(),imdcKalTrk->py(),imdcKalTrk->pz());
		new ((*p_all)[i]) TVector3(p_p);
	}

	for(int j = 0;j < nChrgn; j++)
	{
		EvtRecTrackIterator jtTrk = evtRecTrkCol->begin() + iChrgn[j];
		RecMdcTrack *jmdcTrk = (*jtTrk)->mdcTrack();
		RecMdcKalTrack *jmdcKalTrk = (*jtTrk)->mdcKalTrack();

		HepVector ja = jmdcTrk->helix();
		HepSymMatrix jEa = jmdcTrk->err();

		HepPoint3D point0(0.,0.,0.);   // the initial point for MDC recosntruction
		HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]); 

		VFHelix jhelixip(point0,ja,jEa); 
		jhelixip.pivot(IP);
		HepVector jvecipa = jhelixip.a();
		double  Rvxy1=fabs(jvecipa[0]);  //the nearest distance to IP in xy plane
		double  Rvz1=jvecipa[3];         //the nearest distance to IP in z direction
		double  Rvphi1=jvecipa[1];

		costheta_chrgd[j+nChrgp]=cos(jmdcTrk->theta());
		Rxy[j+nChrgp]=jmdcTrk->r();
		Rz[j+nChrgp]=jmdcTrk->z();
		Rvxy[j+nChrgp]=Rvxy1;
		Rvz[j+nChrgp]=Rvz1;	

		if((*jtTrk)->isEmcShowerValid()) 
		{
			RecEmcShower *emcTrk=(*jtTrk)->emcShower();

			m_deTrk[j+nChrgp]= emcTrk->energy();
			m_hitsTrk[j+nChrgp]=emcTrk->numHits();
			m_pTrk[j+nChrgp]=jmdcKalTrk->p();
			m_epTrk[j+nChrgp]=m_deTrk[j+nChrgp]/m_pTrk[j+nChrgp];
			//for track have emc deposit,use eop to require  eop > 0.8
			if(m_epTrk[j+nChrgp]<epcut) return StatusCode::SUCCESS;
		}
		else
		{
												//		--Fengyun LI @ 2015-01-27
			return StatusCode::SUCCESS;	
			/*
			//for track have no emc deposit,use PID info to identify.
			//require P(e)>0.001 & P(e) > P(mu,pi,k,p)
			if((prob[j+nChrgp][0]<0.001)||(prob[j+nChrgp][0]<prob[j+nChrgp][1])||(prob[j+nChrgp][0]<prob[j+nChrgp][2])||(prob[j+nChrgp][0]<prob[j+nChrgp][3])||(prob[j+nChrgp][0]<prob[j+nChrgp][4]))
				return StatusCode::SUCCESS;

			m_deTrk[j+nChrgp]= -1;
			m_hitsTrk[j+nChrgp]= -1;
			m_pTrk[j+nChrgp]=jmdcKalTrk->p();
			m_epTrk[j+nChrgp]=-1;
			*/
		}

		//simplePID

		//m_simplePIDSvc->preparePID(*jtTrk);
		//if(!m_simplePIDSvc->iselectron(true)) return StatusCode::SUCCESS;

		/*	
			for(int k=0;k<5;k++)
			{
			chiDeDx[j+nChrgp][k]=m_simplePIDSvc->getdEdxChi(k);
			cout<<m_simplePIDSvc->getTOFChi(k)<<endl;
			chiTof[j+nChrgp][k]=m_simplePIDSvc->getTOFChi(k);
			}
			*/
		TVector3 p_m(jmdcKalTrk->px(),jmdcKalTrk->py(),jmdcKalTrk->pz());
		new ((*p_all)[j+nChrgp]) TVector3(p_m);
	}			



	Ncut3++;	
	//cout<<"finish get trark info"<<endl;
	//************************************************************************************************************************************************

	//*****************************************************************Assign track momentum**********************************************************
	WTrackParameter wvTrkp;
	WTrackParameter wvTrkm;

	EvtRecTrackIterator lTrk1 = evtRecTrkCol->begin() + iChrgp[0];
	RecMdcKalTrack *mdcKalTrk1 = (*lTrk1)->mdcKalTrack();

	EvtRecTrackIterator lTrk2 = evtRecTrkCol->begin() + iChrgn[0];
	RecMdcKalTrack *mdcKalTrk2 = (*lTrk2)->mdcKalTrack();


	wvTrkp = WTrackParameter(me,mdcKalTrk1->getZHelixE(),mdcKalTrk1->getZErrorE());
	wvTrkm = WTrackParameter(me,mdcKalTrk2->getZHelixE(),mdcKalTrk2->getZErrorE());

	//cout<<"finish charged track momentum assignment"<<endl;
	//************************************************************************************************************************************************

	//******************************************************************Vertex fit *******************************************************************
	//cout<<"begin vertex fit"<<endl;
	WTrackParameter wTrkp;
	WTrackParameter wTrkm;

	HepPoint3D vx_infit;
	HepSymMatrix Evx_infit;

	HepPoint3D vx(0., 0., 0.);
	HepSymMatrix Evx(3, 0);

	double bx = 1E+6;
	double by = 1E+6;
	double bz = 1E+6;
	Evx[0][0] = bx*bx;
	Evx[1][1] = by*by;
	Evx[2][2] = bz*bz;

	VertexParameter vxpar;
	vxpar.setVx(vx);
	vxpar.setEvx(Evx);

	VertexFit* vtxfit = VertexFit::instance();
	vtxfit->init();
	vtxfit->AddTrack(0,  wvTrkp);
	vtxfit->AddTrack(1,  wvTrkm);
	vtxfit->AddVertex(0, vxpar,0,1);

	if(!vtxfit->Fit(0)) 
	{
		if(checkVtx==1)
		{
			cout<<"vtx_failed!"<<endl;
			cout<<"event ID:"<<event<<endl;
			cout<<" TrackNo "<<" Px "<<" Py "<<" Pz "<<" E "<<" Rxy "<<" Rz "<<" Rvxy "<<" Rvz "<<endl;

			cout<<" plus    "<<(wvTrkp.p()).px()<<" "<<(wvTrkp.p()).py()<<" "<<(wvTrkp.p()).pz()<<" "<<(wvTrkp.p()).e()<<" "<<
				Rxy[0]<<" "<<Rz[0]<<" "<<Rvxy[0]<<" "<<Rvz[0]<<" "<<endl;

			cout<<" minus    "<<(wvTrkm.p()).px()<<" "<<(wvTrkm.p()).py()<<" "<<(wvTrkm.p()).pz()<<" "<<(wvTrkm.p()).e()<<" "<<
				Rxy[1]<<" "<<Rz[1]<<" "<<Rvxy[1]<<" "<<Rvz[1]<<" "<<endl;
		}
		return StatusCode::SUCCESS;
	}

	vtxfit->Swim(0);

	vtxchisq=vtxfit->chisq(0);
	wTrkp=vtxfit->wtrk(0);
	wTrkm=vtxfit->wtrk(1);

	vx_infit=vtxfit->vx(0);
	Evx_infit=vtxfit->Evx(0);

	Ncut4++;
	//cout<<"finish vertex fit"<<endl;
	//************************************************************************************************************************************************

	TLorentzVector p4_jpsi,lepton1_unfit,lepton2_unfit,mis_unfit;	

	lepton1_unfit.SetPxPyPzE((wTrkp.p()).px(),(wTrkp.p()).py(),(wTrkp.p()).pz(),(wTrkp.p()).e());
	lepton2_unfit.SetPxPyPzE((wTrkm.p()).px(),(wTrkm.p()).py(),(wTrkm.p()).pz(),(wTrkm.p()).e());
	p4_jpsi.SetPxPyPzE(p4_cms.px(),p4_cms.py(),p4_cms.pz(),p4_cms.e());

	mis_unfit=p4_jpsi-(lepton1_unfit+lepton2_unfit);

	new ((*p_e1)[nevt]) TLorentzVector(lepton1_unfit);
	new ((*p_e2)[nevt]) TLorentzVector(lepton2_unfit);
	new ((*p_u)[nevt]) TLorentzVector(mis_unfit);


	TVector3 p3_lepton1,p3_lepton2,p3_mis;
	p3_lepton1.SetXYZ(lepton1_unfit.Px(),lepton1_unfit.Py(),lepton1_unfit.Pz());
	p3_lepton2.SetXYZ(lepton2_unfit.Px(),lepton2_unfit.Py(),lepton2_unfit.Pz());
	p3_mis.SetXYZ(mis_unfit.Px(),mis_unfit.Py(),mis_unfit.Pz());

	mmiss2=mis_unfit.M2();
	umiss=mis_unfit.E()-fabs(mis_unfit.P());
	mmiss=sqrt(mmiss2);
	costhe_ee=cos(p3_lepton1.Angle(p3_lepton2));
	sinthe_ee=sqrt(1-costhe_ee*costhe_ee);
	ee_ivm=(lepton1_unfit+lepton2_unfit).M();
	emiss=mis_unfit.E();
	pmiss=fabs(mis_unfit.P());
	ptr=(p3_lepton1.Mag()>p3_lepton2.Mag())?fabs(sinthe_ee*p3_lepton2.Mag()):fabs(sinthe_ee*p3_lepton1.Mag());
	ptr2=ptr*ptr;
	costhe_u=p3_mis.CosTheta();

	if(emiss<p_emiss) return StatusCode::SUCCESS;
	Ncut5++;
	//if(emiss<Ecut) return StatusCode::SUCCESS;
	//Ncut6++;
	if(fabs(costhe_u)>p_missang) return StatusCode::SUCCESS; 
	Ncut7++;

	nevt++;

	KalmanKinematicFit * kmfit = KalmanKinematicFit::instance();
	HepLorentzVector ecms(0.034,0,0,3.097);
	double chisq = 9999.;
	
	//***********************************************************************un-1C kmfit*****************************************************************
	//cout<<"begin 1C kmfit"<<endl;
	if(chk1C==1)
	{
		kmfit->init();
		kmfit->setBeamPosition(vx_infit);
		kmfit->setVBeamPosition(Evx_infit);
		kmfit->AddTrack(0,wTrkp);
		kmfit->AddTrack(1,wTrkm);
		kmfit->AddMissTrack(2,0.);
		kmfit->AddFourMomentum(0,ecms);
		bool okfit=kmfit->Fit();
		//if(okfit) return StatusCode::SUCCESS;	
		if(okfit)
		{
			stat1C=1; 
			chi1C=kmfit->chisq();
		}
		else
		{
			stat1C=0;
			chi1C=-1.0;
		}
		Ncut8++;
	}
	//cout<<"finish 1C kmfit"<<endl;
	//************************************************************************************************************************************************

	//***********************************************************************un-4C kmfit*****************************************************************
	//cout<<"begin 4C kmfit"<<endl;
	if(chk4C==1)
	{
		kmfit->init();
		kmfit->setBeamPosition(vx_infit);
		kmfit->setVBeamPosition(Evx_infit);
		kmfit->AddTrack(0,wTrkp);
		kmfit->AddTrack(1,wTrkm);
		kmfit->AddFourMomentum(0,ecms);
		bool okfit1 = kmfit->Fit();
		//double chi_4C=kmfit->chisq();
		if(okfit1) return StatusCode::SUCCESS;
		Ncut9++;	
	}
	//cout<<"finish 4C kmfit"<<endl;
	//************************************************************************************************************************************************



	//**************************************************************check TOF*************************************************************************
	//cout<<"begin TOF delat_tof check"<<endl;
	tof[0]=-1;
	tof[1]=-1;
	dtof=-1;	

	if(check_tof==1)
	{
		for(int i = 0; i < nChrgp; i++)
		{
			EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iChrgp[i];
			if(!(*itTrk)->isTofTrackValid()) continue;
			SmartRefVector<RecTofTrack> tofTrkCol = (*itTrk)->tofTrack();
			SmartRefVector<RecTofTrack>::iterator iter_tof = tofTrkCol.begin();
			for(;iter_tof != tofTrkCol.end(); iter_tof++ ) 
			{ 
				TofHitStatus *status = new TofHitStatus; 
				status->setStatus((*iter_tof)->status());
				if( !(status->is_raw()) )  continue; //no TOF hit
				if( !(status->is_cluster()) ) continue; // 
				tof[i]  = (*iter_tof)->tof();
			}
		}
		for(int i = 0; i < nChrgn; i++)
		{
			EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iChrgn[i];
			if(!(*itTrk)->isTofTrackValid()) continue;
			SmartRefVector<RecTofTrack> tofTrkCol = (*itTrk)->tofTrack();
			SmartRefVector<RecTofTrack>::iterator iter_tof = tofTrkCol.begin();
			for(;iter_tof != tofTrkCol.end(); iter_tof++ ) 
			{ 
				TofHitStatus *status = new TofHitStatus; 
				status->setStatus((*iter_tof)->status());
				if( !(status->is_raw()) )  continue; //no TOF hit
				if( !(status->is_cluster()) ) continue; // 
				tof[i+nChrgp]  = (*iter_tof)->tof();
			}
		}
		dtof=fabs(tof[0]-tof[1]);
	}
	Ncut10++;
	//cout<<"end TOF delta_tof check"<<endl;
	//************************************************************************************************************************************************
	TreeAna->Fill();

	p_all->Clear();
	p_e1->Clear();
	p_e2->Clear();
	p_u->Clear();
	mcgam->Clear();
	return StatusCode::SUCCESS;
}

//***************************************************************************



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
StatusCode Eemiss::finalize() {

	NbInfo->Fill();
	saveFile->cd();
	TreeAna->Write();
	if(m_saveTopoTree == 1)	TopoTree->Write();
	if(m_saveNbInfo == 1) NbInfo->Write();
	saveFile->Close();

	cout<<"finalize has completed!"<<endl;
	cout<<"Version 6"<<endl;

	cout<<"Total number:                         "<<Ncut0<<endl;
	cout<<"nGood==2, nCharge==0:                 "<<Ncut1<<endl;
	cout<<"nGamma=0:                             "<<Ncut2<<endl;
	cout<<"after PID:                            "<<Ncut3<<endl;
	cout<<"after vertex fit:                     "<<Ncut4<<endl;
	cout<<"after Emiss cut:                      "<<Ncut5<<endl;
	cout<<"after costhe miss:                    "<<Ncut7<<endl;
	if(chk1C==1)
	{cout<<"after Veto 1C:                        "<<Ncut8<<endl;}
	if(chk4C==1)
	{cout<<"after Veto 4C:                        "<<Ncut9<<endl;}
	cout<<"after tof check:                      "<<Ncut10<<endl;
	//	cout<<"after MUC check:                      "<<Ncut8<<endl;


	MsgStream log(msgSvc(), name());
	log << MSG::INFO << "in finalize()" << endmsg;
	return StatusCode::SUCCESS;
}

//mis_unfit=p4_cms-(lepton1_unfit+lepton2_unfit);
/*
   double ppx,ppy,ppz,ppe;
   ppx=p4_cms.px()-(lepton1_unfit.Px()+lepton2_unfit.Px());
   ppy=p4_cms.py()-(lepton1_unfit.Py()+lepton2_unfit.Py());
   ppz=p4_cms.pz()-(lepton1_unfit.Pz()+lepton2_unfit.Pz());
   ppe=p4_cms.e()-(lepton1_unfit.E()+lepton2_unfit.E());
   mis_unfit.SetPxPyPzE(ppx,ppy,ppz,ppe);
   */
//**************************************************************check eop*************************************************************************
//cout<<"begin deposit energy in EMC over Momentum check"<<endl;
/*
   if(m_checkRatio==1)
   {		
//cout<<"nGood="<<nGood<<endl;
double emcValid=1;

for(int i = 0; i < nChrgp; i++)
{
EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iChrgp[i];
if(!(*itTrk)->isEmcShowerValid()) 
{
emcValid=0;
//cout<<"emc invalid"<<endl;
}
RecMdcKalTrack *mdcKalTrk = (*itTrk)->mdcKalTrack();

if( emcValid==1 ) 
{
RecEmcShower *emcTrk=(*itTrk)->emcShower();
m_deTrk[i]= emcTrk->energy();
m_hitsTrk[i]=emcTrk->numHits();
}
else 
{
m_deTrk[i]= -10.0;
m_hitsTrk[i]= -10.0;
}

m_pTrk[i]=mdcKalTrk->p();
m_epTrk[i]=m_deTrk[i]/m_pTrk[i];
}

for(int i = 0; i < nChrgn; i++)
{
EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iChrgn[i];
if(!(*itTrk)->isEmcShowerValid()) 
{
emcValid=0;
//cout<<"emc invalid"<<endl;
}
RecMdcKalTrack *mdcKalTrk = (*itTrk)->mdcKalTrack();
if( emcValid==1 ) 
{
RecEmcShower *emcTrk=(*itTrk)->emcShower();
m_deTrk[i+nChrgp]= emcTrk->energy();
m_hitsTrk[i+nChrgp]=emcTrk->numHits();
}
else 
{
m_deTrk[i+nChrgp]= -10.0;
m_hitsTrk[i+nChrgp]= -10.0;
}
m_pTrk[i+nChrgp]=mdcKalTrk->p();
m_epTrk[i+nChrgp]=m_deTrk[i+nChrgp]/m_pTrk[i+nChrgp];
}
Ncut7++;
}
*/

//cout<<"finish dE/p check"<<endl;	
//************************************************************************************************************************************************

//****************************************************************check MUC info.*****************************************************************
//cout<<"begin vertex fit"<<endl;
/*
   if(m_checkMuc==1)
   {
   for(int i=0;i<nChrgp;i++)
   {
   EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iChrgp[i];
   if(!(*itTrk)->isMucTrackValid()) 
   {
   m_mucstat[i]=-1;
   continue;
   }

   RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
   RecMucTrack *mucTrk = (*itTrk)->mucTrack();

   m_mucstat[i]=1;
   m_depMuc[i]=mucTrk->depth();
   m_layerMuc[i]=mucTrk->numLayers();
   m_kalrechi2[i]=mucTrk->kalRechi2();
   m_kaldof[i]=mucTrk->kaldof();
   m_kaldep[i]=mucTrk->kaldepth();
   m_kalbrLastLayer[i]=mucTrk->kalbrLastLayer();
   m_kalecLastLayer[i]=mucTrk->kalecLastLayer();

   if(!(*itTrk)->isExtTrackValid()) 
   {
   m_angMuc[i]=-10;
   continue;
   }
   else
   {
   RecExtTrack *extTrk = (*itTrk)->extTrack();
   Hep3Vector extmuc = extTrk->mucPosition();
   Hep3Vector mucpos = (mucTrk->px(),mucTrk->py(),mucTrk->pz());
   double angg=extmuc.angle(mucpos);
   if(angg>=200) continue;
   angg = angg * 180 / (CLHEP::pi);
   m_angMuc[i]=angg;
   }

   }

   for(int i=0;i<nChrgn;i++)
   {
   EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iChrgn[i];
   if(!(*itTrk)->isMucTrackValid()) 
   {
   m_mucstat[i+nChrgp]=-1;
   continue;
   }

   RecMdcTrack *mdcTrk = (*itTrk)->mdcTrack();
   RecMucTrack *mucTrk = (*itTrk)->mucTrack();

   m_mucstat[i+nChrgp]=1;
   m_depMuc[i+nChrgp]=mucTrk->depth();
   m_layerMuc[i+nChrgp]=mucTrk->numLayers();
   m_kalrechi2[i+nChrgp]=mucTrk->kalRechi2();
   m_kaldof[i+nChrgp]=mucTrk->kaldof();
   m_kaldep[i+nChrgp]=mucTrk->kaldepth();
   m_kalbrLastLayer[i+nChrgp]=mucTrk->kalbrLastLayer();
   m_kalecLastLayer[i+nChrgp]=mucTrk->kalecLastLayer();

   if(!(*itTrk)->isExtTrackValid()) 
   {
   m_angMuc[i+nChrgp]=-10;
   continue;
   }
   else
   {
   RecExtTrack *extTrk = (*itTrk)->extTrack();
Hep3Vector extmuc = extTrk->mucPosition();
Hep3Vector mucpos = (mucTrk->px(),mucTrk->py(),mucTrk->pz());
double angg=extmuc.angle(mucpos);
if(angg>=200) continue;
angg = angg * 180 / (CLHEP::pi);
m_angMuc[i+nChrgp]=angg;
}

}
Ncut8++;
}
*/
