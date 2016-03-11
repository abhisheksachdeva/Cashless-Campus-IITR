# -*- coding: utf-8 -*-
## Fingerprint
import serial,time, socket
import requests
import csv
print "Type 1 to pay or 2 to enroll"
ser = serial.Serial('/dev/ttyACM0',9600)
#################################################################
def fingerprint():
	flag=0
        ser.write("1")
        while True:
	    if flag==1:
	    	break
            outfile=open('user1.csv',"w")
            writer= csv.writer(outfile)
            infile=open('user.csv',"r")
            reader = csv.reader(infile)
            res= ser.readline()
            print res
            id=-1
            if res[0]=='#':
                id=res[1:]
                lines=[l for l in reader]
                for line in lines:
                        if int(line[0])==int(id):
                                print "Name is ",line[1]
                                print "Id is ",line[0]
                                print "Your balance is" , line[2]
                                print "Enter the amount spent"
                                amount=input()
                                line[2]= str(int(line[2])-amount)
                                print "Updated amount is", line[2]
				flag=1
                writer.writerows(lines)
                outfile.close()
                infile2= open('user1.csv',"r")
                reader2=csv.reader(infile2)
                lines2 = [l for l in reader2]
                infile2.close()
                outfile2=open("user.csv","w")
                writer2=csv.writer(outfile2)
                writer2.writerows(lines2)
                outfile2.close()
		sendData()
                print "End :)"

################################################################
def enroll():
	flag=0
	ser.write("2")
	infile=open('user.csv',"r")
       	reader=csv.reader(infile)
        while True:
		if flag==1:
			break
		already=0
		while True:
			if already==1:
				break
			print "Please Enter your Id :"
                	id=raw_input()
			lines=[l for l in reader]
			already=2
               		for line in lines:
				if int(line[0])==int(id):
					already=3
					print "This Id already exists! Please Try Again!"
				else:
					already=1
					break
			if already==2:
				break
		infile.close()
                print "Please Enter your name :"
                name=raw_input()
                while True:
                        res=ser.readline()
			ser.write(id)
                        print res
                        if res[0:7]=='Stored!':
				outfile=open('user.csv',"a")
               			writer=csv.writer(outfile,dialect="excel")
                                writer.writerow([id, name, 500])
				print "End :)"
				flag=1
                                break
	sendData()
        outfile.close()

##################################################################
#Send data to server
def sendData():
    r2 = requests.post('http://172.25.13.239:8080/user', files={'report': open('user.csv', 'rb')})



##################################################################
a= int(raw_input())
if a==2:
        enroll()
elif a==1:
        fingerprint()

