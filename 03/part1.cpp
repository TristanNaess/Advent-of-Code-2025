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

    unsigned int sum = 0;

    std::string buffer;
    while (std::getline(fs, buffer))
    {
        std::size_t tens = 0;
        for (std::size_t i = 0; i < buffer.size() - 1; i++)
        {
            if (buffer[i] > buffer[tens]) tens = i;
        }
        
        std::size_t ones = tens + 1;
        for (std::size_t i = tens + 1; i < buffer.size(); i++)
        {
            if (buffer[i] > buffer[ones]) ones = i;
        }

        std::cout << buffer << ' ' << buffer[tens] << buffer[ones] << '\n';
        sum += digit_concat(buffer[tens], buffer[ones]);
    }

    std::cout << "Sum: " << sum << '\n';
}
