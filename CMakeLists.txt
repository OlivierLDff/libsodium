# 2014/2015 - Initial Work Cyberunner23/Isammoc/march44/novocodev
# 2019 - CMakeLists updated to libsodium 1.0.18.

# ┌──────────────────────────────────────────────────────────────────┐
# │                       CMAKE PROPERTIES                           │
# └──────────────────────────────────────────────────────────────────┘

CMAKE_MINIMUM_REQUIRED( VERSION 3.11 )

# ┌──────────────────────────────────────────────────────────────────┐
# │                       PROJECT SETTINGS                           │
# └──────────────────────────────────────────────────────────────────┘

# General
SET( SODIUM_PROJECT             "libsodium"       CACHE STRING "Sodium Project Name")
SET( SODIUM_TARGET              ${SODIUM_PROJECT} CACHE STRING "libsodium library name" )
SET( SODIUM_AESNI_TARGET        libaesni          CACHE STRING "libaesni library name" )
SET( SODIUM_SSE2_TARGET         libsse2           CACHE STRING "libsse2 library name" )
SET( SODIUM_SSSE3_TARGET        libssse3          CACHE STRING "libssse3 library name" )
SET( SODIUM_SSE41_TARGET        libsse41          CACHE STRING "libsse41 library name" )
SET( SODIUM_AVX2_TARGET         libavx2           CACHE STRING "libavx2 library name" )
SET( SODIUM_AVX512F_TARGET      libavx512f        CACHE STRING "libavx512f library name" )
SET( SODIUM_RDRAND_TARGET       librdrand         CACHE STRING "librdrand library name" )

SET(SODIUM_VERSION              "1.0.18" CACHE STRING "libsodium current version" FORCE )
# VERSION is only here to configure version.h.in properly without changing source code
SET(VERSION ${SODIUM_VERSION} )
SET(SODIUM_LIBRARY_VERSION_MAJOR 10)
SET(SODIUM_LIBRARY_VERSION_MINOR 3)
SET(DLL_VERSION 24)

SET(SODIUM_LIBRARY_VERSION "26:0:3")
#                            | | |
#                     +------+ | +---+
#                     |        |     |
#                  current:revision:age
#                     |        |     |
#                     |        |     +- increment if interfaces have been added
#                     |        |        set to zero if interfaces have been removed
#                     |        |        or changed
#                     |        +- increment if source code has changed
#                     |           set to zero if current is incremented
#                     +- increment if interfaces have been added, removed or changed

SET( SODIUM_BUILD_SHARED          OFF CACHE BOOL "Build as a shared library (ON) or a static library (OFF)" )
SET( SODIUM_FOLDER_PREFIX         ${SODIUM_PROJECT} CACHE STRING "Prefix folder for all libsodium generated targets in generated project (only decorative)" )

# General
SET(SODIUM_ENABLE_BLOCKING_RANDOM OFF CACHE BOOL "Enable this switch only if /dev/urandom is totally broken on the target platform.")
SET(SODIUM_ENABLE_MINIMAL_BUILD   OFF CACHE BOOL "Only compile the minimum set of functions required for the high-level API.")

SET(SODIUM_DISABLE_ASM            OFF CACHE BOOL "Disable AMD64 assembly implementations.")
SET(SODIUM_DISABLE_PIE            OFF CACHE BOOL "Do not produce position independent executables.")
SET(SODIUM_DISABLE_SSP            OFF CACHE BOOL "Do not compile with -fstack-protector.")

SET(SODIUM_USE_CONTROL_FLOW_GUARD OFF CACHE BOOL "Enable /guard:cf for msvc")
SET(SODIUM_USE_QSPECTRE           OFF CACHE BOOL "Enable /Qspectre options for msvc.")

# Tests
SET( SODIUM_ENABLE_TESTS          OFF CACHE BOOL "Create or not a target for test (compatible with CTests)" )
SET( SODIUM_TESTS_PREFIX          ${SODIUM_PROJECT} CACHE STRING "Prefix for all libsodium tests" )

# Install
SET( SODIUM_ENABLE_INSTALL        OFF CACHE BOOL "Create or not a target for install" )
SET( SODIUM_INSTALL_PREFIX        ${SODIUM_PROJECT} CACHE STRING "Prefix for all libsodium headers in the install folder" )

# Create the project
PROJECT(${SODIUM_PROJECT} VERSION ${SODIUM_VERSION} LANGUAGES C CXX ASM)
# We use folder, only for decoration
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
# CMake script folder
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# We configure the version.h file inside the source directory (ignore in .gitignore) for the build process to find the version.h
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/version.h)

MESSAGE("---------------- LIBSODIUM OPTIONS. ----------------")

#General
MESSAGE(STATUS "SODIUM_PROJECT                : " ${SODIUM_PROJECT})
MESSAGE(STATUS "SODIUM_TARGET                 : " ${SODIUM_TARGET})
MESSAGE(STATUS "SODIUM_VERSION                : " ${SODIUM_VERSION})
MESSAGE(STATUS "SODIUM_BUILD_SHARED           : " ${SODIUM_BUILD_SHARED})
MESSAGE(STATUS "SODIUM_FOLDER_PREFIX          : " ${SODIUM_FOLDER_PREFIX})

MESSAGE(STATUS "SODIUM_ENABLE_BLOCKING_RANDOM : " ${SODIUM_ENABLE_BLOCKING_RANDOM})
MESSAGE(STATUS "SODIUM_ENABLE_MINIMAL_BUILD   : " ${SODIUM_ENABLE_MINIMAL_BUILD})

MESSAGE(STATUS "SODIUM_DISABLE_ASM            : " ${SODIUM_DISABLE_ASM})
MESSAGE(STATUS "SODIUM_DISABLE_PIE            : " ${SODIUM_DISABLE_PIE})
MESSAGE(STATUS "SODIUM_DISABLE_SSP            : " ${SODIUM_DISABLE_SSP})

# MSVC
IF(MSVC)
MESSAGE(STATUS "SODIUM_USE_CONTROL_FLOW_GUARD : " ${SODIUM_USE_CONTROL_FLOW_GUARD})
MESSAGE(STATUS "SODIUM_USE_QSPECTRE           : " ${SODIUM_USE_QSPECTRE})
ENDIF(MSVC)

# Tests
MESSAGE(STATUS "SODIUM_ENABLE_TESTS           : " ${SODIUM_ENABLE_TESTS})
IF(SODIUM_ENABLE_TESTS)
MESSAGE(STATUS "SODIUM_TESTS_PREFIX           : " ${SODIUM_TESTS_PREFIX})
ENDIF(SODIUM_ENABLE_TESTS)

# Install
MESSAGE(STATUS "SODIUM_ENABLE_INSTALL         : " ${SODIUM_ENABLE_INSTALL})
IF(SODIUM_ENABLE_INSTALL)
MESSAGE(STATUS "SODIUM_INSTALL_PREFIX         : " ${SODIUM_INSTALL_PREFIX})
ENDIF(SODIUM_ENABLE_INSTALL)


MESSAGE("---------------- DONE WITH OPTIONS. -----------------")
MESSAGE("                                                     ")

# ┌──────────────────────────────────────────────────────────────────┐
# │                        SYSTEM CHECKS                             │
# └──────────────────────────────────────────────────────────────────┘

