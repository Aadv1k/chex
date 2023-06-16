# chex

**In active development**

A chess engine built using C++

## Build

### Unix-Like

This will clean up and build chex

```shell
make all 
```

### Windows

Good ol' MS-DOS being MS-DOS

```shell
make chex_win32
```

run the clean up after or it will fail

```shell
make clean_win32
```

## Test

```shell
make engine/tests
./bin/engine.test
```

## TODO
- Fix the implementation for the knight validity check
