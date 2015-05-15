/*
 *======================================================================================
 *       FILENAME: get_no.C
 *        CREATED: 2014年12月10日 00时00分24秒
 *         AUTHOR: Fengyun Li,lfypku@gmail.com
 *    DESCRIPTION: 
 * =====================================================================================
 */
{
	TChain *f=new TChain("nbinfo","");
	f->Add("../*.root");
	char *nb="num";
	f->MakeClass(nb);
	system("cp ./numbak.C ./num.C");
	cout<<"num class made finished"<<endl;
}

