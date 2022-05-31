#include <SPI.h>                          //SPI kütüphanemizi tanımlıyoruz.
#include <MFRC522.h>                      //MFRC522 kütüphanemizi tanımlıyoruz.
#define kled 11                        
#define yled 3
MFRC522 rfid(10,9);           

byte istanbulkart[4] = {0, 0, 0, 0};          //Yetkili kart Kimlik tanımlıyoruz.
byte kart[4] = {0, 0, 0, 0};          //Yetkili anahtarlık tanımlıyoruz. 

void setup() 
{
  Serial.begin(9600);                    
  SPI.begin();                           
  rfid.PCD_Init();                        
}
 

void loop() 
{
        digitalWrite(yled,0);
        digitalWrite(kled,0);
  if ( ! rfid.PICC_IsNewCardPresent())    
    return;
  if ( ! rfid.PICC_ReadCardSerial())     
    return;

  if (rfid.uid.uidByte[0] == kart[0] &&     

    rfid.uid.uidByte[1] == kart[1] &&
    rfid.uid.uidByte[2] == kart[2] &&
    rfid.uid.uidByte[3] == kart[3] ) {
        Serial.println("Erişim Sağlandı! Kapı Başarıyla açıldı.");
        ekranaYazdir();
        digitalWrite(yled,1);
        digitalWrite(kled,0);
        delay(3000);
    }

   else  if (rfid.uid.uidByte[0] == istanbulkart[0] &&     

    rfid.uid.uidByte[1] == istanbulkart[1] &&
    rfid.uid.uidByte[2] == istanbulkart[2] &&
    rfid.uid.uidByte[3] == istanbulkart[3] ) {
      Serial.println("Erişim Sağlandı! İSTANBUL KART");
        ekranaYazdir();
        digitalWrite(yled,1);
        digitalWrite(kled,0);
        delay(3000);
    }else{                                
      Serial.println("Erişim Sağlanamadı!");
      ekranaYazdir();
        digitalWrite(kled,1);
        digitalWrite(yled,1);
        delay(3000);
    }
  rfid.PICC_HaltA();
}

void ekranaYazdir(){
  Serial.print("Kart Numarasi: ");
  for(int sayac = 0; sayac < 4; sayac++){
    Serial.print(rfid.uid.uidByte[sayac]);  
  }
  Serial.println("");
}
