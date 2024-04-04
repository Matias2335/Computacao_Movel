#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Botao_Sim = 0;
int Botao_Nao = 0;
int Botao_Pular = 0;
int Botao_Finalizar = 0; // Botão para encerrar o jogo
int score = 0;
int tentativas = 3;
int numeroQuestao = 1; // Variável para controlar o número da questão atual
unsigned long startTime = 0;
const int tempoTotal = 15000; // Aumentei o tempo total para 15 segundos
const int ledPin = 6;

// Arrays para controlar quais perguntas já foram feitas
bool perguntasFeitasFaceis[5] = {false};
bool perguntasFeitasMedias[5] = {false};
bool perguntasFeitasDificeis[5] = {false};
bool perguntaFeitaImpossivel = false;

// Array de perguntas e respostas fáceis
char perguntasFaceis[5][72] = {
  "Tetris eh um jogo de quebra cabeca?",
  "Fortnite eh um jogo de estrategia em tempo real?",
  "Angry Birds foi desenvolvido pela EA Sports?",
  "The Sims permite que os jogadores controlem um exercito?",
  "FIFA eh uma serie de jogos de corrida?"
};

char respostasFaceis[5] = {'S', 'N', 'N', 'N', 'N'}; // Respostas correspondentes às perguntas fáceis

// Array de perguntas e respostas médias
char perguntasMedias[5][72] = {
  "God of War eh ambientado na mitologia grega?",
  "Overwatch eh um jogo de tiro em primeira pessoa?",
  "World of Warcraft eh um jogo de plataforma 2D?",
  "Metal Gear Solid eh conhecido por seu foco em combate direto?",
  "Street Fighter eh uma serie de jogos de luta?"
};

char respostasMedias[5] = {'S', 'S', 'N', 'N', 'S'}; // Respostas correspondentes às perguntas médias

// Array de perguntas e respostas difíceis
char perguntasDificeis[5][72] = {
  "BioShock se passa em uma cidade subaquatica chamada Rapture?",
  "Mass Effect eh uma serie de jogos de corrida?",
  "Doom eh creditado por ser um dos pioneiros do genero battle royale?",
  "Civilization eh uma serie de jogos de construcao de cidades?",
  "Final Fantasy eh uma série de jogos de estrategia em tempo real?"
};

char respostasDificeis[5] = {'S', 'N', 'N', 'S', 'N'}; // Respostas correspondentes às perguntas difíceis

// Array de perguntas e respostas impossíveis
char perguntaImpossivel[1][72] = {
  "Eh possivel terminar o jogo 'Dark Souls' sem sofrer nenhum dano?"
};

char respostasImpossivel[1] = {'N'};

void setup() {
  lcd.begin(16, 2);
  lcd.cursor();
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP); // Botão para pular a pergunta
  pinMode(7, INPUT_PULLUP); // Botão para encerrar o jogo
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0)); // Inicializa o gerador de números aleatórios
}

void loop() {
  // Escolhe aleatoriamente um nível de dificuldade (0 para fácil, 1 para médio, 2 para difícil, 3 para impossível)
  int nivel;
  int indice;
  char* perguntaSelecionada;
  char* respostaEsperada;

  do {
    nivel = random(0, 4);

    switch (nivel) {
      case 0: // Fácil
        indice = random(0, 5);
        if (!perguntasFeitasFaceis[indice]) {
          perguntasFeitasFaceis[indice] = true;
          perguntaSelecionada = perguntasFaceis[indice];
          respostaEsperada = &respostasFaceis[indice];
        }
        break;
      case 1: // Médio
        indice = random(0, 5);
        if (!perguntasFeitasMedias[indice]) {
          perguntasFeitasMedias[indice] = true;
          perguntaSelecionada = perguntasMedias[indice];
          respostaEsperada = &respostasMedias[indice];
        }
        break;
      case 2: // Difícil
        indice = random(0, 5);
        if (!perguntasFeitasDificeis[indice]) {
          perguntasFeitasDificeis[indice] = true;
          perguntaSelecionada = perguntasDificeis[indice];
          respostaEsperada = &respostasDificeis[indice];
        }
        break;
      case 3: // Impossível
        if (!perguntaFeitaImpossivel) {
          perguntaFeitaImpossivel = true;
          indice = 0;
          perguntaSelecionada = perguntaImpossivel[indice];
          respostaEsperada = &respostasImpossivel[indice];
        }
        break;
    }

    if (perguntaSelecionada != NULL) {
      break; // Sai do loop do-while se uma pergunta válida foi selecionada
    }
  } while (true);

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
    Botao_Sim = digitalRead(10);
    Botao_Nao = digitalRead(9);
    Botao_Pular = digitalRead(8);
    Botao_Finalizar = digitalRead(7);

    // Verifica se o tempo restante está na metade e pisca o LED
    if (millis() - startTime >= tempoTotal / 2) {
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(500);
    }

    if (Botao_Sim == HIGH || Botao_Nao == HIGH || Botao_Pular == HIGH || Botao_Finalizar == HIGH) {
      break; // Sai do loop enquanto
    }
  }

  // Desliga o LED após o tempo esgotado
  digitalWrite(ledPin, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);

  if (millis() - startTime >= tempoTotal || Botao_Pular == HIGH) {
    lcd.write("Pulou a questao");
    tentativas--;
    lcd.setCursor(0, 1);
    lcd.write("Restam ");
    lcd.print(tentativas);
    lcd.write(" Vidas");
    if (tentativas == 0) {
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
  } else if (Botao_Finalizar == HIGH || tentativas == 0) {
    lcd.write("Fim do Jogo!");
    lcd.setCursor(0, 1);
    lcd.write("Score=");
    lcd.print(score);
    delay(5000);
    while (true) {
      // Loop infinito para encerrar o jogo
    }
  } else {
    if ((Botao_Sim == HIGH && *respostaEsperada == 'S') || (Botao_Nao == HIGH && *respostaEsperada == 'N')) {
      score++;
      // Adicionei um bônus de pontuação por resposta correta
      score += 2; // Adicionei um bônus extra por resposta rápida
      lcd.write("Resposta Correta! +2 pontos!");
    } else {
      tentativas--;
      // Reduza o número de tentativas por resposta errada
      score -= 1; // Aplique uma penalidade por resposta errada
      lcd.write("Resposta Errada! -1 ponto");
      // Verifica se o usuário ainda tem vidas restantes
      if (tentativas == 0) {
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
    }
  }

  delay(5000);

  // Incrementa o número da questão para pular para a próxima
  numeroQuestao++;
}
