include_guard()
message("device_STM32F411CE_startup component is included.")

file(GLOB ST_LIB_SRC_FILE 
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f401xx.s
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
    ${CMAKE_CURRENT_LIST_DIR}/stm32f4xx_it.c
    ${ST_LIB_SRC_FILE}
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/CMSIS/Include
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/STM32F4xx_StdPeriph_Driver/inc
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/CMSIS/Device/ST/STM32F4xx/Include
)

