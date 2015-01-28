import _mysql
import sys

try: 
	db=_mysql.connect(host="localhost",user="root",passwd="hellonice",db="test")
	db.query("SELECT * FROM STATION")
	r=db.use_result()
	print r.fetch_row(0)[0][1]

except _mysql.Error, e:

	print "Error %d %s" % (e.args[0], e.args[1])
	sys.exit(1)

finally:
    
    if db:
        db.close()
