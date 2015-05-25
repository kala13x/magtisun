#!/bin/bash

cd ${PWD##}/libmagtisun
make clean
make

cd ../libslog
make clean
make

cd ..
make clean
make

echo "[-] Build done"