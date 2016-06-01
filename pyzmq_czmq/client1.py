import zmq

ctx = zmq.Context()
sock = ctx.socket(zmq.REQ)
sock.connect('tcp://localhost:5566')
sock.send('pong')
print sock.recv()
sock.close()
