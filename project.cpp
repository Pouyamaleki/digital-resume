#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;


struct admin
{
    string adminusername;
    string adminpassword;
};

admin pouya = {"pouya", "pouya"};
admin danial = {"danial", "danial"};


struct customer
{
    string customerusername;
    string customerpassword;
    float balance;
};
customer fazel ={"fazel", "fazel", 1000};
customer yasaman ={"yasaman", "yasaman", 1000};
customer matin ={"matin", "matin", 1000};



void logsystem(const string &message, fstream &myfile)
{
    auto now = chrono::system_clock::now();
    time_t currenttime = chrono::system_clock::to_time_t(now);
    tm* localTime = localtime(&currenttime);
    myfile.open("log.txt", ios::app);
    if(myfile.is_open())
    {
        myfile << put_time(localTime, "%Y-%m-%d %H:%M:%S ") << message << endl;
        myfile.close();
    }else cout << "could not open the log file!" << endl;
}



bool login(string username, string password, fstream &myfile)
{
    bool a;
    while(1)
    {
    if(pouya.adminusername == username && pouya.adminpassword == password)
    { a = 1; break; logsystem("pouya has logged in" , myfile);}
    else if(danial.adminusername == username && danial.adminpassword == password)
    {a = 1; break; logsystem("danial has logged in", myfile);}
    else if (matin.customerusername == username && matin.customerpassword == password)
    {a = 0; break; logsystem("matin has logged in", myfile);}
    else if (yasaman.customerusername == username && yasaman.customerpassword == password)
    {a = 0; break; logsystem("yasaman has logged in", myfile);}
    else if (fazel.customerusername == username && fazel.customerpassword == password)
    {a = 0; break; logsystem("fazel has logged in", myfile);}
    else 
    { 
        cout << "there isn't any account with this username and password, please try again! " << endl;
        logsystem("wrong username and password", myfile);
    }
    cout << "username: ";
    getline( cin , username);
    cout << endl;
    cout << "password: ";
    getline ( cin , password);
    cout << endl;
    }
    return a;
}



void increasebalance(string command, string &x, int &y, fstream &myfile)
{
    istringstream iss(command);
    iss >> command >> x >> y ;
    if(x == "matin") {matin.balance += y; logsystem("increased the balance of matin's account", myfile);}
    else if(x == "yasaman") {yasaman.balance += y; logsystem("increased the balance of yasaman's account", myfile);}
    else if(x == "fazel") {fazel.balance += y; logsystem("increased the balance of fazel's account", myfile);}
    else{ cout <<"wrong name, please try again! " << endl; logsystem("wrong username!", myfile);}

}



struct product
{
    string name;
    float price;
    int number;
};



void additem(string command, fstream &myfile, string &x, int &z, product* (&fruit))
{
    logsystem("add item", myfile);
    istringstream iss(command);
    while (iss >> x)
    {
        if(x == "add") iss >> x;

            fruit[z].name = x;
            iss >> x;
            fruit[z].price = stoi(x);
            iss >> x;
            fruit[z].number = stoi(x);
            myfile.open("inventory.txt", ios::app);
            myfile << fruit[z].name << endl;
            myfile << fruit[z].price << endl;
            myfile << fruit[z].number << endl;
            myfile.close();
            z++;
    }
    logsystem("a product has been added", myfile);
}



void remove(string command, fstream &myfile, string &x, int &z, product* (&fruit))
{
    logsystem("remove", myfile);
    bool found = 0;
    istringstream iss(command);
    iss >> command >> x;
    for(int i = 0; i<z; i++)
    {
        if( x == fruit[i].name)
        {
            found = 1;
            for(int j = i; j<z-1; j++)
            {
                fruit[j] = fruit[j+1];
            }
            z--;
            myfile.open("inventory.txt", ios::out);
            for(int i = 0; i<z; i++)
            {
                
                myfile << fruit[i].name << endl;
                myfile << fruit[i].price << endl;
                myfile << fruit[i].number << endl;
                
            }
            myfile.close();
            break;
        }
    }
    if(!found)
    {
        cout << "this fruit is not in the storage!" << endl;
        logsystem("the fruit is not in the storage!", myfile);
    }
}


void changeprice(string command, string &x, fstream &myfile, int &z, product* (&fruit))
{
    bool found = 1;
    istringstream iss(command);
    iss >> command >> x;
     for(int i =0; i<z; i++)
    {
        if(x == fruit[i].name)
        {
            logsystem("a product price has been changed!", myfile);
            found = 1;
            iss >> x;
            fruit[i].price = stoi(x);
            myfile.open("inventory.txt", ios::out);
            for(int i =0; i<z; i++)
            {
                myfile << fruit[i].name << endl;
                myfile << fruit[i].price << endl;
                myfile << fruit[i].number << endl;
            }
            myfile.close();
            break;
        }
    }
    if(!found)
    {
    cout << "the product was not in the storage!" << endl;
    logsystem("the product was not in the storage!", myfile);
    cout << "please try again" << endl;
    }

}


