{
	gSystem->Load("libMathCore");
  ifstream input;
  //input.open("bkg4th_fitmetap_step_zero_point2.txt");//12.4 at 90% C.L
  //input.open("Narrow_Range_fitmetap_step_zero_point2.txt");//12.6 
  
  //input.open("Wider_Range_fitmetap_step_zero_point2.txt"); 
  //9.2  at 90% C.L(0.82-1.10)
  //11.6 at 90% C.L(0.85-1.07)
  
  //input.open("tmp_fitmetap.txt"); // upper limit of signal number is 11.8 at 90% C.L.
  
  
  //input.open("fitmetap_087_102.txt"); // 2nd,a0,a1 [0.87-1.02] nEvent=10.6 at 90% C.L.
 
  
  //input.open("Fit_uncertainty_087_102_bkgShape_2nd/fitmetap_leftRightW.txt"); // 2nd,a0,a1 [0.85-1.04] nEvent=9.8 
  //input.open("Fit_uncertainty_087_102_bkgShape_2nd/fitmetap_LeftW.txt");      // 2nd,a0,a1 [0.85-1.02] nEvent=9.6 
  //input.open("Fit_uncertainty_087_102_bkgShape_2nd/fitmetap_LeftN.txt");      // 2nd,a0,a1 [0.89-1.02] nEvent=10.6 
  //input.open("Fit_uncertainty_087_102_bkgShape_2nd/fitmetap_LeftRightN.txt"); // 2nd,a0,a1 [0.89-1.00] nEvent=11.4 
  //input.open("Fit_uncertainty_087_102_bkgShape_2nd/fitmetap_RightN.txt");     // 2nd,a0,a1 [0.87-1.00] nEvent=10.8 
  //input.open("Fit_uncertainty_087_102_bkgShape_2nd/fitmetap_RightW.txt");     // 2nd,a0,a1 [0.87-1.04] nEvent=11.0 
  //input.open("Fit_uncertainty_087_102_bkgShape_2nd/fitmetap_BkgShape_1st.txt"); // 1st,a0      [0.87-1.02] nEvent=9.8 
    input.open("./FitKs_step_zero_point2.txt"); // 3rd,a0,a1,a2[0.87-1.02] nEvent=10.0 
  
  
  //input.open("fitmetap_step_zero_point2.txt"); // 3rd,a0,a1,a2 [0.87-1.05] nEvent= 12.6 at 90% C.L.
	
  //int N = 60;
  int N = 300;
  double nEvent[N],F[N],m[N],S[N];
  double total_sum=0., sum=0.;
	
  for (int i = 0; i < N; i++) {
      
      input>>nEvent[i];
      input>>F[i];
      input>>m[i];
      input>>S[i];
//cout<<nEvent[i]<<" "<<F[i]<<" "<<m[i]<<" "<<S[i]<<endl;
	}

  for (int j = 0; j < N-1; j++) {
      double tmp = (( S[j] + S[j+1] ) * ( nEvent[j+1] - nEvent[j] ))/2.;
      total_sum += tmp; 
  }
  cout<<"total Size="<<total_sum<<", 0.9*total_sum="<<(0.9*total_sum)<<endl; 

  for(int j=0;j<N-1;j++){
     
      double tmp = (( S[j] + S[j+1] ) * ( nEvent[j+1] - nEvent[j] ))/2.;
      
      sum += tmp;
      if(sum>(0.89*total_sum) ||sum==(0.90*total_sum)) 
         //cout<<"nEvent="<<nEvent[j]<<" S= "<<S[j]<<endl;
         cout<<"nEvent="<<nEvent[j]<<" S= "<<S[j]<<" ratio="<<(sum/total_sum)<<endl;
 }

//(when step=0.5) tatal    S=90.3663
  //nEvent=12  S= 0.15795  ratio=0.907667
  
//(when step=0.2) tatal    S=317.721
//nEvent=14    S= 0.17018 ratio=0.900473
}
