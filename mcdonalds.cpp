
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <functional>
#include <numeric>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

/*
Pseduocode:
1. start off by declaring your variables, string user_name, user_order and so on
2. create a personalized message string function for the user
3. make a display void function with the menu
4. make a void function for the users choice
5. make three vector arrays for the quantity, cost, and order
6. use a string hash map to store all of the menu items with their prices
7. use a boolean hash map to determine if each menu is true or false for their sizes
8. prompt user to enter their order
9. users order should be getting pushed back (added) into the order vector array  each time
10. if the user chooses a drink, drinks have specific sizes (small,medium, large) all with different prices
11. when the user chooses a drink and chooses their size, the size should be calculated with the cost of the actual drink
12. the orderQuantity should also be pushed back into the quantity vector array (back of the array, not the front.)
13. create a double function to calculate tax and total cost with tax
14. make a void function for the reciept
15. use a void function for the amount tendered
16. call functions in main and use a while loop and do loop to repeat the code
17. you should also use if statements to keep track of what the user is entering and if it is an option.


IMPORTANT THINGS TO NOTE WHILE WRITING THE PROGRAM:

1. USE A HASHMAP FOR THE MENU.
Why use a hashmap? a hashmap (data structure) is used to allow arbitrary objects to be linked with other arbirtrary objects. A hashmap is a list that contains these arbitrary objects. Arbitrary objects can also be known as keys. If the keys match, it will return the value that was linked to that specific key.

In this problem, my menu contains more than 5 items. Instead of using multiple if-else statements, using a hashmap is more efficient and a quicker way to store multiple menu items. 

The boolean hashmap is used to determine whether you should ask the user to input the size of the menu item.

2. Everytime, an item is getting pushed back into a vector array, it has to be added into the back of the array. If the item is added to the front of the vector array, it will mess up the order.

3. The prices hashmap contains strings that are all in the lowercase format. If the user inputs an item in the uppercase format, the code should still proccess that input. Make sure that the users order gets converted to the lowercase format so you can pair the users order with keys from the hashmap.

4. The prices hashmap also contains strings in the lowercase format but should look like this: "icedcoffee_small". The underscore is a special indicator for when you pair a menu item with the users size input.

5. Use array.size instead of sizeof when iterating through the vector arrays. This is a very common mistake where a programmer will use sizeof instead of array.size. This will result into a segmentation fault. sizeof will return the size of the array in bytes. array.size, will return the actual size of the array instead of returning the size of the array in numbers of elements.


*/


//welcoming the user
string personalizedMessage(string &user_name)
{
    cout << "Please enter your name: " << endl;
    cin >> user_name;

    cout << "Hello " << user_name << "! Welcome to Mcdonalds. \n" << endl;

    return user_name;
}

//menu 
void menuDisplay()
{
    //menu display
    cout << "Here is our menu: " << endl;
    cout << "\n" << endl;

    //meals
    cout << "     Meals:   " << endl;
    cout << "BigMac Combo    (bigmac)       $11.50" << endl;
    cout << "Chicken Nuggets (nuggets)      $6.30" << endl;
    cout << "Happy Meal      (happymeal)    $5.00" << endl;

    cout << "\n"<< endl;

    //drinks
    cout << "     Drinks:   " << endl;
    cout << "Iced Coffee     (icedcoffee) $2.65 " << endl;
    cout << "Regular Coffee  (regcoffee)  $1.50 " << endl;
    cout << "Chai Tea        (chaitea)    $2.40 " << endl;

    //desserts
    cout << "\n" << endl;
    cout << "     Desserts:   " << endl;
    cout << "6 Pack Donuts   (donuts)   $7.50 " << endl;
    cout << "Mcflurry        (mcflurry) $4.00" << endl;
    cout << "Vanilla Sundae  (sundae)   $2.00" << endl;

   cout << "\n"<< endl;

    cout << "Additional cost for drink sizes: " << endl;
    cout << "Small: Remains the same price" << endl;
    cout << "Medium: additional 10 cents" << endl;
    cout << "Large: additional 20 cents" << endl;

    cout << "\n"<< endl;

     cout << "8 PERCENT TAX!" << endl;

    cout << "\n"<< endl;
}

