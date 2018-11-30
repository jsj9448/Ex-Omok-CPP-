//
//  Omok.hpp
//  Omok(C++)
//
//  Created by 조성진 on 30/11/2018.
//  Copyright © 2018 조성진. All rights reserved.
//

#ifndef Omok_hpp
#define Omok_hpp

#include "string"
using namespace std;

enum color { White = 1, Black, Empty };

class OMOK {
protected:
    int m_col, m_row, m_x, m_y, m_color;
    string m_symbol = "┼";
    string m_StoneColor;
    string m_BlackStone = "●";
    string m_WhiteStone = "○";
    string Board[11][21];
public:
    OMOK();
    ~OMOK();
    void StoneSet(int const&);                  //돌 색깔 지정
    void PositionSet(const int&, const int&);   //입력한 좌표를 그림상 좌표로 보정해줌
    void DrawBoard();                           //바둑판 세팅
    void RefreshBoard(const int&, const int&);  //돌을 둘 때마다 판을 새로고침시킴
    bool IsPlaced(const int&, const int&);      //돌이 놓여있는지 확인해줌
    bool WhoIsTurn(int const&);                 //누구 차례인지 확인해줌
    void ChangeTurn(int&);                      //순서를 바꿔줌
    color WhoIsWinner();                        //누가 이겼는지 판별해줌
};

#endif /* Omok_hpp */
