cmake_minimum_required(VERSION 3.22)

# enable_language(C ASM)
# # Project name
# project(main)
# # The project version number.
# set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
# set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
# set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
# mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

list(APPEND MODULES_USED
    PowerManager
    LockerDriver
    )


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME 02-BasicProject)


if(CMAKE_CROSSCOMPILING STREQUAL "1")
    # Control specific options if crosscompiling

    message(STATUS "[INFO] Cross compiling")

    # Add macro cross compilation
    add_compile_definitions(CROSS_COMPILE)

    # Include toolchain file
    include("cmake/gcc-arm-none-eabi.cmake")

    # Enable compile command to ease indexing with e.g. clangd
    set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

    # Enable CMake support for ASM and C languages
    enable_language(C ASM)

    # Core project settings
    project(${CMAKE_PROJECT_NAME})
    message("Build type: " ${CMAKE_BUILD_TYPE})

    # Create an executable object type
    add_executable(${CMAKE_PROJECT_NAME})

    # Add STM32CubeMX generated sources
    add_subdirectory(cmake/stm32cubemx)
    add_subdirectory(Modules)

    # Link directories setup
    target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
        # Add user defined library search paths
    )

    # Add sources to executable
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        Src/MuxDriver.c
        Src/UtilDriver.c
        # Add user sources here
    )

    # Add include paths
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        # Add user defined include paths
    )

    # Add project symbols (macros)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        # Add user defined symbols
    )

    # Add linked libraries
    target_link_libraries(${CMAKE_PROJECT_NAME}
        PUBLIC
        stm32cubemx
        ${MODULES_USED}
        # Add user defined libraries
    )
    
    ######################################################################
    # @Target: doc
    # @Brief: Generate doxygen documentation
    ######################################################################
    # check if Doxygen is installed
    find_package(Doxygen REQUIRED dot)
    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        # exclude folders while making documentation
        # should be separated by spaces
        set(DOXYGEN_EXCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Tools/* ${CMAKE_CURRENT_SOURCE_DIR}/build/* ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/*")

        # set mainpage in doxygen
        set(DOXYGEN_MAIN_PAGE "README.md")

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

        # note the option ALL which allows to build the docs together with the application
        add_custom_target(Docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)

else()

    #------------------
    # Debug Flags
    #------------------
    set(CMAKE_C_FLAGS_DEBUG "-Og -g -gdwarf-3 -gstrict-dwarf " CACHE INTERNAL "C Compiler options for debug build type")
    set(CMAKE_CXX_FLAGS_DEBUG "-Og -g -gdwarf-3 -gstrict-dwarf " CACHE INTERNAL "C++ Compiler options for debug build type")
    set(CMAKE_ASM_FLAGS_DEBUG "-Og -g -gdwarf-3 -gstrict-dwarf " CACHE INTERNAL "ASM Compiler options for debug build type")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "" CACHE INTERNAL "Linker options for debug build type")

    #------------------
    # Release Flags
    #-----------------
    set(CMAKE_C_FLAGS_RELEASE "-Os -flto " CACHE INTERNAL "C Compiler options for release build type")
    set(CMAKE_CXX_FLAGS_RELEASE "-Os -flto " CACHE INTERNAL "C++ Compiler options for release build type")
    set(CMAKE_ASM_FLAGS_RELEASE "" CACHE INTERNAL "ASM Compiler options for release build type")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto " CACHE INTERNAL "Linker options for release build type")

    # set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
    #-------------------
    # General Flags
    #-------------------
    set(OBJECT_GEN_FLAGS " \
    -fno-builtin \
    -Wall \
    -ffunction-sections -fdata-sections \
    -fomit-frame-pointer \
    " CACHE INTERNAL "Common flags for C/CXX/ASM/Linker")

    #-------------------
    # CFLAGS
    #-------------------
    set(CMAKE_C_FLAGS " \
    " CACHE INTERNAL "C Compiler options")

    #-------------------
    # ASMFLAGS for cross
    #-------------------
    set(CMAKE_ASM_FLAGS " \
    -x assembler-with-cpp \
    " CACHE INTERNAL "ASM Compiler options")

    #-------------------
    # LFLAGS for cross
    #-------------------
    set(CMAKE_EXE_LINKER_FLAGS " \
    -Wl,-Map=${PROJECT_NAME}.map \
    -Wl,--print-memory-usage \
    -Wl,--gc-sections \
    " CACHE INTERNAL "Linker options")

    message(STATUS "[INFO] Compiling natively")

    # Enable compile command to ease indexing with e.g. clangd
    set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

    # Enable CMake support for ASM and C languages
    enable_language(C ASM)

    # Core project settings
    # project(${CMAKE_PROJECT_NAME})
    project(main)
    message("Build type: " ${CMAKE_BUILD_TYPE})

    #-------------------
    # General Flags for native
    #-------------------
    string(APPEND OBJECT_GEN_FLAGS " \
    --coverage \
    ")

    #-------------------
    # CFLAGS for native
    #-------------------
    string(APPEND CMAKE_C_FLAGS " \
    ${OBJECT_GEN_FLAGS} \
    ")

    #-------------------
    # ASMFLAGS for native
    #-------------------
    string(APPEND CMAKE_ASM_FLAGS " \
    ${OBJECT_GEN_FLAGS} \
    ")

    #-------------------
    # LFLAGS for native
    #-------------------
    string(APPEND CMAKE_EXE_LINKER_FLAGS " \
    ${OBJECT_GEN_FLAGS} \
    ")

    add_subdirectory(Modules)

    add_library(unity STATIC
        Tools/unity/unity.c
        )

    target_include_directories(unity PUBLIC
        Tools/unity/
        )

    enable_testing()
    include(CTest)
    add_subdirectory(Test)

    set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
    include(CodeCoverage)
    setup_target_for_coverage_lcov(
        NAME coverage
        EXCLUDE "/usr/include/x86_64-linux-gnu/*" "Tools/unity/*"
        EXECUTABLE ctest -V
        DEPENDENCIES LockerDriver PowerManager
        )


endif()

# Unset all cache
unset(SEMIHOSTING)
unset(CMAKE_TOOLCHAIN_FILE)
unset(CMAKE_BUILD_TYPE)










