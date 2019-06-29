#!/bin/bash

getIS()
{
    cat /sdzw/ibp/dicationary/local.xml|grep \<INDEXSERVER|grep ip|awk '{print $2}'|awk -F\" '{print $2}'
}

getWJJ()
{
    cat /sdzw/ibp/dicationary/local.xml|grep \<SJWJFWQ|grep ip|awk '{print $2}'|awk -F\" '{print $2}'
}

getALLIP()
{
    getIS
    getWJJ
}

DIRSPath=ZWFLGS
APPSPath=ZWAPPS
DIRDSTPATH=/sdzw/ibp/flg
APPDSTPATH=/sdzw/ibp/bin

#创建标志文件
touchZWFlag() #touchZWFlag 127.0.0.1 /sdzw/ibp/dictionary
{
    DESTPATH=$DIRDSTPATH;
    DICTS=`ls $DIRSPath`;
    for DICT in $DICTS
    do
	if [[ -n $2 ]]
	then
	    echo otherpath: $2;
	    $DESTPATH=$2;
	fi;
	scp -o StrictHostKeyChecking=false $DIRSPath/$DICT $1:$DESTPATH/$DICT;
	echo scp -o StrictHostKeyChecking=false $DIRSPath/$DICT $1:$DESTPATH/$DICT;
    done
}

#升级程序
installAPP()
{
    for APP in `ls ${APPSPath}`;
    do
	scp -o StrictHostKeyChecking=false $DIRSPath/$DICT $1:$DESTPATH/$DICT;

}

getLog() #getLog 127.0.0.1 zwkvdb 20171218

pkgLog() #pkgLog

    
