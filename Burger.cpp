#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

struct Sides {
    string name;
    double price;
};

struct Order {
    string size;
    vector<Sides> Sides;
    double totalPrice;

    Order() : totalPrice(0.0) {} // Constructor to initialize totalPrice
};

double credits = 0.0;
vector<Order> recentOrders;

void displayMainMenu() {
    cout << "-------------------------------" << endl;
    cout << "Our School Burger" << endl;
    cout << "-------------------------------" << endl;
    cout << "MAIN MENU" << endl;
    cout << " 1. Add Credits (current credits = " << fixed << setprecision(2) << credits << ")\n";
    cout << " 2. Order Burger\n";
    cout << " 3. Checkout\n";
    cout << " 4. Recent Orders\n";
    cout << " 0. Exit\n\n";
    cout << "Please enter a number: ";
}

void addCredits() {
    double amount;
    cout << "Enter the amount to add to your credits: ";
    cin >> amount;
    credits += amount;
    cout << "Your new balance = " << fixed << setprecision(2) << credits << " credits\n";
}

void orderBurger(Order& order) {
    cout << "\nORDER Burger - Select Burger Flavor Option [Current Balance = " << fixed << setprecision(2) << credits << " credits]\n\n";
    cout << "Please choose from the following options:\n";
    cout << " 1. Egg [5.0 credits]\n";
    cout << " 2. Fish [8.50 credits]\n";
    cout << " 3. Chicken [10.25 credits]\n";
    cout << " 0. Return to Main Menu\n";
    cout << "........................................\n";
    cout << "Please enter a number: ";

    int sizeChoice;
    cin >> sizeChoice;
    if (sizeChoice == 0) {
        return;
    }

    order.size = (sizeChoice == 1) ? "Egg" : ((sizeChoice == 2) ? "Fish" : "Chicken");
    order.totalPrice += (sizeChoice == 1) ? 5.0 : ((sizeChoice == 2) ? 8.50 : 10.25);

    cout << "You have selected a " << order.size << " Burger.\n";
    cout << "........................................\n";

    cout << "ORDER Burger - Select Sides\n";
    cout << "You have selected a " << order.size << " Burger.\n";
    cout << "Please choose from the following Sides:\n\n";

    vector<Sides> sides;
    sides.push_back(Sides());
    sides.back().name = "French Fries";
    sides.back().price = 0.80;

    sides.push_back(Sides());
    sides.back().name = "Chicken Nuggets";
    sides.back().price = 0.50;

    sides.push_back(Sides());
    sides.back().name = "Salad";
    sides.back().price = 0.80;

    sides.push_back(Sides());
    sides.back().name = "Soda";
    sides.back().price = 0.40;

    sides.push_back(Sides());
    sides.back().name = "Burger Meal(Burger + Fries + Soda)";
    sides.back().price = 1.00;

    sides.push_back(Sides());
    sides.back().name = "Full Burger Meal(Burger + Fries + Nuggets + Salad + Soda)";
    sides.back().price = 1.50;



    for (size_t i = 0; i < sides.size(); ++i) {
        cout << " " << i + 1 << ". " << sides[i].name << " [" << fixed << setprecision(2) << sides[i].price << " credits]\n";
    }

    cout << " 0. Return to Main Menu\n\n";
    cout << "........................................\n";
    cout << "Please enter a number: ";

    int sidesChoice; // Corrected variable name
    cin >> sidesChoice;
    if (sidesChoice == 0) {
        return;
    }

    order.Sides.push_back(sides[sidesChoice - 1]);
    order.totalPrice += sides[sidesChoice - 1].price;

    cout << "You have added " << sides[sidesChoice - 1].name << " to your Burger. Your current price is: " << fixed << setprecision(2) << order.totalPrice << " credits.\n";

    char addMoreSides;
    cout << "Would you like to add additional Sides?\nPlease input 'Y' for yes and 'N' for no: ";
    cin >> addMoreSides;

    while (addMoreSides == 'Y' || addMoreSides == 'y') {
        cout << "ORDER Burger - Select Sides\n";
        cout << "You have selected a " << order.size << " Burger.\n";
        cout << "Please choose from the following Sides:\n\n";

        for (size_t i = 0; i < sides.size(); ++i) {
            cout << " " << i + 1 << ". " << sides[i].name << " [" << fixed << setprecision(2) << sides[i].price << " credits]\n";
        }

        cout << " 0. Return to Main Menu\n\n";
        cout << "........................................\n";
        cout << "Please enter a number: ";

        cin >> sidesChoice;
        if (sidesChoice == 0) {
            break;
        }

        order.Sides.push_back(sides[sidesChoice - 1]);
        order.totalPrice += sides[sidesChoice - 1].price;

        cout << "You have added " << sides[sidesChoice - 1].name << " to your Burger. Your current price is: " << fixed << setprecision(2) << order.totalPrice << " credits.\n";

        cout << "Would you like to add additional Sides?\nPlease input 'Y' for yes and 'N' for no: ";
        cin >> addMoreSides;
    }
}

