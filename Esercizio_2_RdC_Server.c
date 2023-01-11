/*
 ============================================================================
 Name        : Esercizio_2_RdC_Server.c
 Author      : checcolino
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//portabilità
#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

//Librerie
#include <stdio.h>
#include <stdlib.h> // for atoi()
#include <string.h>
#include <ctype.h>

//costanti
#define PROTOPORT 27015 //default protocol port number
#define QLEN 2 // size of request queue
#define BUFF 512

//funzioni
void ErrorHandler(char *errorMessage) {
printf ("%s", errorMessage);
}
void ClearWinSock() {
#if defined WIN32
WSACleanup();
#endif
}
void ClearArray(char* a, int j) {

	for(int i = 0; i < j; i++) {

		a[i] = 0;
	}
}





int main(void) {
//inizializzo winsock32

	#if defined WIN32
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		ErrorHandler("Error at WSAStartup()\n");
		return -1;
	}
	#endif







//crezione di una variabile int che conterrà descrittore della socket
int ServerSocket;

  //chiamo la funzione socket() assegnando il valore di ritorno dalla variabile appena creata
	ServerSocket = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);

  //valuto la presenza di errori per assicurarmi che la socket sia valida
  if(ServerSocket < 0 )
	{
		ErrorHandler("socket creation failed\n");
		return -1;
	}


  //Assegnazione di un indirizzo alla socket (solo lato server)

  //Creo un elemento di tipo sockaddr_in

  struct sockaddr_in sad;

  //Avvaloro l'elemento creato
  //Assegno porta e ip alla socket
  	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	sad.sin_port = htons( 27015 );

  //Verifico la presenza di eventuali errori

  if (bind(ServerSocket, (struct sockaddr*) &sad,
    sizeof(sad)) <0) {
		ErrorHandler("bind() failed.\n");
		closesocket(ServerSocket);
		ClearWinSock();
		return -1;
	}

  //server alla modalità di ascolto
	if (listen (ServerSocket, QLEN) < 0) {
		ErrorHandler("listen() failed.\n");
		closesocket(ServerSocket);
		ClearWinSock();
		return -1;
	}



  //ACCETTARE NUOVA CONNESSIONE
  struct sockaddr_in cad; //definizione della struct per l'indirizzo client
	int ClientSocket; //descrittore socket dedicata
	int clientLen; //dimensione indirizzo client
	printf( "In attesa del Client...");

	while(1){

		clientLen = sizeof(cad); //si ricava la dimensione dell'indirizzo client
		if ( (ClientSocket=accept(ServerSocket, (struct sockaddr *)&cad, &clientLen)) < 0) {
			ErrorHandler("accept() failed.\n");

      //CHIUSURA
			closesocket(ServerSocket);
			ClearWinSock();
			return -1;
		}

    else
		{
			printf("Connessione stabilita con il client: %s\n", inet_ntoa(cad.sin_addr));
		}



		char msgConn[] = "\n***Connessione avvenuta***\n";
		//invio stringa di conferma della connessione
				if(send(ClientSocket, msgConn, strlen(msgConn), 0) != strlen(msgConn)) {
					ErrorHandler("Messaggio non inviato.\n");
					closesocket(ServerSocket);
					ClearWinSock();
					return -1;
				}
				int flag_chiusura = 1; //flag che gestisce il caso di chiusura della comunicazione 1= vero, 0= falso

				while (flag_chiusura) {
					char msg1[BUFF];
					ClearArray(msg1, BUFF);


					if(recv(ClientSocket, msg1, BUFF-1, 0) <= 0) {
						ErrorHandler("Messaggio non ricevuto.\n");
						closesocket(ServerSocket);
						ClearWinSock();
						return -1;
							}
					else{
						printf("\nMessaggio ricevuto dal Client %s: '%s'\n",inet_ntoa(cad.sin_addr), msg1);
						}
					ClearArray(msg1, BUFF);

					char ack[BUFF]="ack";
					if(send(ClientSocket, ack, strlen(ack), 0) != strlen(ack)) {
										ErrorHandler("Messaggio non inviato.\n");
										closesocket(ServerSocket);
										ClearWinSock();
										return -1;
									}

					char s1[BUFF];


					if(recv(ClientSocket, s1, BUFF-1, 0) <= 0) {
											ErrorHandler("Messaggio non ricevuto.\n");
											closesocket(ServerSocket);
											ClearWinSock();
											return -1;
												}

					char s2[BUFF];
					if(recv(ClientSocket, s2, BUFF-1, 0) <= 0) {
										ErrorHandler("Messaggio non ricevuto.\n");
										closesocket(ServerSocket);
										ClearWinSock();
										return -1;
											}

					int n1 = atoi(s1);
					int n2 = atoi(s2);
					int res = n1+n2;

					printf("\nLa somma di %d + %d == %d \n",n1,n2,res);

					char sres[BUFF];
					sprintf(sres, "%d", res);

					if(send(ClientSocket, sres, strlen(sres), 0) != strlen(sres)) {
															ErrorHandler("Messaggio non inviato.\n");
															closesocket(ServerSocket);
															ClearWinSock();
															return -1;
														}







				break;
				}
}
}
