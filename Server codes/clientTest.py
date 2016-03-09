import requests
id=3
r= requests.post('http://192.168.0.29:8080/id',data={'q':id})
r2 = requests.post('http://192.168.0.29:8080/user', files={'report': open('user.csv', 'rb')})
r3 = requests.post('http://192.168.0.29:8080/getfile')

print r.text
print r2.text
print r3.text