/* XP-only adapter for the upstream external RNG hook. No upstream patches. */
#include <windows.h>
#include <wincrypt.h>
#include <psa/crypto.h>
#include <psa/crypto_extra.h>
#include <limits.h>

psa_status_t mbedtls_psa_external_get_random(mbedtls_psa_external_random_context_t *context,
    uint8_t *output, size_t output_size, size_t *output_length)
{
    HCRYPTPROV provider = 0;
    size_t offset = 0;
    (void)context;
    *output_length = 0;
    if (!CryptAcquireContextW(&provider, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
        return PSA_ERROR_INSUFFICIENT_ENTROPY;
    while (offset < output_size) {
        DWORD chunk = output_size - offset > MAXDWORD ? MAXDWORD : (DWORD)(output_size - offset);
        if (!CryptGenRandom(provider, chunk, output + offset)) {
            SecureZeroMemory(output, output_size);
            CryptReleaseContext(provider, 0);
            return PSA_ERROR_INSUFFICIENT_ENTROPY;
        }
        offset += chunk;
    }
    CryptReleaseContext(provider, 0);
    *output_length = output_size;
    return PSA_SUCCESS;
}
