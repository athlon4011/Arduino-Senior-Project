import json
import sys
import commands
import os

#Node Class
class node:
	def __init__(self,id,ip,motion, lux,temp,smoke):
		self.motion = motion
		self.lux = lux
		self.temp = temp
		self.id = id
		self.ip = ip
		self.smoke = smoke

# Functions
#Convert arduino String to JSON
def convert_ArduinoString_ToJSON( arduinoData ):
    stringArray = arduinoData.split(',')

    json_file = dict([(k, v) for k,v in zip (stringArray[::2], stringArray[1::2])])
    
    try:
        return json.dumps(json_file, sort_keys=True)
   
    except (ValueError, KeyError, TypeError):
        print ("JSON ERROR")

#Checks to see if Script is already running, if so exit 
def check_for_running():
    script_name = os.path.basename("/home/pi/scripts/Node_Data_Collect.py")
    status = commands.getstatusoutput("ps aux | grep -e '%s' | grep -v grep | awk '{print $2}'| awk '{print $2}'" % script_name)
    if status[1]:
        sys.exit(0);
       
#Storing of Node Data into Array
def tempNodeArray(NodeID,NodeIP,data):
	data = json.loads(data)
	nodeobj = node(NodeID,NodeIP,data["motion"],data["lux"],data["temp"],data["smoke"])
	return nodeobj

def convert_inst_to_dict(node):
	dict_result = dict((name, getattr(node, name)) for name in dir(node) if not name.startswith('__'))
	return dict_result

#convert string to JSON OBJECT
def convert_String_toJSON(data):
	return json.loads(data)
	