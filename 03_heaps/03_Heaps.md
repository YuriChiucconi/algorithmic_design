# Heaps

Nel file `min_heap_class.cpp` è stata implementata la classe `min_heap` attraverso la rappresentazione basata sugli array.

Il metodo `insert` permette di inserire un nuovo valore nell'array mantenendo la struttura corretta.

`get_next` ritorna il valore più piccolo dell'array senza rimuoverlo mentre `extract_next` ritorna lo stesso valore ma rimuovendolo dalla "cima" dell'heap.
All'interno di quest'ultima funzione è presente `HEAPIFY`.

In ultimo, con la funzione `decrease_key` è possibile abbassare un qualunque valore contenuto nell'array e mantenere la struttura dell'heap.


Nel file `main.cpp` ho effettuato una misurazione dei tempi di esecuzione delle quattro funzioni principali implementate, utilizzate su una min_heap di dimension n.
Si nota che BUILDING va come O(n) mentre le altre operazioni come O(log n).

```
n       BUILDING        EXTRACTING      INSERTING       DECREASING

2^1     8.54e-07        1.28e-06        1.28e-06        2.133e-06


2^2     4.27e-07        2.133e-06       1.28e-06        2.56e-06


2^3     8.54e-07        1.707e-06       8.53e-07        1.28e-06


2^4     8.53e-07        5.546e-06       1.28e-06        1.706e-06


2^5     1.28e-06        3.413e-06       1.28e-06        2.134e-06


2^6     2.133e-06       4.267e-06       2.133e-06       2.56e-06


2^7     2.56e-06        3.84e-06        2.56e-06        3.414e-06


2^8     4.267e-06       4.693e-06       2.133e-06       3.413e-06


2^9     9.814e-06       5.547e-06       2.134e-06       2.56e-06


2^10    1.408e-05       5.12e-06        3.414e-06       3.84e-06


2^11    2.9013e-05      7.68e-06        3.84e-06        5.12e-06


2^12    5.3333e-05      6.4e-06 	2.133e-06       3.413e-06


2^13    0.00010112      6.826e-06       2.986e-06       4.267e-06


2^14    0.00022912      2.0053e-05      7.254e-06       1.152e-05


2^15    0.000366507     8.96e-06        6.4e-06 	6.4e-06


2^16    0.000952746     1.0666e-05      3.84e-06        4.266e-06


2^17    0.00211243      2.048e-05       3.413e-06       2.56e-06


2^18    0.0027392       1.0667e-05      3.84e-06        2.987e-06


2^19    0.00547925      9.387e-06       2.56e-06        2.56e-06


2^20    0.010932        1.024e-05       2.56e-06        2.56e-06


2^21    0.0219507       1.024e-05       3.414e-06       2.56e-06


2^22    0.0436484       1.3653e-05      3.84e-06        2.987e-06


2^23    0.18857 	1.1093e-05      5.12e-06        5.546e-06


2^24    0.177821        1.3227e-05      4.693e-06       4.694e-06


2^25    0.35285 	1.5786e-05      5.12e-06        4.266e-06


2^26    0.704959        1.4507e-05      5.12e-06        4.693e-06
```
