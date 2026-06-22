Follow the repository style closely and keep diffs surgical.

Files over roughly 300 lines should be treated as a design smell. Split route
groups, transport helpers, and tests before adding broad endpoint coverage.

Do not add mock exchange behavior, silent fallbacks, or speculative endpoint
wrappers. Prefer generic request helpers for unwrapped Binance routes and
surface real HTTP/API errors to callers.

Current scope:
- Binance Spot REST over libcurl with connection reuse and HMAC SHA-256 signing.
- Public market WebSocket stream helpers behind an optional ixwebsocket build.
- Thin typed helpers for common market, account, and trading endpoints.
- Raw JSON responses, matching the Bybit C++ client style.

Verification:
- Configure and build with CMake.
- Run the narrow unit tests for signing, query encoding, order params, and
  WebSocket topic construction.
- Run formatting when source files change.

