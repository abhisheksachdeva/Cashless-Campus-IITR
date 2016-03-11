from bottle import route, run, template,response, get, post,request, static_file
import os
import time
import requests
import json
import csv
from urlparse import urlparse,parse_qs

url = '172.25.13.239'

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
	print userData.filename
	file_path = "serverData.csv"
	if os.path.exists("serverData.csv"):
		os.remove("serverData.csv")
		userData.save(file_path)

@post('/getfile')
def getFile():
	file= open('serverData.csv',"rb")
	return file

run(host=url, port=8080, debug=True)



