//By Bart³omiej Horiszny, 2013

#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<cstring>
using namespace std;

void rys_plan(void); 	 //rysowanie planszy
bool twoj_ruch(void);	 //ruch gracza
bool szukaj_poziom(const char[], short int&, short int&);	 //szukanie znaków w poziomie
bool szukaj_pion(char[], const char[], short int&, short int&);  //szukanie znaków w pionie
bool szukaj_ukos(char[], const char[], short int&, short int&);  //szukanie znaków po ukosie w prawo
bool szukaj_ukos2(char[], const char[], short int&, short int&); //szukanie znaków po ukosie w lewo
bool szukaj(char[], const char[], short int&, short int&);	 //³¹czy funkcje szukaj_...
void dostaw(short int, short int);  //wpisanie ruchu komputera
bool komputer(void); //ruch komputera
char tab[15][15];    //tablica planszy

int main ()
{
  //inicjacja stanu planszy
  for(int i=0;i<15;i++)
     for(int j=0;j<15;j++) tab[i][j]=' ';

  rys_plan();

  //no to gramy
  while(twoj_ruch() && komputer())
  {
	system("cls");
	rys_plan();
  }
  cout<<"\nGAME OVER\n\n";

  system("pause");
 return 0;
}
//rysownie planszy
void rys_plan(void)
{
	for(int i=14;i>=0;i--)
		{
			cout<<setw(2)<<i+1;
			cout<<"|";

		for(int j=0;j<15;j++)
			cout<<tab[i][j]<<"|";
		cout<<endl;
		}
	cout<<"   A B C D E F G H I J K L M N O "<<endl;
}


bool twoj_ruch(void)
{
  bool blad=true;
  char x; 	        //wspó³rzêdna x pola
  short int y; 		//wspó³rzêdna y pola
  cout<<"Gracz-x\n";
  cout<<"Komputer-o\n";
  cout<<"Podaj wspolrzedne komorki np. A7."<<endl<<"\nJesli chcesz wyjsc, wpisz \"X\"i zatwierdz.\n";
  do
  {
     cin>>x;		//wprowadzenie  wspó³rzêdnych punktu gracza
     x=toupper(x);	//wszystkie litery du¿e
     if(x=='X') break;
     cin>>y;
     if(x<'A' || x>'O' || y<1 || y>15) cout<<"\nBledne dane, jeszcze raz\n";
     else if(tab[y-1][(int)x-(int)'A']==' ') blad=false; //czy wolne pole
          else
          {
             blad=true;
             cout<<"Pole zajete! Wybierz inne.\n";
          }
  }
  while(x<'A' || x>'O' || y<1 || y>15 || blad);
  if(x!='X')
  {
    tab[y-1][(int)x-(int)'A']='x'; // przypisanie 'x' do pola
    return true;
  }
  else return false;
}
//szukanie w poziomie
bool szukaj_poziom(const char wzor[], short int &wspx, short int &wspy)
{
	char tab5[6];
    short int ile;
	bool jest5= false;

	ile=strlen(wzor);		//d³ugosæ ³añcucha znaków
	for(short int i=0;i<15;i++)	//poszukiwanie wzorca na planszy
		{											
	       	 for(short int j=0;j<16-ile;j++)	
			{
		    	  for(int n=0;n<ile;n++) tab5[n]=tab[i][j+n];
                          tab5[ile]='\0';						// znak 0 na koñcu ³añcucha krótszego od max d³ugosci
		          jest5=jest5 ||(strcmp(tab5, wzor)==0);
		    	  if(jest5)
			  		{
                		wspy=i;
			    		wspx=j+ile-1;
              		}
            if (jest5) break;
            }
         if (jest5) break;
		}
        return jest5;
}
//szukanie w pionie
bool szukaj_pion(const char wzor[], short int &wspx, short int &wspy)
{
    short int ile;
	bool jest5= false;
	char tab5[6];

	ile=strlen(wzor);
	for(short int i=0;i<15;i++)
		{
	          for(short int j=0;j<16-ile;j++)
			{
			   for(int n=0;n<ile;n++)  tab5[n]=tab[j+n][i];
                           tab5[ile]='\0';
			   jest5=jest5 ||(strcmp(tab5, wzor)==0);
			   if(jest5)
			   {
			     wspy=j+ile-1;
			     wspx=i;
			   }
            if (jest5) break;
			}
        if (jest5) break;
		}
        return jest5;
}
//szukanie po ukosie w prawo 
bool szukaj_ukos(const char wzor[], short int &wspx, short int &wspy)
{
    short int ile;
	bool jest5= false;
	char tab5[6];

	ile=strlen(wzor);
	for(short int i=0;i<16-ile;i++)
		{
		  for(short int j=0;j<16-ile-i;j++)
	            {
				for(int n=0;n<ile;n++) tab5[n]=tab[j+i+n][j+n];
                        tab5[ile]='\0';
				jest5=jest5 ||(strcmp(tab5, wzor)==0);
				if(jest5)
					{
			   	 	wspy=j+i+ile-1;
			     	wspx=j+ile-1;
                	}
                if (jest5) break;
                }
        if (jest5) break;
		}
	if(jest5) return jest5;
	for(short int j=1;j<16-ile;j++)
		{
		  for(short int i=0;i<16-ile-j;i++)
			{
			   for(int n=0;n<ile;n++) tab5[n]=tab[i+n][i+j+n];
                           tab5[ile]='\0';
			   jest5=(jest5 || (strcmp(tab5, wzor)==0));
			   if(jest5)
			     {
				  wspy=i+ile-1;
			 	  wspx=i+j+ile-1;
                 }
            if (jest5) break;
			}
        if (jest5) break;
		}
	return jest5;
}
//szukanie po ukosie w lewo
bool szukaj_ukos2(const char wzor[], short int &wspx, short int &wspy)
{
	short int ile;
	bool jest5= false;
	char tab5[6];

	ile=strlen(wzor);
	for(short int i=0;i<16-ile;i++)
		{
		  for(short int j=14;j>i+ile-2;j--)
			{
			  for(int n=0;n<ile;n++) tab5[n]=tab[i+n-j+14][j-n];
                          tab5[ile]='\0';
                          jest5=(strcmp(tab5, wzor)==0);
                          if(jest5)
			     {
			        wspy=i+ile-j+13;
			        wspx=j-ile+1;
                 }
            if (jest5) break;
			}
        if (jest5) break;
		}
	if(jest5) return jest5;
	for(short int j=13;j>ile-2;j--)
		{
		  for(short int i=0;i<j-ile+2;i++)
			{
			  for(int n=0;n<ile;n++) tab5[n]=tab[i+n][j-n-i];
                          tab5[ile]='\0';
                          jest5=jest5 || (strcmp(tab5, wzor)==0);
                          if(jest5)
			   				{
			     		  	 wspy=i+ile-1;
			   				 wspx=j-ile-i+1;
			  			  	}
            if (jest5) break;
			}
        if (jest5) break;
		}
	return jest5;
}
//zebranie funkcji szukaj
bool szukaj(const char wzor[], short int &wspx, short int &wspy)
{
  bool wynik;
  wynik=(szukaj_poziom(wzor, wspx, wspy)
         || szukaj_pion(wzor, wspx, wspy)
         || szukaj_ukos(wzor, wspx, wspy)
         || szukaj_ukos2(wzor, wspx, wspy));
  return wynik;
}
//dostawianie o
void dostaw(short int x, short int y)
{
 tab[y][x]='o';
}

