#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

struct vec3
{
    vec3(const std::string& s)
    {
        char comma;
        std::stringstream ss(s);
        ss >> x >> comma >> y >> comma >> z;
    }

    double x, y, z;
};

std::ostream& operator<<(std::ostream& os, const vec3& v)
{
    os << '<' << v.x << ',' << v.y << ',' << v.z << '>';
    return os;
}

struct distance
{
    distance(vec3* p1, vec3* p2) : p1(p1), p2(p2)
    {
        dist = sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2) + pow(p2->z - p1->z, 2));
    }

    vec3 *p1, *p2;
    double dist;
};

bool operator<(const distance& d1, const distance& d2)
{
    return d1.dist < d2.dist;
}

std::ostream& operator<<(std::ostream& os, const distance& d)
{
    os << d.dist << ' ' << d.p1 << ' ' << d.p2;
    return os;
}


struct circuit
{
    circuit(const distance& d)
    {
        points.push_back(d.p1);
        points.push_back(d.p2);
    }

    bool check_connection(const distance& d)
    {
        for (auto p : points)
        {
            if (p == d.p1 || p == d.p2) return true;
        }
        return false;
    }

    void add_connection(const distance& d)
    {
        bool skip1 = false, skip2 = false;
        for (auto p : points)
        {
            if (p == d.p1) skip1 = true;
            if (p == d.p2) skip2 = true;
        }
        if (!skip1) points.push_back(d.p1);
        if (!skip2) points.push_back(d.p2);
    }

    void merge(circuit& other)
    {
        points.insert(points.end(), other.points.begin(), other.points.end());
    }

    std::vector<vec3*> points;
};

bool operator<(const circuit& c1, const circuit& c2)
{
    return c1.points.size() < c2.points.size();
}


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file> [connections]\n";
        return EXIT_FAILURE;
    }
    
    std::size_t connections = 10;
    if (argc == 3)
    {
        connections = std::stoi(argv[2]);
    }

    std::ifstream fs{argv[1]};
    if (!fs.is_open())
    {
        std::cerr << "Failed to open file: " << argv[1] << '\n';
        return EXIT_FAILURE;
    }

    std::vector<vec3> points;

    std::string buffer;
    while (std::getline(fs, buffer))
    {
        points.emplace_back(buffer);
    }

   
    std::vector<distance> distances;
    for (std::size_t i = 0; i < points.size(); i++)
    {
        for (std::size_t j = i + 1; j < points.size(); j++)
        {
            distances.emplace_back(&points[i], &points[j]);
        }
    }

    std::sort(distances.begin(), distances.end());

    std::vector<circuit> circuits;
    std::vector<circuit>::iterator c1, c2;
    for (std::size_t i = 0; i < connections; i++)
    {
        c1 = circuits.end();
        c2 = circuits.end();

        for (auto itr = circuits.begin(); itr < circuits.end(); itr++)
        {
            if (itr->check_connection(distances[i]))
            {
                if (c1 == circuits.end())
                {
                    c1 = itr;
                }
                else if (c2 == circuits.end())
                {
                    c2 = itr;
                    break;
                }
            }
        }
        
        if (c2 != circuits.end())
        {
            c1->merge(*c2);
            circuits.erase(c2);
        }
        else if (c1 != circuits.end())
        {
            c1->add_connection(distances[i]);
        }
        else
        {
            circuits.emplace_back(distances[i]);
        }
    }

    std::sort(circuits.begin(), circuits.end());
    std::reverse(circuits.begin(), circuits.end());

    std::size_t product = 1;
    for (std::size_t i = 0; i < 3; i++)
    {
        product *= circuits[i].points.size();
    }

    std::cout << "Product: " << product << '\n';
}
