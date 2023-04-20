include_guard()
message("kalman process.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/kalman.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

