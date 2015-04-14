import json
import dBComm
import time
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
			if eval(ifcondition) == True:
				resultcondition_Creation(results,nodedict,None)
		else:
			for node in nodedict:
				ifcondition = ifcondition_Creation("",conditions,nodedict,node)
				print(eval(ifcondition))
				if eval(ifcondition) == True:
					resultcondition_Creation(results,nodedict,node)

#Creation of ifcondition	
def ifcondition_Creation(ifcondition,conditions, nodedict, node):
	for idx, each in enumerate(conditions):				
			modifier = conditions[idx]['modifier']
			leftype = conditions[idx]['leftype']
			leftvar = conditions[idx]['leftvar']
			operand = conditions[idx]['operand']
			rightype = conditions[idx]['rightype']
			rightvar = conditions[idx]['rightvar']
			joiner = conditions[idx]['joiner']
			#LEFT SIDE OF OPERAND
			#NODE ALL TYPE
			if leftype == 'nodeall':
				if leftvar == 'temp':
					if modifier == 'avg':
						sum = 0.0
						for node in nodedict:
							sum += float(node.temp)							
						ifcondition = ifcondition + " " + str(sum/(len(nodedict)*1.0))  + " " + operand
					elif modifier == 'sum':
						sum = 0.0
						for node in nodedict:
							sum += float(node.temp)
						ifcondition = ifcondition + " " + str(sum) + " " + operand
					# elif modifier == 'max':
						# #Get MAX
						# continue
					# elif modifier == 'min':
						# #Get MIN
						# continue
					# else modifier == 'na':
						# #Not sure if this will ever happen with a nodeall
						# continue
				if leftvar == 'lux':
					if modifier == 'avg':
						sum = 0.0
						for node in nodedict:
							sum += float(node.lux)							
						ifcondition = ifcondition + " " + str(sum/(len(nodedict)*1.0))  + " " + operand
					elif modifier == 'sum':
						sum = 0.0
						for node in nodedict:
							sum += float(node.lux)
						ifcondition = ifcondition + " " +  str(sum) + " " + operand
					# elif modifier == 'max':
						# #Get MAX
						# continue
					# elif modifier == 'min':
						# #Get MIN
						# continue
					# else modifier == 'na':
						# #Not sure if this will ever happen with a nodeall
						# continue
				if leftvar == 'motion':
					if modifier == 'avg':
						sum = 0.0
						for node in nodedict:
							sum += float(node.motion)							
						ifcondition = ifcondition + " " + str(sum/(len(nodedict)*1.0))  + " " + operand
					elif modifier == 'sum':
						sum = 0.0
						for node in nodedict:
							sum += float(node.motion)
						ifcondition = ifcondition + " " + str(sum) + " " + operand
					# elif modifier == 'max':
						# #Get MAX
						# continue
					# elif modifier == 'min':
						# #Get MIN
						# continue
					# else modifier == 'na':
						# #Not sure if this will ever happen with a nodeall
						# continue
			#NODE ANY TYPE
			elif leftype == 'nodeany':
				if leftvar == 'motion':
					ifcondition =  ifcondition + " "  + node.motion + " " + operand
				if leftvar == 'lux':
					ifcondition =  ifcondition + " " + node.lux+ " " + operand
				if leftvar == 'temp':
					ifcondition = ifcondition + " " + node.temp + " " + operand
			#SERVER TYPE
			if leftype == 'server':
				if leftvar == 'current_time':
					current_time = int(time.time())
					ifcondition =  ifcondition + " " + str(current_time) + " " + operand
			#RIGHT SIDE OF OPERAND
			if rightype == 'numbervalue':
					ifcondition = ifcondition + " "  + rightvar
			if rightype == 'system':
				if rightvar == 'restricted_time_start':
					ifcondition = ifcondition + " " + str(300000)	
				if rightvar == 'restricted_time_end':
					ifcondition = ifcondition + " " + str(5)
				if rightvar == 'desired_temp':
					ifcondition = ifcondition + " " + str(15)
			if joiner != 'na':
				ifcondition = ifcondition + " " + joiner
	return ifcondition

#Retrieving and executing all results
def resultcondition_Creation(results,nodedict,node):
	for idx, each in enumerate(results):				
			sound = results[idx]['sound']
			lednodetype = results[idx]['lednodetype']
			ledcolor = results[idx]['ledcolor']
			ctrnodeloc = results[idx]['ctrnodeloc']
			ctrtype = results[idx]['ctrtype']
			ctrstate = results[idx]['ctrstate']
			log = results[idx]['log']

			if ctrnodeloc == 'same':
				#Update the Control Surfaces State for the given node
				dBComm.update_Control_Surface(node.id,ctrtype,ctrstate)			
			if ctrnodeloc == 'all':
				#Updating all nodes Control Surfaces States
				for node in nodedict:
					#Update the Control Surfaces State for the given node
					dBComm.update_Control_Surface(node.id,ctrtype,ctrstate)		
			
			if sound == 'nodeall' or 'nodeany' or 'nodeexact':
				sound = 1
			else:
				sound = 0
			
			if ledcolor or lednodetype != 'na':
				#(sound,red,green,blue,loops(1-9),delay(1-9))
				red,green,blue = dBComm.get_Color_Codes(ledcolor)
				data = "%s,%s,%s,%s,%s,%s",(sound,red,green,blue,4,3)
			if lednodetype == 'nodeall':
				for node in nodedict: 
					Node_Send_Command(node.ip,data,node.id)
			
				