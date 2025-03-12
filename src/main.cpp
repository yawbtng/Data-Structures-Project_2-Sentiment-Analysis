/**
 * main.cpp
 * 
 * Entry point for the sentiment analysis program.
 * Parses command-line arguments and orchestrates the training,
 * prediction, and evaluation of the sentiment classifier.
 */

#include "../include/DSString.h"
#include "../include/SentimentClassifier.h"
#include <iostream>

/**
 * Display usage information when incorrect arguments are provided
 */
void displayUsage() {
    std::cout << "Usage: ./sentiment <training_file> <test_file> <test_sentiment_file> <results_file> <accuracy_file>" << std::endl;
    std::cout << std::endl;
    std::cout << "Arguments:" << std::endl;
    std::cout << "  <training_file>       - CSV file with labeled training data" << std::endl;
    std::cout << "  <test_file>           - CSV file with unlabeled test data" << std::endl;
    std::cout << "  <test_sentiment_file> - CSV file with actual sentiments for test data" << std::endl;
    std::cout << "  <results_file>        - Output file for prediction results" << std::endl;
    std::cout << "  <accuracy_file>       - Output file for accuracy metrics" << std::endl;
    std::cout << std::endl;
    std::cout << "Example:" << std::endl;
    std::cout << "  ./sentiment data/train.csv data/test.csv data/test_sentiment.csv results.csv accuracy.txt" << std::endl;
}

int main(int argc, char** argv) {
    // Check if the correct number of arguments is provided
    if (argc != 6) {
        std::cerr << "Error: Incorrect number of arguments." << std::endl;
        displayUsage();
        return 1;
    }
    
    // Parse command-line arguments
    DSString trainingFile(argv[1]);
    DSString testFile(argv[2]);
    DSString testSentimentFile(argv[3]);
    DSString resultsFile(argv[4]);
    DSString accuracyFile(argv[5]);
    
    // Display the configuration
    std::cout << "Sentiment Analysis Configuration:" << std::endl;
    std::cout << "  Training File:       " << trainingFile << std::endl;
    std::cout << "  Test File:           " << testFile << std::endl;
    std::cout << "  Test Sentiment File: " << testSentimentFile << std::endl;
    std::cout << "  Results File:        " << resultsFile << std::endl;
    std::cout << "  Accuracy File:       " << accuracyFile << std::endl;
    std::cout << std::endl;
    
    // Create a sentiment classifier
    SentimentClassifier classifier;
    
    // Step 1: Train the classifier
    std::cout << "Training classifier..." << std::endl;
    if (!classifier.train(trainingFile)) {
        std::cerr << "Error: Failed to train the classifier." << std::endl;
        return 1;
    }
    
    // Step 2: Make predictions
    std::cout << "Making predictions..." << std::endl;
    if (!classifier.predict(testFile, resultsFile)) {
        std::cerr << "Error: Failed to make predictions." << std::endl;
        return 1;
    }
    
    // Step 3: Evaluate predictions
    std::cout << "Evaluating predictions..." << std::endl;
    if (!classifier.evaluatePredictions(testSentimentFile, accuracyFile)) {
        std::cerr << "Error: Failed to evaluate predictions." << std::endl;
        return 1;
    }
    
    std::cout << "Sentiment analysis complete." << std::endl;
    std::cout << "Results written to: " << resultsFile << std::endl;
    std::cout << "Accuracy metrics written to: " << accuracyFile << std::endl;
    
    return 0;
}
