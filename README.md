# Chex

The homegrown cross-platform chess game/engine in C++

- [Quickstart](#quickstart)
  - [Usage](#usage)
  - [Build](#build)
  - [Test](#test)
- [The engine](#the-engine)

## Quickstart

head on over to the [releases](https://github.com/aadv1k/chex/releases/latest) and grab a copy for your system

### Usage

```shell
$ chex help

Usage:
        ./bin/chex web --port 8000
        ./bin/chex console
Commands:
        web             Start Chex on a local web server
        console         Start Chex as a text-based game
        help            Print this help message
Options:
        --port, -p  Specify the port for the server (default: 8080)
```

### Build

We use [make](https://www.gnu.org/software/make/) to build the source

```
make chex
make clean
```

### Test

```shell
make chex/tests
./bin/chex.test
```


## The engine

The engine is aimed to be **modular**, hence here there is a clear separation between the UI and the engine itself. You can use the engine in your code if you wish to implement a different UI, for which you can refer to:

<img src="./docs/the-layers.svg" alt="the-layers" style="display: block;">

- [UI](./ui/ui.hpp): chex implements two UIs
  - [ui/web](./ui/web/): runs a web server and serves a html frontend  
  - [ui/console](./ui/console): this is essentially a TUI(ish) game
- [Game](./game/game.cpp): The implementation for the game which is an abstraction over the board
- [Board](./board/board.cpp): the board which is the base level of interaction


