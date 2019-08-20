# 2014/2015 - Initial Work Cyberunner23/Isammoc/march44/novocodev
# 2019 - CMakeLists updated to libsodium 1.0.18.

CMAKE_MINIMUM_REQUIRED(VERSION 3.5.0)
SET( SODIUM_TARGET "libsodium" CACHE STRING "Target Name" )
PROJECT(${SODIUM_TARGET} VERSION 1.0.18 LANGUAGES C CXX ASM)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

INCLUDE(CheckCCompilerFlag)

#----------------------------------------------------------
######################### OPTIONS #########################
#----------------------------------------------------------

MESSAGE("---------------- LIBSODIUM OPTIONS. ----------------")

OPTION(SODIUM_BUILD_SHARED           "Build the library dynamically (ON/TRUE) or statically (OFF/FALSE).")
OPTION(SODIUM_ENABLE_BLOCKING_RANDOM "Enable this switch only if /dev/urandom is totally broken on the target platform.")
OPTION(SODIUM_ENABLE_MINIMAL_BUILD   "Only compile the minimum set of functions required for the high-level API.")
OPTION(SODIUM_ENABLE_TESTS           "Enable testing.")
OPTION(SODIUM_DISABLE_ASM            "Disable AMD64 assembly implementations.")
OPTION(SODIUM_DISABLE_PIE            "Do not produce position independent executables.")
OPTION(SODIUM_DISABLE_SSP            "Do not compile with -fstack-protector.")
OPTION(SODIUM_USE_CONTROL_FLOW_GUARD "Enable /guard:cf for msvc")
OPTION(SODIUM_USE_QSPECTRE           "Enable /Qspectre options for msvc.")

MESSAGE(STATUS "SODIUM_BUILD_SHARED           : " ${SODIUM_BUILD_SHARED})
MESSAGE(STATUS "SODIUM_ENABLE_BLOCKING_RANDOM : " ${SODIUM_ENABLE_BLOCKING_RANDOM})
MESSAGE(STATUS "SODIUM_ENABLE_MINIMAL_BUILD   : " ${SODIUM_ENABLE_MINIMAL_BUILD})
MESSAGE(STATUS "SODIUM_ENABLE_TESTS           : " ${SODIUM_ENABLE_TESTS})
MESSAGE(STATUS "SODIUM_DISABLE_ASM            : " ${SODIUM_DISABLE_ASM})
MESSAGE(STATUS "SODIUM_DISABLE_PIE            : " ${SODIUM_DISABLE_PIE})
MESSAGE(STATUS "SODIUM_DISABLE_SSP            : " ${SODIUM_DISABLE_SSP})
IF(MSVC)
    MESSAGE(STATUS "SODIUM_USE_CONTROL_FLOW_GUARD : " ${SODIUM_USE_CONTROL_FLOW_GUARD})
    MESSAGE(STATUS "SODIUM_USE_QSPECTRE           : " ${SODIUM_USE_QSPECTRE})
ENDIF(MSVC)

#----------------------------------------------------------
######################### VERSION #########################
#----------------------------------------------------------

SET(SODIUM_VERSION "1.0.18" CACHE STRING "libsodium current version" )
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

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/version.h)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/libsodium/include/sodium/version.h)


MESSAGE("---------------- DONE WITH OPTIONS. -----------------")
MESSAGE("                                                     ")

#----------------------------------------------------------
###################### SYSTEM CHECKS ######################
#----------------------------------------------------------

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
    MESSAGE("System is in Big Endian.")
ELSE(${BIG_ENDIAN})
    SET(IS_BIG_ENDIAN OFF)
    ADD_DEFINITIONS("-DNATIVE_LITTLE_ENDIAN=1")
    MESSAGE("System is in Little Endian.")
ENDIF(${BIG_ENDIAN})


IF(EMSCRIPTEN)
    SET(SODIUM_DISABLE_ASM ON)
    MESSAGE("Compiling to javascript, disabling asm implementations.")
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

    ADD_DEFINITIONS(-DHAVE_TI_MODE)

    MESSAGE("Gcc TI Mode is available.")

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

    MESSAGE("Gcc TI Mode is not available.")

