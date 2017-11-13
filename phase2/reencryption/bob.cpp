#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <bits/stdc++.h>
#include <gmpxx.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(){
  int clientSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  send(clientSocket, "bob", 4, 0);
  recv(clientSocket, buffer, 2, 0);
  cout << "\nConnected to server";

  struct {
    char msg[600];
    char pri[600];
    char n[600];
  } recvc;

  recv(clientSocket, &recvc, 1800, 0);
  cout << "\nReceived data from proxy server";
  cout << "\nreceived" << recvc.msg << endl << recvc.pri << endl << recvc.n << endl; 
  cout.flush();
  mpz_class pri, m, n;
  pri.set_str(recvc.pri, 10);
  m.set_str(recvc.msg, 10);
  n.set_str(recvc.n, 10);
  mpz_powm(m.get_mpz_t(), m.get_mpz_t(), pri.get_mpz_t(), n.get_mpz_t());
  cout << "\nthe number received is : " << m;
  //printf("Data received: %s",buffer);   
  close(clientSocket);
  return 0;
}