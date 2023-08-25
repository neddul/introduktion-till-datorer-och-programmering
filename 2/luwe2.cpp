//Inlämningsuppift 2
//Skriven av Ludvig Westerholm
//2023-08-24
#include <iostream>
using namespace std;

int main(){
    int starthh, startmm, startss;
    int endhh, endmm, endss;

    int runner_number, winner_number;
    int no_runners = 0;
    int best_time = 24*60*60;

    while(true){
        cout << "Startnummer? ";
        cin >> runner_number;

        if(runner_number < 0){
            if(no_runners == 0){
                cout << "Inga tävlande" << endl << "Programmet avslutas" << endl;
                return 0;
            }
            else{
                int besthh, bestmm, bestss;
                besthh = best_time / (60*60);
                bestmm = (best_time - besthh*60*60) / 60;
                bestss = best_time - besthh*60*60 - bestmm*60;
                cout << "Vinnare är startnr: " << winner_number << endl;
                cout << "Tim: " << besthh << " Min: " << bestmm << " Sek: " << bestss << endl;
                cout << "Antal tävlande: " << no_runners << endl;
                cout << "Programmet avslutas" << endl;
                return 0;
            }
        }
        else{
            cout << "Starttid? ";
            cin >> starthh >> startmm >> startss;
            cout << "Måltid? ";
            cin >> endhh >> endmm >> endss;

            int goal_time = endhh*60*60 + endmm*60 + endss - (starthh*60*60 + startmm*60 + startss);

            if(goal_time < 0){
                goal_time += 24*60*60;
            }
            if(goal_time < best_time){
                best_time = goal_time;
                winner_number = runner_number;
            }
            no_runners += 1;
        }
    }

    return 0;
}


//Yahoo