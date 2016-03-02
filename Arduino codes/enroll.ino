#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include<SPI.h>
#include<SD.h>

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//Initialising variables
uint32_t id;
//String name="";
//File myFile;
void setup()  
{
  while (!Serial); 
  delay(500);
  
  Serial.begin(9600);
  Serial.println("Fingerprint sensor enrollment");
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
   Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  if(!SD.begin(4)){
 //   Serial.println("Initialization of SD Card failed !");
    return;
  }
}

uint32_t readnumber(void) {
  uint32_t c=0;
    while(!Serial.available());
    c = Serial.parseInt();
    return c;
}

void loop()                     // run over and over again
{
  Serial.println("Ready to enroll a fingerprint!");
  id=readnumber();
  Serial.print("Enrolling ID ");
  Serial.println(id);
  while (!getFingerprintEnroll() ){
   Serial.println("Couldn't enroll! Try Again");
    loop();
  }
  Serial.println("\n\n");
}
uint32_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as ID "); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.println("No finger");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
   Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
     Serial.println("Unknown error");
      break;
    }
  }

  // OK success!
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      break;
    default:
     Serial.println("Error !");
      return p;
  }
  
  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      break;
    default:
     //Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      break;
    default:
     Serial.println("Unknowen error");
      return p;
  }
  
  // OK converted!
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else {
   Serial.println("Unknown error");
    return p;
  }


  
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  }  else {
   Serial.println("Unknown error");
    return p;
  }   
}
