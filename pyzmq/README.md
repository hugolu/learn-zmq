# Examples of PyZMQ

## Simple TCP Request/Reply

source:
- [client1.py](client1.py)
- [server1.py](server1.py)

run:
```shell
$ python server1.py
ping
```
```shell
$ python client1.py
pong
```

## OOP client/server

source:
- [client2.py](client2.py)
- [server2.py](server2.py)

run:
```shell
$ python server2.py
```
```shell
$ python client2.py
HELLO WORLD
```

## Send/receive tuple and json object

source:
- [client3.py](client3.py)
- [server3.py](server3.py)

run:
```shell
$ python client3.py
[1111, u'20160520000001']
[2222, u'20160520000002']
[3333, u'20160520000003']
```
```shell
$ python server3.py
['192.168.1.100', '20160520000100']
```

## Send/receive Multi-part Message

source:
- [multipart_test.py](multipart_test.py)

run:
```shell
$ python multipart_test.py
apple
banana
cherry
```
