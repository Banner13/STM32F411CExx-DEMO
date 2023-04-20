#!/bin/sh
if [ ! -d "temp_build" ];then echo "Error: Not found temp_build" && exit; fi
cd temp_build
make -j4 2>&1 | tee build_log.txt
