// Pines de botones
const int pinEncendido = 3; // D3
const int pinApagado = 4;   // D4

// Pines semáforo vía 1
const int rojo1 = A0;
const int amarillo1 = A4;
const int verde1 = A5;

// Pines semáforo vía 2
const int rojo2 = A1;
const int amarillo2 = A2;
const int verde2 = A3;

// Estado del sistema
bool encendido = false;

// Variables para detección de flancos y debounce
bool estadoAnteriorEncendido = HIGH;
bool estadoAnteriorApagado = HIGH;
unsigned long tiempoUltimoEncendido = 0;
unsigned long tiempoUltimoApagado = 0;
const unsigned long debounceDelay = 50; // 50ms de debounce

// Variables para el ciclo del semáforo
unsigned long tiempoAnterior = 0;
int fase = 0; // 0=verde1, 1=amarillo1, 2=verde2, 3=amarillo2
int contadorParpadeo = 0;
bool estadoParpadeo = false;
unsigned long tiempoParpadeo = 0;

void setup() {
  // Configurar botones con resistencias internas pull-up
  pinMode(pinEncendido, INPUT_PULLUP);
  pinMode(pinApagado, INPUT_PULLUP);

  // Pines de salida
  pinMode(rojo1, OUTPUT);
  pinMode(amarillo1, OUTPUT);
  pinMode(verde1, OUTPUT);
  pinMode(rojo2, OUTPUT);
  pinMode(amarillo2, OUTPUT);
  pinMode(verde2, OUTPUT);

  // Apagar todo al inicio
  apagarSemaforos();
}

void loop() {
  // Verificar botones
  verificarBotones();

  // Si está encendido, ejecutar el ciclo de semáforo
  if (encendido) {
    cicloSemaforoNoBlocking();
  }
}

void verificarBotones() {
  unsigned long tiempoActual = millis();
  
  // Leer estado actual de los botones
  bool estadoActualEncendido = digitalRead(pinEncendido);
  bool estadoActualApagado = digitalRead(pinApagado);

  // Verificar botón de encendido con debounce
  if (estadoAnteriorEncendido == HIGH && estadoActualEncendido == LOW) {
    if (tiempoActual - tiempoUltimoEncendido > debounceDelay) {
      encendido = true;
      fase = 0; // Reiniciar ciclo
      tiempoAnterior = tiempoActual;
      tiempoUltimoEncendido = tiempoActual;
    }
  }

  // Verificar botón de apagado con debounce
  if (estadoAnteriorApagado == HIGH && estadoActualApagado == LOW) {
    if (tiempoActual - tiempoUltimoApagado > debounceDelay) {
      encendido = false;
      apagarSemaforos();
      tiempoUltimoApagado = tiempoActual;
    }
  }

  // Actualizar estados anteriores
  estadoAnteriorEncendido = estadoActualEncendido;
  estadoAnteriorApagado = estadoActualApagado;
}

void cicloSemaforoNoBlocking() {
  unsigned long tiempoActual = millis();
  
  switch (fase) {
    case 0: // Vía 1 verde, vía 2 rojo
      if (tiempoActual - tiempoAnterior == 0) { // Primera vez en esta fase
        digitalWrite(verde1, HIGH);
        digitalWrite(rojo2, HIGH);
        digitalWrite(rojo1, LOW);
        digitalWrite(verde2, LOW);
        digitalWrite(amarillo1, LOW);
        digitalWrite(amarillo2, LOW);
      }
      if (tiempoActual - tiempoAnterior >= 4000) {
        fase = 1;
        tiempoAnterior = tiempoActual;
        contadorParpadeo = 0;
        estadoParpadeo = false;
        tiempoParpadeo = tiempoActual;
        digitalWrite(verde1, LOW);
      }
      break;
      
    case 1: // Parpadeo amarillo vía 1
      if (tiempoActual - tiempoParpadeo >= 300) {
        estadoParpadeo = !estadoParpadeo;
        digitalWrite(amarillo1, estadoParpadeo ? HIGH : LOW);
        tiempoParpadeo = tiempoActual;
        if (!estadoParpadeo) {
          contadorParpadeo++;
        }
      }
      if (contadorParpadeo >= 3) {
        fase = 2;
        tiempoAnterior = tiempoActual;
        digitalWrite(amarillo1, LOW);
      }
      break;
      
    case 2: // Vía 2 verde, vía 1 rojo
      if (tiempoActual - tiempoAnterior == 0) { // Primera vez en esta fase
        digitalWrite(rojo1, HIGH);
        digitalWrite(rojo2, LOW);
        digitalWrite(verde2, HIGH);
        digitalWrite(verde1, LOW);
        digitalWrite(amarillo1, LOW);
        digitalWrite(amarillo2, LOW);
      }
      if (tiempoActual - tiempoAnterior >= 4000) {
        fase = 3;
        tiempoAnterior = tiempoActual;
        contadorParpadeo = 0;
        estadoParpadeo = false;
        tiempoParpadeo = tiempoActual;
        digitalWrite(verde2, LOW);
      }
      break;
      
    case 3: // Parpadeo amarillo vía 2
      if (tiempoActual - tiempoParpadeo >= 300) {
        estadoParpadeo = !estadoParpadeo;
        digitalWrite(amarillo2, estadoParpadeo ? HIGH : LOW);
        tiempoParpadeo = tiempoActual;
        if (!estadoParpadeo) {
          contadorParpadeo++;
        }
      }
      if (contadorParpadeo >= 3) {
        fase = 0; // Volver al inicio
        tiempoAnterior = tiempoActual;
        digitalWrite(amarillo2, LOW);
      }
      break;
  }
}

// Apaga todos los LEDs
void apagarSemaforos() {
  digitalWrite(rojo1, LOW);
  digitalWrite(amarillo1, LOW);
  digitalWrite(verde1, LOW);
  digitalWrite(rojo2, LOW);
  digitalWrite(amarillo2, LOW);
  digitalWrite(verde2, LOW);
}
