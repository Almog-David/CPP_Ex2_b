#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Direction.hpp"
#include "Notebook.hpp"
using namespace std;
using namespace ariel;

Notebook::Notebook(){};
Notebook::~Notebook(){};

void Notebook::write(int page, int row, int col, Direction direction, string text)
{
    /* first we will check for every bad input we could get from the user in order to throw exception*/
    if (page < 0 || row < 0 || col < 0) /* if one of the numbers is negetive */
    {
        throw std::invalid_argument("invalid number");
    }
    if (direction != Direction::Horizontal && direction != Direction::Vertical) /* if it's not valid direction */
    {
        throw std::invalid_argument("invalid direction! theres only Horizontal and Vertical");
    }
    if (col >= LIMIT) /* if the col number is 100 and more */
    {
        throw std::invalid_argument("the size of the row is 100 chars!");
    }
    if (direction == Direction::Horizontal && col + int(text.size()) >= LIMIT) /* if we went too far in the col */
    {
        throw std::invalid_argument("the size of the row is 100 chars!");
    }
    /*now we check if the string is valid or not by going through his chars*/
    for (size_t i = 0; i < text.size(); i++)
    {
        if (text[i] < ' ' || text[i] >= '~')
        {
            throw std::invalid_argument("invalid char inside the string");
        }
    }
    /* we will check if the page exist in the unordered map */
    if (this->notebook.find(page) == this->notebook.end())
    {
        unordered_map<int, vector<char>> temp;
        this->notebook.insert({page, temp}); /* add the page to the unordered map */
    }

    /* we will check if we wrote/delete from the following row/column since we cant write where the char isn't '_' */
    if (direction == Direction::Horizontal) /* 0 = Horizontal */
    {
        if (this->notebook.at(page).find(row) == this->notebook.at(page).end()) /* if the row doesnt exist */
        {
            vector<char> temp(LIMIT, '_');
            this->notebook[page][row] = temp;
        }

        for (size_t i = (size_t)col; i < (size_t)col + text.size(); i++)
        {
            if (this->notebook.at(page).at(row).at(i) != '_')
            {
                throw std::invalid_argument("you already wrote in this place!");
            }
        }
    }
    else /* 1 = Vertical */
    {
        for (size_t i = (size_t)row; i < (size_t)row + text.size(); i++)
        {
            if (this->notebook.at(page).find(i) == this->notebook.at(page).end())
            {
                vector<char> temp(LIMIT, '_');
                this->notebook.at(page).insert({i, temp});
            }

            if (this->notebook.at(page).at(i).at(size_t(col)) != '_')
            {
                throw std::invalid_argument("you already wrote in this place!");
            }
        }
    }
    /* if we reached to this spot it means that everything is valid and we didnt wrote/delete from the following
    row/column and we will start to write the text inside the notebook */
    size_t index = 0;
    if (direction == Direction::Horizontal)
    {
        // vector<char> line = this->notebook.at(page).at(row);
        for (size_t i = (size_t)col; i < (size_t)col + text.size(); i++)
        {
            this->notebook.at(page).at(row).at(i) = text.at(index);
            index++;
        }
    }

    else
    {
        for (size_t i = (size_t)row; i < (size_t)row + text.size(); i++)
        {
            this->notebook.at(page).at(i).at(size_t(col)) = text.at(index);
            index++;
        }
    }
}

