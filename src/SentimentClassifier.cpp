/**
 * SentimentClassifier.cpp
 * 
 * Implementation of the SentimentClassifier class for tweet sentiment analysis.
 * This file contains the code for training the classifier, making predictions,
 * and evaluating those predictions against ground truth.
 */

#include "../include/SentimentClassifier.h"
#include <iostream>
#include <iomanip> // For formatting accuracy output

/**
 * Default constructor
 * Initializes counters and data structures to their default values
 */
SentimentClassifier::SentimentClassifier() {
    // Initialize counters
    totalPositiveTweets = 0;
    totalNegativeTweets = 0;
    
    // Other member variables (maps) are automatically initialized by their constructors
}

/**
 * Tokenizes a tweet text into individual words
 * 
 * Approach:
 * 1. Convert the tweet to lowercase
 * 2. Split by spaces and punctuation
 * 3. Filter out empty tokens
 * 
 * Note: This implementation manually tokenizes by iterating through the text
 * character by character, building words until a delimiter is encountered.
 * 
 * @param tweetText The text of the tweet to tokenize
 * @return Vector of DSString objects representing individual words
 */
std::vector<DSString> SentimentClassifier::tokenizeTweet(const DSString& tweetText) const {
    std::vector<DSString> tokens;
    
    // Convert tweet to lowercase for case-insensitive analysis
    DSString lowerText = tweetText.toLowerCase();
    
    // Current word being built
    DSString currentWord;
    
    // Characters that delimit words (space, punctuation)
    const char* delimiters = " ,.!?;:\"'()[]{}@#$%^&*-_=+<>/\\|~`";
    
    // Process each character
    for (int i = 0; i < lowerText.size(); i++) {
        char c = lowerText[i];
        
        // Check if current character is a delimiter
        bool isDelimiter = false;
        for (int j = 0; delimiters[j] != '\0'; j++) {
            if (c == delimiters[j]) {
                isDelimiter = true;
                break;
            }
        }
        
        if (isDelimiter) {
            // If we have a word, add it to tokens
            if (currentWord.size() > 0) {
                tokens.push_back(currentWord);
                currentWord = DSString(); // Reset current word
            }
        } else {
            // Add character to current word
            // Create a temporary null-terminated C-string with just this character
            char temp[2] = {c, '\0'};
            currentWord = currentWord + DSString(temp);
        }
    }
    
    // Don't forget last word if not followed by delimiter
    if (currentWord.size() > 0) {
        tokens.push_back(currentWord);
    }
    
    return tokens;
}

/**
 * Parses a CSV line into its components
 * 
 * Format for training data: <sentiment>,<tweetID>,<date>,<query>,<user>,<text>
 * Format for test data: <tweetID>,<date>,<query>,<user>,<text>
 * 
 * @param line A line from the CSV file
 * @param hasSentiment Whether the line contains a sentiment value (true for training, false for test)
 * @return Vector of DSString objects for each column in the CSV
 */
std::vector<DSString> SentimentClassifier::parseCSVLine(const DSString& line, bool hasSentiment) const {
    std::vector<DSString> fields;
    
    // Current field being built
    DSString currentField;
    
    bool inQuotes = false;
    
    // Process each character
    for (int i = 0; i < line.size(); i++) {
        char c = line[i];
        
        // Handle quotes (text field can contain commas within quotes)
        if (c == '\"') {
            inQuotes = !inQuotes;
            continue; // Skip the quote character
        }
        
        // If comma and not in quotes, we've reached a field boundary
        if (c == ',' && !inQuotes) {
            fields.push_back(currentField);
            currentField = DSString(); // Reset current field
        } else {
            // Add character to current field
            // Create a temporary null-terminated C-string with just this character
            char temp[2] = {c, '\0'};
            currentField = currentField + DSString(temp);
        }
    }
    
    // Add the last field
    fields.push_back(currentField);
    
    return fields;
}

/**
 * Calculates a sentiment score for a tweet based on the training data
 * For each word, adds (positive count - negative count) to the score
 * 
 * @param tokens Vector of words from a tokenized tweet
 * @return The sentiment score (positive value suggests positive sentiment)
 */
