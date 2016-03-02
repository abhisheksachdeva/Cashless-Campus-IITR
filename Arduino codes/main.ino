#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int getFingerprintIDez();

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint32_t id;

void setup()  
{
  while (!Serial);  
  
  Serial.begin(9600);
  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
}

void loop()                     // run over and over again
{
	Serial.println("Type 1 to pay or 2 to enroll");
	uint32_t a=5;
    while(!Serial.available());
	 a = Serial.parseInt();
	switch (a){
	case 1:
  a=5;
	fingerprint();
  break;
	case 2:
  a=5;
	enroll();
  break;
  default:
  a=5;
  fingerprint();
		  }
	}


////////////////////////////////////////////////////////////////

//for fingerprint detection 


void fingerprint(){
	
  Serial.println("Waiting for valid finger...");
  while(getFingerprintID()){
    getFingerprintID();
  }
  delay(50);            //don't ned to run this at full speed.
}

uint32_t getFingerprintID() {
  uint32_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
     //Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("#"); Serial.println(finger.fingerID); 
//   Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint32_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID "); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}


///////////////////////////////////////////////////////////////////////////////


//enroll a new fingerprint

uint32_t readnumber(void) {
  Serial.println("Enter ID");
  uint32_t c=0;
    while(!Serial.available());
    c = Serial.parseInt();
    return c;
}
void enroll(){
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
