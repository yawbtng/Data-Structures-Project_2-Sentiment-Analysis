/**
 * DSString.h
 * 
 * Custom string class implementation that uses dynamic memory allocation.
 * Follows the rule-of-three pattern (constructor, copy constructor, destructor).
 * Implements various operations and comparisons via operator overloading.
 * 
 * This class does NOT use <cstring> or <string> internally.
 */

#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream> // For ostream operator<< overloading

/**
 * DSString class - A custom implementation of a string class using dynamic memory
 * 
 * This class provides basic string functionality while managing its own memory.
 * It stores strings as null-terminated char arrays and tracks their length.
 */
class DSString {
private:
    char* data;     // Dynamically allocated character array
    int length;     // Length of the string (excluding null terminator)

public:
    /**
     * Default constructor
     * Creates an empty string with just a null terminator
     */
    DSString();

    /**
     * Constructor from C-string
     * @param str C-style string to copy
     */
    DSString(const char* str);

    /**
     * Copy constructor
     * Creates a deep copy of another DSString
     * @param other DSString to copy
     */
    DSString(const DSString& other);

    /**
     * Destructor
     * Properly deallocates all dynamic memory
     */
    ~DSString();

    /**
     * Assignment operator
     * Creates a deep copy of the right-hand side string
     * @param other DSString to copy
     * @return Reference to this object after assignment
     */
    DSString& operator=(const DSString& other);

    /**
     * Addition operator (concatenation)
     * @param other DSString to append to this string
     * @return New DSString with concatenated result
     */
    DSString operator+(const DSString& other) const;

    /**
     * Equality operator
     * @param other DSString to compare with
     * @return true if strings are equal, false otherwise
     */
    bool operator==(const DSString& other) const;

    /**
     * Less than operator for string comparison
     * @param other DSString to compare with
     * @return true if this string is lexicographically less than other
     */
    bool operator<(const DSString& other) const;

    /**
     * Greater than operator for string comparison
     * @param other DSString to compare with
     * @return true if this string is lexicographically greater than other
     */
    bool operator>(const DSString& other) const;

    /**
     * Array subscript operator
     * @param index Position of character to access
     * @return Reference to character at specified position
     * @note Does not perform bounds checking
     */
    char& operator[](int index);

    /**
     * Const array subscript operator
     * @param index Position of character to access
     * @return Character at specified position (const version)
     * @note Does not perform bounds checking
     */
    const char& operator[](int index) const;

    /**
     * Returns the length of the string
     * @return Number of characters in the string (excluding null terminator)
     */
    int size() const;

    /**
     * Returns a C-style string representation
     * @return Pointer to internal null-terminated char array
     * @note Caller should not modify or free the returned pointer
     */
    const char* c_str() const;

    /**
     * Returns a substring of this string
     * @param start Starting position (0-based index)
     * @param numChars Number of characters to include in substring
     * @return New DSString containing the specified substring
     */
    DSString substring(int start, int numChars) const;

    /**
     * Converts string to lowercase
     * @return New DSString with all characters converted to lowercase
     */
    DSString toLowerCase() const;

    /**
     * Stream insertion operator
     * @param os Output stream
     * @param str DSString to output
     * @return Reference to the output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const DSString& str);
};

#endif // DSSTRING_H
