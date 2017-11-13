#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string.h>
#include <bits/stdc++.h>
#include <gmpxx.h>
#include <time.h>

using namespace std;

void sendGeneratedKeyPairs(int sock)
{
    mpz_class p, q, pa, qa, pp, qp, pb, qb, n, phi, bits = 512, g1, g2, g3, i1, i2;
    gmp_randclass r(gmp_randinit_default);
    r.seed(time(NULL));
    mpz_nextprime(p.get_mpz_t(), (phi = r.get_z_bits(bits)).get_mpz_t());
    sleep(1);
    mpz_nextprime(q.get_mpz_t(), (phi = r.get_z_bits(bits)).get_mpz_t());
    n = p*q;
    phi = (p-1)*(q-1);
    int a = 0;
    while(1)
    {

        if(!(a & 4))
          qa = r.get_z_range(phi);
        if(!(a & 2))
          qb = r.get_z_range(phi);
        if(!(a & 1))
          qp = r.get_z_range(phi);

        if(qa>1 && qb > 1 && qp > 1)
        {
            if(!(a&4))
            mpz_gcd(g1.get_mpz_t(),qa.get_mpz_t(),phi.get_mpz_t());
            if(!(a&2))
            mpz_gcd(g2.get_mpz_t(),qb.get_mpz_t(),phi.get_mpz_t());
            if(!(a&1))
            mpz_gcd(g3.get_mpz_t(),qp.get_mpz_t(),phi.get_mpz_t());
            if(g1==1)
            {
              if(qa != qb && qa != qp)
                a |= 4;
            } 
            if(g2 == 1)
            {
              if(qb != qa && qb != qp)
                a |= 2;
            }
            if(g3 == 1)
            {
              if(qp != qa && qb != qp)
                a |= 1;
            }
            if(a == 7)
              break;
        }
    }

    //mpz_gcdext(g.get_mpz_t(),i1.get_mpz_t(),i2.get_mpz_t(),e.get_mpz_t(),phi.get_mpz_t());
    mpz_invert(pa.get_mpz_t(), qa.get_mpz_t(), n.get_mpz_t());
    mpz_invert(pb.get_mpz_t(), qb.get_mpz_t(), n.get_mpz_t());
    mpz_invert(pp.get_mpz_t(), qp.get_mpz_t(), n.get_mpz_t());
    cout << (pa * qa )% n << (pb * qb )%n << (pp*qp)%n;
    qp = (pa*qp*qb)%n;
    qb = (qa*pp)%n;

    struct
    {
      char msg[600];
      char proxypub[600];
      char proxypri[600];
      char bobpub[600];
      char bobpri[600];
      char n[600];
    }sendc;

    mpz_class msg;
    cout << "\nenter number to send : ";
    cin >> msg;
    mpz_powm(msg.get_mpz_t(), msg.get_mpz_t(), qp.get_mpz_t(), n.get_mpz_t());
    strcpy(sendc.msg, msg.get_str().c_str());
    strcpy(sendc.proxypri, pp.get_str(10).c_str());
    strcpy(sendc.proxypub, qp.get_str(10).c_str());
    strcpy(sendc.bobpub, qb.get_str(10).c_str());
    strcpy(sendc.bobpri, pb.get_str(10).c_str());
    strcpy(sendc.n, n.get_str(10).c_str());
    send(sock, &sendc, 3600, 0);
    cout << "\nDone sending >> :D";

}
int main(){
  int clientSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  string s = "alice";
  send(clientSocket, s.c_str(), s.size(), 0);

  recv(clientSocket, buffer, 2, 0);

  cout << "\nSending the stuff now";
  sendGeneratedKeyPairs(clientSocket);

  recv(clientSocket, buffer, 2, 0);
  printf("Data received: %s",buffer);   
  close(clientSocket);
  return 0;
}