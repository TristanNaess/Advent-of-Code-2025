#include <iostream>
#include <fstream>
#include <string>

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

    std::ofstream log{"log.txt", std::ios::trunc};

    // I could have done this with std::algorithms, but then I'd have to read into a vector and I didn't start with that
    // Otherwise I'd have to check but I think this would be a for_each, or I probably could have made it a fold
    int count = 0;
    int pos = 50;
    for (std::string buffer; std::getline(fs, buffer);)
    {
        // I'm expecting good data in this coding challenge
        if (buffer[0] == 'L')   pos -= std::stoi(buffer.substr(1));
        else                    pos += std::stoi(buffer.substr(1));

        pos %= 100;
        if (pos < 0) pos += 100;
        if (pos > 99) pos -= 100;

        if (pos == 0) count++;

        log << buffer << ' ' << pos << ' ' << count << '\n';
    }

    std::cout << "Number of 0s: " << count << '\n';

    fs.close();
    log.close();
}
