#include <iostream>
#include <optional>
#include <string>

// A function that might return a value or might not
std::optional<std::string> findNameByID(int id) {
    if (id == 1) return "Alice";    // Return a valid name
    else if (id == 2) return "Bob"; // Return another valid name
    else return std::nullopt;       // Indicate no value
}

int main() {
    std::optional<std::string> result = findNameByID(1);
    if (result.has_value()) {
        std::cout << "Found: " << result.value() << std::endl;
    } else {
        std::cout << "No name found!" << std::endl;
    }

    // Another example of using std::optional directly
    std::optional<int> optValue = 42;
    if (optValue) {
        std::cout << "Optional value: " << *optValue << std::endl;
    }

    optValue.reset(); // Clear the value
    if (!optValue) {
        std::cout << "Optional is empty!" << std::endl;
    }

    return 0;
}

/*

json file
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/include",
                "C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/ucrt",
                "C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/shared",
                "C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/um",
                "C:/MinGW/include",
                "C:/MinGW/lib/gcc/mingw32/8.2.0/include"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}



~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ old ~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "cStandard": "c11",
            "cppStandard": "gnu++14",
            "intelliSenseMode": "windows-gcc-x86"
        }
    ],
    "version": 4
}
*/
