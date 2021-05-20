#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

bool isSafe(int* need, int* available,int* allocation,int* finish,int n,int m) {
    int* work = new int[m];
    for (int i = 0; i < m; i++)work[i] = available[i];
    for (int i = 0; i < n; i++)finish[i] = -1;
    int sort = 0;
    bool end = false;
    while (!end) {
        end = true;
        for (int i = 0; i < n; i++) {
            if (finish[i] != -1)continue;
            bool pass = true;
            for (int j = 0; j < m; j++) {
                if (need[(i * m) + j] > work[j]) {
                    pass = false; break;
                }
            }
            if (pass) {
                finish[i] = sort;
                sort++;
                for (int j = 0; j < m; j++) work[j] = work[j] + allocation[(i * m) + j];
                end = false;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (finish[i] == -1)return false;
    }
    return true;
}

int* getNeed(int* max,int* allocation,int n,int m) { 
    int* need = new int[n * m];
    for (int i = 0; i < n * m; i++) 
        need[i] = max[i] - allocation[i];
    return need;
}



int main() {
    while (1) {
        int n, m; //Num of Processes and Resources 
        cout << "Enter The Number of Processes:\t\t"; cin >> n;
        cout << "Enter The Number of Resources:\t\t"; cin >> m;

        int* available = new int[m];
        int* allocation = new int[n * m];
        int* max = new int[n * m];

        for (int i = 0; i < n; i++) {
            cout << "Insert Allocation Vector of [P" + to_string(i) + "]:\t";
            for (int j = 0; j < m; j++) {
                cin >> allocation[i * m + j];
            }
        }
        for (int i = 0; i < n; i++) {
            cout << "Insert Max Vector of [P" + to_string(i) + "]:\t\t";
            for (int j = 0; j < m; j++) {
                cin >> max[i * m + j];
            }
        }
        cout << "Insert Available Vector of [R0:R" + to_string(m - 1) + "]:\t";
        for (int i = 0; i < m; i++) cin >> available[i];

        int* need = getNeed(max, allocation, n, m);
        cout << "\nThe Need Matrix of the System:\n";
        for (int i = 0; i < m; i++) cout << "\tR" + to_string(i);
        cout << "\n";

        for (int i = 0; i < n; i++) {
            cout << "P" + to_string(i);
            for (int j = 0; j < m; j++) {
                cout << "\t" << need[i * m + j];
            }
            cout << "\n";
        }

        while (1) {
            cout << "--------------------------------------------------------------------------\n";
            cout << "Enter\t'safe'\t>> To Enquiry if the system is in a safe state\n";
            cout << "Enter\t'req'\t>> To Enquiry if a request by a process can be granted\n";
            cout << "Enter\t'reset'\t>> To reset the program and re-enter vectors\n";
            cout << "*otherwise will terminate the program*\n";
            cout << "--------------------------------------------------------------------------\n";

            string key;
            cin >> key;

            if (key == "safe") {
                int* finish = new int[n];
                bool safe = isSafe(need, available, allocation, finish, n, m);
                if (safe) {
                    cout << "\n>>\tYes, Safe state <";
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            if (finish[j] == i) {
                                if (i == 0) cout << "P" + to_string(j);
                                else   cout << ",P" + to_string(j);
                                break;
                            }
                        }
                    }
                    cout << ">\n";
                }
                else {
                    cout << "\n>>\tNo\n";
                }
            }
            else if (key == "req") {
                int pnum;
                int* req = new int[m];
                cout << "Enter The Process Number [0:" + to_string(n - 1) + "]:\t\t";
                cin >> pnum;
                for (int i = 0; i < m; i++) {
                    int temp;
                    cout << "Enter The instances required from R" + to_string(i) + ":\t";
                    cin >> temp;
                    req[i] = temp;
                }
                int* Tavailable = new int[m];
                int* Tallocation = new int[n * m];
                int* Tmax = new int[n * m];
                for (int i = 0; i < n * m; i++) {
                    Tallocation[i] = allocation[i];
                    Tmax[i] = max[i];
                    if (i < m)Tavailable[i] = available[i];
                }
                bool error = false;
                for (int i = 0; i < m; i++) {
                    if (req[i] > Tavailable[i]) {
                        error = true; break;
                    }
                    else {
                        Tavailable[i] = Tavailable[i] - req[i];
                        Tallocation[(pnum * m) + i] = Tallocation[(pnum * m) + i] + req[i];
                    }
                }
                if (!error) {
                    int* Tneed = getNeed(Tmax, Tallocation, n, m);
                    int* Tfinish = new int[n];
                    bool safe = isSafe(Tneed, Tavailable, Tallocation, Tfinish, n, m);
                    if (safe) {
                        cout << "\n>>\tYes, Safe state <P" + to_string(pnum) + "req,";
                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < n; j++) {
                                if (Tfinish[j] == i) {
                                    if (i == 0) cout << "P" + to_string(j);
                                    else   cout << ",P" + to_string(j);
                                    break;
                                }
                            }
                        }
                        cout << ">\n";
                    }
                    else cout << "\n>>\tNo\n";
                }
                else cout << "\n>>\tNo\n";
            }
            else if (key == "reset") {
                cout << "\n\n";
                cout << "--------------------------------------------------------------------------\n";
                cout << "--------------------------------------------------------------------------\n";
                cout << "\n\n";
                break;
            }
            else return 0;
        }
    }
    
}