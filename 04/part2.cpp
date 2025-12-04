#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return EXIT_FAILURE;
    }

    std::ifstream fs{argv[1]};
    if (!fs.is_open())
    {
        std::cerr << "Failed to open file: " << argv[1] << '\n';
        return EXIT_FAILURE;
    }

    std::vector<std::string> grid;

    std::string buffer;
    std::getline(fs, buffer);
    buffer.insert(0, 1, '.');
    buffer.push_back('.');
    grid.push_back(std::string(buffer.size(), '.'));
    grid.push_back(buffer);
    while (std::getline(fs, buffer))
    {
        grid.push_back(".");
        grid.back().append(buffer + '.');
    }
    grid.push_back(std::string(grid.back().size(), '.'));

    fs.close();

    for (const auto& r : grid)
    {
        std::cout << r << '\n';
    }

    unsigned int sum = 0;
    bool removed = true;
    unsigned int adjacent;
    while (removed == true)
    {
        removed = false;
        for (std::size_t col = 1; col < grid[0].size() - 1; col++)
        {
            for (std::size_t row = 1; row < grid.size() - 1; row++)
            {
                if (grid[row][col] != '@') continue;
                adjacent = 0;
                if (grid[row-1][col-1] == '@') adjacent++;
                if (grid[row-1][col  ] == '@') adjacent++;
                if (grid[row-1][col+1] == '@') adjacent++;
                if (grid[row  ][col-1] == '@') adjacent++;
                if (grid[row  ][col+1] == '@') adjacent++;
                if (grid[row+1][col-1] == '@') adjacent++;
                if (grid[row+1][col  ] == '@') adjacent++;
                if (grid[row+1][col+1] == '@') adjacent++;
                
                if (adjacent < 4)
                {
                    grid[row][col] = 'x';
                    removed = true;
                    sum++;
                }
            }
        }
    }

    std::cout << "Accessable: " << sum << '\n';
}
