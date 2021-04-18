#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "Grid.hpp"

int main(int argc, char**argv) {
  Grid grid(16,16);

  if (argc != 2)
  {
    std::cout << "Invalid arguments - usage:" << std::endl;
    std::cout << argv[0] << " <filename>" << std::endl;
    return -1;
  }

  std::string filename(argv[1]);

  if (!std::filesystem::exists(filename))
  {
    std::cout << "Error: " << filename << " does not exist" << std::endl;
    return -1;
  }

  std::ifstream input(filename, std::ios::binary);

  std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

  for (const auto& byte: buffer)
  {
    std::size_t row = byte >> 4;
    std::size_t col = byte & 0xF;

    //std::cout << "Doing op on (" << row << "," << col << ")" << std::endl;
    grid.do_operation(row, col);
    //std::cout << "State after op on (" << row << "," << col << ")" << std::endl;
    //grid.pretty_print(std::cout);
  }

  std::cout << grid.get_clear_count() << std::endl;

  return 0;
}