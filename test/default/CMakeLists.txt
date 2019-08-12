
ADD_EXECUTABLE       (aead_aes256gcm        cmptest.h aead_aes256gcm.c)
TARGET_LINK_LIBRARIES(aead_aes256gcm        libsodium)

ADD_EXECUTABLE       (aead_aes256gcm2       cmptest.h aead_aes256gcm2.c)
TARGET_LINK_LIBRARIES(aead_aes256gcm2       libsodium)

ADD_EXECUTABLE       (aead_chacha20poly1305 cmptest.h aead_chacha20poly1305.c)
TARGET_LINK_LIBRARIES(aead_chacha20poly1305 libsodium)

ADD_EXECUTABLE       (aead_chacha20poly13052 cmptest.h aead_chacha20poly13052.c)
TARGET_LINK_LIBRARIES(aead_chacha20poly13052 libsodium)

ADD_EXECUTABLE       (aead_xchacha20poly1305 cmptest.h aead_xchacha20poly1305.c)
TARGET_LINK_LIBRARIES(aead_xchacha20poly1305 libsodium)

ADD_EXECUTABLE       (auth                  cmptest.h auth.c)
TARGET_LINK_LIBRARIES(auth                  libsodium)

ADD_EXECUTABLE       (auth2                 cmptest.h auth2.c)
TARGET_LINK_LIBRARIES(auth2                 libsodium)

ADD_EXECUTABLE       (auth3                 cmptest.h auth3.c)
TARGET_LINK_LIBRARIES(auth3                 libsodium)

ADD_EXECUTABLE       (auth5                 cmptest.h auth5.c ${PROJECT_SOURCE_DIR}/test/quirks/quirks.h)
TARGET_LINK_LIBRARIES(auth5                 libsodium)

ADD_EXECUTABLE       (auth6                 cmptest.h auth6.c ${PROJECT_SOURCE_DIR}/test/quirks/quirks.h)
TARGET_LINK_LIBRARIES(auth6                 libsodium)

ADD_EXECUTABLE       (auth7                 cmptest.h auth7.c ${PROJECT_SOURCE_DIR}/test/quirks/quirks.h)
TARGET_LINK_LIBRARIES(auth7                 libsodium)

ADD_EXECUTABLE       (box                   cmptest.h box.c)
TARGET_LINK_LIBRARIES(box                   libsodium)

ADD_EXECUTABLE       (box2                  cmptest.h box2.c)
TARGET_LINK_LIBRARIES(box2                  libsodium)

ADD_EXECUTABLE       (box7                  cmptest.h box7.c)
TARGET_LINK_LIBRARIES(box7                  libsodium)

ADD_EXECUTABLE       (box8                  cmptest.h box8.c)
TARGET_LINK_LIBRARIES(box8                  libsodium)

ADD_EXECUTABLE       (box_easy              cmptest.h box_easy.c)
TARGET_LINK_LIBRARIES(box_easy              libsodium)

ADD_EXECUTABLE       (box_easy2             cmptest.h box_easy2.c)
TARGET_LINK_LIBRARIES(box_easy2             libsodium)

ADD_EXECUTABLE       (box_seal              cmptest.h box_seal.c)
TARGET_LINK_LIBRARIES(box_seal              libsodium)

ADD_EXECUTABLE       (box_seed              cmptest.h box_seed.c)
TARGET_LINK_LIBRARIES(box_seed              libsodium)

ADD_EXECUTABLE       (chacha20              cmptest.h chacha20.c)
TARGET_LINK_LIBRARIES(chacha20              libsodium)

ADD_EXECUTABLE       (codecs                cmptest.h codecs.c)
TARGET_LINK_LIBRARIES(codecs                libsodium)

ADD_EXECUTABLE       (core1                 cmptest.h core1.c)
TARGET_LINK_LIBRARIES(core1                 libsodium)

ADD_EXECUTABLE       (core2                 cmptest.h core2.c)
TARGET_LINK_LIBRARIES(core2                 libsodium)

ADD_EXECUTABLE       (core3                 cmptest.h core3.c)
TARGET_LINK_LIBRARIES(core3                 libsodium)

ADD_EXECUTABLE       (core4                 cmptest.h core4.c)
TARGET_LINK_LIBRARIES(core4                 libsodium)

