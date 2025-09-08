#include <bits/stdc++.h>

using namespace std;

class PasswordEntry
{
public:
    string website;
    string username;
    string passwordHash;
    string originalPassword;
};

class Vault
{
    vector<PasswordEntry> entries;

public:
    void addEntry(const PasswordEntry &entry) { entries.push_back(entry); }

    void listEntries(bool showPasswords = false)
    {
        if (entries.empty())
        {
            cout << "No entries yet.\n";
            return;
        }
        for (auto &e : entries)
        {
            cout << "Website: " << e.website << endl
                 << "Username: " << e.username << endl;
            if (showPasswords)
            {
                cout << "Password: " << e.originalPassword << endl;
                cout << "==================" << endl;
            }
            cout << endl;
        }
    }

    PasswordEntry *getEntry(const string &website)
    {
        for (auto &e : entries)
        {
            if (e.website == website)
                return &e;
        }
        return nullptr;
    }

    void deleteEntry(const string &website)
    {
        for (size_t i = 0; i < entries.size(); i++)
        {
            if (entries[i].website == website)
            {
                entries.erase(entries.begin() + i);
                cout << "Deleted entry for " << website << "\n";
                return;
            }
        }
        cout << "No entry found for " << website << "\n";
    }
};

class Authenticator
{
    size_t hashed;

public:
    void setmasterpass(const string &password)
    {
        hash<string> hasher;
        hashed = hasher(password);
    }

    bool verifymasterpass(const string &password)
    {
        hash<string> hasher;
        return hashed == hasher(password);
    }
};

string inputpass()
{
    string password;
    cout << "Type Password ";
    getline(cin, password);
    return password;
}

string genpass(int length = 8)
{
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    string pass;
    for (int i = 0; i < length; i++)
    {
        pass += chars[rand() % chars.size()];
    }
    return pass;
}

int main()
{
    cout << "WELCOME TO SECUREVAULT :)" << endl;

    Authenticator auth;
    Vault vault;

    cout << "Please set master password: " << endl;
    string master = inputpass();
    auth.setmasterpass(master);
    cout << "Master password set!" << endl;

    // ---- Login ----
    string input;
    while (true)
    {
        cout << "Enter master password to access vault: ";
        input = inputpass();
        if (auth.verifymasterpass(input))
        {
            cout << "Great! Access granted :)" << endl;
            break;
        }
        else
        {
            cout << "Oops! Incorrect password.Please Try again." << endl;
        }
    }

    int choice;
    do
    {
        cout << endl;
        cout << "1. Add password" << endl;
        cout << "2. List entries" << endl;
        cout << "3. Delete entry" << endl;
        cout << "4. Generate strong password" << endl;
        cout << "5. Exit" << endl;
        cout << "Choice: ";

        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            PasswordEntry entry;
            cout << "Website: ";
            getline(cin, entry.website);
            cout << "Username: ";
            getline(cin, entry.username);
            cout << "Password: " << endl;
            string password = inputpass();
            entry.originalPassword = password;
            entry.passwordHash = to_string(hash<string>{}(password));
            vault.addEntry(entry);
            cout << "Password added!" << endl;
        }
        else if (choice == 2)
        {
            cout << "Enter master password to view entries: " << endl;
            string masterCheck = inputpass();
            if (auth.verifymasterpass(masterCheck))
            {
                cout << "Access granted!\n";
                cout << "1. List all entries\n";
                cout << "2. List entry for a specific website\n";
                cout << "Enter choice: ";
                int choice;
                cin >> choice;
                cin.ignore();

                if (choice == 1)
                {
                    cout << "Showing all entries:\n";
                    vault.listEntries(true);
                }
                else if (choice == 2)
                {
                    cout << "Enter website name: ";
                    string website;
                    getline(cin, website);
                    PasswordEntry *entry = vault.getEntry(website);
                    if (entry != nullptr)
                    {
                        cout << "Website: " << entry->website << endl;
                        cout << "Username: " << entry->username << endl;
                        cout << "Password: " << entry->originalPassword << endl;
                        cout << "==================" << endl;
                    }
                    else
                    {
                        cout << "No entry found for " << website << endl;
                    }
                }
                else
                {
                    cout << "Invalid choice.\n";
                }
            }
            else
            {
                cout << "Incorrect master password. Access denied.\n";
            }
        }

        else if (choice == 3)
        {
            string site;
            cout << "Enter website to delete: ";
            getline(cin, site);
            vault.deleteEntry(site);
        }
        else if (choice == 4)
        {
            cout << "enter the length you want" << endl;
            int n;
            cin >> n;
            cout << "Generated password: " << genpass(n) << endl;
        }
    } while (choice != 5);

    cout << "Thanks for using Secure Vault" << endl
         << "Exiting vault..." << endl;
    return 0;
}
