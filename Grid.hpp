#pragma once

#include <cstddef>
#include <memory>
#include <iostream>

class Grid
{
  public:
    Grid(std::size_t num_rows, std::size_t num_cols);

    // Basic operations
    bool is_bit_set(std::size_t row, std::size_t col);
    void set_row(std::size_t row);
    void set_column(std::size_t column);
    void clear_diagonals(std::size_t row, std::size_t column);
    void do_operation(std::size_t row, std::size_t col);
    int get_clear_count(void);

    // For debugging
    void pretty_print(std::ostream& out);

  private:
    const std::size_t num_rows;
    const std::size_t num_cols;
    std::unique_ptr<unsigned char[]> bitset;

    void set_bit(std::size_t row, std::size_t col);
    void clear_bit(std::size_t row, std::size_t col);

    static std::size_t dim_to_bytes(std::size_t rows, std::size_t cols);
    std::size_t bits_in_last_byte(void);
    void calculate_index_and_shift(std::size_t row, std::size_t col, std::size_t& byte_index, std::size_t& shift);

};