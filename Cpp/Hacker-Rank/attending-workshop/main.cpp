#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
struct Workshop{
    int startTime;
    int duration;
    int endTime;
    int operator<(Workshop &operand) {
        return startTime < operand.startTime;
    }
};

typedef struct {
    int n;
    Workshop *pWs;
} Available_Workshops;
//Implement the functions initialize and CalculateMaxWorkshops
Available_Workshops * initialize(int start_time[], int duration[], int n) {
    Available_Workshops *retval = new Available_Workshops;
    retval->n = n;
    retval->pWs = new Workshop[n];
    for (int i = 0; i < n; i++) {
        retval->pWs[i].startTime = start_time[i];
        retval->pWs[i].duration = duration[i];
        retval->pWs[i].endTime = start_time[i] + duration[i];
    }
    return retval;
}
int CalculateMaxWorkshops(Available_Workshops *ptr) {
    sort(ptr->pWs, ptr->pWs + ptr->n);
    // for (int i = 0; i < ptr->n; i++) {
    //     cout << ptr->pWs[i].startTime << " " << ptr->pWs[i].endTime << endl;
    // }
    int retval = ptr->n;
    Workshop *previous = &ptr->pWs[0];
    for (int i = 1; i < ptr->n; i++) {
        if (previous->endTime > ptr->pWs[i].startTime) {
            if (previous->endTime >= ptr->pWs[i].endTime) {
                previous = &ptr->pWs[i];
                retval --;
            } else {
                retval --;
            }
        } else {
            previous = &ptr->pWs[i];
        }
    }
    return retval;
}
int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