bool komputer(void)
{
 short int wspx; //wspó³rzêdna x komórki do uzupe³nienia
 short int wspy; //wspó³rzêdna y komórki do uzupe³nienia
 short int wspx1; //pomocnicza wspó³rzêdna x komórki do uzupe³nienia
 short int wspy1; //pomocnicza wspó³rzêdna y komórki do uzupe³nienia

 // algorytm komputera
 if(szukaj("xxxxx",wspx, wspy))
   	if(szukaj("oooo ",wspx, wspy))
   	{
      dostaw(wspx, wspy); // dostaw  o5 i remis
      system("cls");
      rys_plan();
      cout<<"\nNiech bedzie REMIS\n";
      return false;
   	}
   	else //koniec, pora¿ka
  	{
      system("cls");
      rys_plan();
      cout<<"\nOj, PRZEGRALEM...\n";
      return false;
  	 }
 else if(szukaj("xxxx ",wspx, wspy))
      {
        wspx1=wspx;
        wspy1=wspy;
      	if(szukaj("oooo ",wspx, wspy))
        {
           dostaw(wspx, wspy); // dostaw o5 i wygrana
	   	   system("cls");
	       rys_plan();
           cout<<"\nJuppi, WYGRALEM!\n";
           return false;
        }
        else if(szukaj("ooo ", wspx, wspy))
             {
               dostaw(wspx, wspy); //dostaw o4 i nastêpny ruch
               return true;
             }
             else
             {
               dostaw(wspx1, wspy1); //zablokuj  4x, nstêpny ruch
               return true;
             }
      }
 else if(szukaj("xxx ",wspx, wspy))
           {
             wspx1=wspx;
             wspy1=wspy;
             if(szukaj("oooo ",wspx, wspy))
             	{
                 dostaw(wspx, wspy); //dostaw o5 i wygrana
	       	     system("cls");
                 rys_plan();
                 cout<<"\nJuppi, WYGRALEM!\n";
                 return false;
             	}
             else if(szukaj("ooo ",wspx, wspy))
                  {
                   dostaw(wspx, wspy); //dostaw o4 i nastêpny ruch
                   return true;
                  }
             else if (szukaj("oo ",wspx, wspy))
                  {
                    dostaw(wspx, wspy); //dostaw o3 i nastêpny ruch
                    return true;
                  }
                  else
                  {
                     dostaw(wspx1, wspy1); //zablokuj 3x i nastêpny ruch
                     return true;
                  }
           }
 else if(szukaj("oooo ",wspx, wspy))
           {
               dostaw(wspx, wspy); // dostaw o5 i wygrana
	           system("cls");
	           rys_plan();
                   cout<<"\nJuppi, WYGRALEM!\n";
                   return false;
           }
 else if(szukaj("ooo ",wspx, wspy))
           {
                   dostaw(wspx, wspy); // dostaw o4 i nastêpny ruch
                   return true;
           }
 else if(szukaj("oo ",wspx, wspy))
           {
                   dostaw(wspx, wspy); // dostaw o3 i nastêpny ruch
                   return true;
           }
 else if(szukaj("o ",wspx, wspy))
           {
                   dostaw(wspx, wspy); // dostaw o2 i nastêpny ruch
                   return true;
           }
 else
           {
                   if (!szukaj("o ",wspx, wspy)) szukaj("x ",wspx, wspy);
                   dostaw(wspx, wspy); //dostaw o i nastêpny ruch
                   return true;
           }
}
