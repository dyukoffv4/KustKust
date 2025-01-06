#!/bin/bash

BACKUPDIR="backup $(date +"%Y-%m-%d %k:%M")"
SOURCEDIR=icons

function get_source {
  echo /usr/share/icons/Yaru/$1/apps/libreoffice-main.png
}

function get_destination {
  echo $BACKUPDIR/libreoffice-main-$1.png
}

function get_filename {
  echo $SOURCEDIR/icons8-libre-office-suite-$1.png
}

mkdir -p "$BACKUPDIR"
for i in 16x16 16x16@2x 24x24 24x24@2x 32x32 32x32@2x 48x48 48x48@2x 256x256 256x256@2x;
do
  cp $(get_source $i) "$(get_destination $i)";
  sudo cp "$(get_filename $i)" $(get_source $i);
done;
