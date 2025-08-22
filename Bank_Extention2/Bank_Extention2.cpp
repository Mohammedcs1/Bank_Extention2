// #45  read bank client data.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<fstream>
#include<iomanip>
#include <iostream>
#include<string>
#include<vector>
using namespace std;
string Mfile = "myfile.txt";
string UserFile = "User.txt";
string sprator = "#//#";

void Menu();
void TransactionMenu();
void ManageUsersMenu();
void LogInMenu();
 
enum enMenuOptions { enPrintData = 1, enAddClient = 2, enDeletClient = 3, enUpdateClientData = 4, enFindClient = 5, Transaction = 6, UsersMenu = 7 ,enEndProgram = 8 };
enum enTransactonOptions { enDeposit = 1, enWitDraw = 2, enClientTotalBalances = 3, enMainMenu = 4 };
enum enManageUserOptions {enShowUserList = 1, enAddNewUser = 2, enDeletUser = 3, enUpdateUser = 4 ,enFindUser = 5, enBackToMainMenu = 6};
struct UserInfo {
    short Permission =0;
    string  Name;
    string PassWord;
    bool MarkForDelet = false;
};
UserInfo CurrentUser;
struct stinfo {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double  AccountBalance;
    bool MarkToDelet = false;

};
//const struct PermissionData {
//    short ShowClientList = 1;
//    short AddNewClient = 2;
//    short DeletClient = 4;
//    short FindClient = 8;
//    short UpdateClient = 16;
//    short TransactionMenu = 32;
//    short ManageUser = 64;
//};
enum enPermissionDate { 
                        ShowClientListOption = 1,  
                        AddNewClientOption = 2,
                        DeletClientOption = 4,
                        FindClientOption = 8,
                        UpdateClientOption = 16,
                        TransactionMenuOption = 32,
                        ManageUserOption = 64,
                                                };


//permission section;

void NotPermissionedMenuScreen()
{
    cout << "_________________________________________________\n";
    cout << "\t Access Denied,\n\tYou Dont Have Permission To Do This \n\t Please conact You Admin.\n";
    cout << "_________________________________________________\n";
}


int ReadMenuOption(int from, int to)
{
    int Number;
    do
    {
        cin >> Number;

    } while (Number < from || Number > to);
    return Number;
}

vector <string> splitString(string message, string deli)
{
    int  pos = 0;

    string sword;
    vector <string> vec;
    while ((pos = message.find(deli)) != message.npos)
    {

        sword = message.substr(0, pos);
        if (sword != "")
        {
            vec.push_back(sword);
        }

        message.erase(0, pos + deli.length());
    }

    if (message != "") {
        vec.push_back(message);
    }

    return vec;
}

void AddClientToFile(string fileName, string Line)
{
    ofstream file;
    file.open(fileName, ios::app);

    if (file.is_open())
    {
        file << Line << endl;
        file.close();
    }
}

stinfo ConvertLineToRecord(string Line)
{
    stinfo client;
    vector <string> vec = splitString(Line, sprator);
    if (vec.size() == 5) {
        client.AccountNumber = vec[0];
        client.PinCode = vec[1];
        client.Name = vec[2];
        client.Phone = vec[3];
        client.AccountBalance = stod(vec[4]);
    }
    return client;
}

UserInfo ConvertLineToRecordForUser(string Line)
{
    UserInfo User;
    vector <string> vUsers = splitString(Line, sprator);
    if (vUsers.size() == 3) {
        User.Name = vUsers[0];
        User.PassWord = vUsers[1];
        User.Permission = stoi(vUsers[2]);
    }
    return User;
}

string ConvertRecordToLine(stinfo Client)
{
    string Line = Client.AccountNumber + sprator;
    Line += Client.PinCode + sprator;
    Line += Client.Name + sprator;
    Line += Client.Phone + sprator;
    Line += to_string(Client.AccountBalance);
    return Line;
}

string ConvertRecordToLineForUser(UserInfo User)
{
    string Line = User.Name + sprator;
    Line += User.PassWord + sprator;
    Line += to_string(User.Permission) + sprator;

    return Line;
}

