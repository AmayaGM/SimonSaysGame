// =========================
// SIMON DICE - Arduino Nano
// =========================

const int leds[] = {2, 3, 4, 5};
const int botones[] = {6, 7, 8, 9};

const int buzzer = 10;

int secuencia[100];
int nivel = 0;

void setup() {

  // LEDs
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }

  // Botones
  for (int i = 0; i < 4; i++) {
    pinMode(botones[i], INPUT_PULLUP);
  }

  pinMode(buzzer, OUTPUT);

  randomSeed(analogRead(A0));

  inicioJuego();
}

void loop() {

  generarPaso();
  mostrarSecuencia();

  if (!leerJugador()) {
    perder();
  } else {
    ganarNivel();
  }

  delay(1000);
}

// =========================

void inicioJuego() {

  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH);
  }

  tone(buzzer, 1000);
  delay(500);

  noTone(buzzer);

  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }
}

// =========================

void generarPaso() {

  secuencia[nivel] = random(0, 4);
  nivel++;
}

// =========================

void mostrarSecuencia() {

  delay(500);

  for (int i = 0; i < nivel; i++) {

    int ledActual = secuencia[i];

    digitalWrite(leds[ledActual], HIGH);

    tone(buzzer, 500 + ledActual * 200);

    delay(500);

    digitalWrite(leds[ledActual], LOW);

    noTone(buzzer);

    delay(250);
  }
}

// =========================

bool leerJugador() {

  for (int i = 0; i < nivel; i++) {

    int boton = esperarBoton();

    // Mostrar botón presionado
    digitalWrite(leds[boton], HIGH);

    tone(buzzer, 500 + boton * 200);

    delay(300);

    digitalWrite(leds[boton], LOW);

    noTone(buzzer);

    // Verificar
    if (boton != secuencia[i]) {
      return false;
    }
  }

  return true;
}

// =========================

int esperarBoton() {

  while (true) {

    for (int i = 0; i < 4; i++) {

      if (digitalRead(botones[i]) == LOW) {

        delay(50);

        while (digitalRead(botones[i]) == LOW);

        return i;
      }
    }
  }
}

// =========================

void perder() {

  for (int i = 0; i < 3; i++) {

    for (int j = 0; j < 4; j++) {
      digitalWrite(leds[j], HIGH);
    }

    tone(buzzer, 200);

    delay(300);

    for (int j = 0; j < 4; j++) {
      digitalWrite(leds[j], LOW);
    }

    noTone(buzzer);

    delay(300);
  }

  nivel = 0;
}

// =========================

void ganarNivel() {

  tone(buzzer, 1200);

  delay(200);

  noTone(buzzer);
}