void checkout(Order& order) {
    if (order.totalPrice <= credits) {
        cout << "Checking out...\n";
        cout << "........................................\n";
        cout << "Available Balance:     " << fixed << setprecision(2) << credits << " credits\n";
        cout << "Burger price:           " << fixed << setprecision(2) << order.totalPrice << " credits\n";
        cout << "----------------------------------------\n";
        double remainingCredits = credits - order.totalPrice;
        cout << "Your new Balance = " << fixed << setprecision(2) << remainingCredits << " credits\n";
        cout << "----------------------------------------\n";

        credits = remainingCredits;
        recentOrders.insert(recentOrders.begin(), order);

        cout << "Thank you for your purchase!\n";
    } else {
        cout << "........................................\n";
        cout << "Available Balance:       " << fixed << setprecision(2) << credits << " credits\n";
        cout << "Burger price:             " << fixed << setprecision(2) << order.totalPrice << " credits\n";
        cout << "----------------------------------------\n";
        cout << "You have insufficient credits available. You require \"" << fixed << setprecision(2) << order.totalPrice << "\" credits.\n";

        char addMoreCredits;
        cout << "Would you like to add more credits?\nPlease enter 'Y' for yes and 'N' for no: ";
        cin >> addMoreCredits;
        if (addMoreCredits == 'Y' || addMoreCredits == 'y') {
            double additionalCredits;
            cout << "........................................\n";
            cout << "Please enter how many credits you would like to add to your balance: ";
            cin >> additionalCredits;
            credits += additionalCredits;
            cout << "........................................\n";
            cout << "Your new Balance = " << fixed << setprecision(2) << credits << " credits\n";
            cout << "Thank you for your purchase!\n";
        } else {
            cout << "Thank you, goodbye!\n";
        }
    }
}

void displayRecentOrders() {
    cout << "Recent Orders - High first criteria only\n";
    for (size_t i = 0; i < recentOrders.size(); ++i) {
        const Order& order = recentOrders[i];
        cout << "Burger: " << order.size << " | Sides: " << endl;
        for (size_t j = 0; j < order.Sides.size(); ++j) {
            cout << order.Sides[j].name;
            if (j != order.Sides.size() - 1) {
                cout << ", ";
            }
        }
        cout << " | Price: " << fixed << setprecision(2) << order.totalPrice << " credits\n";
    }
}

int main() {
    int choice;
    Order currentOrder;

    do {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
        
            case 1:
                addCredits();
                break;
                
            case 2:
                orderBurger(currentOrder);
                break;
                
            case 3:
                checkout(currentOrder);
                break;
                
            case 4:
                displayRecentOrders();
                break;
                
            case 0:
                cout << "Goodbye!\n";
                break;
                
            default:
                cout << "Invalid choice. Please enter a valid number.\n";
        }

    } while (choice != 0);

    return 0;
}

