#!/bin/bash
alias root="root -l"
alias histg="history | grep"
alias la='ls -al'
alias lh='ls -lh'
alias grep='grep --color=auto'
alias du1='du -h --max-depth 1'
alias du2='du -h --max-depth 2'
alias qs="qstat -u $USER"
alias lt='ls -lt'
#PS1="\[\e[0;34m\][\[\e[m\]\[\e[0;32m\]\u\[\e[m\]\[\e[0;32m\]@\[\e[m\]\[\e[0;32m\]\h\[\e[m\] \[\e[0;36m\]\A\[\e[m\] \[\e[0;31m\]\W\[\e[m\]\[\e[0;34m\]]\[\e[m\]\$ "
#export PS1="\[\e[0;34m\][\[\e[m\]\[\e[0;32m\]\u\[\e[m\]\[\e[0;32m\]@\[\e[m\]\[\e[0;32m\]\h\[\e[m\] \[\e[0;36m\]\A\[\e[m\] \[\e[0;35m\]\W\[\e[m\]\[\e[0;34m\]]\[\e[m\]\[\e[0;34m\]\$\[\e[m\] \[\e[0;31m\]"
NOHOST=`echo $HOSTNAME|cut -c 6-8`

#if [ $BES_RELEASE ];then
#	BES_VER=" $BES_RELEASE "
#else
#	BES_VER=" "
#fi

if [ $WorkArea ];then
	BES_VER=" "`basename $WorkArea`" "	
elif [ $BES_RELEASE ];then
	BES_VER=" $BES_RELEASE "
else
	BES_VER=" "
fi

export PS1="\[\e[0;34m\][\[\e[m\]\[\e[0;31m\]\u\[\e[m\]\[\e[0;31m\]@\[\e[m\]\[\e[0;31m\]${NOHOST}\[\e[m\]\[\e[0;32m\]${BES_VER}\[\e[m\]\[\e[0;36m\]\A\[\e[m\] \[\e[0;35m\]\W\[\e[m\]\[\e[0;34m\]]\[\e[m\]\[\e[0;34m\]\$\[\e[m\] \[\e[0;33m\]"
#export PS1="\[\e[0;34m\][\[\e[m\]\[\e[0;33m\]\u\[\e[m\]\[\e[0;33m\]@\[\e[m\]\[\e[0;33m\]${NOHOST}\[\e[m\] \[\e[0;36m\]\A\[\e[m\] \[\e[0;35m\]\W\[\e[m\]\[\e[0;34m\]]\[\e[m\]\[\e[0;34m\]\$\[\e[m\] \[\e[0;31m\]"
