/*
 ============================================================================
 Name        : Esercizio_2_RdC_Client.c
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


//COSTANTI
#define BUFFERSIZE 512
#define PROTOPORT 27015

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
int ClientSocket;

  //chiamo la funzione socket() assegnando il valore di ritorno dalla variabile appena creata
	ClientSocket = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);

  //valuto la presenza di errori per assicurarmi che la socket sia valida
  if(ClientSocket < 0 )
	{
		ErrorHandler("socket creation failed\n");
		return -1;
	}


  //Assegnazione di un indirizzo alla socket (solo lato server)

  //Creo un elemento di tipo sockaddr_in
  char server[BUFFERSIZE];
  int porta;
  puts("Inserisci IP server (127.0.0.1)\n");
  gets(server);
  fflush(stdin);
  puts("\nInserisci porta (27015)\n");
  scanf("%d", &porta);


  struct sockaddr_in sad;
  memset(&sad, 0, sizeof(sad));
  //Avvaloro l'elemento creato
  //Assegno porta e ip alla socket
  	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr( server );
	sad.sin_port = htons( porta );


  //richiesta di connessione del client al server
	if (connect(ClientSocket, (struct sockaddr*) &sad, sizeof(sad)) <0)
	{
		ErrorHandler("Failed to connect.");
		return 0;
	}



char msg[BUFFERSIZE];
ClearArray(msg, BUFFERSIZE);

//ricezione della stringa di connessione
if(recv(ClientSocket, msg, BUFFERSIZE-1, 0) <=0 ) {

	ErrorHandler("Messaggio non ricevuto");
	closesocket(ClientSocket);
	ClearWinSock();
	return -1;
}

else {

	puts(msg);
}
int flag_chiusura = 1; //flag che gestisce il caso di chiusura della comunicazione 1= vero, 0 = falso

	while(flag_chiusura) {


		char msg1[BUFFERSIZE]="Hello";



					if(send(ClientSocket, msg1, strlen(msg1), 0) != strlen(msg1))
					{
						ErrorHandler("Messaggio non inviato");
						closesocket(ClientSocket);
						ClearWinSock();
						return -1;
					}

				ClearArray(msg1, BUFFERSIZE);


				if(recv(ClientSocket, msg1, BUFFERSIZE-1, 0) <=0 ) {

									ErrorHandler("Messaggio non ricevuto1");
									closesocket(ClientSocket);
									ClearWinSock();
									return -1;
								}
				printf("Messaggio ricevuto dal Server: '%s'\n\n", msg1);
				ClearArray(msg1, BUFFERSIZE);

				int n1,n2;
				printf("Inserisci numero:\n");
				scanf("%d", &n1);
				printf("Inserisci numero:\n");
				scanf("%d", &n2);

				char s1[BUFFERSIZE];
				char s2[BUFFERSIZE];

				sprintf(s1, "%d", n1);
				sprintf(s2, "%d", n2);

				if(send(ClientSocket, s1, strlen(s1), 0) != strlen(s1))
									{
										ErrorHandler("Messaggio non inviato");
										closesocket(ClientSocket);
										ClearWinSock();
										return -1;
									}
				if(send(ClientSocket, s2, strlen(s2), 0) != strlen(s2))
													{
														ErrorHandler("Messaggio non inviato");
														closesocket(ClientSocket);
														ClearWinSock();
														return -1;
													}

				char res[BUFFERSIZE];
				if(recv(ClientSocket, res, BUFFERSIZE-1, 0) <=0 ) {

													ErrorHandler("Messaggio non ricevuto1");
													closesocket(ClientSocket);
													ClearWinSock();
													return -1;
												}
				else{
					printf("\nRES == ** %s **\n",res);
					break;
				}


	}


// CHIUSURA DELLA CONNESSIONE
closesocket(ClientSocket);
ClearWinSock();
printf("\n"); // Print a final linefeed
system("pause");
return(0);
}










