{
	gSystem->Load("libMathCore");
	
  double mean  = 5.21439e+00;
	double sigma = 3.18965e+00;
	
  int N = 8;
	double total_prob = ROOT::Math::gaussian_prob(0, sigma, mean);
	std::cout << "prob(0,sigma,mean) = " << total_prob << ";// the prob from x = 0 to +oo" << std::endl;
	for (int i = 1; i < 30; i++) {
		double intup_prob = ROOT::Math::gaussian_prob(N + i * 0.05, sigma, mean);
		double ratio = intup_prob / total_prob;
		//cout << " intup = " << intup << "; ratio = " << ratio << endl;
		std::cout << (N + i * 0.05) << " ,  intup_prob= " << intup_prob<<",  ratio= " << ratio << std::endl;
	}
//(when step=0.5)
  //mean= 5.21439e+00, Sigma= 3.18965e+00
  //N=9.4 , total_prob=0.948953,  intup_prob= 0.0947183,  ratio= 0.0998135

  
  
//(when step=0.2)
  //mean= 5.20614e+00, Sigma= 3.20410e+00 
  //N=9.4 , total_prob=0.947901 , intup_prob=0.0952834,   ratio= 0.10052 
}
