# Tema PA

- pentru inceput am deschis si citit fisierul c.in pentru a ma putea raporta la diferite teste din perspectiva cerintelor respective

Task 1

- pentru a creste eficienta, am construit o functie care atribuie jucatorilor din fiecare echipe datele citite din fisierul d.in, atribuite_juc
- aceasta functie am apelat-o apoi in momentul in care am citit si restul datelor, anume numarul de echipe, dar si, pe rand, numarul de jucatori ai fiecarei echipe si numele acesteia, adaugand la final datele retinute la inceputul unei liste
- am creat o functie speciala pentru task-ul 1, prin care sunt afisate elemntele listei, doar daca cerinta este prezenta in c.in, iar task-ul 2 nu


Task 2
- functie pentru a calcula punctajul fiecarei echipe - medie aritmetica
- folosind functiile create, se executa dupa urmatorul principiu:
	- se calculeaza cate echipe trebuie eliminate pentru a ajunge la acel 2^N
	- se calculeaza punctajul minim existent in lista dupa fiecare data cand s-au eliminat 			toate echipele cu punctajul minim anterior/initial iar numarul nu a ajuns inca la 2^N
	- se elimina echipele cu acel punctaj minim, fara a depasi pragul
	-in final, se afiseaza lista dupa eliminarea elementelor
	
Task 3
- creare coada, fiecare element continand cate o pereche de 2 echipe, plus afisarea acestora conform fisierelor r.out
- adunarea punctelor pentru echipa castigatoare
- la fiecare runda se modifica listele de castigatori si invinsi
- afisare si mutare in coada
- functii pentru a facilita afisarea conform fisierelor r.out
- in functia task3, sunt utilizate impreuna functiile create mai sus pentru facilitarea rezolvarii task-ului

Task 4
- creare bst, prin care sunt sortate echipele din lista retinuta la task3
- afisare bst

Task 5
- functii pentru inserare la stanga, respectiv la dreapta, in functie de pozitia in lista retinuta la task 4
- creare avl pentru o lista cu 2^N elemente:
	- root: elementul de pe pozitia 2^(N-1)+1
	- left: elementul de pe pozitia 2^(N-1)+1 - 2^(N-i), i=N-2 initial, apoi scade 
	- right: elementul de pe pozitia 2^(N-1)+1 + 2^(N-i)
	- ultimul nivel: un singur nod, cel mai din stanga/dreapta, fiind cel mai mic/mare element din lista
- afisare elemente de pe nivelul cerut


