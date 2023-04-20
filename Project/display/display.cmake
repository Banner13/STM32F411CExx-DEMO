include_guard()
message("display function.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/display.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

