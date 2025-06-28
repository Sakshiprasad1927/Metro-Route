#include <bits/stdc++.h>
#define rep0(i,n) for(int i=0;i<n;i++)
using namespace std;

const int V = 300;
string metro_lst[V];
int metro_no[V];

void metro_fare(float dis) {
    cout << "Expected Metro Fare (Weekdays except Sunday) would be: Rs. ";
    if (dis <= 2.0) cout << 10.0 << endl;
    else if (dis <= 5.0) cout << 20.0 << endl;
    else if (dis <= 12.0) cout << 30.0 << endl;
    else if (dis <= 21.0) cout << 40.0 << endl;
    else if (dis <= 32.0) cout << 50.0 << endl;
    else cout << 60.0 << endl;
    cout << endl;
}

int minDistance(float dist[], bool sptSet[]) {
    float min = 1e9;
    int min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printPath(int parent[], int j, int src, vector<int>& cnt) {
    if (parent[j] == src || parent[j] <= 0) {
        if (parent[j] == src) {
            cnt.push_back(metro_no[j]);
            cout << " -->>" << metro_lst[metro_no[j]];
        }
        return;
    }
    printPath(parent, parent[j], src, cnt);
    cnt.push_back(metro_no[j]);
    cout << " -->> " << metro_lst[metro_no[j]];
}

void printSolution(float dist[], int src, int parent[], int dest, vector<int>& cnt) {
    cout << "Distance between stations: " << dist[dest] << " km" << endl;
    metro_fare(dist[dest]);
    cout << metro_lst[metro_no[src]];
    cnt.push_back(metro_no[src]);
    printPath(parent, dest, src, cnt);
}

void dijkstra(float graph[][V], int src, int dest, vector<int>& cnt) {
    float dist[V];
    bool sptSet[V];
    int parent[V];
    fill(dist, dist + V, 1e9);
    fill(sptSet, sptSet + V, false);
    fill(parent, parent + V, -1);
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        if (u == -1) break;
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    printSolution(dist, src, parent, dest, cnt);
}

void print_ticket() {
    cout << "\n\n----------TOKEN---------\n";
    cout << "1. One way permitted\n2. Valid for one day\n3. Refund within 60 minutes\n4. Exit within 170 minutes (Penalty Rs. 10/hr, max Rs. 50)\n";
    cout << "\n----------TRAVEL CARD---------\n";
    cout << "1. Rs 150 (Rs 50 refundable security)\n2. Recharge Rs 200-2000\n3. Validity: 1 year after recharge, max 10 years\n4. Same station entry/exit Rs 10 within 20 minutes\n";
    cout << "\n----------BENEFITS---------\n";
    cout << "1. 10% discount on rides\n2. 20% off-peak discount\n3. Sunday/National Holiday Rs 10 discount\n4. Refundable balance\n5. Security Rs 50\n";
    cout << "\n----------TOURIST CARD---------\n";
    cout << "1. Rs 200/day (Rs 150 + Rs 50 security)\n2. Rs 500/3 days (Rs 450 + Rs 50 security)\n";
}

int main() {
    map<string, int> metro;
    float graph[V][V] = {0};
    int count = 0;

    vector<pair<string, pair<vector<string>, vector<float>>>> lines = {
        {"Red Line", {{"Dilshad Garden", "Jhil Mil", "Mansarovar Park", "Shahdara", "Welcome", "Seelampur", "Shastri Park", "Kashmere Gate", "Tis Hazari", "Pul Bangash", "Pratap Nagar", "Shastri Nagar", "Inderlok", "Kanhaiya Nagar", "Keshav Puram", "Netaji Subhash Place", "Kohat Enclave", "Pitam Pura", "Rohini East", "Rohini West", "Rithala"}, {0, 0.9, 1.1, 1.1, 1.2, 1.1, 1.6, 2.2, 1.1, 0.9, 0.8, 1.7, 1.2, 1.2, 0.8, 1.2, 1.1, 1.0, 0.8, 1.3, 1.0}}},
        {"Yellow Line", {{"Samaypur Badli", "Rohini Sector 18,19", "Haiderpur Badli Mor", "Jahangirpuri", "Adarsh Nagar", "Azadpur", "Model Town", "GTB Nagar", "Vishwavidyalaya", "Vidhan Sabha", "Civil Lines", "Kashmere Gate", "Chandni Chowk", "Chawri Bazar", "New Delhi", "Rajiv Chowk", "Patel Chowk", "Central Secretariat", "Udyog Bhawan", "Lok Kalyan Marg", "Jorbagh", "INA", "AIIMS", "Green Park", "Hauz Khas", "Malviya Nagar", "Saket", "Qutub Minar", "Chhatarpur", "Sultanpur", "Ghitorni", "Arjan Garh", "Guru Dronacharya", "Sikandarpur", "MG Road", "IFFCO Chowk", "HUDA City Centre"}, {0, 0.8, 1.3, 1.3, 1.3, 1.5, 1.4, 1.4, 0.8, 1.0, 1.3, 1.1, 1.1, 1.0, 0.8, 1.1, 1.3, 0.9, 0.3, 1.6, 1.2, 1.3, 0.8, 1.0, 1.8, 1.7, 0.9, 1.7, 1.3, 1.6, 1.3, 1.7, 1.5, 1.0, 1.2, 1.1, 1.5}}},
        {"Blue Line", {{"Dwarka Sector 21", "Dwarka Sector 8", "Dwarka Sector 9", "Dwarka Sector 10", "Dwarka Sector 11", "Dwarka Sector 12", "Dwarka Sector 13", "Dwarka Sector 14", "Dwarka", "Dwarka Mor", "Nawada", "Uttam Nagar West", "Uttam Nagar East", "Janakpuri West", "Janakpuri East", "Tilak Nagar", "Subhash Nagar", "Tagore Garden", "Rajouri Garden", "Ramesh Nagar", "Moti Nagar", "Kirti Nagar", "Shadipur", "Patel Nagar", "Rajendra Place", "Karol Bagh", "Jhandewalan", "RK Ashram Marg", "Rajiv Chowk", "Barakhamba", "Mandi House", "Pragati Maidan", "Indraprastha", "Yamuna Bank", "Akshardham", "Mayur Vihar Phase-1", "Mayur Vihar Extn", "New Ashok Nagar", "Noida Sector 15", "Noida Sector 16", "Noida Sector 18", "Botanical Garden", "Golf Course", "Noida City Centre", "Noida Sector 34", "Noida Sector 52", "Noida Sector 61", "Noida Sector 59", "Noida Sector 62", "Noida Electronic City"}, {0,1.7,1.0,1.1,1.0,1.0,0.9,0.9,1.5,1.1,1.2,1.0,1.0,1.3,1.0,1.0,0.9,0.9,1.1,1.0,1.2,1.0,0.7,1.3,0.9,1.0,1.2,1.0,1.2,0.7,1.0,0.8,0.8,1.8,1.3,1.8,1.2,0.9,1.0,1.1,1.1,1.1,1.2,1.3,0.8,1.3,1.4,1.1,1.0,1.2}}}
    };

    for (auto& line : lines) {
        const string& lineName = line.first;
        const vector<string>& stations = line.second.first;
        const vector<float>& dists = line.second.second;
        for (int i = 0; i < stations.size(); i++) {
            if (metro.find(stations[i]) == metro.end()) {
                metro[stations[i]] = count;
                metro_lst[count] = stations[i];
                metro_no[count] = count;
                count++;
            }
        }
        for (int i = 0; i < stations.size() - 1; i++) {
            int u = metro[stations[i]];
            int v = metro[stations[i + 1]];
            graph[u][v] = graph[v][u] = dists[i + 1];
        }
    }

    string response;
    while (true) {
        cout << "\nChoose an option:\n1. Find shortest route\n2. Ticket info\n3. List all stations with lines\n4. Exit\nEnter your choice: ";
        cin >> response;
        cin.ignore();

        if (response == "1") {
            string src, dst;
            cout << "Enter source station: "; getline(cin, src);
            cout << "Enter destination station: "; getline(cin, dst);
            if (metro.find(src) == metro.end() || metro.find(dst) == metro.end()) {
                cout << "Invalid station name. Please try again." << endl;
                continue;
            }
            vector<int> cnt;
            dijkstra(graph, metro[src], metro[dst], cnt);
            cout << "\nNumber of stations in route: " << cnt.size() - 1 << endl;
        }
        else if (response == "2") {
            print_ticket();
        }
        else if (response == "3") {
            for (auto& line : lines) {
                cout << "\n--- " << line.first << " ---\n";
                for (auto& station : line.second.first) {
                    cout << station << "\n";
                }
            }
        }
        else if (response == "4") {
            cout << "Thank you for using Metro App." << endl;
            break;
        }
        else {
            cout << "Invalid option. Try again." << endl;
        }
    }

    return 0;
}