string Notebook::read(int page, int row, int col, Direction direction, int numOfChars)
{
    /* first we will check for every bad input we could get from the user in order to throw exception*/
    if (page < 0 || row < 0 || col < 0 || numOfChars < 0) /* if one of the numbers is negetive */
    {
        throw std::invalid_argument("invalid number");
    }
    if (direction != Direction::Horizontal && direction != Direction::Vertical) /* if its not a valid direction */
    {
        throw std::invalid_argument("invalid direction! theres only Horizontal and Vertical");
    }
    if (col >= LIMIT) /* if the col number is 100 or more */
    {
        throw std::invalid_argument("the size of the row is 100 chars!");
    }
    if (direction == Direction::Horizontal && col + numOfChars > LIMIT) /* if the col + the number of chars is 100 or more */
    {
        throw std::invalid_argument("the size of the row is 100 chars!");
    }

    /* we will check if the page exist in the unordered map */
    if (this->notebook.find(page) == this->notebook.end())
    {
        unordered_map<int, vector<char>> temp;
        this->notebook.insert({page, temp}); /* add the page to the unordered map */
    }

    /* if we reached to this point it means that the values we got from the user are valid.
    now we will start to read from the notebook */
    string ans;
    if (numOfChars == 0) /* if we need to read 0 chars - return empty string */
    {
        return ans;
    }

    if (direction == Direction::Horizontal) /* if we need to read in horizontal */
    {
        if (this->notebook.at(page).find(row) == this->notebook.at(page).end())
        {
            vector<char> temp(LIMIT, '_');
            this->notebook.at(page).insert({row, temp});
        }

        vector<char> line = this->notebook.at(page).at(row);
        for (size_t i = (size_t)col; i < col + numOfChars; i++)
        {
            ans += this->notebook.at(page).at(row).at((size_t)i);
        }
    }

    else /* if we need to read in vertical */
    {
        for (size_t i = (size_t)row; i < row + numOfChars; i++)
        {
            if (this->notebook.at(page).find(i) == this->notebook.at(page).end())
            {
                vector<char> temp(LIMIT, '_');
                this->notebook.at(page).insert({i, temp});
            }

            vector<char> column = this->notebook.at(page).at(i);
            ans += this->notebook.at(page).at(i).at((size_t)col);
        }
    }
    return ans;
}
void Notebook::erase(int page, int row, int col, Direction direction, int numOfChars)
{
    /* first we will check for every bad input we could get from the user in order to throw exception*/
    if (page < 0 || row < 0 || col < 0 || numOfChars < 0) /* if one of the numbers is negetive */
    {
        throw std::invalid_argument("invalid number");
    }
    if (direction != Direction::Horizontal && direction != Direction::Vertical) /* if the direction isnt valid */
    {
        throw std::invalid_argument("invalid direction! theres only Horizontal and Vertical");
    }
    if (col >= LIMIT) /* if the col is 100 or more */
    {
        throw std::invalid_argument("the size of the row is 100 chars!");
    }
    if (direction == Direction::Horizontal && col + numOfChars > LIMIT) /* if the col+numOfChars is 100 or more */
    {
        throw std::invalid_argument("the size of the row is 100 chars!");
    }

    /* we will check if the page exist in the unordered map */
    if (this->notebook.find(page) == this->notebook.end())
    {
        unordered_map<int, vector<char>> temp;
        this->notebook.insert({page, temp}); /* add the page to the unordered map */
    }

    if (direction == Direction::Horizontal)
    {
        if (this->notebook.at(page).find(row) == this->notebook.at(page).end())
        {
            vector<char> temp(LIMIT, '_');
            this->notebook.at(page).insert({row, temp});
        }

        vector<char> line = this->notebook.at(page).at(row);
        for (size_t i = (size_t)col; i < col + numOfChars; i++)
        {
            this->notebook.at(page).at(row).at((size_t)i) = '~';
        }
    }

    else
    {
        for (size_t i = (size_t)row; i < row + numOfChars; i++)
        {
            if (this->notebook.at(page).find(i) == this->notebook.at(page).end())
            {
                vector<char> temp(LIMIT, '_');
                this->notebook.at(page).insert({i, temp});
            }

            vector<char> column = this->notebook.at(page).at(i);
            this->notebook.at(page).at(i).at((size_t)col) = '~';
        }
    }
}
void Notebook::show(int page)
{
    if (page < 0)
    {
        throw std::invalid_argument("invalid page number");
    }
    if (this->notebook.find(page) == this->notebook.end())
    {
        vector<char> row(LIMIT, '_');

        for (char i : row)
        {
            std::cout << i << ' ';
        }
    }
    // else
    // {
    //     unordered_map<int, vector<char>> p = this->notebook.at(page);
    //     <int, vector<char>>::iterator it;
    //     for (it = p.begin(); it != p.end(); it++)
    //     {
    //         vector<char> row = p.at(*it);
    //         for (char i : row)
    //         {
    //             std::cout << i << endl;
    //         }
    //     }
    // }
}
