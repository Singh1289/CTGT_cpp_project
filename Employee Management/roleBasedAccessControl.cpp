#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <memory>
#include <algorithm> 

using namespace std;

// Abstract Role Class
class Role {
public:
    virtual ~Role() {}
    virtual string getRoleName() const = 0;
    virtual bool hasPermission(const string& action) const = 0;
};

// Concrete Roles
class AdminRole : public Role {
private:
    unordered_set<string> permissions = {"add_user", "delete_user", "view_reports"};

public:
    string getRoleName() const override {
        return "Admin";
    }

    bool hasPermission(const string& action) const override {
        return permissions.find(action) != permissions.end();
    }
};

class ManagerRole : public Role {
private:
    unordered_set<string> permissions = {"view_reports", "approve_leave"};

public:
    string getRoleName() const override {
        return "Manager";
    }

    bool hasPermission(const string& action) const override {
        return permissions.find(action) != permissions.end();
    }
};

class EmployeeRole : public Role {
private:
    unordered_set<string> permissions = {"request_leave"};

public:
    string getRoleName() const override {
        return "Employee";
    }

    bool hasPermission(const string& action) const override {
        return permissions.find(action) != permissions.end();
    }
};

// User Class
class User {
private:
    string name;
    vector<unique_ptr<Role>> roles;

public:
    User(const string& name) : name(name) {}

    string getName() const {
        return name;
    }

    void addRole(unique_ptr<Role> role) {
        roles.push_back(move(role));
    }

    void removeRole(const string& roleName) {
        roles.erase(
            remove_if(roles.begin(), roles.end(),
                      [&roleName](const unique_ptr<Role>& role) { return role->getRoleName() == roleName; }),
            roles.end());
    }

    vector<string> getRoleNames() const {
        vector<string> roleNames;
        for (const auto& role : roles) {
            roleNames.push_back(role->getRoleName());
        }
        return roleNames;
    }

    bool canPerformAction(const string& action) const {
        for (const auto& role : roles) {
            if (role->hasPermission(action)) {
                return true;
            }
        }
        return false;
    }
};

// Test RBAC System
int main() {
    // Create a user and assign multiple roles
    User user("Charlie");
    user.addRole(make_unique<AdminRole>());
    user.addRole(make_unique<EmployeeRole>());

    // Display roles
    cout << "User: " << user.getName() << "\nRoles: ";
    for (const auto& roleName : user.getRoleNames()) {
        cout << roleName << " ";
    }
    cout << "\n\n";

    // Test permissions
    vector<string> actions = {"add_user", "delete_user", "view_reports", "approve_leave", "request_leave"};
    for (const auto& action : actions) {
        cout << "Can perform " << action << "? "
             << (user.canPerformAction(action) ? "Yes" : "No") << '\n';
    }

    // Remove a role
    cout << "\nRemoving Manager role...\n";
    user.removeRole("Manager");

    // Display roles after removal
    cout << "User: " << user.getName() << "\nRoles: ";
    for (const auto& roleName : user.getRoleNames()) {
        cout << roleName << " ";
    }
    cout << "\n\n";

    // Test permissions after role removal
    for (const auto& action : actions) {
        cout << "Can perform " << action << "? "
             << (user.canPerformAction(action) ? "Yes" : "No") << '\n';
    }

    return 0;
}
