import serial,time
import csv
ser = serial.Serial('/dev/ttyACM0',9600)
outfile=open('user.csv',"a")
writer=csv.writer(outfile,dialect="excel")
while True:
        print "Please Enter your Id :"
        id=raw_input()
        ser.write(id)
        print "Please Enter your name :"
        name=raw_input()
        while True:
                res=ser.readline()
                print res
                if res[0:7]=='Stored!':
                        writer.writerow([id, name, 500])
                        break
outfile.close()
