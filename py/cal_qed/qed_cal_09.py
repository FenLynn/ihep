def calcQEDscale(nsample_qed = 1E7):
	xsec = 1069.5581142  ## in nb, from Vindy
	xsec_err = 3.7191714 ## from Vindy
	lumi_jpsi = 79.631 ## pb-1, from BAM-123
	num_jpsi = 223.72E6 ##2009 Jpsi#
	numerr_jpsi= 7.0E6 ##2012+2009 Jpsi# err

	num_qed =  lumi_jpsi*xsec*1000
	s_qed = num_qed/nsample_qed
	return s_qed

print calcQEDscale(1E7);
