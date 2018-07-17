#include "HX711.h"//Librería celda de carga
#include <Keypad.h>//Librería botones 4x4
#define Y_DIR_PIN 61 // poner número del pin de dirección
#define Y_STEP_PIN 60 // poner número de pin de conexión al motor
#define Y_ENABLE_PIN 56 // poner número de pin de poner en marcha 
#define FIN_CARRERA_1 14 // poner número de pin de final de carrera 1
#define FIN_CARRERA_2 15 // poner número de pin de final de carrera 2
#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define DOUT  3
#define CLK  2
int stepDelay = 30;
int stepDelay1 = 70;// tiempo de parada para controlar la velocidad
long avancepasos = 0;
long restapasos=0;
float distancia = 0;
float fuerza;
long pasosdescarga;
int final_carrera_1 = 1;
int final_carrera_2 = 1; //Final de carrera para finalizar proceso
const byte rowsCount = 4;
const byte columsCount = 4;
char keyantigua = '0';
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '#','0','*', 'D' }
}; 
const byte rowPins[rowsCount] = { 16, 17, 23, 25 };
const byte columnPins[columsCount] = { 27, 29, 31, 4 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
HX711 balanza(DOUT, CLK);
const int pinJoyButton = 13;
const int pinJoyX = A3;
void setup() 
{
  Serial.begin(9600);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  digitalWrite(Y_ENABLE_PIN, LOW);
  pinMode(FIN_CARRERA_1, INPUT_PULLUP);
  pinMode(FIN_CARRERA_2, INPUT_PULLUP);
   pinMode(pinJoyButton , INPUT_PULLUP);   //activar resistencia pull up 
  Serial.println("Iniciando ensayo de telas");

  Serial.print("Seleccione una opción:");
  Serial.print(" 1-->  Ensayo de tracción");
  Serial.print(" 2-->  Ensayo de bucle de pera");
}


void loop() 
{
   int Xvalue = 0;
   bool buttonValue = false;
  char key = keypad.getKey();
   if(key == '1') 
    {
      Serial.println("  Iniciando ensayo de tracción");
      digitalWrite(Y_STEP_PIN, LOW);
    posicion_1();
   }
   if (key == '2')
   {
     Serial.println("  Iniciendo ensayo de bucle de pera");
    digitalWrite(Y_STEP_PIN, LOW);
  posicion_2();
   }
    if (key == '#')
   {
     Serial.println("  Iniciendo ensayo descarga");
    digitalWrite(Y_STEP_PIN, LOW);
  posicion_3();
   }
if(key == '4' )
    {
      Serial.println(key);
     for (int i = 0; i<3200; i++)
    {
    digitalWrite(Y_DIR_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay1);
    digitalWrite(Y_STEP_PIN, HIGH); 
    delayMicroseconds(stepDelay1);
    }
    char key = 'X';
    Serial.println(key);
    delay(1000);
    }
if(key == '5' )
    {
      Serial.println(key);
     for (int i = 0; i<3200; i++)
    {
    digitalWrite(Y_DIR_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay);
    digitalWrite(Y_STEP_PIN, HIGH); 
    delayMicroseconds(stepDelay);
    }
   char key = 'X';
    Serial.println(key);
    delay(1000);
    }
    if(key == '7' )
    {
      Serial.println(key);
     for (int i = 0; i<12800; i++)
    {
    digitalWrite(Y_DIR_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay1);
    digitalWrite(Y_STEP_PIN, HIGH); 
    delayMicroseconds(stepDelay1);
    }
    char key = 'X';
    Serial.println(key);
    delay(1000);
    }
        if(key == '8' )
    {
      Serial.println(key);
     for (int i = 0; i<12800; i++)
    {
    digitalWrite(Y_DIR_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay);
    digitalWrite(Y_STEP_PIN, HIGH); 
    delayMicroseconds(stepDelay);
    }
    char key = 'X';
    Serial.println(key);
    delay(1000);
    }

  Xvalue = analogRead(pinJoyX);  
  //delay(100);
  
  while (Xvalue <= 505)
  {
      //Serial.println(Xvalue);
          digitalWrite(Y_DIR_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay1);
    digitalWrite(Y_STEP_PIN, HIGH); 
    delayMicroseconds(stepDelay1);
      Xvalue = analogRead(pinJoyX);
  }
    while (Xvalue >= 520)
  {
      //Serial.println(Xvalue);
     digitalWrite(Y_DIR_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay);
    digitalWrite(Y_STEP_PIN, HIGH); 
    delayMicroseconds(stepDelay);
      Xvalue = analogRead(pinJoyX);
 
  }

}


//-----------------------------------------------------------

void posicion_1()
{ 
 final_carrera_1 = digitalRead(FIN_CARRERA_1);
  while (final_carrera_1 == 1) 
  {
    digitalWrite(Y_DIR_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay);
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(stepDelay);
    final_carrera_1 = digitalRead(FIN_CARRERA_1);
  }

  delay(2000);
     for (long i = 0; i<140800; i++)
    {
    digitalWrite(Y_DIR_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay1);
    digitalWrite(Y_STEP_PIN, HIGH); 
    delayMicroseconds(stepDelay1);
    avancepasos++;
    }
    
    delay(3000);
    Serial.println("AVANCE PASOS:");
    Serial.print(avancepasos);
    
          Serial.println("Lectura del valor del ADC:  ");
         Serial.println(balanza.read());
         Serial.println("No ponga ningun  objeto sobre la balanza");
         Serial.println("Destarando...");
         Serial.println("...");
         balanza.set_scale(246000); // Establecemos la escala 1kg
         balanza.tare(20);  //El peso actual es considerado Tara.
         Serial.println("Listo para pesar");
         //Serial.println("CLEARDATA");
         Serial.println("LABEL,HORA,TIEMPO DE INICIO,FUERZA(kg),PASOS");
         Serial.println("RESETTIMER");
         fuerza = balanza.get_units(20),3;
         Serial.print("DATA,TIME,TIMER,");
         Serial.print(fuerza);Serial.print(",");
         Serial.println(avancepasos);

    for (int j = 0; j<35; j++)
    {
    for (long i = 0; i<1600; i++)
    {
    avancepasos++;  
    digitalWrite(Y_DIR_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay1);
    digitalWrite(Y_STEP_PIN, HIGH); 
    delayMicroseconds(stepDelay1);
    final_carrera_2 = digitalRead(FIN_CARRERA_2);
    }
    final_carrera_2 = digitalRead(FIN_CARRERA_2);
      delay(2000); 
           fuerza = balanza.get_units(20),3;
      Serial.print("DATA,TIME,TIMER,");
       Serial.print(fuerza);Serial.print(",");
        Serial.println(avancepasos);
    final_carrera_2 = digitalRead(FIN_CARRERA_2);
  }
  Serial.print("        FNAL      ");
}

//-----------------------------------------------------------

void posicion_2()
{ 
 final_carrera_1 = digitalRead(FIN_CARRERA_1);
  while (final_carrera_1 == 1) 
  {
    digitalWrite(Y_DIR_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay);
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(stepDelay);
    final_carrera_1 = digitalRead(FIN_CARRERA_1);
  }

  delay(2000);
  
  Serial.println("Lectura del valor del ADC:  ");
  Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  Serial.println("...");
  balanza.set_scale(246000); // Establecemos la escala 1kg
  balanza.tare(20);  //El peso actual es considerado Tara.
  Serial.println("Listo para pesar");
     for (long i = 0; i<153600; i++)
    {
    digitalWrite(Y_DIR_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay1);
    digitalWrite(Y_STEP_PIN, HIGH); 
    delayMicroseconds(stepDelay1);
    avancepasos++;
    }
delay(2000);
final_carrera_1 = digitalRead(FIN_CARRERA_1);


  while (final_carrera_1 == 1)
  {
    
    digitalWrite(Y_DIR_PIN, HIGH);
    
    for (int i = 0; i<3200; i++)
    {
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay1);
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(stepDelay1);
    final_carrera_1 = digitalRead(FIN_CARRERA_1);
    }
      final_carrera_1 = digitalRead(FIN_CARRERA_1);
       
      delay(800); 
      
      final_carrera_1 = digitalRead(FIN_CARRERA_1);
  }
  Serial.print("        FNAL       ");
    } 

