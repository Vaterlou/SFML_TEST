//
//  Field.hpp
//  ee
//
//  Created by Денис Гончаров on 19.08.2020.
//  Copyright © 2020 Денис Гончаров. All rights reserved.
//

#ifndef Field_hpp
#define Field_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Pawn.hpp"

const int BOARD_SIZE = 8;
const float CELL_SIZE = 100.f;

using ChessField = std::vector<std::vector<Pawn> >;

class Field
{
public:
    Field();
    
    ChessField &get_field();
    void update_field(const ChessField &_field);
    void check_for_select(int x, int y);
    void check_for_step(int x, int y, sf::Music &step);
    void draw(sf::RenderWindow &_window);
    std::vector<std::pair<int, int> > possbly_moves(const Pawn &fig);
    
    void onMouseBtnPressed(Event& event, sf::Music &step);
private:
    Pawn create_figure(int x, int y);
    void swap_cells(int x, int x1, int y, int y1);
    ChessField field;
    std::vector<std::vector<RectangleShape>> squares;
    
    bool is_selected, ready_to_move;
};

#endif /* Field_hpp */