int SentimentClassifier::calculateSentimentScore(const std::vector<DSString>& tokens) const {
    int score = 0;
    
    // For each word in the tweet
    for (const DSString& token : tokens) {
        // Look up the word in our frequency map
        auto it = wordSentimentCounts.find(token);
        
        if (it != wordSentimentCounts.end()) {
            // Add the difference between positive and negative frequencies to the score
            score += (it->second.first - it->second.second);
        }
    }
    
    return score;
}

/**
 * Trains the sentiment classifier on labeled data
 * 
 * @param trainingDataFile Path to the training CSV file
 * @return True if training was successful, false otherwise
 */
bool SentimentClassifier::train(const DSString& trainingDataFile) {
    // Open the training file
    std::ifstream inFile(trainingDataFile.c_str());
    if (!inFile.is_open()) {
        std::cerr << "Error opening training file: " << trainingDataFile.c_str() << std::endl;
        return false;
    }
    
    // Read the file line by line
    std::string line;
    bool isFirstLine = true; // Skip header line
    
    while (std::getline(inFile, line)) {
        // Skip the header line
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        
        // Convert std::string to DSString
        DSString dsLine(line.c_str());
        
        // Parse the CSV line (with sentiment)
        std::vector<DSString> fields = parseCSVLine(dsLine, true);
        
        // Ensure we have enough fields (at least sentiment and text)
        if (fields.size() < 6) {
            continue; // Skip malformed lines
        }
        
        // Extract sentiment and text
        DSString sentimentStr = fields[0];
        DSString tweetID = fields[1];
        DSString tweetText = fields[5]; // The text is the 6th field (index 5)
        
        // Convert sentiment to integer (0 for negative, 4 for positive)
        int sentiment = 0;
        if (sentimentStr[0] == '4') {
            sentiment = 4;
            totalPositiveTweets++;
        } else {
            totalNegativeTweets++;
        }
        
        // Tokenize the tweet
        std::vector<DSString> tokens = tokenizeTweet(tweetText);
        
        // Update word frequency counts based on sentiment
        for (const DSString& token : tokens) {
            // Skip very short words (likely not meaningful)
            if (token.size() <= 1) {
                continue;
            }
            
            // Get the current counts for this word
            auto& counts = wordSentimentCounts[token];
            
            // Update positive or negative count
            if (sentiment == 4) {
                counts.first++; // Increment positive count
            } else {
                counts.second++; // Increment negative count
            }
        }
    }
    
    inFile.close();
    
    // Output some stats about the training
    std::cout << "Training complete. Processed " 
              << (totalPositiveTweets + totalNegativeTweets) << " tweets ("
              << totalPositiveTweets << " positive, "
              << totalNegativeTweets << " negative)." << std::endl;
    std::cout << "Vocabulary size: " << wordSentimentCounts.size() << " words." << std::endl;
    
    return true;
}

/**
 * Predicts sentiments for tweets in test data
 * 
 * @param testDataFile Path to the test CSV file
 * @param predictionsOutputFile Path where prediction results will be written
 * @return True if prediction was successful, false otherwise
 */
bool SentimentClassifier::predict(const DSString& testDataFile, const DSString& predictionsOutputFile) {
    // Open the test file
    std::ifstream inFile(testDataFile.c_str());
    if (!inFile.is_open()) {
        std::cerr << "Error opening test file: " << testDataFile.c_str() << std::endl;
        return false;
    }
    
    // Open the output file
    std::ofstream outFile(predictionsOutputFile.c_str());
    if (!outFile.is_open()) {
        std::cerr << "Error opening predictions output file: " << predictionsOutputFile.c_str() << std::endl;
        inFile.close();
        return false;
    }
    
    // Read the file line by line
    std::string line;
    bool isFirstLine = true; // Skip header line
    
    while (std::getline(inFile, line)) {
        // Skip the header line
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        
        // Convert std::string to DSString
        DSString dsLine(line.c_str());
        
        // Parse the CSV line (without sentiment)
        std::vector<DSString> fields = parseCSVLine(dsLine, false);
        
        // Ensure we have enough fields (at least ID and text)
        if (fields.size() < 5) {
            continue; // Skip malformed lines
        }
        
        // Extract tweet ID and text
        DSString tweetID = fields[0]; // ID is the first field
        DSString tweetText = fields[4]; // Text is the 5th field (index 4)
        
        // Tokenize the tweet
        std::vector<DSString> tokens = tokenizeTweet(tweetText);
        
        // Calculate sentiment score
        int score = calculateSentimentScore(tokens);
        
        // Determine sentiment (4 for positive, 0 for negative)
        int predictedSentiment = (score > 0) ? 4 : 0;
        
        // Store the prediction
        predictions[tweetID] = predictedSentiment;
        
        // Write prediction to output file: <sentiment>,<tweetID>
        outFile << predictedSentiment << "," << tweetID << std::endl;
    }
    
    inFile.close();
    outFile.close();
    
    std::cout << "Prediction complete. Made predictions for " << predictions.size() << " tweets." << std::endl;
    
    return true;
}