vector <stinfo> LoadDataFromFileToVector(string FileName)
{
    vector <stinfo> Vclient;
    fstream Myfile;
    Myfile.open(FileName, ios::in);//read mood
    if (Myfile.is_open())
    {
        string Line;
        stinfo sClient;
        while (getline(Myfile, Line))
        {
            sClient = ConvertLineToRecord(Line);
            Vclient.push_back(sClient);
        }
        Myfile.close();

    }
    return Vclient;
}

vector <UserInfo> LoadDataFromFileToVectorForUser(string FileName)
{
    vector <UserInfo> vUsers;
    fstream Myfile;
    Myfile.open(FileName, ios::in);//read mood
    if (Myfile.is_open())
    {
        string Line;
        UserInfo User;
        while (getline(Myfile, Line))
        {
            User = ConvertLineToRecordForUser(Line);
            vUsers.push_back(User);
        }
        Myfile.close();

    }
    return vUsers;
}

string ReadAccountNumber()
{
    string accountnumber;
    cout << " Plz Enter The Account Number You Are Looking For : \n";
    cin >> accountnumber;
    return accountnumber;
}

int ReadUserPermisson(UserInfo User)
{

    User.Permission = 0;
    char y;
    cout << "Access To Cient List ? [y]/[No]\n";
    cin >> y;
    if (toupper(y) == 'Y')
    {
        User.Permission += enPermissionDate::ShowClientListOption;
    }
    cout << "Access To Add Client ? [y]/[No]\n";
    cin >> y;
    if (toupper(y) == 'Y')
    {
        User.Permission += enPermissionDate::AddNewClientOption;
    }
    cout << "Access To Delet Client ? [y]/[No]\n";
    cin >> y;
    if (toupper(y) == 'Y')
    {
        User.Permission += enPermissionDate::DeletClientOption;
    }
    cout << "Access To Update Client ? [y]/[No]\n";
    cin >> y;
    if (toupper(y) == 'Y')
    {
        User.Permission += enPermissionDate::UpdateClientOption;
    }
    cout << "Access Find Client ? [y]/[No]\n";
    cin >> y;
    if (toupper(y) == 'Y')
    {
        User.Permission += enPermissionDate::FindClientOption;
    }
    cout << "Access To Transaction Menu ? [y]/[No]\n";
    cin >> y;
    if (toupper(y) == 'Y')
    {
        User.Permission += enPermissionDate::TransactionMenuOption;
    }
    cout << "Access To Manage Users ? [y]/[No]\n";
    cin >> y;
    if (toupper(y) == 'Y')
    {
        User.Permission += enPermissionDate::ManageUserOption;
    }
    return User.Permission;
}
bool CheckAccessPermission(enPermissionDate enPermission)
{
    if (CurrentUser.Permission == -1)
         return true;

    if ((CurrentUser.Permission & enPermission) == enPermission)
         return true;
    return false;
}

