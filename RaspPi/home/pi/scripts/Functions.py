import json
import sys
import commands
import os

# Functions
#Convert String to JSON
def convert_String_ToJSON( arduinoData ):
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
def tempNodeArray(NodeID,data):
    data = []
    dataObj = {NodeID,data}
    data.append(dataObj)
    
    return data
    