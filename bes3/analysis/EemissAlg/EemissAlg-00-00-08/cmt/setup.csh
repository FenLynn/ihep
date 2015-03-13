# echo "Setting EemissAlg EemissAlg-00-00-08 in /besfs/users/lify/Analysis"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /afs/ihep.ac.cn/bes3/offline/ExternalLib/contrib/CMT/v1r20p20081118
endif
source ${CMTROOT}/mgr/setup.csh

set tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set tempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=EemissAlg -version=EemissAlg-00-00-08 -path=/besfs/users/lify/Analysis  -no_cleanup $* >${tempfile}; source ${tempfile}
/bin/rm -f ${tempfile}