//-----------------------------------------------------------

void posicion_3()
{ 
 final_carrera_1 = digitalRead(FIN_CARRERA_1);
  while (final_carrera_1 == 1) 
  {
    digitalWrite(Y_DIR_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay);
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(stepDelay);
    final_carrera_1 = digitalRead(FIN_CARRERA_1);
  }

  delay(2000);

     for (long i = 0; i<140800; i++)
    {
    digitalWrite(Y_DIR_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay1);
    digitalWrite(Y_STEP_PIN, HIGH); 
    delayMicroseconds(stepDelay1);
    avancepasos++;
    }
    delay(1000);
    //Serial.println("CLEARDATA");
  Serial.println("Lectura del valor del ADC:  ");
  Serial.println(balanza.read());
  Serial.println("No ponga ningun  objeto sobre la balanza");
  Serial.println("Destarando...");
  Serial.println("...");
  balanza.set_scale(246000); // Establecemos la escala 1kg
  balanza.tare(20);  //El peso actual es considerado Tara.
  Serial.println("Listo para pesar");
Serial.println("LABEL,HORA,TIEMPO DE INICIO,FUERZA(kg),PASOS");
Serial.println("RESETTIMER");
    
         for (long i = 0; i<73600; i++)
    {
    digitalWrite(Y_DIR_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay1);
    digitalWrite(Y_STEP_PIN, HIGH); 
    delayMicroseconds(stepDelay1);
    avancepasos++;
    }
    Serial.println("AVANCE PASOS:");
    Serial.print(avancepasos);

      Serial.print("DATA,TIME,TIMER,");
       Serial.print(fuerza);Serial.print(",");
       pasosdescarga= avancepasos-restapasos;
        Serial.println(pasosdescarga);
delay(2000);
final_carrera_1 = digitalRead(FIN_CARRERA_1);
         for (long i = 0; i<35; i++)
    {
      
        for (long j = 0; j<1600; j++)
    {
    digitalWrite(Y_DIR_PIN, HIGH);

    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(stepDelay1);
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(stepDelay1);
    final_carrera_1 = digitalRead(FIN_CARRERA_1);
    restapasos++;
    }
               fuerza = balanza.get_units(20),3;
      Serial.print("DATA,TIME,TIMER,");
       Serial.print(fuerza);Serial.print(",");
       pasosdescarga= avancepasos-restapasos;
        Serial.println(pasosdescarga);
      final_carrera_1 = digitalRead(FIN_CARRERA_1);

  }
  Serial.print("        FNAL       ");
    } 
