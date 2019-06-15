# Matrix Multiplication
All'interno della classe `Matrix` è presente il metodo `strassen`, nel quale è stato implementato l'algoritmo di Volker Strassen per la moltiplicazione di matrici.

Le matrici vengono dapprima "embeddate" in alto a sinistra all'interno di matrici quadrate di zeri di ordine 2^n.
Questo passaggio rende la moltiplicazione standard più rapida per matrici piccole ma è necessario per poter utilizzare l'algoritmo.

Dopodiché le matrici vengono moltiplicate seguendo il metodo ricorsivo visto a lezione.

Viene restituita come risultato la moltiplicazione standard per matrici quadrate di ordine minore di un certo 2^m.
Il valore di m è stato preso uguale a 6 a seguito dei dati mostrati nella tabella qua sotto.
Nelle due colonne sono riportati i tempi che impiega l'algoritmo di Strassen per moltiplicare due matrici di dimensione rispettivamente 1024x1024 e 2048x2048.
Si vede che in entrambi i casi il valore ottimale di m è 6.
```
| m | 1024x1024 | 2048x2048 |
|:-:|:---------:|:---------:|
| 9 |  18.6832  |  127.688  |
| 8 |  10.5758  |  72.5178  |
| 7 | 6.73463   |  44.1305  |
| 6 | 5.78997   |  40.0705  |
| 5 | 5.9209    |  40.1546  |
| 4 | 6.83313   |           |
| 3 | 11.8889   |           |
| 2 | 39.4926   |           |
```
Nella seguente tabella vengono invece riportati i tempi impiegati dai due metodi per moltiplicare dua matrici quadrate di dimensione 2^n x 2^n.

```markdown
|  n |     A*B    | strassen(A,B) |
|:--:|:----------:|:-------------:|
|  2 |  3.414e-06 |   4.3947e-05  |
|  3 |  7.68e-06  |   3.2427e-05  |
|  4 | 5.248e-05  |   0.0001024   |
| 5  | 0.00116565 |  0.000500053  |
| 6  | 0.00337877 |   0.00359253  |
| 7  | 0.0275277  |   0.0267528   |
| 8  | 0.234304   |    0.125131   |
| 9  | 3.25179    |    1.06152    |
| 10 | 41.8094    | 5.99175       |
| 11 | 324.557    | 42.3501       
```
