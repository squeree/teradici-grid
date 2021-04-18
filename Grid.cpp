
#include "Grid.hpp"

#include <cstring>
#include <stdexcept>
#include <bit>

// Calculate the numer of bytes required to store the bitset
// based on the grid's dimensions
std::size_t Grid::dim_to_bytes(std::size_t rows, std::size_t cols)
{
  std::size_t num_bits = (rows * cols);
  std::size_t num_bytes = num_bits / 8;

  if (num_bits % 8)
  {
    num_bytes++;
  }

  return num_bytes;
}

// Calculate the number of bits used in the last byte of the bitset
std::size_t Grid::bits_in_last_byte(void)
{
  auto used_bits = (num_rows * num_cols) % 8;
  return used_bits ? used_bits : 8;
}

// Construct a Grid with the specified number of rows and columns
Grid::Grid(std::size_t rows, std::size_t cols)
          : num_rows(rows),
            num_cols(cols),
            bitset(std::make_unique<unsigned char []>(dim_to_bytes(rows, cols)))
{
}

// Calculate the byte index and bit shift for accessing a row/column in the bitset 
void Grid::calculate_index_and_shift(std::size_t row, std::size_t col, std::size_t& byte_index, std::size_t& shift)
{    
    int bit_index = (row * num_cols) + col;

    byte_index = bit_index / 8;
    shift = bit_index % 8;
}

// The operation as described in the assignment
void Grid::do_operation(std::size_t row, std::size_t col)
{
  if (row >= num_rows || col >= num_cols)
  {
    throw std::out_of_range("Index out of bounds");
  }

  if (is_bit_set(row, col))
  {
    clear_diagonals(row, col);
  }
  else
  {
    set_row(row);
    set_column(col);
  }
}

// Set all bits in a given row
void Grid::set_row(std::size_t row)
{
  if (row >= num_rows)
  {
    throw std::out_of_range("Row out of bounds");
  }

  for (auto col = 0; col < num_cols; col++)
  {
    set_bit(row, col);
  }
}

// Set all bits in a given column
void Grid::set_column(std::size_t column)
{
  if (column >= num_cols)
  {
    throw std::out_of_range("Column out of bounds");
  }

  for (auto row = 0; row < num_rows; row++)
  {
    set_bit(row, column);
  }
}

// Clear diagonals of the given coordinate
void Grid::clear_diagonals(std::size_t row, std::size_t column)
{
  if (row >= num_rows || column >= num_cols)
  {
    throw std::out_of_range("Index out of bounds");
  }

  /*
   * For the coordinate at X, the column offset is the distance
   * to the start of the diagonals at Y and Z from the column of X.
   *
   *   |<----|++++>|
   * 0 Y 0 0 0 0 0 Z
   * 0 0 0 0 0 0 0 0
   * 0 0 0 0 0 0 0 0
   * 0 0 0 0 X 0 0 0
   * 0 0 0 0 0 0 0 0
   *
   */
  int col_offset = row;

  for (auto i = 0; i < num_rows; i++)
  {
    // Clear the top left to bottom right diagonal
    int left_diag_col = column - col_offset;

    if (left_diag_col >= 0 && left_diag_col < num_cols)
    {
      clear_bit(i, left_diag_col);
    }
        
    // Clear the top right to bottom left diagonal
    int right_diag_col = column + col_offset;

    if (right_diag_col >= 0 && right_diag_col < num_cols)
    {
      clear_bit(i, right_diag_col);
    }

    col_offset--;
  }
}

// Set the bit at the specified row/column
void Grid::set_bit(std::size_t row, std::size_t col)
{
  if (row >= num_rows || col >= num_rows)
  {
    throw std::out_of_range("Index out of bounds");
  }

  std::size_t byte_index, shift;

  calculate_index_and_shift(row, col, byte_index, shift);

  bitset[byte_index] |= (0x1 << shift);
}

// Clear bit at given coordinate
void Grid::clear_bit(std::size_t row, std::size_t col)
{
  if (row >= num_rows || col >= num_cols)
  {
    throw std::out_of_range("Index out of bounds");
  }

  std::size_t byte_index, shift;

  calculate_index_and_shift(row, col, byte_index, shift);

  bitset[byte_index] &= ~(0x1 << shift);
}

// Check if the bit at the given coordinate is set
bool Grid::is_bit_set(std::size_t row, std::size_t col)
{
    if (row >= num_rows || col >= num_cols)
    {
      throw std::out_of_range("Index out of bounds");
    }

    std::size_t byte_index, shift;
    
    calculate_index_and_shift(row, col, byte_index, shift);

    return (bitset[byte_index] & (0x1 << shift));
}

// Get the number of clear bits in the grid
int Grid::get_clear_count(void)
{
  auto count = 0;

  // Loop through each packed byte and count the number of cleared bits
  for (int i = 0; i < dim_to_bytes(num_rows, num_cols); i++)
  {
    count += 8 - std::popcount(bitset[i]);
  }

  auto last_bits = bits_in_last_byte();

  // If the final byte is not completely used,
  // subtract any empty space 
  count -= (8 - last_bits);

  return count;
}

// Print the state of the grid to an output stream
void Grid::pretty_print(std::ostream& out)
{
  for (int row = 0; row < num_rows; row++)
  {
    for (int col = 0; col < num_cols; col++)
    {
      out << (is_bit_set(row, col) ? "1" : "0");
    }

    out << std::endl;
  }
}