#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>


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

    std::vector<std::pair<unsigned long, unsigned long>> ranges;

    std::size_t index;
    std::string buffer;
    std::getline(fs, buffer);
    while (buffer != "")
    {
        index = buffer.find('-');
        ranges.push_back(std::make_pair(std::stoul(buffer.substr(0, index)), std::stoul(buffer.substr(index+1))));

        std::getline(fs, buffer);
    }

    size_t count = 0;
    unsigned long id;
    while (std::getline(fs, buffer))
    {
        id = std::stoul(buffer);
        for (auto& r : ranges)
        {
            if (id >= r.first && id <= r.second)
            {
                count++;
                break;
            }
        }
    }

    std::cout << "Count: " << count << '\n';

    fs.close();
}
