#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

bool sort_pairs(std::pair<unsigned long, unsigned long> a, std::pair<unsigned long, unsigned long> b)
{
    return a.first < b.first;
}

class ranges
{
    std::vector<std::pair<unsigned long, unsigned long>> ranges;

    public:
    void add(const std::string& line)
    {
        std::size_t index = line.find('-');
        ranges.push_back(std::make_pair(std::stoul(line.substr(0, index)), std::stoul(line.substr(index+1))));
    }

    void consolidate()
    {
        std::sort(ranges.begin(), ranges.end(), sort_pairs);
        for (std::size_t i = 0; i < ranges.size() - 1; i++)
        {
            if (ranges[i].second >= ranges[i+1].first)
            {
                if (ranges[i].second < ranges[i+1].second)
                {
                    ranges[i].second = ranges[i+1].second;
                }

                ranges.erase(ranges.begin()+i+1);
                i--;
            }
        }
    }

    void print()
    {
        for (const auto& r : ranges)
        {
            printf("%15lu - %15lu\n", r.first, r.second);
        }
    }

    unsigned long sum()
    {
        size_t sum = 0;
        for (const auto& r : ranges)
        {
            sum += r.second - r.first + 1;
        }
        return sum;
    }

};


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

    ranges ranges;

    std::size_t count = 0;
    unsigned long start, end;
    std::size_t index;
    std::string buffer;
    std::getline(fs, buffer);
    while (buffer != "")
    {
        ranges.add(buffer);

        std::getline(fs, buffer);
    }

    ranges.consolidate();

    //ranges.print();

    std::cout << "Sum : " << ranges.sum() << '\n';

    fs.close();
}
