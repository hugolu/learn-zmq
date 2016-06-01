import zmq

class CLIENT:
    def __init__(self, addr):
        self.sock = None
        self.addr = addr

    def connect(self):
        ctx = zmq.Context()
        self.sock = ctx.socket(zmq.REQ)
        self.sock.connect(self.addr)
        self.sock.setsockopt(zmq.RCVTIMEO, 20000)

    def close(self, linger = 0):
        self.sock.close(linger)

    def greet(self, msg):
        self.sock.send(msg)
        return self.sock.recv()

client = CLIENT('tcp://localhost:5566')
client.connect()
print client.greet('hello world')
client.close()
