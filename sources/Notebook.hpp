#include <iostream>
#include <vector>
#include <unordered_map>
#include "Direction.hpp"
#define LIMIT 100
using namespace std;

namespace ariel
{
    class Notebook
    {
    private:
        unordered_map<int, unordered_map<int, vector<char>>> notebook;

    public:
        Notebook();
        ~Notebook();
        void write(int page, int row, int col, Direction direction, string text);
        string read(int page, int row, int col, Direction direction, int numOfChars);
        void erase(int page, int row, int col, Direction direction, int numOfChars);
        void show(int page);
    };
};