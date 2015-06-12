import socket

from dBComm import store_node_information
from Functions import check_for_running

#Checking To see if this script is already running, if so do not run
check_for_running()

addr = ('', 8888)
# SOCK_DGRAM is the socket type to use for UDP sockets
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(addr)

while 1:
    data = sock.recvfrom(1024)
    
    if data is not None:
        reply = data[0]
        addr = data[1]
        sock.sendto(str('booting'),addr)
        #Check if Node already exist in database
        store_node_information(str(addr[0]),str(reply))


