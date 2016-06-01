# Examples of CZMQ

## Simple Push/Pull pattern

source: 
- [helloworld.c](helloworld.c)

build:
```shell
$ g++ -o helloworld helloworld.c -L/usr/local/lib -lczmq -lzmq -lsodium -lrt -lpthread
```

run:
```shell
$ ./helloworld
Hello, World
```

## TCP Request & Reply

source:
- [client.c](client.c)
- [server.c](server.c)

build:
```shell
$ g++ -o client client.c -L/usr/local/lib -lczmq -lzmq -lsodium -lrt -lpthread
$ g++ -o server server.c -L/usr/local/lib -lczmq -lzmq -lsodium -lrt -lpthread
```

run:
```shell
$ ./client
pong
```
```shell
$ ./server
ping
```

## Multi-part Message

source:
- [singleframe_test.c](singleframe_test.c)
- [multiframe_test.c](multiframe_test.c)

build:
```shell
$ g++ -o singleframe_test singleframe_test.c -L/usr/local/lib -lczmq -lzmq -lsodium -lrt -lpthread
$ g++ -o multiframe_test multiframe_test.c -L/usr/local/lib -lczmq -lzmq -lsodium -lrt -lpthread
```

run:
```shell
$ ./singleframe_test
hello
```
```shell
$ ./multiframe_test
apple
banana
cherry
```
