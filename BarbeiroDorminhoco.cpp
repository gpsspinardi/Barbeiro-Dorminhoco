#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define MAX 5  //Número de cadeiras presentes na sala de espera, sem contar a do barbeiro.


int begin = 0, end = 0, size = 0, fila[MAX+1]; // MAX+1 por contar a cadeira de corte do barbeiro.
pthread_mutex_t travaFila;


int vazio(){
  return !size;
}

void enqueue(int cliente){
  if (size < MAX+1){
    if (vazio())
      cout<<"O cliente "<<cliente<<" chega/acorda o barbeiro e senta na cadeira de corte. Barbeiro comeca a cortar seu cabelo."<<endl;
    else
      cout<<"O cliente "<<cliente<<" senta em uma das cadeiras vagas da sala de espera."<<endl;

    fila[end] = cliente;
    end = (end+1) % (MAX+1);
    size++;
  }else
    cout<<"Todas as 5 cadeiras de espera estavam ocupadas, e o "<<cliente<<" foi embora."<<endl;
}

int denqueue(){
	int t;
  if (!vazio()){
    srand(time(NULL));
    t = (rand() % 10) + 20; // Para usar a média de 25 minutos por corte, com variações de 5 pra cima e 5 pra baixo.
sleep(t);
   
    cout<<"O barbeiro termina de cortar o cabelo do cliente "<<fila[begin]<<", que vai embora."<<endl;
    cout<<"Tempo de corte: "<<t<<" minutos."<<endl;
    //return t;

    int cliente = fila[begin];
    begin = (begin+1) % (MAX+1);
    size--;

    if (vazio())
      cout<<"Nao existem clientes para serem atendidos no momento. O barbeiro dorme."<<endl;
    else
      cout<<"O cliente "<<fila[begin]<<" senta na cadeira de corte do barbeiro."<<endl;

    return cliente;
  }else
    return -1;
}

void* cliente(void* argumento){
  unsigned long idCliente = *((unsigned long*) argumento);

  pthread_mutex_trylock(&travaFila);
  enqueue(idCliente);
  pthread_mutex_unlock(&travaFila);
}

void* barbeiro(void* argumento){
  for ( ; ; ){
    pthread_mutex_trylock(&travaFila);
    denqueue();
    pthread_mutex_unlock(&travaFila);
  }
}

int main(){
int tempototal;


	int x;
cout<<"Bem vindo ao problema do Barbeiro Dorminhoco. Para comecar a rodar, pressione 1. Para sair, pressione 0."<<endl;
cout<<"Escolha: ";
cin>>x;
int i;
if (x==1){
	cout<<"Iniciando, aguarde...\n\n\n";
	while (tempototal < 1440)	{
  pthread_mutex_init(&travaFila, NULL);

  
  pthread_t threadBarbeiro, threadCliente;

  pthread_create(&threadBarbeiro, NULL, barbeiro, NULL);
  srand(time(NULL));
  for (i = 0 ; ; ++i){
  	int y = (rand() % 20) + 20; // Valor aproximado para que se fique com uma taxa de 2 clientes por hora.
  	tempototal = tempototal + y; // Somar valor do tempo de chegada dos clientes, até 1440 minutos, que totaliza 1 dia.
    sleep(y); 
    cout<<"Tempo ate chegada de novo cliente, desde a chegada do ultimo cliente: "<<y<<" minutos."<<endl;
    pthread_create(&threadCliente, NULL, cliente, &i);
}

  }
  cout<<"Durante um dia, foram atendidos em média "<<i<<" clientes."<<endl;
}

else if (x==0);
{

	cout<<"Fim.";
	return 0;
}
  return 0;
}


