//
//  Omok.cpp
//  Omok(C++)
//
//  Created by 조성진 on 30/11/2018.
//  Copyright © 2018 조성진. All rights reserved.
//

#include "iostream"
#include "sstream"
#include "Omok.hpp"


OMOK::OMOK() : m_col(21), m_row(11), m_x(0), m_y(0), m_color(1) {}
OMOK::~OMOK() {}

void OMOK::StoneSet(int const &color) {
    if(color == White) m_StoneColor = m_WhiteStone;
    else m_StoneColor = m_BlackStone;
}

void OMOK::PositionSet(const int &x, const int &y) {
    m_x = x;
    m_y = m_row - (y + 2);
}

void OMOK::DrawBoard() {
    for(int i(0); i < m_row; i++) {            //세로
        for(int j(0); j < m_col; j++) {        //가로
            string symbol = m_symbol;
            //string symbol = "+";
            //i(10), j(0) : 가로-세로 행열번호 넣을 곳
            stringstream sstr;
            int temp(m_row);
            
            //세로좌표 매기는 부분. int -> string 형으로 바꿔서 배열에 저장한다.
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
            //가로좌표번호를 매기는 부분. 출력시 그림판이 홀쭉하게나와서 0~9 까지만 출력
            else if(i == 10 && j >= 0) {
                stringstream sstr;
                int temp(j - 1);
                if(temp >= 0 && temp < 10) {
                    sstr << temp;
                    symbol = sstr.str();
                }
                else symbol = " ";
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
    PositionSet(x, y);
    
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
    //RefreshBoard 에서 위치조정을 해줬으니까, 여기서도 위치조정을 해서 놓여있는지 유무를 찾아야한다.
    PositionSet(x, y);
    if(Board[m_y][m_x + 1] == m_WhiteStone || Board[m_y][m_x + 1] == m_BlackStone) return true;
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
        m_StoneColor = m_BlackStone;
    }
    else {
        turn -= 1;
        m_StoneColor = m_WhiteStone;
    }
}

color OMOK::WhoIsWinner() {
    int check(0);
    
    for(int i(0); i < m_row - 1; i++) {
        for(int j(1); j < m_col; j++) {
            //돌을 발견한 순간을 시작점으로 잡는다.
            if(Board[i][j] == m_BlackStone || Board[i][j] == m_WhiteStone) {
                //해당 돌 색깔을 기준으로 잡고
                string ThisStone = Board[i][j];
                //기준돌 이하로 쭈욱 스캔
                int ti(i), tj(j);
                //기준돌 이후로 같은 돌이 놓여있을 경우
                //가로 --- 이상 무
                while(tj < j + 5 && j + 5 < m_col) {
                    if(ThisStone == Board[ti][tj]) {
                        tj++;
                        check++;
                    }
                    else {
                        tj = j;
                        check = 0;
                        break;
                    }
                }
                //세로 --- 이상 무
                while(ti < i + 5 && i + 5 < m_row) {
                    if(ThisStone == Board[ti][tj]) {
                        ti++;
                        check++;
                    }
                    else {
                        ti = i;
                        check = 0;
                        break;
                    }
                }
                //대각선 남동방향(4사)
                while(ti < i + 5 && tj < j + 5 && i + 5 < m_row && j + 5 < m_col) {
                    if(ThisStone == Board[ti][tj]) {
                        ti++;
                        tj++;
                        check++;
                    }
                    else {
                        ti = i;
                        tj = j;
                        check = 0;
                        break;
                    }
                }
                //대각선 남서방향(3사)
                while(ti < i + 5 && tj > j - 5 && i + 5 < m_row && j - 5 > 0) {
                    if(ThisStone == Board[ti][tj]) {
                        ti++;
                        tj--;
                        check++;
                    }
                    else {
                        check = 0;
                        break;
                    }
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

