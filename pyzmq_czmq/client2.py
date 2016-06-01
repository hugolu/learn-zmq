import zmq

ctx = zmq.Context()
sock = ctx.socket(zmq.REQ)
sock.connect('tcp://localhost:5566')
sock.send_multipart(['hello', 'world', 'pyzmq'])
words = sock.recv_multipart()
for word in words:
    print word
sock.close()
