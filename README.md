<h1 align="center"> Relatório do Projeto de Computação Móvel </h1

Introdução

Apresentação:

O tema deste projeto é a Computação Embarcada. Consiste no desenvolvimento de um jogo de perguntas e respostas de sim ou não, contendo 3 níveis de perguntas, fácil, médio, difícil + perguta final para vencer o jogo. 
Cada nível contém 5 perguntas devem ser randomizadas e através dos acertos é contabilizada a pontuação do jogador. Mas a cada erro são perdidas vidas, caso haja três erros ou pulos ou ausência de respostas gerará o fim do jogo.
Para cada tipo de resposta, como acerto, erro, pulo e desistência, deve haver um som customizado. 

Objetivos:
1) Utilizando a aplicação Tinkercad, construir uma estrutura de circuitos que pudesse ser utilizada para jogar um jogo de perguntas e respostas
2) Desenvolver um código na liguagem C++ gerasse "vida" a estrutura de circuitos construída. Deste modo, o código construído gerou as perguntas, respostas, pontuação, numeração e randomização de perguntas que apareceram no display LCD. Também através do código criamos sons customizados para cada condição, como erro, acerto, pulo e desistência
3) Através da integração entre Replit e Github, realizar commits comentando e explicando cada alteração e adição feita no código 
4) Correção de erros encontrados
5) Montagem, em sala, da estrutura de circuitos e teste das funcionalidades com a circuito construído

Metodologia

Materiais utilizados no Tinkercad:
- Arduino UNO
- 1 LED vermelho
- Potenciômetro
- 4 botões 
- 6 Resistores
- Buzzer
- Display LCD 16x2
- Placa de ensaio
  
Materiais utilizados para desenvolvimento do código:
- Replit
- Github - commits, vídeo e foto

Conclusão:
- Durante o desenvolvimento, o primeiro problema que encontramos foi na função do código que randomizava as perguntas. Inicialmente ela funcionava, porém conforme atualizamos o código, ela foi prejudicada, sendo assim ao invés de randomizar todas as perguntas ela repetia algumas. A solução encontrada para este problema foi retirar todas as atualizações que haviam sido alteradas no código, com isso descobrimos que o verdadeiro problema estava no buzzer que estava conectado na porta lógica A0, o que acabava não gerando o random de perguntas - quando você conecta algo à porta A0, o Arduino pode interpretar o sinal nessa porta como entrada analógica. Isso acabou interferindo na leitura dos dados analógicos e, consequentemente, afetando na aleatoriedade gerada pela função randomSeed().

Link do vídeo de demonstração e explicação do projeto desenvolvido: https://drive.google.com/file/d/1nf7CF4pb4wJLQCIzZBsLyprjdINaqyqf/view?usp=sharing
