#include <iostream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ios>
#include <conio.h>
#include <fstream>

using namespace std ;
// -------------------------------------------------FUNKCJE-------------------//
//deklaracje
void WybierzMetode(double przekroj[][2], int &rozmiar, double &max, double &min, double tablica_num[][2], char tablica_znak[][14], char folder_domyslny[100], char folder_odczytu[100], char folder_zapisu[100]) ;
void SortujTablice(double tablica[][2], int rozmiar) ;
bool CzyPlik(char plik[]) ;
//definicje
int DlugoscWyrazu(char wyraz[])
{
	int nr_znak ;
	int idw = 0 ;
	do
		{
			nr_znak = (int) wyraz[idw] ;
			idw++ ;
		}
		while(nr_znak != 0) ;
	return idw - 1 ;
}


void WyswietlTablice(double tablica[][2],int rozmiar)
{
		printf("\n______________________________") ;
		printf("\n||    ||         ||         ||") ;
		printf("\n||    ||ODLEGLOŒÆ||  RZÊDNE ||") ;
		printf("\n||____||_________||_________||") ;
	
	for (int wytab = 0 ; wytab < rozmiar ; wytab++)
		{
				printf("\n||%3u || %7.2f || %7.2f ||",wytab+1,tablica[wytab][0],tablica[wytab][1]);
		}
		printf("\n||____||_________||_________||\n") ;
}// -------------------------------------funkcja wyswietla tablice dwuwymiarowe w zaleznosci od liczby wierszy


int DoubleToChar(double liczba, char wyraz[50])
{	
		int dlug = sprintf(wyraz,"%.2f", liczba) ;
		return dlug ;
}// ---funkcja konwertuje liczby na tablice znakowe char i zwraca wartosc ich dlugosci

int DodajPunkt (double tablica[][2], int &wi, double &max, double &min )
{
	system("cls");
	int klawisz;
	if (wi > 0)
	{	

		SortujTablice(tablica, wi + 1) ;
		WyswietlTablice(tablica,wi);
	}
	cout << "\n\nPUNKT: " << wi + 1 ;
	cout << "\nO: " ;
	cin >> tablica[wi][0] ;
	cout << "R: " ;
	cin >> tablica[wi][1] ;
	
	if	(wi == 0)
		{
			max = tablica[0][1];
			min = tablica[0][1];
		}
	else
		{
		  if ( tablica[wi][0] != 0 )
		  	{
			
			if (tablica[wi][1] > max )
				max = tablica[wi][1] ;
			if (tablica[wi][1] < min )
				min = tablica[wi][1] ;
			}	
		}
	wi++ ;
}// -------------------------------------------funkcja wczytuje punkty przekroju z klawiatury

void PrzepiszTablice (double tablica_we[][2], double tablica_wy[][2], int wi)
{
	for (int wyi = 0 ; wyi < wi - 1 ; wyi++)
		{
			tablica_wy[wyi][0] = tablica_we[wyi][0] ;
//cout << "\ntablica_we (" << tablica_we[wyi][0] << ") -----> tablica wy (" << tablica_wy[wyi][0] << ")\n" ;
			tablica_wy[wyi][1] = tablica_we[wyi][1] ;
//cout << "tablica_we (" << tablica_we[wyi][1] << ") -----> tablica wy (" << tablica_wy[wyi][1] << ")\n" ;
			
			
		}
//	system("pause") ;
}// ----------------------------funkcja przepisuje wartosci z tablicy do tablicy

