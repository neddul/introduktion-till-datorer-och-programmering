//Inlämningsuppift 6A
//Skriven av Ludvig Westerholm
//2023-08-25

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;


class Transaktion
{
    private:
        string  datum;
        string  typ;
        string  namn;
        double  belopp;
        int     antal_kompisar;
        string  kompisar[MAX_PERSONER];

    public:
        Transaktion();
        ~Transaktion();
        string hamtaNamn();
        double hamtaBelopp();
        int    hamtaAntalKompisar();
        bool   finnsKompis(const string &namnet);
        bool   lasIn(istream &is);
        void   skrivUt(ostream &os);
        void   skrivTitel(ostream &os);
}; 

class Person
{
    private:
        string  namn;
        double  betalat_andras; // ligger ute med totalt
        double  skyldig;        // skyldig totalt

    public:
        Person();
        Person(const string &namn, double betalat_andras, double skyldig);
        string  hamtaNamn();
        double  hamtaBetalat();
        double  hamtaSkyldig();
        void    skrivUt(ostream &os);
};

class PersonLista
{
    private:
        int     antal_personer;
        Person  personer[MAX_PERSONER];

    public:
        PersonLista();
        ~PersonLista();
        void    laggTill(Person ny_person);
        void    skrivUtOchFixa(ostream &os);
        double  summaSkyldig();
        double  summaBetalat();
        bool    finnsPerson(const string& namn);
};

class TransaktionsLista
{
    private:
        int         antal_transaktioner;
        Transaktion transaktioner[MAX_TRANSAKTIONER];

    public:
        TransaktionsLista();
        ~TransaktionsLista();
        void    lasIn(istream & is);
        void    skrivUt(ostream & os);
        void    laggTill(Transaktion & t);
        double  totalKostnad();
        double  liggerUteMed(const string &namnet);
        double  arSkyldig(const string &namnet);
        PersonLista FixaPersoner();
};

