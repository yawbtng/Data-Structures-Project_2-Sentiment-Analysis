/**
 * DSStringTest.cpp
 * 
 * A simple test program for the DSString class.
 * Tests basic functionality such as constructors, operators, and utility methods.
 */

#include "../include/DSString.h"
#include <iostream>
#include <cassert>

// Helper function to check if an assertion passed
void testPassed(const char* testName) {
    std::cout << "✓ " << testName << " passed" << std::endl;
}

int main() {
    std::cout << "Running DSString tests..." << std::endl;
    
    // Test 1: Default constructor
    {
        DSString s;
        assert(s.size() == 0);
        assert(s.c_str()[0] == '\0');
        testPassed("Default constructor");
    }
    
    // Test 2: Constructor from C-string
    {
        DSString s("hello");
        assert(s.size() == 5);
        assert(s[0] == 'h');
        assert(s[4] == 'o');
        testPassed("C-string constructor");
    }
    
    // Test 3: Copy constructor
    {
        DSString s1("hello");
        DSString s2(s1);
        assert(s2.size() == 5);
        assert(s2[0] == 'h');
        // Verify deep copy by modifying s1 and checking s2
        s1[0] = 'j';
        assert(s2[0] == 'h'); // s2 should be unchanged
        testPassed("Copy constructor");
    }
    
    // Test 4: Assignment operator
    {
        DSString s1("hello");
        DSString s2;
        s2 = s1;
        assert(s2.size() == 5);
        assert(s2[0] == 'h');
        // Verify deep copy
        s1[0] = 'j';
        assert(s2[0] == 'h'); // s2 should be unchanged
        testPassed("Assignment operator");
    }
    
    // Test 5: Addition (concatenation)
    {
        DSString s1("hello");
        DSString s2(" world");
        DSString s3 = s1 + s2;
        assert(s3.size() == 11);
        assert(s3[5] == ' ');
        assert(s3[10] == 'd');
        testPassed("Addition operator");
    }
    
    // Test 6: Equality operator
    {
        DSString s1("hello");
        DSString s2("hello");
        DSString s3("world");
        assert(s1 == s2);
        assert(!(s1 == s3));
        testPassed("Equality operator");
    }
    
    // Test 7: Less than operator
    {
        DSString s1("apple");
        DSString s2("banana");
        assert(s1 < s2);
        assert(!(s2 < s1));
        testPassed("Less than operator");
    }
    
    // Test 8: Greater than operator
    {
        DSString s1("zebra");
        DSString s2("apple");
        assert(s1 > s2);
        assert(!(s2 > s1));
        testPassed("Greater than operator");
    }
    
    // Test 9: Substring
    {
        DSString s("hello world");
        DSString sub = s.substring(6, 5);
        assert(sub.size() == 5);
        assert(sub == DSString("world"));
        testPassed("Substring method");
    }
    
    // Test 10: toLowerCase
    {
        DSString s("Hello WORLD!");
        DSString lower = s.toLowerCase();
        assert(lower == DSString("hello world!"));
        testPassed("toLowerCase method");
    }
    
    // Test 11: Edge case - Empty string operations
    {
        DSString empty;
        DSString s("test");
        DSString concat = empty + s;
        assert(concat == s);
        assert(empty.size() == 0);
        testPassed("Empty string operations");
    }
    
    // Test 12: Edge case - Self assignment
    {
        DSString s("test");
        s = s; // Self-assignment
        assert(s == DSString("test"));
        testPassed("Self assignment");
    }
    
    std::cout << "\nAll DSString tests passed successfully!" << std::endl;
    return 0;
} 