ADD_EXECUTABLE       (core5                 cmptest.h core5.c)
TARGET_LINK_LIBRARIES(core5                 libsodium)

ADD_EXECUTABLE       (core6                 cmptest.h core6.c)
TARGET_LINK_LIBRARIES(core6                 libsodium)

ADD_EXECUTABLE       (core_ed25519          cmptest.h core_ed25519.c)
TARGET_LINK_LIBRARIES(core_ed25519          libsodium)

ADD_EXECUTABLE       (core_ristretto255     cmptest.h core_ristretto255.c)
TARGET_LINK_LIBRARIES(core_ristretto255     libsodium)

ADD_EXECUTABLE       (ed25519_convert       cmptest.h ed25519_convert.c)
TARGET_LINK_LIBRARIES(ed25519_convert       libsodium)

ADD_EXECUTABLE       (generichash           cmptest.h generichash.c)
TARGET_LINK_LIBRARIES(generichash           libsodium)

ADD_EXECUTABLE       (generichash2          cmptest.h generichash2.c)
TARGET_LINK_LIBRARIES(generichash2          libsodium)

ADD_EXECUTABLE       (generichash3          cmptest.h generichash3.c)
TARGET_LINK_LIBRARIES(generichash3          libsodium)

ADD_EXECUTABLE       (hash                  cmptest.h hash.c)
TARGET_LINK_LIBRARIES(hash                  libsodium)

ADD_EXECUTABLE       (hash3                 cmptest.h hash3.c)
TARGET_LINK_LIBRARIES(hash3                 libsodium)

ADD_EXECUTABLE       (kdf                   cmptest.h kdf.c)
TARGET_LINK_LIBRARIES(kdf                   libsodium)

ADD_EXECUTABLE       (keygen                cmptest.h keygen.c)
TARGET_LINK_LIBRARIES(keygen                libsodium)

ADD_EXECUTABLE       (metamorphic           cmptest.h metamorphic.c)
TARGET_LINK_LIBRARIES(metamorphic           libsodium)

ADD_EXECUTABLE       (misuse                cmptest.h misuse.c)
TARGET_LINK_LIBRARIES(misuse                libsodium)

ADD_EXECUTABLE       (onetimeauth           cmptest.h onetimeauth.c)
TARGET_LINK_LIBRARIES(onetimeauth           libsodium)

ADD_EXECUTABLE       (onetimeauth2          cmptest.h onetimeauth2.c)
TARGET_LINK_LIBRARIES(onetimeauth2          libsodium)

ADD_EXECUTABLE       (onetimeauth7          cmptest.h onetimeauth7.c)
TARGET_LINK_LIBRARIES(onetimeauth7          libsodium)

ADD_EXECUTABLE       (pwhash_argon2i        cmptest.h pwhash_argon2i.c)
TARGET_LINK_LIBRARIES(pwhash_argon2i        libsodium)

ADD_EXECUTABLE       (pwhash_argon2id       cmptest.h pwhash_argon2id.c)
TARGET_LINK_LIBRARIES(pwhash_argon2id       libsodium)

ADD_EXECUTABLE       (pwhash_scrypt         cmptest.h pwhash_scrypt.c)
TARGET_LINK_LIBRARIES(pwhash_scrypt         libsodium)

ADD_EXECUTABLE       (pwhash_scrypt_ll      cmptest.h pwhash_scrypt_ll.c)
TARGET_LINK_LIBRARIES(pwhash_scrypt_ll      libsodium)

ADD_EXECUTABLE       (randombytes           cmptest.h randombytes.c)
TARGET_LINK_LIBRARIES(randombytes           libsodium)

ADD_EXECUTABLE       (scalarmult            cmptest.h scalarmult.c)
TARGET_LINK_LIBRARIES(scalarmult            libsodium)

ADD_EXECUTABLE       (scalarmult2           cmptest.h scalarmult2.c)
TARGET_LINK_LIBRARIES(scalarmult2           libsodium)

ADD_EXECUTABLE       (scalarmult5           cmptest.h scalarmult5.c)
TARGET_LINK_LIBRARIES(scalarmult5           libsodium)

ADD_EXECUTABLE       (scalarmult6           cmptest.h scalarmult6.c)
TARGET_LINK_LIBRARIES(scalarmult6           libsodium)

ADD_EXECUTABLE       (scalarmult7           cmptest.h scalarmult7.c)
TARGET_LINK_LIBRARIES(scalarmult7           libsodium)

