import MySQLdb
import time

#DataBase Connection
dataBase = MySQLdb.connect(host = 'localhost',
                           user = 'root',
                           passwd = 'H0m3r',
                           db = 'homer'		)		
dataBase.autocommit(True)
						   
						   
#Store JSON into Database
def dBJSON_Store(json_file,NodeID):
    cursor = dataBase.cursor()
    cursor.execute("Insert into Sensor_Log(Date,NodeID,Data) values(NOW(),%s,%s)",(NodeID,json_file))
    message = "Node "+str(NodeID)+" sensor data was stored."
    log_Event("System",message)

#Fetch an Associative Array from MySQL database
def getEnabledNodes():
	out = []  
	try:
		cursor = dataBase.cursor()
		cursor.execute("Select NodeID,IP from Nodes where enabled = 1 and type = 'data'")
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
		return out;

#Get Node Count
def nodeCount():
	try:
		cursor = dataBase.cursor()
		cursor.execute("Select count(*) from Nodes where Nodes.enabled = 1;")
		count = cursor.fetchone()[0]
		cursor.close()
		return count
	except Exception as err:
		print(err)
		print("Error with getting Node Count.")
		

		
#Creates a new Event based on type/message		
def log_Event(type,message):
    cursor = dataBase.cursor()
    cursor.execute("Insert into Event_Log(Date,Type,Message) values(NOW(),%s,%s)",(type,message))

#gets Last Log Event Message
def get_Last_Log_Event():
	try:
		cursor = dataBase.cursor()
		cursor.execute("Select Message from Event_Log ORDER BY Date DESC LIMIT 1")
		previous_data = ''.join(cursor.fetchone())
		return previous_data
	except Exception as err:
		print("Failed to get last Log Event")
		print(err)
#Checks to see if the last data entry matches if so, do not store in Database
def check_duplicate_data(NodeID,json_file):

    try:
		cursor = dataBase.cursor()
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
		return False;
		print("Error checking duplicate data")
		print(err)

#Checks Node Database if Node Exists, if Not Store
def store_node_information(NodeIP,MAC):
    try:
		cursor = dataBase.cursor()
		cursor.execute("Select count(*) from Nodes where MAC= %s;",(MAC))
		count = cursor.fetchone()[0]
		if count == 0:
			cursor.execute("Insert into Nodes(IP,MAC,enabled,type,loc) values (%s, %s, 0, 'data','*New*')",(NodeIP,MAC))
			log_Event('System','New node added to the system.')
		else:
			cursor.execute("Update Nodes set  IP= %s where MAC= %s;",(NodeIP,MAC))
			print("Already Have that Node, Updated IP")        

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

def check_Control_Surface_State(nodeid,ctrtype,ctrstate):
	try:
		cursor = dataBase.cursor()
		cursor.execute("Select count(*) from ctrl_surf inner join Nodes where (Select Nodes.Loc from Nodes where NodeID = %s) = ctrl_surf.Loc and ctrl_surf.Type = %s",(nodeid,ctrtype))
		count = cursor.fetchone()[0]
		if count > 0:
			cursor.execute("Select State from ctrl_surf inner join Nodes where (Select Nodes.Loc from Nodes where NodeID = %s) = ctrl_surf.Loc and ctrl_surf.Type = %s",(nodeid,ctrtype))
			dbState = ''.join(cursor.fetchone())
			if dbState == ctrstate:
				return True
			else:
				return False
		else:
			return True
	except Exception as err:
		print("Error updating control surfaces")
		print(err)

def check_Control_Surface_State_NA(ctrtype,ctrstate):
	try:
		cursor = dataBase.cursor()
		cursor.execute("Select count(*) from ctrl_surf where ctrl_surf.Type = %s",(ctrtype))
		count = cursor.fetchone()[0]
		if count > 0:
			cursor.execute("Select State from ctrl_surf where ctrl_surf.Type = %s",(ctrtype))
			dbState = ''.join(cursor.fetchone())
			if dbState == ctrstate:
				return True
			else:
				return False
		else:
			return True
	except Exception as err:
		print("Error updating control surfaces")
		print(err)
		
def update_Control_Surface_HVAC(ctrtype,ctrstate):
	try:
		cursor = dataBase.cursor()
		cursor.execute("Update ctrl_surf Set State = %s where Type = %s",(ctrstate,ctrtype))
	except Exception as err:
		print("Error updating control surfaces")
		print(err)
		
def get_Color_Codes(ledcolor):
	try:
		cursor = dataBase.cursor()
		cursor.execute('Select red,green,blue from Colors where name = %s',(ledcolor))
		colors = cursor.fetchone()
		if(colors != None):
			colorsArray = []
			for idx,color in enumerate(colors):
				color = str(color)
				while len(color) < 3:
					color = '0' + color
				colorsArray.append(color)
			return colorsArray[0],colorsArray[1],colorsArray[2]
		else:
			return "000","000","000"
	except Exception as err:
		print("Error getting color codes data")
		print(err)
		
def getSettings():
	try:
		cursor = dataBase.cursor()
		cursor.execute('Select Settings from Settings')
		data = cursor.fetchone()
		return data[0]
	except Exception as err:
		print("Error getting Settings from SettingLog")
		print(err)
		
def checkConsistency(nodeID,delay,leftvar,rightvar):
	try:
		cursor = dataBase.cursor()
		cursor.execute("SELECT count(*) FROM homer.Sensor_Log where NodeID=\'" + str(nodeID) + "\' and Date BETWEEN \'" + delay + "\' AND NOW() and Data NOT LIKE \'%\"" + leftvar + "\": \"" + rightvar + "\"%\';")
		data = cursor.fetchone()[0]
		return data
	except Exception as err:
		print("Error checking Consistency")
		print(err)
	
	#Gets enabled Control Surfaces
def get_Control_Surface_Nodes():
	out = []
	try:
		cursor = dataBase.cursor()
		cursor.execute("Select IP,Loc from Nodes where enabled = 1 and type = 'control' ")
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
		print (err)
	finally:
		return out
		
def get_State_of_Control_Surface(Loc):
	out= []
	try:
		cursor = dataBase.cursor()
		cursor.execute("Select State,Type from ctrl_surf where Loc = %s ",(Loc))
		rows = cursor.fetchall()	
		for row in rows:    
			data ={}
			for i in range(len(row)):
				if row[i] != None:
				    tmp = cursor.description            
				    data[tmp[i][0]] = row[i]
			out.append(data)
	except Exception as err:
		print (err)	
	finally:
		return out