#!/bin/bash
cd ..;
BASEDIR=`pwd`;
export BASEDIR;
cd doc;

/usr/local/bin/phpdoc -o HTML:frames:DOM/phphtmllib \
-j on \
-s on \
-ric \
-t $BASEDIR/doc \
-d $BASEDIR \
-dn phpHtmlLib \
-dc phpHtmlLib \
-ti phpHtmlLib \
-i *css*,*doc*,*test*,*init.inc*,*autoload.inc*,includes.inc,*scriptaculous*,*project_templates*