void list(string command, fstream &myfile, string &x, int &z, product* (&fruit)) 
{
    logsystem("list", myfile);
    istringstream iss(command);
    bool found = 0;
    iss >> command >> x;
    if(x == "")
    {
        found = 1;
        for(int i = 0; i<z; i++)
         {
            cout << fruit[i].name << endl;
         }
    } else 
    {
         for(int i = 0; i<z; i++)
        {
            if(x == fruit[i].name)
            {
                found = 1;
                cout << "name: " << fruit[i].name << " price: " << fruit[i]. price << " number: " << fruit[i].number << endl;
            }
        }
        if(!found)
        {
            cout << "worng name!" << endl;
            logsystem("wrong name!", myfile);
        }
        x = "";
    }
}




void productlist(fstream &myfile, int &z, product* (&fruit)) 
{
    myfile.open("inventory.txt", ios::in);
    if (myfile.is_open()) 
    {
        int i = 0;
        string line;
        while (getline(myfile, line)) 
        {
            fruit[i].name = line;
            if (getline(myfile, line)) 
            {
                fruit[i].price = stoi(line);
            }
            if (getline(myfile, line))
             {
                fruit[i].number = stoi(line);
            }
            i++;
        }
        z = i;
        myfile.close();
    } else cout << "file could not be open!" << endl;
}



void buyitem(string username , string command, string &x, fstream &myfile, int &z, product* (&fruit))
{
    bool found = 0;
    istringstream iss(command);
    iss >> command >> x;
    for(int i = 0; i<z ; i++)
    {
            if(x == fruit[i].name)
            {
                found = 1;
                fruit[i].number--;
                if(fruit[i].number < 0)
                {
                    cout << "there is enough product in the storage! " << endl;
                    logsystem("there is not enough product in the storage", myfile);
                    fruit[i].number++;
                    break;
                }
                if(username == "yasaman")
                {
                    logsystem("yasaman bought a product", myfile);
                    yasaman.balance -= fruit[i].price;
                    if(yasaman.balance < 0)
                    {
                        cout << "you don't have enough money!" << endl;
                        logsystem("yasaman does not have enough money to buy this product", myfile);
                        yasaman.balance += fruit[i].price;
                    }
                    break;
                } else if(username == "matin")
                {
                    logsystem("matin bought a product", myfile);
                    matin.balance -= fruit[i].price;
                    if(matin.balance < 0)
                    {
                        cout << "you don't have enough money!" << endl;
                        logsystem("matin does not have enough money to buy this product", myfile);
                        matin.balance += fruit[i].price;
                    }
                    break;
                }else if(username == "fazel")
                {
                    logsystem("fazel bought a product", myfile);
                    fazel.balance -= fruit[i].price;
                    if(fazel.balance < 0)
                    {
                        cout << "you don't have enough money!" << endl;
                        logsystem("fazel does not have enough money to buy this product", myfile);
                        fazel.balance += fruit[i].price;
                    }
                    break;
                }
            }
            myfile.open("inventory.txt", ios::out);
            for(int i =0; i<z; i++)
            {
                myfile << fruit[i].name << endl;
                myfile << fruit[i].price << endl;
                myfile << fruit[i].number << endl;
            }
            myfile.close();
        }
        if(!found)
        {
        cout << "there is not any product with this name!" << endl;
    }
}


void showbalance (string username, fstream &myfile)
{
    if(username == "yasaman") {cout << yasaman.balance << endl; logsystem("show yasaman balance", myfile);}
    else if(username == "matin") {cout << matin.balance << endl; logsystem("show matin balance", myfile);}
    else if(username == "fazel") {cout << fazel.balance << endl; logsystem("show fazel balance", myfile);}
}


void rename(string command, fstream &myfile, string &x, string &h, int &z, product* (&fruit))
{
    bool found = 0;
    istringstream iss(command);
    iss >> command >> x >> h;
    for(int i = 0; i<z; i++)
    {
        if( x == fruit[i].name)
        {
            logsystem("a product name has been changed", myfile);
            found = 1;
            fruit[i].name = h;
            cout << "product name has been changed successfully!" << endl;
            myfile.open("inventory.txt", ios::out);
            for(int i =0; i<z; i++)
            {
                myfile << fruit[i].name << endl;
                myfile << fruit[i].price << endl;
                myfile << fruit[i].number << endl;
            }
            myfile.close();
            break;
        }
    }
    if(!found)
    {
        cout << "wrong name!" << endl;
        logsystem("wrong name!", myfile);
        cout << " please try again! " << endl;
    }

}