//utility function to convert from uppercase to lowercase
string toLowercase(std::string &user_order)
{
     transform(user_order.begin(), user_order.end(), user_order.begin(), ::tolower);

     return user_order;
}

//users choice with calculations
void userChoice(string &user_name, string &user_order, string &size, vector<double> &cost, vector<int> &quantity, vector<string> &order)
{
    //string hash map
    map<string, double> prices;

    //meals
    prices["bigmac"] = 11.50;
    prices["happymeal"] = 5.00;
    prices["nuggets"] = 6.30;

    //drinks
    prices["icedcoffee"] = 2.65;
    prices["icedcoffee_small"] = 2.65;
    prices["icedcoffee_medium"] = 2.75;
    prices["icedcoffee_large"] = 2.85;

    prices["chaitea"] = 2.40;
    prices["chaitea_small"] = 2.40;
    prices["chaitea_medium"] = 2.50;
    prices["chaitea_large"] = 2.60;

    prices["regcoffee"] = 1.50;
    prices["regcoffee_small"] = 1.50;
    prices["regcoffee_medium"] = 1.60;
    prices["regcoffee_large"] = 1.70;

    //desserts
    prices["mcflurry"] = 4.00;
    prices["donuts"] = 7.50;
    prices["sundae"] = 2.00;


//boolean hash map
    map<string, bool> sizes;


//meals/desserts would be false since they have no sizes.

    sizes["bigmac"] = false;
    sizes["happymeal"] = false;
    sizes["nuggets"] = false;

    sizes["icedcoffee"] = true;
    sizes["chaitea"] = true;
    sizes["regcoffee"] = true;

    sizes["mcflurry"] = false;
    sizes["donuts"] = false;
    sizes["sundae"] = false;

    cout << user_name << ", what would you like to order?" << endl;
    cin >> user_order;

    //call lowercase function
    user_order = toLowercase(user_order);

    //check if the user enters in an option from the given menu.
    //use count method, if key does not exist will return zero
    if (prices.count(user_order) == 0) 
    {
        cout << "Not a menu item \n";
        return;
    }

    //push back to order vector array
    order.push_back(user_order);

    int orderQuantity = 0;

    cout << "How many " << user_order << "s would you like to order?" << endl;
    cin >> orderQuantity;

    //push back to quantity vector array
    quantity.push_back(orderQuantity);

    if (sizes[user_order] == true)
    {
        for (int i = 0; i < orderQuantity; i++)
        {
            cout << "What size? " << endl;
            cin >> size;

            size = toLowercase(size);

            //check if the user enters in the correct size.
            if ( (size.compare("small") == 0) || (size.compare("medium") == 0) || (size.compare("large") == 0) )
            {
                //take the users order + the underscore + the users size input(icedcoffee_small)
                //this key will be recognized from the prices hashmap
                 cost.push_back(prices[user_order + "_" + size] * orderQuantity);
            }
            else
            {
                cout << "Not a size. \n";
                cout << "Available sizes are: small, medium, large. \n";
                return;
            }  
        }
    }
    else
    {
        //calculates the users input * users order quantity
        cost.push_back(prices[user_order] * orderQuantity);
    }
}

//the three void print functions are only used for debugging.
void print(std::vector<double> const &input)
{
    for (int i = 0; i < input.size(); i++)
    {
        std::cout << input.at(i) << ' ';
    }
}

void print(std::vector<string> const &input)
{
    for (int i = 0; i < input.size(); i++)
    {
        std::cout << input.at(i) << ' ';
    }
}

void print(std::vector<int> const &input)
{
    for (int i = 0; i < input.size(); i++)
    {
        std::cout << input.at(i) << ' ';
    }
}

//total cost with no tax
double totalCost(std::vector<double> const &input)
{
    double totalCost = 0.0;
    for (int i = 0; i < input.size(); i++)
    {
        totalCost += input[i];
    }

    return totalCost;
}

//calculates tax only
double calculateTax(vector<double> &cost)
{
    return totalCost(cost) * 0.08;
}

