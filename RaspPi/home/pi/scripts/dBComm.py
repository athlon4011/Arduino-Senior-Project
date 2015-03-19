import MySQLdb

#DataBase Connection
dataBase = MySQLdb.connect(host = 'localhost',
                           user = 'root',
                           passwd = 'H0m3r',
                           db = 'homer'		)				   

						   
#Store JSON into Database
def dBJSON_Store(json_file,NodeID):
    cursor = dataBase.cursor()
    cursor.execute("Insert into Sensor_Log(Date,NodeID,Data) values(NOW(),%s,%s)",(NodeID,json_file))
    dataBase.commit()
    message = "Node "+str(NodeID)+" sensor data was stored."
    log_Event("System",message)

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

#Creates a new Event based on type/message		
def log_Event(type,message):
    cursor = dataBase.cursor()
    cursor.execute("Insert into Event_Log(Date,Type,Message) values(NOW(),%s,%s)",(type,message))
    dataBase.commit()
  
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