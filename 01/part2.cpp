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
    int delta;
    for (std::string buffer; std::getline(fs, buffer);)
    {
        // I'm expecting good data in this coding challenge
        delta = std::stoi(buffer.substr(1));

        // deal with additional rotations
        count += delta / 100;
        delta %= 100;

        if (buffer[0] == 'L') delta *= -1;

        if (pos == 0)
        {
            pos += delta;
            if (pos < 0) pos += 100;
        }
        else
        {
            pos += delta;
            if (pos < 0)    { count++; pos += 100; }
            if (pos == 100) pos = 0;
            if (pos > 100)  { count++; pos -= 100; }
        }

        if (pos == 0) count++;

        log << buffer << ' ' << pos << ' ' << count << '\n';
    }

    std::cout << "Number of 0s: " << count << '\n';

    fs.close();
    log.close();
}
