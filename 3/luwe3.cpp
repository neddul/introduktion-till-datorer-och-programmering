//Inlämningsuppift 3
//Skriven av Ludvig Westerholm
//2023-08-24

#include <iostream>
#include <cctype>
using namespace std;

void skrivInfo();
int lasEttTal();
char lasOp();
void ordna(int &a, int &b);
int berakna(int a, int b, char op);
void skrivResultat(int svar);

int main()
{  
    // Här ska deklaration av variabler finnas
    int tal1, tal2, svar;
    char op;

    skrivInfo();

    tal1 = lasEttTal();

    tal2 = lasEttTal();

    op = lasOp();

    ordna(tal1, tal2);

    svar = berakna(tal1, tal2, op);

    skrivResultat(svar);

    return 0;
}

void skrivInfo(){
    cout << "Beräkning av två tal. A för addition, M för multiplikation eller K för kvadratsumman." << endl;
}

int lasEttTal(){
    int tal;
    cout << "Skriv in ett tal: ";
    cin >> tal;
    return tal;
}

char lasOp(){
    char op;
    while(true){
        cout << "Skriv in en operation (A, M eller K): ";
        cin >> op;
        op = (char) tolower(op);

        if(op == 'a' || op == 'm' || op == 'k'){
            return op;
        }
        else{
            cout << "Felaktig inmatning!" << endl;
            
        }
    }    
    return 'a';
}

void ordna(int &a, int &b){
    if(a>b){
        int tmp = a;
        a = b;
        b = tmp;
    }
}

int berakna(int a, int b, char op){
    int sum = 0;
    switch(op)
    {
        case 'a':
        {
            for(a; a <= b; a++){
                sum += a;
            }
            break;
        }
        case 'm':
        {
            sum = 1;
            for(a; a <= b; a++){
                sum *= a;
            }
            break;
        }
        case 'k':
        {
            for(a; a <= b; a++){
                sum += a*a;
            }
            break;
        }
    }

    return sum;
}

void skrivResultat(int svar){
    cout << "Svar: " << svar << endl;
}


//Yahoo