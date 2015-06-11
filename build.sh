#!/bin/bash

cd ${PWD##}/magtisun
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