```
           /$$
          | $$                          
  /$$$$$$$| $$$$$$$   /$$$$$$  /$$   /$$
 /$$_____/| $$__  $$ /$$__  $$|  $$ /$$/
| $$      | $$  \ $$| $$$$$$$$ \  $$$$/ 
| $$      | $$  | $$| $$_____/  >$$  $$ 
|  $$$$$$$| $$  | $$|  $$$$$$$ /$$/  $$
 \_______/|__/  |__/ \_______/|__/  \__/
```

**In active development** The homegrown chess engine in C++

## Usage

```shell
$ chex help

Usage:
	./bin/chex web --port 8000
Commands:
	web         Start Chex on a local web server
	help        Print this help message
Options:
	--port, -p  Specify the port for the server (default: 8080)
```

## Build

We use [make](https://www.gnu.org/software/make/) to build the source

```
make chex
make clean
```

## Test

```shell
make chex/tests
./bin/chex.test
```

