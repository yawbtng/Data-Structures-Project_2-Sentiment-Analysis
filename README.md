# Sentiment Analysis Engine

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Natural Language Processing](https://img.shields.io/badge/NLP-Sentiment%20Analysis-green)
![Data Structures](https://img.shields.io/badge/Data%20Structures-Custom%20Implementation-orange)
![Memory Management](https://img.shields.io/badge/Memory-Dynamic%20Allocation-red)

## Project Overview

This sentiment analysis engine is a robust C++ application capable of classifying tweet sentiment as either positive or negative with high accuracy. The project demonstrates advanced C++ programming skills, including custom data structure implementation, dynamic memory management, and natural language processing techniques.

### Key Technical Features

- **Custom String Class Implementation**: Developed a bespoke `DSString` class with dynamic memory allocation, demonstrating deep understanding of memory management in C++.
- **Natural Language Processing**: Engineered a machine learning classifier from scratch, without relying on external libraries.
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
   - Text normalization techniques
   - Feature extraction methodology
   - Statistical scoring algorithm

## Implementation Details

### Data Structures

The project utilizes several sophisticated data structures:

- **Custom hash maps** for O(1) word lookup performance
- **Dynamic arrays** for efficient memory usage
- **STL containers** for complex data relationships

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

## Technical Challenges Overcome

1. **Custom Memory Management**
   - Implemented dynamic resizing of internal character arrays
   - Ensured proper deep copying of string data
   - Prevented memory leaks in all edge cases

2. **Tokenization Edge Cases**
   - Handled special characters and punctuation in tweets
   - Managed URL structures and hashtags
   - Addressed case sensitivity challenges

3. **Algorithmic Efficiency**
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
- **Test Sentiment Truth**: CSV with format `id,sentiment`

### Output Files
- **Results**: CSV with format `predicted_sentiment,id`
- **Accuracy Report**: Text file with overall accuracy and misclassification details

## Development Practices

- **Version Control**: Systematic Git usage with meaningful commit messages
- **Code Documentation**: Comprehensive inline documentation explaining algorithmic decisions
- **Testing Methodology**: Rigorous test cases covering edge conditions
- **Code Structure**: Clean separation of concerns with modular design patterns

## Skills Demonstrated

- Advanced C++ programming
- Custom data structure implementation
- Natural language processing
- Algorithm design and analysis
- Memory management
- File I/O and parsing
- Command-line application development
- Software architecture design

## Future Enhancements

- Multi-class sentiment analysis (beyond binary classification)
- Performance optimizations for larger datasets
- Additional feature extraction techniques
- Parallel processing for training phase

---

*This project was developed as part of CS 5393: Data Structures in C++, showcasing real-world application of advanced data structures and algorithms.* 