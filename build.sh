#!/bin/bash

cd ${PWD##}/lib
make clean
make

cd ../slog
make clean
make

cd ../src
make clean
make

cd ..

echo "[-] Build done"