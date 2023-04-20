include_guard()
message("I2C sensor.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/i2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

include(${CMAKE_CURRENT_LIST_DIR}/aht10/aht10.cmake)