void ZmienUstawienia (double &cz_wys, int &skala_pion, int &skala_poziom, double &ppor, char nazwa[],double min, char plik_ustawien_rysunkowych[141] , double najmodl)
{
	FILE * draw_set ;
	
	if (CzyPlik(plik_ustawien_rysunkowych) == 1)
		{
			cout << "\nznaleziono plik\n" ;
			char tmp_cw[15];
			char tmp_spi[10];
			char tmp_spo[10];
			char tmp_ppor[7];
			draw_set = fopen(plik_ustawien_rysunkowych,"r") ;
			fscanf(draw_set,"%s",tmp_cw) ;
			cz_wys = atof(tmp_cw);
			fscanf(draw_set,"%s",tmp_spi) ;
			skala_pion = atof(tmp_spi) ;
			fscanf(draw_set,"%s",tmp_spo) ;
			skala_poziom = atof(tmp_spo) ;
			fscanf(draw_set,"%s",tmp_ppor) ;
			ppor = atof(tmp_ppor) ;
			fscanf(draw_set,"%s",nazwa) ;
			fclose(draw_set) ;
		}
	
	int nr_us ;
	do
	{
	system("cls");
	cout << "BIEZACE USTAWIENIA" << endl ;
	cout << "\n1 - wysokosc czcionki:\t" << cz_wys << endl ;
	cout << "2 - skala w pionie: \t" << skala_pion << endl ;
	cout << "3 - skala w poziomie:\t" << skala_poziom << endl ;
	cout << "4 - poziom porownawczy:\t" << ppor << endl ;
	cout << "5 - nazwa przekroju:\t" << nazwa << endl ;	
	cout << "0 - zapisz ustawienia" << endl ;
	cout << "\n\nWYBIERZ NUMER OPCJI DO ZMIANY, LUB \"0\" - ZAPISZ USTAWIENIA " ;
	cin >> nr_us ;
	switch (nr_us)
		{
			case 1 :
				cout << "przy biezacej skali sugerowana najwieksza czcionka\n" ;
				cout << "nie powinna przekraczac " << ((najmodl*1000)/skala_poziom) << " pixeli\n" ;
				cout << "wysokosc czcionki [px] : " ;
				cin >> cz_wys ;	
				break ;
			case 2 :
				cout << "skala w pionie: " ;
				cin >> skala_pion ;
				break ;
			case 3 :
				cout << "skala w poziomie: " ;
				cin >> skala_poziom ;
				break ;
			case 4 :
				cout << "poziom porownawczy [m n.p.m.] : (najnizsza wysokosc - " ;
				cout << min << "m n.p.m. ) " ;
				cin >> ppor ;
				break ;
			case 5 :
				cout << "nazwa przekroju: " ;
				cin >> nazwa ;
				break ;
			case 0 :
				{
				break ;
				}
			default :
				cout << "podano niewlasciwy numer" ;
				break ;
		}
	} 
	while ( nr_us != 0 ) ;

	draw_set = fopen(plik_ustawien_rysunkowych,"w") ;
	fprintf(draw_set,"%.1f\n",cz_wys) ;
	fprintf(draw_set,"%u\n",skala_pion) ;
	fprintf(draw_set,"%u\n",skala_poziom) ;
	fprintf(draw_set,"%.2f\n",ppor) ;
	fprintf(draw_set,"%s\n",nazwa) ;
	fclose(draw_set) ;
	//zapisywanie ustawien do pliku tmp
			
}// ----------------------------------------funkcja zmienia ustawienia rysunkowe

void SkalujTablice(double tab_we[][2], double tab_wy[][2],int wymiar_tablicy, int skala_pion, int skala_poziom, double ppor)
{
	for (int ist = 0 ; ist < wymiar_tablicy ; ist++)
		{
			tab_wy[ist][0] = 1000 * tab_we[ist][0] / skala_poziom ;
			tab_wy[ist][1] = 1000 * (tab_we[ist][1] - ppor) / skala_pion ;
		}
}// ----------------------------------------funkcja skaluje tablice wg zadanej skali i zapisuje jej kopie

