// připojení knihovny DHT
#include "DHT.h"
// nastavení čísla pinu s připojeným DHT senzorem
#define pinDHT 5

// odkomentování správného typu čidla
#define typDHT11 DHT11     // DHT 11
//#define typDHT22 DHT22   // DHT 22 (AM2302)

// inicializace DHT senzoru s nastaveným pinem a typem senzoru
DHT mojeDHT(pinDHT, typDHT11);

int pinR = 9;
int pinG = 11;
int pinB = 10;

void setup() {
  // komunikace přes sériovou linku rychlostí 9600 baud
  Serial.begin(9600); 
  // zapnutí komunikace s teploměrem DHT
  mojeDHT.begin();

  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
}

void loop() {
  // pomocí funkcí readTemperature a readHumidity načteme
  // do proměnných tep a vlh informace o teplotě a vlhkosti,
  // čtení trvá cca 250 ms
  float tep = mojeDHT.readTemperature();
  float vlh = mojeDHT.readHumidity();
  // kontrola, jestli jsou načtené hodnoty čísla pomocí funkce isnan
  if (isnan(tep) || isnan(vlh)) {
    // při chybném čtení vypiš hlášku
    Serial.println("Chyba při čtení z DHT senzoru!");
  } else {
    // pokud jsou hodnoty v pořádku,
    // vypiš je po sériové lince

    if(tep<20){ // Je příliš chladno, svítí modrá
      
      analogWrite(pinR, 0);
      analogWrite(pinG, 0);
      analogWrite(pinB, 255);
  
      // Také můžeme zapnout například topení / přímotop
      
    }else if(tep >= 20 && tep < 25){ // teplota je optimalní, svítí zelená
         
      analogWrite(pinR, 0);
      analogWrite(pinG, 255);
      analogWrite(pinB, 0);
    
    }else if(tep >= 25){ // je příliš horko, svítí červená
         
      analogWrite(pinR, 255);
      analogWrite(pinG, 0);
      analogWrite(pinB, 0);
  
      // Také můžeme zapnout například klimatizaci / ventilátor
    
    }
    
    Serial.print("Teplota: "); 
    Serial.print(tep);
    Serial.print(" stupnu Celsia, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlh);
    Serial.println("  %");
  }
  // pauza pro přehlednější výpis
  delay(2000);
}
