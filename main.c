#include <LiquidCrystal.h>
#define Botao_Iniciar 11;
#define Botao_Sim 10;
#define Botao_Nao 9;
#define Botao_Pular 8;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


void setup(){
  pinMode(Botao_Iniciar, INPUT_PULLUP);
  pinMode(Botao_Sim, INPUT_PULLUP);
  pinMode(Botao_Nao, INPUT_PULLUP);
  pinMode(Botao_Pular, INPUT_PULLUP);
}

int main(void) {
  printf("Hello World\n");
  return 0;
}