void ZapiszTablice(double tablica[][2], int rozmiar, char plik[300])
{
	FILE * dane_tmp ;
	dane_tmp = fopen(plik,"w");
	for (int zi = 0 ; zi < rozmiar - 2 ; zi++)
		{
			fprintf(dane_tmp,"%.2f,%.2f\n",tablica[zi][0],tablica[zi][1]);	
		}
			fprintf(dane_tmp,"%.2f,%.2f",tablica[rozmiar-2][0],tablica[rozmiar-2][1]);
	fclose(dane_tmp);
}//-----------------------------------------funkcja zapisuje do pliku dane ostatio wprowadzonego przekroju

void WczytajTablice(char tablica[][14], double tablica_num[][2], double &max, double &min, int &rozmiar, char sciezka_do_pliku[50])
{
	FILE * plik_we ;
	char znak ;
	int nr_znak, nr_znak2, nr_znak3 ;
	char bufor[10];
	znak = '1' ;
	plik_we = fopen(sciezka_do_pliku,"r");
	int io = 0 ;
		while ((nr_znak != 2)&&(znak != EOF))
			{
				int ib = 0 ;
				int ip = 0 ;
				fscanf(plik_we,"%s",tablica[io]);
					do
						{
							bufor[ib] = tablica[io][ip];							
							nr_znak = (int) tablica[io][ip];
							
							ip++ ;
							ib++ ;
							nr_znak2 = (int) tablica[io][ip+1];
//							cout << "\nindeks znaku to: " << ip << "\tnumer znaku to: " << nr_znak << endl ;
							if ((nr_znak == 2)||((nr_znak == 1)&&(ip == 1)))
								{
//									cout << "\nzatrzymano w pierwszej petli\n" ;
									break ;
								}
						} while ((nr_znak != 44)&&(nr_znak != 59)&&(nr_znak != 32));
						if ((nr_znak == 2)||((nr_znak == 1)&&(ip == 1)))
								{
//									cout << "\nzatrzymano w drugiej petli\n" ;
									break ;	
								}
//						cout << "\nznak separacji to: " << nr_znak << endl ;
						tablica_num[io][0] = atof(bufor);
						ib = 0 ;
						
					
					do
						{
							bufor[ib] = tablica[io][ip];
							nr_znak = (int) tablica[io][ip];
							ip++ ;
							ib++ ;
						} while (nr_znak != 0);
//						cout << "\nkoniec lini, znak nr: " << nr_znak << endl ; 
						tablica_num[io][1] = atof(bufor);				
				
									
	if	(io == 0)
		{
			max = tablica_num[0][1];
			min = tablica_num[0][1];
		}
	else
		{
		  	if ( tablica_num[io][0] != 0 )
		  	{
			
			if (tablica_num[io][1] > max )
				max = tablica_num[io][1] ;
			if (tablica_num[io][1] < min )
				min = tablica_num[io][1] ;
			}
		}
				io++ ;
				rozmiar = io + 1 ;
				znak = fgetc(plik_we);
}
//system("pause") ;
}//-----------------------------------------funkcja wczytuje tablice z pliku



void xy (double x, double y, FILE * plik)
{
		fprintf(plik,"%.2f,%.2f\n", x, y) ;	
}// ----------------------------------funkcja wypisujaca wspolrzedne do rysunku

void linia(double odX, double odY, double doX, double doY, FILE * plik)
{
	fprintf(plik,"_line\n");
	xy(odX,odY,plik) ;
	xy(doX,doY,plik) ;
	fprintf(plik,"\n");
}// ----------------------------------funkcja rysujnie linie od wspolrzednych do wspolrzednych

void tekst(double wstawX, double wstawY, double wysokosc, double katObrotu, char tresc[], FILE * plik)
{
	fprintf(plik, "_text\n");
	xy(wstawX, wstawY, plik) ;
	fprintf(plik, "%.1f\n", wysokosc );
	fprintf(plik, "%.2f\n", katObrotu) ;
	fprintf(plik, " %s\n", tresc);
}// ----------------------------------funkcja rysujaca obszar tekstowy wg zadanych parametrow


