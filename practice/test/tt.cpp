// #include <iostream>
// struct X {
// static char x;
// X() { std::cout << "X:" <<++x; }
// virtual ~X() { std::cout << "Z:"<<--x; }
// };
// struct Y: protected X {
// static char y;
// Y(): X() { std::cout << "Y:"<<++X::x; }
// virtual ~Y() { std::cout << "A:"<<++y; }
// };
// char X::x;
// char Y:: y = 0;

// int main() {
// const Y y();
// std::cout << static_cast<int>(++Y::y % ++X::x);
// std::cout << static_cast<int>(++X::x % ++Y::y);
// exit((int) NULL);
// }

// #include <iostream>

// int main()
// {
//     int n = 3;
//     int i = 0;

//     switch (n % 2)
//     {
//     case 0:
//         do
//         {
//             ++i;
//         case 1:
//             ++i;
//         } while (--n > 0); 
//     }

//     std::cout << i;
// }

#include <iostream>

template <class T>
void f(T &i) { std::cout << 1; }

template <>
void f(int &i) { std::cout << 2; }

int main()
{
    int i = 42;
    f(i);
}