void adminhelp(string command, fstream &myfile, string &x)
{
    logsystem("help", myfile);
    istringstream iss(command);
    iss >> command >> x;
    if(x == "")
    {
        cout << "add" << endl;
        cout << "remove" << endl;
        cout << "price" << endl;
        cout << "credit" << endl;
        cout << "rename" << endl;
        cout << "list" << endl;
        cout << endl;
    } else 
    {
        if(x == "add") cout << " * add name price number * if you want to add anything to the storage" << endl;
        else if(x == "remove") cout << " * remove name * if you want to delete an item from the storage" << endl;
        else if(x == "price") cout << " * price name price * if you want to change an item price" << endl;
        else if(x == "credit") cout << " * credit user * if you want to increase a normal user's balance" << endl;
        else if(x == "rename") cout << " * rename name newname * if you want to change a product name" << endl;
        else if(x == "list") cout << " * list * if you want to see the items list " << endl;
        else cout << "wrong command" << endl;
        x = "";
    }
}


void customerhelp(string command, string &x, fstream &myfile)
{
    logsystem("help", myfile);
    istringstream iss(command);
    iss >> command >> x;
    if(x == "")
    {
        cout << "buy" << endl;
        cout << "list" << endl;
        cout << "balance" << endl;
    } else
    {
        if(x == "list") cout << " * list * if you want to see the items list" << endl;
        else if(x == "buy") cout << " * buy item * if you want to buy something " << endl;
        else if(x == "balance") cout << " * balance * if you want to see your balance " << endl;
        else cout << "wrong command!" << endl;
        x = "";
    }
}


void admincommads(string command, string &order, fstream &myfile, string &x, int &y, string &h, int &z, product* (&fruit))
{
       if(order == "add") additem(command, myfile, x, z, fruit);
       else if(order == "remove") remove(command, myfile, x, z, fruit);
       else if(order == "price") changeprice(command, x, myfile, z, fruit);
       else if(order == "credit") increasebalance(command, x, y, myfile);
       else if(order == "rename") rename(command, myfile, x, h, z, fruit);
       else if(order == "list") list(command, myfile, x, z, fruit);
       else if(order == "help") adminhelp(command, myfile, x); 
       else cout << "wrong command! " << endl;
}



void customercommands(string command, string &order, const string &username, fstream &myfile, string &x, int &z, product* (&fruit))
{
    if(order == "list") list(command, myfile, x, z, fruit);
    else if(order == "buy") buyitem(username , command, x, myfile, z, fruit);
    else if(order == "balance") showbalance(username, myfile);
    else if(order == "help") customerhelp(command, x, myfile);
}



int main()
{
    bool a;
    string command, password, username, x, h, order;
    int y, z = 0;
    fstream myfile;
    product* fruit = new product[20];

    logsystem("program started!", myfile);

    logsystem("productlist function has been called", myfile);
    productlist(myfile, z, fruit);


    cout << "welcome to WMS system please login into your account: " << endl;
    cout << "username: ";
    getline( cin , username);
    transform(username.begin(), username.end(), username.begin(), ::tolower);
    cout << endl;
    cout << "password: ";
    getline ( cin , password);
    transform(password.begin(), password.end(), password.begin(), ::tolower);
    cout << endl;
    
    a = login(username , password, myfile);
    
    if(a == 1) 
    {
        cout << "you are an admin" << endl;
        logsystem("user is an admin", myfile);
        cout << endl;
      while(1)
      {
        cout << "please tell me what do you want to do with the system? " << endl;
        getline(cin , command);
        istringstream iss(command);
        iss >> order;
        transform(order.begin(), order.end(), order.begin(), ::tolower);
        logsystem(order, myfile);

        if(order == "exit") break;

        transform(command.begin(), command.end(), command.begin(), ::tolower);
        admincommads(command , order, myfile, x, y, h, z, fruit);
      }
    }
    else {
        cout << "you are a customer";
        logsystem("user is a customer", myfile);
        cout << endl;

        while(1)
        {
            cout << "please tell me what do you want to do with the system? " << endl;
            getline(cin , command);
            istringstream iss(command);
            iss >> order;
            transform(order.begin(), order.end(), order.begin(), ::tolower);
            logsystem(order, myfile);

            if(order == "exit") break;

            transform(command.begin(), command.end(), command.begin(), ::tolower);
            customercommands(command, order, username, myfile, x, z, fruit);
        }
    }
    
delete[] fruit;
return 0;
}