int main()
    {
    cout << "Startar med att läsa från en fil." << std::endl;

    TransaktionsLista transaktioner;
    std::ifstream     is("resa.txt");
    transaktioner.lasIn(is);

    int     operation = 1;
    while (operation != 0)
    {
        cout << endl;
        cout << "Välj i menyn nedan:" << endl;
        cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
        cout << "1. Skriv ut information om alla transaktioner." << endl;
        cout << "2. Läs in en transaktion från tangentbordet." << endl;
        cout << "3. Beräkna totala kostnaden." << endl;
        cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
        cout << "5. Hur mycket ligger en viss person ute med?" << endl;
        cout << "6. Lista alla personer mm och FIXA" << endl;

        cin >> operation;
        cout << endl;

        switch (operation)
        {
        case 1:
            {
                transaktioner.skrivUt(cout);
                break;
            }
        case 2:
            {
                Transaktion transaktion;
                cout << "Ange transaktion i följande format" << endl;
                transaktion.skrivTitel(cout);
                transaktion.lasIn(cin);
                transaktioner.laggTill(transaktion);
                break;
            }
        case 3:
            {
                cout << "Den totala kostnanden för resan var "
                << transaktioner.totalKostnad() << endl;
                break;
            }
        case 4:
            {
                cout << "Ange personen: ";
                string namn;
                cin >> namn;
                double ar_skyldig = transaktioner.arSkyldig(namn);
                if (ar_skyldig == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
                else
                cout << namn << " är skyldig " << ar_skyldig << endl;
                break;
            }
        case 5:
            {
                cout << "Ange personen: ";
                string namn;
                cin >> namn;
                double ligger_ute_med = transaktioner.liggerUteMed(namn);
                if (ligger_ute_med == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
                else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
                break;
            }
        case 6:
            {
                cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
                PersonLista lista = transaktioner.FixaPersoner();
                lista.skrivUtOchFixa(cout);
                break;
            }
        }
    }

    std::ofstream os("transaktioner.txt");
    transaktioner.skrivUt(os);

    return 0;
}

//------------------------------------------------------------------

Transaktion::Transaktion()
{
    datum = "";
    typ = "";
    namn = "";
    belopp = 0.0;
    antal_kompisar = 0;
}

Transaktion::~Transaktion()
{}

string Transaktion::hamtaNamn(){
    return namn;
}

double Transaktion::hamtaBelopp(){
    return belopp;
}

int Transaktion::hamtaAntalKompisar(){
    return antal_kompisar;
}

bool Transaktion::finnsKompis(const string &namnet){
    for(int i = 0; i < antal_kompisar; i++){
        if(namnet.compare(kompisar[i]) == 0){
            return true;
        }
    }
    return false;
}

bool Transaktion::lasIn(istream &is){
    is >> datum >> typ >> namn >> belopp >> antal_kompisar; 
    if (is.fail()){
        return false;
    }
    for (int i = 0; i < antal_kompisar; i++){
        is >> kompisar[i]; 
        if (is.fail()){
            return false;
        }
    }
    return true; 
}

void Transaktion::skrivUt(ostream &os){
    os 
    << left << std::setw(8) << datum
    << left << std::setw(8) << typ
    << left << std::setw(8) << namn
    << left << std::setw(8) << belopp
    << left << std::setw(8) << antal_kompisar;

    for(int i = 0; i < antal_kompisar; i++){
        os << left << std::setw(8) << kompisar[i] << " ";
    }
    os << endl;
}

void Transaktion::skrivTitel(ostream &os){
    os
    << left << std::setw(8) << "Datum"
    << left << std::setw(8) << "Typ"
    << left << std::setw(8) << "Namn"
    << left << std::setw(8) << "Belopp"
    << left << std::setw(8) << "Antal kompisar och deras namn" << std::endl;
}

//------------------------------------------------------------------

Person::Person()
{
    namn = "";
    betalat_andras = 0.0;
    skyldig = 0.0;
}

Person::Person(const string &namn, double betalat_andras, double skyldig)
: namn(namn), betalat_andras(betalat_andras), skyldig(skyldig)
{}

string Person::hamtaNamn(){
    return namn;
}

double Person::hamtaBetalat(){
    return betalat_andras;
}

double Person::hamtaSkyldig(){
    return skyldig;
}

void Person::skrivUt(ostream &os){
    double diff = betalat_andras - skyldig;
    os << namn << " ligger ute med " << betalat_andras << " och är skyldig " << skyldig << ". ";
    if(diff >= 0){
        os << "Skall ha " << abs(diff) << " från potten!" << endl;
    }
    else{
        os << "Skall lägga " << abs(diff) << " till potten!" << endl;
    }
}

//------------------------------------------------------------------

PersonLista::PersonLista()
{
    antal_personer = 0;
}

PersonLista::~PersonLista()
{}

void PersonLista::laggTill(Person ny_person){
    personer[antal_personer] = ny_person;
    antal_personer +=1;
}

void PersonLista::skrivUtOchFixa(ostream &os){
    for(int i = 0; i < antal_personer; i++){
        personer[i].skrivUt(os);
    }
    if(abs(summaBetalat() - summaSkyldig()) > 0.0000000001){
        os << "Pengarna som har betalats till potten och som togs ifrån potten "
        << "passar inte ihop, " << summaBetalat() << " != " << summaSkyldig()
        << endl;
    }
}

double PersonLista::summaBetalat(){
    double sum = 0;
    for(int i = 0; i < antal_personer; i++){
        sum += personer[i].hamtaBetalat();
    }
    return sum;
}

double PersonLista::summaSkyldig(){
    double sum = 0;
    for(int i = 0; i < antal_personer; i++){
        sum += personer[i].hamtaSkyldig();
    }
    return sum;
}

bool PersonLista::finnsPerson(const string &namn){
    for(int i = 0; i < antal_personer; i++){
        if(personer[i].hamtaNamn().compare(namn) == 0){
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------

TransaktionsLista::TransaktionsLista(){
    antal_transaktioner = 0;
}

TransaktionsLista::~TransaktionsLista()
{}

void TransaktionsLista::lasIn(istream &is){    
    Transaktion t;
    while (t.lasIn(is)){
        laggTill(t);
    }
}

void TransaktionsLista::skrivUt(ostream &os){
    os << "Antal transaktioner = " << antal_transaktioner << endl;
    transaktioner[0].skrivTitel(os);
    for(int i = 0; i < antal_transaktioner; i++){
        transaktioner[i].skrivUt(os);
    }
}

void TransaktionsLista::laggTill(Transaktion &t){
    transaktioner[antal_transaktioner] = t;
    antal_transaktioner +=1;
}

double TransaktionsLista::totalKostnad(){
    double sum = 0;
    for(int i = 0; i < antal_transaktioner; i++){
        sum += transaktioner[i].hamtaBelopp();
    }
    return sum;
}

double TransaktionsLista::liggerUteMed(const string &namn)
{
    double summa = 0;
    for (int i = 0; i < antal_transaktioner; i++){
        if (transaktioner[i].hamtaNamn() == namn){
            summa += transaktioner[i].hamtaBelopp() * (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
        }
    }
    return summa;
}

double TransaktionsLista::arSkyldig(const string &namnet){
    double sum = 0;
    for(int i = 0; i < antal_transaktioner; i++){
        if(transaktioner[i].finnsKompis(namnet)){
            sum += transaktioner[i].hamtaBelopp() / (transaktioner[i].hamtaAntalKompisar() + 1);
        }
    }
    return sum;
}

PersonLista TransaktionsLista::FixaPersoner(){
    PersonLista pl;
    for(int i = 0; i < antal_transaktioner; i++){
        string namnet = transaktioner[i].hamtaNamn();
        if(!pl.finnsPerson(namnet)){
            Person p(namnet, liggerUteMed(namnet), arSkyldig(namnet));
            pl.laggTill(p);
        }
    }
    return pl;
}


//Yahoo