#include <gtest/gtest.h>

#include <Ancona/Util/Data/Table.hpp>

using namespace ild;

TEST(Table, CreateRowsFirst)
{
   Table<int> table;
   int rowCount = 5;
   int colCount = 7;

   for(int i = 0; i < rowCount; i++)
   {
      table.AddRow(1);
   }

   for(int i = 0; i < colCount; i++)
   {
      table.AddColumn(2);
   }

   ASSERT_EQ(table.Get(rowCount - 1, colCount - 1), 2) << "No cells should have the row default value";
   ASSERT_EQ(table.Get(3, 0), 2) << "No cells should have the row default value";
}

TEST(Table, CreateColsFirst)
{
   Table<int> table;
   int rowCount = 5;
   int colCount = 7;

   for(int i = 0; i < colCount; i++)
   {
      table.AddColumn(2);
   }

   for(int i = 0; i < rowCount; i++)
   {
      table.AddRow(1);
   }

   ASSERT_EQ(table.Get(rowCount - 1, colCount - 1), 1) << "No cells should have the column default value";
   ASSERT_EQ(table.Get(3, 0), 1) << "No cells should have the column default value";
}

TEST(Table, SetAndRetrieve)
{
    Table<int> table;
    int rowCount = 5;
    int colCount = 7;

    for(int i = 0; i < colCount; i++)
    {
        table.AddColumn(0);
    }

    for(int i = 0; i < rowCount; i++)
    {
        table.AddRow(0);
    }

    ASSERT_EQ(table.Get(4,3), 0)  << "Incorrect default value";
    ASSERT_EQ(table.Get(3,3), 0)  << "Incorrect default value";

    table.Get(4,3) = 3;

    ASSERT_EQ(table.Get(4,3), 3)  << "Value is not set correctly";
    ASSERT_EQ(table.Get(3,3), 0)  << "Value should not have changed from the default";
}

