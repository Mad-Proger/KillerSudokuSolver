#include "Solver.hpp"

Solver::Solver(const Field& field) : m_cellValues(), m_cellCages(), 
                                     m_cageSums(), m_currentCageSums()
{
    for (size_t r = 0; r < FIELD_SIZE; ++r)
        for (size_t c = 0; c < FIELD_SIZE; ++c)
            m_cellValues[r][c] = 0;

    for (const auto& [r, c, val] : field.getFixedCells())
        m_cellValues[r][c] = val;

    size_t cntCellsInCages = 0;
    for (const auto& [cells, sum] : field.getCages())
    {
        const size_t cageIndex = m_cageSums.size();
        m_cageSums.push_back(sum);
        m_currentCageSums.push_back(0);

        for (const auto& [r, c] : cells)
        {
            ++cntCellsInCages;
            m_cellCages[r][c] = cageIndex;
            m_currentCageSums[cageIndex] += m_cellValues[r][c];
        }
    }

    if (cntCellsInCages < FIELD_SIZE * FIELD_SIZE)
        throw std::invalid_argument("not all cells are covered with cages");
}

bool Solver::solve()
{
    return rec(0, 0);
}

void Solver::exportSolution(Field& field) const
{
    for (size_t r = 0; r < FIELD_SIZE; ++r)
        for (size_t c = 0; c < FIELD_SIZE; ++c)
            field.addFixedCell({ r, c, m_cellValues[r][c] });
}

std::pair<size_t, size_t> Solver::nextCell(size_t row, size_t col)
{
    if (col + 1 < FIELD_SIZE)
        return std::pair<size_t, size_t>{ row, col + 1 };
    else
        return std::pair<size_t, size_t>{ row + 1, 0 };
}

bool Solver::checkValueRow(size_t row, int value) const
{
    for (size_t col = 0; col < FIELD_SIZE; ++col)
        if (m_cellValues[row][col] == value)
            return false;
    return true;
}

bool Solver::checkValueColumn(size_t col, int value) const
{
    for (size_t row = 0; row < FIELD_SIZE; ++row)
        if (m_cellValues[row][col] == value)
            return false;
    return true;
}

bool Solver::checkValueSquare(size_t row, size_t col, int value) const
{
    const size_t rowOffset = row - row % SQUARE_SIZE;
    const size_t colOffset = col - col % SQUARE_SIZE;

    for (size_t r = 0; r < SQUARE_SIZE; ++r)
        for (size_t c = 0; c < SQUARE_SIZE; ++c)
            if (m_cellValues[rowOffset + r][colOffset + c] == value)
                return false;
    return true;
}

bool Solver::checkValue(size_t row, size_t col, int value) const
{
    return checkValueRow(row, value) &&
           checkValueColumn(col, value) &&
           checkValueSquare(row, col, value);
}

bool Solver::rec(size_t r, size_t c)
{
    if (r == FIELD_SIZE)
    {
        for (size_t i = 0; i < m_cageSums.size(); ++i)
            if (m_cageSums[i] != m_currentCageSums[i])
                return false;
        return true;
    }

    if (m_cellValues[r][c] != 0)
    {
        auto [row, col] = nextCell(r, c);
        return rec(row, col);
    }

    const size_t cageIndex = m_cellCages[r][c];
    const int remainingSum = m_cageSums[cageIndex] - m_currentCageSums[cageIndex];
    for (int d = 1; d <= MAX_DIGIT && d <= remainingSum; ++d)
    {
        if (!checkValue(r, c, d))
            continue;
        
        m_cellValues[r][c] = d;
        m_currentCageSums[cageIndex] += d;
        auto [row, col] = nextCell(r, c);
        if (rec(row, col))
            return true;
        
        m_cellValues[r][c] = 0;
        m_currentCageSums[cageIndex] -= d;
    }

    return false;
}
