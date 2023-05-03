#!/bin/sh
if [ -d "temp_build" ];then rm -rf temp_build; fi
if [ -d "flash_debug" ];then rm -rf flash_debug; fi
DEBUG_FLAG=''
if [ $# ]; then
if [[ $1 -eq 'D' ]];then DEBUG_FLAG='-DDEBUG=1'; fi
fi
mkdir temp_build && cd temp_build
cmake ${DEBUG_FLAG} -DCMAKE_TOOLCHAIN_FILE="../armgcc.cmake" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=flash_debug  ..
make -j4 2>&1 | tee build_log.txt