// for Printing ; 
//client 
void PrintClientRecord(stinfo Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(15) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void PrintAllFileData(vector <stinfo> Vclient)
{
    cout << " \t========================================== < Client List > =================================================\n";
    cout << " \t============================< structure For  " << Vclient.size() << "  Client(S) >\t\t\t===================\n";

    cout << "| " << setw(10) << left << " AccountNumber ";
    cout << "| " << setw(15) << left << " PinCode ";
    cout << "| " << setw(40) << left << " Name ";
    cout << "| " << setw(12) << left << " Phone ";
    cout << "| " << setw(12) << left << " AccountBalance ";
    cout << "\n ====================================================================================================================\n";
    for (stinfo Client : Vclient) {
        PrintClientRecord(Client);
        cout << endl;
    }

}

void PrintClientCard(stinfo Client)
{
    cout << "Account Number : " << setw(15) << left << Client.AccountNumber << endl;
    cout << "Pin Code : " << setw(15) << left << Client.PinCode << endl;
    cout << "Name : " << setw(40) << left << Client.Name << endl;
    cout << "Phone : " << setw(12) << left << Client.Phone << endl;
    cout << "Account Balance : " << setw(12) << left << Client.AccountBalance << endl;
}

//user;

void PrintUserCard(UserInfo User)
{
    cout << setw(20) << "User Name         " << setw(12) << User.Name << endl;
    cout << setw(20) << "User Password     " << setw(12) << User.PassWord << endl;
    cout << setw(20) << "User permission   " << setw(12) << User.Permission << endl;
}

void ShowUserList(UserInfo User)
{

    cout << "| " << setw(15) << left << User.Name;
    cout << "| " << setw(15) << left << User.PassWord;
    cout << "| " << setw(40) << left << User.Permission;


}

void PrintAllUsersInfo(vector <UserInfo> vUsers)
{

    cout << " \t========================================== < Users List > =================================================\n";
    cout << " \t============================< structure For  " << vUsers.size() << "  Users(S) >\t\t\t===================\n";

    cout << "| " << setw(10) << left << " User Name ";
    cout << "| " << setw(15) << left << " User Password ";
    cout << "| " << setw(12) << left << " User permission ";
    cout << "\n ====================================================================================================================\n";
    for (UserInfo User : vUsers) {
        ShowUserList(User);
        cout << endl;
    }

}

void PrintUsersMenu()
{
    vector <UserInfo> vUsers = LoadDataFromFileToVectorForUser(UserFile);
    PrintAllUsersInfo(vUsers);
}

// for adding new client or user;

stinfo ReadClientInfo(stinfo& Clientinfo, vector <stinfo> Vclient)
{
    cout << "Plz : Enter Account Number :";

    getline(cin >> ws, Clientinfo.AccountNumber);
    for (stinfo X : Vclient)
    {
        while (X.AccountNumber == Clientinfo.AccountNumber)
        {
            cout << " This Account Is Already Exsit :\n Plz Enter Another Account Number\n";
            getline(cin >> ws, Clientinfo.AccountNumber);
        }

    }
    cout << "\nPlz : Enter PinCode :";
    getline(cin, Clientinfo.PinCode);
    cout << "\nPlz : Enter Name :";
    getline(cin, Clientinfo.Name);
    cout << "Plz : Enter Phone Number :";
    getline(cin, Clientinfo.Phone);
    cout << "Plz : Enter Account Balance :";
    cin >> Clientinfo.AccountBalance;
    return Clientinfo;
}
 
void AddNewClient(vector <stinfo>& Vclient)
{

    stinfo ClientInfo;
    Vclient = LoadDataFromFileToVector(Mfile);
    ReadClientInfo(ClientInfo, Vclient);
    AddClientToFile(Mfile, ConvertRecordToLine(ClientInfo));


}

void AddClients(vector <stinfo>& Vclient)
{

    char Y;
    do {

        AddNewClient(Vclient);
        cout << " You Add client successfully : Do you want to add New client ? press [y]\n";

        cin >> Y;
        system("cls");
    } while (toupper(Y) == 'Y');
}

UserInfo ReadUserDate()
{
    UserInfo User;
    char option;
    vector <UserInfo> vUsers = LoadDataFromFileToVectorForUser(UserFile);
    cout << "Plz: Enter User Name\n";
    getline(cin >> ws, User.Name);
    for (UserInfo U : vUsers)
    {
        while (U.Name == User.Name)
        {
            cout << "This User Name Is Already Exist Please Try again\n";
            getline(cin, User.Name);
        }
    }
    cout << "Plz: Enter User Password\n";
    cin >> User.PassWord;
    cout << "Do You Want Full Access To the User? [y]/[N]\n";
    cin >> option;
    if (toupper(option) == 'N')
    {
        User.Permission = ReadUserPermisson(User);
    }
    else
        User.Permission = -1;
    return User;
}

void AddUser(vector <UserInfo>& vUsers)
{
    UserInfo User;
    vUsers = LoadDataFromFileToVectorForUser(UserFile);
    User = ReadUserDate();
    AddClientToFile(UserFile, ConvertRecordToLineForUser(User));
}

void AddNewUsers(vector <UserInfo>& vUsers)
{

    char Y;
    do {

        AddUser(vUsers);
        cout << " You Add client successfully : Do you want to add New client ? press [y]\n";

        cin >> Y;
        system("cls");
    } while (toupper(Y) == 'Y');
}


// find user or client;

bool FindClientByAccountNumber(stinfo& client, string accountnumber)
{
    vector <stinfo> Vclient = LoadDataFromFileToVector(Mfile);

    for (stinfo X : Vclient)
    {
        if (X.AccountNumber == accountnumber)
        {
            client = X;
            return true;
        }

    }
    return false;


}

bool FindClient(string accountnumber)
{
    char Answer = 'n';
    stinfo client;
    if (FindClientByAccountNumber(client, accountnumber))
    {
        PrintClientCard(client);
        return true;
    }
    else
        cout << " This Account Is Not Exist \n";
    return false;
}

bool FindUserByUserName(string UserName, UserInfo& User)
{

    vector <UserInfo> vUsers = LoadDataFromFileToVectorForUser(UserFile);

    for (UserInfo& U : vUsers)
    {
        if (U.Name == UserName)
        {
            User = U;
            return true;
            break;
        }


    }
    return false;
}

void FindUserInfo(string Name, UserInfo User)
{
    vector <UserInfo> vUsers = LoadDataFromFileToVectorForUser(UserFile);
    if (FindUserByUserName(Name, User))
        PrintUserCard(User);
    else
        cout << " The User Is Not Exsits\n";
}


//for deleting or user clients;

vector <stinfo> SaveClientToFile(string filename, vector <stinfo>& Vclient)
{
    fstream Myfile;
    Myfile.open(filename, ios::out);//rewrite the file;
    string DataLine;
    if (Myfile.is_open())
    {
        for (stinfo C : Vclient)
        {
            if (C.MarkToDelet == false)
            {
                DataLine = ConvertRecordToLine(C);
                Myfile << DataLine << endl;

            }
        }
        Myfile.close();
    }
    return Vclient;
}

bool MarkClientForDelet(string accountnumber, vector <stinfo >& Vclient)
{
    for (stinfo& c : Vclient)
    {
        if (c.AccountNumber == accountnumber) {
            c.MarkToDelet = true;
            return true;
        }

    }
    return false;
}

bool DeletClient(string accountnumber, vector <stinfo>& Vclient)
{
    
    char x;
    stinfo  Client;
   
    if (FindClientByAccountNumber(Client, accountnumber))
    {
        PrintClientCard(Client);
        cout << "\n\n are you sure you want to delet this client ? [y] or [n] \n";
        cin >> x;
        if (toupper(x) == 'Y')
        {
            MarkClientForDelet(accountnumber, Vclient);
            SaveClientToFile(Mfile, Vclient);

            cout << " accout deleted successfully \n";

        }


        return true;
    }
    else
    {
        cout << " account not found\n";
        return false;
    }
}

bool MarkUserForDelet(string UserName, vector <UserInfo>& vUsers)
{

    for (UserInfo& U : vUsers)
    {
        if (U.Name == UserName) {
            U.MarkForDelet = true;
            return true;
        }
    }
    return false;
}

vector <UserInfo> SaveUserInfoToFile(vector <UserInfo>& vUsers)
{
    fstream file;
    file.open(UserFile, ios::out);//rewrite file;
    string Line;
    if (file.is_open())
    {
        for (UserInfo U : vUsers)
        {
            if (U.MarkForDelet == false)
            {
                Line = ConvertRecordToLineForUser(U);
                file << Line << endl;;
            }
        }
        file.close();
    }
    return vUsers;
}

bool DeletUser(string username, vector <UserInfo>& vUser)
{
    UserInfo User;
    if (username == "Admin") {
        cout << "You Cant Delet This User\n";
        return false;
    }
    char x;

    if (FindUserByUserName(username, User))
    {
        cout << "The User You Intered is :" << endl;
        PrintUserCard(User);
        cout << "\n\n Are you Sure You Want To Delet This Account\n";
        cin >> x;
        if (toupper(x) == 'Y')
        {

            MarkUserForDelet(username, vUser);
            SaveUserInfoToFile(vUser);

            cout << "User Deleted Successfully\n";

        }
        return true;
    }
    else {
        cout << " the username you intered is not found\n";
        return false;
    }
}

// updating user or clients data;
stinfo RereadClientData(string accountnumber)
{
    stinfo Clientinfo;

    Clientinfo.AccountNumber = accountnumber;
    cout << "\nPlz : Enter PinCode :\n";
    cin >> Clientinfo.PinCode;

    cout << "\nPlz : Enter Name :\n";
    getline(cin >> ws, Clientinfo.Name);
    cout << "Plz : Enter Phone Number :\n";
    getline(cin, Clientinfo.Phone);
    cout << "Plz : Enter Account Balance :\n";
    cin >> Clientinfo.AccountBalance;
    return Clientinfo;
}

bool UpdateClientData(string accountnumber, vector <stinfo >& Vclient)
{
    char Answer = 'n';
    stinfo client;
    if (FindClientByAccountNumber(client, accountnumber))
    {
        PrintClientCard(client);
        cout << " \n\nDo you want to change client record y/n ? \n";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {


            for (stinfo& C : Vclient)
            {
                if (C.AccountNumber == accountnumber)
                {
                    C = RereadClientData(accountnumber);
                    break;
                }

            }
            SaveClientToFile(Mfile, Vclient);
            cout << " CLient data changed successfully :\n";

        }
        return true;
    }
    else
        cout << " account is not exist : \n";
    return false;
}

UserInfo ReReadUserInfo(string username)
{
    UserInfo User;

    char option;
    User.Name = username;
    cout << "Plz: Enter User Password\n";
    cin >> User.PassWord;
    cout << "Do You Want Full Access To the User? [y]/[N]\n";
    cin >> option;
    if (toupper(option) == 'N')
    {
        User.Permission = ReadUserPermisson(User);
    }
    else
        User.Permission = -1;
    return User;
}

bool UpdateUserInfo(string username, vector <UserInfo>& vUser)
{
    char x;
    UserInfo User;
    if (username == "Admin") {
        cout << "You Cant Update This User\n";
        return false;
    }
    if (FindUserByUserName(username, User))
    {


        cout << "The Account Is :\n";
        PrintUserCard(User);
        cout << "are u sure you want to delete the account\n";
        cin >> x;
        if (toupper(x) == 'Y')
        {
            for (UserInfo& U : vUser)
            {
                if (U.Name == username) {
                    U = ReReadUserInfo(username);
                    break;
                }
            }
            SaveUserInfoToFile(vUser);
            cout << "User Updated Successfully\n";
        }
        return true;
    }
    else
    {
        cout << " the account isnt exsits \n";
        return false;
    }
}

// go back to menu lists 

void GoBackToMainMenu()
{
    cout << "\n\nPress any key to go back to the main menu...";
    system("pause>0"); // A cleaner way to pause
    Menu();
}

void GoBackToTransactonMenu()
{

    cout << "\n\nPress any key to go back to the Transaction menu...";
    system("pause>0"); // A cleaner way to pause
    system("cls");
    TransactionMenu();
}

void GoBackToUsersMenu()
{

    cout << "\n\nPress any key to go back to the Users menu...";
    system("pause>0"); // A cleaner way to pause
    system("cls");
    ManageUsersMenu();

}

//Transaction Menu List:

bool Deposit(string AccountNumber, double Amount, vector <stinfo >& Vclient)
{

    stinfo Client;
    char Answer;

    cout << " Are You Sure Do You Want To Make This Transaction ? : y/n";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        for (stinfo& C : Vclient)
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                cout << "The Account Balance After Transacton Is :" << C.AccountBalance << endl;
                SaveClientToFile(Mfile, Vclient);
                return true;
            }
    }
    return false;
}

