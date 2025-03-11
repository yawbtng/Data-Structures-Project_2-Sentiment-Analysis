/**
 * DSString.cpp
 * 
 * Implementation of the DSString class declared in DSString.h.
 * All functions manually handle character arrays without using <cstring> or <string>.
 */

#include "../include/DSString.h"

/**
 * Helper function: Calculate the length of a C-string
 * @param str Null-terminated C-string
 * @return Length of the string (number of characters excluding null terminator)
 */
int stringLength(const char* str) {
    // Handle null pointer case
    if (str == nullptr) {
        return 0;
    }
    
    int count = 0;
    // Count characters until null terminator is reached
    while (str[count] != '\0') {
        count++;
    }
    return count;
}

/**
 * Helper function: Copy characters from source to destination
 * @param destination Target array (must be pre-allocated with sufficient space)
 * @param source Source array to copy from
 * @param length Number of characters to copy (excluding null terminator)
 */
void stringCopy(char* destination, const char* source, int length) {
    // Handle null pointer cases
    if (destination == nullptr || source == nullptr) {
        return;
    }
    
    // Copy each character
    for (int i = 0; i < length; i++) {
        destination[i] = source[i];
    }
    // Add null terminator
    destination[length] = '\0';
}

/**
 * Helper function: Compare two C-strings lexicographically
 * @param str1 First string to compare
 * @param str2 Second string to compare
 * @return Negative if str1 < str2, 0 if equal, positive if str1 > str2
 */
int stringCompare(const char* str1, const char* str2) {
    // Handle null pointer cases
    if (str1 == nullptr && str2 == nullptr) {
        return 0;
    }
    if (str1 == nullptr) {
        return -1;
    }
    if (str2 == nullptr) {
        return 1;
    }
    
    // Compare characters until difference is found or end of string
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    
    // If we reached here, the strings match up to the length of the shorter one
    // Return the difference in length
    return str1[i] - str2[i];
}

// Default constructor - creates an empty string
DSString::DSString() {
    // Allocate memory for just the null terminator
    data = new char[1];
    // Set null terminator
    data[0] = '\0';
    // Set length to 0
    length = 0;
}

// Constructor from C-string
DSString::DSString(const char* str) {
    // Handle null pointer case
    if (str == nullptr) {
        data = new char[1];
        data[0] = '\0';
        length = 0;
        return;
    }
    
    // Calculate string length
    length = stringLength(str);
    
    // Allocate memory for characters plus null terminator
    data = new char[length + 1];
    
    // Copy characters from input string
    stringCopy(data, str, length);
}

// Copy constructor
DSString::DSString(const DSString& other) {
    // Allocate new memory for the copy
    length = other.length;
    data = new char[length + 1];
    
    // Copy characters from other string
    stringCopy(data, other.data, length);
}

// Destructor
DSString::~DSString() {
    // Free the dynamically allocated memory
    delete[] data;
    
    // Set data to nullptr (not strictly necessary, but good practice)
    data = nullptr;
    length = 0;
}

// Assignment operator
DSString& DSString::operator=(const DSString& other) {
    // Check for self-assignment
    if (this == &other) {
        return *this;
    }
    
    // Delete old memory
    delete[] data;
    
    // Allocate new memory for the copy
    length = other.length;
    data = new char[length + 1];
    
    // Copy characters from other string
    stringCopy(data, other.data, length);
    
    // Return reference to this object
    return *this;
}

// Addition operator (concatenation)
DSString DSString::operator+(const DSString& other) const {
    // Calculate the length of the new string
    int newLength = length + other.length;
    
    // Create a new character array to hold the concatenated string
    char* newData = new char[newLength + 1];
    
    // Copy characters from this string
    stringCopy(newData, data, length);
    
    // Copy characters from other string (without the null terminator from this string)
    for (int i = 0; i < other.length; i++) {
        newData[length + i] = other.data[i];
    }
    
    // Add null terminator to the end
    newData[newLength] = '\0';
    
    // Create a new DSString with this data
    DSString result;
    
    // Clean up temporary result object's data
    delete[] result.data;
    
    // Set the new data and length
    result.data = newData;
    result.length = newLength;
    
    return result;
}

// Equality operator
bool DSString::operator==(const DSString& other) const {
    // If lengths differ, strings are not equal
    if (length != other.length) {
        return false;
    }
    
    // Compare each character
    for (int i = 0; i < length; i++) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    
    // All characters matched
    return true;
}

// Less than operator
bool DSString::operator<(const DSString& other) const {
    return stringCompare(data, other.data) < 0;
}

// Greater than operator
bool DSString::operator>(const DSString& other) const {
    return stringCompare(data, other.data) > 0;
}

// Array subscript operator (non-const version)
char& DSString::operator[](int index) {
    // Note: No bounds checking for performance reasons
    return data[index];
}

// Array subscript operator (const version)
const char& DSString::operator[](int index) const {
    // Note: No bounds checking for performance reasons
    return data[index];
}

// Returns the length of the string
int DSString::size() const {
    return length;
}

// Returns a C-style string representation
const char* DSString::c_str() const {
    return data;
}

// Returns a substring of this string
DSString DSString::substring(int start, int numChars) const {
    // Check bounds to prevent invalid memory access
    if (start < 0 || start >= length || numChars <= 0) {
        return DSString();  // Return empty string for invalid parameters
    }
    
    // Adjust numChars if it would go past the end of the string
    if (start + numChars > length) {
        numChars = length - start;
    }
    
    // Create a new character array for the substring
    char* subData = new char[numChars + 1];
    
    // Copy the substring characters
    for (int i = 0; i < numChars; i++) {
        subData[i] = data[start + i];
    }
    
    // Add null terminator
    subData[numChars] = '\0';
    
    // Create a DSString from this data
    DSString result;
    
    // Clean up temporary result object's data
    delete[] result.data;
    
    // Set the new data and length
    result.data = subData;
    result.length = numChars;
    
    return result;
}

// Converts string to lowercase
DSString DSString::toLowerCase() const {
    // Create a new character array
    char* lowerData = new char[length + 1];
    
    // Copy characters, converting uppercase to lowercase
    for (int i = 0; i < length; i++) {
        // Check if character is uppercase (ASCII 'A' = 65, 'Z' = 90)
        if (data[i] >= 'A' && data[i] <= 'Z') {
            // Convert to lowercase (ASCII difference between upper and lower is 32)
            lowerData[i] = data[i] + 32;
        } else {
            // Copy character as is
            lowerData[i] = data[i];
        }
    }
    
    // Add null terminator
    lowerData[length] = '\0';
    
    // Create a DSString from this data
    DSString result;
    
    // Clean up temporary result object's data
    delete[] result.data;
    
    // Set the new data and length
    result.data = lowerData;
    result.length = length;
    
    return result;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const DSString& str) {
    // Output the string character by character
    for (int i = 0; i < str.length; i++) {
        os << str.data[i];
    }
    return os;
}
