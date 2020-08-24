//
//  Pawn.cpp
//  ee
//
//  Created by Денис Гончаров on 19.08.2020.
//  Copyright © 2020 Денис Гончаров. All rights reserved.
//

#include "Pawn.hpp"

Pawn::Pawn(int _x, int _y, Types _type, Colors _color, const float cell_size)
          : x(_x),
            y(_y),
            type(_type),
            color(_color),
            _selected(false)
{
    if (_type == Types::PAWN)
    {
        figure = RectangleShape(Vector2f(50.f, 80.f));
        figure.setPosition(_x * cell_size, _y * cell_size);
        figure.setFillColor(Color::Green);
    }
}

void Pawn::set_position(std::pair<int, int> _pos)
{
    x = _pos.first;
    y = _pos.second;
}

void Pawn::set_type(Types _type)
{
    type = _type;
}

void Pawn::set_color(Colors _color)
{
    color = _color;
}

std::pair<int, int> Pawn::get_position() const
{
    std::pair<int, int> pair = std::make_pair(x, y);
    return pair;
}

Types Pawn::get_type() const
{
    return type;
}

Colors Pawn::get_color() const
{
    return color;
}

RectangleShape &Pawn::get_figure()
{
    return figure;
}

bool Pawn::is_selected() const
{
    return _selected;
}

void Pawn::selected()
{
    if (type == Types::PAWN)
    {
        figure.setScale(1.1f, 1.15f);
        _selected = true;
    }
}

void Pawn::unselected()
{
    if (type == Types::PAWN)
    {
        figure.setScale(1.0f, 1.0f);
        _selected = false;
    }
}

void Pawn::draw_new_position()
{
    if (type == Types::PAWN)
    {
        figure.setPosition(100.f * x, 100.f * y);
    }
}
