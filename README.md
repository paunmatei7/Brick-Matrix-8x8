# Brick-Matrix-8x8

Descriere joc: Pe prima linie a matricei, este un om care se misca stanga, dreapta, si trage in sus cu o biluta care umple
casutele de sus. Pentru usurinta jocului, jucatorul se misca automat la stanga. In momentul in care se umple o linie de leduri,
toate casutele de la linia aceea pana la linia omului dispar. In momentul in care o linie este umpluta, Scorul creste cu 1.
La un moment de timp stabilit, apare cate o linie noua, cu o configuratie random. De fiecare data cand scorul ajunge la un 
multipul de 3, timpul de spam al liniilor noi scade cu o secunda.

Omul mereu incepe la pozitia (0,4)
Omul trage mereu, se misca automat la stanga, la dreapta se misca cu comanda data de pe joystick.

Ca mesaj de inceput, apare un "HI" pentru 2 secunde.
Pe serial monitor, initial apare mesajul "Jocul a inceput", la fiecare moment de timp apare scorul jucatorului. La fiecare 
multiplu de 3 apare "next level" insemnand ca nivelul o sa apara din ce in ce mai des linii noi. In momentul in care jucatorul
pierde, apare mesajul "GAME OVER scor final x", x fiind scorul final.

cum functioneaza:

loop:
  - se efectueaza comanda
  - se verifica daca vreo linie este plina
  
  cazul 1: 
      
      - afisam "HI" pe matricea de 8x8
      
  cazul 2:  
      
      - afisam "jocul a inceput" pe serial monitor
      
  cazul 3: 
      
      - la fiecare TimpIntreLinii timp coboram matricea cu o linie
      
      - verificam dificultatea, daca scorul e multipul de 3 scade TimpIntreLinii
      
      - verificam daca jocul s-a terminat sau nu   
      
   cazul 4:
      
      - Jocul s-a terminat se afiseaza mesajul "Game over. Scor final x";
      
 mesajStart: 
      
      -afiseaza mesajul HI pe matrice
 
 mesajStartOff: 
      
      -sterge ce este pe ecranul matricei;
 
 shoot: 
       
       -momentul in care omul arunca o bila in partea de sus a matricei
 
 command:
       
       -comanda de pe joystick.
 
 checkAlive: 
       
       -verifica daca jocul s-a terminat sau nu
 
 cob: 
       
       -coboara cu o linie toata matricea formata pana in momentul acela
 
 acoperaGol: 
       
       -acopera de la linia plina pana jos toata valorile cu 0
 
 dif: 
       
       -creste sau nu dificultate daca scorul este multiplu de 3
 
