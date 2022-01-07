#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

vector<vector<vector<char>>> you(12, vector<vector<char>>(12, vector<char>(3)));
vector<vector<vector<char>>> enemy(12, vector<vector<char>>(12, vector<char>(3)));
bool flag = 1;
int x0_finish, y0_finish, x_finish = -1, y_finish;
int k_you = 0, k_enemy = 0;
mt19937 mersenne(static_cast<unsigned int>(time(0)));
void boardDrawing();
void filling(vector<vector<vector<char>>> &somebody);
void shotByYou();
void shotByEnemy();
void fillWithDots(vector<vector<vector<char>>> &somebody, int x, int y);
bool allDestroyed(vector<vector<vector<char>>> somebody, int x, int y);
void finishTheBattleshipOff();

int main()
{
    setlocale(0, "");

    filling(enemy);
    for(int i = 1; i < 11; ++i)
        for(int j = 1; j < 11; ++j) enemy[i][j][1] = 'n';

    char choice;
    do {
        filling(you);
        boardDrawing();
        cout << "\t���������� ������������ ��������?\n\n\t0\t      - ���, ����� ��������\n\t����� ������� - ��, ��� �����!\n";
        cout << "\t"; choice = _getche();
    }while(choice == '0');

    do {
        shotByYou();
        if(k_you >= 20 || k_enemy >= 20) break;
        shotByEnemy();
    }while(k_you < 20 && k_enemy < 20);

    if(k_enemy == 20) {
        boardDrawing();
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "\n\t*****";
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "\t*****";
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "\t*****";
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "\n\t   *** ������! ***\n";
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "\t*****\t*****\t*****\n\n";
    }
    else {
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "\n\t��������� ((\n\n\t��-��, �������� ���\n";
    }

    return 0;
}

void finishTheBattleshipOff()
{
    int x, y, side;
    if(x_finish == -1) {
        do {
            side = mersenne() % 4;
            switch(side)
            {
                case 0: x = x0_finish - 1;
                        y = y0_finish;
                        break;
                case 1: x = x0_finish;
                        y = y0_finish + 1;
                        break;
                case 2: x = x0_finish + 1;
                        y = y0_finish;
                        break;
                case 3: x = x0_finish;
                        y = y0_finish - 1;
                        break;
            }
        }while(x < 1 || x > 10 || y < 1 || y > 10 || you[x][y][0] == '.');
        if(you[x][y][0] == ' ') {
            you[x][y][0] = '.';
            boardDrawing();
            shotByYou();
            finishTheBattleshipOff();
        }
        else if(you[x][y][0] == 'O') {
            you[x][y][0] = 'X';
            k_you++;
            if(allDestroyed(you, x, y)) {
                fillWithDots(you, x, y);
                boardDrawing();
                if(k_you >= 20) return;
            }
            else {
                x_finish = x;
                y_finish = y;
                finishTheBattleshipOff();
            }
        }

    }
    else {
        if(x0_finish > x_finish) swap(x0_finish, x_finish);
        if(y0_finish > y_finish) swap(y0_finish, y_finish);
        do {
            side = mersenne() % 2;
            if(side) {
                if(x0_finish == x_finish) {
                    x = x_finish;
                    y = y0_finish - 1;
                }
                else if(y0_finish == y_finish) {
                    x = x0_finish - 1;
                    y = y_finish;
                }
            }
            else {
                if(x0_finish == x_finish) {
                    x = x_finish;
                    y = y_finish + 1;
                }
                else if(y0_finish == y_finish) {
                    x = x_finish + 1;
                    y = y_finish;
                }
            }
        }while(x < 1 || x > 10 || y < 1 || y > 10 || you[x][y][0] == '.');
        if(you[x][y][0] == ' ') {
            you[x][y][0] = '.';
            boardDrawing();
            shotByYou();
            finishTheBattleshipOff();
        }
        else if(you[x][y][0] == 'O') {
            you[x][y][0] = 'X';
            k_you++;
            if(allDestroyed(you, x, y)) {
                fillWithDots(you, x, y);
                boardDrawing();
                if(k_you >= 20) return;
                x_finish = -1;
            }
            else {
                if(x < x0_finish) x0_finish = x;
                else if(x > x_finish) x_finish = x;
                if(y < y0_finish) y0_finish = y;
                else if(y > y_finish) y_finish = y;
                finishTheBattleshipOff();
            }
        }
    }
}

