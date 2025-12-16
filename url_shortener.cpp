#include <iostream>
#include <unordered_map>
#include <string>
#include <random>

using namespace std;

class URLShortener {
private:
    // Hash table: shortCode -> longURL
    unordered_map<string, string> urlMap;
    
    // Reverse hash table: longURL -> shortCode (to avoid duplicates)
    unordered_map<string, string> reverseMap;
    
    // Characters used for generating short codes
    const string CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    // Generate a random short code
    string generateCode(int length = 6) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, CHARS.size() - 1);
        
        string code;
        for (int i = 0; i < length; i++) {
            code += CHARS[dist(gen)];
        }
        return code;
    }

public:
    // Shorten a URL
    string shorten(const string& longURL) {
        // Check if URL already shortened
        if (reverseMap.find(longURL) != reverseMap.end()) {
            return reverseMap[longURL];
        }
        
        // Generate unique code
        string code;
        do {
            code = generateCode();
        } while (urlMap.find(code) != urlMap.end());
        
        // Store in both hash tables
        urlMap[code] = longURL;
        reverseMap[longURL] = code;
        
        return code;
    }
    
    // Expand a short code to original URL
    string expand(const string& code) {
        if (urlMap.find(code) != urlMap.end()) {
            return urlMap[code];
        }
        return "ERROR: Code not found";
    }
    
    // Display all mappings
    void displayAll() {
        if (urlMap.empty()) {
            cout << "No URLs stored.\n";
            return;
        }
        
        cout << "\n+--------+------------------------------------------+\n";
        cout << "| Code   | Original URL                             |\n";
        cout << "+--------+------------------------------------------+\n";
        
        for (const auto& pair : urlMap) {
            cout << "| " << pair.first << " | " << pair.second.substr(0, 40);
            if (pair.second.length() > 40) cout << "...";
            cout << "\n";
        }
        cout << "+--------+------------------------------------------+\n";
        cout << "Total entries: " << urlMap.size() << "\n";
    }
};

void displayMenu() {
    cout << "\n===== URL SHORTENER =====\n";
    cout << "1. Shorten URL\n";
    cout << "2. Expand URL\n";
    cout << "3. Display All\n";
    cout << "4. Exit\n";
    cout << "Choice: ";
}

int main() {
    URLShortener shortener;
    int choice;
    string input;
    
    cout << "Welcome to URL Shortener!\n";
    cout << "Using Hash Table (unordered_map) for O(1) lookups\n";
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear newline
        
        switch (choice) {
            case 1: {
                cout << "Enter long URL: ";
                getline(cin, input);
                string code = shortener.shorten(input);
                cout << "Short code: " << code << "\n";
                break;
            }
            case 2: {
                cout << "Enter short code: ";
                getline(cin, input);
                string url = shortener.expand(input);
                cout << "Original URL: " << url << "\n";
                break;
            }
            case 3:
                shortener.displayAll();
                break;
            case 4:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
    
    return 0;
}
