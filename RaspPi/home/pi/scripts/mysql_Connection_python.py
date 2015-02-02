
import MySQLdb


db = MySQLdb.connect(host = 'localhost',
                     user = 'root',
                     passwd = 'Rules@123',
                     db = 'test')

curs = db.cursor()
curs.execute("Insert into testRules(Rule,Status) values('This Rule is Updated',TRUE)")

db.commit()

curs.execute("Select * from testRules")

print ("\nID		Rule		Status")
print ("========================================")

for row in curs.fetchall():
    print ("{}		{}		{}".format(row[0],row[1],row[2]))


