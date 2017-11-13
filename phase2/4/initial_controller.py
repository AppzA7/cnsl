import socket
import signal
import time
from multiprocessing import Process, Manager
import copy_reg
import json
from multiprocessing.reduction import rebuild_socket, reduce_socket

copy_reg.pickle(socket.socket, reduce_socket, rebuild_socket)


#has a list of all connected client_server processes

port = 9999
if __name__ == '__main__':
	processes = {}
	connections = [];
	########################################   create socket #########################################
	try:
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		print "socket successfully created"
	except socket.error as err:
		print "socket creation failed with error %s" % (err)

	s.bind(('0.0.0.0', port))
	print "socket binded to %s"%(port)

	s.listen(5)
	print "socket is listening"
	###################################################################################################

	#######################         close socket on pressing control c       ########################
	def sigint_handler(signum, frame):
	    print '\nclosing socket'
	    s.shutdown(socket.SHUT_RDWR)
	    s.close()
	    print "came here"
	    for i in processes:
	    	i.shutdown(socket.SHUT_RDWR)
	    	i.close()
	    exit()
	 
	signal.signal(signal.SIGINT, sigint_handler)
	##################################################################################################

	## stores the connections by the name of the person who connected
	## name is the first message sent by the person
	while True:
		c, addr = s.accept()
		print "Got connection from", addr
		# connections[1] = c                 manager cnat stoire socket type ?? :(
		#p = Process(target = handleConnection, args=(connections, c, addr, ))
		# connections[c] = p;
		processes[c] = addr
		connections.append(addr);
		for i in processes:
			data_serialised = json.dumps(list(connections));
			i.send(data_serialised.encode());
		#p.start()
		# c.close()

###########################################################################################################
