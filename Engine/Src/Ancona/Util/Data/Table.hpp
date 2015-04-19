#ifndef ANCONA_UTIL_DATA_TABLE_H
#define ANCONA_UTIL_DATA_TABLE_H

#include "../Algorithm.hpp"
#include "../Assert.hpp"

namespace ild
{

/**
 * @brief Table is a generic two dimensional table that is designed to grow
 * dynamically.
 *
 * @tparam T value type that is stored in the table.
 *
 * @author Jeff Swenson
 */
template<typename T>
class Table
{
    public:
        /**
         * @brief Adds a row to the table.  The new row will be initialized
         * using defaultValue.
         *
         * @param defaultValue value that is used to initialize the row.
         */
        void AddRow(const T &defaultValue)
        {
            _numberOfRows++;
            _data.emplace_back(_numberOfColumns, defaultValue);
        }

        /**
         * @brief Adds a column to the table.  The new column will be initialized
         * using defaultValue.
         *
         * @param defaultValue value that is used to initialize the column.
         */
        void AddColumn(const T &defaultValue)
        {
            _numberOfColumns++;
            for (auto &row : _data)
            {
                row.emplace_back(defaultValue);
            }
        }

        /**
         * @brief Retrieve a reference to the value stored in the table at the given
         * row and column. The reference can be used to mutate the object stored in
         * the table.
         *
         * @param row Row that the value will be retrieved from.
         * @param column Column that the value will be retrieved from.
         */
        T & Get(int row, int column)
        {
            Assert(row >= 0 && row < _numberOfRows, "Row is out of bounds");
            Assert(column >= 0 && column < _numberOfColumns, "Column is out of bounds");
            return _data[row][column];
        }

        /* Getters and Setters */
        int numberOfRows() const { return _numberOfRows; }
        int numberOfColumns() const { return _numberOfColumns; }
    private:
        int _numberOfRows = 0;
        int _numberOfColumns = 0;
        std::vector<std::vector<T>> _data;
};

}
#endif
