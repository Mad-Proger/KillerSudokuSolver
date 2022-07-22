#pragma once
#include "Field.hpp"
#include <array>
#include <cstddef>
#include <limits>
#include <vector>

class Solver
{
public:
    Solver(const Field& field);

    bool solve();
    void exportSolution(Field& field) const;

private:
    static constexpr size_t FIELD_SIZE = 9;
    static constexpr size_t SQUARE_SIZE = 3;
    static constexpr int MAX_DIGIT = 9;
    
    std::array<std::array<int, FIELD_SIZE>, FIELD_SIZE> m_cellValues;
    std::array<std::array<size_t, FIELD_SIZE>, FIELD_SIZE> m_cellCages;
    std::vector<int> m_cageSums;
    std::vector<int> m_currentCageSums;

    static std::pair<size_t, size_t> nextCell(size_t row, size_t col);

    bool checkValueRow(size_t row, int value) const;
    bool checkValueColumn(size_t col, int value) const;
    bool checkValueSquare(size_t row, size_t col, int value) const;
    bool checkValue(size_t row, size_t col, int value) const;

    bool rec(size_t r, size_t c);
};
