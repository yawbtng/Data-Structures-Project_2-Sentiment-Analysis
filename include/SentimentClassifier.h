/**
 * SentimentClassifier.h
 * 
 * A classifier that analyzes the sentiment of tweets as either positive or negative.
 * Uses a frequency-based approach to determine if a tweet's sentiment is positive (4) or negative (0).
 * Implements training, prediction, and evaluation functionality using the custom DSString class.
 */

#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include "DSString.h"
#include <vector>
#include <map>
#include <fstream>
#include <utility> // for std::pair

/**
 * SentimentClassifier class - Analyzes sentiment of tweets using a basic word frequency model
 * 
 * This class reads training data to build a model of word frequencies associated with positive
 * and negative sentiments, then uses that model to predict sentiments of new tweets.
 * It also provides functionality to evaluate prediction accuracy against known ground truth.
 */
class SentimentClassifier {
private:
    /**
     * Data structure to store word frequency counts for positive and negative sentiments
     * Key: word (as DSString)
     * Value: pair of integers where:
     *   - first = count of occurrences in positive tweets
     *   - second = count of occurrences in negative tweets
     */
    std::map<DSString, std::pair<int, int>> wordSentimentCounts;
    
    /**
     * Store tweet IDs and their predicted sentiments
     * Key: tweet ID (as DSString)
     * Value: predicted sentiment (0 for negative, 4 for positive)
     */
    std::map<DSString, int> predictions;
    
    /**
     * Total number of positive and negative tweets in training data
     * Used for potential normalization/probability calculations
     */
    int totalPositiveTweets;
    int totalNegativeTweets;
    
    /**
     * Tokenizes a tweet text into individual words
     * Splits text by spaces and punctuation, converts to lowercase
     * 
     * @param tweetText The text of the tweet to tokenize
     * @return Vector of DSString objects representing individual words
     */
    std::vector<DSString> tokenizeTweet(const DSString& tweetText) const;
    
    /**
     * Calculates a sentiment score for a tweet based on the training data
     * If score is positive, the tweet is classified as positive (4)
     * If score is negative or zero, the tweet is classified as negative (0)
     * 
     * @param tokens Vector of words from a tokenized tweet
     * @return The sentiment score (positive value suggests positive sentiment)
     */
    int calculateSentimentScore(const std::vector<DSString>& tokens) const;
    
    /**
     * Parses a CSV line into its components
     * Handles the specific format of the training and testing data
     * 
     * @param line A line from the CSV file
     * @param hasHeader Whether the line contains a sentiment value
     * @return Vector of DSString objects for each column in the CSV
     */
    std::vector<DSString> parseCSVLine(const DSString& line, bool hasSentiment) const;

public:
    /**
     * Default constructor
     * Initializes counters and data structures
     */
    SentimentClassifier();
    
    /**
     * Trains the sentiment classifier on labeled data
     * 
     * Reads the training CSV file, processes each tweet:
     * 1. Extracts sentiment, tweet ID, and text
     * 2. Tokenizes the text into words
     * 3. Updates word frequency counts based on the tweet's sentiment
     * 
     * @param trainingDataFile Path to the training CSV file
     * @return True if training was successful, false otherwise
     */
    bool train(const DSString& trainingDataFile);
    
    /**
     * Predicts sentiments for tweets in test data
     * 
     * Reads the test CSV file (without sentiment labels), for each tweet:
     * 1. Extracts tweet ID and text
     * 2. Tokenizes the text into words
     * 3. Calculates sentiment score based on training data
     * 4. Stores the predicted sentiment
     * 5. Writes predictions to the output file in format: <sentiment>,<tweetID>
     * 
     * @param testDataFile Path to the test CSV file
     * @param predictionsOutputFile Path where prediction results will be written
     * @return True if prediction was successful, false otherwise
     */
    bool predict(const DSString& testDataFile, const DSString& predictionsOutputFile);
    
    /**
     * Evaluates prediction accuracy against ground truth
     * 
     * 1. Reads the ground truth sentiment file
     * 2. Compares predictions to actual sentiments
     * 3. Calculates accuracy (correct / total)
     * 4. Writes accuracy and misclassified tweets to the output file
     * 
     * Output format:
     * - First line: accuracy to 3 decimal places
     * - Remaining lines: <predicted>,<actual>,<tweetID> for misclassified tweets
     * 
     * @param groundTruthFile Path to the file with actual sentiments
     * @param accuracyOutputFile Path where accuracy results will be written
     * @return True if evaluation was successful, false otherwise
     */
    bool evaluatePredictions(const DSString& groundTruthFile, const DSString& accuracyOutputFile);
};

#endif // SENTIMENTCLASSIFIER_H