/**
 * Evaluates prediction accuracy against ground truth
 * 
 * @param groundTruthFile Path to the file with actual sentiments
 * @param accuracyOutputFile Path where accuracy results will be written
 * @return True if evaluation was successful, false otherwise
 */
bool SentimentClassifier::evaluatePredictions(const DSString& groundTruthFile, const DSString& accuracyOutputFile) {
    // Open the ground truth file
    std::ifstream truthFile(groundTruthFile.c_str());
    if (!truthFile.is_open()) {
        std::cerr << "Error opening ground truth file: " << groundTruthFile.c_str() << std::endl;
        return false;
    }
    
    // Open the accuracy output file
    std::ofstream accFile(accuracyOutputFile.c_str());
    if (!accFile.is_open()) {
        std::cerr << "Error opening accuracy output file: " << accuracyOutputFile.c_str() << std::endl;
        truthFile.close();
        return false;
    }
    
    // Variables to track correct and total predictions
    int correctPredictions = 0;
    int totalPredictions = 0;
    
    // Compare predictions to actual sentiments
    std::vector<std::tuple<int, int, DSString>> misclassifications; // (predicted, actual, tweetID)
    
    // Read the ground truth file line by line
    std::string line;
    bool isFirstLine = true; // Skip header line
    
    while (std::getline(truthFile, line)) {
        // Skip the header line
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        
        // Convert std::string to DSString
        DSString dsLine(line.c_str());
        
        // Parse the CSV line
        std::vector<DSString> fields = parseCSVLine(dsLine, false);
        
        // Ensure we have enough fields (ID and sentiment)
        if (fields.size() < 2) {
            continue; // Skip malformed lines
        }
        
        // Extract tweet ID and actual sentiment
        DSString tweetID = fields[1]; // The ID is in the second column (index 1)
        int actualSentiment = (fields[0][0] == '4') ? 4 : 0; // The sentiment is in the first column (index 0)
        
        // Lookup our prediction
        auto it = predictions.find(tweetID);
        if (it != predictions.end()) {
            int predictedSentiment = it->second;
            
            // Increment total count
            totalPredictions++;
            
            // Check if prediction matches actual sentiment
            if (predictedSentiment == actualSentiment) {
                correctPredictions++;
            } else {
                // Store misclassification
                misclassifications.push_back(std::make_tuple(predictedSentiment, actualSentiment, tweetID));
            }
        }
    }
    
    // Calculate accuracy
    double accuracy = 0.0;
    if (totalPredictions > 0) {
        accuracy = static_cast<double>(correctPredictions) / totalPredictions;
    } else {
        std::cerr << "Warning: No predictions were matched with ground truth! Check that your files contain matching tweet IDs." << std::endl;
    }
    
    // Write accuracy to the first line (3 decimal places)
    accFile << std::fixed << std::setprecision(3) << accuracy << std::endl;
    
    // Write misclassifications
    for (const auto& mis : misclassifications) {
        accFile << std::get<0>(mis) << "," << std::get<1>(mis) << "," << std::get<2>(mis) << std::endl;
    }
    
    truthFile.close();
    accFile.close();
    
    std::cout << "Evaluation complete. Accuracy: " << (accuracy * 100.0) << "%" << std::endl;
    std::cout << correctPredictions << " correct predictions out of " << totalPredictions << std::endl;
    std::cout << misclassifications.size() << " misclassifications." << std::endl;
    
    return true;
}
