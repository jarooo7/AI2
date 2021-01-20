//program demonstracyjny, kompilowany w Dev C++,
//na pocz¹tku programu za³¹czamy biblioteki i pliki naglowkowe ze zdefiniowanymi funkcjami
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
//Pliki z rozszerzeniem .h zawieraja tylko prototypy funkcji, kody znajduja
//sie w plikach o tych samych nazwach lecz z rozszerzeniem .cpp
#include "matrix.h"

//deklarujemy u¿ywanie przestrzeni nazw std, zawieraj¹cej wiele przydatnych komend,
//je¿eli nie zdeklarowalibyœmy przestrzeni nazw std, przed komendami tej przestrzeni nale¿a³oby u¿yæ zapisu std::
// np. std::cout<<"tekst";         
using namespace std;

//w funkcji main mamy nasz g³ówny program,
int main (void) {
cout<<"Program pomocniczy do cw1\n";

//definiujemy nazwe pliku, musi istnieæ w katalogu programu
string nazwap="SystemDecyzyjny.txt";

//korzystamy z funkcji umieszczonych w pliku matrix.h
// w celu znalezienia rozmiaru wczytywanego pliku,
//plik powinien byc w formacie
//6 2 5 6 1
//5 8 9 2 0
int wym2=num_rows_file(nazwap.c_str());
int wym1=num_cols_file(nazwap.c_str());

//teraz deklarujemy dynamicznie tablice do, której wczytamy nasz plik,
int rows = wym2+1;
std::string **G;
G = new std::string*[rows];
while(rows--) G[rows] = new std::string[wym1+1];

////wczytujemy tablice w postaci string, czyli jej elementy traktujemy jako stringi(ci¹gi znaków)
//wym2 to liczba wierszy
//wym1 to liczba kolumn
//G nasza tablica stringów
//nazwap.c_str() podajemy nazwe wczytywanego pliku w odpowiednim formacie do funkcji.
cout<<"\n\nNacisnij ENTER aby wczytac tablice o nazwie "<< nazwap;
getchar();
wczytywanie(wym2,wym1,G,nazwap.c_str());
//wypisujemy wczytan¹ tablicê na ekran
cout<<"\nWypisujemy na ekran wczytana tablice\n\n";
for(int i=1;i<wym2+1;i++){
  for(int j=1;j<wym1+1;j++){
    cout<<" "<<G[i][j];
  }
  cout<<"\n";
} 


//******************************************************
//MIEJSCE NA ROZWIAZANIE 
	char tab1[wym2+1][wym1];
	for(int i=0;i<wym2+1;i++){
		for(int j=0;j<wym1;j++){
			tab1[i][j]='p';
		}	
	}
	bool a=true;

	for(int i=1;i<wym2+1;i++){
		for(int j=1;j<wym1;j++){
			a=true;
			for(int k=1;k<wym2+1;k++){
				if(G[i][j]==G[k][j]&&tab1[k][j]=='p'){
					tab1[k][j]='k';
					if(G[i][wym1]!=G[k][wym1]){
						a=false;	
					}
				}
			}
			for(int k=1;k<wym2+1;k++){
				if(tab1[k][j]=='k'){
					if(a){
						tab1[k][j]='s';	
					}	
					else{
						tab1[k][j]='p';	
					}
				}
			}	
		}	
	}

	for(int i=1;i<wym2+1;i++){
  		for(int j=1;j<wym1;j++){
    		cout<<" "<<tab1[i][j];
 		}
  		cout<<"\n";
	} 
	cout<<"\n\nSekwencyjne pokrywanie\n\nRzad I \n\n";
	int	l=0;
	int r=1;
	for(int j=1;j<wym1;j++){
		for(int i=1;i<wym2+1;i++){
  			if(tab1[i][j]=='s')
  			{
  				l=0;
  				for(int k=1;k<wym2+1;k++){
  					if(G[i][j]==G[k][j]){
	 	 				l++;
	  					tab1[k][j]='z';
	 	 			}
  				}	
    			cout<<"R"<<r<<"\t(a"<<j<<"="<<G[i][j]<<")=>d="<<G[i][wym1]<<"""\t["<<l<<"]\n";
    			r++;
  			}
  		}
	} 
	for(int i=1;i<wym2+1;i++){
		for(int j=1;j<wym1;j++){
  			if(tab1[i][j]=='z')
  			{
   				for(int k=1;k<wym1;k++){
   					tab1[i][k]='x';
   				}
  			}
		}
	}
 	for(int i=1;i<wym2+1;i++){
  		for(int j=1;j<wym1;j++){
    		cout<<" "<<tab1[i][j];
  		}
  		cout<<"\n";
	}	 
  


 
//KONIEC MIEJSCA NA ROZWIAZANIE  
//******************************************************

cout<<"\n\nPrzykladowa konwersja string do double i operacja na skonwertowanych wartosciach";
getchar();
double temp1,temp2;
double wynik;
//wrzucam do temp1 i temp2 wartosci G[1][1],G[1][2] z mojej tablicy G i dodaje te wartoœci;
//pamietamy, ze wartosci tablicy sa typu string, stad zanim zaczniemy wykonywac operacje
// trzeba je przekonwertowac do odpowiedniego typu,
// w naszym przypadku potrzebujemy wartosci ca³kowitych stad uzywamy string_to_int,
temp1=string_to_double(G[1][1]);
temp2=string_to_double(G[1][2]);
wynik=temp1+temp2;

//wyswietlamy wynik
cout<<"\n"<<temp1<<" + "<<temp2<<" = "<<wynik;

//funkcja zapisuje tablice stringów do pliku, podajemy
string nazwap2="plik_do zapisu.txt";
cout<<"\n\nNacisnij ENTER aby wykonac demonstracyjny zapis pliku o nazwie "<<nazwap2;
getchar();
zapis(wym2,wym1,G,nazwap2.c_str());

//na koniec czyœcimy pamiêæ po naszej tablicy
for(int i=0;i<wym2+1;i++)
{delete[] G[i];}//czyscimy wiersze
delete[] G;//zwalniamy tablice wskaznikow do wierszy

cout<<"\n\nNacisnij ENTER aby zakonczyc";
getchar();

//na koniec nasza funkcja zwraca wartoœæ 0 i program siê koñczy
return 0;
}
