#include "LiquidCrystal.h"
#include <stdlib.h>
#include <stdio.h>

#define Botao_Iniciar 11;
#define Botao_Sim 10;
#define Botao_Nao 9;
#define Botao_Pular 8;
#define LED 12;
#define TAMANHO_VETOR 16;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

typedef char Pergunta[100];
Pergunta perguntas[16];

void inserirPergunta(Pergunta pergunta, int indice) {
  strcpy(perguntas[indice], pergunta);
}

void imprimirPerguntaAleatoria() {
  int indiceAleatorio = random(TAMANHO_VETOR);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(perguntas[indiceAleatorio]);
}

void setup() {
  pinMode(Botao_Iniciar, INPUT_PULLUP);
  pinMode(Botao_Sim, INPUT_PULLUP);
  pinMode(Botao_Nao, INPUT_PULLUP);
  pinMode(Botao_Pular, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  lcd.begin(16, 2);

  //Facil
  inserirPergunta("Tetris é um jogo de quebra-cabeça?"); // Resposta: Sim
  inserirPergunta("Fortnite é um jogo de estratégia em tempo real?"); // Resposta: Não
  inserirPergunta("Angry Birds foi desenvolvido pela EA Sports?"); // Resposta: Não
  inserirPergunta("The Sims permite que os jogadores controlem um exército?"); // Resposta: Não
  inserirPergunta("FIFA é uma série de jogos de corrida?"); // Resposta: Não

  //Medio
  inserirPergunta("God of War é ambientado na mitologia grega?"); // Resposta: Sim
  inserirPergunta("Overwatch é um jogo de tiro em primeira pessoa?"); // Resposta: Sim
  inserirPergunta("World of Warcraft é um jogo de plataforma 2D?"); // Resposta: Não
  inserirPergunta("Metal Gear Solid é conhecido por seu foco em combate direto?"); // Resposta: Não
  inserirPergunta("Street Fighter é uma série de jogos de luta?"); // Resposta: Sim

  //Dificil
  inserirPergunta("BioShock se passa em uma cidade subaquática chamada Rapture?"); // Resposta: Sim
  inserirPergunta("Mass Effect é uma série de jogos de corrida?"); // Resposta: Não
  inserirPergunta("Doom é creditado por ser um dos pioneiros do gênero battle royale?"); // Resposta: Não
  inserirPergunta("Civilization é uma série de jogos de construção de cidades?"); // Resposta: Não
  inserirPergunta("Final Fantasy é uma série de jogos de estratégia em tempo real?"); // Resposta: Não

  //Impossivel
  inserirPergunta("É possível terminar o jogo 'Dark Souls' sem sofrer nenhum dano?"); // Resposta: Não

  randomSeed(analogRead(0));

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SEJA BEM VINDO");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(3000);
}

void loop() {
  while (digitalRead(Botao_Iniciar) == HIGH) {}

  while (true) {
    imprimirPerguntaAleatoria();

    while (true) {

      if (digitalRead(Botao_Sim) == LOW) {
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
