import zmq

ctx = zmq.Context()
sock = ctx.socket(zmq.REP)
sock.bind('tcp://*:5566')
print sock.recv()
sock.send('pong')
sock.close()