void rysuj_1(double cz_wys, double ppor, char nazwa[],double tab_wsp[][2], double tab_skala[][2],int ni,double Max, int skalaPI,char sciezka[100])
{
cout << "tworzenie skryptu Autocad'a...\n" ;
	//----pomocnicze wspolrzedne---
	double tr = 5*cz_wys ; // ------------------- Table Row 
	double fc = 25*cz_wys + cz_wys*1/12 ; // ---- First Column
	double di = 0.3*cz_wys; // ------------------ DIstance
	char rzedne[] = "RZEDNE" ;
	char odleglosci[] = "ODLEGLOSCI" ;
	double sMax = 1000*(Max - ppor) / skalaPI ;
	char nazwa_pliku[40] ;
	sprintf(nazwa_pliku,"%s\\%s.scr",sciezka,nazwa) ; 
	//-------------------------------
	FILE * skrypt ;
	skrypt = fopen(nazwa_pliku,"w") ; // otwarcie pliku
	//---------------------------wylaczenie przyciagan, siatki, orto, itp
	fprintf(skrypt, "_snap\n_off\n");
	fprintf(skrypt, "_grid\n_off\n");
	fprintf(skrypt, "_ortho\n_off\n");
	fprintf(skrypt, "_osmode\n0\n");	
	//---------------------------tabelka itp---------------//
	fprintf(skrypt, "_text\n");
	xy(-fc, di, skrypt) ;
	fprintf(skrypt, "%.1f\n", cz_wys );
	fprintf(skrypt, "%.2f\n", 0.0) ;
	fprintf(skrypt, " Poziom porownawczy %.2f m n.p.m.\n", ppor);
	tekst(-fc,-tr+di,cz_wys,0.0,rzedne,skrypt);
	tekst(-fc,-2*tr+di,cz_wys,0.0,odleglosci,skrypt);
	linia(-fc,0,-fc,-2*tr,skrypt);
	char odleglosc[14] ;
	char rzedna[14] ;
	for (int ir = 0 ; ir < ni - 1 ; ir++)
		{
			sprintf(odleglosc,"%.2f",tab_wsp[ir][0]);
			sprintf(rzedna,"%.2f",tab_wsp[ir][1]);
			tekst(tab_skala[ir][0],-2*tr,cz_wys,90,odleglosc,skrypt);//---rysuje pole tekstowe z odleglosciami		
			tekst(tab_skala[ir][0],-tr,cz_wys,90,rzedna,skrypt);//-----rysuje pole tekstowe z rzednymi
			linia(tab_skala[ir][0],0,tab_skala[ir][0],-2*tr,skrypt);
			linia(tab_skala[ir][0],0,tab_skala[ir][0],tab_skala[ir][1],skrypt);			
		}
		for (int ir2 = 0 ; ir2 < ni - 2 ; ir2++)
			{
				linia(tab_skala[ir2][0],tab_skala[ir2][1],tab_skala[ir2+1][0],tab_skala[ir2+1][1],skrypt);	
			}
	linia(-fc,0,tab_skala[ni-2][0],0,skrypt);
	linia(-fc,-tr,tab_skala[ni-2][0],-tr,skrypt);
	linia(-fc,-2*tr,tab_skala[ni-2][0],-2*tr,skrypt);
	tekst(0,sMax,3*cz_wys,0,nazwa,skrypt);
	
	//----------------------------------------------------------------
	
	
	fprintf(skrypt, "_zoom\n_e\n"); // ----wysrodkowanie widoku	
	fclose(skrypt) ; // zamkniecie pliku			
}//-------------------------------------------funkcja pisze skrypt do AutoCad'a

