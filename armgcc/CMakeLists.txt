# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.23.0)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
SET(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})


project(DEMO)

set(MCUX_SDK_PROJECT_NAME DEMO.elf)

if (NOT DEFINED SdkRootDirPath)
    SET(SdkRootDirPath ${ProjDirPath}/..)
endif()

include(${ProjDirPath}/flags.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../main.c")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${ProjDirPath}/..
)

set(CMAKE_MODULE_PATH
    ${SdkRootDirPath}/Ext_Lib
    ${SdkRootDirPath}/Project
    ${SdkRootDirPath}/Peripheral
    ${SdkRootDirPath}/Algorithm
)

# include modules
include(Ext_Lib)
include(My_Project)
include(My_Peripheral)
include(Algorithm)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

# Create hex file
ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex   ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/hello_world.hex
        COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/hello_world.bin)

# Print executable size
ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME}
        POST_BUILD
        COMMAND echo "-----------------------------------------------------------------------------------------------------")

# Print executable size
ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME})

