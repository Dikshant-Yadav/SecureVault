#include<bits/stdc++.h>

using namespace std;

// ---- PasswordEntry ----
struct PasswordEntry {
    string website;
    string username;
    string passwordHash;
    string originalPassword;
};

// ---- Vault ----
class Vault {
    vector<PasswordEntry> entries;
public:
    void addEntry(const PasswordEntry& entry) { entries.push_back(entry); }

    void listEntries(bool showPasswords = false) {
        if(entries.empty()){
            cout << "No entries yet.\n";
            return;
        }
        for (auto &e : entries) {
            cout << "Website: " << e.website << ", Username: " << e.username;
            if(showPasswords) {
                cout << ", Password: " << e.originalPassword;
            }
            cout << endl;
        }
    }

    PasswordEntry* getEntry(const string& website){
        for(auto &e: entries){
            if(e.website == website)
                return &e;
        }
        return nullptr;
    }

    void deleteEntry(const string& website){
        for(size_t i=0;i<entries.size();i++){
            if(entries[i].website == website){
                entries.erase(entries.begin() + i);
                cout<<"Deleted entry for "<<website<<"\n";
                return;
            }
        }
        cout<<"No entry found for "<<website<<"\n";
    }
};

// ---- Authenticator ----
class Authenticator {
    size_t masterHash;
public:
    void setMasterPassword(const string& password){
        hash<string> hasher;
        masterHash = hasher(password);
    }

    bool verifyMaster(const string& password){
        hash<string> hasher;
        return masterHash == hasher(password);
    }
};

// ---- Simple terminal input for password ----
string inputPassword(){
    string password;
    cout << "(Input hidden not supported, type normally) ";
    getline(cin, password);
    return password;
}

// ---- Simple password generator ----
string generatePassword(int length=8){
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    string pass;
    for(int i=0;i<length;i++){
        pass += chars[rand() % chars.size()];
    }
    return pass;
}

int main(){
    srand(time(0));

    Authenticator auth;
    Vault vault;

    // ---- Master password setup ----
    cout<<"Set master password: ";
    string master = inputPassword();
    auth.setMasterPassword(master);
    cout<<"Master password set!\n";

    // ---- Login ----
    string input;
    while(true){
        cout<<"Enter master password to access vault: ";
        input = inputPassword();
        if(auth.verifyMaster(input)){
            cout<<"Access granted!\n";
            break;
        } else {
            cout<<"Incorrect password. Try again.\n";
        }
    }

    // ---- Terminal menu ----
    int choice;
    do{
        cout<<"\n1. Add password\n2. List entries\n3. Delete entry\n4. Generate strong password\n5. Exit\nChoice: ";
        cin >> choice;
        cin.ignore(); // clear newline
        
        if(choice==1){
            PasswordEntry entry;
            cout<<"Website: "; getline(cin, entry.website);
            cout<<"Username: "; getline(cin, entry.username);
            cout<<"Password: "; 
            string password = inputPassword();
            entry.originalPassword = password;
            entry.passwordHash = to_string(hash<string>{}(password));
            vault.addEntry(entry);
            cout<<"Password added!\n";
        } 
        else if(choice==2){
            // Verify master password again before showing passwords
            cout<<"Enter master password to view entries: ";
            string masterCheck = inputPassword();
            if(auth.verifyMaster(masterCheck)){
                cout<<"Access granted! Showing entries with passwords:\n";
                vault.listEntries(true); // Show passwords
            } else {
                cout<<"Incorrect master password. Access denied.\n";
            }
        }
        else if(choice==3){
            string site;
            cout<<"Enter website to delete: "; getline(cin, site);
            vault.deleteEntry(site);
        } 
        else if(choice==4){
            cout<<"Generated password: "<<generatePassword(12)<<"\n";
        }
    }while(choice!=5);

    cout<<"Exiting vault...\n";
    return 0;
}