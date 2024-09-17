#include <iostream>
#include <cstring>
using namespace std;

class Product {
public:
    int productId;
    char name[50];
    float price;
    char description[100];

    Product() {}

    Product(int id, const char* n, float p, const char* desc) {
        productId = id;
        strcpy(name, n);
        price = p;
        strcpy(description, desc);
    }

    void displayProduct() const {
        cout << productId << "\t\t" << name << "\t\t" << price << "\t\t" << description << endl;
    }
};

class Order {
public:
    int orderId;
    char date[20];
    char status[20];
    float totalAmount;
    int productIds[100];
    int quantities[100];
    int itemCount;

    Order() : itemCount(0) {
        strcpy(status, "Pending");
    }

    void addProduct(int productId, int quantity) {
        productIds[itemCount] = productId;
        quantities[itemCount] = quantity;
        itemCount++;
    }

    float calculateTotal(const Product products[], int productCount) {
        totalAmount = 0;
        for (int i = 0; i < itemCount; i++) {
            for (int j = 0; j < productCount; j++) {
                if (products[j].productId == productIds[i]) {
                    totalAmount += products[j].price * quantities[i];
                }
            }
        }
        return totalAmount;
    }

    void displayOrder(const Product products[], int productCount) const {
        cout << "\nOrder ID: " << orderId
             << "\nDate: " << date
             << "\nStatus: " << status
             << "\nTotal Amount: " << totalAmount << " PHP\n";
        cout << "Product ID\tName\t\tPrice\tQuantity\n";
        for (int i = 0; i < itemCount; i++) {
            for (int j = 0; j < productCount; j++) {
                if (products[j].productId == productIds[i]) {
                    cout << productIds[i] << "\t\t" << products[j].name << "\t\t"
                         << products[j].price << "\t" << quantities[i] << endl;
                }
            }
        }
        cout << "---------------------\n";
    }
};

class ShoppingCart {
public:
    int productIds[100];
    int quantities[100];
    int itemCount;

    ShoppingCart() : itemCount(0) {}

    void addProduct(int productId, int quantity) {
        for (int i = 0; i < itemCount; i++) {
            if (productIds[i] == productId) {
                quantities[i] += quantity;
                return;
            }
        }
        productIds[itemCount] = productId;
        quantities[itemCount] = quantity;
        itemCount++;
        cout << "Product added successfully!" << endl;
    }

    void viewCart(const Product products[], int productCount) const {
        if (itemCount == 0) {
            cout << "\nShopping cart is empty.\n";
            return;
        }

        cout << "\n--- Shopping Cart ---\n";
        cout << "Product ID\tName\t\tPrice\tQuantity\n";
        for (int i = 0; i < itemCount; i++) {
            for (int j = 0; j < productCount; j++) {
                if (products[j].productId == productIds[i]) {
                    cout << productIds[i] << "\t\t" << products[j].name << "\t\t"
                         << products[j].price << "\t" << quantities[i] << endl;
                }
            }
        }
        cout << "---------------------\n";
    }

    float checkout(const Product products[], int productCount) {
        if (itemCount == 0) {
            cout << "\nShopping cart is empty.\n";
            return 0;
        }

        float total = 0;
        cout << "\n--- Checkout ---\n";
        cout << "Product ID\tName\t\tPrice\tQuantity\n";
        for (int i = 0; i < itemCount; i++) {
            for (int j = 0; j < productCount; j++) {
                if (products[j].productId == productIds[i]) {
                    cout << productIds[i] << "\t\t" << products[j].name << "\t\t"
                         << products[j].price << "\t" << quantities[i] << endl;
                    total += products[j].price * quantities[i];
                }
            }
        }
        cout << "---------------------\nTotal: " << total << " PHP\n";
        cout << "You have successfully checked out the products!\n";
        return total;
    }
};

void displayProducts(const Product products[], int count);
bool isValidProductId(int productId, const Product products[], int productCount);
char getValidYNInput();

void displayProducts(const Product products[], int count) {
    cout << "\n--- Product List ---\n";
    cout << "Product ID\tName\t\tPrice\t\tDescription\n";
    for (int i = 0; i < count; i++) {
        products[i].displayProduct();
    }
}

bool isValidProductId(int productId, const Product products[], int productCount) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].productId == productId) {
            return true;
        }
    }
    return false;
}

char getValidYNInput() {
    char input;
    while (true) {
        cin >> input;
        if (input == 'Y' || input == 'y' || input == 'N' || input == 'n') {
            return input;
        } else {
            cout << "Invalid input! Please enter 'Y' or 'N': ";
        }
    }
}

int main() {
    Product products[] = {
        Product(1, "Rice", 50, "1 kg of rice"),
        Product(2, "Egg", 6, "1 egg"),
        Product(3, "Milk", 70, "1 liter of milk"),
        Product(4, "Bread", 35, "1 loaf of bread")
    };
    int productCount = 4;

    ShoppingCart cart;
    Order orders[100];
    int orderCount = 0;
    int orderIdCounter = 0;

    bool exit = false;
    while (!exit) {
        cout << "\n--- Menu ---\n";
        cout << "1. View Products\n2. View Shopping Cart\n3. View Orders\n4. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                displayProducts(products, productCount);
                char addMore;
                do {
                    int productId, quantity;
                    do {
                        cout << "Enter the Product ID to add to the shopping cart: ";
                        cin >> productId;
                        if (!isValidProductId(productId, products, productCount)) {
                            cout << "Invalid Product ID! Please enter a valid Product ID.\n";
                        }
                    } while (!isValidProductId(productId, products, productCount));

                    cout << "Enter the quantity: ";
                    cin >> quantity;

                    cart.addProduct(productId, quantity);
                    cout << "Do you want to add another product? (Y/N): ";
                    addMore = getValidYNInput();
                } while (addMore == 'Y' || addMore == 'y');
                break;

            case 2:
                cart.viewCart(products, productCount);
                if (cart.itemCount > 0) {
                    char checkoutChoice;
                    cout << "Do you want to check out all the products? (Y/N): ";
                    checkoutChoice = getValidYNInput();
                    if (checkoutChoice == 'Y' || checkoutChoice == 'y') {
                        float total = cart.checkout(products, productCount);
                        if (total > 0) {
                            Order newOrder;
                            newOrder.orderId = ++orderIdCounter;
                            strcpy(newOrder.date, "2024-09-17"); // Static date for simplicity
                            newOrder.itemCount = cart.itemCount;
                            for (int i = 0; i < cart.itemCount; i++) {
                                newOrder.productIds[i] = cart.productIds[i];
                                newOrder.quantities[i] = cart.quantities[i];
                            }
                            newOrder.calculateTotal(products, productCount);
                            strcpy(newOrder.status, "Completed");
                            orders[orderCount++] = newOrder;
                            cart.itemCount = 0;
                        }
                    }
                }
                break;

            case 3:
                if (orderCount == 0) {
                    cout << "\nNo orders found. Please add products and check out first.\n";
                } else {
                    cout << "\n--- Orders ---\n";
                    for (int i = 0; i < orderCount; i++) {
                        orders[i].displayOrder(products, productCount);
                    }
                }
                break;

            case 4:
                exit = true;
                break;

            default:
                cout << "Invalid option! Please try again.\n";
                break;
        }
    }

    return 0;
}