ENDIF(HAVE_TI_MODE_COMPILE)


#Check if weak symbols are supported.
TRY_COMPILE(HAVE_WEAK_SYMBOLS_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_WEAK_SYMBOLS.c)
IF(HAVE_WEAK_SYMBOLS_COMPILE)
    ADD_DEFINITIONS("-DHAVE_WEAK_SYMBOLS")
    MESSAGE("Weak Symbols are supported.")
ELSE(HAVE_WEAK_SYMBOLS_COMPILE)
    MESSAGE("Weak Symbols are not supported.")
    SET(TEST ON)
ENDIF(HAVE_WEAK_SYMBOLS_COMPILE)


#Is __STDC_LIMIT_MACROS needed check.
TRY_COMPILE(IS_STDC_LIMIT_MACROS_NEEDED_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/IS_STDC_LIMIT_MACROS_NEEDED.c)
IF(IS_STDC_LIMIT_MACROS_NEEDED_COMPILE)
    #If this works then we dont need to define __STDC_LIMIT_MACROS and __STDC_CONSTANT_MACROS.
    MESSAGE("__STDC_LIMIT_MACROS and __STDC_CONSTANT_MACROS not needed.")
ELSE(IS_STDC_LIMIT_MACROS_NEEDED_COMPILE)
    ADD_DEFINITIONS("-D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS")
    MESSAGE("__STDC_LIMIT_MACROS and __STDC_CONSTANT_MACROS is needed and was added to the definitions.")
ENDIF(IS_STDC_LIMIT_MACROS_NEEDED_COMPILE)


#Is there a functionnal ASM compiler
SET(CMAKE_ASM_SOURCE_FILE_EXTENSIONS "s;S")
ENABLE_LANGUAGE(ASM)

IF(CMAKE_ASM_COMPILER_WORKS)
    SET(ASSEMBLER_AVAILABLE ON)
    MESSAGE("An ASM compiler has been found and is functionnal.")
ELSE(CMAKE_ASM_COMPILER_WORKS)
    SET(ASSEMBLER_AVAILABLE OFF)
    MESSAGE(FATAL "An ASM compiler has not been found or is not functionnal.")
ENDIF(CMAKE_ASM_COMPILER_WORKS)

# Try to see wheter we can assemble AVX opcodes
TRY_COMPILE(HAVE_AVX_ASM_V_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_AVX_ASM_V.c)
IF(HAVE_AVX_ASM_V_COMPILE)
    SET(HAVE_AVX_ASM_V_COMPILE ON)
    ADD_DEFINITIONS(-DHAVE_AVX_ASM=1)
    MESSAGE("Assemble AVX opcode supported.")

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
ELSE(HAVE_AVX_ASM_V_COMPILE)
    SET(HAVE_AVX_ASM_V_COMPILE OFF)
    MESSAGE("Assemble AVX opcode not supported.")
ENDIF(HAVE_AVX_ASM_V_COMPILE)


#cpuid instruction check
TRY_COMPILE(IS_CPUID_INSTRUCTION_AVAILABLE_COMPILE ${CMAKE_CURRENT_BINARY_DIR}/build ${CMAKE_CURRENT_SOURCE_DIR}/test/HAVE_CPUID.c)
IF(IS_CPUID_INSTRUCTION_AVAILABLE_COMPILE)
    SET(IS_CPUID_INSTRUCTION_AVAILABLE ON)
    ADD_DEFINITIONS("-DHAVE_CPUID")
    MESSAGE("Cpuid instruction is available.")
ELSE(IS_CPUID_INSTRUCTION_AVAILABLE_COMPILE)
    SET(IS_CPUID_INSTRUCTION_AVAILABLE OFF)
    MESSAGE("Cpuid instruction is not available.")
ENDIF(IS_CPUID_INSTRUCTION_AVAILABLE_COMPILE)


