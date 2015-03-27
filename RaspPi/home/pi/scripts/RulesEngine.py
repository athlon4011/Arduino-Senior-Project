import json
from dBComm import get_Rules

#Checking Node data against Rules
def check_vs_Rules():
    data,title = get_Rules()
    ifcondition = ''
    for rule in data:
        rule = json.loads(rule)
        print(rule)
    
