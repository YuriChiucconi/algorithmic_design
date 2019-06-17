# Sorting

Ho scritto gli algoritmi di sorting richiesti come metodi della classe `vector`.

Sono presenti:
- `insertion_sort` 
- `quick_sort` 
- `counting_sort` 
- `radix_sort` 
- `bucket_sort` 
- `select` (implementato in modo da supportare la presenza di elementi ripetuti)

Soltanto `heap_sort` è stato scritto per praticità all'interno della classe `min_heap` scritta per l'esercizio 3:

https://github.com/YuriChiucconi/algorithmic_design/blob/master/03_heaps/min_heap_class.cpp .

Attraverso l'utilizzo del codice presente nel file `main.cpp` è stata effettuata una misurazione dei tempi impiegati dai metodi `insertion_sort` e `quick_sort` per ordinare vettori di lunghezza n sia nei casi peggiori, ovvero quando gli elementi sono ordinati in ordine decrescente, sia nei casi migliori, cioè con vettori già ordinati.

Questi sono i risultati ottenuti
~~~~
(w) = worst case
(b) = best case

n       INSERTION(w)      QUICK(w)     INSERTION(b)     QUICK(b)

2^1     1.28e-06        1.28e-06        1.28e-06        8.53e-07

2^2     8.54e-07        4.693e-06       8.53e-07        8.54e-07

2^3     1.28e-06        2.134e-06       4.27e-07        1.28e-06

2^4     2.133e-06       2.987e-06       8.54e-07        2.56e-06

2^5     5.973e-06       6.4e-06		8.54e-07        5.12e-06

2^6     2.048e-05       1.5786e-05      1.28e-06        1.28e-05

2^7     7.7227e-05      3.6693e-05      1.707e-06       3.6693e-05

2^8     0.000317013     0.000106239     1.707e-06       9.8133e-05

2^9     0.00135253      0.000337067     3.84e-06        0.000326827

2^10    0.00524885      0.0011776       5.973e-06       0.00144811

2^11    0.0222831       0.00970496      1.1093e-05      0.00395605

2^12    0.0570048       0.0135859       1.4507e-05      0.0133308

2^13    0.210886        0.054164        2.9014e-05      0.0532092

2^14    0.827201        0.210279        5.8026e-05      0.210181

2^15    3.45448		0.835085        0.00011648      0.83804

2^16    13.0895 	3.45204 	0.00023296      3.33571

2^17    52.6793 	13.2853 	0.000463359     13.2745

2^18    210     	53.2725 	0.000934399     53.2964

2^19    841.86  	213.4   	0.00185557      212.775
~~~~

Si nota che per il caso peggiore `quick_sort` risulta molto più veloce (impiega circa un quarto del tempo rispetto a `insertion_sort`).
I tempi registrati per entrambi gli algoritmi nel primo caso variano come O(n^2), quadruplicando ogni volta che n raddoppia.

Nel best case invece si vede come `insertion_sort`  abbia un andamento asintotico di O(n), con tempi che raddoppiano al raddoppiare di n.
`quick_sort` è invece risultato avere gli stessi tempi del worst case.
