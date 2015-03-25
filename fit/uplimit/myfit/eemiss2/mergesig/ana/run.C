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
	gROOT->ProcessLine(".L df.C++");

	if(debug==0)
	{
		gROOT->ProcessLine("df t");
		gROOT->ProcessLine("t.Loop()");
		gROOT->ProcessLine(".q");
	}


}
