# echo "Setting EemissAlg EemissAlg-00-00-08 in /besfs/users/lify/Analysis"

if test "${CMTROOT}" = ""; then
  CMTROOT=/afs/ihep.ac.cn/bes3/offline/ExternalLib/contrib/CMT/v1r20p20081118; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh

tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=EemissAlg -version=EemissAlg-00-00-08 -path=/besfs/users/lify/Analysis  -no_cleanup $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

