#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

using namespace std;

// Password Entry Class
class PasswordEntry {
public:
    string website;
    string encryptedPassword;
    string encryptionKey;
    PasswordEntry* next;
    PasswordEntry* prev;

    PasswordEntry(const string& site, const string& password, const string& key)
        : website(site), encryptedPassword(encrypt(password, key)),
          encryptionKey(key), next(nullptr), prev(nullptr) {}

    static string encrypt(const string& password, const string& key) {
        string encrypted = password;
        for (size_t i = 0; i < password.length(); ++i) {
            encrypted[i] = password[i] ^ key[i % 3];
        }
        return encrypted;
    }

    string decrypt(const string& key) {
        if (key != encryptionKey) return "";

        string decrypted = encryptedPassword;
        for (size_t i = 0; i < encryptedPassword.length(); ++i) {
            decrypted[i] = encryptedPassword[i] ^ key[i % 3];
        }
        return decrypted;
    }
};

// Binary Search Tree for Password Management
class PasswordBST {
private:
    class BSTNode {
    public:
        PasswordEntry* entry;
        BSTNode* left;
        BSTNode* right;

        BSTNode(PasswordEntry* e) : entry(e), left(nullptr), right(nullptr) {}
    };

    BSTNode* root;

    BSTNode* insertRecursive(BSTNode* node, PasswordEntry* entry) {
        if (node == nullptr) {
            return new BSTNode(entry);
        }

        if (entry->website < node->entry->website) {
            node->left = insertRecursive(node->left, entry);
        } else if (entry->website > node->entry->website) {
            node->right = insertRecursive(node->right, entry);
        }

        return node;
    }

    void inOrderTraversal(BSTNode* node) {
        if (node == nullptr) return;

        inOrderTraversal(node->left);
        cout << "Website: " << node->entry->website
             << " | Encrypted Password: " << node->entry->encryptedPassword
             << endl;
        inOrderTraversal(node->right);
    }

    PasswordEntry* searchRecursive(BSTNode* node, const string& website) {
        if (node == nullptr) return nullptr;

        if (website == node->entry->website) {
            return node->entry;
        } else if (website < node->entry->website) {
            return searchRecursive(node->left, website);
        } else {
            return searchRecursive(node->right, website);
        }
    }

    BSTNode* deleteRecursive(BSTNode* node, const string& website) {
        if (node == nullptr) return nullptr;

        if (website < node->entry->website) {
            node->left = deleteRecursive(node->left, website);
        } else if (website > node->entry->website) {
            node->right = deleteRecursive(node->right, website);
        } else {
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            BSTNode* temp = findMin(node->right);
            node->entry = temp->entry;
            node->right = deleteRecursive(node->right, temp->entry->website);
        }
        return node;
    }

