#!/usr/bin/bash

echo "Clearing binary ..."
rm -f bin/*.*o

echo "Clearing dpkgs ..."
rm -f ./*.deb

exit 0
