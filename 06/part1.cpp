#include <iostream>
#include <fstream>
#include <sstream>
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

    std::string buffer;
    std::vector<std::vector<std::string>> data;

    while (std::getline(fs, buffer))
    {
        std::stringstream ss{buffer};
        data.push_back(std::vector<std::string>{});
        while (ss >> buffer)
        {
            data.back().push_back(buffer);
        }
    }

    unsigned long sum;
    for (std::size_t c = 0; c < data[0].size(); c++)
    {
        unsigned long result;
        if (data.back()[c] == "*")
        {
            result = 1;
            for (std::size_t r = 0; r < data.size() - 1; r++)
            {
                result *= std::stoul(data[r][c]);
            }
        }
        else
        {
            result = 0;
            for (std::size_t r = 0; r < data.size() - 1; r++)
            {
                result += std::stoul(data[r][c]);
            }
        }

        sum += result;
    }

    std::cout << "Sum: " << sum << '\n';

}
