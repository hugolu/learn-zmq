import zmq

ctx = zmq.Context()
sock = ctx.socket(zmq.REQ)
sock.connect('tcp://localhost:5566')
sock.send_multipart(['192.168.1.100', '20160520000100'])
conns = sock.recv_json()
for conn in conns:
    print conn
sock.close()
