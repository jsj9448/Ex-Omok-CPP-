//
//  main.cpp
//  Omok(C++)
//
//  Created by 조성진 on 17/11/2018.
//  Recently updated on 30/11/2018.
//  Copyright © 2018 조성진. All rights reserved.
//

#include <iostream>
#include "Omok.hpp"


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
            cout << "1. 백돌(○)" << endl;
            cout << "2. 흑돌(●)" << endl;
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
            if(myOmok.WhoIsTurn(color) == true) {
                cout << "백돌의 순서입니다. 놓을 위치(x, y) : ";
            }
            else {
                cout << "흑돌의 순서입니다. 놓을 위치(x, y) : ";
            }
            cin >> x >> y;
            if(x > 19 || y > 10 || x < 0 || y < 0) {
                cout << "돌을 잘못 두셨습니다. 다시 놓아주세요." << endl;
                continue;
            }
            if(myOmok.IsPlaced(x, y)) {
                cout << endl << "돌이 이미 놓여져 있습니다. 다시 놓아주세요." << endl;
                continue;
            }
            cout << endl;
            myOmok.RefreshBoard(x, y);
            
            if(myOmok.WhoIsWinner() == White) {
                cout << endl << "***** 백돌(○)의 승리입니다! *****" << endl;
                break;
            }
            if(myOmok.WhoIsWinner() == Black) {
                cout << endl << "***** 흑돌(●)의 승리입니다! *****" << endl;
                break;
            }
            
            myOmok.ChangeTurn(color);
        }
        
    }
    
    return 0;
}
