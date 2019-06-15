# Chain Matrix Multiplication

L'algoritmo iterativo per moltiplicare le matrici visto a lezione è stato realizzato all'interno della classe `ChainMatrix`, che contiene un array di matrici moltiplicabili in successione.

Il metodo `multiply` permette di utilizzare l'algoritmo di programmazione dinamica (il vero lavoro viene svolto dal metodo privato `multiply_aux`).

`standard_multiply` permette invece di moltiplicare in successione le matrici partendo dalle prime due:
(... ( ( (A * B) * C) * D) * ...)



All'interno della funzione `main` è possibile modificare le dimensioni delle matrici per ricevere in output i tempi di esecuzione di `multiply` e `standard_multiply` per la stessa catena.

Ad esempio per una catena di questo tipo
( 500 x 33 ) * ( 32 x 15 ) * ( 15 x 878 ) * ( 878 x 300 ) * ( 300 x 926 ) 
i tempi ottenuti sono:
- `multiply` ---------------->  0.392209 seconds
- `standard_multiply` ----> 3.32425 seconds

