//Inlämningsuppift 4B
//Skriven av Ludvig Westerholm
//2023-08-24
// Hanterar fallet med 26 bokstäver A-Z

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:

// Tips: Använd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// istället för värdena 26 och 4 i programmet.
const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP innehåller bokstavsfrekvensen i %
// för fyra språk. TOLK_HJALP[0][0] är frekvensen av
// bokstaven a för engelska. TOLK_HJALP[0][25] är frekvensen av
// bokstaven z för engelska.
// Arrayen är en GLOBAL KONSTANT och skall alltså ej skickas
// som parameter till den funktion som behöver den.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
       {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
         7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
         0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
         1.89,0.03},
        {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
         7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
         1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
         0.30,0.15},
        {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
         3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
         0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
         0.45,0.00},
        {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
         8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
         0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
         0.69,1.24}};

// Globala variabler är ej tillåtna

//--------------------------------------------------------
// Funktionsdeklarationer:

// Deklarationer av dina egna funktioner
// Använd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
// denna skrevs i A-uppgiften och kan klippas in här
int berakna_histogram_abs(string str, int histogram[]);

// Funktionen abs_till_rel
void abs_till_rel(int raknade_bokstaver, int histogram[], double rel_histogram[]);

// Funktionen plotta_histogram_rel
void plotta_histogram_rel(double rel_histogram[]);
// Funktionen tolkning
void tolka(int raknade_bokstaver, double rel_histogram[]);

// Funktionen namn_pa_fil
string namn_pa_fil();

// Funktionen inlasning
string inlasning(string filnamn);

//--------------------------------------------------------
// Huvudprogram:

int main()
{
	string filnamn, textfil;
	int raknade_bokstaver;
	int histogram[ANTAL_BOKSTAVER];
	double rel_histogram[ANTAL_BOKSTAVER];

	filnamn = namn_pa_fil();

	textfil = inlasning(filnamn);

	raknade_bokstaver = berakna_histogram_abs(textfil, histogram);

	abs_till_rel(raknade_bokstaver, histogram, rel_histogram);

	plotta_histogram_rel(rel_histogram);

	tolka(raknade_bokstaver, rel_histogram);


  	return 0;
}

//--------------------------------------------------------
// Funktionsdefinitioner:
int berakna_histogram_abs(string str, int histogram[]){
    int no_of_letters = 0;
    for(int i = 0; i < str.length(); i++){
        if((char) tolower(str[i]) >= 'a' && (char) tolower(str[i]) <= 'z'){
            no_of_letters += 1;
        }
    }
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        histogram[i] = 0;
    }
    string alfabet = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < str.length(); i++){
        if(alfabet.find(str[i]) != -1){             //.find() returnar -1 om tecknet inte finns i strängen
            histogram[alfabet.find(str[i])] += 1;
        }
    }
    return no_of_letters;
}

void abs_till_rel(int raknade_bokstaver, int histogram[], double rel_histogram[]){
	for(int i = 0; i < ANTAL_BOKSTAVER; i++){
		rel_histogram[i] = (double(histogram[i]) / raknade_bokstaver) * 100.0;
	}
}

void plotta_histogram_rel(double rel_histogram[]){
	cout << endl;
	string alfabet = "abcdefghijklmnopqrstuvwxyz";
	for(int i = 0; i < ANTAL_BOKSTAVER; i++){
		int stars = (rel_histogram[i]*2);
		cout << (char) toupper(alfabet[i]) << " "; 
		for(int j = 0; j < stars; j++){
			cout << "*";
		}
		cout << endl;
	}
}

void tolka(int raknade_bokstaver, double rel_histogram[]){
	double kvadratsumma[ANTAL_SPRAK] = {0.0, 0.0, 0.0, 0.0};
	string sprak[ANTAL_SPRAK] = {"Engelska", "Franska", "Svenska", "Tyska"};

	for(int i = 0; i < ANTAL_SPRAK; i++){
		for(int j = 0; j < ANTAL_BOKSTAVER; j++){
			kvadratsumma[i] += (TOLK_HJALP[i][j] - rel_histogram[j]) * (TOLK_HJALP[i][j] - rel_histogram[j]);
		}
	}
	int most_probable_language = 0;
	cout << endl << "Antal räknade bokstäver (A-Z): " << raknade_bokstaver << endl;
	for(int i = 0; i < ANTAL_SPRAK; i++){
		if(kvadratsumma[i] < kvadratsumma[most_probable_language]){
			most_probable_language = i;
		}
		cout << "Kvadratsumman för: " << sprak[i] << " " << kvadratsumma[i] << endl;
	}
	cout << "Mest troliga språket är: " << sprak[most_probable_language] << endl;
}

string namn_pa_fil(){
	string filnamn;
	cout << "Ange namn på fil: ";
	getline(cin, filnamn);

	if(filnamn.rfind(".txt") != filnamn.length() - 4){
		filnamn.append(".txt");
	}
	return filnamn;
}

string inlasning(string filnamn){
	string text = "";
	std::ifstream is(filnamn);

	if(!is){
        cout << "Det finns ingen fil med namnet " << filnamn << endl;
        exit( EXIT_FAILURE );
    }

	char c;
	while(is.get(c)){
		text.push_back(c);
	}
	is.close();

	return text;
}


//Yahoo