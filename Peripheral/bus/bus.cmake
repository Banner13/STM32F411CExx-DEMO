include_guard()
message("all class peripheral.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

include(${CMAKE_CURRENT_LIST_DIR}/i2c/i2c.cmake)

