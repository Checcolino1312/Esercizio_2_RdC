# Esercizio_2_RdC

Progettare ed implementare (scrivendo codice portabile) un’applicazione TCP client/server conforme al
seguente protocollo:

1) Il server è avviato su una porta a scelta (NB: Il server resta sempre in ascolto).

2) Il client legge da tastiera l’IP e il numero di porta da utilizzare per contattare il Server

3) Il client contatta il server inviando il messaggio iniziale “Hello”.

4) Ricevuto il messaggio iniziale, il server visualizza sullo std output un messaggio contenente il nome
dell’host del client con cui ha stabilito la connessione. (Esempio: “messaggio ricevuto dal client”)

5) Il server invia al client la stringa "ack".

6) Il client riceve la stringa e la stampa.

7) Il client legge una dallo std input due interi n1 e n2 e li invia al server

8) Il server riceve i due numeri e visualizza sullo std output “la somma di n1+n2=res”, dove res è il
risultato;

9) Il server invia al client il risultato res

10) Il client riceve la stringa dal server. La visualizza sullo STD output e termina;

11) Il server rimane in ascolto.
