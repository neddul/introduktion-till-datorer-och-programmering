//Inlämningsuppift 4A
//Skriven av Ludvig Westerholm
//2023-08-24
// Hanterar fallet med 26 bokstäver A-Z

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;


// Använd gärna denna globala konstant i programmet
// i stället för värdet 26
const int ANTAL_BOKSTAVER = 26;  //A-Z
// Globala variabler är ej tillåtna

//--------------------------------------------------------
// Funktionsdeklarationer:
// Använd exakt de funktionsnamn som finns nedan

// Funktionen berakna_histogram_abs
int berakna_histogram_abs(string str, int histogram[]);

// Funktionen skriv_histogram_abs
void skriv_histogram_abs(int raknade_bokstaver, int histogram[]);

//--------------------------------------------------------
// Huvudprogram:

int main()
{
    // Deklarera variabler
    string str;
    int histogram[ANTAL_BOKSTAVER];
    int raknade_bokstaver = 0;
    // Läs in en rad med text från tangentbordet
    cout << "Skriv en textrad: ";
    getline(cin, str);

    // Anropa funktionen berakna_histogram_abs som beräknar histogrammet
    // och antalet bokstäver.  
    raknade_bokstaver = berakna_histogram_abs(str, histogram);


    // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
    skriv_histogram_abs(raknade_bokstaver, histogram);

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

void skriv_histogram_abs(int raknade_bokstaver, int histogram[]){
    string alfabet = "abcdefghijklmnopqrstuvwxyz";
    cout << "Antal bokstäver i textraden: " << raknade_bokstaver << endl;
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        cout << (char) toupper(alfabet[i]) << ": " << histogram[i] << endl;
    }
}


//Yahoo