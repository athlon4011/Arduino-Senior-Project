import json
import MySQLdb

#DataBase Connection
dataBase = MySQLdb.connect(host = 'localhost',
                           user = 'root',
                           passwd = 'H0m3r',
                           db = 'homer')

# Functions
    #Convert String to JSON
def convertStringToJSON( dataString ):
    stringArray = dataString.split(',')

    json_file = {'extTemp': stringArray[0], 'intTemp': stringArray[1], 'light': stringArray[2], 'carmon': stringArray[3], 'motion': stringArray[4] }

    try:
        return json.dumps(json_file, sort_keys=True, indent=2)
   
    except (ValueError, KeyError, TypeError):
        print ("JSON ERROR")

    return;

    #Store JSON into Database
def dBJSON_Store(json_file,NodeID):
    cursor = dataBase.cursor()
    cursor.execute("Insert into Sensor_Log(Date,NodeID,Data) values(CURDATE(),%s,%s)",(NodeID,json_file))

    dataBase.commit()

    return;
    
    #Requesting NodeID and IP
def nodeInformationRequest(size):
    cursor = dataBase.cursor()
    cursor.execute("Select NodeID,IP from Nodes where NodeID = %s",(size))
    return cursor.fetchone();

    #Requesting Node Count
def nodeCount():
    cursor = dataBase.cursor()
    cursor.execute("Select COUNT(NodeID) from Nodes")
    result = cursor.fetchone()
    return  result;

#Main Function
       
#TEST STRING
data = "extTemp,intTemp,light,carmon,motion"


#Runs Forever
#while True:
for size in nodeCount(): 
    node = nodeInformationRequest(size)
    NodeID = node[0]
    NodeIP = node[1]
    json_file = convertStringToJSON(data)
    dBJSON_Store(json_file,NodeID);
  
