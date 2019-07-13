# Chess Engine

## How to run
```bash
$ ./configure
$ make 
```
This will generate 3 targets that you can also generate separately:
* _chessengine_ - the Chess Engine
* _human_ - the Human client to connect to the engine
* _ai_ - the AI client to connect to the engine

## How to use

### chessengine
```bash
$ ./chessengine -h
```
* -h    Display usage
* -p _port_     Selects the listening port
* --pgn _file_  Parse the _file_ like a PGN file
* -l _listener [listerners]_    Loads the _listeners_

### human

```bash
$ ./human _ip_ _port_
```
Launches a human client on an engine at _ip_ on the port _port_

### ai

```bash
$ ./ai _ip_ _port_
```
Launches an AI client on an engine at _ip_ on the port _port_

## Credit

Daniel Baud (danielbaudf@gmail.com)
Vincent Rivière (vincent1.riviere@epita.fr)
Théo Matas (theo.matas@epita.fr)
