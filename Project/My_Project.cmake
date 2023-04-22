include_guard()
message("My Project source code.")

include(${CMAKE_CURRENT_LIST_DIR}/board/board.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/htime/htime.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/display/display.cmake)