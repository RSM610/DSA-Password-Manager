# Password Manager Implementation in C++

A comprehensive password management system implementing various data structures and algorithms for efficient password storage, retrieval, and management.

## Features

- **Secure Password Storage**: Store encrypted passwords using XOR-based encryption
- **Binary Search Tree**: Efficient password organization and retrieval
- **Multiple Sorting Options**: QuickSort and MergeSort implementations
- **Undo Functionality**: Revert recent operations
- **Admin Authentication**: Secure access control for sensitive operations
- **Random Password Generation**: Generate strong passwords automatically

## Data Structures

### 1. Binary Search Tree (BST)
- Efficient O(log n) operations for search, insert, and delete
- Self-balancing through reconstruction after sorting
- Inorder traversal for sorted password display

### 2. Doubly Linked List
- Bidirectional traversal of password entries
- Maintains insertion order
- Facilitates sequential access

### 3. Stack
- Implements undo functionality
- LIFO (Last In First Out) principle
- Tracks recent operations

## Time Complexities

| Operation | Average Case | Worst Case |
|-----------|--------------|------------|
| Search    | O(log n)     | O(n)       |
| Insert    | O(log n)     | O(n)       |
| Delete    | O(log n)     | O(n)       |
| Sort      | O(n log n)   | O(n log n) |

## Core Classes

### PasswordEntry
```cpp
class PasswordEntry {
    string website;
    string encryptedPassword;
    string encryptionKey;
    PasswordEntry* next;
    PasswordEntry* prev;
};
```

### PasswordBST
```cpp
class PasswordBST {
    class BSTNode;
    BSTNode* root;
    // BST operations
};
```

### PasswordManager
```cpp
class PasswordManager {
    PasswordEntry* head;
    PasswordEntry* tail;
    PasswordBST passwordBST;
    UndoStack undoStack;
};
```

## Key Algorithms

### 1. Encryption/Decryption
```cpp
string encrypt(const string& password, const string& key) {
    string encrypted = password;
    for (size_t i = 0; i < password.length(); ++i) {
        encrypted[i] = password[i] ^ key[i % 3];
    }
    return encrypted;
}
```

### 2. BST Reconstruction
```cpp
BSTNode* arrayToBST(vector<PasswordEntry*>& arr, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    BSTNode* node = new BSTNode(arr[mid]);
    node->left = arrayToBST(arr, start, mid - 1);
    node->right = arrayToBST(arr, mid + 1, end);
    return node;
}
```

## Usage

### 1. Building the Project
```bash
g++ password_manager.cpp -o password_manager
```

### 2. Running the Program
```bash
./password_manager
```

### 3. Menu Options
1. Decrypt Existing Password
2. Generate and Encrypt New Password
3. Add Custom Password
4. Display All Encrypted Passwords
5. Delete Existing Password
6. Undo Last Operation
7. Sort Passwords (QuickSort)
8. Sort Passwords (MergeSort)
9. Exit

## Security Features

1. **Admin Authentication**
   - PIN-based access control
   - Limited attempts (3)
   - Required for sensitive operations

2. **Password Encryption**
   - XOR-based encryption
   - 3-letter key requirement
   - Secure storage

## Implementation Details

### BST Operations
- Maintains ordered storage of passwords
- Self-balancing through reconstruction
- Efficient searching and retrieval

### Sorting Mechanisms
1. **QuickSort**
   - Partition-based sorting
   - Average case O(n log n)
   - In-place sorting

2. **MergeSort**
   - Divide and conquer approach
   - Stable sorting
   - O(n log n) guaranteed

### Undo Functionality
- Stack-based operation tracking
- Supports multiple undo operations
- Memory-efficient implementation

## Best Practices

1. **Password Management**
   - Use strong, random passwords
   - Regular password updates
   - Secure key storage

2. **System Usage**
   - Regular backups
   - Admin PIN protection
   - Clean memory after use

## Contributing

Feel free to contribute to this project by:
1. Forking the repository
2. Creating your feature branch
3. Committing your changes
4. Opening a pull request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Data Structures and Algorithms concepts
- Modern C++ features
- Security best practices

## Requirements

- C++11 or higher
- Standard Template Library (STL)
- Command Line Interface support

## Notes

- This is an educational implementation
- Not recommended for production use without additional security measures
- Demonstrates DSA concepts and C++ features
