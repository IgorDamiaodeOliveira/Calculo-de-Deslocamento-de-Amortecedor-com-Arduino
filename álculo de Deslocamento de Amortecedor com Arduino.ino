#include <math.h> // Para funções matemáticas

// Variáveis de medição
int valor = 0;
float angle = 0.0;
const int max_analog = 1023;
const int max_angle = 180;

// Variáveis geométricas
float length_shockabs = 0.0;
float length_base = 0.0;
float vertical_distance = 0.0;
float displacement_shockabs = 0.0;

// Controle de fluxo
bool inputs_received = false;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Espera a porta serial conectar
  }
  
  Serial.println(F("Sistema de cálculo de deslocamento do amortecedor"));
  requestUserInputs();
}

void loop() {
  if (!inputs_received) {
    checkSerialInput();
  } else {
    valor = analogRead(A0);
    angle = (float)valor * max_angle / max_analog;
    
    float rad_angle = angle * PI / 180.0;
    float new_angle = (PI/2.0) - rad_angle;
    float cos_new_angle = cos(new_angle);
    
    // Lei dos cossenos
    float term1 = pow(length_base, 2);
    float term2 = pow(vertical_distance, 2);
    float term3 = 2.0 * length_base * vertical_distance * cos_new_angle;
    float new_length = sqrt(term1 + term2 - term3);
    
    displacement_shockabs = length_shockabs - new_length;
    
    Serial.print(F("Ângulo: "));
    Serial.print(angle, 1);
    Serial.print(F("° | Deslocamento: "));
    Serial.print(displacement_shockabs, 2);
    Serial.print(F(" | Comprimento atual: "));
    Serial.println(new_length, 2);
    
    delay(100);
  }
}

void requestUserInputs() {
  Serial.println(F("Insira os parâmetros (um por linha):"));
  Serial.println(F("1. Comprimento inicial do amortecedor:"));
}

void checkSerialInput() {
  static byte input_step = 0;
  
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    
    if (input.length() > 0) {
      switch(input_step) {
        case 0:
          length_shockabs = input.toFloat();
          Serial.print(F("Amortecedor: "));
          Serial.println(length_shockabs, 2);
          Serial.println(F("2. Distância da base:"));
          input_step++;
          break;
          
        case 1:
          length_base = input.toFloat();
          Serial.print(F("Base: "));
          Serial.println(length_base, 2);
          Serial.println(F("3. Distância vertical:"));
          input_step++;
          break;
          
        case 2:
          vertical_distance = input.toFloat();
          Serial.print(F("Vertical: "));
          Serial.println(vertical_distance, 2);
          Serial.println(F("Iniciando cálculos..."));
          inputs_received = true;
          break;
      }
    }
  }
}