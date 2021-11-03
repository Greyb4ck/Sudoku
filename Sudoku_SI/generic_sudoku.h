
#include <string>
#include <iostream>
#include <array>
#include <unordered_set>
#include "graph_state.hpp"

template<int M, int N, typename Heuristic>
class generic_sudoku : public graph_state
{
public:

    //generic_sudoku(std::array<std::array<std::uint8_t, M*N>, M*N> & t)
    //: board{t}
   // {}
  // generic_sudoku(std::initializer_list<std::array<std::int8_t, M*N>> lst)      // std::array<std::array<int8_t, 9>, 9> m      initializer_list<std::array<std::uint8_t, M*N>, M*N> lst
    generic_sudoku(std::array<std::array<std::int8_t, M* N>, M* N> lst)
    {
        for (int row = 0; row < M * N; row++)
            for (int col = 0; col < M * N; col++)
                board[row][col] = lst[row][col];


    }

    std::unordered_set<int8_t> possibilities(int wiersz, int kolumna)   const
    {
        std::unordered_set<int8_t> pos;

        for (int i = 0; i < M * N; i++)
        {
            pos.insert(i + 1);
        }
        for (int i = 0; i < M * N; i++)
        {
            pos.erase(board[wiersz][i]);
            pos.erase(board[i][kolumna]);
        }
        int w, k;
        w = (wiersz / M) * M;
        k = (kolumna / N) * N;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                pos.erase(board[i + w][j + k]);


        return pos;
    }

    virtual std::unique_ptr<graph_state> clone() const override
    {
        return std::unique_ptr<graph_state>(new generic_sudoku(*this));
    }

    virtual std::size_t hash_code() const override
    {

        //Stan tablicy jako liczba ¿eby sprawdziæ czy miejsce by³o odwiedzone
        size_t h = 1;
        for (const auto& row : board) {
            for (const auto& col : row) {
                h = h * 31 + col;
            }
        }
        return h;

    }

    virtual std::vector<std::unique_ptr<graph_state>> get_successors() const override
    {
        /**/
        std::vector<std::unique_ptr<graph_state>> successors;
        for (int8_t i = 0; i < M * N; i++)
        {
            for (int8_t j = 0; j < M * N; j++)
            {
                if (board[i][j] == 0)
                {
                    for (int8_t p : possibilities(i, j))
                    {
                        auto c = clone();
                        ((generic_sudoku&)*c).board[i][j] = p;
                        c->set_parent(this);
                        c->update_score(get_g() + 1);
                        successors.push_back(std::move(c));

                    }
                    return successors;
                }
            }

        }
        return{};

    }

    virtual bool is_solution() const override
    {
        for (const auto& row : board) {
            for (const auto& col : row) {
                if (col == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    virtual std::string to_string() const override
    {
        std::string t;
        for (const auto& row : board) {
            for (const auto& col : row) {
                t += (col + '0');
                t += " ";
            }
            t += "\n";
        }
        return t;
    }


    //private:
    //std::array<std::array<std::uint8_t, M*N>, M*N> board;
    //    Heuristic heuristic;



protected:


    double get_heuristic_grade() const override
    {
        return heuristic(board);
    }

    std::array<std::array<uint8_t, M* N>, M* N> board;
    static constexpr Heuristic heuristic{};

    virtual bool is_equal(const graph_state& s) const override
    {

        const generic_sudoku* st = dynamic_cast<const generic_sudoku*>(&s);
        return st != nullptr && st->board == this->board;

    }


};

auto comp = [](const graph_state& a, const graph_state& b)
{
    return a.get_h() < b.get_h();
};

template<int M, int N>
struct  H_remaining
{
    double operator()(const std::array<std::array<uint8_t, M* N>, M* N>& board) const
    {
        return 0;
    }
};