void shotByEnemy()
{
    int x, y;
    do {
        x = mersenne() % 10 + 1;
        y = mersenne() % 10 + 1;
    }while(you[x][y][0] == 'X' || you[x][y][0] == '.');
    if(you[x][y][0] == ' ') {
        you[x][y][0] = '.';
        boardDrawing();
    }
    else if(you[x][y][0] == 'O') {
        you[x][y][0] = 'X';
        k_you++;
        if(allDestroyed(you, x, y))
            fillWithDots(you, x, y);
        else {
            x0_finish = x;
            y0_finish = y;
            finishTheBattleshipOff();
        }
        boardDrawing();
        if(k_you >= 20) return;
        else shotByEnemy();
    }
}

void shotByYou()
{
    string s;
    int x, y;
    char ch_x, ch_y;
    if(flag) {
        boardDrawing();
        flag = 0;
    }
    coords:
    cout << "\t������� ���������� ��������: ";
    cin >> s;
    for(int i = 0; i < s.size(); ++i) s[i] = tolower(s[i]);
    ch_y = s[0];
    ch_x = s.back();
    switch(ch_x)
    {
        case '1': x = 1; break;
        case '2': x = 2; break;
        case '3': x = 3; break;
        case '4': x = 4; break;
        case '5': x = 5; break;
        case '6': x = 6; break;
        case '7': x = 7; break;
        case '8': x = 8; break;
        case '9': x = 9; break;
        case '0': x = 10; break;
        default: boardDrawing();
                cout << "\t�������� ����������\n";
                goto coords;
    }
    switch(ch_y)
    {
        case 'a': y = 1; break;
        case 'b': y = 2; break;
        case 'c': y = 3; break;
        case 'd': y = 4; break;
        case 'e': y = 5; break;
        case 'f': y = 6; break;
        case 'g': y = 7; break;
        case 'h': y = 8; break;
        case 'i': y = 9; break;
        case 'j': y = 10; break;
        default: boardDrawing();
                cout << "\t�������� ����������\n";
                goto coords;
    }
    if(enemy[x][y][0] == '.' || enemy[x][y][0] == 'X') {
        cout << "\n\t�� ���, �����? ���� �������� ���, �������� ��� ���";
        cin.get();
        cin.ignore();
        shotByYou();
    }
    if(enemy[x][y][0] == ' ') {
        enemy[x][y][1] = 'v';
        enemy[x][y][0] = '.';
    }
    else if(enemy[x][y][0] = 'O') {
        enemy[x][y][0] = 'X';
        enemy[x][y][1] = 'v';
        k_enemy++;
        if(allDestroyed(enemy, x, y))
            fillWithDots(enemy, x, y);
        boardDrawing();
        if(k_enemy >= 20) return;
        else shotByYou();
    }
}

bool allDestroyed(vector<vector<vector<char>>> somebody, int x, int y)
{
    if(somebody[x][y][0] == 'O') return 0;
    somebody[x][y][2] = 'm';
    if(somebody[x+1][y][0] == 'O') return 0;
    if(somebody[x-1][y][0] == 'O') return 0;
    if(somebody[x][y+1][0] == 'O') return 0;
    if(somebody[x][y-1][0] == 'O') return 0;

    if(somebody[x+1][y][0] == 'X' && somebody[x+1][y][2] != 'm') return allDestroyed(somebody, x+1, y);
    if(somebody[x-1][y][0] == 'X' && somebody[x-1][y][2] != 'm') return allDestroyed(somebody, x-1, y);
    if(somebody[x][y+1][0] == 'X' && somebody[x][y+1][2] != 'm') return allDestroyed(somebody, x, y+1);
    if(somebody[x][y-1][0] == 'X' && somebody[x][y-1][2] != 'm') return allDestroyed(somebody, x, y-1);

    return 1;
}

