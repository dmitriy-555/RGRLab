#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <cctype> 
using namespace std;

class Player {
private:
    string ID;
    string name1, name2, name3, team;
    int goal;
    int pass;
    int penaltyTime;
public:
    Player(string i = "", string t = "", string a = "", string b = "", string c = "", int d = 0, int e = 0, int f = 0)
        : ID(i), name1(a), name2(b), name3(c), team(t), goal(d), pass(e), penaltyTime(f) {}

    friend istream& operator>>(istream& is, Player& player) {
        return is >> player.ID >> player.name1 >> player.name2 >> player.name3 >> player.team >> player.goal >> player.pass >> player.penaltyTime;
    }

    friend ostream& operator<<(ostream& os, Player& player) {
        return os << "ID: " << player.ID << ", Name: " << player.name1 << " " << player.name2 << " " << player.name3 << ", Team: " << player.team << ", Goals: " << player.goal << ", Passes: " << player.pass << ", Penalty time: " << player.penaltyTime << endl;
    }

    int getTotalScore() {
        return goal + pass;
    }

    string get_ID() {
        return ID;
    }
    string get_Name1() {
        return name1;
    }
    string get_Name2() {
        return name2;
    }
    string get_Name3() {
        return name3;
    }
    string get_Team() {
        return team;
    }
    int get_Goals() {
        return goal;
    }
    int get_Passes() {
        return pass;
    }
    int get_PenaltyTime() {
        return penaltyTime;
    }

    void set_ID(string a) {
        ID = a;
    }
    void set_Name1(string a) {
        name1 = a;
    }
    void set_Name2(string a) {
        name2 = a;
    }
    void set_Name3(string a) {
        name3 = a;
    }
    void set_Team(int a) {
        team = a;
    }
    void set_Goals(int a) {
        goal = a;
    }
    void set_Passes(int a) {
        pass = a;
    }
    void set_PenaltyTime(int a) {
        penaltyTime = a;
    }
};

vector<Player> readPlayersFromFile(string filename) {
    vector<Player> players;
    ifstream file(filename);
    if (file.is_open()) {
        Player player;
        while (file >> player) {
            players.push_back(player);
        }
        file.close();
    }
    else {
        cout << "File opening error " << filename << endl;
    }
    return players;
}

void writePlayersToFile(vector<Player> players, string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (auto player : players) {
            file << player.get_ID() << " " << player.get_Name1() << " " << player.get_Name2() << " " << player.get_Name3() << " " << player.get_Team() << " " << player.get_Goals() << " " << player.get_Passes() << " " << player.get_PenaltyTime() << endl;
        }
        file.close();
    }
    else {
        cout << "File opening error " << filename << endl;
    }
}

void printPlayers(vector<Player> players) {
    for (auto player : players) {
        cout << player;
    }
}

bool comparePlayers(Player a, Player b) {
    return a.getTotalScore() > b.getTotalScore();
}

bool idCheck(vector<Player> players, string id) {
    if (id.length() != 5) {
        system("CLS");
        cout << "Invalid ID format. Please enter a 5-digit number." << endl;
        return false;
    }
    for (char ch : id) {
        if (!isdigit(ch)) {
            system("CLS");
            cout << "Invalid ID format. Please enter a 5-digit number." << endl;
            return false;
        }
    }
    for (auto player : players) {
        if (player.get_ID() == id) {
            system("CLS");
            cout << "This ID already exists. Please enter a different ID." << endl;
            return false;
        }
    }
    return true;
}

bool isString(string str) {
    for (char ch : str) {
        if (!(ch >= 'a' && ch <= 'z') && (!(ch >= 'A' && ch <= 'Z'))) {
            return false;
        }
    }
    return true;
}

bool isPositive(int a) {
    if (a < 0) return false;
    return true;
}

vector<Player> getTopPlayers(vector<Player> players, int count) {
    vector<Player> topPlayers = players;
    sort(topPlayers.begin(), topPlayers.end(), comparePlayers);
    if (topPlayers.size() > count) {
        topPlayers.resize(count);
    }
    return topPlayers;
}

