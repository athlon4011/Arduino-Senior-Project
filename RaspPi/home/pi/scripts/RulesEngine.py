import json
import dBComm
import time
import Functions
from nodeComm import Node_Send_Command


#Checking Node data against Rules
def check_vs_Rules(nodedict):
	data,title = dBComm.get_Rules()
	for rule in data:
		ifcondition = ""
		str_rule = rule[0]
		json_data = json.loads(str_rule)
		condition = json_data['if']
		conditions = condition['condition']
		result = json_data['then']
		results = result['result']
		#check to see if the Rule needs to run once or more than once
		if 'nodeall' in str_rule and not 'nodeany' in str_rule or  'nodeexact' in str_rule:
			ifcondition = ifcondition_Creation("",conditions,nodedict,None)
			print(eval(ifcondition))
			print(ifcondition)
			if eval(ifcondition) == True:
				resultcondition_Creation(results,nodedict,None)
		else:
			for node in nodedict:
				ifcondition = ifcondition_Creation("",conditions,nodedict,node)
				print(eval(ifcondition))
				print(ifcondition)
				if eval(ifcondition) == True:
					resultcondition_Creation(results,nodedict,node)

#Creation of ifcondition	
def ifcondition_Creation(ifcondition,conditions, nodedict, node):
	#Convert type instance to dictionary
	if node != None:
		node = Functions.convert_inst_to_dict(node)
	#check to see if the Rule needs to run once or more than once2
	for idx, each in enumerate(conditions):				
			modifier = conditions[idx]['modifier']
			leftype = conditions[idx]['leftype']
			leftvar = conditions[idx]['leftvar']
			operand = conditions[idx]['operand']
			rightype = conditions[idx]['rightype']
			rightvar = conditions[idx]['rightvar']
			joiner = conditions[idx]['joiner']
			
			if ('group' in conditions[idx]):
				if conditions[idx]['group'] == 'a':
					ifcondition = ifcondition + '('
				
			
			#LEFT SIDE OF OPERAND						
			#NODE ALL TYPE
			if leftype == 'nodeall':
				if modifier == 'avg':
					sum = 0.0
					for anode in nodedict:
						anode = Functions.convert_inst_to_dict(anode)
						sum += float(anode[leftvar])			
					ifcondition = ifcondition + " " + str(sum/(len(nodedict)*1.0))  + " " + operand
				elif modifier == 'sum':
					sum = 0.0
					for anode in nodedict:
						anode = Functions.convert_inst_to_dict(anode)
						sum += float(anode[leftvar])
					ifcondition = ifcondition + " " + str(sum) + " " + operand
			#NODE ANY TYPE
			elif leftype == 'nodeany':
				if('overtime' in conditions[idx]):
					ifcondition = ifcondition + " 0 " + operand
				else:
					ifcondition = ifcondition + " " + node[leftvar] + " " + operand				
			#SERVER TYPE
			elif leftype == 'server':
				if leftvar == 'current_time':
					current_time = int(time.time())
					current_time = time.strftime("%H:%M", time.localtime(current_time))
					current_time = current_time.split(':')
					hours_to_seconds = int(current_time[0]) * 3600
					minutes_to_seconds = int(current_time[1]) * 60
					current_time = hours_to_seconds + minutes_to_seconds
					ifcondition =  ifcondition + " " + str(current_time) + " " + operand
			#RIGHT SIDE OF OPERAND
			if rightype == 'numbervalue':						
				if('overtime' in conditions[idx]):
					current_time = int(time.time())
					settings = Functions.convert_String_toJSON(dBComm.getSettings())
					delay = settings[conditions[idx]['overtime']]		
					newTime = current_time - int(delay)
					delayedDateTime =  time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(newTime))			
					rightvar = dBComm.checkConsistency(node['id'],delayedDateTime,leftvar,rightvar)
				ifcondition = ifcondition + " "  + str(rightvar)
			elif rightype == 'system':
				settings = Functions.convert_String_toJSON(dBComm.getSettings())
				ifcondition = ifcondition + " " + settings[rightvar]			
			if 'group' in conditions[idx]:
				if conditions[idx]['group'] == 'b':
					ifcondition = ifcondition + ')'
			if joiner != 'na':
				ifcondition = ifcondition + " " + joiner
				
				
	return ifcondition

#Retrieving and executing all results
def resultcondition_Creation(results,nodedict,node):
	for idx, each in enumerate(results):		
			dataString = '';
			sound = results[idx]['sound']
			lednodetype = results[idx]['lednodetype']
			ledcolor = results[idx]['ledcolor']
			ctrnodeloc = results[idx]['ctrnodeloc']
			ctrtype = results[idx]['ctrtype']
			ctrstate = results[idx]['ctrstate']
			log = results[idx]['log']
			
			if sound == 'na':
				sound = 0
				dataString = dataString + str(sound)
			else:
				sound = 1
				dataString = dataString + str(sound)
			
			if ledcolor != 'na':
				#(sound,red,green,blue,loops(1-9),delay(1-9))
				red,green,blue = dBComm.get_Color_Codes(ledcolor)
				dataString= dataString +  ',' +  str(red) + ',' + str(green) + ',' + str(blue) + ',' + str(4) + ',' + str(3)
			else:
				red,green,blue = dBComm.get_Color_Codes('black')
				dataString= dataString +  ',' +  str(red) + ',' + str(green) + ',' + str(blue) + ',' + str(0) + ',' + str(0)
			
			if ctrnodeloc != 'na':
				#check for ctrl state being requested matches to dbState dont run this code
				if dBComm.check_Control_Surface_State(node.id,ctrtype,ctrstate) != True:	
					if ctrnodeloc == 'same':	
						#Update the Control Surfaces State for the given node
						dBComm.update_Control_Surface(node.id,ctrtype,ctrstate)
						#Log Event
						log = 'Node ' + str(node.id) +': ' + log
						dBComm.log_Event('Rule',log)	
					elif ctrnodeloc == 'all':
						#Updating all nodes Control Surfaces States
						for Anode in nodedict:
							print (Anode)
							#Update the Control Surfaces State for the given node
							dBComm.update_Control_Surface(Anode.id,ctrtype,ctrstate)
							#Log Event
							log = 'Node ' + str(Anode.id) + ': ' + log
							dBComm.log_Event('Rule',log)
							
					if lednodetype != 'nodeall':
						if lednodetype == 'nodeany':
							Node_Send_Command(node.ip,dataString,node.id)								
					else:
						for Anode in nodedict: 
							Node_Send_Command(Anode.ip,dataString,Anode.id)
			else:
				if ctrtype != 'na':
					if dBComm.check_Control_Surface_State_NA(ctrtype,ctrstate) != True:
						dBComm.update_Control_Surface_HVAC(ctrtype,ctrstate)
						if lednodetype != 'nodeall':
							if lednodetype == 'nodeany':
								Node_Send_Command(node.ip,data,node.id)	
								log = 'Node ' + str(node.id) +': ' + log
								dBComm.log_Event('Rule',log)
							elif lednodetype == 'na':
								dBComm.log_Event('Rule',log)
						else:
							for Anode in nodedict: 
								Node_Send_Command(Anode.ip,dataString,Anode.id)
							dBComm.log_Event('Rule',log)	
				else:
					for Anode in nodedict: 
						Node_Send_Command(Anode.ip,dataString,Anode.id)
					dBComm.log_Event('Rule',log)	
			
				