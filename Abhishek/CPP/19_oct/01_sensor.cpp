
/*
1. C++ Program to manage different type of sensors. Each sensor periodically sends its readings (e.g., temperature reading).
Implement a program where each sensor has a unique ID, and you need to store and retrieve the latest reading for each sensor.
Exercise Details:
(a) Define a Sensor class to store sensor ID and the latest  reading.
(b) Use an efficient data structure to manage multiple sensors.
(c) Implement functions to periodically add a new reading and retrieve the latest reading on a regular basis.
(d) Logging sensor readings with timestamps.
(e) Implement access control for sensitive data and public methods for logging and authentication.
*/

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// Class for handling sensor data
class Sensor
{
private:
    int sensorId;
    string sensorType;
    double currentReading;
    string lastUpdateTime;

public:
    Sensor(int id = 0, string type = "unknown")
    {
        sensorId = id;
        sensorType = type;
        currentReading = 0.0;
        lastUpdateTime = "Not updated yet";
    }

    // Getters
    int getId() const { return sensorId; }
    string getType() const { return sensorType; }
    double getReading() const { return currentReading; }
    string getLastUpdateTime() const { return lastUpdateTime; }

    // Update sensor reading
    void updateReading(double reading)
    {
        currentReading = reading;
        // Get current time as string
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", ltm);
        lastUpdateTime = string(buffer);
    }
};

// Class for managing sensors and user authentication
class SensorManager
{
private:
    map<int, Sensor> sensors;
    bool isLoggedIn;
    string logFile;

    // Internal function to log activities
    void logActivity(const string &activity)
    {
        ofstream file(logFile, ios::app);
        if (file.is_open())
        {
            time_t now = time(0);
            tm *ltm = localtime(&now);
            char buffer[80];
            strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", ltm);
            file << buffer << " - " << activity << endl;
            file.close();
        }
    }

public:
    SensorManager() : isLoggedIn(false), logFile("sensor_log.txt") {}

    // Login function with hardcoded credentials for simplicity
    bool login(const string &username, const string &password)
    {
        if (username == "admin" && password == "admin@123")
        {
            isLoggedIn = true;
            logActivity("User logged in: " + username);
            return true;
        }
        return false;
    }

    void logout()
    {
        isLoggedIn = false;
        logActivity("User logged out");
    }

    // Add new sensor
    bool addSensor(int id, const string &type)
    {
        if (!isLoggedIn)
        {
            cout << "Please login first!\n";
            return false;
        }

        if (sensors.find(id) != sensors.end())
        {
            cout << "Sensor ID already exists!\n";
            return false;
        }

        sensors[id] = Sensor(id, type);
        logActivity("Added new sensor - ID: " + to_string(id) + ", Type: " + type);
        return true;
    }

    // Update sensor reading
    bool updateReading(int id, double reading)
    {
        if (!isLoggedIn)
        {
            cout << "Please login first!\n";
            return false;
        }

        if (sensors.find(id) == sensors.end())
        {
            cout << "Sensor not found!\n";
            return false;
        }

        sensors[id].updateReading(reading);
        logActivity("Updated sensor " + to_string(id) + " reading: " + to_string(reading));
        return true;
    }

    // Display all sensor readings
    void displayAllReadings()
    {
        if (!isLoggedIn)
        {
            cout << "Please login first!\n";
            return;
        }

        if (sensors.empty())
        {
            cout << "No sensors registered!\n";
            return;
        }

        cout << "\nCurrent Sensor Readings:\n";
        cout << "------------------------\n";
        for (const auto &pair : sensors)
        {
            const Sensor &sensor = pair.second;
            cout << "Sensor ID: " << sensor.getId() << "\n";
            cout << "Type: " << sensor.getType() << "\n";
            cout << "Current Reading: " << sensor.getReading() << "\n";
            cout << "Last Updated: " << sensor.getLastUpdateTime() << "\n";
            cout << "------------------------\n";
        }
    }

    // Display specific sensor reading
    bool displaySensorReading(int id)
    {
        if (!isLoggedIn)
        {
            cout << "Please login first!\n";
            return false;
        }

        if (sensors.find(id) == sensors.end())
        {
            cout << "Sensor not found!\n";
            return false;
        }

        const Sensor &sensor = sensors[id];
        cout << "\nSensor Details:\n";
        cout << "ID: " << sensor.getId() << "\n";
        cout << "Type: " << sensor.getType() << "\n";
        cout << "Current Reading: " << sensor.getReading() << "\n";
        cout << "Last Updated: " << sensor.getLastUpdateTime() << "\n";
        return true;
    }
};

int main()
{
    SensorManager manager;
    int choice;
    string username, password;

    while (true)
    {
        cout << "\nSensor Management System\n";
        cout << "1. Login\n";
        cout << "2. Add New Sensor\n";
        cout << "3. Update Sensor Reading\n";
        cout << "4. Display All Sensors\n";
        cout << "5. Display Specific Sensor\n";
        cout << "6. Logout\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        if (!(std::cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (manager.login(username, password))
            {
                cout << "Login successful!\n";
            }
            else
            {
                cout << "Invalid credentials!\n";
            }
            break;
        }

        case 2:
        {
            int id;
            string type;
            cout << "Enter sensor ID: ";
            if (!(std::cin >> id))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid ID!\n";
                break;
            }
            cout << "Enter sensor type: ";
            cin >> type;
            if (manager.addSensor(id, type))
            {
                cout << "Sensor added successfully!\n";
            }
            break;
        }

        case 3:
        {
            int id;
            double reading;
            cout << "Enter sensor ID: ";
            if (!(std::cin >> id))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid ID!\n";
                break;
            }
            cout << "Enter new reading: ";
            if (!(std::cin >> reading))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid reading!\n";
                break;
            }
            if (manager.updateReading(id, reading))
            {
                cout << "Reading updated successfully!\n";
            }
            break;
        }

        case 4:
        {
            manager.displayAllReadings();
            break;
        }

        case 5:
        {
            int id;
            cout << "Enter sensor ID: ";
            if (!(std::cin >> id))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid ID!\n";
                break;
            }
            manager.displaySensorReading(id);
            break;
        }

        case 6:
        {
            manager.logout();
            cout << "Logged out successfully!\n";
            break;
        }

        case 7:
        {
            cout << "Thank you for using Sensor Management System!\n";
            return 0;
        }

        default:
        {
            cout << "Invalid choice! Please try again.\n";
        }
        }
    }

    return 0;
}
