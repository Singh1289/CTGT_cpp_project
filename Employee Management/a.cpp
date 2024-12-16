
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Point
{
    double x, y;
};

void trimString(string &str)
{
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    if (start == string::npos || end == string::npos)
        str = "";
    else
        str = str.substr(start, end - start + 1);
}

vector<Point> stringToPair(const string &str)
{
    vector<Point> res;
    stringstream ss(str);
    string token;
    size_t zero = str.find("-0");
    if(zero != std::string::npos){
        cout<<"ERROR: Invalid input string";
        exit(-1);
    }

    while (getline(ss, token, ')'))
    {
        double x, y;

        size_t openBracket = token.find('(');
        if (openBracket != string::npos)
        {
            token = token.substr(openBracket + 1);

            stringstream pairStream(token);
            string xstr, ystr;

            size_t commaPos = token.find(',');
            if (commaPos != string::npos)
            {
                xstr = token.substr(0, commaPos);
                ystr = token.substr(commaPos + 1);
                size_t hexPos1 = xstr.find("0x");
                if (hexPos1 != string::npos)
                    x = strtoull(xstr.c_str(), NULL, 16);
                else
                    x = stod(xstr);
                size_t hexPos2 = ystr.find("0x");
                if (hexPos2 != string::npos)
                    y = strtoull(ystr.c_str(), NULL, 16);
                else
                    y = stod(ystr);

                Point temp = {x, y};
                res.push_back(temp);
            }
        }
    }
    return res;
}



bool isSquare(double side1, double side2, double side3, double side4, double firstDia, double secondDia)
{
    return side1 == side2 && side3 == side2 && side3 == side4 && firstDia == secondDia;
}
bool isRhombus(double side1, double side2, double side3, double side4, double firstDia, double secondDia)
{
    return (side1 == side3 && side2 == side4 && side1 == side2 && firstDia != secondDia);
}

bool isRectangle(double side1, double side2, double side3, double side4, double firstDia, double secondDia)
{
    return (side1 == side3 && side2 == side4 && firstDia == secondDia);
}

bool isParallelogram(double side1, double side2, double side3, double side4, double firstDia, double secondDia)
{
    return side1 == side3 && side2 == side4 && side1 != side2 && firstDia != secondDia;
}

bool isTrapezoid(double side1, double side2, double side3, double side4, double firstDia, double secondDia)
{
    double maxx = max(max(side1, side2), max(side3, side4));
    if (maxx == side1)
        return side1 != side3 && side1 != side4 && side1 != side2 && firstDia == secondDia;
    if (maxx == side2)
        return side2 != side3 && side2 != side4 && side1 != side2 && firstDia == secondDia;
    if (maxx == side3)
        return side1 != side3 && side3 != side4 && side3 != side2 && firstDia == secondDia;
    if (maxx == side4)
        return side4 != side3 && side1 != side4 && side4 != side2 && firstDia == secondDia;
}

int main()
{
    string line;
    cout << "Input: ";
    getline(cin, line);
    trimString(line);
    if (line.size() == 0)
    {
        cout << "Invalid input!" << endl;
        return 0;
    }

    //cout << "line: " << line << endl;

    vector<Point> points = stringToPair(line);
    if (points.size() != 4)
    {
        cout << "Entered points do not form any Quadrilateral" << endl;
        return 0;
    }

    // cout << "Size " << points.size() << endl;
    // // print the points
    // for (auto p : points)
    // {
    //     cout << "(" << p.x << ", " << p.y << ") \n";
    // }
    // cout << endl;

    double side1 = sqrt(pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2));
    double side2 = sqrt(pow(points[1].x - points[2].x, 2) + pow(points[1].y - points[2].y, 2));
    double side3 = sqrt(pow(points[2].x - points[3].x, 2) + pow(points[2].y - points[3].y, 2));
    double side4 = sqrt(pow(points[3].x - points[0].x, 2) + pow(points[3].y - points[0].y, 2));

    double firstDia = sqrt(pow(points[0].x - points[2].x, 2) + pow(points[0].y - points[2].y, 2));
    double secondDia = sqrt(pow(points[1].x - points[3].x, 2) + pow(points[1].y - points[3].y, 2));

    if (isSquare(side1, side2, side3, side4, firstDia, secondDia))
        cout << "Quadrilateral Type: Square" << endl;
    else if (isRectangle(side1, side2, side3, side4, firstDia, secondDia))
        cout << "Quadrilateral Type: Rectangle" << endl;
    else if (isRhombus(side1, side2, side3, side4, firstDia, secondDia))
        cout << "Quadrilateral Type: Rhombus" << endl;
    else if (isParallelogram(side1, side2, side3, side4, firstDia, secondDia))
        cout << "Quadrilateral Type: Parallelogram" << endl;
    else if (isTrapezoid(side1, side2, side3, side4, firstDia, secondDia))
        cout << "Quadrilateral Type: Trapezoid" << endl;
    else
        cout << "Quadrilateral Type: Not a Quadrilateral" << endl;

    return 0;
}
