#include "Field.hpp"

Field::Field() : m_fixedCells(), m_cages() {};

void Field::addCage(const Field::Cage& cage)
{
    if (!checkCagePossibility(cage))
        throw std::invalid_argument("cage has intersections with existing cages");
    m_cages.push_back(cage);
}

void Field::addFixedCell(const Field::FixedCell& fixedCell)
{
    if (fixedCell.value < 1 || fixedCell.value > 9)
        throw std::out_of_range("cell value is not a digit from 1 to 9");
    m_fixedCells.push_back(fixedCell);
}

void Field::removeCage(size_t row, size_t column)
{
    auto it = std::find_if(m_cages.begin(), m_cages.end(), [&row, &column](const Field::Cage& cage) {
        return std::find(cage.cells.begin(), cage.cells.end(), std::pair{ row, column }) != cage.cells.end();
    });
    
    if (it != m_cages.end())
    {
        std::swap(*it, m_cages.back());
        m_cages.pop_back();
    }
}

void Field::removeAllCages()
{
    m_cages.clear();
}

void Field::removeFixedCell(size_t row, size_t column)
{
    auto it = std::find_if(m_fixedCells.begin(), m_fixedCells.end(), [&row, &column](const FixedCell& cell) {
        return cell.row == row && cell.column == column;
    });
    if (it != m_fixedCells.end())
    {
        std::swap(*it, m_fixedCells.back());
        m_fixedCells.back();
    }
}

void Field::removeAllFixedCells()
{
    m_fixedCells.clear();
}

void Field::clear()
{
    removeAllCages();
    removeAllFixedCells();
}

int Field::operator()(size_t row, size_t column) const
{
    auto it = std::find_if(m_fixedCells.begin(), m_fixedCells.end(), [&row, &column](const FixedCell& cell) {
        return cell.row == row && cell.column == column;
    });
    return it == m_fixedCells.end() ? 0 : it->value;
}

const std::vector<Field::FixedCell>& Field::getFixedCells() const
{
    return m_fixedCells;
}

const std::vector<Field::Cage>& Field::getCages() const
{
    return m_cages;
}

bool Field::checkCagePossibility(const Field::Cage& cage) const
{
    auto checkIntersection = [&cage](const Field::Cage& other) -> bool {
        for (const auto& cell : cage.cells)
            if (std::find(other.cells.begin(), other.cells.end(), cell) != other.cells.end())
                return true;
        return false;
    };

    auto it = std::find_if(m_cages.begin(), m_cages.end(), checkIntersection);
    return it == m_cages.end();
}
