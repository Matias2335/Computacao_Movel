#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Botao_Sim = 0;
int Botao_Nao = 0;
int Botao_Pular = 0;
int Botao_Desistir = 0; 
int score = 0;
int tentativas = 3;
int numeroQuestao = 1;
unsigned long startTime = 0;
const int tempoTotal = 15000;
const int ledPin = 6;
const int buzzerPin = A5; //buzzer

// Frequências para os sons
const int freqAcerto = 1000;
const int freqErro = 500;     
const int freqPulo = 300; 
const int freqDesistencia = 200; 

// Arrays para controlar quais perguntas já foram feitas
bool perguntasFeitasFaceis[5] = {false};
bool perguntasFeitasMedias[5] = {false};
bool perguntasFeitasDificeis[5] = {false};
bool perguntaFeitaImpossivel = {false};

// Arrays de perguntas e respostas
char* perguntasFaceis[5] = {
  "Tetris eh um jogo de quebra cabeca?",
  "Fortnite eh um jogo de estrategia em tempo real?",
  "Angry Birds foi desenvolvido pela EA Sports?",
  "The Sims permite que os jogadores controlem um exercito?",
  "FIFA eh uma serie de jogos de corrida?"
};

char respostasFaceis[5] = {'S', 'N', 'N', 'N', 'N'}; //Resposta Facil

char* perguntasMedias[5] = {
  "God of War eh ambientado na mitologia grega?",
  "Overwatch eh um jogo de tiro em primeira pessoa?",
  "World of Warcraft eh um jogo de plataforma 2D?",
  "Metal Gear Solid eh conhecido por seu foco em combate direto?",
  "Street Fighter eh uma serie de jogos de luta?"
}; 

char respostasMedias[5] = {'S', 'S', 'N', 'N', 'S'}; // Respostas médias

char* perguntasDificeis[5] = {
  "BioShock se passa em uma cidade subaquatica chamada Rapture?",
  "Mass Effect eh uma serie de jogos de corrida?",
  "Doom eh creditado por ser um dos pioneiros do genero battle royale?",
  "Civilization eh uma serie de jogos de construcao de cidades?",
  "Final Fantasy eh uma serie de jogos de estrategia em tempo real?"
};

char respostasDificeis[5] = {'S', 'N', 'N', 'S', 'N'}; // Respostas difíceis

char* perguntaImpossivel[1] = {
  "Eh possivel terminar o jogo 'Dark Souls' sem sofrer nenhum dano?"
};

char respostasImpossivel[1] = {'S'};

// Funções para tocar sons
void playSound(int frequency, int duration) {
  tone(buzzerPin, frequency);
  delay(duration);
  noTone(buzzerPin);
}

// Função para tocar a melodia de vitória
void playVictoryMelody() {
  int victoryMelody[] = {262, 330, 392, 523, 659, 784, 1046};
  int victoryMelodyDurations[] = {400, 400, 400, 400, 400, 400, 800};

  for (int i = 0; i < sizeof(victoryMelody) / sizeof(int); i++) {
    tone(buzzerPin, victoryMelody[i]);
    delay(victoryMelodyDurations[i]);
    noTone(buzzerPin);
  }
}

void setup() {
  lcd.begin(16, 2);
  lcd.cursor();
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP); 
  pinMode(7, INPUT_PULLUP); 
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0)); 
}

