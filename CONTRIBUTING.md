# Contributing

Keep endpoint wrappers thin and route-specific. Put common transport, signing,
and serialization behavior in shared helpers.

Before opening a change:

```sh
cmake --build build
ctest --test-dir build --output-on-failure
cmake --build build --target format-check
```

