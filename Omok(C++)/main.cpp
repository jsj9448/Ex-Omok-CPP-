//
//  main.cpp
//  Omok(C++)
//
//  Created by 조성진 on 17/11/2018.
//  Recently updated on 25/11/2018.
//  Copyright © 2018 조성진. All rights reserved.
//

#include <iostream>
#include "sstream"
#include "string"
using namespace std;

enum color { White = 1, Black, Empty };

class OMOK {
protected:
    int m_col, m_row, m_x, m_y, m_color;
    string m_symbol = "┼";
    string m_StoneColor = "●";
    string Board[11][21];
public:
    OMOK();
    void StoneSet(int const&);
    void DrawBoard();
    void RefreshBoard(const int&, const int&);
    bool IsPlaced(const int&, const int&);
    bool WhoIsTurn(int const&);
    void ChangeTurn(int&);
    color WhoIsWinner();
};

OMOK::OMOK() : m_col(21), m_row(11), m_x(0), m_y(0), m_color(1) {}

void OMOK::StoneSet(int const &color) {
    if(color == 1) m_StoneColor = "●";
    else m_StoneColor = "○";
}

void OMOK::DrawBoard() {
    for(int i(0); i < m_row; i++) {            //세로
        for(int j(0); j < m_col; j++) {        //가로
            string symbol = m_symbol;
            //string symbol = "+";
            //i(10), j(0) : 가로-세로 행열번호 넣을 곳
            stringstream sstr;
            int temp(m_row);
            
            if(i >= 0 && i < 10 && j == 0) {
                temp -= (i + 2);
                sstr << temp;
                symbol = sstr.str();
            }
            else if(i == 0) {
                if(j == 1 || j == m_col - 1) {
                    if(j == 1) {
                        symbol = "┌";
                    }
                    if(j == m_col - 1) {
                        symbol = "┐";
                    }
                }
                else symbol = "┬";
            }
            else if(i == 9) {
                if(j == 1 || j == 20) {
                    if(j == 1) {
                        symbol = "└";
                    }
                    if(j == 20) {
                        symbol = "┘";
                    }
                }
                else symbol = "┴";
            }
            else if(i == 10 && j >= 0) {
                /*stringstream sstr;
                int temp(j - 1);
                sstr << temp;
                symbol = sstr.str();*/
                symbol = " ";
             }
            else {
                if(j == 1 || j == 20) {
                    if(j == 1) symbol = "├";
                    if(j == 20) symbol = "┤";
                }
            }
            
            cout << symbol;
            Board[i][j] = symbol;
        }
        cout << endl;
    }

}

void OMOK::RefreshBoard(const int &x, const int &y) {
        //0,0 -> 0,9
        //9,0 -> 9,9
        //0,9 -> 0,0
        //9,9 -> 9,0
    m_x = x;
    m_y = m_row - (y + 2);
    
    for(int i(0); i < m_row; i++) {
        for(int j(0); j < m_col; j++) {
            if(i == m_y && j == m_x + 1)
                Board[i][j] = m_StoneColor;
            cout << Board[i][j];
        }
        cout << endl;
    }
}

bool OMOK::IsPlaced(const int &x, const int &y) {
    if(Board[x][y] == m_StoneColor) return true;
    else return false;
}

bool OMOK::WhoIsTurn(int const &color) {
    m_color = color;
    if(color == White) return true;
    else return false;
}

void OMOK::ChangeTurn(int &turn) {
    if(turn == White) {
        turn += 1;
        m_StoneColor = "○";
    }
    else {
        turn -= 1;
        m_StoneColor = "●";
    }
}

color OMOK::WhoIsWinner() {
    int check(0);
    
    for(int i(0); i < m_row; i++) {
        for(int j(0); j < m_col; j++) {
            //돌을 발견한 순간을 시작점으로 잡는다.
            if(Board[i][j] == m_StoneColor) {
                //해당 돌 색깔을 기준으로 잡고
                string ThisStone = Board[i][j];
                //기준돌 이하로 쭈욱 스캔

                //기준돌 이후로 같은 돌이 놓여있을 경우
                //이상한 에러남 수정하기
                if(ThisStone == Board[i + 1][j] && ThisStone == Board[i + 2][j] && ThisStone == Board[i + 3][j] && ThisStone == Board[i + 4][j]) {
                    check++;
                }
                else if(ThisStone == Board[i][j + 1] && ThisStone == Board[i][j + 2] && ThisStone == Board[i][j + 3] && ThisStone == Board[i][j + 4]) {
                    check++;
                }
                else if(ThisStone == Board[i + 1][j + 1] && ThisStone == Board[i + 2][j + 2] && ThisStone == Board[i + 3][j + 3] && ThisStone == Board[i + 4][j + 4]) {
                    check++;
                }
                else if(ThisStone == Board[i - 1][j - 1] && ThisStone == Board[i - 2][j - 2] && ThisStone == Board[i - 3][j - 3] && ThisStone == Board[i - 4][j - 4]) {
                    check++;
                }
                
                
                if(check == 5) {
                    if(WhoIsTurn(m_color)) return White;
                    else return Black;
                }
            }
        }
    }
    return Empty;
}


int main() {
    char menu;
    int color(1), x(0), y(0);
    string StoneColor;
    OMOK myOmok;
    
    cout << "오목 게임을 시작합니다!" << endl;
    cout << "이 게임은 좌표입력으로 돌을 두며 진행됩니다." << endl << endl;
    while(true) {
        cout << "1. 시작" << endl;
        cout << "2. 종료" << endl << endl;
        cout << "메뉴 선택 : ";
        cin >> menu;
        if(menu == '2') break;
        else if(menu != '1') {
            cout << "잘못 입력하셨습니다. 다시 입력해주세요." << endl;
            continue;
        }
        else {
            cout << endl << "돌 색상을 선택해주세요." << endl;
            cout << "1. 백돌(●)" << endl;
            cout << "2. 흑돌(○)" << endl;
            cout << "돌 선택 : ";
            cin >> color;
            if(color == White) {
                cout << "백돌로 시작합니다. 선공입니다." << endl;
            }
            else if(color == Black) {
                cout << "흑돌로 시작합니다. 후공입니다." << endl;
            }
            else {
                cout << "잘못 선택하셨습니다. 다시 선택해주세요." << endl;
                break;
            }
            myOmok.StoneSet(color);
            myOmok.DrawBoard();
        }
        
        while(myOmok.WhoIsWinner() == Empty) {
            if(myOmok.WhoIsTurn(color)) {
                cout << "백돌의 순서입니다. 놓을 위치(x, y) : ";
            }
            else {
                cout << "흑돌의 순서입니다. 놓을 위치(x, y) : ";
            }
            cin >> x >> y;
            if((x > 20 || y > 10) || myOmok.IsPlaced(x, y)) {
                cout << "돌을 잘못 두셨습니다. 다시 놓아주세요." << endl;
                continue;
            }
            cout << endl;
            myOmok.RefreshBoard(x, y);
            
            if(myOmok.WhoIsWinner() == White) {
                cout << endl << "***** 백돌의 승리입니다! *****" << endl;
                break;
            }
            if(myOmok.WhoIsWinner() == Black) {
                cout << endl << "***** 흑돌의 승리입니다! *****" << endl;
                break;
            }
            
            myOmok.ChangeTurn(color);
        }
        
    }
    
    return 0;
}
