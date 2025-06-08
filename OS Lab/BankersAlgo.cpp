#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>> allocation, vector<vector<int>> max, 
            vector<int> available, vector<int>& safeSeq) {
    int P = allocation.size();    
    int R = available.size();    
    
    vector<int> work = available;
    vector<bool> finish(P, false);
    safeSeq.clear();
    
    // Find a process that can be executed
    bool found;
    for (int count = 0; count < P; count++) {
        found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool flag = true;
                for (int r = 0; r < R; r++) {
                    if (max[p][r] - allocation[p][r] > work[r]) {
                        flag = false;
                        break;
                    }
                }
                
                if (flag==true) {
                    //execute the process
                    for (int r = 0; r < R; r++)
                        work[r] += allocation[p][r];
                    
                    finish[p] = true;
                    safeSeq.push_back(p);
                    found = true;
                    break;
                }
            }
        }
        
        if (!found) return false; // No process found ->> unsafe state
    }
    
    return true; // All processes executed -> safe state
}

bool requestResources(int process, vector<int> request, 
                     vector<vector<int>>& allocation, vector<vector<int>>& max,
                     vector<int>& available) {
    int R = available.size();
    
    // Step 1: Check if request <= need
    for (int r = 0; r < R; r++) {
        if (request[r] > max[process][r] - allocation[process][r]) {
            cout << "Error: Request exceeds maximum need\n";
            return false;
        }
    }
    
    // Step 2: Check if request <= available
    for (int r = 0; r < R; r++) {
        if (request[r] > available[r]) {
            cout << "Error: Not enough resources available\n";
            return false;
        }
    }
    
    // Step 3: Try to allocate resources temporarily
    for (int r = 0; r < R; r++) {
        available[r] -= request[r];
        allocation[process][r] += request[r];
    }
    
    // Step 4: Check if the new state is safe
    vector<int> safeSeq;
    bool safe = isSafe(allocation, max, available, safeSeq);
    
    if (safe) {
        cout << "Request granted. Safe sequence: ";
        for (int p : safeSeq) cout << "P" << p << " ";
        cout << endl;
        return true;
    } else {
        // Roll back changes
        cout << "Request denied - would lead to unsafe state\n";
        for (int r = 0; r < R; r++) {
            available[r] += request[r];
            allocation[process][r] -= request[r];
        }
        return false;
    }
}

int main() {
    int P, R;
    
    // Input num of processes and resources
    cout << "Enter number of processes: ";
    cin >> P;
    cout << "Enter number of resource types: ";
    cin >> R;
    
    // Allocation 
    vector<vector<int>> allocation(P, vector<int>(R));
    cout << "Enter allocation matrix (P x R):\n";
    for (int p = 0; p < P; p++)
        for (int r = 0; r < R; r++)
            cin >> allocation[p][r];
    
    // Max 
    vector<vector<int>> max(P, vector<int>(R));
    cout << "Enter maximum matrix (P x R):\n";
    for (int p = 0; p < P; p++)
        for (int r = 0; r < R; r++)
            cin >> max[p][r];
    
    // Available 
    vector<int> available(R);
    cout << "Enter available resources (R entries): ";
    for (int r = 0; r < R; r++)
        cin >> available[r];
    
    vector<int> safeSeq;
    if (isSafe(allocation, max, available, safeSeq)) {
        cout << "System is in safe state. Safe sequence: ";
        for (int p : safeSeq) cout << "P" << p << " ";
        cout << endl;
    } else {
        cout << "System is in unsafe state!\n";
    }
    
    // Handle multiple requests
    while (true) {
        int choice;
        cout << "\n1. Make resource request\n2. Exit\nEnter choice: ";
        cin >> choice;
        
        if (choice == 2) break;
        
        if (choice == 1) {
            int process;
            vector<int> request(R);
            
            cout << "Enter process number (0-" << P-1 << "): ";
            cin >> process;
            cout << "Enter request (R entries): ";
            for (int r = 0; r < R; r++)
                cin >> request[r];
            
            requestResources(process, request, allocation, max, available);
        } else {
            cout << "Invalid choice\n";
        }
    }
    
    return 0;
}