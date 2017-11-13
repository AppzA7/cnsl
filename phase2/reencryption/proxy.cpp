#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <bits/stdc++.h>
#include <pthread.h>
#include <arpa/inet.h>
#include  <unistd.h>
#include <gmpxx.h>

using namespace std;

void *handler(void *);
int main(){
  int welcomeSocket, newSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  addr_size = sizeof serverStorage;
  int connections = 2, i =0;
  vector<int> clients;
  map<string, int> namesocket;
  while(i < connections)
  {
  	newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  	i++;
  	clients.push_back(newSocket);
  	char a[100];
  	recv(newSocket, a, 100, 0);
  	namesocket[a] = newSocket;
  	cout << "\n" << a << " joined *";
  	send(newSocket, "c", 2, 0);
  }

  //receive the key pair
  struct
    {
      char msg[600];
      char proxypub[600];
      char proxypri[600];
      char bobpub[600];
      char bobpri[600];
      char n[600];
    }sendc;

    recv(namesocket["alice"], &sendc, 3600, 0); 
    send(namesocket["alice"], "c" , 2, 0);
    mpz_class t;
    t.set_str(sendc.msg, 10);
    mpz_class pubb;
    pubb.set_str(sendc.bobpub, 10);
    //compute
    mpz_class m, n;
    n.set_str(sendc.n, 10);
    mpz_powm(m.get_mpz_t(), t.get_mpz_t(), pubb.get_mpz_t(), n.get_mpz_t()); 

    struct{
    	char msg[600];
    	char bobpri[600];
    	char n[600];
    } sendb;


    strcpy(sendb.bobpri, sendc.bobpri);
    strcpy(sendb.msg, m.get_str(10).c_str());
    strcpy(sendb.n, sendc.n);
    cout << "\nsending" << sendb.msg << endl << sendb.bobpri << endl << sendb.n << endl; 
    send(namesocket["bob"], &sendb, 1800, 0);
    cout << "\nSent data to bob";
  /*---- Send message to the socket of the incoming connection ----*/
  strcpy(buffer,"Hello World\n");
  send(newSocket,buffer,13,0);

  close(newSocket);
  close(welcomeSocket);
  return 0;
}