ADD_EXECUTABLE       (scalarmult8           cmptest.h scalarmult8.c)
TARGET_LINK_LIBRARIES(scalarmult8           libsodium)

ADD_EXECUTABLE       (scalarmult_ed25519    cmptest.h scalarmult_ed25519.c)
TARGET_LINK_LIBRARIES(scalarmult_ed25519    libsodium)

ADD_EXECUTABLE       (scalarmult_ristretto255 cmptest.h scalarmult_ristretto255.c)
TARGET_LINK_LIBRARIES(scalarmult_ristretto255 libsodium)

ADD_EXECUTABLE       (secretbox             cmptest.h secretbox.c)
TARGET_LINK_LIBRARIES(secretbox             libsodium)

ADD_EXECUTABLE       (secretbox2            cmptest.h secretbox2.c)
TARGET_LINK_LIBRARIES(secretbox2            libsodium)

ADD_EXECUTABLE       (secretbox7            cmptest.h secretbox7.c)
TARGET_LINK_LIBRARIES(secretbox7            libsodium)

ADD_EXECUTABLE       (secretbox8            cmptest.h secretbox8.c)
TARGET_LINK_LIBRARIES(secretbox8            libsodium)

ADD_EXECUTABLE       (secretbox_easy        cmptest.h secretbox_easy.c)
TARGET_LINK_LIBRARIES(secretbox_easy        libsodium)

ADD_EXECUTABLE       (secretbox_easy2       cmptest.h secretbox_easy2.c)
TARGET_LINK_LIBRARIES(secretbox_easy2       libsodium)

ADD_EXECUTABLE       (secretstream          cmptest.h secretstream.c)
TARGET_LINK_LIBRARIES(secretstream          libsodium)

ADD_EXECUTABLE       (shorthash             cmptest.h shorthash.c)
TARGET_LINK_LIBRARIES(shorthash             libsodium)

ADD_EXECUTABLE       (sign                  cmptest.h sign.c)
TARGET_LINK_LIBRARIES(sign                  libsodium)

ADD_EXECUTABLE       (siphashx24           cmptest.h siphashx24.c)
TARGET_LINK_LIBRARIES(siphashx24           libsodium)

ADD_EXECUTABLE       (sodium_core           cmptest.h sodium_core.c)
TARGET_LINK_LIBRARIES(sodium_core           libsodium)

ADD_EXECUTABLE       (sodium_utils          cmptest.h sodium_utils.c)
TARGET_LINK_LIBRARIES(sodium_utils          libsodium)

ADD_EXECUTABLE       (sodium_utils2         cmptest.h sodium_utils2.c)
TARGET_LINK_LIBRARIES(sodium_utils2         libsodium)

ADD_EXECUTABLE       (sodium_utils3         cmptest.h sodium_utils3.c)
TARGET_LINK_LIBRARIES(sodium_utils3         libsodium)

ADD_EXECUTABLE       (sodium_version        cmptest.h sodium_version.c)
TARGET_LINK_LIBRARIES(sodium_version        libsodium)

ADD_EXECUTABLE       (stream                cmptest.h stream.c)
TARGET_LINK_LIBRARIES(stream                libsodium)

ADD_EXECUTABLE       (stream2               cmptest.h stream2.c)
TARGET_LINK_LIBRARIES(stream2               libsodium)

ADD_EXECUTABLE       (stream3               cmptest.h stream3.c)
TARGET_LINK_LIBRARIES(stream3               libsodium)

ADD_EXECUTABLE       (stream4               cmptest.h stream4.c)
TARGET_LINK_LIBRARIES(stream4               libsodium)

ADD_EXECUTABLE       (verify1               cmptest.h verify1.c)
TARGET_LINK_LIBRARIES(verify1               libsodium)

ADD_EXECUTABLE       (xchacha20             cmptest.h xchacha20.c)
TARGET_LINK_LIBRARIES(xchacha20             libsodium)