void SortujTablice(double tablica[][2], int rozmiar)
{
	double bufor_odl, bufor_rze ; // bufory do przetrzymywania przepisywanych wartosci
	bool poprawka ; // sprawdza czy zostaly wykonane jakies operacje przepisania
	do 
		{
			poprawka = 0 ;
	for (int is = 0 ; is < rozmiar - 2 ; is++)
			{
				if 	(tablica[is][0] > tablica[is+1][0])
					{
						bufor_odl = tablica[is][0] ;
						bufor_rze = tablica[is][1] ;
						tablica[is][0] = tablica[is+1][0] ;
						tablica[is][1] = tablica[is+1][1] ;
						tablica[is+1][0] = bufor_odl ;
						tablica[is+1][1] = bufor_rze ;
						poprawka = 1 ;
					}
			}
		} while (poprawka == 1) ;
}//-------------------------------------------funkcja sortuje elementy tabilcy wg rosnacych odleglosci

bool CzyPlik(char plik[])
{
	bool istnieje ;
	fstream bufor_pliku ;
	bufor_pliku.open(plik,ios::in) ;
	if ( bufor_pliku.good() )
		{
		istnieje = 1 ;
//		cout << "plik istnieje\n" ;
		}
	else
		{
		istnieje = 0 ;	
//		cout << "plik nie istnieje\n" ;
		}
	return istnieje ;
}//-------------------------------------------funkcja sprawdza czy plik istnieje

void metoda_klawiatura(double tablica_num[][2], int &ni, double &r_max, double &r_min)
{
	do
		{
		DodajPunkt (tablica_num, ni, r_max, r_min ) ;
			
			if ( (ni > 1)&&(tablica_num[ni-1][0] == 0) )
				break ;
		}
	while ( true ) ;	
}// ------------------------------------------funkcja wprowadzania punktow przekroju z klawiatury

void WybierzPlik(char plik[], char tablica_znak[][14], double tablica_num[][2], int &rozmiar, double &maksimum, double &minimum, char folder_domyslny[], char folder_odczytu[], char folder_zapisu[])
{
	if (CzyPlik(plik) == 1 )
		{
		WczytajTablice(tablica_znak, tablica_num, maksimum, minimum, rozmiar,plik);
		system("cls") ;
		}
	else
		{
		system("cls") ;
		cout<< "Nie znaleziono pliku!!!" << endl ;
		system("pause") ;
		system("cls") ;
		WybierzMetode(tablica_num, rozmiar, maksimum, minimum, tablica_num, tablica_znak, folder_domyslny, folder_odczytu, folder_zapisu) ;
		}
}//-------------------------------------------funkcja wyboru pliku do wczytania

void UstawieniaGlowne(char folder_odczytu[100],char folder_zapisu[100],char folder_domyslny[100], double tablica_num[][2], int &rozmiar, double &max, double &min, double tablica_tmp[][2], char tablica_znak[][14])
{
	char nr ;
	char f_od[100] ; 
	char f_za[100] ;
	FILE * ustawienia_rw ;
	do{
	system("cls") ;
	cout << "\n\n\nOPCJE USTAWIENIA ODCZYTU/ZAPISU PLIKOW:\n\n\n " ;
	cout << "\n[1] - zmien folder odczytu plikow,\n - biezacy : " << folder_odczytu ;
	cout << "\n\n[2] - zmien folder zapisu plikow,\n - biezacy: " << folder_zapisu ;
	cout << "\n\n[0] - zapisz biezace ustawienia" ;
	cout << "\n\n: " ;
	cin >> nr ;
	
		char stworz[141] ;
		switch (nr)
		{
		case '1' :
			{
			cout << "\npodaj nowa pelna sciezke dostepu do katalogu z przekrojami:\n" ;
			cin >> f_od ;	
			folder_odczytu = f_od ;
			cout << "\nzapisano nowa sciezke" ;
			sprintf(stworz,"md %s",f_od);
			system(stworz) ;
			break ;
			}
		case '2' :
			{
			cout << "podaj nowa plena sciezke dostepu do katalogu zapisu prekrojow:\n" ;
			cin >> f_za ;
			folder_zapisu = f_za ;
			cout << "\nzapisano nowa sciezke" ;
			sprintf(stworz,"md %s",folder_zapisu);
			system(stworz) ;
			break ;
			}
		case '0' :
			{
				ustawienia_rw = fopen("c:\\przekroj_tmp\\default_rw.txt","w");
					fprintf(ustawienia_rw,"%s\n",folder_odczytu);
					fprintf(ustawienia_rw,"%s",folder_zapisu);
				fclose(ustawienia_rw);
				cout << "\nustawienia zapisano\n" ;
				system ("pause") ;
				system ("cls") ;
				WybierzMetode(tablica_num, rozmiar, max,min,tablica_tmp,tablica_znak,folder_domyslny, folder_odczytu, folder_zapisu) ;
				
				break ;
			}
		default :
			{
			cout << "\nNieprawidlowy numer opcji - sprobuj ponownie!\n" ;
			system("pause") ;
			system("cls") ;
			break ;
			}
		}
		
	
	}while (nr != '0') ;
		
		
}// --------------------------------------funkcja edycji ustawien glownych

