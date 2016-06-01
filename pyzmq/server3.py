import zmq

conns = [(1111, '20160520000001'), (2222, '20160520000002'), (3333, '20160520000003')]

ctx = zmq.Context()
sock = ctx.socket(zmq.REP)
sock.bind('tcp://*:5566')
event = sock.recv_multipart()
print event
sock.send_json(conns)
sock.close()
