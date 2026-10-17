# ca2 Mbed TLS port

Wrapper for upstream Mbed TLS 4.1.1 LTS, pinned as `mbedtls/` with its own nested dependencies.
Initialize with `git submodule update --init --recursive`.

Link `ca2::mbedtls` for static TLS, X.509 and PSA crypto libraries. The wrapper is cross-platform.
The exact `__REACTOS__` CMake flag selects the Windows XP/ReactOS adapter: secure randomness
comes from CryptoAPI instead of BCrypt. Recent Windows keeps the upstream RNG.
Upstream files must remain unchanged; configuration and adapters belong in this wrapper.

Mbed TLS and TF-PSA-Crypto retain their upstream licenses. Choose the Apache-2.0 option
and preserve upstream licenses/notices when redistributing.

XP runtime compatibility requires import auditing and actual XP testing; a host build alone
is not proof. TLS does not supply HTTP framing or trusted roots: those belong in the HTTP backend.

Build-time prerequisites: CMake >=3.20, Python with `jinja2` and `jsonschema`, and Perl.
Pass `-DPython3_EXECUTABLE=...` when using a dedicated build virtual environment.
Generated upstream files are placed in the build tree.
