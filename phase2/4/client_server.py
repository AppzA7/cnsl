import socket
import signal
import time
from multiprocessing import Process, Manager
import copy_reg
import json
import time
from multiprocessing.reduction import rebuild_socket, reduce_socket

copy_reg.pickle(socket.socket, reduce_socket, rebuild_socket)

port = 9999

def authenticate(p):
	pass
def checkConnections(connections, s):
	nconnections =list()
	try:
		nconnections = json.dumps(s.recv(100, 2))
		connections = nconnections
		if connections == ['']:
			raise ValueError("ho")
		if len(connections) == 0:
			raise ValueError("ha")
	except:
		raise ValueError('socket error') 
		raise Exception('asd')
	return connections

if __name__ == '__main__':
	processes = {}
	connections = Manager().list()
	###############try connecting#################
	try:
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		p = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		p.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		print "socket successfully created"
	except socket.error as err:
		print "socket creation failed with error %s" % (err)

	try:
		s.connect(('0.0.0.0', port));
	except socket.error as err:
		print "connection failed with error %s" % (err)
	#######################         close socket on pressing control c       ########################
	def sigint_handler(signum, frame):
	    print '\nclosing socket'
	    s.shutdown(socket.SHUT_RDWR)
	    p.shutdown(socket.SHUT_RDWR)
	    s.close()
	    p.close()
	    print "came here"
	    for i in processes:
	    	processes[i].terminate()
	    	if not processes[i].is_alive():
	    		processes[i].join()
	    exit()
	 
	signal.signal(signal.SIGINT, sigint_handler)
	##################################################################################################
	
	while True:
		try:
			connections = list()
			connections = checkConnections(connections, s)
			print connections
		except ValueError as e:
			print "hahahahaha"
			#connect to another server here

		time.sleep(1)
		pass