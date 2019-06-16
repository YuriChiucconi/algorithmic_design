# BSTs and RBTs
La classe `BST` era stata già creata per sostenere la prima parte dell'esame col professor Sartori.
La funzione richiesta negli esercizi è quella chiamata `RemoveNode`.
Per ogni altra informazione sulla classe rimando al report già realizzato.

https://github.com/YuriChiucconi/Advanced-Programming/blob/master/cpp_exam/Report.md

La classe `RBT` è stata scritta a partire da quella precedente ma modificando la struttura dei nodi (`struct Node`) in modo da contenere un `bool` che rappresenti il colore del nodo.

Il metodo `AddLeaf`, che serve per aggiungere un nodo all'albero, è stato modificato dal precedente in modo da tener conto delle regole per la costruzione dei RBTs.

La ricerca attraverso le chiavi, come nella classe `BST`, viene effettuata dalla funzione `find`.

Per motivi di tempo non ho invece realizzato una funzione per rimuovere un nodo da un RBT, funzione che ovviamente dovrebbe tener conto delle regole imposte a questi alberi.

A titolo di esempio, nel file `RBT.png` è riportato l'output che si ottiene eseguendo il seguente codice
~~~~
RBT<int, int> t;
	
for (int i = 0; i < 12; i++)
{
	t.AddLeaf(i, 0);
}
t.PrintInOrder();
~~~~