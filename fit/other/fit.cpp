/*
 * =====================================================================================
 *
 *       Filename:  fit_rm.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/29/2013 02:57:24 PM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  
 *
 * =====================================================================================
 */


    RooAddition nll("nll","nll",list);

    RooMinuit mm(nll);
    mm.migrad();
    // mm.hesse();
    //mm.minos();

    RooFitResult *rs = mm.save();
    ofstream fout("mcstudy3.txt");
    Double_t r_mass, r_width;
    TString s_mass = v_mean->GetName();
    TString s_width = v_gamma->GetName();
    for(int itoy=0; itoy<1000; itoy++){
        RooArgList check = rs->randomizePars();
        TIterator *parIter = check.createIterator();
        RooRealVar *par(0);
        while(0 !=(par = (RooRealVar*)parIter->Next())){
            if(par->GetName() == s_mass) r_mass = par->getVal();
            if(par->GetName() == s_width) r_width = par->getVal();
        }
        fout<<setw(15)<<setprecision(6)<<setiosflags(ios::left)<<r_mass
            <<setw(15)<<setprecision(6)<<setiosflags(ios::left)<<r_width<<endl;
        delete parIter;
    }

    fout.close();


    TCanvas *c1=new TCanvas("c1","",800,800);
    c1->cd();
    TPad *pad1 = new TPad("pad1","",0.0,0.25,1.0,1.0);
    pad1->SetBottomMargin(0.00);
    pad1->SetLeftMargin(0.14);
    pad1->SetBottomMargin(0.1);
    pad1->Draw();
    pad1->cd();

    RooPlot* frame1 = rmpi0_.frame(Bins(20),Range(4.01,4.09));
    //RooPlot* frame1 = rmpi0_.frame(Bins(20),Range(4.01,4.085));
    //frame1->GetXaxis()->SetTitle("RM(#pi^{0})(Gev/c^{2})");
    frame1->GetXaxis()->SetTitle("");
    frame1->SetTitle("");
    set_data_1->plotOn(frame1);
    model_1->plotOn(frame1, LineColor(kBlack), LineWidth(3),LineStyle(1));
    model_1->plotOn(frame1,Components(sigxgauss_tot_1), LineColor(kRed), LineWidth(3),LineStyle(1));
    model_1->plotOn(frame1,Components(bkgpdf_1), LineColor(kGreen), LineWidth(3),LineStyle(1));
    model_1->plotOn(frame1,Components(*pdf_PHSP_1), LineColor(kBlue), LineWidth(3),LineStyle(1));
    frame1->Draw();
    TLatex *t = new TLatex();
    t->SetNDC();
    t->SetTextFont(62);
    t->SetTextColor(2);
    t->SetTextSize(0.08);
    t->DrawLatex(0.63,0.66,"4230"); 


    c1->cd();
    RooCurve *curve = (RooCurve*)frame1->getObject(1);
    RooHist *histo = (RooHist*)frame1->getObject(0);

    Int_t nh = histo->GetN();
    cout<<" nh   "<<nh<<endl;
    Double_t x[1000];
    Double_t y[1000];
    Double_t eyl[1000];
    Double_t eyh[1000];
    Double_t exl[1000];
    Double_t exh[1000];
    Double_t xstart, ystart, xstop, ystop;
    histo->GetPoint(0, xstart, ystart);
    histo->GetPoint(nh-1, xstop, ystop);
    cout<<"xstart == "<<xstart<<"  xstop == "<<xstop<<endl;

    Double_t avg[1000];
    float tx[1000];
    float tx_err[1000]={0};
    float chi[1000];
    float chi_err[1000];
    float chisq = 0;
    float tmpy(0);
    float tmpavg(0);
    float tmpeyl(0);
    float tmpeyh(0);
    Int_t ndf_4230 = 0;
    ofstream outfile("chi.dat");
    for (int i =0; i<nh; i++){
        histo->GetPoint(i, x[i], y[i]);
        if (x[i]<xstart || x[i]>xstop) continue;
        exl[i] = histo->GetEXlow()[i];
        exh[i] = histo->GetEXhigh()[i];
        eyl[i] = histo->GetEYlow()[i];
        eyh[i] = histo->GetEYhigh()[i];
        avg[i] = curve->average(x[i]-exl[i], x[i]+exh[i]);
        //avg[i] = NormalizedIntegral(model_1, mx, x[i]-exl[i], x[i]+exh[i]) * 26725;
        tmpy += y[i];
        tmpavg += avg[i];
        //tmpeyl = sqrt(tmpeyl*tmpeyl + eyl[i]*eyl[i]);
        //tmpeyh = sqrt(tmpeyh*tmpeyh + eyh[i]*eyh[i]);
        //if (tmpy<20) continue;
        //if (tmpavg<10) continue;
        tx[ndf_4230] = x[i];
        chi[ndf_4230] = (tmpy-tmpavg)/sqrt(tmpavg);
        //chi[ndf_4260] = (tmpy>tmpavg)?((tmpy-tmpavg)/tmpeyl) : ((tmpy-tmpavg)/tmpeyh);
        chi_err[ndf_4230] = sqrt(tmpy/tmpavg);
        chisq += chi[ndf_4230]*chi[ndf_4230];
        /*  outfile<<
            setw(15)<<setprecision(6)<<setiosflags(ios::left)<<tx[ndf_4260]<<
            setw(15)<<setprecision(6)<<setiosflags(ios::left)<<tmpy<<
            setw(15)<<setprecision(6)<<setiosflags(ios::left)<<tmpavg<<
            setw(15)<<setprecision(6)<<setiosflags(ios::left)<<chi[ndf_4260]<<endl;
            */
        tmpy = 0;
        tmpavg = 0;
        tmpeyl = 0;
        tmpeyh = 0;
        ndf_4230++;
    }
    cout<<ndf_4230<<endl;
    TH2F *h2=new TH2F("h2","",xbin,xmin_,xmax_, 20,-5,5);
    TPad *pad2=new TPad("pad2","",0.0,0.0,1.0,0.25);
    pad2->SetTopMargin(0.1);
    pad2->SetBottomMargin(0.4);
    pad2->SetLeftMargin(0.14);
    pad2->Draw();
    pad2->cd();
    c1->Update();
    gStyle->SetOptStat(0);
    TGraphErrors *diff=new TGraphErrors(xbin,tx,chi,tx_err,chi_err);

    h2->Draw();
    h2->SetYTitle("#chi");
    h2->GetYaxis()->SetTitleSize(0.1);
    h2->GetYaxis()->SetTitleOffset(0.3);
    h2->GetYaxis()->SetNdivisions(501);
    h2->GetYaxis()->SetLabelSize(0.15);
    h2->GetYaxis()->CenterTitle();
    h2->GetXaxis()->CenterTitle();
    h2->GetXaxis()->SetLabelSize(0.16);
    h2->SetXTitle("RM(#pi^{0})(GeV/c^{2})");
    h2->GetXaxis()->SetTitleSize(0.18);
    h2->GetXaxis()->SetTitleOffset(1);

    diff->SetMarkerStyle(20);
    diff->Draw("Psame");

    TLine *Line=new TLine(xmin_,0,xmax_,0);
    Line->Draw();

    //c1->SaveAs("massdependentfit_4230.eps");
    //c1->SaveAs("fit_nosignal_4230.eps");
    c1->SaveAs("fit_Phsp_4230.eps");



    TCanvas *c2=new TCanvas("c2","",800,800);
    c2->cd();
    TPad *pad1_ = new TPad("pad1_","",0.0,0.25,1.0,1.0);
    pad1_->SetBottomMargin(0.00);
    pad1_->SetLeftMargin(0.14);
    pad1_->SetBottomMargin(0.1);
    pad1_->Draw();
    pad1_->cd(); 


    RooPlot* frame2 = rmpi0.frame(Bins(20),Range(4.01,4.11));
    //RooPlot* frame2 = rmpi0.frame(Bins(20),Range(4.01,4.105));
    //frame2->GetXaxis()->SetTitle("RM(#pi^{0})(Gev/c^{2})");
    frame2->GetXaxis()->SetTitle("");
    frame2->SetTitle("");
    set_data_2->plotOn(frame2);
    model_2->plotOn(frame2, LineColor(kBlack), LineWidth(3),LineStyle(1));
    model_2->plotOn(frame2, Components(sigxgauss_tot_2),LineColor(kRed), LineWidth(3),LineStyle(1));
    model_2->plotOn(frame2,Components(bkgpdf_2), LineColor(kGreen), LineWidth(3),LineStyle(1));
    model_2->plotOn(frame2,Components(*pdf_PHSP_2), LineColor(kBlue), LineWidth(3),LineStyle(1));

    frame2->Draw();
    TLatex *t_ = new TLatex();
    t_->SetNDC();
    t_->SetTextFont(62);
    t_->SetTextColor(4);
    t_->SetTextSize(0.08);
    t_->DrawLatex(0.63,0.66,"4260"); 
    c2->cd();
    RooCurve *curve_ = (RooCurve*)frame2->getObject(1);
    RooHist *histo_ = (RooHist*)frame2->getObject(0);

    Int_t nh_ = histo_->GetN();
    cout<<" nh_   "<<nh_<<endl;
    Double_t x_[1000];
    Double_t y_[1000];
    Double_t eyl_[1000];
    Double_t eyh_[1000];
    Double_t exl_[1000];
    Double_t exh_[1000];
    Double_t xstart_, ystart_, xstop_, ystop_;
    histo_->GetPoint(0, xstart_, ystart_);
    histo_->GetPoint(nh_-1, xstop_, ystop_);
    cout<<"xstart == "<<xstart_<<"  xstop == "<<xstop_<<endl;

    Double_t avg_[1000];
    float tx_[1000];
    float tx_err_[1000]={0};
    float chi_[1000];
    float chi_err_[1000];
    float chisq_ = 0;
    float tmpy_(0);
    float tmpavg_(0);
    float tmpeyl_(0);
    float tmpeyh_(0);
    Int_t ndf_4260 = 0;
    cout<<"hehe"<<endl;
    ofstream outfile_("chi_.dat");
    for (int i =0; i<nh_; i++){
        histo_->GetPoint(i, x_[i], y_[i]);
        if (x_[i]<xstart_ || x_[i]>xstop_) continue;
        exl_[i] = histo_->GetEXlow()[i];
        exh_[i] = histo_->GetEXhigh()[i];
        eyl_[i] = histo_->GetEYlow()[i];
        eyh_[i] = histo_->GetEYhigh()[i];
        avg_[i] = curve_->average(x_[i]-exl_[i], x_[i]+exh_[i]);
        //avg_[i] = NormalizedIntegral(model_1, mx, x[i]-exl[i], x[i]+exh[i]) * 26725;
        tmpy_ += y_[i];
        tmpavg_ += avg_[i];
        //tmpeyl = sqrt(tmpeyl*tmpeyl + eyl[i]*eyl[i]);
        //tmpeyh = sqrt(tmpeyh*tmpeyh + eyh[i]*eyh[i]);
        //if (tmpy<20) continue;
        //if (tmpavg<10) continue;
        tx_[ndf_4260] = x_[i];
        chi_[ndf_4260] = (tmpy_-tmpavg_)/sqrt(tmpavg_);
        //chi[ndf_4260] = (tmpy>tmpavg)?((tmpy-tmpavg)/tmpeyl) : ((tmpy-tmpavg)/tmpeyh);
        chi_err_[ndf_4260] = sqrt(tmpy_/tmpavg_);
        chisq_ += chi_[ndf_4260]*chi_[ndf_4260];

        tmpy_ = 0;
        tmpavg_ = 0;
        tmpeyl_ = 0;
        tmpeyh_ = 0;
        ndf_4260++;
    }
    cout<<"hehe"<<endl;
    cout<<ndf_4260<<endl;
    TH2F *h2_=new TH2F("h2_","",xbin,xmin,xmax, 20,-5,5);
    TPad *pad2_=new TPad("pad2_","",0.0,0.0,1.0,0.25);
    pad2_->SetTopMargin(0.1);
    pad2_->SetBottomMargin(0.4);
    pad2_->SetLeftMargin(0.14);
    pad2_->Draw();
    pad2_->cd();
    c2->Update();
    gStyle->SetOptStat(0);
    TGraphErrors *diff_=new TGraphErrors(xbin,tx_,chi_,tx_err_,chi_err_);

    h2_->Draw();
    h2_->SetYTitle("#chi");
    h2_->GetYaxis()->SetTitleSize(0.1);
    h2_->GetYaxis()->SetTitleOffset(0.3);
    h2_->GetYaxis()->SetNdivisions(501);
    h2_->GetYaxis()->SetLabelSize(0.15);
    h2_->GetYaxis()->CenterTitle();
    h2_->GetXaxis()->CenterTitle();
    h2_->GetXaxis()->SetLabelSize(0.16);
    h2_->SetXTitle("RM(#pi^{0})(GeV/c^{2})");
    h2_->GetXaxis()->SetTitleSize(0.18);
    h2_->GetXaxis()->SetTitleOffset(1);

    diff_->SetMarkerStyle(20);
    diff_->Draw("Psame");

    TLine *Line_=new TLine(xmin,0,xmax,0);
    Line_->Draw();

  //  c2->SaveAs("massdependentfit_4260.eps");
   // c2->SaveAs("fit_nosignal_4260.eps");
    c2->SaveAs("fit_Phsp_4260.eps");

}


