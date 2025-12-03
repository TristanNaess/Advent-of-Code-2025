#include <iostream>
#include <fstream>
#include <string>


bool valid(unsigned long n)
{
    std::string val = std::to_string(n);

    if (val.size() % 2 != 0) return true; // odd number of characters

    for (std::size_t i = 0, j = val.size() / 2; j < val.size(); i++, j++)
    {
        if (val[i] != val[j]) return true;
    }

    return false;
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
            if (!valid(i)) sum += i;
        }

    } while (end != std::string::npos);

    std::cout << "Sum: " << sum << '\n';

}
