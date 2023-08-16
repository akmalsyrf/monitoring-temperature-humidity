#include <DHT.h>
// #include  <Wire.h>
#include  <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C adalah kelas
// mylcd adalah objek
LiquidCrystal_I2C mylcd(0x27, 16,2);  // Ganti 0x3F or 0x27 dengan address I2C anda

#define DHTPIN 5
#define DHTTYPE DHT22

const int KIPAS = 8;
const int POMPA = 9;

DHT dht(DHTPIN, DHTTYPE);

float hum;
float temp;



void setup()
{
  Serial.begin(9600);

  pinMode(POMPA, OUTPUT);
  pinMode(KIPAS, OUTPUT);
  dht.begin();
  mylcd.init();      //Initialisasi LCD 
  mylcd.backlight();  // Mengaktifkan backligh LCD
  delay(250);
  mylcd.noBacklight(); // Menonaktifkan backligh LCD
  delay(250);
  mylcd.backlight();
 
  mylcd.setCursor(0,0); // Navigasi LCD pada baris 0 dan character ke 0
  mylcd.print("Edspert.id");
  mylcd.setCursor(0,1);
  mylcd.print("Bootcamp Ke-4");
  delay(3000);
 mylcd.clear(); 
}

void loop()
{
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  // Silahkan tambahkan komponen LDR dan baca parameter LUXnya


  if (temp > 25 && hum < 80){
    digitalWrite(KIPAS, HIGH); // Kipas Menyala
    digitalWrite(POMPA, HIGH); // Pompa Menyala
    lcdMon("ON ", "ON ");
  }
  else if(temp > 25 && hum>= 80 ){
    digitalWrite(KIPAS, HIGH); // Kipas Menyala
    lcdMon("OFF", "ON ");
  }
  else if(temp <= 25 && hum < 80){
    digitalWrite(POMPA, HIGH); // Pompa Menyala
    lcdMon("ON ", "OFF");
  }
  else{
    digitalWrite(KIPAS, LOW); // Kipas Menyala
    digitalWrite(POMPA, LOW); // Pompa Menyala
    lcdMon("OFF", "OFF");
  }
  displayMon();

  delay(500);
}

void displayMon(){
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("\t Temperaure: ");
  Serial.println(temp);
}

void lcdMon(String POM, String FAN){
    mylcd.setCursor(0,0);
    mylcd.print("H:");
    mylcd.print(hum,1);
    mylcd.print("%");
    mylcd.setCursor(9,0);
    mylcd.print("POM:"); 
    mylcd.print(POM);

    mylcd.setCursor(0,1);
    mylcd.print("T:");
    mylcd.print(temp,1);
    mylcd.print((char)223);// prints degree symbol
    mylcd.println("C");
    mylcd.setCursor(9,1);
    mylcd.print("FAN:"); 
    mylcd.print(FAN);
}
