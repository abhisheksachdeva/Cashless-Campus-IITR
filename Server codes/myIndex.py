from bottle import route, run, template,response, get, post,request, static_file
import os
import time
import requests
import json
import csv
from urlparse import urlparse,parse_qs
from twilio.rest import TwilioRestClient

##url = '10.42.0.1'
url='172.25.13.239'
account_sid = "AC8d882210cd24e4b2a437d31f35018fa1"
auth_token = "5b65f7d6c7a60c7bc2d3b5ace89e0f29"
@route('/')
def home():
	msg = 'Home'
	return msg


@post('/id')
def sendToCLient():
	no=request.forms.get('q')
	print no
	readFile= open('serverData.csv','rb')
	reader = csv.reader(readFile)
	lines=[l for l in reader]
	name ='Hello'
	for line in lines:
                if int(line[0])==int (no):
                        print "Name is ",line[1]
                        print "Id is ",line[0]
                        print "Your balace is" , line[2]
                        name=  "Name is "+line[1] +"\nId is "+line[0] + "\nYour balance is "+line[2]
                                                  
	readFile.close()
	return name

@post('/user')
def receiveFile():
	userData = request.files.get('report')
	userID= request.forms.get('q')
	print userID
	print userData.filename
	file_path = "serverData.csv"
	if os.path.exists("serverData.csv"):
		os.remove("serverData.csv")
		userData.save(file_path)
	readFile= open('serverData.csv','rb')
	reader = csv.reader(readFile)
	lines=[l for l in reader]
	for line in lines:
                if int(line[0])==int (userID):
                        client = TwilioRestClient(account_sid, auth_token)
			message = client.messages.create(to="++917060334386", from_="+12248032729",
                                     body="\nA/c holder: "+line[1]+"\nTransaction Successful for ID "+line[0]+". Balance is "+line[2])
                                                  
	readFile.close()
	


@post('/getfile')
def getFile():
	file= open('serverData.csv',"rb")
	return file

run(host=url, port=8080, debug=True)



