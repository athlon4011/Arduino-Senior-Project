import time
import nodeComm
import dBComm
import Functions
import RulesEngine

#Checks to see if another instance of this scrip is running
#if running end this process, if not continue running script
Functions.check_for_running()

#(sound,red,green,blue,loops(1-9),delay(1-9))
#data = "1,111"	

#Runs Forever
while 1:
	nodedict = []
	#Checks all known Nodes, retrieves NodeID and NodeIP and polls through
	for node in dBComm.mysql_fetch_assoc():
		#Testing Send command to node
		#nodeComm.Node_Send_Command(node['IP'],data,node['NodeID'])
		
		#Collects Nodes Sensor data (String Form)
		nodeData = nodeComm.Node_Data_Request(node['IP'],node['NodeID'])
		
		#Converts Nodes string into Json
		json_file = Functions.convert_String_ToJSON(nodeData)
		
		#Stores NodeID/Node Json into nodedict
		nodedict.append(Functions.tempNodeArray(node['NodeID'],json_file))

		#Checks to see if current data is equal to last entry
		#if not store the json
		if dBComm.check_duplicate_data(node['NodeID'],json_file) == False:
			dBComm.dBJSON_Store(json_file,node['NodeID']);
		time.sleep(1)
	
	RulesEngine.check_vs_Rules(nodedict)