# PyZMQ Client + CZMQ Server

## Simple message string

source:
- [client1.py](client1.py)
- [server1.c](server1.c)

build:
```shell
g++ -o server1 server1.c -L/usr/local/lib -lczmq -lzmq -lsodium -lrt -lpthread
```

run:
```shell
$ python client1.py
pong
```
```shell
$ ./server1
pong
```

## Multi-part Message

source:
- [client2.py](client2.py)
- [server2.c](server2.c)

build:
```shell
g++ -o server2 server2.c -L/usr/local/lib -lczmq -lzmq -lsodium -lrt -lpthread
```

run:
```shell
$ python client2.py
apple
banana
cherry
```
```shell
$ ./server2
hello
world
pyzmq
```
