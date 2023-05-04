include_guard()
message("All external Library.")

# STM32F10x_StdPeriph_Driver
include(${CMAKE_CURRENT_LIST_DIR}/ST_Lib/STM32F4x_StdPeriph_Driver.cmake)

# ST emWin Library
include(${CMAKE_CURRENT_LIST_DIR}/STemWinLibrary/STemWinLibrary.cmake)
