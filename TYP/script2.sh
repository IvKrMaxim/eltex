#!/bin/bash
H=`date '+%H'`
M=`date '+%M'`
S=`date '+%S'`
PUTH=$*'_'$H'_'$M'_'$S.tar
tar -cvf $PUTH $HOME/*.txt