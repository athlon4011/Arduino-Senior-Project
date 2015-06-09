import socket
import time
import dBComm

#Send Arduino a command
def Node_Send_Command(NodeIP,data,NodeID):
	HOST, PORT = NodeIP, 8888
	# SOCK_DGRAM is the socket type to use for UDP sockets
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	
	# As you can see, there is no connect() call; UDP has no connections.
	# Instead, data is directly sent to the recipient via sendto().
	sock.sendto("send," + data + "\n", (HOST, PORT))
	
	#Log Event Command to arduino
	message = "Sent " + data + " to Node " + str(NodeID) + "."
	dBComm.log_Event("System",message)
	
#Send Request to Arduino for Sensor information
def Node_Data_Request(NodeIP,NodeID):
    received = ''
    #Loop till data is received
    while received == '':
        HOST, PORT = NodeIP, 8888
    
        # SOCK_DGRAM is the socket type to use for UDP sockets
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
        # As you can see, there is no connect() call; UDP has no connections.
        # Instead, data is directly sent to the recipient via sendto().
        sock.sendto("pull" + "\n", (HOST, PORT))
        received = recv_timeout(sock)
        #Check for Null data, if so Create Error Event
        if received == '':
			message = "Failed to retrieve Node "+str(NodeID)+" data."
			#check to see if last logged Message was the same if so do not log again
			if message != dBComm.get_Last_Log_Event():
				#Create Error Event      
				dBComm.log_Event("Error",message)
    return received;

#Waits for Data to be available on the socket
def recv_timeout(sock,timeout=1):
    #make socket non blocking
    sock.setblocking(0)
    #total data in an array
    total_data=[];
    data='';
     
    #beginning time
    begin=time.time()
    while 1:
        #if you got some data, then break after timeout
        if total_data and time.time()-begin > timeout:
            break
         
        #if you got no data at all, wait a little longer, twice the timeout
        elif time.time()-begin > timeout*2:
            break
         
        #recv something
        try:
            data = sock.recv(8192)
            if data:
                total_data.append(data)
                #change the beginning time for measurement
                begin=time.time()
            else:
                #sleep for sometime to indicate a gap
                time.sleep(0.1)
        except:
            pass
    return ''.join(total_data)  