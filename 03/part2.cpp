#include <iostream>
#include <fstream>
#include <string>

unsigned int digit_concat(char a, char b)
{
    return (a - '0') * 10 + (b - '0');
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

    unsigned long sum = 0;

    std::string buffer;
    std::size_t itr;
    std::size_t removable;
    while (std::getline(fs, buffer))
    {
        itr = 1;
        removable = buffer.size() - 12;
        for (itr = 1; itr < buffer.size(); itr++)
        {
            if (buffer[itr] > buffer[itr-1])
            {
                buffer.erase(buffer.begin() + itr-1);
                removable--;
                if (itr < 2) itr = 2;
                itr -= 2;
                if (removable == 0) break;
            }
        }

        if (removable > 0)
        {
            buffer.erase(buffer.end()-removable, buffer.end());
        }

        //std::cout << buffer << '\n';
        sum += std::stoul(buffer);
    }

    std::cout << "Sum: " << sum << '\n';
}
