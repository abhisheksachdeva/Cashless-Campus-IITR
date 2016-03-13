# -*- coding: utf-8 -*-
## Fingerprint
import serial,time
import csv
ser = serial.Serial('/dev/ttyACM0',9600)
a= int(raw_input())
if a==1:
	fingerprint()
if a==2:
	enroll()



#################################################################
def fingerprint():
	ser.write("1")
	##writer=csv.writer(outfile,delimiter='\t')
	while True:
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
		                print lines
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
		print "end"

################################################################
def enroll():
	ser.write("2")
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

#################################################################
