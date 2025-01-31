# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(oneshot C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(oneshot oneshot.c)

pico_set_program_name(oneshot "oneshot")
pico_set_program_version(oneshot "0.1")

# Habilita saída USB para depuração via `printf()`
pico_enable_stdio_uart(oneshot 0)  # 0 = Desativado, 1 = Ativado
pico_enable_stdio_usb(oneshot 1)   # Ativar USB para debug via `printf()`

# Adiciona bibliotecas padrão e `hardware_timer`
target_link_libraries(oneshot
    pico_stdlib
    hardware_timer  # Necessário para `add_alarm_in_ms()`
    hardware_gpio   # Necessário para controle dos LEDs e botões
)

# Adiciona diretórios de inclusão
target_include_directories(oneshot PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Gera os arquivos adicionais (.uf2, .bin, .hex)
pico_add_extra_outputs(oneshot)