int main() {
    char choice;

    vector<Player> dynamoPlayers = readPlayersFromFile("dinamo_players.txt");
    vector<Player> spartakPlayers = readPlayersFromFile("spartak_players.txt");
    vector<Player> allPlayers = dynamoPlayers;
    allPlayers.insert(allPlayers.end(), spartakPlayers.begin(), spartakPlayers.end());

    do {

        cout << "Menu:" << endl;
        cout << "1. Display a list of players" << endl;
        cout << "2. Output to a file result.txt and the top 6 players of both teams in total points (goals + passes) are shown on the screen" << endl;
        cout << "3. Sorting methods" << endl;
        cout << "4. Delete by ID" << endl;
        cout << "5. Add a player" << endl;
        cout << "0. Exiting the program" << endl;
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            system("CLS");
            cout << "Dynamo Team players:" << endl;
            printPlayers(dynamoPlayers);
            cout << endl;
            cout << "Spartak Team players:" << endl;
            printPlayers(spartakPlayers);
            cout << endl;
            break;
        }
        case '2': {
            system("CLS");

            vector<Player> topPlayers = getTopPlayers(allPlayers, 6);

            ofstream outputFile("result.txt");
            if (outputFile.is_open()) {
                for (auto player : topPlayers) {
                    outputFile << player;
                }
                outputFile.close();
                cout << "The results are recorded in a file result.txt" << endl << endl;
            }
            else {
                cout << "File opening error result.txt" << endl;
            }

            cout << "Best players:" << endl;
            printPlayers(topPlayers);
            cout << endl;
            break;
        }
        case '3': {
            system("CLS");
            cout << "Which team should sort? (1.dynamo/2.spartak/3.all/0.return to main)" << endl;
            string team;
            if (team == "0") {
                system("CLS");
                break;
            }
            cin >> team;
            transform(team.begin(), team.end(), team.begin(), ::tolower);
            vector<Player> Players;
            if (team == "1") {
                Players = dynamoPlayers;
            }
            else if (team == "2") {
                Players = spartakPlayers;
            }
            else if (team == "3") {
                Players = allPlayers;
            }
            else {
                cout << "Invalid team name." << endl;
                break;
            }
            system("CLS");
            cout << "Select sorting method:" << endl;
            cout << "1. Last name" << endl;
            cout << "2. Number of passes" << endl;
            cout << "3. Number of goals" << endl;
            cout << "4. Penalty time" << endl;
            cout << "Enter your choice: ";
            char sortChoice;
            cin >> sortChoice;
            switch (sortChoice) {
            case '1':
                sort(Players.begin(), Players.end(), [](Player a, Player b) {
                    return a.get_Name1() < b.get_Name1();
                    });
                break;
            case '2':
                sort(Players.begin(), Players.end(), [](Player a, Player b) {
                    return a.get_Passes() > b.get_Passes();
                    });
                break;
            case '3':
                sort(Players.begin(), Players.end(), [](Player a, Player b) {
                    return a.get_Goals() > b.get_Goals();
                    });
                break;
            case '4':
                sort(Players.begin(), Players.end(), [](Player a, Player b) {
                    return a.get_PenaltyTime() > b.get_PenaltyTime();
                    });
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
            }
            system("CLS");
            cout << "Sorted players:" << endl;
            printPlayers(Players);
            cout << endl;
            break;
        }
        case '4': {
            system("CLS");
            cout << "Which team's players do you want to see?(1.dynamo/2.spartak/3.all) Or 0 to return to main screen " << endl;
            int team;
            cin >> team;
            switch (team) {
            case 1:
                system("CLS");
                cout << "Dynamo Team players:" << endl;
                printPlayers(dynamoPlayers);
                break;
            case 2:
                system("CLS");
                cout << "Spartak Team players:" << endl;
                printPlayers(spartakPlayers);
                break;
            case 3:
                system("CLS");
                cout << "Dynamo Team players:" << endl;
                printPlayers(dynamoPlayers);
                cout << endl;
                cout << "Spartak Team players:" << endl;
                printPlayers(spartakPlayers);
                break;
            case 0:
                system("CLS");
                cout << "Dynamo Team players:" << endl;
                printPlayers(dynamoPlayers);
                cout << endl;
                cout << "Spartak Team players:" << endl;
                printPlayers(spartakPlayers);
                break;
            default:
                system("CLS");
                cout << "Invalid choice. Showing all players." << endl;
                cout << "Dynamo Team players:" << endl;
                printPlayers(dynamoPlayers);
                cout << endl;
                cout << "Spartak Team players:" << endl;
                printPlayers(spartakPlayers);
                break;
            }

            string idToRemove;
            cout << endl << "Enter the ID of the player you want to delete or enter 0 to return on Main screen:  " << endl;
            cin >> idToRemove;
            if (idToRemove == "0") {
                system("CLS");
                break;
            }

            auto dynamoPlayerToRemove = find_if(dynamoPlayers.begin(), dynamoPlayers.end(), [idToRemove](Player p) { return p.get_ID() == idToRemove; });
            if (dynamoPlayerToRemove != dynamoPlayers.end()) {
                dynamoPlayers.erase(dynamoPlayerToRemove);
                writePlayersToFile(dynamoPlayers, "dinamo_players.txt");
                system("CLS");
                cout << "A player with ID " << idToRemove << " has been removed from the Dynamo team." << endl;
            }
            else {
                auto spartakPlayerToRemove = find_if(spartakPlayers.begin(), spartakPlayers.end(), [idToRemove](Player p) { return p.get_ID() == idToRemove; });
                if (spartakPlayerToRemove != spartakPlayers.end()) {
                    spartakPlayers.erase(spartakPlayerToRemove);
                    writePlayersToFile(spartakPlayers, "spartak_players.txt");
                    system("CLS");
                    cout << "A player with ID " << idToRemove << " has been removed from the Spartak team." << endl;
                }
                else {
                    system("CLS");
                    cout << "A player with ID " << idToRemove << " was not found." << endl;
                }
            }
            break;
        }
        case '5': {
            system("CLS");
            string id, team, name1, name2, name3;
            int goal, pass, penaltyTime;
            bool flag = 0;

            do {
                cout << "Enter the new player's ID (a 5-digit number) or enter 0 to return to the main menu: ";
                if (id == "0") {
                    system("CLS");
                    break;
                }
                cin >> id;
                flag = idCheck(allPlayers, id);

            } while (!flag);
            if (id == "0") break;

            do {
                cout << "Enter the name of the new player's team(1.Dynamo/2.Spartak): ";
                cin >> team;
                if (team == "1") { system("CLS"); 
                    cout << "Dynamo" << endl;  team = "Dynamo"; break;
                }
                else if (team == "2") { system("CLS");
                    cout << "Spartak" << endl; team = "Spartak"; break;
                }
                else {
                    system("CLS");
                    cout << "Enter currect team." << endl;
                }
            } while (true);

            do {
                cout << "Enter the name of the new player (separated by a space: last name, first name, patronymic): ";
                cin >> name1 >> name2 >> name3;
                if (!isString(name1) && !isString(name2) && !isString(name3)) {
                    system("CLS");
                    cout << "Enter currect letters." << endl;
                }
                else break;
            } while (true);

            do {
                cout << "Enter the number of goals of the new player: ";
                cin >> goal;
                cout << "Enter the number of new player's passes: ";
                cin >> pass;
                cout << "Enter the number of minutes of the new player's penalty time: ";
                cin >> penaltyTime;
                if (!isPositive(goal) && !isPositive(pass) && !isPositive(penaltyTime)) {
                    system("CLS");
                    cout << "Enter a positive integer numbers only" << endl;
                }
                else break;
            } while (true);

            Player newPlayer(id, team, name1, name2, name3, goal, pass, penaltyTime);
            if (team == "Dynamo") {
                dynamoPlayers.push_back(newPlayer);
                writePlayersToFile(dynamoPlayers, "dinamo_players.txt");
                cout << "The player are recorded in a file dinamo_players.txt" << endl;
            }
            else if (team == "Spartak") {
                spartakPlayers.push_back(newPlayer);
                writePlayersToFile(spartakPlayers, "spartak_players.txt");
                cout << "The player are recorded in a file spartak_players.txt" << endl;
            }
            system("CLS");
            break;

        }
        case '0':
            system("CLS");
            cout << "Exit the program." << endl;
            break;
        default:
            system("CLS");
            cout << "Wrong choice. Please select again." << endl;
            break;
        }

    } while (choice != '0');

    return 0;
}
