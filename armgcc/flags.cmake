IF(NOT DEFINED SPECS)  
    SET(SPECS "--specs=nano.specs --specs=nosys.specs")  
ENDIF()  

SET(CPU "-mcpu=cortex-m4")
SET(FPU "-mfpu=fpv4-sp-d16")
SET(FLOAT-ABI "-mfloat-abi=hard")
SET(MCU "${CPU} -mthumb ${FPU} ${FLOAT-ABI}")
SET(LINK_FILE "STM32F411CEUx_FLASH.ld")
SET(COMPILE_OPTION_LEVEL 1)
SET(DEVICE "STM32F411xE")
SET(DRIVER_LIB "USE_STDPERIPH_DRIVER")

SET(COM_FLAG " \
    -Wall \
    -ffunction-sections \
    -fdata-sections \
")

SET(C_CXX_FLAG " \
    -D${DEVICE} \
    -D${DRIVER_LIB} \
    ${COM_FLAG} \
    -MMD \
    -MP \
    -Wno-address-of-packed-member \
    -O${COMPILE_OPTION_LEVEL} \
")

SET(CMAKE_ASM_FLAGS_FLASH_DEBUG " \
    ${CMAKE_ASM_FLAGS_FLASH_DEBUG} \
    ${MCU} \
")

SET(CMAKE_C_FLAGS_FLASH_DEBUG " \
    ${CMAKE_C_FLAGS_FLASH_DEBUG} \
    ${C_CXX_FLAG} \
    -g \
    -std=gnu99 \
    ${MCU} \
")

SET(CMAKE_CXX_FLAGS_FLASH_DEBUG " \
    ${CMAKE_CXX_FLAGS_FLASH_DEBUG} \
    ${C_CXX_FLAG} \
    -g \
    -fno-rtti \
    -fno-exceptions \
    ${MCU} \
")

SET(CMAKE_EXE_LINKER_FLAGS_FLASH_DEBUG " \
    ${CMAKE_EXE_LINKER_FLAGS_FLASH_DEBUG} \
    ${MCU} \
    ${SPECS} \
    -T${ProjDirPath}/${LINK_FILE} \
    -g \
    -lm -lc -lgcc -lnosys \
    -Wl,--print-memory-usage \
    -Wl,-Map=${EXECUTABLE_OUTPUT_PATH}/output.map,--cref \
    -Wl,--gc-sections\
")