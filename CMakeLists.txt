# Toolchain must come before first project
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arm-none-eabi-gcc.cmake
  CACHE FILEPATH "CMake ARM GCC toolchain file" FORCE
)
  
cmake_minimum_required(VERSION 3.0)

project(SensorPanelPK)

enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

set(CMAKE_EXECUTABLE_SUFFIX ".elf")

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(DRIVER_DIR ${SOURCE_DIR}/drivers)
set(MIDDLE_DIR ${SOURCE_DIR}/middlewares)
set(CORE_DIR ${SOURCE_DIR}/core)
set(CODE_DIR ${SOURCE_DIR}/code)


file(GLOB SOURCE
  ${CORE_DIR}/*.c
  ${DRIVER_DIR}/STM32F7xx_HAL_Driver/Src/*.c
  ${MIDDLE_DIR}/Third_Party/FreeRTOS/Source/*.c
  ${MIDDLE_DIR}/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/*.c
  ${MIDDLE_DIR}/Third_Party/FreeRTOS/Source/portable/MemMang/*.c
  ${MIDDLE_DIR}/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/*.c

  ${CODE_DIR}/*.cpp
  ${CODE_DIR}/screens/*.cpp
  ${CODE_DIR}/devices/*.cpp
  ${CODE_DIR}/VA_EEPROM_AT25640/*.cpp
  ${CODE_DIR}/VA_Modbus/*.cpp

  ${CODE_DIR}/VA_GUI/*.cpp
  ${CODE_DIR}/VA_GUI/Adafruit_RA8875/*.cpp
  ${CODE_DIR}/VA_GUI/Window/*.cpp
  ${CODE_DIR}/VA_GUI/Screens/*.cpp
  ${CODE_DIR}/VA_GUI/Fonts/*.cpp
  ${CODE_DIR}/VA_GUI/Fonts/TimesNewRoman/*.c

  ${CODE_DIR}/VA_GUI/Elements/*.cpp
  ${CODE_DIR}/VA_GUI/Elements/Graphics/*.cpp
  ${CODE_DIR}/VA_GUI/Elements/VAButton/*.cpp
  ${CODE_DIR}/VA_GUI/Elements/VACanvas/*.cpp
  ${CODE_DIR}/VA_GUI/Elements/VADisplay/*.cpp
  ${CODE_DIR}/VA_GUI/Elements/VAIndicator/*.cpp
  ${CODE_DIR}/VA_GUI/Elements/VAKeyboard/*.cpp
  ${CODE_DIR}/VA_GUI/Elements/VALabel/*.cpp
)
set(STARTUP
  ${CORE_DIR}/startup_stm32f746zetx.s
)

set(EXECUTABLE ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${SOURCE} ${STARTUP})

target_compile_definitions(${PROJECT_NAME} PRIVATE
  -DSTM32F746xx
  -DUSE_HAL_DRIVER
  $<$<CONFIG:Debug>: -DDEBUG>
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${SOURCE_DIR}/core
  ${SOURCE_DIR}/code/devices
  ${SOURCE_DIR}/code/screens
  ${SOURCE_DIR}/code/windows
  ${SOURCE_DIR}/code/VA_GUI
  ${SOURCE_DIR}/code/VA_EEPROM_AT25640
  ${SOURCE_DIR}/code
  ${SOURCE_DIR}/drivers/STM32F7xx_HAL_Driver/Inc
  ${SOURCE_DIR}/drivers/STM32F7xx_HAL_Driver/Inc/Legacy
  ${SOURCE_DIR}/drivers/CMSIS/Device/ST/STM32F7xx/Include
  ${SOURCE_DIR}/drivers/CMSIS/Include
  ${SOURCE_DIR}/middlewares/Third_Party/FreeRTOS/Source/include
  ${SOURCE_DIR}/middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
  ${SOURCE_DIR}/middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1
#  ${SOURCE_DIR}/etl/include/etl
)



target_compile_options(${PROJECT_NAME} PRIVATE
  -mcpu=cortex-m7
  -mthumb
  -mfloat-abi=hard
  -mfpu=fpv5-sp-d16
  -c

  -fdata-sections
  -ffunction-sections
#  -fno-rtti
#  -fno-use-cxa-atexit
  -Wall
#  -Winline
  -fstack-usage

  --specs=nano.specs

  $<$<CONFIG:Debug>: -Ofast>
  $<$<CONFIG:Release>: -Ofast>
)

target_link_options(${PROJECT_NAME} PRIVATE
  -T${CMAKE_SOURCE_DIR}/STM32F746ZETX_FLASH.ld
  -mcpu=cortex-m7
  -mthumb
  -mfloat-abi=hard
  -mfpu=fpv5-sp-d16

  --specs=nano.specs
  --specs=nosys.specs

  -Wl,-Map=${EXECUTABLE}.map,--cref
  -Wl,--gc-sections
  -static
  -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
)

# Print executable size
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND arm-none-eabi-size ${EXECUTABLE}${CMAKE_EXECUTABLE_SUFFIX}
)

# Create hex file
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE}${CMAKE_EXECUTABLE_SUFFIX} ${EXECUTABLE}.hex
  COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE}${CMAKE_EXECUTABLE_SUFFIX} ${EXECUTABLE}.bin
)
