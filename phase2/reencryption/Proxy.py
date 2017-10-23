#proxy file starts first -- maybe change this
import socket
import signal
import time
from multiprocessing import Process, Manager

processes = {}
#######################         close socket on pressing control c       ########################
def sigint_handler(signum, frame):
    print '\nclosing socket'
    s.shutdown(socket.SHUT_RDWR)
    s.close()
    for i in processes:
    	processes[i].terminate()
    	if not processes[i].is_alive():
    		processes[i].join()
    exit()
 
signal.signal(signal.SIGINT, sigint_handler)
#################################################################################################

port = 9999

########################################   create socket #########################################
try:
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	print "socket successfully created"
except socket.error as err:
	print "socket creation failed with error %s" % (err)

s.bind(('', port))
print "socket binded to %s"%(port)

s.listen(5)
print "socket is listening"
###################################################################################################


##function to handle incoming connections
def handleConnection(connections, c, addr):
	print "handler started for %s" % (c)
	name = c.recv(100)
	print "Connection is from %s" % (name)
	#add alice connection to the connection pool
	print "type c = " + str(type(c))
	############################    THIS PART DOES NOT WORK ############# THE SHARED MEMORY
	item = connections[name] = list()
	item.append(c)
	connections[name] = item
	print "connections : " + str(connections)
	c.send('Thank you for connecting %s\n' % (name))


	######  listen forever from client till client says to stop  #####
	while True:
		message = c.recv(1024);
		if message.split()[0] == 'System':
			print name + ' closed Connection'
			break;
		if message.split()[0] in connections:	#send the message to the required guy
			connections[message.split()[0]][0].send( name + ' ' + message[len(message.split()[0]):] );
			c.send("message sent successfully")
		else:
			c.send("user not online...")
		time.sleep(1/1000000.0)
	
	print "handler quitting"
	c.shutdown(socket.SHUT_RDWR)
	c.close()
	#remove alice from the connection pool
	del connections[name]
	return

# connections = {}	
# def handleJoins():
# 	while True:
# 		for i in connections:
# 			connections[i].join()
# 			i.close();
#listen for incoming connections

############################################   main function   ############################################
if __name__ == '__main__':
	## stores the connections by the name of the person who connected
	## name is the first message sent by the person
	connections = Manager().dict()
	while True:
		c, addr = s.accept()
		print "Got connection from", addr
		# connections[1] = c                 manager cnat stoire socket type ?? :(
		p = Process(target = handleConnection, args=(connections, c, addr, ))
		# connections[c] = p;
		processes[c] = p;
		p.start()
		# c.close()

###########################################################################################################
