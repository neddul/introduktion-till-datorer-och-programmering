//Inlämningsuppift 5B
//Skriven av Ludvig Westerholm
//2023-08-25
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
// H�r kommer klassdeklarationen
class Text
{
    private:
        string  text;
        int     text_langd;
        int     histogram[ANTAL_BOKSTAVER];
        double  rel_histogram[ANTAL_BOKSTAVER];

    public:
        Text();
        ~Text();
        void    setText( const string &nyText);
        bool    beraknaHistogramAbs();
        void    skrivHistogramAbs();
        void    absTillRel();
        void    plottaHistogramRel();
        void    beraknaHistogram();
        string  tolka();
};

// -------------------------------------------------------

// Funktionen namn_pa_fil
string namn_pa_fil();

// Funktionen inlasning
string inlasning(string filnamn);

// Huvudprogram:

int main()
{
    // Deklarera variabler
    string filnamn = namn_pa_fil();
    string text = inlasning(filnamn);
    Text minText;  // Ett objekt av typen Text skapas


    // Skicka strängen text till objektet minText
    minText.setText( text );

    // Beräkna och skriv ut histogrammet
    minText.beraknaHistogram();
    minText.plottaHistogramRel();
    
    string sprak = minText.tolka();
    cout << "Mest troliga språket är: " << sprak << endl;
}

//------------------------------------------------------------------

Text::Text()
{
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        histogram[i] = 0;
        rel_histogram[i] = 0.0;
    }
    text_langd = 0;
    text = "";
}

Text::~Text()
{}

void Text::setText(const string &nyText){
    text = nyText;
}

bool Text::beraknaHistogramAbs(){
    for(int i = 0; i < text.length(); i++){
        if((char) tolower(text[i]) >= 'a' && (char) tolower(text[i]) <= 'z'){
            text_langd += 1;
        }
    }
    string alfabet = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < text.length(); i++){
        if(alfabet.find(text[i]) != -1){             //.find() returnar -1 om tecknet inte finns i strängen
            histogram[alfabet.find(text[i])] += 1;
        }
    }
    return text_langd > 0;
}

void Text::skrivHistogramAbs(){
    string alfabet = "abcdefghijklmnopqrstuvwxyz";
    cout << "Antal bokstäver i textraden: " << text_langd << endl;
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        cout << (char) toupper(alfabet[i]) << ": " << histogram[i] << endl;
    }
}

void Text::absTillRel(){
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
		rel_histogram[i] = (double(histogram[i]) / text_langd) * 100.0;
	}
}

void Text::plottaHistogramRel(){
    cout << endl;
	string alfabet = "abcdefghijklmnopqrstuvwxyz";
	for(int i = 0; i < ANTAL_BOKSTAVER; i++){
		cout << (char) toupper(alfabet[i]) << " "; 
		for(int j = 0; j < (rel_histogram[i]*2); j++){
			cout << "*";
		}
		cout << endl;
	}
}

void Text::beraknaHistogram(){
    if(beraknaHistogramAbs()){
        absTillRel();
    }
}

string Text::tolka(){
    double kvadratsumma[ANTAL_SPRAK] = {0.0, 0.0, 0.0, 0.0};
	string sprak[ANTAL_SPRAK] = {"Engelska", "Franska", "Svenska", "Tyska"};

	for(int i = 0; i < ANTAL_SPRAK; i++){
		for(int j = 0; j < ANTAL_BOKSTAVER; j++){
			kvadratsumma[i] += (TOLK_HJALP[i][j] - rel_histogram[j]) * (TOLK_HJALP[i][j] - rel_histogram[j]);
		}
	}
	int most_probable_language = 0;
	cout << endl << "Antal räknade bokstäver (A-Z): " << text_langd << endl;
	for(int i = 0; i < ANTAL_SPRAK; i++){
		if(kvadratsumma[i] < kvadratsumma[most_probable_language]){
			most_probable_language = i;
		}
		cout << "Kvadratsumman för: " << sprak[i] << " " << kvadratsumma[i] << endl;
	}
    return sprak[most_probable_language];
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