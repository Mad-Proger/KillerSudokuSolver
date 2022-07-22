#pragma once
#include <array>
#include <cstddef>
#include <utility>
#include <vector>

class Field
{
public:
    struct FixedCell
    {
        size_t row;
        size_t column;
        int value;
    };

    struct Cage
    {
        std::vector<std::pair<size_t, size_t>> cells;
        int sum;
    };

    Field();

    void addCage(const Cage& cage);
    void addFixedCell(const FixedCell& fixedCell);

    void removeCage(size_t row, size_t column);
    void removeAllCages();
    void removeFixedCell(size_t row, size_t column);
    void removeAllFixedCells();
    void clear();

    int operator()(size_t row, size_t column) const;

private:
    std::vector<FixedCell> m_fixedCells;
    std::vector<Cage> m_cages;
};