#Have AMD64 ASM check
IF(SODIUM_DISABLE_ASM)

    MESSAGE("AMD64 ASM implementations have been disabled.")

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
            ADD_DEFINITIONS(-DHAVE_AMD64_ASM=1)

            SET(libsodium_HEADERS ${libsodium_HEADERS}
                ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6/salsa20_xmm6.h
                ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6/salsa20_xmm6-asm_namespace.h
            )

            # Not sure about these
            #SET(libsodium_HEADERS ${libsodium_HEADERS}
            #    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/consts.S
            #    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/fe51_mul.S
            #    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/fe51_nsquare.S
            #    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/fe51_pack.S
            #    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/ladder.S
            #    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_scalarmult/curve25519/sandy2x/ladder_base.S
            #)

            SET(libsodium_SOURCE ${libsodium_SOURCE}
                ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6/salsa20_xmm6-asm.S
                ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/xmm6/salsa20_xmm6.c
            )

            MESSAGE("AMD64 ASM is available.")

        ELSE(HAVE_AMD64_ASM_COMPILE)

            SET(libsodium_HEADERS ${libsodium_HEADERS}
                ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/ref/salsa20_ref.h
            )

            SET(libsodium_SOURCE ${libsodium_SOURCE}
                ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/salsa20/ref/salsa20_ref.c
            )

            MESSAGE("AMD64 ASM is not available.")

        ENDIF(HAVE_AMD64_ASM_COMPILE)
    ENDIF(ASSEMBLER_AVAILABLE)
ENDIF(SODIUM_DISABLE_ASM)


MESSAGE("---------------- DONE WITH SYSTEM CHECKS. -----------------")
MESSAGE("                                                           ")


#----------------------------------------------------------
################### COMPILER FLAG CHECKS ##################
#----------------------------------------------------------

#Compiler flag check macro definition.
MACRO(CHECK_COMPILER_FLAG)

    SET(FLAG "-${ARGV0}")
    SET(IS_${ARGV0}_AVAILABLE)

    CHECK_C_COMPILER_FLAG(${FLAG} IS_${ARGV0}_AVAILABLE)

    IF(IS_${ARGV0}_AVAILABLE)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAG}")
        MESSAGE("Checking if ${FLAG} is available... It is available.")
    ELSE(IS_${ARGV0}_AVAILABLE)
        MESSAGE("Checking if ${FLAG} is available... It is not available.")
    ENDIF(IS_${ARGV0}_AVAILABLE)

ENDMACRO(CHECK_COMPILER_FLAG)


MESSAGE("------------- PERFORMING COMPILER FLAG CHECKS. ------------")


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

#Check if -D_FORTIFY_SOURCE=2 is available.
CHECK_COMPILER_FLAG(D_FORTIFY_SOURCE=2)

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

#Check if -Wsometimes-uninitialized is available.
CHECK_COMPILER_FLAG(Wsometimes-uninitialized)

#Check if -Wbad-function-cast is available.
CHECK_COMPILER_FLAG(Wbad-function-cast)

#Check if -Wcast-align is available.
CHECK_COMPILER_FLAG(Wcast-align)

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

#Check if -Wimplicit is available.
CHECK_COMPILER_FLAG(Wimplicit)

#Check if -Wmissing-declarations is available.
CHECK_COMPILER_FLAG(Wmissing-declarations)

#Check if -Wmissing-prototypes is available.
CHECK_COMPILER_FLAG(Wmissing-prototypes)

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

IF(${CMAKE_SYSTEM_NAME} NOT STREQUAL "Darwin")

    #Check if -Wl,-z,relro is available.
    CHECK_COMPILER_FLAG(Wl,-z,relro)

    #Check if -Wl,-z,now is available.
    CHECK_COMPILER_FLAG(Wl,-z,now)

    #Check if -Wl,-z,noexecstack is available.
    CHECK_COMPILER_FLAG(Wl,-z,noexecstack)

ENDIF(${CMAKE_SYSTEM_NAME} NOT STREQUAL "Darwin")

#Check if -Wl,--verbose is available and enable it.
#CHECK_COMPILER_FLAG(Wl,--verbose)


MESSAGE("------------- DONE WITH COMPILER FLAG CHECKS. -------------")
MESSAGE("                                                           ")


#----------------------------------------------------------
##################### SOURCE / HEADERS ####################
#----------------------------------------------------------

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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/private/quirks.h
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

