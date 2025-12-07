#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct manifold
{
    public:
        manifold(const std::string& file)
        {
            std::ifstream ifs{file};
            if (!ifs.is_open())
            {
                std::cerr << "Failed to open file: " << file << '\n';
                exit(1);
            }

            std::string buffer;
            std::getline(ifs, buffer);
            std::size_t width = buffer.size() / 2;
            splitters = std::vector<splitter>((width * (width+1)) / 2);

            // connect splitters
            std::size_t height = width;
            std::string::iterator itr;
            for (std::size_t row = 1; row <= height; row++)
            {
                std::getline(ifs, buffer); // skip empty line
                std::getline(ifs, buffer);
                itr = buffer.begin() + width - row + 1;


                for (size_t col = 1; col <= row; col++)
                {
                    std::size_t n = ((row-1)*row) / 2 + col - 1;
                    splitter& s = splitters[n];
                    s.state = *itr == '^';

                    if (n+row < splitters.size())
                    {
                        s.split_1 = &splitters[n+row];
                        s.split_2 = &splitters[n+row+1];
                    }
                    if (n+(2*row)+2 < splitters.size()) s.null_path = &splitters[n+(2*row)+2];

                    itr += 2;
                    
                    //std::cout << n << ": " << (s.split_1 != nullptr ? n+row : 0) << ' ' << (s.split_2 != nullptr ? n+row+1 : 0) << ' ' << (s.null_path != nullptr ? n+2*row+2 : 0) << '\n';
                }
            }
        }


        void print() const
        {
            for (std::size_t i = 0; i < splitters.size(); i++)
            {
                splitters[i].print(i);
            }
        }

        std::size_t activate()
        {
            return splitters[0].activate();
        }

    private:
        struct splitter
        {
            bool state = false;
            std::size_t paths = 0;
            splitter* null_path = nullptr;
            splitter* split_1 = nullptr;
            splitter* split_2 = nullptr;

            std::size_t activate()
            {
                if (paths > 0) return paths;

                if(state)
                {
                    if (split_1 != nullptr) paths += split_1->activate();
                    else paths += 1;
                    if (split_2 != nullptr) paths += split_2->activate();
                    else paths += 1;
                    return paths;
                }

                if (null_path != nullptr) return null_path->activate();

                return 1;
            }

            void print(std::size_t i) const
            {
                std::cout << i+1 << ' ' << this << ": " << (state ? "true" : "false")  << "\npaths: " << paths  << "\nleft: " << split_1 << "\nright: " << split_2 << "\n passthrough: " << null_path << "\n\n";
            }

        };

        std::vector<splitter> splitters;
};


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return EXIT_FAILURE;
    }

    manifold manifold (argv[1]);

    std::cout << "Splits: " << manifold.activate() << '\n';
    //manifold.print();

}
