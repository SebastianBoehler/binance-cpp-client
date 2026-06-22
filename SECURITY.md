# Security

Do not commit real Binance API keys. Use environment variables or an external
secret manager for examples and local testing.

The client exposes raw HTTP/API errors. Treat unknown order status after Binance
timeout responses as unresolved until confirmed through account queries or user
data events.

