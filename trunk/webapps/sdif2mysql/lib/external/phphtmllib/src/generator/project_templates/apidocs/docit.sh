#!/bin/bash
cd ..;
BASEDIR=`pwd`;
export BASEDIR;
cd apidocs;

XX_PHPDOC_PATH_XX -o HTML:frames:DOM/phphtmllib \
-j on \
-s on \
-t $BASEDIR/apidocs \
-d $BASEDIR \
-dn XX_PROJECT_NAME_XX \
-ti XX_PROJECT_NAME_XX \
-i *css*,*doc*,*bin*,*test*,*init.inc*,*autoload.inc*,includes.inc,*scriptaculous*,*project_templates*
