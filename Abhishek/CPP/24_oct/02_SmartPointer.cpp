#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Resource class that holds data
class Resource {
private:
    string data;

public:
    Resource(const string& data) : data(data) {
        cout << "Resource created: " << data << endl;
    }

    ~Resource() {
        cout << "Resource destroyed: " << data << endl;
    }

    void display() const {
        cout << "Resource Data: " << data << endl;
    }

    void setData(const string& newData) {
        data = newData;
    }
};

// SmartPointer class that simulates reference counting for dynamic memory management
template <typename T>
class SmartPointer {
private:
    T* ptr;           
    int* refCount;

public:
    // Constructor
    
     SmartPointer(T* p = nullptr) : ptr(p), refCount(new int(1)) {
        if (ptr) {
            cout << "SmartPointer: Resource is being managed." << endl;
        } else {
            cout << "SmartPointer: Null pointer." << endl;
        }
    }

    // Copy Constructor (Increments reference count)
    SmartPointer(const SmartPointer& other) {
        ptr = other.ptr;
        refCount = other.refCount;
        (*refCount)++;
        cout << "SmartPointer: Copied, reference count is now " << *refCount << endl;
    }

    // Assignment Operator (Increments reference count)
    SmartPointer& operator=(const SmartPointer& other) {
        if (this != &other) {
            // Decrease the current reference count
            if (--(*refCount) == 0) {
                delete ptr;
                delete refCount;
                cout << "SmartPointer: Resource deleted (assign)." << endl;
            }

            // Copy the new resource and reference count
            ptr = other.ptr;
            refCount = other.refCount;
            (*refCount)++;
            cout << "SmartPointer: Assigned, reference count is now " << *refCount << endl;
        }
        return *this;
    }

    // Destructor (Decrements reference count and deletes resource if no references)
    ~SmartPointer() {
        if (--(*refCount) == 0) {
            delete ptr;
            delete refCount;
            cout << "SmartPointer: Resource deleted (destructor)." << endl;
        } else {
            cout << "SmartPointer: Resource still in use, reference count: " << *refCount << endl;
        }
    }

    // Dereference operator (*)
    T& operator*() {
        return *ptr;
    }

    // Arrow operator (->)
    T* operator->() {
        return ptr;
    }

    // Method to get the reference count
    int getRefCount() const {
        return *refCount;
    }
};


void displayMenu() {
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "1. Create and manage a resource" << endl;
    cout << "2. Create another SmartPointer (copy)" << endl;
    cout << "3. Show reference count" << endl;
    cout << "4. Modify resource data" << endl;
    cout << "5. Exit" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

int main() {
    SmartPointer<Resource> ptr1(nullptr);
    SmartPointer<Resource> ptr2(nullptr);
    int choice;
    string data;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "Enter resource data: ";
                getline(cin, data);
                ptr1 = SmartPointer<Resource>(new Resource(data)); 
                break;
            }

            case 2: {
                if (!ptr1.getRefCount()) {
                    cout << "No resource created yet!" << endl;
                    break;
                }

                ptr2 = ptr1;
                cout << "SmartPointer ptr2 created and assigned from ptr1." << endl;
                break;
            }

            case 3: {
                if (!ptr1.getRefCount()) {
                    cout << "No resource created yet!" << endl;
                    break;
                }

                cout << "Reference count: " << ptr1.getRefCount() << endl;
                break;
            }

            case 4: {
                if (!ptr1.getRefCount()) {
                    cout << "No resource created yet!" << endl;
                    break;
                }

                cout << "Enter new resource data: ";
                getline(cin, data);
                ptr1->setData(data);
                cout << "Updated resource data: ";
                ptr1->display();
                break;
            }

            case 5:
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}
