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

## Host-connection Client & Server

source:
- [client3.py](client3.py)
- [server3.c](server3.c)

client3 components:

| Item | Description |
|------|-------------|
| `struct host_connection` | is a structure contains the information of host connections |
| `struct request` | is a structure describes the request from clients |
| `get_request()` | parses the requests from clients |
| `hczmq()` | handles the requests from clients |
| `main()` | maintains the information of host connections |

build:
```shell
g++ -o server3 server3.c -L/usr/local/lib -lczmq -lzmq -lsodium -lrt -lpthread
```

run:
```shell
$ ./server3
message from main thread: hello world
ip: 192.168.1.100, timestamp: 20160701074905
  37743:20160601154903
  37744:20160601154904
  37745:20160601154905
ip: 192.168.1.100, timestamp: 20160701074906
  37746:20160601154906
  37744:20160601154904
  37745:20160601154905
ip: 192.168.1.100, timestamp: 20160701074909
  37749:20160601154909
  37747:20160601154907
  37748:20160601154908
```
```shell
$ python client3.py
port: 37743, timestamp: 20160601154903
port: 37744, timestamp: 20160601154904
port: 37745, timestamp: 20160601154905

$ python client3.py
port: 37746, timestamp: 20160601154906
port: 37744, timestamp: 20160601154904
port: 37745, timestamp: 20160601154905

$ python client3.py
port: 37749, timestamp: 20160601154909
port: 37747, timestamp: 20160601154907
port: 37748, timestamp: 20160601154908
```
