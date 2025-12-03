#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool valid(unsigned long n)
{
    std::string val = std::to_string(n);

    std::vector<std::size_t> ptrs;
    ptrs.reserve(val.size());

    std::size_t len;
    char c;

    bool esc = false;

    for (std::size_t repeats = 2; repeats <= val.size(); repeats++)
    {
        if (val.size() % repeats != 0) continue; // no a whole number of repeats
        len = val.size() / repeats;
        ptrs.clear();
        for (std::size_t i = 0; i < val.size(); i += len)
        {
            ptrs.push_back(i);
        }
        
        for (std::size_t i = 0; i < len; i++)
        {
            c = val[i];
            for (auto p : ptrs)
            {
                if (val[p + i] != c)
                {
                    esc = true;
                    break;
                }
            }

            if (esc) break;
        }
        if (esc)
        {
            esc = false;
            continue;
        }
        return false;
    }

    return true;
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

    // Body here
    std::string input;
    std::getline(fs, input);
    fs.close();

    unsigned long sum = 0;

    std::size_t start = 0;
    std::size_t end;
    std::size_t dash;
    unsigned long first, last;
    do
    {
        end = input.find(',', start);
        dash = input.find('-', start);
        first = std::stoul(input.substr(start, dash));
        last = std::stoul(input.substr(dash+1, end));
        start = end+1;

        for (unsigned long i = first; i <= last; i++)
        {
            if (!valid(i))
            {
                //std::cout << i << '\n';
                sum += i;
            }
        }

    } while (end != std::string::npos);

    std::cout << "Sum: " << sum << '\n';

}
