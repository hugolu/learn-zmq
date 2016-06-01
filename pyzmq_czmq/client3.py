import zmq
from datetime import datetime

ctx = zmq.Context()
socket = ctx.socket(zmq.REQ)
socket.connect('tcp://localhost:5566')
socket.send_multipart(['192.168.1.100', datetime.utcnow().strftime("%Y%m%d%H%M%S")])
words = socket.recv_multipart()
for word in words:
    port, timestamp = word.split(':')
    print "port: %5s, timestamp: %s" % (port, timestamp)
socket.close()