void WybierzMetode(double tablica_num[][2], int &rozmiar, double &max, double &min, double tablica_tmp[][2], char tablica_znak[][14],char folder_domyslny[100], char folder_odczytu[100], char folder_zapisu[100])
{
	char default_rw[100] = "c:\\przekroj_tmp\\default_rw.txt" ;
	FILE * ustawienia_rw ;
	
	if (CzyPlik(default_rw) == 0 )
		{
			folder_odczytu = folder_domyslny ;
			folder_zapisu = folder_domyslny ;
			system("md c:\\przekroj_tmp") ;
		}
//	else
//		{
//			ustawienia_rw = fopen(default_rw,"r") ;
//			fscanf(ustawienia_rw,"%s",folder_odczytu) ;
//			fscanf(ustawienia_rw,"%s",folder_zapisu) ;
//			fclose(ustawienia_rw) ;
//		}
	cout << "\n\n\nWYBIERZ OPCJE:\n\n\n" ;
	cout << "Wczytanie ostatnio uzywanego pliku\t[1]\n" ;
	cout << "\nWczytanie z pliku CSV lub txt\t\t[2]\n\n" ;
	cout << "Wprowadzenie z klawiatury\t\t[3]\n\n" ;
	cout << "Zmiana ustawien odczytu/zapisu\t\t[0]\n\n" ;
	cout << "nr opcji: " ;
	char metoda_wprowadzania ;
	cin >> metoda_wprowadzania ;
	switch (metoda_wprowadzania)
		{
			case '1' :
			{
				char plik[150] = "c:\\przekroj_tmp\\tmp.txt" ;
				WybierzPlik(plik, tablica_znak, tablica_num, rozmiar, max, min, folder_domyslny, folder_odczytu, folder_zapisu);
				break;	
			}	
			case '2' :
			{
				char nazwa_pliku[40] ;
				char folder[100] ;
				sprintf(folder,"%s",folder_odczytu) ;
				char plik[150] ;
				cout << "\n\numiesc plik w folderze\n" << folder << "\\\ni podaj jego nazwe wraz z rozszerzeniem:\n" ;
				cout << folder << "\\" ;
				cin >> nazwa_pliku ;
				sprintf(plik,"%s\\%s",folder,nazwa_pliku) ; 
				cout << "\n" ;
				cout << "pelna sciezka do pliku to:\n " ;
				cout << plik ; 
				cout << endl ;
				WybierzPlik(plik, tablica_znak, tablica_num, rozmiar, max, min, folder_domyslny, folder_odczytu, folder_zapisu);
				break;	
				
			}
			case '3' :
			{
				metoda_klawiatura(tablica_num,rozmiar, max, min) ;
				break ;
			}
			case '0' :
			{
				UstawieniaGlowne(folder_odczytu, folder_zapisu, folder_domyslny, tablica_num, rozmiar, max, min, tablica_tmp, tablica_znak) ;
				break ;
			}
			default :
				{
				cout << "Nieprawidlowy numer" << endl ;
				system("pause");
				system("cls");
				WybierzMetode(tablica_num, rozmiar, max, min, tablica_tmp, tablica_znak, folder_domyslny, folder_odczytu, folder_zapisu) ;
				break ;	
				}
		}
		FILE * ustawienia_rwm ;
		ustawienia_rwm = fopen("c:\\przekroj_tmp\\default_rw.txt","w");
		fprintf(ustawienia_rwm,"%s\n",folder_odczytu) ;
		fprintf(ustawienia_rwm,"%s",folder_zapisu) ;
		fclose(ustawienia_rwm) ;
		
		//cout << "\nTablice posortowano!!! \n" ;
		//system("pause");
}// ------------------------------------------funkcja wybiera metode wprowadzania danych przekroju

