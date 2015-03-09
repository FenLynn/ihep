	histname->GetXaxis()->SetTitle("M(e^{-}) [GeV/c^{2}]");                         
	histname->GetYaxis()->SetTitle("Events");                                       
	histname->SetStats(0);                                       
	histname->SetLineColor(color_no);                                                 
	histname->SetLineWidth(2);
	histname->SetMarkerSize(1);
	histname->SetMarkerStyle(style_no);
	histname->Draw(draw_no);                                                          
	legend->AddEntry(histname,histtype_no);   

