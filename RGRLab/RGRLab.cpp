#include <iostream> 
#include <string> // Подключение библиотеки для работы со строками
#include <fstream> // Подключение библиотеки для работы с файлами
#include <vector> // Подключение библиотеки для работы с векторами
#include <algorithm> // Подключение библиотеки для использования алгоритмов, таких как sort и find_if
#include <cctype> // Подключение библиотеки для работы с функциями преобразования символов: isdigit, transform
using namespace std;

// Класс, представляющий игрока
class Player {
private:
    string ID;
    string name1, name2, name3, team;
    int goal;
    int pass;
    int penaltyTime;
public:
    // Конструктор с параметрами по умолчанию
    Player(string i = "", string t = "", string a = "", string b = "", string c = "", int d = 0, int e = 0, int f = 0)
        : ID(i), name1(a), name2(b), name3(c), team(t), goal(d), pass(e), penaltyTime(f) {}

    // Перегрузка оператора ввода
    friend istream& operator>>(istream& is, Player& player) {
        return is >> player.ID >> player.name1 >> player.name2 >> player.name3 >> player.team >> player.goal >> player.pass >> player.penaltyTime;
    }

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, Player& player) {
        return os << "ID: " << player.ID << ", Name: " << player.name1 << " " << player.name2 << " " << player.name3 << ", Team: " << player.team << ", Goals: " << player.goal << ", Passes: " << player.pass << ", Penalty time: " << player.penaltyTime << endl;
    }

    // Получение общего количества очков игрока
    int getTotalScore() {
        return goal + pass;
    }

    // Геттеры для членов класса
    string get_ID() { return ID; }
    string get_Name1() { return name1; }
    string get_Name2() { return name2; }
    string get_Name3() { return name3; }
    string get_Team() { return team; }
    int get_Goals() { return goal; }
    int get_Passes() { return pass; }
    int get_PenaltyTime() { return penaltyTime; }

    // Сеттеры для членов класса
    void set_ID(string a) { ID = a; }
    void set_Name1(string a) { name1 = a; }
    void set_Name2(string a) { name2 = a; }
    void set_Name3(string a) { name3 = a; }
    void set_Team(string a) { team = a; }
    void set_Goals(int a) { goal = a; }
    void set_Passes(int a) { pass = a; }
    void set_PenaltyTime(int a) { penaltyTime = a; }
};

// Функция для чтения данных об игроках из файла
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

// Функция для записи данных об игроках в файл
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

// Функция для вывода списка игроков на экран
void printPlayers(vector<Player> players) {
    for (auto player : players) {
        cout << player;
    }
}


// Функция для проверки формата ID
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

// Функция для проверки строки на наличие только букв
bool isString(string str) {
    for (char ch : str) {
        if (!(ch >= 'a' && ch <= 'z') && (!(ch >= 'A' && ch <= 'Z'))) {
            return false;
        }
    }
    return true;
}

// Функция для проверки положительных чисел
bool isPositive(int a) {
    return a >= 0;
}

// Функция для сравнения игроков по общему количеству очков
bool comparePlayers(Player a, Player b) {
    return a.getTotalScore() > b.getTotalScore();
}

// Функция для получения 6 лучших игроков по общему количеству очков
vector<Player> getTopPlayers(vector<Player> players, int count) {
    vector<Player> topPlayers = players;
    sort(topPlayers.begin(), topPlayers.end(), comparePlayers);
    if (topPlayers.size() > count) {
        topPlayers.resize(count);
    }
    return topPlayers;
}

void printTeamMenu(char team, vector<Player> dynamoPlayers, vector<Player> spartakPlayers) {
    // Выбор команды для отображения
    switch (team) {
    case '1':
        system("CLS");
        // Отображение игроков команды "Динамо"
        cout << "Dynamo Team players:" << endl;
        printPlayers(dynamoPlayers);
        break;
    case '2':
        system("CLS");
        // Отображение игроков команды "Спартак"
        cout << "Spartak Team players:" << endl;
        printPlayers(spartakPlayers);
        break;
    case '3':
        system("CLS");
        // Отображение игроков всех игроков
        cout << "Dynamo Team players:" << endl;
        printPlayers(dynamoPlayers);
        cout << endl << "Spartak Team players:" << endl;
        printPlayers(spartakPlayers);
        break;
    default:
        system("CLS");
        cout << "Invalid choice. Showing all players." << endl;
        // Отображение игроков всех игроков
        cout << "Dynamo Team players:" << endl;
        printPlayers(dynamoPlayers);
        cout << endl << "Spartak Team players:" << endl;
        printPlayers(spartakPlayers);
        break;
    }
}