void loop() {
  char* perguntaSelecionada;
  char* respostaEsperada;

  // Verifica se todas as perguntas de cada nível foram feitas
  bool todasPerguntasFaceisFeitas = perguntasFeitasFaceis[0] && perguntasFeitasFaceis[1] && perguntasFeitasFaceis[2] && perguntasFeitasFaceis[3] && perguntasFeitasFaceis[4];
  bool todasPerguntasMediasFeitas = perguntasFeitasMedias[0] && perguntasFeitasMedias[1] && perguntasFeitasMedias[2] && perguntasFeitasMedias[3] && perguntasFeitasMedias[4];
  bool todasPerguntasDificeisFeitas = perguntasFeitasDificeis[0] && perguntasFeitasDificeis[1] && perguntasFeitasDificeis[2] && perguntasFeitasDificeis[3] && perguntasFeitasDificeis[4];

  // Escolhe aleatoriamente uma pergunta do nível fácil, se ainda houver perguntas disponíveis nesse nível
  if (!todasPerguntasFaceisFeitas) {
    int indiceFacil;
    do {
      indiceFacil = random(0, 5);
    } while (perguntasFeitasFaceis[indiceFacil]);

    perguntasFeitasFaceis[indiceFacil] = true;
    perguntaSelecionada = perguntasFaceis[indiceFacil];
    respostaEsperada = &respostasFaceis[indiceFacil];
  }
  // Escolhe aleatoriamente uma pergunta do nível médio, se ainda houver perguntas disponíveis nesse nível
  else if (!todasPerguntasMediasFeitas) {
    int indiceMedio;
    do {
      indiceMedio = random(0, 5);
    } while (perguntasFeitasMedias[indiceMedio]);

    perguntasFeitasMedias[indiceMedio] = true;
    perguntaSelecionada = perguntasMedias[indiceMedio];
    respostaEsperada = &respostasMedias[indiceMedio];
  }
  // Escolhe aleatoriamente uma pergunta do nível difícil, se ainda houver perguntas disponíveis nesse nível
  else if (!todasPerguntasDificeisFeitas) {
    int indiceDificil;
    do {
      indiceDificil = random(0, 5);
    } while (perguntasFeitasDificeis[indiceDificil]);

    perguntasFeitasDificeis[indiceDificil] = true;
    perguntaSelecionada = perguntasDificeis[indiceDificil];
    respostaEsperada = &respostasDificeis[indiceDificil];
  }
  // Se todas as perguntas de todos os níveis foram feitas, escolhe a pergunta impossível
  else {
    perguntaSelecionada = perguntaImpossivel[0];
    respostaEsperada = &respostasImpossivel[0];
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
    lcd.clear(); 
    for (int i = 0; i < comprimento; i++) {
        if (i == 16 || i == 32 || i == 48 || i == 64) {
            lcd.clear();
            lcd.setCursor(0, 0); 
        }
        lcd.write(perguntaSelecionada[i]);
        delay(250);
    }
  } else {
    lcd.print(perguntaSelecionada);
  }

  // Atualiza o valor de comprimento após a exibição da pergunta
  comprimento = strlen(perguntaSelecionada);

  delay(2000);
  lcd.clear();
  lcd.write("Q-");
  lcd.print(numeroQuestao);
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

  // Aguardar até que algum botão seja pressionado, o tempo se esgote, o botão de pular seja pressionado ou o botão de desistir seja pressionado
  while (millis() - startTime < tempoTotal) {
    Botao_Sim = digitalRead(10);
    Botao_Nao = digitalRead(9);
    Botao_Pular = digitalRead(8);
    Botao_Desistir = digitalRead(7);

    // Verifica se o tempo restante está na metade e pisca o LED
    if (millis() - startTime >= tempoTotal / 2) {
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(500);
    }

    if (Botao_Sim == HIGH || Botao_Nao == HIGH || Botao_Pular == HIGH || Botao_Desistir == HIGH) {
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
      playSound(freqDesistencia, 200);
      lcd.write("Fim do Jogo!");
      lcd.setCursor(3,1);
      lcd.write("Score=");
      lcd.print(score);
      delay(5000);
          while (true) {
    
      }
    }
    playSound(freqPulo, 200);
  } else if (Botao_Desistir == HIGH || tentativas == 0) {
    playSound(freqDesistencia, 200);
    lcd.write("Fim do Jogo!");
    lcd.setCursor(0, 1);
    lcd.write("Score=");
    lcd.print(score);
    delay(5000);
    while (true) {
  
    }
  } else {
    if ((Botao_Sim == HIGH && *respostaEsperada == 'S') || (Botao_Nao == HIGH && *respostaEsperada == 'N')) {
      score++;
      lcd.write("Resposta Correta!");
      playSound(freqAcerto, 200);
    } else {
      tentativas--;
      lcd.write("Resposta Errada!");
      // Verifica se o usuário ainda tem vidas restantes
      if (tentativas == 0) {
        lcd.clear();
        playSound(freqDesistencia, 200);
        lcd.write("Fim do Jogo!");
        lcd.setCursor(3,1);
        lcd.write("Score=");
        lcd.print(score);
        delay(5000);
        while (true) {
        }
      }
      playSound(freqErro, 200);
    }
  }

  delay(5000);
  
  numeroQuestao++;

  // Verifica se o jogo foi vencido (todas as perguntas respondidas corretamente)
  if (numeroQuestao > 16 && tentativas > 0) {
    lcd.clear();
    lcd.write("Voce venceu!");
    lcd.setCursor(0, 1);
    lcd.write("Score=");
    lcd.print(score);
    delay(5000);
    playVictoryMelody();
    while (true) {
    }
  }
}