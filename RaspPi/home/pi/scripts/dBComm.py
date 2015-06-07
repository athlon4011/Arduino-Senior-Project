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
			print(out)
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

#Checks Node Database if Node Exists, if Not Store
def store_node_information(NodeIP):
    try:
        cursor = dataBase.cursor()
        cursor.execute("Select count(*) from Nodes where IP = %s;",(NodeIP))
        count = cursor.fetchone()[0]
        if count == 0:
            cursor.execute("Insert into Nodes(IP) values (%s)",(NodeIP))
            dataBase.commit()
        #NODE RESTART LOG??? 
        else:
            print("Already Have that Node")           
    except Exception as err:
        print("Error checking Node Table")
        print(err)

def get_Rules():
    try:
        cursor = dataBase.cursor()
        cursor.execute("Select Data from Rules where enabled = 1")
        data = cursor.fetchall()
        cursor.execute("Select Title from Rules where enabled = 1")
        title = cursor.fetchall()
        return data,title
    except Exception as err:
        print("Error checking Node Table")
        print(err)

def update_Control_Surface(nodeid,ctrtype,ctrstate):
	try:
		cursor = dataBase.cursor()
		cursor.execute("Update ctrl_surf inner join Nodes Set State = %s where (Select Nodes.Loc from Nodes where NodeID = %s) = ctrl_surf.Loc and ctrl_surf.Type = %s",(ctrstate,nodeid,ctrtype))
	except Exception as err:
		print("Error updating control surfaces")
		print(err)
		
def get_Color_Codes(ledcolor):
	try:
		cursor = dataBase.cursor()
		cursor.execute('Select red,green,blue from Colors where name = %s',(ledcolor))
		colors = cursor.fetchone()
		colorsArray = []
		for idx,color in enumerate(colors):
			color = str(color)
			while len(color) < 3:
				color = '0' + color
			colorsArray.append(color)

		return colorsArray[0],colorsArray[1],colorsArray[2]
	except Exception as err:
		print("Error getting color codes data")
		print(err)