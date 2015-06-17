import time
import nodeComm
import dBComm
import Functions
import RulesEngine

#Checks to see if another instance of this scrip is running
#if running end this process, if not continue running script
Functions.check_for_running()

#Runs Forever
while 1:
	nodedict = []
	if(dBComm.nodeCount() > 0):
		#Checks all known Nodes, retrieves NodeID and NodeIP and polls through
		for node in dBComm.getEnabledNodes():
			#Collects Nodes Sensor data (String Form)
			nodeData = nodeComm.Node_Data_Request(node['IP'],node['NodeID'])
			
			#Converts Nodes string into JSON
			json_file = Functions.convert_ArduinoString_ToJSON(nodeData)
			
			#Stores NodeID/Node JSON into nodedict
			nodedict.append(Functions.tempNodeArray(node['NodeID'],node['IP'],json_file))
			#Checks to see if current data is equal to last entry
			#if not store the JSON
			if dBComm.check_duplicate_data(node['NodeID'],json_file) == False:
				dBComm.dBJSON_Store(json_file,node['NodeID']);
			
		RulesEngine.check_vs_Rules(nodedict)