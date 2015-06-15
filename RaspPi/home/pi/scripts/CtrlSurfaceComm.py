import dBComm


while 1:
	#get the Control Nodes Information
	for ctrlNodeLoc in dBComm.get_Control_Surface_Nodes():
		LightState = ''
		FanState = ''
		print(ctrlNodeLoc)
		for ctrlState in dBComm.get_State_of_Control_Surface(ctrlNodeLoc['Loc']):
			print (ctrlState)
			if ctrlState['Type'] == 'Light':
				if ctrlState['State'] == 'on':
					LightState = '1'
				else:
					LightState = '0'
			if ctrlState['Type'] == 'Fan':
				if ctrlState['State'] == 'on':
					FanState = '1'
				else:
					FanState = '0'
					#Send Command to Control Surface
			data = LightState + ',' + FanState
			send_Command_to_CtrlSurface(ctrlNodeLoc['IP'], data,ctrlNodeLoc['Loc'])
		
		
		
def send_Command_to_CtrlSurface(NodeIP,data,Loc)
	HOST, PORT = NodeIP, 8888
	# SOCK_DGRAM is the socket type to use for UDP sockets
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	
	# As you can see, there is no connect() call; UDP has no connections.
	# Instead, data is directly sent to the recipient via sendto().
	sock.sendto("send," + data + "\n", (HOST, PORT))
	
	#Log Event Command to arduino
	message = "Sent " + data + " to Control Node in" + Loc+ "."
	dBComm.log_Event("System",message)		