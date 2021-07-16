/*
 * MedQ: codigo de protótipo de caixa de medicamentos
 * 
 * Este primeiro potótipo se propõe a realizar as seguintes tarefas:
 * - ler e armazenar os medicamentos e os horários a serem tomados por meio de um terminal.
 * - controlar o horário do dia por meio de um widget de relógio do Blynk.
 * - montar uma agenda diária.
 * - avisar o usuário quando estiver próximo da hora de tomar um medicamento, através do led verde.
 * - feedback instantâneo com um led vermelho caso o usuário levante a tampa errada.
 * 
 * Considerações:
 * - considera-se que o usuário colocará o medicamento em sua devida divisória da caixa ao adicioná-lo no programa.
 * - para este protótipo, trabalha-se num período de apenas um dia, não sendo possível programar uma rotina ou frequência de medicamentos.
 * - lê-se apeanas valores inteiros de horas(18:00, 10:00, etc)
 * - o programa prevê atrasos de apenas poucos minutos (se fosse contar com atrasos de horas, o atraso de um medicamento poderia coincidir com o horário de outro,
 *   gerando erros, algo que será trabalhado para resolver nas próximas versões).
 * 
 * Projeções futuras:
 * - ler valores fracionais de hora.
 * - trabalhar com períodos maiores que de um dia e poder programar a frequência dos medicamentos.
 * - armazenar a hora em que o medicamento foi tomado e alertar caso tomado com atraso.
 * - organizar a agenda em ordem crescente de horários.
*/
#include<stdlib.h>
#include<string.h>

#define BLYNK_PRINT SwSerial     //
#include <SoftwareSerial.h>      //funções necessárias para o Blynk
SoftwareSerial SwSerial(10, 11); //
#include <BlynkSimpleStream.h>   //

#define MAX 5 //maximo de 5 medicamentos
#define LETRAS 20 // maximo de letras para nomes

char auth[] = "";

WidgetTerminal terminal(V1);

int tarefa;
long int tempo;

const int manha = 2;
const int tarde = 3;
const int noite = 4;

const int ledVerde = 8;
const int ledVermelho = 9;

char agenda[MAX][LETRAS];
long int horario[MAX];
int i;

bool tomou[MAX];

BLYNK_WRITE(V1){ /*função chamada quando algo é digitado no terminal*/
  switch(tarefa){/*a variável "tarefa" controla o fluxo da função.*/
    case 0:
      switch(param.asInt()){
        case 1:
          terminal.println("Nome do remedio:");
          terminal.flush();
          tarefa = 1;
          break;
        case 2:
          terminal.clear();
          for(int k=0; k<i; k++){
              terminal.print(agenda[k]);
              terminal.print(" - ");
              terminal.print(String(horario[k]));
              terminal.print(":00");
              if(tomou[k])
                terminal.println(" ok!");
              else
                terminal.println(" X");
          }terminal.print("\n");
          imprimir();
          break;
      }break;
    case 1:
      strcpy(agenda[i], param.asStr());
      terminal.println("Horario:");
      terminal.flush();
      tarefa = 2;
      break;
    case 2:
      horario[i] = param.asInt();
      tomou[i] = false;
      i++;
      tarefa = 0;
      terminal.clear();
      terminal.print("remedio ");
      terminal.write(agenda[i-1]);
      terminal.println(" adicionado as");
      terminal.print(String(horario[i-1]));
      terminal.println(" horas!\n");
      imprimir();
  }
}

BLYNK_WRITE(V2){ //Widget de relógio
  tempo = param.asLong();
}

void imprimir(){
  terminal.println("Digite um numero para a tarefa:");
  terminal.println("1) Adicionar remedio");
  terminal.println("2) Ver agenda");
  terminal.flush();  
}

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  pinMode(manha, INPUT);
  pinMode(tarde, INPUT);
  pinMode(noite, INPUT);
  
  SwSerial.begin(9600);
  Serial.begin(9600);
  Blynk.begin(Serial, auth);

  tarefa = 0;
  i = 0; /*armazena quantos remedios tem no dia*/
  
  terminal.clear();
  terminal.println("***MedQ - prototipo***");
  imprimir();
}

void loop() {
  Blynk.run();
  for(int k=0; k<i; k++){
    long int hor = horario[k]*3600;
    long int intervalo = 900;
    if(tempo>hor-intervalo && tempo<hor+intervalo && tomou[k]==false){
      digitalWrite(ledVerde, HIGH);
      if(hor>=18000 && hor<43200){ //manhã 
        if(digitalRead(manha)==HIGH){
          digitalWrite(ledVerde, LOW);
          tomou[k]=true;
          terminal.println("tomou remedio!");
          terminal.flush();
        }if(digitalRead(tarde)==HIGH || digitalRead(noite)==HIGH)
          digitalWrite(ledVermelho, HIGH);
        else
          digitalWrite(ledVermelho, LOW);
      }
      if(hor>=43200 && hor<64800){//tarde
          if(digitalRead(tarde)==HIGH){
          digitalWrite(ledVerde, LOW);
          tomou[k]=true;
          terminal.println("tomou remedio!");
          terminal.flush();
        }if(digitalRead(manha)==HIGH || digitalRead(noite)==HIGH)
          digitalWrite(ledVermelho, HIGH);
        else
          digitalWrite(ledVermelho, LOW);
      }
      if(hor>=64800 || hor<18000){//noite
          if(digitalRead(noite)==HIGH){
          digitalWrite(ledVerde, LOW);
          tomou[k]=true;
          terminal.println("tomou remedio!");
          terminal.flush();
        }if(digitalRead(manha)==HIGH || digitalRead(tarde)==HIGH)
          digitalWrite(ledVermelho, HIGH);
        else
          digitalWrite(ledVermelho, LOW);
      }
    }
  }
}
