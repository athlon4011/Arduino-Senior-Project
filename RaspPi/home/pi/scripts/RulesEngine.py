import json
from dBComm import get_Rules
import time

#Checking Node data against Rules
def check_vs_Rules(nodedict):
	data,title = get_Rules()
	for rule in data:
		ifcondition = ""
		str_rule = rule[0]
		json_data = json.loads(str_rule)
		condition = json_data['if']
		conditions = condition['condition']
		#check to see if the Rule needs to run once or more than once
		if 'nodeall' in str_rule and not 'nodeany' in str_rule or  'nodeexact' in str_rule:
			ifcondition = ifcondition_Creation("",conditions,nodedict,None)
			print('Once')
			print(ifcondition)
			print(eval(ifcondition))
		else:
			for node in nodedict:
				ifcondition = ifcondition_Creation("",conditions,nodedict,node)
				print('Many')
				print(ifcondition)
				print(eval(ifcondition))

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
					ifcondition = ifcondition + " " + str(30)	
				if rightvar == 'restricted_time_end':
					ifcondition = ifcondition + " " + str(5)
				if rightvar == 'desired_temp':
					ifcondition = ifcondition + " " + str(15)
			if joiner != 'na':
				ifcondition = ifcondition + " " + joiner
	return ifcondition