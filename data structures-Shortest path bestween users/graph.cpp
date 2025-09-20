#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <list>
#include <set>

using namespace std;

class SocialNetwork {
private:
    unordered_map<int, list<int>> adjList;

public:
    SocialNetwork() {}

    void addConnection(int user1, int user2) {
        adjList[user1].push_back(user2);
        adjList[user2].push_back(user1);
    }

    vector<int> getDirectConnections(int user) {
        vector<int> connections;
        if (adjList.find(user) != adjList.end()) {
            for (int neighbor : adjList[user]) {
                connections.push_back(neighbor);
            }
        }
        else {
            cout << "User " << user << " does not exist in the network." << endl;
        }
        return connections;
    }

    int countTotalConnections() {
        set<pair<int, int>> uniqueConnections;
        for (auto& pair : adjList) {
            int user = pair.first;
            for (int neighbor : pair.second) {
                if (user < neighbor) {
                    uniqueConnections.insert(make_pair(user, neighbor));
                }
            }
        }
        return uniqueConnections.size();
    }

    bool deleteConnection(int user1, int user2) {
        if (adjList.find(user1) == adjList.end() || adjList.find(user2) == adjList.end()) {
            return false;
        }

        adjList[user1].remove(user2);
        adjList[user2].remove(user1);
        return true;
    }

    void bfs(int start) {
        if (adjList.find(start) == adjList.end()) {
            cout << "User " << start << " does not exist in the network." << endl;
            return;
        }
        unordered_map<int, bool> visited;
        queue<int> queue;

        visited[start] = true;
        queue.push(start);

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();
            cout << current << " ";

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void dfsUtil(int v, unordered_map<int, bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited);
            }
        }
    }

    void dfs(int start) {
        if (adjList.find(start) == adjList.end()) {
            cout << "User " << start << " does not exist in the network." << endl;
            return;
        }

        unordered_map<int, bool> visited;
        dfsUtil(start, visited);
        cout << endl;
    }

    int shortestPath(int src, int dest) {
        if (adjList.find(src) == adjList.end() || adjList.find(dest) == adjList.end()) {
            cout << "One or both users do not exist in the network." << endl;
            return -1;
        }

        unordered_map<int, int> dist;
        unordered_map<int, bool> visited;
        queue<int> q;

        visited[src] = true;
        q.push(src);
        dist[src] = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
                    if (neighbor == dest) {
                        return dist[neighbor];
                    }
                }
            }
        }
        return -1;
    }

    bool searchUser(int user) {
        return adjList.find(user) != adjList.end();
    }
};

int main() {
    SocialNetwork network;
    int choice, user1, user2;

    while (true) {
        cout << "Social Network Menu:\n";
        cout << "1. Add Connection\n";
        cout << "2. Delete Connection\n";
        cout << "3. Display BFS Traversal\n";
        cout << "4. Display DFS Traversal\n";
        cout << "5. Find Shortest Path\n";
        cout << "6. Search for User\n";
        cout << "7. Get Direct Connections of a User\n";
        cout << "8. Get Total Count of Connections\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter two user IDs to connect: ";
            cin >> user1 >> user2;
            network.addConnection(user1, user2);
            break;
        case 2:
            cout << "Enter two user IDs to delete connection: ";
            cin >> user1 >> user2;
            if (!network.deleteConnection(user1, user2))
                cout << "Failed to delete connection. One or both users not found.\n";
            break;
        case 3:
            cout << "Enter user ID to start BFS: ";
            cin >> user1;
            network.bfs(user1);
            break;
        case 4:
            cout << "Enter user ID to start DFS: ";
            cin >> user1;
            network.dfs(user1);
            break;
        case 5:
            cout << "Enter source and destination user IDs for shortest path: ";
            cin >> user1 >> user2;
            int dist;
            dist = network.shortestPath(user1, user2);
            if (dist != -1)
                cout << "Shortest path is " << dist << " steps.\n";
            else
                cout << "No path found.\n";
            break;
        case 6:
            cout << "Enter user ID to search: ";
            cin >> user1;
            if (network.searchUser(user1))
                cout << "User found in the network.\n";
            else
                cout << "User not found.\n";
            break;
        case 7: {
            cout << "Enter user ID to get direct connections: ";
            cin >> user1;
            vector<int> connections = network.getDirectConnections(user1);
            if (!connections.empty()) {
                cout << "Direct connections of user " << user1 << ": ";
                for (int conn : connections) {
                    cout << conn << " ";
                }
                cout << endl;
            }
            break;
        }
        case 8:
            cout << "Total number of connections in the network: " << network.countTotalConnections() << endl;
            break;
        case 9:
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