#----------------------------------------------------------
################### MINIMAL BUILD CHECK ###################
#----------------------------------------------------------

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

IF(MSVC)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 /Oy- /Ob1 /O2 /Gy /wd4146 /wd4244 /wd4197 /wd4996 /wd4710 /wd4820 /wd4711")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /Oy- /Ob1 /O2 /Gy /wd4146 /wd4244 /wd4197 /wd4996 /wd4710 /wd4820 /wd4711")
ENDIF()

#----------------------------------------------------------
######################### LIBRDRAND #######################
#----------------------------------------------------------

IF(NOT EMSCRIPTEN)

    SET(librdrand_HEADERS ${librdrand_HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium/randombytes_sysrandom.h
    )
    SET(librdrand_SOURCE ${librdrand_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/randombytes/internal/randombytes_internal_random.c
    )
ENDIF(NOT EMSCRIPTEN)

#----------------------------------------------------------
######################### LIBAESNI ########################
#----------------------------------------------------------

    SET(libaesni_HEADERS ${libaesni_HEADERS}
    )
    SET(libaesni_SOURCE ${libaesni_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_aead/aes256gcm/aesni/aead_aes256gcm_aesni.c
    )
SET(LIBAESNI_TARGET libaesni)

#----------------------------------------------------------
######################### LIBSSE2 #########################
#----------------------------------------------------------

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

#----------------------------------------------------------
######################### LIBSSE3 #########################
#----------------------------------------------------------

SET(libsse3_HEADERS ${libsse3_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-compress-ssse3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/blamka-round-ssse3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/chacha20_dolbeau-ssse3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/u0.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/u1.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/u4.h
)

SET(libsse3_SOURCE ${libsse3_SOURCE}

    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-compress-ssse3.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/argon2-fill-block-ssse3.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_stream/chacha20/dolbeau/chacha20_dolbeau-ssse3.c
)

#----------------------------------------------------------
######################### LIBSSE41 ########################
#----------------------------------------------------------

SET(libsse41_HEADERS ${libsse41_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-compress-sse41.h
)

SET(libsse41_SOURCE ${libsse41_SOURCE}

    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_generichash/blake2b/ref/blake2b-compress-sse41.c
)

#----------------------------------------------------------
######################### LIBAVX2 #########################
#----------------------------------------------------------

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

#----------------------------------------------------------
######################### LIBAVC512F ######################
#----------------------------------------------------------

SET(libavx512f_HEADERS ${libavx512f_HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/blamka-round-avx512f.h
)

SET(libavx512f_SOURCE ${libavx512f_SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/crypto_pwhash/argon2/argon2-fill-block-avx512f.c
)

#----------------------------------------------------------
######################### LIBSODIUM #######################
#----------------------------------------------------------

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

IF(SODIUM_BUILD_SHARED)
    MESSAGE(STATUS "Build shared libsodium")
    IF( MSVC )
    INCLUDE (GenerateExportHeader)
    ENDIF( MSVC )

    ADD_LIBRARY(${SODIUM_TARGET} SHARED
        ${libsodium_HEADERS}
        ${libsodium_SOURCE}
        ${librdrand_HEADERS}
        ${librdrand_SOURCE}
        ${libaesni_HEADERS}
        ${libaesni_SOURCE}
        ${libsse2_HEADERS}
        ${libsse2_SOURCE}
        ${libsse3_HEADERS}
        ${libsse3_SOURCE}
        ${libsse41_HEADERS}
        ${libsse41_SOURCE}
        ${libavx2_HEADERS}
        ${libavx2_SOURCE}
        ${libavx512f_HEADERS}
        ${libavx512f_SOURCE}
        )

    IF( MSVC )
    GENERATE_EXPORT_HEADER( ${SODIUM_TARGET}
        BASE_NAME ${SODIUM_TARGET}
        EXPORT_MACRO_NAME ${SODIUM_TARGET}_EXPORT
        EXPORT_FILE_NAME ${SODIUM_TARGET}_Export.h
        STATIC_DEFINE ${SODIUM_TARGET}_BUILT_AS_STATIC
    )
    ENDIF( MSVC )
    TARGET_COMPILE_DEFINITIONS(${SODIUM_TARGET} PRIVATE "-DSODIUM_DLL_EXPORT")
ELSE(SODIUM_BUILD_SHARED)
    MESSAGE(STATUS "Build static libsodium")
    ADD_DEFINITIONS("-DSODIUM_STATIC")
    ADD_LIBRARY(${SODIUM_TARGET} STATIC
        ${libsodium_HEADERS}
        ${libsodium_SOURCE}
        ${librdrand_HEADERS}
        ${librdrand_SOURCE}
        ${libaesni_HEADERS}
        ${libaesni_SOURCE}
        ${libsse2_HEADERS}
        ${libsse2_SOURCE}
        ${libsse3_HEADERS}
        ${libsse3_SOURCE}
        ${libsse41_HEADERS}
        ${libsse41_SOURCE}
        ${libavx2_HEADERS}
        ${libavx2_SOURCE}
        ${libavx512f_HEADERS}
        ${libavx512f_SOURCE}
        )
ENDIF(SODIUM_BUILD_SHARED)

SET_TARGET_PROPERTIES(${SODIUM_TARGET} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
    PROJECT_LABEL "${SODIUM_TARGET}"
)

TARGET_INCLUDE_DIRECTORIES(${SODIUM_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
TARGET_INCLUDE_DIRECTORIES(${SODIUM_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium)
TARGET_INCLUDE_DIRECTORIES(${SODIUM_TARGET} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include> $<INSTALL_INTERFACE:libsodium>)
TARGET_INCLUDE_DIRECTORIES(${SODIUM_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/sodium)
#For version.h.in to version.h
TARGET_INCLUDE_DIRECTORIES(${SODIUM_TARGET} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src/libsodium/include/sodium)

# Avoid liblibsodium on darwin for example.
SET_TARGET_PROPERTIES(${SODIUM_TARGET} PROPERTIES PREFIX "")

#----------------------------------------------------------
########################## TESTS ##########################
#----------------------------------------------------------

IF(${SODIUM_ENABLE_TESTS})

    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test/default)
    ENABLE_TESTING()

    ADD_TEST(NAME aead_aes256gcm_test          COMMAND aead_aes256gcm          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME aead_aes256gcm2_test         COMMAND aead_aes256gcm2         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME aead_chacha20poly1305_test   COMMAND aead_chacha20poly1305   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME aead_chacha20poly13052_test  COMMAND aead_chacha20poly13052  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME auth_test                    COMMAND auth                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME auth2_test                   COMMAND auth2                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME auth3_test                   COMMAND auth3                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME auth5_test                   COMMAND auth5                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME auth6_test                   COMMAND auth6                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME auth7_test                   COMMAND auth7                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME box_test                     COMMAND box                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME box2_test                    COMMAND box2                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME box7_test                    COMMAND box7                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME box8_test                    COMMAND box8                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME box_easy_test                COMMAND box_easy                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME box_easy2_test               COMMAND box_easy2               WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME box_seal_test                COMMAND box_seal                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME box_seed_test                COMMAND box_seed                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME chacha20_test                COMMAND chacha20                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME codecs_test                  COMMAND codecs                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME core1_test                   COMMAND core1                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME core2_test                   COMMAND core2                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME core3_test                   COMMAND core3                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME core4_test                   COMMAND core4                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME core5_test                   COMMAND core5                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME core6_test                   COMMAND core6                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME core_ed25519_test            COMMAND core_ed25519            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME core_ristretto255_test       COMMAND core_ristretto255       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME ed25519_convert_test         COMMAND ed25519_convert         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME generichash_test             COMMAND generichash             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME generichash2_test            COMMAND generichash2            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME generichash3_test            COMMAND generichash3            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME hash_test                    COMMAND hash                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME hash3_test                   COMMAND hash3                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME kdf_test                     COMMAND kdf                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME keygen_test                  COMMAND keygen                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME metamorphic_test             COMMAND metamorphic             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME misuse_test                  COMMAND misuse                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME onetimeauth_test             COMMAND onetimeauth             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME onetimeauth2_test            COMMAND onetimeauth2            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME onetimeauth7_test            COMMAND onetimeauth7            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME pwhash_argon2i_test          COMMAND pwhash_argon2i          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME pwhash_argon2id_test         COMMAND pwhash_argon2id         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME pwhash_scrypt_test           COMMAND pwhash_scrypt           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME pwhash_scrypt_ll_test        COMMAND pwhash_scrypt_ll        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME randombytes_test             COMMAND randombytes             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME scalarmult_test              COMMAND scalarmult              WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME scalarmult2_test             COMMAND scalarmult2             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME scalarmult5_test             COMMAND scalarmult5             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME scalarmult6_test             COMMAND scalarmult6             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME scalarmult7_test             COMMAND scalarmult7             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME scalarmult8_test             COMMAND scalarmult8             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME scalarmult_ed25519_test      COMMAND scalarmult_ed25519      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME scalarmult_ristretto255_test COMMAND scalarmult_ristretto255 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME secretbox_test               COMMAND secretbox               WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME secretbox2_test              COMMAND secretbox2              WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME secretbox7_test              COMMAND secretbox7              WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME secretbox8_test              COMMAND secretbox8              WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME secretbox_easy_test          COMMAND secretbox_easy          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME secretbox_easy2_test         COMMAND secretbox_easy2         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME secretstream_test            COMMAND secretstream            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME shorthash_test               COMMAND shorthash               WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME sign_test                    COMMAND sign                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME siphashx24_test              COMMAND siphashx24              WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME sodium_core_test             COMMAND sodium_core             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME sodium_utils_test            COMMAND sodium_utils            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME sodium_utils2_test           COMMAND sodium_utils2           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME sodium_utils3_test           COMMAND sodium_utils3           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME sodium_version_test          COMMAND sodium_version          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME stream_test                  COMMAND stream                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME stream2_test                 COMMAND stream2                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME stream3_test                 COMMAND stream3                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME stream4_test                 COMMAND stream4                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME verify1_test                 COMMAND verify1                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)
    ADD_TEST(NAME xchacha20_test               COMMAND xchacha20               WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/default/)


    SET_TESTS_PROPERTIES(aead_aes256gcm_test          PROPERTIES DEPENDS aead_aes256gcm)
    SET_TESTS_PROPERTIES(aead_aes256gcm2_test         PROPERTIES DEPENDS aead_aes256gcm2)
    SET_TESTS_PROPERTIES(aead_chacha20poly1305_test   PROPERTIES DEPENDS aead_chacha20poly1305)
    SET_TESTS_PROPERTIES(aead_chacha20poly13052_test  PROPERTIES DEPENDS aead_chacha20poly13052)
    SET_TESTS_PROPERTIES(auth_test                    PROPERTIES DEPENDS auth)
    SET_TESTS_PROPERTIES(auth2_test                   PROPERTIES DEPENDS auth2)
    SET_TESTS_PROPERTIES(auth3_test                   PROPERTIES DEPENDS auth3)
    SET_TESTS_PROPERTIES(auth5_test                   PROPERTIES DEPENDS auth5)
    SET_TESTS_PROPERTIES(auth6_test                   PROPERTIES DEPENDS auth6)
    SET_TESTS_PROPERTIES(auth7_test                   PROPERTIES DEPENDS auth7)
    SET_TESTS_PROPERTIES(box_test                     PROPERTIES DEPENDS box)
    SET_TESTS_PROPERTIES(box2_test                    PROPERTIES DEPENDS box2)
    SET_TESTS_PROPERTIES(box7_test                    PROPERTIES DEPENDS box7)
    SET_TESTS_PROPERTIES(box8_test                    PROPERTIES DEPENDS box8)
    SET_TESTS_PROPERTIES(box_easy_test                PROPERTIES DEPENDS box_easy)
    SET_TESTS_PROPERTIES(box_easy2_test               PROPERTIES DEPENDS box_easy2)
    SET_TESTS_PROPERTIES(box_seal_test                PROPERTIES DEPENDS box_seal)
    SET_TESTS_PROPERTIES(box_seed_test                PROPERTIES DEPENDS box_seed)
    SET_TESTS_PROPERTIES(chacha20_test                PROPERTIES DEPENDS chacha20)
    SET_TESTS_PROPERTIES(codecs_test                  PROPERTIES DEPENDS codecs)
    SET_TESTS_PROPERTIES(core1_test                   PROPERTIES DEPENDS core1)
    SET_TESTS_PROPERTIES(core2_test                   PROPERTIES DEPENDS core2)
    SET_TESTS_PROPERTIES(core3_test                   PROPERTIES DEPENDS core3)
    SET_TESTS_PROPERTIES(core4_test                   PROPERTIES DEPENDS core4)
    SET_TESTS_PROPERTIES(core5_test                   PROPERTIES DEPENDS core5)
    SET_TESTS_PROPERTIES(core6_test                   PROPERTIES DEPENDS core6)
    SET_TESTS_PROPERTIES(core_ed25519_test            PROPERTIES DEPENDS core_ed25519)
    SET_TESTS_PROPERTIES(core_ristretto255_test       PROPERTIES DEPENDS core_ristretto255)
    SET_TESTS_PROPERTIES(ed25519_convert_test         PROPERTIES DEPENDS ed25519_convert)
    SET_TESTS_PROPERTIES(generichash_test             PROPERTIES DEPENDS generichash)
    SET_TESTS_PROPERTIES(generichash2_test            PROPERTIES DEPENDS generichash2)
    SET_TESTS_PROPERTIES(generichash3_test            PROPERTIES DEPENDS generichash3)
    SET_TESTS_PROPERTIES(hash_test                    PROPERTIES DEPENDS hash)
    SET_TESTS_PROPERTIES(hash3_test                   PROPERTIES DEPENDS hash3)
    SET_TESTS_PROPERTIES(kdf_test                     PROPERTIES DEPENDS kdf)
    SET_TESTS_PROPERTIES(keygen_test                  PROPERTIES DEPENDS keygen)
    SET_TESTS_PROPERTIES(metamorphic_test             PROPERTIES DEPENDS metamorphic)
    SET_TESTS_PROPERTIES(misuse_test                  PROPERTIES DEPENDS misuse)
    SET_TESTS_PROPERTIES(onetimeauth_test             PROPERTIES DEPENDS onetimeauth)
    SET_TESTS_PROPERTIES(onetimeauth2_test            PROPERTIES DEPENDS onetimeauth2)
    SET_TESTS_PROPERTIES(onetimeauth7_test            PROPERTIES DEPENDS onetimeauth7)
    SET_TESTS_PROPERTIES(pwhash_argon2i_test          PROPERTIES DEPENDS pwhash_argon2i)
    SET_TESTS_PROPERTIES(pwhash_argon2id_test         PROPERTIES DEPENDS pwhash_argon2id)
    SET_TESTS_PROPERTIES(pwhash_scrypt_test           PROPERTIES DEPENDS pwhash_scrypt)
    SET_TESTS_PROPERTIES(pwhash_scrypt_ll_test        PROPERTIES DEPENDS pwhash_scrypt_ll)
    SET_TESTS_PROPERTIES(randombytes_test             PROPERTIES DEPENDS randombytes)
    SET_TESTS_PROPERTIES(scalarmult_test              PROPERTIES DEPENDS scalarmult)
    SET_TESTS_PROPERTIES(scalarmult2_test             PROPERTIES DEPENDS scalarmult2)
    SET_TESTS_PROPERTIES(scalarmult5_test             PROPERTIES DEPENDS scalarmult5)
    SET_TESTS_PROPERTIES(scalarmult6_test             PROPERTIES DEPENDS scalarmult6)
    SET_TESTS_PROPERTIES(scalarmult7_test             PROPERTIES DEPENDS scalarmult7)
    SET_TESTS_PROPERTIES(scalarmult8_test             PROPERTIES DEPENDS scalarmult8)
    SET_TESTS_PROPERTIES(scalarmult_ed25519_test      PROPERTIES DEPENDS scalarmult_ed25519)
    SET_TESTS_PROPERTIES(scalarmult_ristretto255_test PROPERTIES DEPENDS scalarmult_ristretto255)
    SET_TESTS_PROPERTIES(secretbox_test               PROPERTIES DEPENDS secretbox)
    SET_TESTS_PROPERTIES(secretbox2_test              PROPERTIES DEPENDS secretbox2)
    SET_TESTS_PROPERTIES(secretbox7_test              PROPERTIES DEPENDS secretbox7)
    SET_TESTS_PROPERTIES(secretbox8_test              PROPERTIES DEPENDS secretbox8)
    SET_TESTS_PROPERTIES(secretbox_easy_test          PROPERTIES DEPENDS secretbox_easy)
    SET_TESTS_PROPERTIES(secretbox_easy2_test         PROPERTIES DEPENDS secretbox_easy2)
    SET_TESTS_PROPERTIES(secretstream_test            PROPERTIES DEPENDS secretstream)
    SET_TESTS_PROPERTIES(shorthash_test               PROPERTIES DEPENDS shorthash)
    SET_TESTS_PROPERTIES(sign_test                    PROPERTIES DEPENDS sign)
    SET_TESTS_PROPERTIES(siphashx24_test              PROPERTIES DEPENDS siphashx24)
    SET_TESTS_PROPERTIES(sodium_core_test             PROPERTIES DEPENDS sodium_core)
    SET_TESTS_PROPERTIES(sodium_utils_test            PROPERTIES DEPENDS sodium_utils)
    SET_TESTS_PROPERTIES(sodium_utils2_test           PROPERTIES DEPENDS sodium_utils2)
    SET_TESTS_PROPERTIES(sodium_utils3_test           PROPERTIES DEPENDS sodium_utils3)
    SET_TESTS_PROPERTIES(sodium_version_test          PROPERTIES DEPENDS sodium_version)
    SET_TESTS_PROPERTIES(stream_test                  PROPERTIES DEPENDS stream)
    SET_TESTS_PROPERTIES(stream2_test                 PROPERTIES DEPENDS stream2)
    SET_TESTS_PROPERTIES(stream3_test                 PROPERTIES DEPENDS stream3)
    SET_TESTS_PROPERTIES(stream4_test                 PROPERTIES DEPENDS stream4)
    SET_TESTS_PROPERTIES(verify1_test                 PROPERTIES DEPENDS verify1)
    SET_TESTS_PROPERTIES(xchacha20_test               PROPERTIES DEPENDS xchacha20)

ENDIF(${SODIUM_ENABLE_TESTS})

####
# Installation (https://github.com/novocodev/libsodium-CMake)

# Layout. This works for all platforms:
#   * <prefix>/lib/cmake/<PROJECT-NAME>
#   * <prefix>/lib/
#   * <prefix>/include/
set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * targets_export_name
#   * PROJECT_NAME
MESSAGE(STATUS "Configure Config.cmake.in file located in ${CMAKE_CURRENT_SOURCE_DIR}/cmake")
configure_package_config_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Targets:
#   * <prefix>/lib/libbar.a
#   * <prefix>/lib/libbaz.a
#   * header location after install: <prefix>/include/foo/Bar.hpp
#   * headers can be included by C++ code `#include <foo/Bar.hpp>`
install(
    TARGETS ${SODIUM_TARGET}
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

#install(TARGETS libsodium DESTINATION ".")

# Headers:
#   * Source/foo/Bar.hpp -> <prefix>/include/foo/Bar.hpp
#   * Source/foo/Baz.hpp -> <prefix>/include/foo/Baz.hpp
install(
	DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/libsodium/include/"
    DESTINATION "${include_install_dir}/libsodium"
    FILES_MATCHING PATTERN "*.h"
)

# Export headers:
#   ${libsodium_HEADERS}
#install(
#    FILES
#        ${libsodium_HEADERS}
#    DESTINATION "${include_install_dir}"
#)

# Config
#   * <prefix>/lib/cmake/Foo/FooConfig.cmake
#   * <prefix>/lib/cmake/Foo/FooConfigVersion.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooTargets.cmake
install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)


#install(FILES ${libsodium_HEADERS} DESTINATION "libsodium")
