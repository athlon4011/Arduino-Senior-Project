import json
import MySQLdb
import socket
import time

#DataBase Connection
dataBase = MySQLdb.connect(host = 'localhost',
                           user = 'root',
                           passwd = 'H0m3r',
                           db = 'homer')

# Functions
#Convert String to JSON
def convert_String_ToJSON( arduinoData ):
    stringArray = arduinoData.split(',')

    json_file = dict([(k, v) for k,v in zip (stringArray[::2], stringArray[1::2])])
    
    try:
        return json.dumps(json_file, sort_keys=True)
   
    except (ValueError, KeyError, TypeError):
        print ("JSON ERROR")

#Store JSON into Database
def dBJSON_Store(json_file,NodeID):
    cursor = dataBase.cursor()
    cursor.execute("Insert into Sensor_Log(Date,NodeID,Data) values(NOW(),%s,%s)",(NodeID,json_file))
    dataBase.commit()
    message = "Node "+str(NodeID)+" sensor data was stored."
    log_Event("System",message)

#Send Request to Arduino for Sensor information
def arduino_Data_Request(NodeIP,NodeID):
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
            #Create Error Event
            message = "Failed to retrieve Node "+str(NodeID)+" data."
            log_Event("Error",message)
    return received;

#Fetch an Associative Array from MySQL database
def mysql_fetch_assoc():
	out = []  
	try:
		cursor = dataBase.cursor()
		cursor.execute("Select NodeID,IP from Nodes")
		rows = cursor.fetchall()    
		for row in rows:        
			data ={}
			for i in range(len(row)):          
			    if row[i] != None:                        
				    tmp = cursor.description            
				    data[tmp[i][0]] = row[i]
                out.append(data)     
	except Exception as err:
		print("Error in fetchassoc:")
		print(err)
	finally:
	    return out	

#Checks to see if the last data entry matches if so, do not store in Database
def check_duplicate_data(NodeID,json_file):

    try:
        cursor = dataBase.cursor()
        cursor.execute("Select count(*) from Sensor_Log")
        count =  cursor.fetchone()[0]
        if count == 0:
            return False
        else:
            cursor.execute("Select Data from Sensor_Log where NodeID = %s ORDER BY Date DESC LIMIT 1",(NodeID))
            previous_data = ''.join(cursor.fetchone())
            if previous_data == json_file:
                return True
            else:
                return False
    except Exception as err:
        print("Error checking duplicate data")
        print(err)

#Creates a new Event based on type/message		
def log_Event(type,message):
    cursor = dataBase.cursor()
    cursor.execute("Insert into Event_Log(Date,Type,Message) values(NOW(),%s,%s)",(type,message))
    dataBase.commit()

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
  
#Send Arduino a command
def arduino_Send_Command(NodeIP,data,NodeID):
	HOST, PORT = NodeIP, 8888
	# SOCK_DGRAM is the socket type to use for UDP sockets
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	
	# As you can see, there is no connect() call; UDP has no connections.
	# Instead, data is directly sent to the recipient via sendto().
	sock.sendto("send," + data + "\n", (HOST, PORT))
	
	#Log Event Command to arduino
	message = "Sent " + data + " to Node " + str(NodeID) + "."
	log_Event("System",message)

data = "1,111"	


    
#Runs Forever

for node in mysql_fetch_assoc():
	#Testing
	arduino_Send_Command(node['IP'],data,node['NodeID'])
	#Working
	arduinoData = arduino_Data_Request(node['IP'],node['NodeID'])
	json_file = convert_String_ToJSON(arduinoData)
	if check_duplicate_data(node['NodeID'],json_file) == False:
		dBJSON_Store(json_file,node['NodeID']);
	time.sleep(1)
  