void fillWithDots(vector<vector<vector<char>>> &somebody, int x, int y)
{
    if(somebody[x-1][y][0] == ' ') {
        somebody[x-1][y][0] = '.';
        somebody[x-1][y][1] = 'v';
    }
    if(somebody[x+1][y][0] == ' ') {
        somebody[x+1][y][0] = '.';
        somebody[x+1][y][1] = 'v';
    }
    if(somebody[x][y-1][0] == ' ') {
        somebody[x][y-1][0] = '.';
        somebody[x][y-1][1] = 'v';
    }
    if(somebody[x][y+1][0] == ' ') {
        somebody[x][y+1][0] = '.';
        somebody[x][y+1][1] = 'v';
    }

    if(somebody[x+1][y+1][0] == ' ') {
        somebody[x+1][y+1][0] = '.';
        somebody[x+1][y+1][1] = 'v';
    }
    if(somebody[x-1][y+1][0] == ' ') {
        somebody[x-1][y+1][0] = '.';
        somebody[x-1][y+1][1] = 'v';
    }
    if(somebody[x+1][y-1][0] == ' ') {
        somebody[x+1][y-1][0] = '.';
        somebody[x+1][y-1][1] = 'v';
    }
    if(somebody[x-1][y-1][0] == ' ') {
        somebody[x-1][y-1][0] = '.';
        somebody[x-1][y-1][1] = 'v';
    }

    somebody[x][y][2] = 'f';

    if(somebody[x-1][y][0] == 'X' && somebody[x-1][y][2] == '.') fillWithDots(somebody, x-1, y);
    if(somebody[x+1][y][0] == 'X' && somebody[x+1][y][2] == '.') fillWithDots(somebody, x+1, y);
    if(somebody[x][y-1][0] == 'X' && somebody[x][y-1][2] == '.') fillWithDots(somebody, x, y-1);
    if(somebody[x][y+1][0] == 'X' && somebody[x][y+1][2] == '.') fillWithDots(somebody, x, y+1);
}