    BSTNode* findMin(BSTNode* node) {
        BSTNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void bstToArray(BSTNode* node, vector<PasswordEntry*>& arr) {
        if (node == nullptr) return;
        bstToArray(node->left, arr);
        arr.push_back(node->entry);
        bstToArray(node->right, arr);
    }

    BSTNode* arrayToBST(vector<PasswordEntry*>& arr, int start, int end) {
        if (start > end) return nullptr;

        int mid = (start + end) / 2;
        BSTNode* node = new BSTNode(arr[mid]);

        node->left = arrayToBST(arr, start, mid - 1);
        node->right = arrayToBST(arr, mid + 1, end);

        return node;
    }
// Continuing from PasswordBST class...
    void quickSort(vector<PasswordEntry*>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    int partition(vector<PasswordEntry*>& arr, int low, int high) {
        PasswordEntry* pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j]->website <= pivot->website) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    void mergeSort(vector<PasswordEntry*>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    void merge(vector<PasswordEntry*>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<PasswordEntry*> L(n1), R(n2);

        for (int i = 0; i < n1; i++) {
            L[i] = arr[left + i];
        }
        for (int j = 0; j < n2; j++) {
            R[j] = arr[mid + 1 + j];
        }

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (L[i]->website <= R[j]->website) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

public:
    PasswordBST() : root(nullptr) {}

    void insert(PasswordEntry* entry) {
        root = insertRecursive(root, entry);
    }

    void displayAll() {
        inOrderTraversal(root);
    }

    PasswordEntry* search(const string& website) {
        return searchRecursive(root, website);
    }

    void remove(const string& website) {
        root = deleteRecursive(root, website);
    }

    void sortByWebsiteQuick() {
        vector<PasswordEntry*> entries;
        bstToArray(root, entries);

        if (!entries.empty()) {
            quickSort(entries, 0, entries.size() - 1);
            root = arrayToBST(entries, 0, entries.size() - 1);
        }
    }

    void sortByWebsiteMerge() {
        vector<PasswordEntry*> entries;
        bstToArray(root, entries);

        if (!entries.empty()) {
            mergeSort(entries, 0, entries.size() - 1);
            root = arrayToBST(entries, 0, entries.size() - 1);
        }
    }
};

class PasswordManager {
private:
    PasswordEntry* head;
    PasswordEntry* tail;
    PasswordBST passwordBST;

    class UndoStack {
    private:
        struct UndoNode {
            PasswordEntry* entry;
            UndoNode* next;
            UndoNode(PasswordEntry* e) : entry(e), next(nullptr) {}
        };
        UndoNode* top;

    public:
        UndoStack() : top(nullptr) {}

        void push(PasswordEntry* entry) {
            UndoNode* newNode = new UndoNode(entry);
            newNode->next = top;
            top = newNode;
        }

        PasswordEntry* pop() {
            if (isEmpty()) return nullptr;

            UndoNode* temp = top;
            PasswordEntry* entry = temp->entry;
            top = top->next;
            delete temp;
            return entry;
        }

        bool isEmpty() {
            return top == nullptr;
        }
    } undoStack;

    class AdminAuthentication {
    private:
        static const string ADMIN_PIN;
        int attempts;

    public:
        AdminAuthentication() : attempts(3) {}

        bool authenticate() {
            while (attempts > 0) {
                string inputPin;
                cout << "Enter Admin PIN (" << attempts << " attempts left): ";
                cin >> inputPin;

                if (inputPin == ADMIN_PIN) {
                    return true;
                }

                attempts--;
                cout << "Incorrect PIN. " << attempts << " attempts remaining.\n";
            }
            return false;
        }
    };

public:
    PasswordManager() : head(nullptr), tail(nullptr) {}

    void addPassword(const string& website, const string& password, const string& key) {
        PasswordEntry* newEntry = new PasswordEntry(website, password, key);

        if (!head) {
            head = tail = newEntry;
        } else {
            tail->next = newEntry;
            newEntry->prev = tail;
            tail = newEntry;
        }

        passwordBST.insert(newEntry);
        undoStack.push(newEntry);
    }

    void displayPasswords() {
        passwordBST.displayAll();
    }

    void deletePassword(const string& website) {
        AdminAuthentication auth;
        if (!auth.authenticate()) {
            cout << "Authentication failed. Access denied.\n";
            return;
        }

        PasswordEntry* entryToDelete = passwordBST.search(website);
        if (!entryToDelete) {
            cout << "Password not found.\n";
            return;
        }

        if (entryToDelete->prev) entryToDelete->prev->next = entryToDelete->next;
        if (entryToDelete->next) entryToDelete->next->prev = entryToDelete->prev;
        if (head == entryToDelete) head = entryToDelete->next;
        if (tail == entryToDelete) tail = entryToDelete->prev;

        passwordBST.remove(website);
        undoStack.push(entryToDelete);

        cout << "Password deleted successfully.\n";
    }

    void decryptPassword(const string& website, const string& key) {
        PasswordEntry* entry = passwordBST.search(website);
        if (!entry) {
            cout << "Password not found.\n";
            return;
        }

        string decrypted = entry->decrypt(key);
        if (decrypted.empty()) {
            cout << "Incorrect decryption key.\n";
            return;
        }

        cout << "Decrypted Password: " << decrypted << endl;
    }

    void undoLastOperation() {
        if (undoStack.isEmpty()) {
            cout << "No operations to undo.\n";
            return;
        }

        PasswordEntry* lastEntry = undoStack.pop();
        cout << "Last operation undone.\n";
    }

    PasswordBST& getPasswordBST() {
        return passwordBST;
    }
};

// Define Admin PIN
const string PasswordManager::AdminAuthentication::ADMIN_PIN = "dsaastar";

string generateRandomPassword() {
    const string chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
    string password;

    srand(time(nullptr));
    for (int i = 0; i < 14; ++i) {
        password += chars[rand() % chars.length()];
    }

    return password;
}

void displayMenu() {
    cout << "\n=== Password Management Console ===\n";
    cout << "1. Decrypt Existing Password\n";
    cout << "2. Generate and Encrypt New Password\n";
    cout << "3. Add Custom Password\n";
    cout << "4. Display All Encrypted Passwords\n";
    cout << "5. Delete Existing Password\n";
    cout << "6. Undo Last Operation\n";
    cout << "7. Sort Passwords (QuickSort)\n";
    cout << "8. Sort Passwords (MergeSort)\n";
    cout << "9. Exit\n";
    cout << "Enter your choice (1-9): ";
}

int main() {
    PasswordManager passwordManager;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1: {
                string website, decryptKey;
                cout << "Enter website: ";
                getline(cin, website);
                cout << "Enter decryption key: ";
                getline(cin, decryptKey);

                passwordManager.decryptPassword(website, decryptKey);
                break;
            }
            case 2: {
                string website, encryptKey;
                string generatedPassword;

                cout << "Enter website: ";
                getline(cin, website);

                generatedPassword = generateRandomPassword();
                cout << "Generated Password: " << generatedPassword << endl;

                cout << "Enter encryption key (3 letters): ";
                getline(cin, encryptKey);

                while (encryptKey.length() != 3) {
                    cout << "Key must be exactly 3 letters. Try again: ";
                    getline(cin, encryptKey);
                }

                passwordManager.addPassword(website, generatedPassword, encryptKey);
                break;
            }
            case 3: {
                string website, customPassword, encryptKey;

                cout << "Enter website: ";
                getline(cin, website);

                cout << "Enter your custom password: ";
                getline(cin, customPassword);

                cout << "Enter encryption key (3 letters): ";
                getline(cin, encryptKey);

                while (encryptKey.length() != 3) {
                    cout << "Key must be exactly 3 letters. Try again: ";
                    getline(cin, encryptKey);
                }

                passwordManager.addPassword(website, customPassword, encryptKey);
                break;
            }
            case 4: {
                passwordManager.displayPasswords();
                break;
            }
            case 5: {
                string website;
                cout << "Enter website to delete: ";
                getline(cin, website);

                passwordManager.deletePassword(website);
                break;
            }
            case 6: {
                passwordManager.undoLastOperation();
                break;
            }
            case 7: {
                passwordManager.getPasswordBST().sortByWebsiteQuick();
                cout << "Passwords sorted using QuickSort.\n";
                break;
            }
            case 8: {
                passwordManager.getPasswordBST().sortByWebsiteMerge();
                cout << "Passwords sorted using MergeSort.\n";
                break;
            }
            case 9: {
                cout << "Exiting Password Management Console...\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
            }
        }

        if (choice != 9) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 9);

    return 0;
}