void addPlayer(vector<Player>& dynamoPlayers, vector<Player>& spartakPlayers) {

}

// Основная функция программы
int main() {
    char choice;

    // Чтение данных об игроках из файлов
    vector<Player> dynamoPlayers = readPlayersFromFile("dinamo_players.txt");
    vector<Player> spartakPlayers = readPlayersFromFile("spartak_players.txt");
    vector<Player> allPlayers = dynamoPlayers;
    allPlayers.insert(allPlayers.end(), spartakPlayers.begin(), spartakPlayers.end());

    do {
        // Отображение главного меню
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
            // Очистка экрана
            system("CLS");
            cout << "Which team's players do you want to see?(1.dynamo/2.spartak/3.all)" << endl;
            char team;
            cin >> team;
            // Вывод меню для выбор команды для отображения 
            printTeamMenu(team, dynamoPlayers, spartakPlayers);
            cout << endl;
            break;
        }
        case '2': {
            system("CLS");

            // Получение списка топ-игроков
            vector<Player> topPlayers = getTopPlayers(allPlayers, 6);

            // Запись результатов в файл result.txt
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

            // Отображение лучших игроков на экране
            cout << "Best players:" << endl;
            printPlayers(topPlayers);
            cout << endl;
            break;
        }
        case '3': {
            system("CLS");
            cout << "Which team should sort? (1.dynamo/2.spartak/3.all). Type 0 to return to main screen: " << endl;
            string team;
            cin >> team;
            if (team == "0") {
                // Возвращение в главное меню
                system("CLS");
                break;
            }
            transform(team.begin(), team.end(), team.begin(), ::tolower);
            vector<Player> Players;
            // Определение команды для сортировки
            system("CLS");
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
                cout << "Invalid choice. Sorting all players." << endl << endl;
                Players = allPlayers; 
            }

            cout << "Select sorting method:" << endl;
            cout << "1. Last name" << endl;
            cout << "2. Number of passes" << endl;
            cout << "3. Number of goals" << endl;
            cout << "4. Penalty time" << endl;
            cout << "Enter your choice: ";
            char sortChoice;
            cin >> sortChoice;
            // Выбор метода сортировки
            switch (sortChoice) {
            case '1':
                // Сортировка по фамилии
                sort(Players.begin(), Players.end(), [](Player a, Player b) {
                    string str1 = a.get_Name1();
                    string str2 = b.get_Name1();
                    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
                    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
                    return str1 < str2;
                    });
                break;
            case '2':
                // Сортировка по количеству передач
                sort(Players.begin(), Players.end(), [](Player a, Player b) {
                    return a.get_Passes() > b.get_Passes();
                    });
                break;
            case '3':
                // Сортировка по количеству голов
                sort(Players.begin(), Players.end(), [](Player a, Player b) {
                    return a.get_Goals() > b.get_Goals();
                    });
                break;
            case '4':
                // Сортировка по штрафному времени
                sort(Players.begin(), Players.end(), [](Player a, Player b) {
                    return a.get_PenaltyTime() > b.get_PenaltyTime();
                    });
                break;
            default:
                cout << "Invalid choice. Sorting players by lastname." << endl;
                // Сортировка по фамилии
                sort(Players.begin(), Players.end(), [](Player a, Player b) {
                    string str1 = a.get_Name1();
                    string str2 = b.get_Name1();
                    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
                    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
                    return str1 < str2;
                    });
                break;
            }
            system("CLS");
            // Отображение отсортированных игроков
            cout << "Sorted players:" << endl;
            printPlayers(Players);
            cout << endl;
            break;
        }
        case '4': {
            system("CLS");
            cout << "Which team's players do you want to see?(1.dynamo/2.spartak/3.all). Type 0 to return to main screen: " << endl;    
            char team;
            cin >> team;
            if (team == '0') {
                system("CLS");
                break;
            }
            // Вывод меню для выбор команды для отображения 
            printTeamMenu(team, dynamoPlayers, spartakPlayers);
            // Ввод ID игрока для удаления
            string idToRemove;
            cout << endl << "Enter the ID of the player you want to delete or enter 0 to return on Main screen:  " << endl;
            cin >> idToRemove;
            if (idToRemove == "0") {
                system("CLS");
                break;
            }

            // Поиск и удаление игрока по ID
            auto dynamoPlayerToRemove = find_if(dynamoPlayers.begin(), dynamoPlayers.end(), [idToRemove](Player p) { return p.get_ID() == idToRemove; });
            if (dynamoPlayerToRemove != dynamoPlayers.end()) {
                dynamoPlayers.erase(dynamoPlayerToRemove);
                // Запись обновленного списка игроков в файл
                writePlayersToFile(dynamoPlayers, "dinamo_players.txt");
                system("CLS");
                cout << "A player with ID " << idToRemove << " has been removed from the Dynamo team." << endl;
            }
            else {
                auto spartakPlayerToRemove = find_if(spartakPlayers.begin(), spartakPlayers.end(), [idToRemove](Player p) { return p.get_ID() == idToRemove; });
                if (spartakPlayerToRemove != spartakPlayers.end()) {
                    spartakPlayers.erase(spartakPlayerToRemove);
                    // Запись обновленного списка игроков в файл
                    writePlayersToFile(spartakPlayers, "spartak_players.txt");
                    system("CLS");
                    cout << "A player with ID " << idToRemove << " has been removed from the Spartak team." << endl << endl;
                }
                else {
                    system("CLS");
                    cout << "A player with ID " << idToRemove << " was not found." << endl << endl;
                }
            }
            break;
        }
        case '5': {
            system("CLS");
            string id, team, name1, name2, name3;
            int goal, pass, penaltyTime;
            bool flag = 0;

            // Ввод ID нового игрока с проверкой
            do {
                cout << "Enter the new player's ID (a 5-digit number) or enter 0 to return to the main menu: ";
                cin >> id;
                if (id == "0") {
                    system("CLS");
                    break;
                }
                flag = idCheck(allPlayers, id);

            } while (!flag);
            if (id == "0") break;

            // Ввод команды нового игрока
            do {
                cout << "Enter the name of the new player's team (1.Dynamo/2.Spartak): " << endl;
                cin >> team;
                if (team == "1") {
                    system("CLS");
                    cout << "Dynamo" << endl; team = "Dynamo"; break;
                }
                else if (team == "2") {
                    system("CLS");
                    cout << "Spartak" << endl; team = "Spartak"; break;
                }
                else {
                    system("CLS");
                    cout << "Enter correct team." << endl;
                }
            } while (true);

            // Ввод имени нового игрока
            do {
                cout << "Enter the name of the new player (separated by a space: last name, first name, patronymic): ";
                cin >> name1 >> name2 >> name3;
                if (!isString(name1) && !isString(name2) && !isString(name3)) {
                    system("CLS");
                    cout << "Enter correct letters." << endl;
                }
                else break;
            } while (true);

            // Ввод данных о голах, передачах и штрафном времени нового игрока
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

            // Создание нового игрока и добавление его в соответствующий список
            Player newPlayer(id, team, name1, name2, name3, goal, pass, penaltyTime);
            if (team == "Dynamo") {
                dynamoPlayers.push_back(newPlayer);
                // Запись обновленного списка игроков в файл
                writePlayersToFile(dynamoPlayers, "dinamo_players.txt");
                cout << "The player is recorded in a file dinamo_players.txt" << endl << endl;
            }
            else if (team == "Spartak") {
                spartakPlayers.push_back(newPlayer);
                // Запись обновленного списка игроков в файл
                writePlayersToFile(spartakPlayers, "spartak_players.txt");
                cout << "The player is recorded in a file spartak_players.txt" << endl << endl;
            }
            system("CLS");
            break;
        }
        case '0':
            system("CLS");
            cout << "Exit the program." << endl;
            break;
        default:
            // Обработка неверного выбора
            system("CLS");
            cout << "Wrong choice. Please select again." << endl << endl;
            break;
        }

    } while (choice != '0');

    return 0;
}
