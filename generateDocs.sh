#!/bin/bash

set -e

WORK_DIR=$(pwd)

rm -rf doxygen
doxygen Doxyfile

cd doxygen/latex
make
cd ${WORK_DIR}