import zmq

ctx = zmq.Context()

# client
req = ctx.socket(zmq.REQ)
req.connect('tcp://localhost:5566')
req.send_multipart(['apple', 'banana', 'cherry'])
req.close()

# server
rep = ctx.socket(zmq.REP)
rep.bind('tcp://*:5566')
fruits = rep.recv_multipart()
for fruit in fruits:
    print fruit
rep.close()
