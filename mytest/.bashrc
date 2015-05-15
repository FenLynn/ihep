# .bashrc
# my bashrc
# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi


source /workfs/bes/lify/myinclude/shell/alias.sh
source /workfs/bes/lify/myinclude/shell/func.sh
alias KK='cd /ihepbatch/bes/luhn/workarea664/Analysis/KKAlg'
alias la='ls -al'
alias lh='ls -lh'
alias qs='qstat -u lify'
alias grep='grep --color=auto'

alias scrfs='cd /scratchfs/bes/lify/664p01'
alias workfs='cd /workfs/bes/lify'
alias besfs='cd /besfs/users/lify'
alias cddir='cd /besfs/users/lify/workarea/otherswork/chuxk/DSemilepAlg/DSemilepAlg-00-00-01'
alias tchscrfs='qsub -q shortq ~/scripts/touchscratch.sh'
alias setroot='source /afs/ihep.ac.cn/soft/atlas/ROOT/v5.34.01/bin/thisroot.sh'
alias ckqstat='source ~/scripts/ckqstat.sh'
alias du1='du -h --max-depth 1'
alias du2='du -h --max-depth 2'
alias upgit='cd /workfs/bes/lify/git && source update.sh && cd ~  '

export HEADHOME=/workfs/bes/lify/myinclude
export GITHOME=/workfs/bes/lify/git


PS1="\[\e[0;34m\][\[\e[m\]\[\e[0;32m\]\u\[\e[m\]\[\e[0;32m\]@\[\e[m\]\[\e[0;32m\]\h\[\e[m\] \[\e[0;36m\]\A\[\e[m\] \[\e[0;31m\]\W\[\e[m\]\[\e[0;34m\]]\[\e[m\]\$ "
#PS1="\[\e[1;34m\][\[\e[m\]\[\e[1;32m\]\u\[\e[m\]\[\e[0;32m\]@\[\e[m\]\[\e[0;32m\]\h\[\e[m\] \[\e[4;36m\]\A\[\e[m\] \[\e[1;41m\]\W\[\e[m\]\[\e[1;34m\]]\[\e[m\]\$ "



#for root 5.34
source /afs/ihep.ac.cn/soft/atlas/ROOT/v5.34.01/bin/thisroot.sh

#for fltk
export LD_LIBRARY_PATH=/besfs/users/lify/soft/fltk-1.3.3/lib:$LD_LIBRARY_PATH
export PATH=/besfs/users/lify/soft/fltk-1.3.3:${PATH}

#for python 2.7
#export LD_LIBRARY_PATH=/besfs/users/lify/soft/python/python2.7/lib:$LD_LIBRARY_PATH
#export PATH=/besfs/users/lify/soft/python/python2.7/bin:${PATH}

#source /afs/ihep.ac.cn/bes3/offline/ExternalLib/lcg/app/releases/ROOT/5.24.00b/x86_64-slc5-gcc43-opt/root/bin/thisroot.sh

#root 5.32
#source /afs/ihep.ac.cn/soft/asgamma/root/bin/thisroot.sh

#source ~/setboss/setboss664p01.sh

#for geant4
#below has been #
#source /afs/ihep.ac.cn/soft/asgamma/geant4.10.00-install/bin/geant4.sh
#export Geant4_DIR=/afs/ihep.ac.cn/soft/asgamma/geant4.10.00-install/lib64/Geant4-10.0.1

#/afs/ihep.ac.cn/soft/asgamma/geant4.10.00-install/lib64/Geant4-10.0.1/Modules
#below has been #
#export HEPMC_DIR=~/besfs/soft/HepMC
#export HEPMCLOCATION=~/besfs/soft/HepMC

