include_guard()
message("ST emWin Library component is included.")

file(GLOB ST_LIB_SRC_FILE 
    ${CMAKE_CURRENT_LIST_DIR}/UserConfig/*.c
)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ST_LIB_SRC_FILE}
)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/Lib/STemWin532_CM4_GCC.a
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/UserConfig
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

