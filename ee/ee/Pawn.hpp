//
//  Pawn.hpp
//  ee
//
//  Created by Денис Гончаров on 19.08.2020.
//  Copyright © 2020 Денис Гончаров. All rights reserved.
//

#ifndef Pawn_hpp
#define Pawn_hpp

#include <stdio.h>
#include <utility>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

enum Types { NONE, PAWN };
enum Colors { NONE_COLOR, BLACK, WHITE };


class Pawn
{
public:
    Pawn() = default;
    Pawn( int _x, int _y, Types _type, Colors _color, const float cell_size);

    void set_position(std::pair<int, int> _pos);
    void set_type(Types _type);
    void set_color(Colors _color);

    std::pair<int, int> get_position() const;
    Types get_type() const;
    Colors get_color() const;
    RectangleShape &get_figure();
    bool is_selected() const;
    
    void selected();
    void unselected();
    
    void draw_new_position();
    
private:
    int x, y;
    Types type;
    Colors color;
    
    RectangleShape figure;
    bool _selected;
};

#endif /* Pawn_hpp */