//calculates total cost with tax
double totalCostWithTax(vector<double> &cost)
{
    return totalCost(cost) * 1.08;
}

void reciept(vector<double> &cost, vector<int> &quantity, vector<string> &order)
{

    cout << fixed << setprecision(2) << endl;
    //print(cost);
    //print(order);
    //print(quantity);

    cout << "YOUR RECIEPT" << endl;

    for (int i = 0; i < quantity.size(); i++)
    {
        cout << "Total cost for " << quantity[i] << " " << order[i] << ": "
             << "$" << cost[i] << endl;
    }

    cout << "Total tax: $" << calculateTax(cost) << endl;
    cout << "Your total bill plus HST 8 % tax is: $" << totalCostWithTax(cost) << endl;
}

void amountTendered(string &user_order, string &user_name, string &cash_or_card, double &amount_tendered, double &total_bill, vector<double> &cost)
{

    cout << fixed << setprecision(2);

    cout << "Are you paying with Cash or Card?" << endl;
    cin >> cash_or_card;

    if (cash_or_card == "card" || cash_or_card == "Card")
    {
        cout << "Your card has been approved. \n"
             << endl;
        cout << user_name << ", thank you for coming, have a nice day." << endl;
    }
    else if (cash_or_card == "cash" || cash_or_card == "Cash")
    {
        cout << "Enter the amount tendered: " << endl;
        cin >> amount_tendered;

        total_bill = totalCostWithTax(cost);

        if (amount_tendered > total_bill)
        {
            amount_tendered = amount_tendered - total_bill;

            cout << "Your change is: $" << amount_tendered << endl;
            cout << user_name << ", thank you for coming, have a nice day." << endl;
        }
        else if (amount_tendered < total_bill)
        {
            total_bill = total_bill - amount_tendered;
            cout << "You still need to pay $" << total_bill << " more. \n" << endl;
            cout << "Enter the amount tendered: " << endl;
            cin >> amount_tendered;

            amount_tendered = amount_tendered - total_bill;

            cout << "Your change is: $" << amount_tendered << endl;
            cout << user_name << ", thank you for coming, have a nice day." << endl;
        }
        else
        {
            cout << "Invalid. Try again" << endl;
            cout << "Enter the amount tendered: " << endl;
            cin >> amount_tendered;
        }
        
    }
    else
        {
            cout << "Invalid. Try again \n" << endl;
            cout << "Are you paying with Cash or Card?" << endl;
            cin >> cash_or_card;
        }
}

int main()
{

    string user_name = " ";
    string response = " ";
    string user_order = " ";
    string size = " ";
    string cash_or_card = " ";

    vector<int> quantity;
    vector<string> order;
    vector<double> cost;

    double amount_tendered = 0;
    double total_bill = 0;

    bool notFinished = true;

  //text display
  cout << " __  __  ____ ____   ___  _   _    _    _     ____  ____  " << endl;
  cout << "|  \\/  |/ ___|  _ \\ / _ \\| \\ | |  / \\  | |   |  _ \\/ ___| " << endl;
  cout << "| |\\/| | |   | | | | | | |  \\| | / _ \\ | |   | | | \\___ \\ " << endl;
  cout << "| |  | | |___| |_| | |_| | |\\  |/ ___ \\| |___| |_| |___) |" << endl;
  cout << "|_|  |_|\\____|____/ \\___/|_| \\_/_/  \\ \\_\\_____|____/|____/ " << endl;
                                                           


    while(notFinished)
    {
        personalizedMessage(user_name);
        do {
        
        menuDisplay();
        userChoice(user_name, user_order, size, cost, quantity, order);
   
        cout << "Would you like to continue ordering? y/n" << endl;
        cin >> response;

        } while (response == "Y" || response == "y");

       reciept(cost, quantity, order);
       amountTendered(user_order, user_name, cash_or_card, amount_tendered, total_bill, cost);

       //clear the arrays
       quantity.clear();
       order.clear();
       cost.clear();

       cout << "Exit? y/n" << endl;
       cin >> response;

       if (response == "Y" || response == "y")
       {
           notFinished = false;
       }

    }
    
}