#include <LiquidCrystal.h>
#include <stdlib.h>
#include <stdio.h>
#include <Tone.h>


// Definições de pinos
#define Botao_Iniciar 11
#define Botao_Sim 10
#define Botao_Nao 9
#define Botao_Pular 8
#define LED 12
#define TAMANHO_VETOR 16

// Buzzer
int buzzer = 13;

// Notas musicais
int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};

// Melodias
int correctMelody[] = {notes[4], notes[6], notes[7], notes[5], notes[4]};
int errorMelody[] = {notes[0], notes[1], notes[2], notes[1], notes[0]};
int winMelody[] = {notes[7], notes[6], notes[5], notes[4], notes[3], notes[2], notes[1]};

// Perguntas
typedef char Pergunta[100];
Pergunta perguntas[16];

// Funções
void inserirPergunta(Pergunta pergunta, int indice);
void imprimirPerguntaAleatoria();
void tocarSom(int melodia[]);

void setup() {
  // Inicialização do LCD
  LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
  lcd.begin(16, 2);

  // Inicialização do Tone
  tone(buzzer, notes[0]);
  noTone(buzzer);

  // Inserir perguntas
  //Facil
  inserirPergunta("Tetris é um jogo de quebra-cabeça?", 1); // Sim
  inserirPergunta("Fortnite é um jogo de estratégia em tempo real?", 2); // Não
  inserirPergunta("Angry Birds foi desenvolvido pela EA Sports?", 3); // Não
  inserirPergunta("The Sims permite que os jogadores controlem um exército?", 4); // Não
  inserirPergunta("FIFA é uma série de jogos de corrida?", 5); // Não

  
  //Medio
  inserirPergunta("God of War é ambientado na mitologia grega?", 6); // Sim
  inserirPergunta("Overwatch é um jogo de tiro em primeira pessoa?", 7); // Sim
  inserirPergunta("World of Warcraft é um jogo de plataforma 2D?", 8); // Não
  inserirPergunta("Metal Gear Solid é conhecido por seu foco em combate direto?", 9); // Não
  inserirPergunta("Street Fighter é uma série de jogos de luta?", 10); // Sim
  //Dificil
  inserirPergunta("BioShock se passa em uma cidade subaquática chamada Rapture?", 11); // Sim
  inserirPergunta("Mass Effect é uma série de jogos de corrida?", 12); // Não
  inserirPergunta("Doom é creditado por ser um dos pioneiros do gênero battle royale?", 13); // Não
  inserirPergunta("Civilization é uma série de jogos de construção de cidades?", 14); // Sim
  inserirPergunta("Final Fantasy é uma série de jogos de estratégia em tempo real?", 15); // Não
  //
  inserirPergunta("É possível terminar o jogo 'Dark Souls' sem sofrer nenhum dano?", 16); // Não

  // Sementes aleatórias
  randomSeed(analogRead(0));

  // Mensagem inicial
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SEJA BEM VINDO");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(3000);
}

void loop() {
  int nivel = random(0, 4); // Adicionei o nível "Impossível", então agora varia de 0 a 3
  // Escolhe aleatoriamente uma questão do nível de dificuldade selecionado
  int indice;
  char* perguntaSelecionada;
  char* respostaEsperada;

  switch (nivel) {
    case 0: // Fácil
      indice = random(0, 5);
      perguntaSelecionada = perguntasFaceis[indice];
      respostaEsperada = &respostasFaceis[indice];
      break;
    case 1: // Médio
      indice = random(0, 5);
      perguntaSelecionada = perguntasMedias[indice];
      respostaEsperada = &respostasMedias[indice];
      break;
    case 2: // Difícil
      indice = random(0, 5);
      perguntaSelecionada = perguntasDificeis[indice];
      respostaEsperada = &respostasDificeis[indice];
      break;
    case 3: // Impossível
      indice = 0; // Apenas uma pergunta no nível "Impossível"
      perguntaSelecionada = perguntaImpossivel[indice];
      respostaEsperada = &respostasImpossivel[indice];
      break;  
}
  lcd.clear();
  lcd.write("Questao ");
  lcd.print(numeroQuestao); // Mostra o número da questão atual
  lcd.write(":");
  delay(3000);
  lcd.clear();
  lcd.home();
  
int comprimento = strlen(perguntaSelecionada);

if (comprimento > 16) {
  for (int i = 0; i < comprimento; i++) {
    lcd.write(perguntaSelecionada[i]);
    delay(250);
    if (i > 15) {
      lcd.scrollDisplayLeft();
    }
  }
} else {
  // Se a pergunta não exceder a largura do display, simplesmente a escreva no display
  lcd.print(perguntaSelecionada);
}

  delay(2000);
  lcd.clear();
  lcd.write("Q-");
  lcd.print(numeroQuestao); // Mostra o número da questão atual
  lcd.setCursor(8, 0);
  lcd.write("Score=");
  lcd.print(score);
  lcd.setCursor(2, 1);
  lcd.write("Sim");
  lcd.setCursor(7, 1);
  lcd.write("ou");
  lcd.setCursor(10, 1);
  lcd.write("Nao");
  startTime = millis();

  // Aguardar até que algum botão seja pressionado, o tempo se esgote, o botão de pular seja pressionado ou o botão de encerrar seja pressionado
  while (millis() - startTime < tempoTotal) {
    buttonStateS = digitalRead(10);
    buttonStateN = digitalRead(9);
    buttonStateP = digitalRead(8);
    buttonStateF = digitalRead(7);

    // Verifica se o tempo restante está na metade e pisca o LED
    if (millis() - startTime >= tempoTotal / 2) {
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(500);
      }

    if (buttonStateS == HIGH || buttonStateN == HIGH || buttonStateP == HIGH || buttonStateF == HIGH) {
      break; // Sai do loop enquanto
    }
  }
  // Desliga o LED após o tempo esgotado
  digitalWrite(ledPin, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);

  if (millis() - startTime >= tempoTotal || buttonStateP == HIGH) {
  lcd.write("Pulou a questao");
  tentativas--;
  lcd.setCursor(0, 1);
  lcd.write("Restam ");
  lcd.print(tentativas);
  lcd.write(" Vidas");
  if (tentativas == 0){
    lcd.clear();
    lcd.write("Fim do Jogo!");
    lcd.setCursor(3,1);
    lcd.write("Score=");
    lcd.print(score);
    delay(5000);
    while (true) {
      // Loop infinito para encerrar o jogo
    }
  }
  } else if (buttonStateF == HIGH || tentativas == 0) {
    lcd.write("Fim do Jogo!");
    lcd.setCursor(0, 1);
    lcd.write("Score=");
    lcd.print(score);
    delay(5000);
    while (true) {
      // Loop infinito para encerrar o jogo
    }
  } else {
    if ((buttonStateS == HIGH && *respostaEsperada == 'S') || (buttonStateN == HIGH && *respostaEsperada == 'N')) {
      score++;
      // Adicionei um bônus de pontuação por resposta correta
      score += 2; // Adicionei um bônus extra por resposta rápida
      lcd.write("Resposta Correta! +2 pontos!");
    } else {
      tentativas--;
      // Reduza o número de tentativas por resposta errada
      score -= 1; // Aplique uma penalidade por resposta errada
      lcd.write("Resposta Errada! -1 ponto");