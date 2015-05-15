/*
 *======================================================================================
 *       FILENAME: run.C
 *        CREATED: 2014年12月11日 12时01分41秒
 *         AUTHOR: Fengyun Li,lfypku@gmail.com
 *    DESCRIPTION: 
 * =====================================================================================
 */
{
	int debug=0;
	//system("pwd");
	gROOT->ProcessLine(".x mkclass.C");
	gROOT->ProcessLine(".L num.C++");

	if(debug==0)
	{
		gROOT->ProcessLine("num t");
		gROOT->ProcessLine("t.Loop()");
		gROOT->ProcessLine(".q");
	}


}
