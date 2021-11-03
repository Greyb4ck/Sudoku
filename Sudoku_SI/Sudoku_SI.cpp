// Sudoku_SI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "generic_sudoku.h"
#include <string>
#include "graph_search.hpp"
int main()
{
    auto xxx = generic_sudoku<3, 3, H_remaining<3, 3>>(
        {
                std::array<int8_t, 9>
                {9, 0, 0, 0, 7, 0, 6, 0, 1},
                {0, 6, 0, 0, 0, 0, 0, 3, 4},
                {0, 1, 0, 3, 6, 0, 2, 8, 0},
                {0, 2, 3, 5, 9, 0, 0, 0, 6},
                {0, 0, 4, 6, 8, 2, 0, 1, 3},
                {1, 0, 0, 0, 3, 0, 0, 0, 0},
                {0, 4, 1, 0, 5, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 5, 8, 4, 6, 0, 0, 2}
        }
        
    );

    

    informative_searcher s(xxx, comp, 3);
    s.get_solution(1)->to_string();
    std::cout << xxx.to_string();
    std::cout << "\n" << s.get_solution(1)->to_string();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