MESSAGE("---------------- PERFORMING SYSTEM CHECKS. ----------------")

# MSVC does not provide inline in C (only CXX)
IF(MSVC)
    ADD_DEFINITIONS("-Dinline=__inline")
ENDIF(MSVC)

#Endianess check
INCLUDE(TestBigEndian)
TEST_BIG_ENDIAN(BIG_ENDIAN)

IF(${BIG_ENDIAN})
    SET(IS_BIG_ENDIAN ON)
    ADD_DEFINIIONS("-DNATIVE_BIG_ENDIAN=1")
    MESSAGE(STATUS "System is in Big Endian.")
ELSE(${BIG_ENDIAN})
    SET(IS_BIG_ENDIAN OFF)
    ADD_DEFINITIONS("-DNATIVE_LITTLE_ENDIAN=1")
    MESSAGE(STATUS "System is in Little Endian.")
ENDIF(${BIG_ENDIAN})


IF(EMSCRIPTEN)
    SET(SODIUM_DISABLE_ASM ON)
    MESSAGE(STATUS "Compiling to javascript, disabling asm implementations.")
ELSE(EMSCRIPTEN)
    SET(libsodium_SOURCE ${libsodium_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/randombytes/sysrandom/randombytes_sysrandom.c
    )
ENDIF(EMSCRIPTEN)


IF(MSYS OR MINGW OR CYGWIN)
    SET(SODIUM_DISABLE_PIE ON)
ENDIF()

#TI mode check
IF(${IS_BIGENDIAN})
    TRY_COMPILE(HAVE_TI_MODE_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_TI_MODE.c COMPILE_DEFINITIONS -DNATIVE_BIG_ENDIAN=1)
ELSE(${IS_BIGENDIAN})
    TRY_COMPILE(HAVE_TI_MODE_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_TI_MODE.c COMPILE_DEFINITIONS -DNATIVE_LITTLE_ENDIAN=1)
ENDIF(${IS_BIGENDIAN})

IF(HAVE_TI_MODE_COMPILE)

    SET(libsodium_HEADERS ${libsodium_HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/ed25519/ref10/fe_51/base.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/ed25519/ref10/fe_51/base2.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/ed25519/ref10/fe_51/constants.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/ed25519/ref10/fe_51/fe.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/private/ed25519_ref10_fe_51.h
    )

    SET(libsodium_SOURCE ${libsodium_SOURCE}
    )

    ADD_DEFINITIONS("-DHAVE_TI_MODE=1")

    MESSAGE(STATUS "Gcc TI Mode is available.")

ELSE(HAVE_TI_MODE_COMPILE)

    SET(libsodium_HEADERS ${libsodium_HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/ed25519/ref10/fe_25_5/base.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/ed25519/ref10/fe_25_5/base2.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/ed25519/ref10/fe_25_5/constants.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/ed25519/ref10/fe_25_5/fe.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/private/ed25519_ref10_fe_25_5.h

    )

    SET(libsodium_SOURCE ${libsodium_SOURCE}
    )

    MESSAGE(STATUS "Gcc TI Mode is not available.")

ENDIF(HAVE_TI_MODE_COMPILE)


#Check if weak symbols are supported.
TRY_COMPILE(HAVE_WEAK_SYMBOLS_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_WEAK_SYMBOLS.c)
IF(HAVE_WEAK_SYMBOLS_COMPILE)
    ADD_DEFINITIONS("-DHAVE_WEAK_SYMBOLS=1")
    MESSAGE(STATUS "Weak Symbols are supported.")
ELSE(HAVE_WEAK_SYMBOLS_COMPILE)
    MESSAGE(STATUS "Weak Symbols are not supported.")
    SET(TEST ON)
ENDIF(HAVE_WEAK_SYMBOLS_COMPILE)


#Is __STDC_LIMIT_MACROS needed check.
TRY_COMPILE(IS_STDC_LIMIT_MACROS_NEEDED_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/IS_STDC_LIMIT_MACROS_NEEDED.c)
IF(IS_STDC_LIMIT_MACROS_NEEDED_COMPILE)
    #If this works then we dont need to define __STDC_LIMIT_MACROS and __STDC_CONSTANT_MACROS.
    MESSAGE(STATUS "__STDC_LIMIT_MACROS and __STDC_CONSTANT_MACROS not needed.")
ELSE(IS_STDC_LIMIT_MACROS_NEEDED_COMPILE)
    ADD_DEFINITIONS("-D__STDC_LIMIT_MACROS=1 -D__STDC_CONSTANT_MACROS=1")
    MESSAGE(STATUS "__STDC_LIMIT_MACROS and __STDC_CONSTANT_MACROS is needed and was added to the definitions.")
ENDIF(IS_STDC_LIMIT_MACROS_NEEDED_COMPILE)


#Is there a functionnal ASM compiler
SET(CMAKE_ASM_SOURCE_FILE_EXTENSIONS "s;S")
ENABLE_LANGUAGE(ASM)

IF(CMAKE_ASM_COMPILER_WORKS)
    SET(ASSEMBLER_AVAILABLE ON)
    MESSAGE(STATUS "An ASM compiler has been found and is functionnal.")
ELSE(CMAKE_ASM_COMPILER_WORKS)
    SET(ASSEMBLER_AVAILABLE OFF)
    MESSAGE(FATAL "An ASM compiler has not been found or is not functionnal.")
ENDIF(CMAKE_ASM_COMPILER_WORKS)

# Try to see wheter we can assemble AVX opcodes
TRY_COMPILE(HAVE_AVX_ASM_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_AVX_ASM.c)
IF(HAVE_AVX_ASM_COMPILE)
    SET(HAVE_AVX_ASM_COMPILE ON)
    ADD_DEFINITIONS("-DHAVE_AVX_ASM=1")
    MESSAGE(STATUS "Assemble AVX opcode supported.")

    SET(libsodium_HEADERS ${libsodium_HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/consts_namespace.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/curve25519_sandy2x.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/fe.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/fe51.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/fe51_namespace.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/ladder.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/ladder_base.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/ladder_base_namespace.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/ladder_namespace.h
    )

    SET(libsodium_SOURCE ${libsodium_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/curve25519_sandy2x.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/fe51_invert.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/fe_frombytes_sandy2x.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/sandy2x.S
    )
ELSE(HAVE_AVX_ASM_COMPILE)
    SET(HAVE_AVX_ASM_COMPILE OFF)
    MESSAGE(STATUS "Assemble AVX opcode not supported.")
ENDIF(HAVE_AVX_ASM_COMPILE)


#cpuid instruction check
TRY_COMPILE(IS_CPUID_INSTRUCTION_AVAILABLE_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_CPUID.c)
IF(IS_CPUID_INSTRUCTION_AVAILABLE_COMPILE)
    SET(IS_CPUID_INSTRUCTION_AVAILABLE ON)
    ADD_DEFINITIONS("-DHAVE_CPUID=1")
    MESSAGE(STATUS "Cpuid instruction is available.")
ELSE(IS_CPUID_INSTRUCTION_AVAILABLE_COMPILE)
    SET(IS_CPUID_INSTRUCTION_AVAILABLE OFF)
    MESSAGE(STATUS "Cpuid instruction is not available.")
ENDIF(IS_CPUID_INSTRUCTION_AVAILABLE_COMPILE)


#Have AMD64 ASM check
IF(SODIUM_DISABLE_ASM)

    MESSAGE(STATUS "AMD64 ASM implementations have been disabled.")

    SET(libsodium_HEADERS ${libsodium_HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/ref/salsa20_ref.h
    )

    SET(libsodium_SOURCE ${libsodium_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/ref/salsa20_ref.c
    )

ELSE(SODIUM_DISABLE_ASM)

    IF(ASSEMBLER_AVAILABLE)

        TRY_COMPILE(HAVE_AMD64_ASM_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_AMD64_ASM.c)
        IF(HAVE_AMD64_ASM_COMPILE)
            ADD_DEFINITIONS("-DHAVE_AMD64_ASM=1")

            SET(libsodium_HEADERS ${libsodium_HEADERS}
                ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6/salsa20_xmm6.h
            )

            SET(libsodium_SOURCE ${libsodium_SOURCE}
                ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6/salsa20_xmm6-asm.S
                ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6/salsa20_xmm6.c
            )

            MESSAGE(STATUS "AMD64 ASM is available.")

        ELSE(HAVE_AMD64_ASM_COMPILE)

            SET(libsodium_HEADERS ${libsodium_HEADERS}
                ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/ref/salsa20_ref.h
            )

            SET(libsodium_SOURCE ${libsodium_SOURCE}
                ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/ref/salsa20_ref.c
            )

            MESSAGE(STATUS "AMD64 ASM is not available.")

        ENDIF(HAVE_AMD64_ASM_COMPILE)
    ENDIF(ASSEMBLER_AVAILABLE)
ENDIF(SODIUM_DISABLE_ASM)

INCLUDE(CheckCCompilerFlag)

IF(NOT MSVC)

    #Check if -mmmx is available.
    CHECK_C_COMPILER_FLAG(-mmmx IS_mmmx_AVAILABLE)

    IF(IS_mmmx_AVAILABLE)
        TRY_COMPILE(HAVE_MMINTRIN_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_MMINTRIN.c COMPILE_DEFINITIONS "-mmmx")
        IF(HAVE_MMINTRIN_COMPILE)
            SET(HAVE_MMINTRIN ON)
            ADD_DEFINITIONS("-DHAVE_MMINTRIN_H=1")
            #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmmx")
            SET(CMAKE_C_FLAGS_MMMX "-mmmx")
            MESSAGE(STATUS "mmx is available.")
        ELSE(HAVE_MMINTRIN_COMPILE)
            SET(HAVE_MMINTRIN OFF)
            MESSAGE(STATUS "mmx is not available.")
        ENDIF(HAVE_MMINTRIN_COMPILE)
    ENDIF(IS_mmmx_AVAILABLE)

    #Check if -msse2 is available.
    CHECK_C_COMPILER_FLAG(-msse2 IS_msse2_AVAILABLE)

    IF(IS_msse2_AVAILABLE)
        TRY_COMPILE(HAVE_EMMINTRIN_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_EMMINTRIN.c COMPILE_DEFINITIONS "-msse2")
        IF(HAVE_EMMINTRIN_COMPILE)
            SET(HAVE_EMMINTRIN ON)
            ADD_DEFINITIONS("-DHAVE_EMMINTRIN_H=1")
            #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse2")
            SET(CMAKE_C_FLAGS_SSE2 "-msse2")
            MESSAGE(STATUS "sse2 is available.")
        ELSE(HAVE_EMMINTRIN_COMPILE)
            SET(HAVE_EMMINTRIN OFF)
            MESSAGE(STATUS "sse2 is not available.")
        ENDIF(HAVE_EMMINTRIN_COMPILE)
    ENDIF(IS_msse2_AVAILABLE)

    #Check if -msse3 is available.
    CHECK_C_COMPILER_FLAG(-msse3 IS_msse3_AVAILABLE)

    IF(IS_msse3_AVAILABLE)
        TRY_COMPILE(HAVE_PMMINTRIN_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_PMMINTRIN.c COMPILE_DEFINITIONS "-msse3")
        IF(HAVE_PMMINTRIN_COMPILE)
            SET(HAVE_PMMINTRIN ON)
            ADD_DEFINITIONS("-DHAVE_PMMINTRIN_H=1")
            #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse3")
            SET(CMAKE_C_FLAGS_SSE3 "-msse3")
            MESSAGE(STATUS "sse3 is available.")
        ELSE(HAVE_PMMINTRIN_COMPILE)
            SET(HAVE_PMMINTRIN OFF)
            MESSAGE(STATUS "sse3 is not available.")
        ENDIF(HAVE_PMMINTRIN_COMPILE)
    ENDIF(IS_msse3_AVAILABLE)

    #Check if -mssse3 is available.
    CHECK_C_COMPILER_FLAG(-mssse3 IS_mssse3_AVAILABLE)

    IF(IS_mssse3_AVAILABLE)
        TRY_COMPILE(HAVE_TMMINTRIN_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_TMMINTRIN.c COMPILE_DEFINITIONS "-mssse3")
        IF(HAVE_TMMINTRIN_COMPILE)
            SET(HAVE_TMMINTRIN ON)
            ADD_DEFINITIONS("-DHAVE_TMMINTRIN_H=1")
            #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mssse3")
            SET(CMAKE_C_FLAGS_SSSE3 "-mssse3")
            MESSAGE(STATUS "ssse3 is available.")
        ELSE(HAVE_TMMINTRIN_COMPILE)
            SET(HAVE_TMMINTRIN OFF)
            MESSAGE(STATUS "ssse3 is not available.")
        ENDIF(HAVE_TMMINTRIN_COMPILE)
    ENDIF(IS_mssse3_AVAILABLE)

    #Check if -msse4.1 is available.
    CHECK_C_COMPILER_FLAG(-msse4.1 IS_msse41_AVAILABLE)

    IF(IS_msse41_AVAILABLE)
        TRY_COMPILE(HAVE_SMMINTRIN_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_SMMINTRIN.c COMPILE_DEFINITIONS "-msse4.1")
        IF(HAVE_SMMINTRIN_COMPILE)
            SET(HAVE_SMMINTRIN ON)
            ADD_DEFINITIONS("-DHAVE_SMMINTRIN_H=1")
            #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse4.1")
            SET(CMAKE_C_FLAGS_SSE41 "-msse4.1")
            MESSAGE(STATUS "sse4.1 is available.")
        ELSE(HAVE_SMMINTRIN_COMPILE)
            SET(HAVE_SMMINTRIN OFF)
            MESSAGE(STATUS "sse4.1 is not available.")
        ENDIF(HAVE_SMMINTRIN_COMPILE)
    ENDIF(IS_msse41_AVAILABLE)

    #Check if -mavx is available.
    CHECK_C_COMPILER_FLAG(-mavx IS_mavx_AVAILABLE)

    IF(IS_mavx_AVAILABLE)
        TRY_COMPILE(HAVE_AVXINTRIN_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_AVXINTRIN.c COMPILE_DEFINITIONS "-mavx")
        IF(HAVE_AVXINTRIN_COMPILE)
            SET(HAVE_AVXINTRIN ON)
            ADD_DEFINITIONS("-DHAVE_AVXINTRIN_H=1")
            #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx")
            SET(CMAKE_C_FLAGS_AVX "-mavx")
            MESSAGE(STATUS "avx is available.")
        ELSE(HAVE_AVXINTRIN_COMPILE)
            SET(HAVE_AVXINTRIN OFF)
            MESSAGE(STATUS "avx is not available.")
        ENDIF(HAVE_AVXINTRIN_COMPILE)
    ENDIF(IS_mavx_AVAILABLE)

    #Check if -mavx2 is available.
    CHECK_C_COMPILER_FLAG(-mavx2 IS_mavx2_AVAILABLE)

    IF(IS_mavx2_AVAILABLE)
        TRY_COMPILE(HAVE_AVX2INTRIN_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_AVX2INTRIN.c COMPILE_DEFINITIONS "-mavx2")
        IF(HAVE_AVX2INTRIN_COMPILE)
            SET(HAVE_AVX2INTRIN ON)
            ADD_DEFINITIONS("-DHAVE_AVX2INTRIN_H=1")
            #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx2")
            SET(CMAKE_C_FLAGS_AVX2 "-mavx2")
            MESSAGE(STATUS "avx2 is available.")

            TRY_COMPILE(HAVE_AVX2INTRIN_MM256_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_AVX2INTRIN_MM256.c)
            IF(HAVE_AVX2INTRIN_MM256_COMPILE)
                MESSAGE(STATUS "_mm_broadcastsi128_si256 is correctly defined")
            ELSE(HAVE_AVX2INTRIN_MM256_COMPILE)
                ADD_DEFINITIONS("-D_mm256_broadcastsi128_si256=_mm_broadcastsi128_si256")
                MESSAGE(STATUS "Define to the local name of _mm256_broadcastsi128_si256 to _mm_broadcastsi128_si256")
            ENDIF(HAVE_AVX2INTRIN_MM256_COMPILE)

        ELSE(HAVE_AVX2INTRIN_COMPILE)
            SET(HAVE_AVX2INTRIN OFF)
            MESSAGE(STATUS "avx2 is not available.")
        ENDIF(HAVE_AVX2INTRIN_COMPILE)
    ENDIF(IS_mavx2_AVAILABLE)

    #Check if -mavx512f is available.
    CHECK_C_COMPILER_FLAG(-mavx512f IS_mavx512f_AVAILABLE)

    IF(IS_mavx512f_AVAILABLE)
        TRY_COMPILE(HAVE_AVX512FINTRIN_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_AVX512FINTRIN.c COMPILE_DEFINITIONS "-mavx512f")
        IF(HAVE_AVX512FINTRIN_COMPILE)
            SET(HAVE_AVX512FINTRIN ON)
            ADD_DEFINITIONS("-DHAVE_AVX512FINTRIN_H=1")
            #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx512f")
            SET(CMAKE_C_FLAGS_AVX512F "-mavx512f")
            MESSAGE(STATUS "avx512f is available.")
        ELSE(HAVE_AVX512FINTRIN_COMPILE)
            SET(HAVE_AVX512FINTRIN OFF)
            MESSAGE(STATUS "avx512f is not available.")
        ENDIF(HAVE_AVX512FINTRIN_COMPILE)
    ENDIF(IS_mavx512f_AVAILABLE)

    #Check if -maes & -mpclmul are available for AESNI instructions set and PCLMULQDQ.
    CHECK_C_COMPILER_FLAG(-maes IS_maes_AVAILABLE)
    CHECK_C_COMPILER_FLAG(-mpclmul IS_mpclmul_AVAILABLE)

    IF(IS_maes_AVAILABLE AND IS_mpclmul_AVAILABLE)
        TRY_COMPILE(HAVE_WMMINTRIN_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_WMMINTRIN.c COMPILE_DEFINITIONS "-maes -mpclmul")
        IF(HAVE_WMMINTRIN_COMPILE)
            SET(HAVE_WMMINTRIN ON)
            ADD_DEFINITIONS("-DHAVE_WMMINTRIN_H=1")
            #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes -mpclmul")
            SET(CMAKE_C_FLAGS_AESNI "-maes" "-mpclmul")
            MESSAGE(STATUS "aesni is available.")
        ELSE(HAVE_WMMINTRIN_COMPILE)
            SET(HAVE_WMMINTRIN OFF)
            MESSAGE(STATUS "aesni is not available.")
        ENDIF(HAVE_WMMINTRIN_COMPILE)
    ENDIF(IS_maes_AVAILABLE AND IS_mpclmul_AVAILABLE)

    #Check if -mrdrnd is available.
    CHECK_C_COMPILER_FLAG(-mrdrnd IS_mrdrnd_AVAILABLE)

    IF(IS_mrdrnd_AVAILABLE)
        TRY_COMPILE(HAVE_RDRAND_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_RDRAND.c COMPILE_DEFINITIONS "-mrdrnd")
        IF(HAVE_RDRAND_COMPILE)
            SET(HAVE_RDRAND ON)
            ADD_DEFINITIONS("-DHAVE_RDRAND=1")
            #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mrdrnd")
            SET(CMAKE_C_FLAGS_RDRND "-mrdrnd")
            MESSAGE(STATUS "rdrnd is available.")
        ELSE(HAVE_RDRAND_COMPILE)
            SET(HAVE_RDRAND OFF)
            MESSAGE(STATUS "rdrnd is not available.")
        ENDIF(HAVE_RDRAND_COMPILE)
    ENDIF(IS_mrdrnd_AVAILABLE)

    TRY_COMPILE(HAVE_XGETBV_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_XGETBV.c)
    IF(HAVE_XGETBV_COMPILE)
        MESSAGE(STATUS "_xgetbv() is available")
        ADD_DEFINITIONS("-DHAVE__XGETBV=1")
    ELSE(HAVE_XGETBV_COMPILE)
        MESSAGE(STATUS "_xgetbv() isn't available")
    ENDIF(HAVE_XGETBV_COMPILE)

    TRY_COMPILE(HAVE_INLINE_ASM_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_INLINE_ASM.c)
    IF(HAVE_INLINE_ASM_COMPILE)
        MESSAGE(STATUS "inline asm code can be used")
        ADD_DEFINITIONS("-DHAVE_INLINE_ASM=1")
    ELSE(HAVE_INLINE_ASM_COMPILE)
        MESSAGE(STATUS "inline asm code can't be used")
    ENDIF(HAVE_INLINE_ASM_COMPILE)

    IF(NOT SODIUM_DISABLE_ASM)

        SET(ASM_HIDE_SYMBOL "unsupported")

        TRY_COMPILE(HAVE_PRIVATE_EXTERN_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_PRIVATE_EXTERN.c)
        IF(HAVE_PRIVATE_EXTERN_COMPILE)
            MESSAGE(STATUS "The .private_extern asm directive is supported")
            SET(ASM_HIDE_SYMBOL ".private_extern")
        ELSE(HAVE_PRIVATE_EXTERN_COMPILE)

            TRY_COMPILE(HAVE_HIDDEN_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_HIDDEN.c)
            IF(HAVE_HIDDEN_COMPILE)
                MESSAGE(STATUS "The .hidden asm directive is supported")
                SET(ASM_HIDE_SYMBOL ".hidden")
            ELSE(HAVE_HIDDEN_COMPILE)
                MESSAGE(STATUS "Unable to reliably tag symbols as private")
            ENDIF(HAVE_HIDDEN_COMPILE)

        ENDIF(HAVE_PRIVATE_EXTERN_COMPILE)

        IF(NOT ASM_HIDE_SYMBOL STREQUAL "unsupported")
            MESSAGE(STATUS "Define ASM_HIDE_SYMBOL to ${ASM_HIDE_SYMBOL}")
            ADD_DEFINITIONS("-DASM_HIDE_SYMBOL=${ASM_HIDE_SYMBOL}")
        ENDIF(NOT ASM_HIDE_SYMBOL STREQUAL "unsupported")

    ENDIF(NOT SODIUM_DISABLE_ASM)

    TRY_COMPILE(CPU_UNALIGNED_ACCESS_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/CPU_UNALIGNED_ACCESS.c)
    IF(CPU_UNALIGNED_ACCESS_COMPILE)
        MESSAGE(STATUS "unaligned memory access is supported")
        ADD_DEFINITIONS("-DCPU_UNALIGNED_ACCESS=1")
    ELSE(CPU_UNALIGNED_ACCESS_COMPILE)
        MESSAGE(STATUS "unaligned memory access isn't supported")
    ENDIF(CPU_UNALIGNED_ACCESS_COMPILE)

    TRY_COMPILE(HAVE_ATOMIC_OPS_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_ATOMIC_OPS.c)
    IF(HAVE_ATOMIC_OPS_COMPILE)
        MESSAGE(STATUS "atomic operations are supported")
        ADD_DEFINITIONS("-DHAVE_ATOMIC_OPS=1")
    ELSE(HAVE_ATOMIC_OPS_COMPILE)
        MESSAGE(STATUS "atomic operations are not supported")
    ENDIF(HAVE_ATOMIC_OPS_COMPILE)

    TRY_COMPILE(HAVE_SYS_RANDOM_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_SYS_RANDOM.c)
    IF(HAVE_SYS_RANDOM_COMPILE)
        MESSAGE(STATUS "getrandom is supported")
        ADD_DEFINITIONS("-HAVE_GETRANDOM=1")
    ELSE(HAVE_SYS_RANDOM_COMPILE)
        MESSAGE(STATUS "getrandom isn't supported")
    ENDIF(HAVE_SYS_RANDOM_COMPILE)

    TRY_COMPILE(HAVE_GET_ENTROPY_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_GET_ENTROPY.c)
    IF(HAVE_GET_ENTROPY_COMPILE)
        MESSAGE(STATUS "getentropy is supported")
        ADD_DEFINITIONS("-DHAVE_GETENTROPY=1")
    ELSE(HAVE_GET_ENTROPY_COMPILE)
        MESSAGE(STATUS "getentropy isn't supported")
    ENDIF(HAVE_GET_ENTROPY_COMPILE)

ENDIF(NOT MSVC)

MESSAGE("---------------- DONE WITH SYSTEM CHECKS. -----------------")
MESSAGE("                                                           ")


# ┌──────────────────────────────────────────────────────────────────┐
# │                    COMPILER FLAGS CHECKS                         │
# └──────────────────────────────────────────────────────────────────┘

#Compiler flag check macro definition.
MACRO(CHECK_COMPILER_FLAG)

    SET(FLAG "-${ARGV0}")
    SET(IS_${ARGV0}_AVAILABLE)

    CHECK_C_COMPILER_FLAG(${FLAG} IS_${ARGV0}_AVAILABLE)

    IF(IS_${ARGV0}_AVAILABLE)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAG}")
        MESSAGE(STATUS "Checking if ${FLAG} is available... It is available.")
    ELSE(IS_${ARGV0}_AVAILABLE)
        MESSAGE(STATUS "Checking if ${FLAG} is available... It is not available.")
    ENDIF(IS_${ARGV0}_AVAILABLE)

ENDMACRO(CHECK_COMPILER_FLAG)

MESSAGE("------------- PERFORMING COMPILER FLAG CHECKS. ------------")

#Check if -D_FORTIFY_SOURCE=2 is available.
CHECK_COMPILER_FLAG(D_FORTIFY_SOURCE=2)

IF(MSVC)

    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 /Oy- /Ob1 /O2 /Gy /wd4146 /wd4244 /wd4197 /wd4996 /wd4710 /wd4820 /wd4711")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /Oy- /Ob1 /O2 /Gy /wd4146 /wd4244 /wd4197 /wd4996 /wd4710 /wd4820 /wd4711")

ELSE(MSVC)

    #Check if debug mode is active
    IF(CMAKE_BUILD_TYPE MATCHES Debug)
        MESSAGE("-- Debug build enabled. --")
        ADD_DEFINITIONS("-DDEBUG=1")
        CHECK_COMPILER_FLAG(O)
        CHECK_COMPILER_FLAG(g3)
    ELSE(CMAKE_BUILD_TYPE MATCHES Debug)
        MESSAGE("-- Release build enabled. --")
        CHECK_COMPILER_FLAG(O3)
    ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

    #Check if -std=c99 is available.
    CHECK_COMPILER_FLAG(std=c99)

    #Check if clang and if -Wno-unknown-warning-option is available.
    IF("${CMAKE_C_COMPILER_ID}" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        CHECK_COMPILER_FLAG(Wno-unknown-warning-option)
    ENDIF()

    IF(NOT (MSYS OR MINGW OR CYGWIN))
        #Check if -fPIC is available.
        CHECK_COMPILER_FLAG(fPIC)
    ELSE(NOT (MSYS OR MINGW OR CYGWIN))
        CHECK_COMPILER_FLAG(Wl,--dynamicbase)
        CHECK_COMPILER_FLAG(Wl,--nxcompat)
    ENDIF(NOT (MSYS OR MINGW OR CYGWIN))

    #Check if -fPIE is available.
    IF(NOT SODIUM_DISABLE_PIE)
        CHECK_COMPILER_FLAG(fPIE)
    ENDIF(NOT SODIUM_DISABLE_PIE)

    #Check if -Wall is available.
    CHECK_COMPILER_FLAG(Wall)

    #Check if -Wextra is available.
    CHECK_COMPILER_FLAG(Wextra)

    #Check if -fvisibility=hidden is available
    CHECK_COMPILER_FLAG(fvisibility=hidden)

    #Check if -fno-strict-aliasing is available.
    CHECK_COMPILER_FLAG(fno-strict-aliasing)

    #Check if -fno-strict-overflow is available.
    CHECK_COMPILER_FLAG(fno-strict-overflow)
    IF(NOT IS_fno-strict-overflow_AVAILABLE)
        #If -fno-strict-overflow is not available, try with -fwrapv.
        CHECK_COMPILER_FLAG(fwrapv)
    ENDIF()

    IF(NOT SODIUM_DISABLE_SSP)
        #Check if -fstack-protector is available.
        CHECK_COMPILER_FLAG(fstack-protector)
    ENDIF(NOT SODIUM_DISABLE_SSP)

    #Check if -Winit-self is available.
    CHECK_COMPILER_FLAG(Winit-self)

    #Check if -Wwrite-strings is available.
    CHECK_COMPILER_FLAG(Wwrite-strings)

    #Check if -Wdiv-by-zero is available.
    CHECK_COMPILER_FLAG(Wdiv-by-zero)

    CHECK_COMPILER_FLAG(Wduplicated-branches)
    CHECK_COMPILER_FLAG(Wduplicated-cond)

    #Check if -Wmaybe-uninitialized is available.
    CHECK_COMPILER_FLAG(Wmaybe-uninitialized)

    CHECK_COMPILER_FLAG(Wsometimes-uninitialized)

    #Check if -Wbad-function-cast is available.
    CHECK_COMPILER_FLAG(Wbad-function-cast)

    #Check if -Wcast-qual is available.
    CHECK_COMPILER_FLAG(Wcast-qual)

    #Check if -Wchar-subscripts is available.
    CHECK_COMPILER_FLAG(Wchar-subscripts)

    #Check if -Wcomment is available.
    CHECK_COMPILER_FLAG(Wcomment)

    #Check if -Wfloat-equal is available.
    CHECK_COMPILER_FLAG(Wfloat-equal)

    #Check if -Wformat=2 is available.
    CHECK_COMPILER_FLAG(Wformat=2)
    CHECK_COMPILER_FLAG(Wlogical-op)

    #Check if -Wimplicit is available.
    CHECK_COMPILER_FLAG(Wimplicit)

    #Check if -Wmissing-declarations is available.
    CHECK_COMPILER_FLAG(Wmissing-declarations)

    CHECK_COMPILER_FLAG(Wmisleading-indentation)

    #Check if -Wmissing-prototypes is available.
    CHECK_COMPILER_FLAG(Wmissing-prototypes)

    CHECK_COMPILER_FLAG(Wnested-externs)

    CHECK_COMPILER_FLAG(Wno-type-limits)

    CHECK_COMPILER_FLAG(Wno-unknown-pragmas)

    CHECK_COMPILER_FLAG(Wnull-dereference)

    CHECK_COMPILER_FLAG(Wold-style-declaration)

    CHECK_COMPILER_FLAG(Wrestrict)

    CHECK_COMPILER_FLAG(Wwrite-strings)

    #Check if -Wnormalized=id is available.
    CHECK_COMPILER_FLAG(Wnormalized=id)

    #Check if -Woverride-init is available.
    CHECK_COMPILER_FLAG(Woverride-init)

    #Check if -Wparentheses is available.
    CHECK_COMPILER_FLAG(Wparentheses)

    #Check if -Wpointer-arith is available.
    CHECK_COMPILER_FLAG(Wpointer-arith)

    #Check if -Wredundant-decls is available.
    CHECK_COMPILER_FLAG(Wredundant-decls)

    #Check if -Wstrict-prototypes is available.
    CHECK_COMPILER_FLAG(Wstrict-prototypes)

    #Check if -Wswitch-enum is available.
    CHECK_COMPILER_FLAG(Wswitch-enum)

    #Check if -Wvariable-dec is available.
    CHECK_COMPILER_FLAG(Wvariable-decl)

    #Check if -ftls-model=local-dynamic is available.
    CHECK_COMPILER_FLAG(-ftls-model=local-dynamic)

    # Macro says flag is available but ld says unknown flag
    IF(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

        #Check if -Wl,-z,relro is available.
        CHECK_COMPILER_FLAG(Wl,-z,relro)

        #Check if -Wl,-z,now is available.
        CHECK_COMPILER_FLAG(Wl,-z,now)

        #Check if -Wl,-z,noexecstack is available.
        CHECK_COMPILER_FLAG(Wl,-z,noexecstack)

    ENDIF(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

ENDIF(MSVC)

MESSAGE("------------- DONE WITH COMPILER FLAG CHECKS. -------------")
MESSAGE("                                                           ")

# ┌──────────────────────────────────────────────────────────────────┐
# │                      SOURCES / HEADERS                           │
# └──────────────────────────────────────────────────────────────────┘

SET(libsodium_HEADERS ${libsodium_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-load-sse2.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-load-sse41.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-load-avx2.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_onetimeauth/poly1305/onetimeauth_poly1305.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_onetimeauth/poly1305/donna/poly1305_donna.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_onetimeauth/poly1305/donna/poly1305_donna32.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_onetimeauth/poly1305/donna/poly1305_donna64.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/argon2-core.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/argon2-encoding.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/argon2.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/blake2b-long.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/blamka-round-ref.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/ref10/x25519_ref10.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/scalarmult_curve25519.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_shorthash/siphash24/ref/shorthash_siphash_ref.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_sign/ed25519/ref10/sign_ed25519_ref10.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/stream_chacha20.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/ref/chacha20_ref.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/stream_salsa20.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/private/chacha20_ietf_ext.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/private/common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/private/ed25519_ref10.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/private/implementations.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/private/mutex.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/private/sse2_64_32.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium.h
)

SET(libsodium_SOURCE ${libsodium_SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_aead/chacha20poly1305/sodium/aead_chacha20poly1305.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_aead/xchacha20poly1305/sodium/aead_xchacha20poly1305.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_auth/crypto_auth.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_auth/hmacsha256/auth_hmacsha256.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_auth/hmacsha512/auth_hmacsha512.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_auth/hmacsha512256/auth_hmacsha512256.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_box/crypto_box.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_box/crypto_box_easy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_box/crypto_box_seal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_box/curve25519xsalsa20poly1305/box_curve25519xsalsa20poly1305.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/ed25519/ref10/ed25519_ref10.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/hchacha20/core_hchacha20.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/hsalsa20/ref2/core_hsalsa20_ref2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/hsalsa20/core_hsalsa20.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/salsa/ref/core_salsa_ref.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/crypto_generichash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/generichash_blake2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-compress-ref.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-ref.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/generichash_blake2b.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_hash/crypto_hash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_hash/sha256/hash_sha256.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_hash/sha256/cp/hash_sha256_cp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_hash/sha512/hash_sha512.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_hash/sha512/cp/hash_sha512_cp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_kdf/blake2b/kdf_blake2b.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_kdf/crypto_kdf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_kx/crypto_kx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_onetimeauth/crypto_onetimeauth.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_onetimeauth/poly1305/onetimeauth_poly1305.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_onetimeauth/poly1305/donna/poly1305_donna.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/argon2-core.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/argon2-encoding.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/argon2-fill-block-ref.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/argon2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/blake2b-long.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/pwhash_argon2i.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/pwhash_argon2id.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/crypto_pwhash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/crypto_scalarmult.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/ref10/x25519_ref10.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/scalarmult_curve25519.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_secretbox/crypto_secretbox.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_secretbox/crypto_secretbox_easy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_secretbox/xsalsa20poly1305/secretbox_xsalsa20poly1305.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_secretstream/xchacha20poly1305/secretstream_xchacha20poly1305.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_shorthash/crypto_shorthash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_shorthash/siphash24/shorthash_siphash24.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_shorthash/siphash24/ref/shorthash_siphash24_ref.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_sign/crypto_sign.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_sign/ed25519/sign_ed25519.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_sign/ed25519/ref10/keypair.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_sign/ed25519/ref10/open.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_sign/ed25519/ref10/sign.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/stream_chacha20.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/ref/chacha20_ref.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/crypto_stream.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/stream_salsa20.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/xsalsa20/stream_xsalsa20.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_verify/sodium/verify.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/randombytes/randombytes.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/sodium/codecs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/sodium/core.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/sodium/runtime.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/sodium/utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/sodium/version.c
)

# ┌──────────────────────────────────────────────────────────────────┐
# │                    MINIMAL_BUILD_CHECK                           │
# └──────────────────────────────────────────────────────────────────┘

IF(NOT SODIUM_ENABLE_MINIMAL_BUILD)

    SET(libsodium_HEADERS ${libsodium_HEADERS}
    )

    SET(libsodium_SOURCE ${libsodium_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_box/curve25519xchacha20poly1305/box_curve25519xchacha20poly1305.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_box/curve25519xchacha20poly1305/box_seal_curve25519xchacha20poly1305.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/ed25519/core_ed25519.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_core/ed25519/core_ristretto255.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/scryptsalsa208sha256/crypto_scrypt-common.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/scryptsalsa208sha256/crypto_scrypt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/scryptsalsa208sha256/scrypt_platform.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/scryptsalsa208sha256/pbkdf2-sha256.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/scryptsalsa208sha256/pbkdf2-sha256.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/scryptsalsa208sha256/pwhash_scryptsalsa208sha256.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/scryptsalsa208sha256/nosse/pwhash_scryptsalsa208sha256_nosse.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/ed25519/ref10/scalarmult_ed25519_ref10.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/ristretto255/ref10/scalarmult_ristretto255_ref10.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_secretbox/xchacha20poly1305/secretbox_xchacha20poly1305.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_shorthash/siphash24/shorthash_siphashx24.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_shorthash/siphash24/ref/shorthash_siphashx24_ref.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_sign/ed25519/ref10/obsolete.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa2012/ref/stream_salsa2012_ref.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa2012/stream_salsa2012.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa208/ref/stream_salsa208_ref.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa208/stream_salsa208.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/xchacha20/stream_xchacha20.c
    )

ENDIF(NOT SODIUM_ENABLE_MINIMAL_BUILD)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/build")

IF(SODIUM_ENABLE_BLOCKING_RANDOM)
    ADD_DEFINITIONS("-DUSE_BLOCKING_RANDOM")
ENDIF(SODIUM_ENABLE_BLOCKING_RANDOM)

# ┌──────────────────────────────────────────────────────────────────┐
# │                           LIBRDRAND                              │
# └──────────────────────────────────────────────────────────────────┘

IF(NOT EMSCRIPTEN)
    SET(librdrand_HEADERS ${librdrand_HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/randombytes_sysrandom.h
    )
    SET(librdrand_SOURCE ${librdrand_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/randombytes/internal/randombytes_internal_random.c
    )
ENDIF(NOT EMSCRIPTEN)

# ┌──────────────────────────────────────────────────────────────────┐
# │                           LIBAESNI                               │
# └──────────────────────────────────────────────────────────────────┘

SET(libaesni_HEADERS ${libaesni_HEADERS}
)
SET(libaesni_SOURCE ${libaesni_SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_aead/aes256gcm/aesni/aead_aes256gcm_aesni.c
)
SET(LIBAESNI_TARGET libaesni)

# ┌──────────────────────────────────────────────────────────────────┐
# │                            LIBSSE2                               │
# └──────────────────────────────────────────────────────────────────┘

SET(libsse2_HEADERS ${libsse2_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_onetimeauth/poly1305/sse2/poly1305_sse2.h
)

SET(libsse2_SOURCE ${libsse2_SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_onetimeauth/poly1305/sse2/poly1305_sse2.c
)

IF(NOT SODIUM_ENABLE_MINIMAL_BUILD)
    SET(libsse2_SOURCE ${libsse2_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/scryptsalsa208sha256/sse/pwhash_scryptsalsa208sha256_sse.c
    )
ENDIF(NOT SODIUM_ENABLE_MINIMAL_BUILD)

IF(NOT HAVE_AMD64_ASM_COMPILE)
    SET(libsse2_HEADERS ${libsse2_HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6int/salsa20_xmm6int-sse2.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6int/u0.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6int/u1.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6int/u4.h
    )
    SET(libsse2_SOURCE ${libsse2_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6int/salsa20_xmm6int-sse2.c
    )
ENDIF(NOT HAVE_AMD64_ASM_COMPILE)

# ┌──────────────────────────────────────────────────────────────────┐
# │                            LIBSSE3                               │
# └──────────────────────────────────────────────────────────────────┘

SET(libssse3_HEADERS ${libssse3_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-compress-ssse3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/blamka-round-ssse3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/chacha20_dolbeau-ssse3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/u0.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/u1.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/u4.h
)

SET(libssse3_SOURCE ${libssse3_SOURCE}

    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-compress-ssse3.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/argon2-fill-block-ssse3.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/chacha20_dolbeau-ssse3.c
)

# ┌──────────────────────────────────────────────────────────────────┐
# │                            LIBSSE41                               │
# └──────────────────────────────────────────────────────────────────┘

SET(libsse41_HEADERS ${libsse41_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-compress-sse41.h
)

SET(libsse41_SOURCE ${libsse41_SOURCE}

    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-compress-sse41.c
)

# ┌──────────────────────────────────────────────────────────────────┐
# │                            LIBAVX2                               │
# └──────────────────────────────────────────────────────────────────┘

SET(libavx2_HEADERS ${libavx2_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-compress-avx2.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/blamka-round-avx2.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/chacha20_dolbeau-avx2.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/u8.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6int/salsa20_xmm6int-avx2.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6int/u0.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6int/u1.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6int/u4.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6int/u8.h
)

SET(libavx2_SOURCE ${libavx2_SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-compress-avx2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/argon2-fill-block-avx2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/chacha20_dolbeau-avx2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6int/salsa20_xmm6int-avx2.c
)

# ┌──────────────────────────────────────────────────────────────────┐
# │                            LIBAVX512F                            │
# └──────────────────────────────────────────────────────────────────┘

SET(libavx512f_HEADERS ${libavx512f_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/blamka-round-avx512f.h
)

SET(libavx512f_SOURCE ${libavx512f_SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/argon2-fill-block-avx512f.c
)

# ┌──────────────────────────────────────────────────────────────────┐
# │                            LIBSODIUM                             │
# └──────────────────────────────────────────────────────────────────┘

foreach(_source IN ITEMS ${libsodium_HEADERS})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()
foreach(_source IN ITEMS ${libsodium_SOURCE})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

if (MSVC AND (MSVC_VERSION GREATER 1900))
    if (${SODIUM_USE_CONTROL_FLOW_GUARD})
        MESSAGE(STATUS "Setting CONTROL FLOW GUARD")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /guard:cf")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /guard:cf")
        SET(CMAKE_EXE_LINKER_FLAGS  "/guard:cf /DYNAMICBASE")
    endif()
    if (${SODIUM_USE_QSPECTRE})
        MESSAGE(STATUS "Setting QSPECTRE")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Qspectre")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Qspectre")
    endif()
endif()

INCLUDE(CMakeParseArguments)

MACRO(SODIUM_ADD_LIBRARY)
    SET(OPTIONS )
    SET(ONE_VALUE_ARGS TARGET)
    SET(MULTI_VALUES_ARGS SOURCES DEPENDENCIES FLAGS)

    CMAKE_PARSE_ARGUMENTS(SODIUM_ADD_LIBRARY "${OPTIONS}" "${ONE_VALUE_ARGS}" "${MULTI_VALUES_ARGS}" ${ARGN} )

    MESSAGE(STATUS "Add Library : ${SODIUM_ADD_LIBRARY_TARGET}")

    IF(SODIUM_BUILD_SHARED)

        ADD_LIBRARY(${SODIUM_ADD_LIBRARY_TARGET} SHARED ${SODIUM_ADD_LIBRARY_SOURCES})
        TARGET_COMPILE_DEFINITIONS(${SODIUM_ADD_LIBRARY_TARGET} PRIVATE "-DSODIUM_DLL_EXPORT")

    ELSE(SODIUM_BUILD_SHARED)

        ADD_LIBRARY(${SODIUM_ADD_LIBRARY_TARGET} STATIC ${SODIUM_ADD_LIBRARY_SOURCES})
        TARGET_COMPILE_DEFINITIONS(${SODIUM_ADD_LIBRARY_TARGET} PUBLIC "-DSODIUM_STATIC")

    ENDIF(SODIUM_BUILD_SHARED)

    # Public interface only requires #include <sodium.h>
    TARGET_INCLUDE_DIRECTORIES(${SODIUM_ADD_LIBRARY_TARGET} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include> $<INSTALL_INTERFACE:${SODIUM_INSTALL_PREFIX}>)
    # Required by c core files
    TARGET_INCLUDE_DIRECTORIES(${SODIUM_ADD_LIBRARY_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium)

    # Put the target inside the correct folder for superbuild
    SET_TARGET_PROPERTIES(${SODIUM_ADD_LIBRARY_TARGET} PROPERTIES FOLDER ${SODIUM_FOLDER_PREFIX})

    # Avoid liblibsodium on darwin for example.
    SET_TARGET_PROPERTIES(${SODIUM_ADD_LIBRARY_TARGET} PROPERTIES PREFIX "")

    # The build system was properly configured
    TARGET_COMPILE_DEFINITIONS(${SODIUM_ADD_LIBRARY_TARGET} PRIVATE "-DCONFIGURED=1")

    IF(SODIUM_ADD_LIBRARY_FLAGS)
        MESSAGE(STATUS "${SODIUM_ADD_LIBRARY_TARGET} flags: ${SODIUM_ADD_LIBRARY_FLAGS}")
        TARGET_COMPILE_OPTIONS(${SODIUM_ADD_LIBRARY_TARGET} PRIVATE ${SODIUM_ADD_LIBRARY_FLAGS})
    ENDIF(SODIUM_ADD_LIBRARY_FLAGS)

    IF(SODIUM_ADD_LIBRARY_DEPENDENCIES)
        MESSAGE(STATUS "${SODIUM_ADD_LIBRARY_TARGET} dependencies: ${SODIUM_ADD_LIBRARY_DEPENDENCIES}")
        TARGET_LINK_LIBRARIES(${SODIUM_ADD_LIBRARY_TARGET} PUBLIC ${SODIUM_ADD_LIBRARY_DEPENDENCIES})
    ENDIF(SODIUM_ADD_LIBRARY_DEPENDENCIES)

ENDMACRO(SODIUM_ADD_LIBRARY)


MESSAGE("---------------- LIBSODIUM TARGETS. -----------------")

SODIUM_ADD_LIBRARY(TARGET ${SODIUM_AESNI_TARGET}
    SOURCES ${libaesni_HEADERS} ${libaesni_SOURCE}
    FLAGS ${CMAKE_C_FLAGS_SSE2} ${CMAKE_C_FLAGS_SSSE3} ${CMAKE_C_FLAGS_AESNI})

SODIUM_ADD_LIBRARY(TARGET ${SODIUM_SSE2_TARGET}
    SOURCES ${libsse2_HEADERS} ${libsse2_SOURCE}
    FLAGS ${CMAKE_C_FLAGS_SSE2})

SODIUM_ADD_LIBRARY(TARGET ${SODIUM_SSSE3_TARGET}
    SOURCES ${libssse3_HEADERS} ${libssse3_SOURCE}
    FLAGS ${CMAKE_C_FLAGS_SSE2} ${CMAKE_C_FLAGS_SSSE3})

SODIUM_ADD_LIBRARY(TARGET ${SODIUM_SSE41_TARGET}
    SOURCES ${libsse41_HEADERS} ${libsse41_SOURCE}
    FLAGS ${CMAKE_C_FLAGS_SSE2} ${CMAKE_C_FLAGS_SSSE3} ${CMAKE_C_FLAGS_SSE41})

SODIUM_ADD_LIBRARY(TARGET ${SODIUM_AVX2_TARGET}
    SOURCES ${libavx2_HEADERS} ${libavx2_SOURCE}
    FLAGS ${CMAKE_C_FLAGS_SSE2} ${CMAKE_C_FLAGS_SSSE3} ${CMAKE_C_FLAGS_SSE41} ${CMAKE_C_FLAGS_AVX} ${CMAKE_C_FLAGS_AVX2})

SODIUM_ADD_LIBRARY(TARGET ${SODIUM_AVX512F_TARGET}
    SOURCES ${libavx512f_HEADERS} ${libavx512f_SOURCE}
    FLAGS ${CMAKE_C_FLAGS_SSE2} ${CMAKE_C_FLAGS_SSSE3} ${CMAKE_C_FLAGS_SSE41} ${CMAKE_C_FLAGS_AVX} ${CMAKE_C_FLAGS_AVX2} ${CMAKE_C_FLAGS_AVX512F})

IF(NOT EMSCRIPTEN)
    SODIUM_ADD_LIBRARY(TARGET ${SODIUM_RDRAND_TARGET}
        SOURCES ${librdrand_HEADERS} ${librdrand_SOURCE}
        FLAGS ${CMAKE_C_FLAGS_RDRND})
    SET(_SODIUM_RDRAND_TARGET ${SODIUM_RDRAND_TARGET})
ENDIF(NOT EMSCRIPTEN)

SODIUM_ADD_LIBRARY(TARGET ${SODIUM_TARGET}
    SOURCES ${libsodium_HEADERS} ${libsodium_SOURCE}
    DEPENDENCIES ${SODIUM_AESNI_TARGET} ${SODIUM_SSE2_TARGET} ${SODIUM_SSSE3_TARGET} ${SODIUM_SSE41_TARGET} ${SODIUM_AVX2_TARGET} ${SODIUM_AVX512F_TARGET} ${_SODIUM_RDRAND_TARGET})

MESSAGE("---------------- DONE WITH TARGETS. -----------------")
MESSAGE("                                                     ")

# ┌──────────────────────────────────────────────────────────────────┐
# │                            TESTS                                 │
# └──────────────────────────────────────────────────────────────────┘

IF(SODIUM_ENABLE_TESTS)
    MESSAGE("---------------- LIBSODIUM TESTS. -------------------")

    INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CTestLists.txt)

    MESSAGE("---------------- DONE WITH TESTS. -------------------")
    MESSAGE("                                                     ")
ENDIF(SODIUM_ENABLE_TESTS)

# ┌──────────────────────────────────────────────────────────────────┐
# │                          INSTALL                                 │
# └──────────────────────────────────────────────────────────────────┘

IF(SODIUM_ENABLE_INSTALL)
    MESSAGE("---------------- LIBSODIUM EXAMPLES. ----------------")

    INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/CInstallLists.txt)

    MESSAGE("---------------- DONE WITH EXAMPLES. ----------------")
    MESSAGE("                                                     ")
ENDIF(SODIUM_ENABLE_INSTALL)
