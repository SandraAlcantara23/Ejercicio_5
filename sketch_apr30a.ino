// Pines para los LEDs del semáforo
const int ledVerde1    = 5;
const int ledAmarillo1 = 6;
const int ledRojo1     = 7;
const int ledVerde2    = 2;
const int ledAmarillo2 = 3;
const int ledRojo2     = 4;

// Pines para los botones
const int botonStart = 9;
const int botonStop  = 8 ;

// Variable para saber si el semáforo está activo
bool semaforoActivo = false;
bool estadoAnteriorStart = HIGH;
bool estadoAnteriorStop = HIGH;

void setup() {
  // Configurar LEDs como salidas
  pinMode(ledVerde1, OUTPUT);
  pinMode(ledAmarillo1, OUTPUT);
  pinMode(ledRojo1, OUTPUT);
  pinMode(ledVerde2, OUTPUT);
  pinMode(ledAmarillo2, OUTPUT);
  pinMode(ledRojo2, OUTPUT);

  // Configurar botones como entradas con pull-up interno
  pinMode(botonStart, INPUT_PULLUP);
  pinMode(botonStop, INPUT_PULLUP);

  // Apagar todos los LEDs al inicio
  apagarTodos();
}

void loop() {
  // Leer el estado de los botones con un debounce
  bool estadoActualStart = digitalRead(botonStart);
  bool estadoActualStop = digitalRead(botonStop);

  // Si se presiona el botón "Start" (y ha cambiado de estado)
  if (estadoActualStart == LOW && estadoAnteriorStart == HIGH) {
    semaforoActivo = true;  // Iniciar el semáforo
    apagarTodos();          // Asegurarse de que los LEDs estén apagados al inicio
    delay(300);             // Retardo para evitar rebotes del botón
  }

  // Si se presiona el botón "Stop" (y ha cambiado de estado)
  if (estadoActualStop == LOW && estadoAnteriorStop == HIGH) {
    semaforoActivo = false;  // Detener el semáforo
    apagarTodos();           // Apagar todos los LEDs
    delay(300);              // Retardo para evitar rebotes del botón
  }

  // Actualizar el estado anterior de los botones
  estadoAnteriorStart = estadoActualStart;
  estadoAnteriorStop = estadoActualStop;

  // Si el semáforo está activo, ejecutar la secuencia
  if (semaforoActivo) {
    secuenciaSemaforo();  // La secuencia se ejecutará cíclicamente
  }
}

// Función para apagar todos los LEDs
void apagarTodos() {
  digitalWrite(ledVerde1, LOW);
  digitalWrite(ledAmarillo1, LOW);
  digitalWrite(ledRojo1, LOW);
  digitalWrite(ledVerde2, LOW);
  digitalWrite(ledAmarillo2, LOW);
  digitalWrite(ledRojo2, LOW);
}

// Función para ejecutar la secuencia completa del semáforo
void secuenciaSemaforo() {
  // Semáforo 1 verde, semáforo 2 rojo
  digitalWrite(ledVerde1, HIGH);
  digitalWrite(ledRojo2, HIGH);
  delay(5000); // Mantener 5 segundos

  // Parpadear verde del semáforo 1
  parpadearVerde(ledVerde1);
  // Parpadear amarillo del semáforo 1
  parpadearAmarillo(ledAmarillo1);

  // Cambiar luces: semáforo 1 rojo, semáforo 2 verde
  digitalWrite(ledRojo1, HIGH);
  digitalWrite(ledRojo2, LOW);

  digitalWrite(ledVerde2, HIGH);
  delay(5000); // Mantener 5 segundos

  // Parpadear verde del semáforo 2
  parpadearVerde(ledVerde2);
  // Parpadear amarillo del semáforo 2
  parpadearAmarillo(ledAmarillo2);

  // Cambiar luces: semáforo 2 rojo, semáforo 1 verde
  digitalWrite(ledRojo2, HIGH);
  digitalWrite(ledRojo1, LOW);
}

// Función para parpadear el LED verde
void parpadearVerde(int pin) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(pin, LOW);
    delay(300);
    digitalWrite(pin, HIGH);
    delay(300);
  }
  digitalWrite(pin, LOW);  // Apagar después de parpadear
}

// Función para parpadear el LED amarillo
void parpadearAmarillo(int pin) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(pin, HIGH);
    delay(300);
    digitalWrite(pin, LOW);
    delay(300);
  }
}
