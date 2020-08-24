//
//  Field.cpp
//  ee
//
//  Created by Денис Гончаров on 19.08.2020.
//  Copyright © 2020 Денис Гончаров. All rights reserved.
//

#include "Field.hpp"

Field::Field() : is_selected(false), ready_to_move(false)
{
    field.resize(BOARD_SIZE, std::vector<Pawn>(BOARD_SIZE));
    for (size_t i(0); i < BOARD_SIZE; ++i)
    {
        for (size_t j(0); j < BOARD_SIZE; ++j)
        {
            Pawn fig = create_figure(j, i);
            field[i][j] = fig;
        }
    }
    
    for (size_t i(0); i < BOARD_SIZE; ++i)
    {
        squares.resize(BOARD_SIZE);
        for (size_t j(0); j < BOARD_SIZE; ++j)
        {
            RectangleShape square(Vector2f(CELL_SIZE, CELL_SIZE));
            square.setPosition(square.getSize().x * j, square.getSize().y * i);
            
            if ((i + j) % 2 == 0)
            {
                square.setFillColor(Color::White);
            }
            else
            {
                square.setFillColor(Color(110, 1, 29));
            }
            
            squares[i].push_back(square);
        }
    }
}

ChessField &Field::get_field()
{
    return field;
}

void Field::update_field(const ChessField &_field)
{
    field = _field;
}

void Field::check_for_select(int x, int y)
{
    std::cout << "check for select" << std::endl;
    int x1 = -1, y1 = -1;
    for (size_t i(0); i < field.size(); ++i)
    {
        for(size_t j(0); j < field[i].size(); ++j)
        {
            field[i][j].unselected();
            if (field[i][j].get_figure().getGlobalBounds().contains(x, y))
            {
                x1 = i;
                y1 = j;
            }
            is_selected = false;
        }
    }
    if (x1 >= 0)
    {
        field[x1][y1].selected();
        is_selected = true;
    }
    
}

void Field::check_for_step(int x, int y, sf::Music &step)
{
    std::cout << "check for step" << std::endl;
    for (size_t i(0); i < field.size(); ++i)
    {
        for(size_t j(0); j < field[i].size(); ++j)
        {
            if (field[i][j].get_figure().getGlobalBounds().contains(x, y))
            {
                check_for_select(x, y);
                i = field.size();
                break;
            }
            else if (field[i][j].is_selected())
            {
                auto moves = possbly_moves(field[i][j]);
                
                x = x / 100;
                y = y / 100;
                
                for (size_t k(0); k < moves.size(); ++k)
                {
                    if (x  == moves[k].first && y == moves[k].second)
                    {
                        swap_cells(x, y, i, j);
                        is_selected = false;
                        step.play();
                        break;
                    }
                }
            }
        }
    }
}

void Field::draw(sf::RenderWindow &_window)
{
    for (size_t i(0); i < BOARD_SIZE; ++i)
    {
        for(size_t j(0); j < BOARD_SIZE; ++j)
            _window.draw(squares[i][j]);
    }
    
    for (size_t i(0); i < BOARD_SIZE; ++i)
    {
        for(size_t j(0); j < BOARD_SIZE; ++j)
            _window.draw(field[i][j].get_figure());
    }
}

Pawn Field::create_figure(int x, int y)
{
    Pawn fig(x, y, Types::NONE, Colors::NONE_COLOR, CELL_SIZE);
    
    if (y >= 0 && y < 3 && x >= 0 && x < 3)
        fig = Pawn(x, y, Types::PAWN, Colors::BLACK, CELL_SIZE);
    else if (y >= BOARD_SIZE - 3 && y < BOARD_SIZE && x >= BOARD_SIZE - 3 && y < BOARD_SIZE)
        fig = Pawn(x, y, Types::PAWN, Colors::WHITE, CELL_SIZE);

    return fig;
}

void Field::swap_cells(int x, int y, int x1, int y1)
{
    field[x][y] = field[x1][y1];
    field[x][y].set_position({x, y});
    field[x1][y1] = Pawn(x1, y1, Types::NONE, Colors::NONE_COLOR, CELL_SIZE);
    field[x][y].draw_new_position();
    field[x][y].unselected();
}

std::vector<std::pair<int, int> > Field::possbly_moves(const Pawn &fig)
{
    std::pair<int, int> pos = fig.get_position();
    int x = pos.first;
    int y = pos.second;
    
    std:: cout << x << " " << y << std::endl;

    std::vector<std::pair<int, int> > possible_moves;
    if (fig.get_type() == Types::PAWN)
    {
        if (y + 1 < BOARD_SIZE)
        {
            if (field[x][y + 1].get_type() != Types::PAWN)
                possible_moves.push_back(std::make_pair(x, y + 1));
        }
        if (y - 1 >= 0)
        {
            if (field[x][y - 1].get_type() != Types::PAWN)
                possible_moves.push_back(std::make_pair(x, y - 1));
        }
        
        if (x + 1 < BOARD_SIZE)
        {
            if (field[x + 1][y].get_type() != Types::PAWN)
                possible_moves.push_back(std::make_pair(x + 1, y));
        }
        
        if (x - 1 >= 0)
        {
            if (field[x - 1][y].get_type() != Types::PAWN)
            possible_moves.push_back(std::make_pair(x - 1, y));
        }
    }
    return possible_moves;
}

void Field::onMouseBtnPressed(Event& event, sf::Music &step)
{
    int x = event.mouseButton.x;
    int y = event.mouseButton.y;
    
    if (!is_selected)
        check_for_select(x, y);
    else
        check_for_step(x, y, step);
}