SET_TARGET_PROPERTIES(aead_aes256gcm                    PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(aead_aes256gcm2                   PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(aead_chacha20poly1305             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(aead_chacha20poly13052            PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(aead_xchacha20poly1305            PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(auth                              PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(auth2                             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(auth3                             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(auth5                             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(auth6                             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(auth7                             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(box                               PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(box2                              PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(box7                              PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(box8                              PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(box_easy                          PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(box_easy2                         PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(box_seal                          PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(box_seed                          PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(chacha20                          PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(codecs                            PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(core1                             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(core2                             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(core3                             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(core4                             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(core5                             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(core6                             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(core_ed25519                      PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(core_ristretto255                 PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(ed25519_convert                   PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(generichash                       PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(generichash2                      PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(generichash3                      PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(hash                              PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(hash3                             PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(kdf                               PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(keygen                            PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(metamorphic                       PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(misuse                            PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(onetimeauth                       PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(onetimeauth2                      PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(onetimeauth7                      PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(pwhash_argon2i                    PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(pwhash_argon2id                   PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(pwhash_scrypt                     PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(pwhash_scrypt_ll                  PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(randombytes                       PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(scalarmult                        PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(scalarmult2                       PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(scalarmult5                       PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(scalarmult6                       PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(scalarmult7                       PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(scalarmult8                       PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(scalarmult_ed25519                PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(scalarmult_ristretto255           PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(secretbox                         PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(secretbox2                        PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(secretbox7                        PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(secretbox8                        PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(secretbox_easy                    PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(secretbox_easy2                   PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(secretstream                      PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(shorthash                         PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(sign                              PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(siphashx24                        PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(sodium_core                       PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(sodium_utils                      PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(sodium_utils2                     PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(sodium_utils3                     PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(sodium_version                    PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(stream                            PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(stream2                           PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(stream3                           PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(stream4                           PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(verify1                           PROPERTIES FOLDER Tests)
SET_TARGET_PROPERTIES(xchacha20                         PROPERTIES FOLDER Tests)

TARGET_INCLUDE_DIRECTORIES(aead_aes256gcm               PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(aead_aes256gcm2              PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(aead_chacha20poly1305        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(aead_chacha20poly13052       PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(aead_xchacha20poly1305       PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(auth                         PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(auth2                        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(auth3                        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(auth5                        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(auth6                        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(auth7                        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(box                          PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(box2                         PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(box7                         PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(box8                         PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(box_easy                     PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(box_easy2                    PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(box_seal                     PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(box_seed                     PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(chacha20                     PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(codecs                       PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(core1                        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(core2                        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(core3                        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(core4                        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(core5                        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(core6                        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(core_ed25519                 PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(core_ristretto255            PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(ed25519_convert              PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(generichash                  PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(generichash2                 PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(generichash3                 PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(hash                         PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(hash3                        PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(kdf                          PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(keygen                       PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(metamorphic                  PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(misuse                       PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(onetimeauth                  PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(onetimeauth2                 PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(onetimeauth7                 PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(pwhash_argon2i               PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(pwhash_argon2id              PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(pwhash_scrypt                PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(pwhash_scrypt_ll             PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(randombytes                  PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(scalarmult                   PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(scalarmult2                  PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(scalarmult5                  PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(scalarmult6                  PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(scalarmult7                  PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(scalarmult8                  PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(scalarmult_ed25519           PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(scalarmult_ristretto255      PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(secretbox                    PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(secretbox2                   PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(secretbox7                   PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(secretbox8                   PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(secretbox_easy               PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(secretbox_easy2              PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(secretstream                 PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(shorthash                    PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(sign                         PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(siphashx24                   PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(sodium_core                  PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(sodium_utils                 PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(sodium_utils2                PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(sodium_utils3                PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(sodium_version               PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(stream                       PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(stream2                      PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(stream3                      PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(stream4                      PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(verify1                      PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)
TARGET_INCLUDE_DIRECTORIES(xchacha20                    PRIVATE ${PROJECT_SOURCE_DIR}/test/quirks)

SET(ADDITIONAL_CLEAN_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/aead_chacha20poly1305.res
    ${CMAKE_CURRENT_SOURCE_DIR}/auth.res
    ${CMAKE_CURRENT_SOURCE_DIR}/auth2.res
    ${CMAKE_CURRENT_SOURCE_DIR}/auth3.res
    ${CMAKE_CURRENT_SOURCE_DIR}/auth5.res
    ${CMAKE_CURRENT_SOURCE_DIR}/auth6.res
    ${CMAKE_CURRENT_SOURCE_DIR}/auth7.res
    ${CMAKE_CURRENT_SOURCE_DIR}/box.res
    ${CMAKE_CURRENT_SOURCE_DIR}/box2.res
    ${CMAKE_CURRENT_SOURCE_DIR}/box7.res
    ${CMAKE_CURRENT_SOURCE_DIR}/box8.res
    ${CMAKE_CURRENT_SOURCE_DIR}/box_easy.res
    ${CMAKE_CURRENT_SOURCE_DIR}/box_easy2.res
    ${CMAKE_CURRENT_SOURCE_DIR}/box_seal.res
    ${CMAKE_CURRENT_SOURCE_DIR}/box_seed.res
    ${CMAKE_CURRENT_SOURCE_DIR}/chacha20.res
    ${CMAKE_CURRENT_SOURCE_DIR}/core1.res
    ${CMAKE_CURRENT_SOURCE_DIR}/core2.res
    ${CMAKE_CURRENT_SOURCE_DIR}/core3.res
    ${CMAKE_CURRENT_SOURCE_DIR}/core4.res
    ${CMAKE_CURRENT_SOURCE_DIR}/core5.res
    ${CMAKE_CURRENT_SOURCE_DIR}/core6.res
    ${CMAKE_CURRENT_SOURCE_DIR}/ed25519_convert.res
    ${CMAKE_CURRENT_SOURCE_DIR}/generichash.res
    ${CMAKE_CURRENT_SOURCE_DIR}/generichash2.res
    ${CMAKE_CURRENT_SOURCE_DIR}/generichash3.res
    ${CMAKE_CURRENT_SOURCE_DIR}/hash.res
    ${CMAKE_CURRENT_SOURCE_DIR}/hash2.res
    ${CMAKE_CURRENT_SOURCE_DIR}/hash3.res
    ${CMAKE_CURRENT_SOURCE_DIR}/onetimeauth.res
    ${CMAKE_CURRENT_SOURCE_DIR}/onetimeauth2.res
    ${CMAKE_CURRENT_SOURCE_DIR}/onetimeauth7.res
    ${CMAKE_CURRENT_SOURCE_DIR}/pwhash.res
    ${CMAKE_CURRENT_SOURCE_DIR}/pwhash_scrypt_ll.res
    ${CMAKE_CURRENT_SOURCE_DIR}/randombytes.res
    ${CMAKE_CURRENT_SOURCE_DIR}/scalarmult.res
    ${CMAKE_CURRENT_SOURCE_DIR}/scalarmult2.res
    ${CMAKE_CURRENT_SOURCE_DIR}/scalarmult5.res
    ${CMAKE_CURRENT_SOURCE_DIR}/scalarmult6.res
    ${CMAKE_CURRENT_SOURCE_DIR}/scalarmult7.res
    ${CMAKE_CURRENT_SOURCE_DIR}/secretbox.res
    ${CMAKE_CURRENT_SOURCE_DIR}/secretbox2.res
    ${CMAKE_CURRENT_SOURCE_DIR}/secretbox7.res
    ${CMAKE_CURRENT_SOURCE_DIR}/secretbox8.res
    ${CMAKE_CURRENT_SOURCE_DIR}/secretbox_easy.res
    ${CMAKE_CURRENT_SOURCE_DIR}/secretbox_easy2.res
    ${CMAKE_CURRENT_SOURCE_DIR}/shorthash.res
    ${CMAKE_CURRENT_SOURCE_DIR}/sign.res
    ${CMAKE_CURRENT_SOURCE_DIR}/sodium_core.res
    ${CMAKE_CURRENT_SOURCE_DIR}/sodium_utils.res
    ${CMAKE_CURRENT_SOURCE_DIR}/sodium_utils2.res
    ${CMAKE_CURRENT_SOURCE_DIR}/sodium_utils3.res
    ${CMAKE_CURRENT_SOURCE_DIR}/sodium_version.res
    ${CMAKE_CURRENT_SOURCE_DIR}/stream.res
    ${CMAKE_CURRENT_SOURCE_DIR}/stream2.res
    ${CMAKE_CURRENT_SOURCE_DIR}/stream3.res
    ${CMAKE_CURRENT_SOURCE_DIR}/stream4.res
    ${CMAKE_CURRENT_SOURCE_DIR}/verify1.res
)

SET_DIRECTORY_PROPERTIES(PROPERTIES
ADDITIONAL_MAKE_CLEAN_FILES "${ADDITIONAL_CLEAN_FILES}")