void filling(vector<vector<vector<char>>> &somebody)
{
    for(int i = 1; i < 11; ++i) {
        for(int j = 1; j < 11; ++j) {
            somebody[i][j][1] = 'v';
            somebody[i][j][0] = ' ';
            somebody[i][j][2] = ' ';
        }
    }
    int x0, y0, x1, y1, stop;
	
    do {
        x0 = mersenne() % 10 + 1;
        y0 = mersenne() % 10 + 1;
    }while(somebody[x0][y0][0] != ' ');
    int side;
    bool ok = 0;
    do {
        side = mersenne() % 4;
        switch(side)
        {
            case 0: if(x0 - 3 >= 1) {
                        ok = 1;
                        x1 = x0 - 3;
                        y1 = y0;
                        swap(x0, x1);
                    } break;
            case 1: if(y0 + 3 <= 10) {
                        ok = 1;
                        x1 = x0;
                        y1 = y0 + 3;
                    } break;
            case 2: if(x0 + 3 <= 10) {
                        ok = 1;
                        x1 = x0 + 3;
                        y1 = y0;
                    } break;
            case 3: if(y0 - 3 >= 1) {
                        ok = 1;
                        x1 = x0;
                        y1 = y0 - 3;
                        swap(y0, y1);
                    } break;
            default: cout << "\n\n������� ������������ ����������\n\n"; return;
        }
    }while(!ok);
    if(x0 != x1) {
        for(int i = x0; i <= x1; ++i) {
            somebody[i][y0][0] = 'O';
            somebody[i][y0][2] = '.';
            if(y0 > 1) somebody[i][y0-1][2] = '.';
            if(y0 < 10) somebody[i][y0+1][2] = '.';
        }
        if(x0 > 1) {
            somebody[x0-1][y0][2] = '.';
            if(y0 > 1) somebody[x0-1][y0-1][2] = '.';
            if(y0 < 10) somebody[x0-1][y0+1][2] = '.';
        }
        if(x1 < 10) {
            somebody[x1+1][y0][2] = '.';
            if(y0 > 1) somebody[x1+1][y0-1][2] = '.';
            if(y0 < 10) somebody[x1+1][y0+1][2] = '.';
        }
    }
    else {
        for(int i = y0; i <= y1; ++i) {
            somebody[x0][i][0] = 'O';
            somebody[x0][i][2] = '.';
            if(x0 > 1) somebody[x0-1][i][2] = '.';
            if(x0 < 10) somebody[x0+1][i][2] = '.';
        }
        if(y0 > 1) {
            somebody[x0][y0-1][2] = '.';
            if(x0 > 1) somebody[x0-1][y0-1][2] = '.';
            if(x0 < 10) somebody[x0+1][y0-1][2] = '.';
        }
        if(y1 < 10) {
            somebody[x0][y1+1][2] = '.';
            if(x0 > 1) somebody[x0-1][y1+1][2] = '.';
            if(x0 < 10) somebody[x0+1][y1+1][2] = '.';
        }
    }

    int count3 = 0;
    wrong_place3:
    do {
        x0 = mersenne() % 10 + 1;
        y0 = mersenne() % 10 + 1;
    }while(somebody[x0][y0][2] != ' ');
    ok = 0;
    side = -1;
    stop = 0;
    do {
        if(side == -1) side = mersenne() % 4;
        else side = (side + 1) % 4;
        switch(side)
        {
            case 0: if((x0 - 2 >= 1) && somebody[x0][y0][2] != '.' &&
                       somebody[x0-1][y0][2] != '.' && somebody[x0-2][y0][2] != '.') {
                        ok = 1;
                        x1 = x0 - 2;
                        y1 = y0;
                        swap(x0, x1);
                    }
                    break;
            case 1: if((y0 + 2 <= 10) && somebody[x0][y0][2] != '.' &&
                       somebody[x0][y0+1][2] != '.' && somebody[x0][y0+2][2] != '.') {
                        ok = 1;
                        x1 = x0;
                        y1 = y0 + 2;
                    }
                    break;
            case 2: if((x0 + 2 <= 10) && somebody[x0][y0][2] != '.' &&
                       somebody[x0+1][y0][2] != '.' && somebody[x0+2][y0][2] != '.') {
                        ok = 1;
                        x1 = x0 + 2;
                        y1 = y0;
                    }
                    break;
            case 3: if((y0 - 2 >= 1) && somebody[x0][y0][2] != '.' &&
                       somebody[x0][y0-1][2] != '.' && somebody[x0][y0-2][2] != '.') {
                        ok = 1;
                        x1 = x0;
                        y1 = y0 - 2;
                        swap(y0, y1);
                    }
                    break;
            default: cout << "\n\n������� ������������ ����������\n\n"; return;
        }
        if(++stop >= 5) goto wrong_place3;
    }while(!ok);
    if(x0 != x1) {
        for(int i = x0; i <= x1; ++i) {
            somebody[i][y0][0] = 'O';
            somebody[i][y0][2] = '.';
            if(y0 > 1) somebody[i][y0-1][2] = '.';
            if(y0 < 10) somebody[i][y0+1][2] = '.';
        }
        if(x0 > 1) {
            somebody[x0-1][y0][2] = '.';
            if(y0 > 1) somebody[x0-1][y0-1][2] = '.';
            if(y0 < 10) somebody[x0-1][y0+1][2] = '.';
        }
        if(x1 < 10) {
            somebody[x1+1][y0][2] = '.';
            if(y0 > 1) somebody[x1+1][y0-1][2] = '.';
            if(y0 < 10) somebody[x1+1][y0+1][2] = '.';
        }
    }
    else {
        for(int i = y0; i <= y1; ++i) {
            somebody[x0][i][0] = 'O';
            somebody[x0][i][2] = '.';
            if(x0 > 1) somebody[x0-1][i][2] = '.';
            if(x0 < 10) somebody[x0+1][i][2] = '.';
        }
        if(y0 > 1) {
            somebody[x0][y0-1][2] = '.';
            if(x0 > 1) somebody[x0-1][y0-1][2] = '.';
            if(x0 < 10) somebody[x0+1][y0-1][2] = '.';
        }
        if(y1 < 10) {
            somebody[x0][y1+1][2] = '.';
            if(x0 > 1) somebody[x0-1][y1+1][2] = '.';
            if(x0 < 10) somebody[x0+1][y1+1][2] = '.';
        }
    }
    if(++count3 < 2) goto wrong_place3;

    int count2 = 0;
    wrong_place2:
    do {
        x0 = mersenne() % 10 + 1;
        y0 = mersenne() % 10 + 1;
    }while(somebody[x0][y0][2] != ' ');
    ok = 0;
    side = -1;
    stop = 0;
    do {
        if(side == -1) side = mersenne() % 4;
        else side = (side + 1) % 4;
        switch(side)
        {
            case 0: if((x0 - 1 >= 1) && somebody[x0][y0][2] != '.' &&
                       somebody[x0-1][y0][2] != '.') {
                        ok = 1;
                        x1 = x0 - 1;
                        y1 = y0;
                        swap(x0, x1);
                    }
                    break;
            case 1: if((y0 + 1 <= 10) && somebody[x0][y0][2] != '.' &&
                       somebody[x0][y0+1][2] != '.') {
                        ok = 1;
                        x1 = x0;
                        y1 = y0 + 1;
                    }
                    break;
            case 2: if((x0 + 1 <= 10) && somebody[x0][y0][2] != '.' &&
                       somebody[x0+1][y0][2] != '.') {
                        ok = 1;
                        x1 = x0 + 1;
                        y1 = y0;
                    }
                    break;
            case 3: if((y0 - 1 >= 1) && somebody[x0][y0][2] != '.' &&
                       somebody[x0][y0-1][2] != '.') {
                        ok = 1;
                        x1 = x0;
                        y1 = y0 - 1;
                        swap(y0, y1);
                    }
                    break;
            default: cout << "\n\n������� ������������ ����������\n\n"; return;
        }
        if(++stop >= 5) goto wrong_place2;
    }while(!ok);
    if(x0 != x1) {
        for(int i = x0; i <= x1; ++i) {
            somebody[i][y0][0] = 'O';
            somebody[i][y0][2] = '.';
            if(y0 > 1) somebody[i][y0-1][2] = '.';
            if(y0 < 10) somebody[i][y0+1][2] = '.';
        }
        if(x0 > 1) {
            somebody[x0-1][y0][2] = '.';
            if(y0 > 1) somebody[x0-1][y0-1][2] = '.';
            if(y0 < 10) somebody[x0-1][y0+1][2] = '.';
        }
        if(x1 < 10) {
            somebody[x1+1][y0][2] = '.';
            if(y0 > 1) somebody[x1+1][y0-1][2] = '.';
            if(y0 < 10) somebody[x1+1][y0+1][2] = '.';
        }
    }
    else {
        for(int i = y0; i <= y1; ++i) {
            somebody[x0][i][0] = 'O';
            somebody[x0][i][2] = '.';
            if(x0 > 1) somebody[x0-1][i][2] = '.';
            if(x0 < 10) somebody[x0+1][i][2] = '.';
        }
        if(y0 > 1) {
            somebody[x0][y0-1][2] = '.';
            if(x0 > 1) somebody[x0-1][y0-1][2] = '.';
            if(x0 < 10) somebody[x0+1][y0-1][2] = '.';
        }
        if(y1 < 10) {
            somebody[x0][y1+1][2] = '.';
            if(x0 > 1) somebody[x0-1][y1+1][2] = '.';
            if(x0 < 10) somebody[x0+1][y1+1][2] = '.';
        }
    }
    if(++count2 < 3) goto wrong_place2;

    int count1 = 0;
    wrong_place1:
    do {
        x0 = mersenne() % 10 + 1;
        y0 = mersenne() % 10 + 1;
    }while(somebody[x0][y0][2] != ' ');
    somebody[x0][y0][0] = 'O';
    somebody[x0][y0][2] = '.';
    if(x0 > 1) {
        somebody[x0-1][y0][2] = '.';
        if(y0 > 1) {
            somebody[x0-1][y0-1][2] = '.';
            somebody[x0][y0-1][2] = '.';
        }
        if(y0 < 10) {
            somebody[x0-1][y0+1][2] = '.';
            somebody[x0][y0+1][2] = '.';
        }
    }
    if(x0 < 10) {
        somebody[x0+1][y0][2] = '.';
        if(y0 > 1) somebody[x0+1][y0-1][2] = '.';
        if(y0 < 10) somebody[x0+1][y0+1][2] = '.';
    }
    if(++count1 < 4) goto wrong_place1;
}

void boardDrawing()
{
    system("cls");
        cout << "\n\t\t\t\t  ���� ����\t\t\t\t\t\t\t\t   ��������� ����\n\n\t";
        cout << "\t\t\t\t\t\t\t\t\t       A     B     C     D     E     F     G     H     I     J\n\t";
        cout << " _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ \t\t     _____ _____ _____ _____ _____ _____ _____ _____ _____ _____\n\t";
    for(int i = 1; i < 11; ++i) {
        cout << "|     |     |     |     |     |     |     |     |     |     |\t\t    |     |     |     |     |     |     |     |     |     |     |\n\t";
        cout << "|";
        for(int j = 1; j < 11; ++j) {
            cout << "  ";
            if(you[i][j][1] != 'n') cout << you[i][j][0] << "  |";
            else cout << "   |";
        }
        if(i != 10) cout << "\t\t " << i << "  |";
        else cout << "\t\t10  |";
        for(int j = 1; j < 11; ++j) {
            cout << "  ";
            if(enemy[i][j][1] != 'n') cout << enemy[i][j][0] << "  |";
            else cout << "   |";
        }
        cout << "\n\t|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\t\t    |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n\t";
    }
    cout << "\n";
}
