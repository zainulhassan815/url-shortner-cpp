#include <iostream>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class URLShortener {
private:
    unordered_map<string, string> urlMap;      // shortCode -> longURL
    unordered_map<string, string> reverseMap;  // longURL -> shortCode
    
    const string CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    string generateCode(int length = 6) {
        string code;
        for (int i = 0; i < length; i++) {
            code += CHARS[rand() % CHARS.size()];
        }
        return code;
    }

public:
    string shorten(const string& longURL) {
        // Check if already exists
        if (reverseMap.find(longURL) != reverseMap.end()) {
            return reverseMap[longURL];
        }
        
        // Generate unique code
        string code;
        do {
            code = generateCode();
        } while (urlMap.find(code) != urlMap.end());
        
        // Store in hash tables
        urlMap[code] = longURL;
        reverseMap[longURL] = code;
        
        return code;
    }
    
    string expand(const string& code) {
        if (urlMap.find(code) != urlMap.end()) {
            return urlMap[code];
        }
        return "ERROR: Code not found";
    }
    
    void displayAll() {
        if (urlMap.empty()) {
            cout << "No URLs stored.\n";
            return;
        }
        
        cout << "\nStored URLs:\n";
        for (const auto& pair : urlMap) {
            cout << pair.first << " -> " << pair.second << "\n";
        }
        cout << "Total: " << urlMap.size() << "\n";
    }
};

int main() {
    srand(time(0));  // Seed random number generator
    
    URLShortener shortener;
    int choice;
    string input;
    
    while (true) {
        cout << "\n1.Shorten  2.Expand  3.Display  4.Exit\nChoice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                cout << "Enter URL: ";
                getline(cin, input);
                cout << "Code: " << shortener.shorten(input) << "\n";
                break;
            case 2:
                cout << "Enter code: ";
                getline(cin, input);
                cout << "URL: " << shortener.expand(input) << "\n";
                break;
            case 3:
                shortener.displayAll();
                break;
            case 4:
                return 0;
        }
    }
}
