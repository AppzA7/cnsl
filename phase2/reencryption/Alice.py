import socket
from struct import *
port = 9999

try:
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	print "socket successfully created"
except socket.error as err:
	print "socket creation failed with error %s" % (err)

try:
	s.connect(('0.0.0.0', port));
except socket.error as err:
	print "connection failed with error %s" % (err)

###### initiate connection with the user name
name = raw_input('Enter username : ')
s.send(name)

### recv initial message
msg = s.recv(100);
print msg

while True:
	dest = raw_input('enter dest username : ')
	if dest == 'System':
		s.send('System')
		break
	message = raw_input('enter message : ');
	a = dest + " " + message;
	print "sending %s"%a
	s.send(a);
	print
	result = s.recv(100)
	print result

s.close()