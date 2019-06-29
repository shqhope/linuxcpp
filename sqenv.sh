#!/bin/bash
#打造一个脚本，创建sq工作环境，包括git代码和配置本地路径及代码
bdir=$HOME"/shqdir"

if [ -d $bdir ]
then
	echo dir $bdir exists;
else
	echo create dir $bdir;
	mkdir $bdir;
fi 

#创建子目录，数组形式
cd $bdir

arrsubdir=("shq_make" "shq_shell" "shq_libs")

#echo ${#arrsubdir[*]}
#echo $((${#arrsubdir[*]}+1))

for((i=0;i<${#arrsubdir[*]};i++))
do
	#echo ${arrsubdir[$i]};
	if [ ! -d ${arrsubdir[$i]} ]
	then
		mkdir ${arrsubdir[$i]};
	else
		echo dir ${arrsubdir[$i]} exists
	fi
done

