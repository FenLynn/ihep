# This is a script to create a new package. When you copied a well-configured package like RhopiAlg to create a new one like Dimuon-
# Alg, the script change the old name to new ones in all the directories and files. Note: put this file under the first directory of
# the new package (for safety purpose) like DimuonAlg/ (which is changed manualy)  and run.  Modified by Xinkun Chu 2012.09.16 

if [ -f FileList2 ]; then
mv -f FileList2  FileList2.bak
fi
find . -name '*00*'   > FileList2
while read MY_LINE
do
if [ -d $MY_LINE ]; then
echo $MY_LINE
rename Eemiss Topo $MY_LINE
fi
done < FileList2 

if [ -f FileList2 ]; then
mv -f FileList2  FileList2.bak
fi
find . -name '*Alg*' > FileList2 
while read MY_LINE
do
if [ -d $MY_LINE ]; then
echo $MY_LINE
rename Eemiss Topo $MY_LINE
fi
done < FileList2

if [ -f FileList ]; then
mv -f FileList  FileList.bak
fi
find . -name '*.h'   >>FileList
find . -name '*.cxx' >>FileList
find . -name '*.txt' >>FileList
find . -name 'requirements' >>FileList
while read MY_LINE
do 
if [ ! -d $MY_LINE ]; then
echo $MY_LINE
mv $MY_LINE $MY_LINE.bak
sed  "s/Eemiss/Topo/g;s/eemiss/topo/g;s/EEMISS/TOPO/g"  $MY_LINE.bak > $MY_LINE
rename Eemiss Topo $MY_LINE
rename eemiss topo $MY_LINE
rm -f $MY_LINE.bak
fi
done < FileList

rm -f FileList*

 
