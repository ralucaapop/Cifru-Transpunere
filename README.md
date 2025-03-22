# Cifru Transpunere cu Parola
Această aplicație implementează un algoritm de criptare și decriptare bazat pe o matrice cu coloane ordonate conform unei parole.

## Instrucțiuni de compilare și utilizare
  Pentru compilare: gcc -o transposition_cipher main.c
  Pentru rulare:
    - pentru criptare: ./transposition_cipher -e -p parola -i input.txt -o output.txt
    - pentru decriptare: ./transposition_cipher -d -p parola -i input.txt -o output.txt

## Detalii despre implementare
Aplicația folosește o tehnică de transpoziție a literelor într-o matrice. Textul este plasat într-o matrice cu un număr de coloane egal cu lungimea parolei. 
Coloanele sunt scrise în ordinea determinată de parolă. Apoi, textul este scris în fișierul de ieșire conform acestei ordini.

Funcția getColumnOrder: Determină ordinea coloanelor pe baza parolei, sortând caracterele parolei și stabilind ordinea lor.

Funcția encrypt: Plasează textul într-o matrice, folosind padding (%) pnetru a completa matricea rearanjează coloanele conform parolei și scrie rezultatul în fișierul de ieșire.

Funcția decrypt: Reconstituie matricea folosind textul criptat și ordinea coloanelor determinată de parolă, apoi elimină caracterele de padding (%) de la sfârșit și scrie textul decriptat într-un fișier.

Funcția main: Gestionează argumentele liniei de comandă, determină dacă se efectuează criptarea sau decriptarea și apelează funcțiile corespunzătoare.

### Argumente ale liniei de comandă:
-e pentru criptare.

-d pentru decriptare.

-p parola urmat de parola care va fi folosită pentru a determina ordinea coloanelor.

-i input.txt urmat de calea fișierului de intrare.

-o output.txt urmat de calea fișierului de ieșire.

### Observații:
Textul poate conține orice caractere.

Dacă fișierele de intrare sau ieșire nu sunt specificate corect sau nu pot fi deschise, aplicația va afișa un mesaj de eroare și va opri execuția.

### Exemplu din linia de comanda
![image](https://github.com/user-attachments/assets/2ed02935-cc08-40c6-a2e6-f822f67e647a)