void EdytujIstniejacy(double tablica[][2], int rozmiar, double &maksimum, double &minimum, int &nr_punktu)
{
system("cls");
	if (rozmiar > 0)
	{	

		SortujTablice(tablica, rozmiar ) ;
		WyswietlTablice(tablica,rozmiar );
		cout << "\n\nPodaj nr punktu do edycji: " ;
		cin >>  nr_punktu ;
	}
	
	cout << "\n\nPUNKT: " << nr_punktu ;
	cout << "\nO: " ;
	cin >> tablica[nr_punktu-1][0] ;
	cout << "R: " ;
	cin >> tablica[nr_punktu-1][1] ;
	
	if	(rozmiar == 0)
		{
			maksimum = tablica[0][1];
			minimum = tablica[0][1];
		}
	else
		{
		  if ( tablica[rozmiar][0] != 0 )
		  	{
			
			if (tablica[nr_punktu-1][1] > maksimum )
				maksimum = tablica[nr_punktu-1][1] ;
			if (tablica[nr_punktu-1][1] < minimum )
				minimum = tablica[nr_punktu-1][1] ;
			}	
		}
		
}//---------------funkcja edycji istniejacych punktow przekroju

void EdytujTablice(double tablica[][2],int &rozmiar, double &maksimum, double &minimum)
{
	char metoda_edycji ;
	do
	{
	int nr_pkt = 999 ;
	cout << "Wybierz metode edycji przekroju: \n" ;
	cout << "\n[D] - dodaj nowy punkt\n\n" ;
	cout << "[E] - edytuj istniejacy punkt\n\n" ;
	cout << "[K] - kontynuuj do ustawien rysunku\n\n" ;
	cout << "metoda: " ;
	cin >> metoda_edycji ;
		if ((int) metoda_edycji == 69) 
			metoda_edycji = 'e' ;
		if ((int) metoda_edycji == 68) 
			metoda_edycji = 'd' ;
		if ((int) metoda_edycji == 75)
			metoda_edycji = 'k' ;
		
		switch(metoda_edycji )
			{				
				case 'd' :
					rozmiar = rozmiar - 1 ;
					metoda_klawiatura(tablica,rozmiar, maksimum, minimum);
					
					break ;
				case 'e' :
					{
					do
					{
					EdytujIstniejacy(tablica, rozmiar - 1 , maksimum, minimum, nr_pkt) ;
					} while (nr_pkt != 0) ;
					break ;					
					}
				case 'k' :
					break ;
				default :
					cout << "Nieprawidlowe oznaczenie metody\n wybierz ponownie! " ;
					system("pause");
					EdytujTablice(tablica, rozmiar, maksimum, minimum) ;
					break ;
				
			}
		} while(metoda_edycji != 'k') ;
}// --------------------------------------funkcja wyboru rodzaju edycji tablicy

double ZnajdzNajmniejszaOdleglosc(double tablica[][2], int rozmiar)
{
	double minodl ;
	minodl = ( tablica[1][0] - tablica[0][0] );
	for (int znoi = 1 ; znoi < rozmiar - 2 ; znoi++)
		{
			if ((tablica[znoi + 1][0] - tablica[znoi][0]) < minodl )
			{
			minodl = tablica[znoi + 1][0] - tablica[znoi][0] ;
			}
		}
	return minodl ;
}// --------------------------------------tablica szuka najmniejszej odleglosci miedzy punktami przekroju w celu ustalenia minimalnej zalecanej czcionki...

