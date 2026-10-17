#pragma once
#if defined(__REACTOS__)
#undef MBEDTLS_PSA_BUILTIN_GET_ENTROPY
#define MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG
#endif
