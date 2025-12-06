#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

void remove_spaces(std::string& s)
{
    for (auto itr = s.end()-1; itr >= s.begin(); itr--)
    {
        if (*itr == ' ') s.erase(itr);
    }
}


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
    std::getline(fs, buffer);
    std::vector<std::vector<char>> data(buffer.size()); // treat as column wise instead of row wise
    fs.seekg(0);

    while (std::getline(fs, buffer))
    {
        for (std::size_t i = 0; i < buffer.size(); i++)
        {
            data[i].push_back(buffer[i]);
        }

    }

    fs.close();

    std::reverse(data.begin(), data.end());

    unsigned long sum;
    unsigned long total;
    std::stack<unsigned long> vals;

    for (const auto& col : data)
    {
        buffer = std::string(col.begin(), col.end());
        remove_spaces(buffer);
        if (buffer == "") continue;

        switch (buffer.back())
        {
            case '+':
                total = std::stoul(buffer);
                while (!vals.empty())
                {
                    total += vals.top();
                    vals.pop();
                }
                sum += total;
                break;
            case '*':
                total = std::stoul(buffer);
                while (!vals.empty())
                {
                    total *= vals.top();
                    vals.pop();
                }
                sum += total;
                break;
            default:
                vals.push(std::stoul(buffer));
        }
    }

    std::cout << "Sum: " << sum << '\n';

}
