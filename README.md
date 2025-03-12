# Sentiment Analysis Engine

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Natural Language Processing](https://img.shields.io/badge/NLP-Sentiment%20Analysis-green)
![Data Structures](https://img.shields.io/badge/Data%20Structures-Custom%20Implementation-orange)
![Memory Management](https://img.shields.io/badge/Memory-Dynamic%20Allocation-red)
![Machine Learning](https://img.shields.io/badge/ML-Lexicon%20Based-purple)

## Project Overview

This sentiment analysis engine is a robust C++ application capable of classifying tweet sentiment as either positive or negative with high accuracy. The project demonstrates advanced C++ programming skills, including custom data structure implementation, dynamic memory management, and natural language processing techniques.

At its core, this is a **basic machine learning implementation** using a lexicon-based approach to sentiment classification, demonstrating fundamental ML concepts without relying on external libraries.

### Key Technical Features

- **Custom String Class Implementation**: Developed a bespoke `DSString` class with dynamic memory allocation, demonstrating deep understanding of memory management in C++.
- **Machine Learning from Scratch**: Implemented a lexicon-based classifier using a bag-of-words model and frequency analysis, similar to simplified Naive Bayes.
- **Natural Language Processing**: Engineered a text processing pipeline including tokenization, normalization, and feature extraction.
- **Rule of Three Implementation**: Applied professional C++ practices with proper copy constructors, assignment operators, and destructors.
- **STL Container Usage**: Leveraged C++ Standard Template Library containers to optimize data management and algorithm efficiency.
- **Algorithmic Efficiency**: Optimized for performance with complexity considerations factored into design decisions.

## Technical Architecture

### Core Components

1. **DSString Class**
   - Custom string implementation with dynamic memory management
   - Complete operator overloading (`=`, `+`, `==`, `<`, `>`, `[]`)
   - Memory-safe implementation following the Rule of Three
   - Efficient string manipulation methods without using standard `<string>` library

2. **SentimentClassifier**
   - Training algorithm that builds a statistical model from labeled data
   - Prediction system that evaluates new tweets based on training data
   - Evaluation component that calculates accuracy metrics
   - Performance analysis and misclassification reporting

3. **Tweet Processing Pipeline**
   - Tokenization engine that splits tweets into meaningful units
   - Text normalization techniques (lowercase conversion)
   - Feature extraction methodology
   - Statistical scoring algorithm

## Machine Learning Approach

This project implements a supervised machine learning approach with the following characteristics:

1. **Lexicon-Based Classification**:
   - Words are tracked along with their frequencies in positive and negative contexts
   - A sentiment score is calculated based on these frequencies for new texts
   - Simple yet effective for sentiment analysis tasks

2. **Bag-of-Words Representation**:
   - Words are treated as independent features without considering order or context
   - Feature extraction based on individual word occurrences
   - Simple vectorization approach that works well for sentiment analysis

3. **Statistical Model Training**:
   - Training phase builds word-sentiment associations from labeled data
   - Prediction phase applies these associations to classify new texts
   - Evaluation phase measures model accuracy against ground truth

4. **Supervised Learning Process**:
   - Model learns from labeled training data (tweets with known sentiments)
   - Applies learned patterns to make predictions on test data
   - Performance is measured against known ground truth

## Implementation Details

### Data Structures

The project utilizes several sophisticated data structures:

- **Map of word frequencies**: `std::map<DSString, std::pair<int, int>>` storing positive and negative counts for each word
- **Map of predictions**: `std::map<DSString, int>` storing predicted sentiments for tweet IDs
- **Vector of tokens**: `std::vector<DSString>` for storing tokenized words from tweets
- **Custom string class**: `DSString` for memory-efficient string operations

### Algorithms

1. **Training Phase**
   - Parses CSV format training data
   - Tokenizes text into individual words/features
   - Builds frequency distributions for positive and negative sentiments
   - Creates a statistical model balancing word frequencies and sentiment correlations

2. **Classification Phase**
   - Applies the trained model to new, unlabeled data
   - Calculates sentiment scores based on feature weights
   - Makes binary classification decisions (positive/negative)
   - Outputs predictions in standardized format

3. **Evaluation Metrics**
   - Calculates classification accuracy to 3 decimal places
   - Analyzes failure patterns for model improvement
   - Generates detailed misclassification reports

## Performance & Efficiency

- **Time Complexity**: O(N×M) where N is the number of tweets and M is the average number of words per tweet
- **Space Complexity**: O(V) where V is the vocabulary size (unique words in the corpus)
- **Memory Management**: Zero memory leaks with complete RAII-compliant design
- **Classification Accuracy**: Achieves approximately 64% accuracy on test datasets

## Technical Challenges Overcome

1. **Custom Memory Management**
   - Implemented dynamic resizing of internal character arrays
   - Ensured proper deep copying of string data
   - Prevented memory leaks in all edge cases
   - Resolved constructor issues with single-character string creation

2. **Tokenization Implementation**
   - Manually implemented character-by-character tokenization without relying on standard library functions
   - Handled special characters and punctuation in tweets
   - Managed text normalization through lowercase conversion
   - Created efficient delimiter-based word boundary detection

3. **CSV Parsing Complexities**
   - Implemented robust CSV parsing without external libraries
   - Handled quoted fields containing commas
   - Managed different CSV formats between training and test files
   - Resolved field extraction issues with proper index mapping

4. **File Format Inconsistencies**
   - Fixed critical issue with ground truth file format interpretation
   - Resolved column order mismatches between prediction and ground truth files
   - Implemented proper header line skipping for all file types
   - Added error handling for division by zero in accuracy calculation

5. **Algorithmic Efficiency**
   - Balanced training time against prediction accuracy
   - Optimized data structures for memory efficiency
   - Developed a scoring mechanism that maximizes correct classifications

## Command Line Interface

The application features a professional command-line interface:

```
./sentiment <training_data.csv> <test_data.csv> <test_sentiment.csv> <results_file.csv> <accuracy_file.txt>
```

### Input Files
- **Training Data**: CSV with format `sentiment,id,date,query,user,text`
- **Test Data**: CSV with format `id,date,query,user,text`
- **Test Sentiment Truth**: CSV with format `sentiment,id`

### Output Files
- **Results**: CSV with format `predicted_sentiment,id`
- **Accuracy Report**: Text file with overall accuracy and misclassification details

## Development Practices

- **Version Control**: Systematic Git usage with meaningful commit messages
- **Code Documentation**: Comprehensive inline documentation explaining algorithmic decisions
- **Testing Methodology**: Rigorous test cases covering edge conditions
- **Code Structure**: Clean separation of concerns with modular design patterns
- **Debugging Process**: Systematic issue identification and resolution

## Skills Demonstrated

- Advanced C++ programming
- Custom data structure implementation
- Natural language processing
- Machine learning algorithm design
- Memory management
- File I/O and parsing
- Command-line application development
- Software architecture design
- Debugging and problem-solving

## Future Enhancements

- Multi-class sentiment analysis (beyond binary classification)
- Performance optimizations for larger datasets
- Additional feature extraction techniques (n-grams, TF-IDF)
- Incorporation of negation handling ("not good" is negative)
- Consideration of word position and context
- Parallel processing for training phase

---

*This project was developed as part of CS 5393: Data Structures in C++, showcasing real-world application of advanced data structures and algorithms with machine learning concepts.* 