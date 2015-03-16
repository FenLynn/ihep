#!bin/tcsh
# python ttH_compareshape.py filename1 filename2 variablename cutname weightname1 weightname2 index1 bin_ min_ max_ xtitle additionname

#python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.Px "1==1" "1==1" "noindex" 0 50 -200 200 "Px" "Px"
#python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.Py "1==1" "1==1" "noindex" 0 50 -200 200 "Py" "Py"
#python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.Pz "1==1" "1==1" "noindex" 0 50 -1000 1000 "Pz" "Pz"
#python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.E "1==1" "1==1" "noindex" 0 50 0 1000 "E" "E"
#python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.M "1==1" "1==1" "noindex" 0 50 80 130 "M" "M"
#python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.PT "(Particle.PID==-11||Particle.PID==11||Particle.PID==-13||Particle.PID==13||Particle.PID==-15||Particle.PID==15)&&(Particle.PT>=10)&&(Particle.Eta<=2.5)" "1==1" "noindex" 0 50 0 200 "LeptonPT" "LeptonPT"
#python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.Eta "1==1" "1==1" "noindex" 0 50 -3 3 "Eta" "Eta"
#python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.Phi "1==1" "1==1" "noindex" 0 50 -3 3 "Phi" "Phi"
#python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.Rapidity "1==1" "1==1" "noindex" 0 50 -25 25 "Rapidity" "Rapidity"
#python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.LifeTime "1==1" "1==1" "noindex" 0 50 -1 1 "LifeTime" "LifeTime"

# ---------------------Lepton, pt eta cut------------------------------------

python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.Px "(Particle.PID==-11||Particle.PID==11||Particle.PID==-13||Particle.PID==13||Particle.PID==-15||Particle.PID==15)&&(Particle.PT>=10)&&(Particle.Eta<=2.5)&&(Particle.Eta>=-2.5)" "1==1" "noindex" 0 50 -200 200 "Px" "Px"
python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.Py "(Particle.PID==-11||Particle.PID==11||Particle.PID==-13||Particle.PID==13||Particle.PID==-15||Particle.PID==15)&&(Particle.PT>=10)&&(Particle.Eta<=2.5)&&(Particle.Eta>=-2.5)" "1==1" "noindex" 0 50 -200 200 "Py" "Py"
python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.Pz "(Particle.PID==-11||Particle.PID==11||Particle.PID==-13||Particle.PID==13||Particle.PID==-15||Particle.PID==15)&&(Particle.PT>=10)&&(Particle.Eta<=2.5)&&(Particle.Eta>=-2.5)" "1==1" "noindex" 0 50 -1000 1000 "Pz" "Pz"
python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.E "(Particle.PID==-11||Particle.PID==11||Particle.PID==-13||Particle.PID==13||Particle.PID==-15||Particle.PID==15)&&(Particle.PT>=10)&&(Particle.Eta<=2.5)&&(Particle.Eta>=-2.5)" "1==1" "noindex" 0 50 0 1000 "E" "E"
python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.M "(Particle.PID==-11||Particle.PID==11||Particle.PID==-13||Particle.PID==13||Particle.PID==-15||Particle.PID==15)&&(Particle.PT>=10)&&(Particle.Eta<=2.5)&&(Particle.Eta>=-2.5)" "1==1" "noindex" 0 50 80 130 "M" "M"
python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.PT "(Particle.PID==-11||Particle.PID==11||Particle.PID==-13||Particle.PID==13||Particle.PID==-15||Particle.PID==15)&&(Particle.PT>=10)&&(Particle.Eta<=2.5)&&(Particle.Eta>=-2.5)" "1==1" "noindex" 0 50 0 200 "LeptonPT" "LeptonPT"
python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.Eta "(Particle.PID==-11||Particle.PID==11||Particle.PID==-13||Particle.PID==13||Particle.PID==-15||Particle.PID==15)&&(Particle.PT>=10)&&(Particle.Eta<=2.5)&&(Particle.Eta>=-2.5)" "1==1" "noindex" 0 50 -3 3 "Eta" "Eta"
python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.Phi "(Particle.PID==-11||Particle.PID==11||Particle.PID==-13||Particle.PID==13||Particle.PID==-15||Particle.PID==15)&&(Particle.PT>=10)&&(Particle.Eta<=2.5)&&(Particle.Eta>=-2.5)" "1==1" "noindex" 0 50 -3 3 "Phi" "Phi"
python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.Rapidity "(Particle.PID==-11||Particle.PID==11||Particle.PID==-13||Particle.PID==13||Particle.PID==-15||Particle.PID==15)&&(Particle.PT>=10)&&(Particle.Eta<=2.5)&&(Particle.Eta>=-2.5)" "1==1" "noindex" 0 50 -25 25 "Rapidity" "Rapidity"
python ttH_compareshape.py JHUGenerator_ZH_SM MadGraph_ZH_SM Particle.LifeTime "(Particle.PID==-11||Particle.PID==11||Particle.PID==-13||Particle.PID==13||Particle.PID==-15||Particle.PID==15)&&(Particle.PT>=10)&&(Particle.Eta<=2.5)&&(Particle.Eta>=-2.5)" "1==1" "noindex" 0 50 -1 1 "LifeTime" "LifeTime"
