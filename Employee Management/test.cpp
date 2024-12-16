/*
Problem: Given four points that represent the vertices of a quadrilateral, determine the type of quadrilateral based on these points. The points are provided in a clockwise direction (from point A to point D). The types of quadrilaterals we need to consider are common ones such as square, rectangle, rhombus, parallelogram, trapezoid, and general quadrilateral.
Input: The input consists of 4 points, each represented by their coordinates in a 2D plane. Each point is given as (x, y) coordinates.
Output: Print Quadrilateral Type, i.e., the type of quadrilateral formed by the four points.
Example:
Input: (0,0), (4, 0), (4, 4), (0,4) Output: Quadrilateral Type: Square
Input: (0,0), (0,0), (0,0), (0,0) Output: Entered points do not form any Quadrilateral
*/

/*
Problem: Given a string, find all possible palindromic substrings in it.
Input:
A string of length n (1 ≤ n ≤ 10000).
Output:
A list of all possible palindromic substrings in the input string. The substrings should be presented in a way that each palindrome appears only once (no duplicates), and the list should contain all possible palindromic substrings of any length. The output should not include any non-palindromic substrings.
Instructions: Solve this problem using an approach having time complexity less than O(n^3).
Example:
Input: Enter a string: "google"
Output:
All palindromic substrings of "google": {"e", "1", "g", "o", "oo", "goog"}
*/

/*
Problem: Given a set of integers S, partition this set into two subsets S1 and S2 such that the absolute difference between the sums of the elements in S1 and S2 is minimized. After partitioning, return the minimum absolute difference between the sums of the two subsets. Find all possible ways to partition the set and determine the minimum possible difference between the sum of elements in S1 and S2.
Input: A set S consisting of integers: S = {a1, a2,..., an} where 0 ≤ n ≤ 100
Output: All possible partitions of set S such that for each partition, absolute difference between the sums of the two subsets is minimum.
Example:
Input: S {10, 20, 15, 5, 25}
Output:
S1 S1 {10, 20, 5}, S2 {15, 25}, Min. absolute difference between S1 and S2: 5 {10, 25}, S2 20, 15, 5}, Min. absolute difference between S1 and S2: 5
*/




// #include <iostream>
// #include <cmath>

// using namespace std;

// bool isSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
//     int side1 = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
//     int side2 = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
//     int side3 = sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2));
//     int side4 = sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2));
//     return side1 == side2 && side2 == side3 && side3 == side4;
//     // Check if the sides are equal and if the diagonals are equal
//     // Return true if they are, false otherwise
// }

// bool isRectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
//     int side1 = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
//     int side2 = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
//     int side3 = sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2));
//     int side4 = sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2));
//     return side1 == side2 && side2 == side3 && side3 == side4 && side1 * 2 == side2 + side3;
//     // Check if the sides are equal and if the diagonals are equal
//     // Return true if they are, false otherwise
// }

// bool isRhombus(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
//     int side1 = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
//     int side2 = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
//     int side3 = sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2));
//     int side4 = sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2));
//     return side1 == side2 && side2 == side3 && side3 == side4 && side1!= side2;
//     // Check if the sides are equal and if the diagonals are equal
//     // Return true if they are, false otherwise
// }

// bool isParallelogram(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
//     int side1 = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
//     int side2 = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
//     int side3 = sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2));
//     int side4 = sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2));
//     return side1 == side2 && side2 == side3 && side3 == side4 && side1*2 == side2 + side3;
//     // Check if the sides are equal and if the diagonals are equal
//     // Return true if they are, false otherwise
// }

// bool isTrapezoid(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
//     int side1 = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
//     int side2 = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
//     int side3 = sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2));
//     int side4 = sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2));
//     return side1 == side2 && side3 == side4 && side1!= side2;
//     // Check if the sides are equal and if the diagonals are equal
//     // Return true if they are, false otherwise
// }

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Point {
    double x, y;
};

void trimString(string &str) {
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    if (start == string::npos || end == string::npos) {
        str = "";
    }
    str = str.substr(start, end - start + 1);
}