// --------------------------------------------KONIEC-FUNKCJI---------------//
int main ()
{
	char f_default[100] = "c:\\przekroj_tmp" ;
	char f_read[100] = "c:\\przekroj_tmp" ;
	char f_write[100] = "c:\\przekroj_tmp" ;
	char plik_ust_rys[141] = "c:\\przekroj_tmp\\default_draw.txt" ;
	
	

			double c_w = 1.5 ; //wysokosc czcionki
			int s_pi = 100 ;   //skala pionowa
			int s_po = 200 ;   //skala pozioma
			double pp = 0 ;    //poziom porownawczy
			char pnazwa[150] = "Przekroj" ;
	
	int n, ni ;
	ni = 0 ;
	double r_min = 0 ;
	double r_max = 0 ;
	double tab[200][2] ;				//---------tablica z danymi wejsciowymi
	double tab_tmp[200][2];
	char dane_z_pliku[200][14]; 		//---------tablica dla danych z pliku tekstowego
	cout << "Program \"Przekroj\" sluzy do wczytywania danych \nprzekroju (koryta rzeki, terenu)" ;
	cout << "i tworzenia skryptu\nrysujacego ten przekroj w programie AutoCad\n " ;		
	WybierzMetode(tab, ni, r_max, r_min, tab_tmp, dane_z_pliku, f_default, f_read, f_write) ; // --------wybiera metode wprowadzania danych przekroju do programu
			FILE * ustawienia_mrw ;
			ustawienia_mrw = fopen("c:\\przekroj_tmp\\default_rw.txt","r") ;
			fscanf(ustawienia_mrw,"%s",f_read) ;
			fscanf(ustawienia_mrw,"%s",f_write) ;
			fclose(ustawienia_mrw) ;
	double tab_k[ni][2];				// tablica o wymiarze liczby przekrojow
	double tab_skal[ni][2]; 			// tablica z wymiarami zeskalowanymi do skali rysunku - w poziomie i w pionie - w odniesieniu do poziomu porownawczego
cout << "odczytany wymiar tablicy wynosi: " << ni << endl ;
	PrzepiszTablice(tab, tab_k, ni) ;						// przepisuje tablice do nowej o sformatowanym wymiarze
cout << "\nPrzepisano na nowa tablice:\n" ;
	SortujTablice(tab_k,ni) ;
	WyswietlTablice(tab_k,ni-1) ;
//	system("pause");			
	EdytujTablice(tab_k,ni,r_max,r_min);
//	system("pause");
	double nodl = ZnajdzNajmniejszaOdleglosc(tab_k, ni) ;
	ZmienUstawienia (c_w, s_pi, s_po, pp, pnazwa, r_min, plik_ust_rys, nodl) ;	//zmienia ustawienia rysunkowe - czcionka, nazwa rysunku itp
	SkalujTablice(tab_k, tab_skal,ni,s_pi,s_po,pp) ;		//tworzy tablice wspolrzednych do rysunkub_skal, ni,r_max,s_pi,f_write) ;		//tworzy skrypt od stworzenia rysunku w autocadzie
	char out_tmp[150];
	sprintf(out_tmp,"%s\\tmp.txt",f_default) ; 
	ZapiszTablice(tab_k,ni, out_tmp);
	char out_save[300];
	sprintf(out_save,"%s\\%s.txt",f_write,pnazwa);
cout << "\nout_save - pelna sciezka do pliku ma postaæ: \n" ;
cout << out_save << endl ;
	ZapiszTablice(tab_k,ni, out_save);
cout << "zapisano tablice" << endl ;
	system ("pause");
	rysuj_1 (c_w, pp, pnazwa, tab_k, tab_skal, ni,r_max,s_pi,f_default) ;

}
