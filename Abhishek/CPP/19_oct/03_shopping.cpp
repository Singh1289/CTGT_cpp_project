// 3. Program to implement a simple shopping list application where users can add items to the list, update quantities, and view the entire list. Each item has a name, quantity, and price. The application should also be able to calculate and display the total cost of all items in the list. Exercise details: (a) Add items to the list.
// (b) Update item quantities. (c) Remove items from the list. (d) Search for items by name. (e) Display all items sorted by their total cost. (f) Calculate the total cost of all items. (g) Implement a namespace to organize the code. (h) Use constant expressions for fixed values. (i) Demonstrate the use of constructors and destructors effictively.
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

// Namespace to organize the shopping list application code
namespace ShoppingApp
{
    // Class to represent an item in the shopping list
    class Item
    {
        string name;        // Item name
        int quantity;       // Item quantity
        double price;       // Item price per unit
        double totalCost;   // Total cost of the item (quantity * price)

    public:
        // Constructor to initialize an item with name, quantity, and price
        Item(string n, int q, double p)
        {
            name = n;
            quantity = q;
            price = p;
            totalCost = quantity * price; // Calculate total cost of the item
        }

        // Getter for item name
        string getName() const
        {
            return name;
        }

        // Setter for quantity (also updates total cost)
        void setQuantity(int q)
        {
            quantity = q;
            totalCost = quantity * price; // Recalculate total cost when quantity is updated
        }

        // Getter for item quantity
        int getQuantity() const
        {
            return quantity;
        }

        // Getter for item price
        double getPrice() const
        {
            return price;
        }

        // Getter for total cost of the item
        double getTotalCost() const
        {
            return totalCost;
        }

        // Overloaded < operator to compare items by total cost
        bool operator<(const Item &other) const
        {
            return totalCost < other.totalCost;
        }
    };

    // List to store the shopping items
    list<Item> shoppingList;

    // Set to store item names for quick lookup and avoid duplicates
    set<string> nameSet;

    // Function to add a new item to the shopping list
    void addItem()
    {
        string name;
        int quantity;
        double price;

        // Prompt user for item details
        cout << "Enter item name: ";
        cin >> name;

        // Check if item already exists in the list using nameSet
        auto result = nameSet.insert(name);
        if (!result.second)  // If insertion fails, the item already exists
        {
            cout << "Item is already in the list.\n";
            return;
        }

        cout << "Enter item quantity: ";
        cin >> quantity;
        cout << "Enter item price: ";
        cin >> price;

        // Check if quantity or price is invalid (negative values)
        if (quantity < 0 || price < 0)
        {
            cout << "Invalid input. Quantity and price must be positive.\n";
            nameSet.erase(name); // Remove the item from nameSet if invalid input
            return;
        }

        // Create a new item object and add it to the shopping list
        Item newItem(name, quantity, price);
        shoppingList.push_back(newItem);
        cout << "Item added successfully.\n";
    }

    // Function to print all items in the shopping list
    void printList()
    {
        // Check if the shopping list is empty
        if (shoppingList.empty())
        {
            cout << "The shopping list is empty.\n";
            return;
        }

        cout << "\nShopping List:\n";
        // Iterate through the list and print details of each item
        for (const auto &item : shoppingList)
        {
            cout << "Item Name: " << item.getName() << endl;
            cout << "Quantity: " << item.getQuantity() << endl;
            cout << "Price: " << item.getPrice() << endl;
            cout << "Total Cost: " << item.getTotalCost() << endl;
            cout << "--------------------\n";
        }
    }

    // Function to find an item by its name
    void findByName(string name)
    {
        // Search the list for an item with the specified name
        for (auto &item : shoppingList)
        {
            if (item.getName() == name)
            {
                cout << "Item Found: " << endl;
                cout << "Name: " << item.getName() << endl;
                cout << "Quantity: " << item.getQuantity() << endl;
                cout << "Price: " << item.getPrice() << endl;
                return;
            }
        }
        cout << "Item not found.\n";  // If item not found
    }

    // Function to update the quantity of an item
    void updateQuantity()
    {
        string name;
        int quantity;

        // Prompt for item name and new quantity
        cout << "Enter the name of the item you want to update: ";
        cin >> name;

        // Search the list for the item
        for (auto &item : shoppingList)
        {
            if (item.getName() == name)
            {
                cout << "Enter the new quantity: ";
                cin >> quantity;

                // Check if the new quantity is valid
                if (quantity < 0)
                {
                    cout << "Invalid quantity. Must be positive.\n";
                    return;
                }

                // Update item quantity and total cost
                item.setQuantity(quantity);
                cout << "Quantity updated successfully.\n";
                return;
            }
        }

        cout << "Item not found.\n";  // If item not found
    }

    // Function to remove an item from the list
    void removeItem()
    {
        string name;
        cout << "Enter the name of the item you want to remove: ";
        cin >> name;

        // Search for the item and remove it
        for (auto it = shoppingList.begin(); it != shoppingList.end(); ++it)
        {
            if (it->getName() == name)
            {
                nameSet.erase(name);   // Remove from nameSet to prevent duplicates
                shoppingList.erase(it);  // Remove from shopping list
                cout << "Item removed successfully.\n";
                return;
            }
        }

        cout << "Item not found.\n";  // If item not found
    }

    // Function to sort the shopping list by total cost (ascending)
    void sortList()
    {
        // Check if the shopping list is empty
        if (shoppingList.empty())
        {
            cout << "The shopping list is empty.\n";
            return;
        }

        // Sort the shopping list using a lambda function for comparison
        shoppingList.sort([](const Item &a, const Item &b)
                          { return a.getTotalCost() < b.getTotalCost(); });

        cout << "Shopping list sorted by total cost:\n";
        printList();  // Display the sorted list
    }

    // Function to calculate and display the total cost of all items
    void calculateTotalCost()
    {
        double totalCost = 0.0;

        // Sum up the total cost of all items in the list
        for (const auto &item : shoppingList)
        {
            totalCost += item.getTotalCost();
        }

        cout << "Total cost of all items: " << totalCost << endl;
    }
} // End of ShoppingApp namespace

using namespace ShoppingApp;

int main()
{
    int choice;
    while (true)
    {
        // Display the shopping list menu
        cout << "\nShopping List Menu:\n";
        cout << "1. Add Item\n";
        cout << "2. Update Quantity\n";
        cout << "3. Remove Item\n";
        cout << "4. Search for Item by Name\n";
        cout << "5. Display All Items (Sorted by Total Cost)\n";
        cout << "6. Calculate Total Cost of All Items\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle user choice based on menu options
        switch (choice)
        {
        case 1:
            // Add a new item
            addItem();  
            break;
        case 2:
            // Update quantity of an existing item
            updateQuantity();  
            break;
        case 3:
            // Remove an item from the list
            removeItem();  
            break;
        case 4:
        {
            string name;
            cout << "Enter the name of the item to search: ";
            cin >> name;
            // Search for an item by name
            findByName(name);  
            break;
        }
        case 5:
            // Display sorted list by total cost
            sortList();  
            break;
        case 6:
            // Calculate the total cost of all items
            calculateTotalCost();  
            break;
        case 7:
            // Exit the program
            cout << "Exiting the program. Goodbye!\n";  
            return 0;
        default:
            // Handle invalid input
            cout << "Invalid choice. Please try again.\n";  
        }
    }

    return 0;
}
