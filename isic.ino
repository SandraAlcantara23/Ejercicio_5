// Pines de botones
const int pinEncendido = A1;
const int pinApagado = A2;

// LED mapping (24 LEDs en matriz 6x4)
const int leds[] = {26, 51, 22, 40, 34, 45, 43, 33, 36, 24, 30, 44, 42, 28, 32, 38, 31, 47, 46, 48, 50, 52, 37, 35};
const int numLeds = 24;

// Letras definidas como animación paso a paso
const byte letraI[] = {1, 7, 13, 19};               // columna central
const byte letraS[] = {1, 2, 3, 7, 13, 17, 21, 22, 23}; // forma de S
const byte letraC[] = {2, 3, 4, 10, 16, 22, 21, 20};    // forma de C

const byte* letras[] = {letraI, letraS, letraI, letraC};
const int tamLetras[] = {4, 9, 4, 8};
const int numLetras = 4;

// Estado del sistema
bool encendido = false;
bool mostrandoLetra = false;

// Control de letra actual y animación
int letraActual = 0;
int pasoAnimacion = 0;
unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 300;

void setup() {
  pinMode(pinEncendido, INPUT_PULLUP);
  pinMode(pinApagado, INPUT_PULLUP);

  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void loop() {
  verificarBotones();

  if (encendido) {
    mostrarAnimacionLetra();
  }
}

void verificarBotones() {
  static bool anteriorEncendido = HIGH;
  static bool anteriorApagado = HIGH;

  bool actualEncendido = digitalRead(pinEncendido);
  bool actualApagado = digitalRead(pinApagado);

  if (anteriorEncendido == HIGH && actualEncendido == LOW) {
    encendido = true;
    letraActual = 0;
    pasoAnimacion = 0;
    mostrandoLetra = true;
    apagarLeds();
    tiempoAnterior = millis();
  }

  if (anteriorApagado == HIGH && actualApagado == LOW) {
    encendido = false;
    mostrandoLetra = false;
    apagarLeds();
  }

  anteriorEncendido = actualEncendido;
  anteriorApagado = actualApagado;
}

void mostrarAnimacionLetra() {
  if (!mostrandoLetra || letraActual >= numLetras) return;

  unsigned long ahora = millis();
  if (ahora - tiempoAnterior >= intervalo) {
    const byte* letra = letras[letraActual];
    int tam = tamLetras[letraActual];

    if (pasoAnimacion < tam) {
      digitalWrite(leds[letra[pasoAnimacion]], HIGH);
      pasoAnimacion++;
    } else {
      delay(1000);  // Espera entre letras
      apagarLeds();
      letraActual++;
      pasoAnimacion = 0;
      if (letraActual >= numLetras) {
        letraActual = 0; // reinicia el ciclo
      }
    }
    tiempoAnterior = ahora;
  }
}

void apagarLeds() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], LOW);
  }
}
