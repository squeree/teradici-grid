#include <iostream>
#include "Grid.hpp"

constexpr std::size_t dim = 16;

//Test empty grid
bool test_empty_grid(void)
{
    Grid grid(dim, dim);

    for (auto row = 0; row < dim; row++)
    {
        for (auto col = 0; col < dim; col++)
        {
            if (grid.is_bit_set(row, col))
            {
                return false;
            }
        }
    }

    auto expected_clear = dim * dim;

    return (grid.get_clear_count() == expected_clear);
}

// Test all columns can be set
bool test_all_cols(void)
{
    
    Grid grid(dim,dim);

    for (auto col = 0; col < dim; col++)
    {
        grid.set_column(col);
    }
    
    return (grid.get_clear_count() == 0);
}

// Test all rows can be set
bool test_all_rows(void)
{    
    Grid grid(dim,dim);

    for (auto row = 0; row < dim; row++)
    {
        grid.set_row(row);
    }

    for (auto row = 0; row < dim; row++)
    {
        for (auto col = 0; col < dim; col++)
        {
            if (!grid.is_bit_set(row, col))
            {
                return false;
            }
        }
    }
    
    return (grid.get_clear_count() == 0);
}

// Test an exception is thrown when accessing a row out of bounds
bool test_row_out_of_bounds(void)
{
    Grid grid(dim, dim);
    bool got_exception = false;

    try
    {
        grid.set_row(dim + 1);
    }
    catch(const std::exception& e)
    {
        got_exception = true;
    }
    
    return got_exception;
}

// Test an exception is thrown when accessing a col out of bounds
bool test_col_out_of_bounds(void)
{
    Grid grid(dim, dim);
    bool got_exception = false;

    try
    {
        grid.set_column(dim + 1);
    }
    catch(const std::exception& e)
    {
        got_exception = true;
    }
    
    return got_exception;
}

// Test an exception is thrown when clearing a diagonal with row out of bounds
bool test_diag_row_out_of_bounds(void)
{
    Grid grid(dim, dim);
    bool got_exception = false;

    try
    {
        grid.clear_diagonals(dim + 1, 0);
    }
    catch(const std::exception& e)
    {
        got_exception = true;
    }
    
    return got_exception;
}

// Test an exception is thrown when clearing a diagonal with column out of bounds
bool test_diag_col_out_of_bounds(void)
{
    Grid grid(dim, dim);
    bool got_exception = false;

    try
    {
        grid.clear_diagonals(0, dim + 1);
    }
    catch(const std::exception& e)
    {
        got_exception = true;
    }
    
    return got_exception;
}

// Test the example from the assignment
bool test_example_operations(void)
{
    Grid grid(dim, dim);

    grid.do_operation(0xF, 0xF);
    grid.do_operation(0x1, 0x1);
    grid.do_operation(0x1, 0x2);

    return (grid.get_clear_count() == 200);
}

void report_test_result(const std::string& test_name, bool result)
{
    std::cout << test_name << ": " << (result ? "OK" : "Fail") << std::endl;
}


int main(void)
{
    bool result;

    result = test_empty_grid();
    report_test_result("test_empty_grid", result);

    result = test_all_cols();
    report_test_result("test_all_cols", result); 

    result = test_all_rows();
    report_test_result("test_all_rows", result);

    result = test_example_operations();
    report_test_result("test_example_operations", result);

    result = test_col_out_of_bounds();
    report_test_result("test_col_out_of_bounds", result);

    result = test_row_out_of_bounds();
    report_test_result("test_row_out_of_bounds", result);

    result = test_diag_row_out_of_bounds();
    report_test_result("test_diag_row_out_of_bounds", result);

    result = test_diag_col_out_of_bounds();
    report_test_result("test_diag_col_out_of_bounds", result);

    return 0;
}