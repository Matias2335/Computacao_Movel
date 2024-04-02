#include "LiquidCrystal.h"
#include <stdlib.h>
#include <stdio.h>

#define Botao_Iniciar 11
#define Botao_Sim 10
#define Botao_Nao 9
#define Botao_Pular 8
#define LED 12
#define TAMANHO_VETOR 16

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

typedef char Pergunta[100];
Pergunta perguntas[16];

void inserirPergunta(Pergunta pergunta, int indice) {
  strcpy(perguntas[indice], pergunta);
}

void imprimirPerguntaAleatoria() {
  int indiceAleatorio = gerarNumeroAleatorio();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(perguntas[indiceAleatorio]);
}

int gerarNumeroAleatorio() {
  return rand() % TAMANHO_VETOR;
}

void setup() {
  pinMode(Botao_Iniciar, INPUT_PULLUP);
  pinMode(Botao_Sim, INPUT_PULLUP);
  pinMode(Botao_Nao, INPUT_PULLUP);
  pinMode(Botao_Pular, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  lcd.begin(16, 2);

  inserirPergunta("PERGUNTA 1?");
  inserirPergunta("PERGUNTA 2?");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SEJA BEM VINDO");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(3000);
}

void loop() {
  while (digitalRead(Botao_Iniciar) == HIGH) {}

  // Loop do jogo
  while (true) {
    imprimirPerguntaAleatoria();

    while (true) {
      // Botão Sim
      if (digitalRead(Botao_Sim) == LOW) {
        // Processar resposta "Sim"
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        break;
      }

      if (digitalRead(Botao_Nao) == LOW) {
    
        digitalWrite(LED, LOW);
        delay(500);
        break;
      }

      if (digitalRead(Botao_Pular) == LOW) {
  
        break;
      }
    }

    delay(1000);
  }
}