vector<Point> stringToPair(const string& str) {
    vector<Point> res;
    stringstream ss(str);
    string token;

    while (getline(ss, token, ')')) {
        size_t openBracket = token.find('(');
        if (openBracket != string::npos) {
            token = token.substr(openBracket + 1);  
            
            stringstream pairStream(token);
            string xstr, ystr;

           
            size_t commaPos = token.find(',');
            if (commaPos != string::npos) {
                xstr = token.substr(0, commaPos);
                ystr = token.substr(commaPos + 1);

                double x = stod(xstr);
                double y = stod(ystr);
                Point temp = {x, y};
                res.push_back(temp);
            }
        }
    }

    return res;
}

bool isSquare(double side1, double side2, double side3, double side4, double firstDia, double secondDia){
    return side1 == side2 == side3 == side4 && firstDia == secondDia;
}
bool isRhombus(double side1, double side2, double side3, double side4, double firstDia, double secondDia){
    return (side1 == side3 && side2 == side4 && firstDia != secondDia);
}

bool isRectangle(double side1, double side2, double side3, double side4, double firstDia, double secondDia){
    // double side1 = sqrt(pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2));
    // double side2 = sqrt(pow(points[1].x - points[2].x, 2) + pow(points[1].y - points[2].y, 2));
    // if(side1 == side2){
    //     return false;
    // }
    // double firstDia = sqrt(pow(points[0].x - points[2].x, 2) + pow(points[0].y - points[2].y, 2));
    // double secondDia = sqrt(pow(points[1].x - points[3].x, 2) + pow(points[1].y - points[3].y, 2));
    return (side1 == side3 && side2 == side4 && firstDia == secondDia);
}

bool isParallelogram(double side1, double side2, double side3, double side4, double firstDia, double secondDia){
    return side1 == side3 && side2 == side4 && firstDia != secondDia;
}

bool isTrapezoid(double side1, double side2, double side3, double side4, double firstDia, double secondDia){
    return side1 != side3 && side2 != side4 && side1 != side2 && firstDia == secondDia;
}


int main(){
    string line;
    cout<<"Input: ";
    getline(cin, line);
    trimString(line);
    if(line.size()==0){
        cout<<"Invalid input!"<<endl;
        return 0;
    }

    cout<<"line: "<<line<<endl;

    vector<Point> points= stringToPair(line);
    if(points.size()!=4){
        cout<<"Entered points do not form any Quadrilateral"<<endl;
        return 0;
    }
   
    cout<<"Size "<<points.size()<<endl;
    // print the points
    for(auto p : points){
        cout << "(" << p.x << ", " << p.y << ") \n";
    }
    cout << endl;

    double side1 = sqrt(pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2));
    double side2 = sqrt(pow(points[1].x - points[2].x, 2) + pow(points[1].y - points[2].y, 2));
    double side3 = sqrt(pow(points[2].x - points[3].x, 2) + pow(points[2].y - points[3].y, 2));
    double side4 = sqrt(pow(points[3].x - points[0].x, 2) + pow(points[3].y - points[0].y, 2));
   
    double firstDia = sqrt(pow(points[0].x - points[2].x, 2) + pow(points[0].y - points[2].y, 2));
    double secondDia = sqrt(pow(points[1].x - points[3].x, 2) + pow(points[1].y - points[3].y, 2));

    if(isSquare(side1,side2,side3,side4,firstDia,secondDia))
    cout << "Quadrilateral Type: Square" << endl;
    else if(isRectangle(side1,side2,side3,side4,firstDia,secondDia))
    cout << "Quadrilateral Type: Rectangle" << endl;
    else if(isRhombus(side1,side2,side3,side4,firstDia,secondDia))
    cout << "Quadrilateral Type: Rhombus" << endl;
    else if(isParallelogram(side1,side2,side3,side4,firstDia,secondDia))
    cout << "Quadrilateral Type: Parallelogram" << endl;
    else if(isTrapezoid(side1,side2,side3,side4,firstDia,secondDia))
    cout << "Quadrilateral Type: Trapezoid" << endl;
    else
    cout << "Quadrilateral Type: Not a Quadrilateral" << endl;

    return 0;

}