void PrintClientRecordTransaction(stinfo Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;

    cout << "| " << setw(40) << left << Client.Name;

    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void PrintAllFileDataTransaction(vector <stinfo> Vclient)
{
    cout << " \t========================================== < Client List > =================================================\n";
    cout << " \t============================< structure For  " << Vclient.size() << "  Client(S) >\t\t\t===================\n";
    cout << "| " << setw(10) << left << " AccountNumber ";
    cout << "| " << setw(40) << left << " Name ";
    cout << "| " << setw(12) << left << " AccountBalance ";


    cout << "\n ====================================================================================================================\n";

    double TotalBalances = 0;
    for (stinfo Client : Vclient) {
        PrintClientRecordTransaction(Client);
        cout << endl;
        TotalBalances += Client.AccountBalance;
    }
    cout << " The Total Balances Is : " << TotalBalances << endl;
}

void Depositmenu()
{

    vector <stinfo> Vclient = LoadDataFromFileToVector(Mfile);
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    cout << "                    Deposite  Screen                               \n";
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    string accountnumber = ReadAccountNumber();
    stinfo Client;
    while (!FindClientByAccountNumber(Client, accountnumber))
    {
        cout << " The Account Number You Entered Is Not Available [" << accountnumber << "] \n Plz Try Again \n";
        accountnumber = ReadAccountNumber();
    }
    PrintClientCard(Client);
    cout << " Plz Enter The Amount Of Money You Want To Depoist \n";
    double number;
    cin >> number;


    Deposit(accountnumber, number, Vclient);
}

void WithDrawMenu()
{

    vector <stinfo> Vclient = LoadDataFromFileToVector(Mfile);
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    cout << "                    WithDraw Screen                               \n";
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";

    string accountnumber = ReadAccountNumber();
    stinfo Client;

    while (!FindClientByAccountNumber(Client, accountnumber))
    {
        cout << " The Account Number You Entered Is Not Available [" << accountnumber << "] \n Plz Try Again \n";
        accountnumber = ReadAccountNumber();
    }


    PrintClientCard(Client);
    cout << " Plz Enter The Amount Of Money You Want To WitDraw \n";
    double number;
    cin >> number;
    while (number > Client.AccountBalance)
    {
        cout << " The Number You Entered Is Over Your Account Balance : \n Plz Try Again :";
        cin >> number;


    }

    Deposit(accountnumber, number * -1, Vclient);



}

void PrintDataTransactionMenu()
{
    vector <stinfo> Vclient = LoadDataFromFileToVector(Mfile);
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    cout << "                Show Balances Screen                               \n";
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    PrintAllFileDataTransaction(Vclient);
}

//Main menu MenuLists;


void DeletClientMenu()
{
    if (!CheckAccessPermission(enPermissionDate::DeletClientOption))
    {
        NotPermissionedMenuScreen();
        GoBackToMainMenu();
        return;
    }
    vector <stinfo > Vclient = LoadDataFromFileToVector(Mfile);
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    cout << "                    Delete Client Screen                               \n";
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    string AccountNumber = ReadAccountNumber();
    DeletClient(AccountNumber, Vclient);

}

void UpdateClientMenu()
{
    system("cls");
    if (!CheckAccessPermission(enPermissionDate::UpdateClientOption))
    {
        NotPermissionedMenuScreen();
        GoBackToMainMenu();
        return;
    }

    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    cout << "                    Update Client Screen                               \n";
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    vector <stinfo> Vclient = LoadDataFromFileToVector(Mfile);
    string acountnumber = ReadAccountNumber();

    UpdateClientData(acountnumber, Vclient);


}

void FindClientMenu()
{
    system("cls");
    if (!CheckAccessPermission(enPermissionDate::FindClientOption))
    {
        NotPermissionedMenuScreen();
        GoBackToMainMenu();
        return;
    }
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    cout << "                    Find Client Screen                               \n";
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    string accountnumber = ReadAccountNumber();
    FindClient(accountnumber);

}

void PrintClientDataMenu()
{
    if (!CheckAccessPermission(enPermissionDate::ShowClientListOption))
    {
        NotPermissionedMenuScreen();
        GoBackToMainMenu();
        return;
    }
    vector <stinfo> Vclient = LoadDataFromFileToVector(Mfile);
    PrintAllFileData(Vclient);
}

void AddClientMenu()
{
    system("cls");
    if (!CheckAccessPermission(enPermissionDate::AddNewClientOption))
    {
        NotPermissionedMenuScreen();
        GoBackToMainMenu();
        return;
    }
    vector <stinfo> Vclient = LoadDataFromFileToVector(Mfile);
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    cout << "                    Add Client Screen                               \n";
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    AddClients(Vclient);
}

void EndProgramMenu()
{
    system("cls");
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    cout << "                 Program Ends Screen                                \n";
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";

}
// Manage users Menu list//

void AddUsersMenu()
{
    vector <UserInfo> vUers = LoadDataFromFileToVectorForUser(UserFile);
    cout << "_____________________________________________________________________________\n";
    cout << "                   Add User Menu                                         \n";
    cout << "______________________________________________________________________________\n";
    AddNewUsers(vUers);
}

void FindUserMenu()
{
    UserInfo User;
    string Name;
    vector <UserInfo> vUser = LoadDataFromFileToVectorForUser(UserFile);
    cout << "_____________________________________________________________________________\n";
    cout << "                          Find User                                          \n";
    cout << "______________________________________________________________________________\n";
    cout << "Please Enter The User Name You Are Looking For\n";
    cin >> Name;
    FindUserInfo(Name, User);
}

void DeletUserMenu()
{
    UserInfo User;
    string UserName;
    vector <UserInfo> vUsers = LoadDataFromFileToVectorForUser(UserFile);
    cout << "_____________________________________________________________________________\n";
    cout << "                          Delete User                                          \n";
    cout << "______________________________________________________________________________\n";
    cout << " Please Ente The Use You Want To delete \n";
    cin >> UserName;
   
        DeletUser(UserName, vUsers);
}

void UpdateUserMenu()
{
    UserInfo User;
    string UserName;
    vector <UserInfo> vUsers = LoadDataFromFileToVectorForUser(UserFile);
    cout << "_____________________________________________________________________________\n";
    cout << "                          Update User                                          \n";
    cout << "______________________________________________________________________________\n";
    cout << " Please Ente The Use You Want To Update \n";
    cin >> UserName;
    if (UserName == "admin")
        cout << "You Can't Update This User\n";
    else
        UpdateUserInfo(UserName, vUsers);
}

// main menu projects 

void TransactionProject(enTransactonOptions Option)
{
    switch (Option)
    {
    case enTransactonOptions::enDeposit:
        system("cls");
        Depositmenu();
        GoBackToTransactonMenu();
        break;
    case enTransactonOptions::enWitDraw:
        system("cls");
        WithDrawMenu();
        GoBackToTransactonMenu();
        break;
    case enTransactonOptions::enClientTotalBalances:
        system("cls");
        PrintDataTransactionMenu();
        GoBackToTransactonMenu();
        break;
    case enTransactonOptions::enMainMenu:
        system("cls");
        Menu();
        break;

    }
}

void TransactionMenu()
{
    system("cls");
    if (!CheckAccessPermission(enPermissionDate::TransactionMenuOption))
    {
        NotPermissionedMenuScreen();
        GoBackToMainMenu();
        return;
    }
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";
    cout << " \t [1] Deposit \t\t\n";
    cout << " \t [2] WitDrow \t\t\n";
    cout << " \t [3] Total Balances \t\t\n";
    cout << " \t [4] Main Menu \t\t\n";
    cout << " \n================================================================\n";
    cout << " \n================================================================\n";

    TransactionProject(enTransactonOptions(ReadMenuOption(1, 4)));


}

void UserProject(enManageUserOptions Option)
{
    switch (Option)
    {
    case enShowUserList:
        system("cls");
        PrintUsersMenu();
        GoBackToUsersMenu();
        break;
    case enAddNewUser:
        system("cls");
        AddUsersMenu();
        GoBackToUsersMenu();
        break;
    case enDeletUser:
        system("cls");
        DeletUserMenu();
        GoBackToUsersMenu();
        break;
    case enUpdateUser:
        system("cls");
        UpdateUserMenu();
        GoBackToUsersMenu();
        break;
    case enFindUser:
        system("cls");
        FindUserMenu();
        GoBackToUsersMenu();
    case enBackToMainMenu:
        system("cls");
        Menu();
        break;
    }
}

void ManageUsersMenu()
{
    if (!CheckAccessPermission(enPermissionDate::ManageUserOption))
    {
        NotPermissionedMenuScreen();
        GoBackToMainMenu();
        return;
    }
    cout << "========================================================\n";
    cout << "              Manage Users Menu Screen                  \n";
    cout << "========================================================\n";
    cout << setw(25) << left << "[1] List Users " << endl;
    cout << setw(25) << left << "[2] Add New User " << endl;
    cout << setw(25) << left << "[3] Delete User " << endl;
    cout << setw(25) << left << "[4] Update User " << endl;
    cout << setw(25) << left << "[5] Find User   " << endl;
    cout << setw(25) << left << "[6] Back To Main Menu " << endl;
    cout << "========================================================\n";
    cout << "What Do you Want To Choose From 1 To 6 ?:\n";

    UserProject(enManageUserOptions(ReadMenuOption(1, 6)));

}

//project:
void Project(enMenuOptions MainMenueOption)
{

    switch (MainMenueOption)
    {
    case enMenuOptions::enPrintData:
         
            system("cls");

            PrintClientDataMenu();
            GoBackToMainMenu();
       
        break;
    case enMenuOptions::enAddClient:
     
        system("cls");
        AddClientMenu();
        GoBackToMainMenu();
      
        break;
    case enMenuOptions::enDeletClient:
      
        system("cls");
        DeletClientMenu();
        GoBackToMainMenu();
       
        break;
    case enMenuOptions::enUpdateClientData:
     
        system("cls");
        UpdateClientMenu();
        GoBackToMainMenu();
       
        break;
    case enMenuOptions::enFindClient:
      
        system("cls");
        FindClientMenu();
        GoBackToMainMenu();
      
        break;
    case enMenuOptions::Transaction:
        
        system("cls");
        TransactionMenu();
        
       
        break;
    case enMenuOptions::UsersMenu:
       
        system("cls");
        ManageUsersMenu();
    case enMenuOptions::enEndProgram:
        system("cls");
        LogInMenu();
        break;
    }
}

void Menu()
{
    system("cls");
    cout << "\n =====================================================================\n";
    cout << "                    Program Main Menu                                   \n";
    cout << "\n =====================================================================\n";
    cout << "          [1] Show Client List   \n";
    cout << "          [2] Add New Client     \n";
    cout << "          [3] Delet Client       \n";
    cout << "          [4] Update Client Info \n";
    cout << "          [5] Find Client        \n";
    cout << "          [6] Transaction        \n";
    cout << "          [7] Manage User        \n";
    cout << "          [8] Log out            \n";
    cout << "\n =====================================================================";
    cout << "\n =====================================================================";
    cout << "\n Choose From [1] To [7] : \n";
    int number = ReadMenuOption(1, 8);
    Project(enMenuOptions(number));
}
bool LogIn(string username, string password)
{
    vector <UserInfo> vUser = LoadDataFromFileToVectorForUser(UserFile);
    for (UserInfo U : vUser)
    {
        if (U.Name == username && U.PassWord == password)
        {
            CurrentUser = U;
            return true;
        }
    }
    return false;
}
void LogInMenu()
{
    cout << "_____________________________________________________________________________\n";
    cout << "                          Login Menu                                          \n";
    cout << "______________________________________________________________________________\n";
    cout << " Plz Enter User Name  :" << endl;
    string username, Password;
    getline(cin >>ws , username);
    cout << " Plz Enter  Password  :" << endl;
    getline(cin >> ws, Password);
    while (LogIn(username, Password) == false)
    {
        cout << "The user name " << username << " and Password " << Password << " are invalid \nPlz try again\n";
        cout << " Plz Enter User Name  :" << endl;
        getline(cin, username);
        cout << " Plz Enter  Password  :" << endl;
        getline(cin >> ws, Password);
    }

    Menu();
}
int main()
{
    LogInMenu();
    system("Pause>0");
}
