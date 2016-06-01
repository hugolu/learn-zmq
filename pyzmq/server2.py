import zmq

class SERVER:
    def __init__(self, addr):
        self.sock = None
        self.addr = addr

    def bind(self):
        ctx = zmq.Context()
        self.sock = ctx.socket(zmq.REP)
        self.sock.bind(self.addr)

    def close(self, linger = 0):
        self.sock.close(linger)

    def echo(self):
        msg = self.sock.recv()
        self.sock.send(msg.upper())

server = SERVER('tcp://*:5566')
server.bind()
server.echo()
server.close()
