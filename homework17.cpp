#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cmath>
#include <cassert>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <algorithm>

// Task 3
class InvalidDigitException : public std::exception {
private:
    char invalidChar;
    int base;

public:
    InvalidDigitException(char ch, int b) : invalidChar(ch), base(b) {}

    const char* what() const noexcept override {
        static std::string message;
        message = "Invalid digit '" + std::string(1, invalidChar) +
            "' for base " + std::to_string(base);
        return message.c_str();
    }
};

int charToDigit(char c, int base) {
    int digit;
    if (c >= '0' && c <= '9') {
        digit = c - '0';
    }
    else if (c >= 'A' && c <= 'F') {
        digit = c - 'A' + 10;
    }
    else if (c >= 'a' && c <= 'f') {
        digit = c - 'a' + 10;
    }
    else {
        throw InvalidDigitException(c, base);
    }

    assert(digit >= 0 && digit < base && "Digit out of range for given base");
    return digit;
}

int stringToNumber(const std::string& str, int base) {
    if (base < 2 || base > 16) {
        throw std::invalid_argument("Base must be between 2 and 16");
    }

    if (str.empty()) {
        throw std::invalid_argument("Empty string");
    }

    int result = 0;
    bool negative = false;
    size_t start = 0;

    if (str[0] == '-') {
        negative = true;
        start = 1;
    }

    for (size_t i = start; i < str.length(); ++i) {
        result = result * base + charToDigit(str[i], base);
    }

    return negative ? -result : result;
}

// Task 4
class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    double getReal() const { return real; }
    double getImag() const { return imag; }
    double modulus() const { return std::sqrt(real * real + imag * imag); }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) os << "+";
        os << c.imag << "i";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Complex& c) {
        char plus, i;
        is >> c.real >> plus >> c.imag >> i;
        if (plus == '-' || (plus != '+' && is.fail())) {
            is.clear();
            is >> c.real >> c.imag >> i;
        }
        return is;
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
            real * other.imag + imag * other.real);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            throw std::invalid_argument("Division by zero complex number");
        }
        return Complex((real * other.real + imag * other.imag) / denominator,
            (imag * other.real - real * other.imag) / denominator);
    }

    Complex power(int n) const {
        if (n == 0) return Complex(1, 0);

        Complex result(1, 0);
        Complex base = *this;
        int exp = std::abs(n);

        while (exp > 0) {
            if (exp % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            exp /= 2;
        }

        return n > 0 ? result : Complex(1, 0) / result;
    }
};

Complex arctan(const Complex& z, double epsilon = 1e-10) {
    assert(z.modulus() < 1.0 && "|z| must be less than 1 for arctan series convergence");

    if (z.modulus() >= 1.0) {
        throw std::invalid_argument("|z| must be less than 1 for arctan series");
    }

    Complex result(0, 0);
    Complex term = z;
    int n = 0;

    try {
        while (term.modulus() >= epsilon) {
            double sign = (n % 2 == 0) ? 1.0 : -1.0;
            double denominator = 2 * n + 1;

            Complex current = term * Complex(sign / denominator, 0);
            result = result + current;

            n++;
            term = term * z * z;

            if (n > 10000) {
                throw std::runtime_error("Series did not converge within reasonable iterations");
            }
        }
    }
    catch (const std::bad_alloc& e) {
        throw std::runtime_error("Memory allocation failed in arctan calculation");
    }

    return result;
}

// Task 5
class ThreeByteException : public std::exception {
public:
    const char* what() const noexcept override = 0;
};

class OverflowException : public ThreeByteException {
public:
    const char* what() const noexcept override {
        return "ThreeByteInteger overflow occurred";
    }
};

class DivisionByZeroException : public ThreeByteException {
public:
    const char* what() const noexcept override {
        return "ThreeByteInteger division by zero";
    }
};

class ThreeByteInteger {
private:
    int32_t value;

    static const int32_t MIN_VALUE = -8388608;
    static const int32_t MAX_VALUE = 8388607;

    void checkBounds(int32_t val) const {
        if (val < MIN_VALUE || val > MAX_VALUE) {
            throw OverflowException();
        }
    }

public:
    ThreeByteInteger(int32_t val = 0) {
        checkBounds(val);
        value = val;
    }

    int32_t getValue() const { return value; }

    friend std::ostream& operator<<(std::ostream& os, const ThreeByteInteger& num) {
        os << num.value;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, ThreeByteInteger& num) {
        int32_t val;
        is >> val;
        num.checkBounds(val);
        num.value = val;
        return is;
    }

    ThreeByteInteger operator+(const ThreeByteInteger& other) const {
        int64_t result = static_cast<int64_t>(value) + static_cast<int64_t>(other.value);
        if (result < MIN_VALUE || result > MAX_VALUE) {
            throw OverflowException();
        }
        return ThreeByteInteger(static_cast<int32_t>(result));
    }

    ThreeByteInteger operator-(const ThreeByteInteger& other) const {
        int64_t result = static_cast<int64_t>(value) - static_cast<int64_t>(other.value);
        if (result < MIN_VALUE || result > MAX_VALUE) {
            throw OverflowException();
        }
        return ThreeByteInteger(static_cast<int32_t>(result));
    }

    ThreeByteInteger operator*(const ThreeByteInteger& other) const {
        int64_t result = static_cast<int64_t>(value) * static_cast<int64_t>(other.value);
        if (result < MIN_VALUE || result > MAX_VALUE) {
            throw OverflowException();
        }
        return ThreeByteInteger(static_cast<int32_t>(result));
    }

    ThreeByteInteger operator/(const ThreeByteInteger& other) const {
        if (other.value == 0) {
            throw DivisionByZeroException();
        }
        int32_t result = value / other.value;
        checkBounds(result);
        return ThreeByteInteger(result);
    }

    ThreeByteInteger power(unsigned int n) const {
        if (n == 0) return ThreeByteInteger(1);

        ThreeByteInteger result(1);
        ThreeByteInteger base = *this;

        while (n > 0) {
            if (n % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            n /= 2;
        }

        return result;
    }
};

ThreeByteInteger sumThreeByteArray(const std::vector<ThreeByteInteger>& arr) {
    ThreeByteInteger sum(0);
    for (const auto& num : arr) {
        sum = sum + num;
    }
    return sum;
}

// Task 6
class BinaryFileException : public std::exception {
public:
    const char* what() const noexcept override = 0;
};

class FileCreationException : public BinaryFileException {
public:
    const char* what() const noexcept override {
        return "Failed to create binary file";
    }
};

class FileReadException : public BinaryFileException {
public:
    const char* what() const noexcept override {
        return "Failed to read from binary file";
    }
};

class BinaryInvalidIndexException : public BinaryFileException {
public:
    const char* what() const noexcept override {
        return "Invalid index for binary file operation";
    }
};

class BinaryFileHandler {
private:
    std::string filename;
    int numberCount;

    void updateCount() {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            numberCount = 0;
            return;
        }
        file.seekg(0, std::ios::end);
        numberCount = file.tellg() / sizeof(int);
        file.close();
    }

public:
    BinaryFileHandler(const std::string& name) : filename(name), numberCount(0) {
        updateCount();
    }

    void writeFromConsole(int count) {
        std::ofstream file(filename, std::ios::binary | std::ios::app);
        if (!file) {
            throw FileCreationException();
        }

        std::cout << "Enter " << count << " integers:\n";
        for (int i = 0; i < count; ++i) {
            int num;
            std::cin >> num;
            file.write(reinterpret_cast<const char*>(&num), sizeof(int));
        }
        file.close();
        updateCount();
    }

    void createFromArray(const std::vector<int>& arr) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            throw FileCreationException();
        }

        for (int num : arr) {
            file.write(reinterpret_cast<const char*>(&num), sizeof(int));
        }
        file.close();
        updateCount();
    }

    void displayContents() const {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            throw FileReadException();
        }

        std::cout << "File contents: ";
        int num;
        while (file.read(reinterpret_cast<char*>(&num), sizeof(int))) {
            std::cout << num << " ";
        }
        std::cout << "\n";
        file.close();
    }

    int getNumber(int index) const {
        if (index < 0 || index >= numberCount) {
            throw BinaryInvalidIndexException();
        }

        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            throw FileReadException();
        }

        file.seekg(index * sizeof(int));
        int num;
        file.read(reinterpret_cast<char*>(&num), sizeof(int));
        file.close();

        return num;
    }

    void appendArray(const std::vector<int>& arr) {
        std::ofstream file(filename, std::ios::binary | std::ios::app);
        if (!file) {
            throw FileCreationException();
        }

        for (int num : arr) {
            file.write(reinterpret_cast<const char*>(&num), sizeof(int));
        }
        file.close();
        updateCount();
    }

    void removeNumber(int index) {
        if (index < 0 || index >= numberCount) {
            throw BinaryInvalidIndexException();
        }

        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            throw FileReadException();
        }

        std::vector<int> numbers;
        int num;
        while (inFile.read(reinterpret_cast<char*>(&num), sizeof(int))) {
            numbers.push_back(num);
        }
        inFile.close();

        numbers.erase(numbers.begin() + index);

        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            throw FileCreationException();
        }

        for (int n : numbers) {
            outFile.write(reinterpret_cast<const char*>(&n), sizeof(int));
        }
        outFile.close();
        updateCount();
    }

    int getNumberCount() const { return numberCount; }
    std::string getFilename() const { return filename; }
};

// Task 7
class TextFileException : public std::exception {
public:
    const char* what() const noexcept override = 0;
};

class TextFileCreationException : public TextFileException {
public:
    const char* what() const noexcept override {
        return "Failed to create text file";
    }
};

class TextFileReadException : public TextFileException {
public:
    const char* what() const noexcept override {
        return "Failed to read from text file";
    }
};

class InvalidNumberException : public TextFileException {
public:
    const char* what() const noexcept override {
        return "Invalid number format in text file";
    }
};

class TextFileHandler {
private:
    std::string filename;
    int numberCount;
    int lineCount;

    void updateStats() {
        std::ifstream file(filename);
        if (!file) {
            numberCount = 0;
            lineCount = 0;
            return;
        }

        numberCount = 0;
        lineCount = 0;
        std::string line;

        while (std::getline(file, line)) {
            lineCount++;
            std::istringstream iss(line);
            double num;
            while (iss >> num) {
                numberCount++;
            }
        }
        file.close();
    }

public:
    TextFileHandler(const std::string& name) : filename(name), numberCount(0), lineCount(0) {
        updateStats();
    }

    void writeFromConsole() {
        std::ofstream file(filename, std::ios::app);
        if (!file) {
            throw TextFileCreationException();
        }

        std::string line;
        std::cout << "Enter numbers separated by spaces (empty line to finish):\n";
        std::cin.ignore();

        while (std::getline(std::cin, line) && !line.empty()) {
            file << line << "\n";
        }
        file.close();
        updateStats();
    }

    void createFrom2DArray(const std::vector<std::vector<double>>& arr) {
        std::ofstream file(filename);
        if (!file) {
            throw TextFileCreationException();
        }

        for (const auto& row : arr) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) file << " ";
            }
            file << "\n";
        }
        file.close();
        updateStats();
    }

    void displayContents() const {
        std::ifstream file(filename);
        if (!file) {
            throw TextFileReadException();
        }

        std::string line;
        std::cout << "File contents:\n";
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
        file.close();
    }

    double getNumber(int lineIndex, int numberIndex) const {
        std::ifstream file(filename);
        if (!file) {
            throw TextFileReadException();
        }

        std::string line;
        int currentLine = 0;

        while (std::getline(file, line)) {
            if (currentLine == lineIndex) {
                std::istringstream iss(line);
                double num;
                int currentNum = 0;

                while (iss >> num) {
                    if (currentNum == numberIndex) {
                        return num;
                    }
                    currentNum++;
                }
                throw InvalidNumberException();
            }
            currentLine++;
        }

        throw TextFileReadException();
    }

    void appendArray(const std::vector<double>& arr) {
        std::ofstream file(filename, std::ios::app);
        if (!file) {
            throw TextFileCreationException();
        }

        for (size_t i = 0; i < arr.size(); ++i) {
            file << arr[i];
            if (i < arr.size() - 1) file << " ";
        }
        file << "\n";
        file.close();
        updateStats();
    }

    void removeNumber(int lineIndex, int numberIndex) {
        std::ifstream inFile(filename);
        if (!inFile) {
            throw TextFileReadException();
        }

        std::vector<std::vector<double>> lines;
        std::string lineStr;

        while (std::getline(inFile, lineStr)) {
            std::vector<double> lineNumbers;
            std::istringstream iss(lineStr);
            double num;

            while (iss >> num) {
                lineNumbers.push_back(num);
            }
            lines.push_back(lineNumbers);
        }
        inFile.close();

        if (lineIndex < 0 || lineIndex >= lines.size() ||
            numberIndex < 0 || numberIndex >= lines[lineIndex].size()) {
            throw InvalidNumberException();
        }

        lines[lineIndex].erase(lines[lineIndex].begin() + numberIndex);

        std::ofstream outFile(filename);
        if (!outFile) {
            throw TextFileCreationException();
        }

        for (const auto& line : lines) {
            for (size_t i = 0; i < line.size(); ++i) {
                outFile << line[i];
                if (i < line.size() - 1) outFile << " ";
            }
            outFile << "\n";
        }
        outFile.close();
        updateStats();
    }

    int getNumberCount() const { return numberCount; }
    int getLineCount() const { return lineCount; }
    std::string getFilename() const { return filename; }
};

// Task 8
class PolynomialException : public std::exception {
public:
    const char* what() const noexcept override = 0;
};

class InvalidDegreeException : public PolynomialException {
public:
    const char* what() const noexcept override {
        return "Polynomial degree must be non-negative integer";
    }
};

class InvalidCoefficientException : public PolynomialException {
public:
    const char* what() const noexcept override {
        return "Polynomial coefficient must be a real number";
    }
};

class Polynomial {
private:
    int degree;
    std::vector<double> coefficients;

    void validate() const {
        if (degree < 0) {
            throw InvalidDegreeException();
        }
        if (coefficients.size() != degree + 1) {
            throw std::invalid_argument("Coefficients array size doesn't match degree");
        }
    }

public:
    Polynomial(int deg = 0) : degree(deg) {
        if (deg < 0) throw InvalidDegreeException();
        coefficients.resize(deg + 1, 0.0);
    }

    Polynomial(const std::vector<double>& coeffs) : degree(coeffs.size() - 1), coefficients(coeffs) {
        validate();
    }

    void inputFromConsole() {
        std::cout << "Enter degree: ";
        std::cin >> degree;
        if (degree < 0) throw InvalidDegreeException();

        coefficients.resize(degree + 1);
        std::cout << "Enter " << degree + 1 << " coefficients:\n";
        for (int i = 0; i <= degree; ++i) {
            std::cin >> coefficients[i];
            if (std::cin.fail()) throw InvalidCoefficientException();
        }
        validate();
    }

    void inputFromString(const std::string& str) {
        std::istringstream iss(str);
        iss >> degree;
        if (degree < 0) throw InvalidDegreeException();

        coefficients.resize(degree + 1);
        for (int i = 0; i <= degree; ++i) {
            iss >> coefficients[i];
            if (iss.fail()) throw InvalidCoefficientException();
        }
        validate();
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
        for (int i = p.degree; i >= 0; --i) {
            if (p.coefficients[i] != 0) {
                if (i < p.degree && p.coefficients[i] > 0) os << "+";
                os << p.coefficients[i];
                if (i > 0) os << "x";
                if (i > 1) os << "^" << i;
                if (i > 0) os << " ";
            }
        }
        return os;
    }

    double evaluate(double x) const {
        double result = 0.0;
        double power = 1.0;

        for (int i = 0; i <= degree; ++i) {
            result += coefficients[i] * power;
            power *= x;
        }

        return result;
    }

    Polynomial derivative() const {
        if (degree == 0) return Polynomial(0);

        Polynomial result(degree - 1);
        for (int i = 1; i <= degree; ++i) {
            result.coefficients[i - 1] = coefficients[i] * i;
        }
        return result;
    }

    Polynomial operator+(const Polynomial& other) const {
        int maxDegree = std::max(degree, other.degree);
        Polynomial result(maxDegree);

        for (int i = 0; i <= maxDegree; ++i) {
            double coeff = 0.0;
            if (i <= degree) coeff += coefficients[i];
            if (i <= other.degree) coeff += other.coefficients[i];
            result.coefficients[i] = coeff;
        }

        return result;
    }

    Polynomial operator-(const Polynomial& other) const {
        int maxDegree = std::max(degree, other.degree);
        Polynomial result(maxDegree);

        for (int i = 0; i <= maxDegree; ++i) {
            double coeff = 0.0;
            if (i <= degree) coeff += coefficients[i];
            if (i <= other.degree) coeff -= other.coefficients[i];
            result.coefficients[i] = coeff;
        }

        return result;
    }

    Polynomial operator*(const Polynomial& other) const {
        int resultDegree = degree + other.degree;
        Polynomial result(resultDegree);

        for (int i = 0; i <= degree; ++i) {
            for (int j = 0; j <= other.degree; ++j) {
                result.coefficients[i + j] += coefficients[i] * other.coefficients[j];
            }
        }

        return result;
    }

    int getDegree() const { return degree; }
    const std::vector<double>& getCoefficients() const { return coefficients; }
};

// Task 9
class StringException : public std::exception {
public:
    const char* what() const noexcept override = 0;
};

class InvalidCharacterException : public StringException {
private:
    char invalidChar;

public:
    InvalidCharacterException(char ch) : invalidChar(ch) {}

    const char* what() const noexcept override {
        static std::string message;
        message = "Invalid character '" + std::string(1, invalidChar) + "' for this string";
        return message.c_str();
    }
};

class FileOperationException : public StringException {
public:
    const char* what() const noexcept override {
        return "File operation failed";
    }
};

class CustomString {
private:
    std::vector<char> allowedChars;
    std::vector<char> content;

    bool isCharAllowed(char c) const {
        return std::find(allowedChars.begin(), allowedChars.end(), c) != allowedChars.end();
    }

    void validateContent(const std::vector<char>& chars) const {
        for (char c : chars) {
            if (!isCharAllowed(c)) {
                throw InvalidCharacterException(c);
            }
        }
    }

    std::vector<char> findIntersection(const std::vector<char>& v1, const std::vector<char>& v2) const {
        std::vector<char> result;
        for (char c1 : v1) {
            if (std::find(v2.begin(), v2.end(), c1) != v2.end()) {
                result.push_back(c1);
            }
        }
        return result;
    }

public:
    CustomString(const std::vector<char>& allowed = {}) : allowedChars(allowed) {}

    void setAllowedChars(const std::vector<char>& allowed) {
        allowedChars = allowed;
        validateContent(content);
    }

    void addAllowedChar(char c) {
        if (std::find(allowedChars.begin(), allowedChars.end(), c) == allowedChars.end()) {
            allowedChars.push_back(c);
        }
    }

    void removeAllowedChar(char c) {
        auto it = std::find(allowedChars.begin(), allowedChars.end(), c);
        if (it != allowedChars.end()) {
            allowedChars.erase(it);
            validateContent(content);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const CustomString& str) {
        for (char c : str.content) {
            os << c;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, CustomString& str) {
        std::string input;
        is >> input;

        str.content.clear();
        for (char c : input) {
            if (!str.isCharAllowed(c)) {
                throw InvalidCharacterException(c);
            }
            str.content.push_back(c);
        }
        return is;
    }

    void writeToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) {
            throw FileOperationException();
        }
        for (char c : content) {
            file << c;
        }
        file.close();
    }

    void readFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            throw FileOperationException();
        }

        content.clear();
        char c;
        while (file.get(c)) {
            if (!isCharAllowed(c)) {
                throw InvalidCharacterException(c);
            }
            content.push_back(c);
        }
        file.close();
    }

    size_t length() const { return content.size(); }

    CustomString concatenate(const CustomString& other) const {
        std::vector<char> newAllowed = findIntersection(allowedChars, other.allowedChars);

        CustomString result(newAllowed);
        result.content = content;

        for (char c : other.content) {
            if (result.isCharAllowed(c)) {
                result.content.push_back(c);
            }
        }

        return result;
    }

    size_t hash() const {
        size_t h = 0;
        for (char c : content) {
            h = h * 31 + static_cast<size_t>(c);
        }
        return h;
    }

    const std::vector<char>& getAllowedChars() const { return allowedChars; }
    const std::vector<char>& getContent() const { return content; }
};

// Task 10
class VectorException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Vector operation failed";
    }
};

class InvalidSizeException : public VectorException {
public:
    const char* what() const noexcept override {
        return "Invalid vector size";
    }
};

class VectorInvalidIndexException : public VectorException {
public:
    const char* what() const noexcept override {
        return "Invalid vector index";
    }
};

class DimensionMismatchException : public VectorException {
public:
    const char* what() const noexcept override {
        return "Vector dimension mismatch";
    }
};

class Vector {
private:
    size_t size;
    double* data;

    void allocateMemory(size_t n) {
        try {
            data = new double[n];
            size = n;
            std::fill_n(data, n, 0.0);
        }
        catch (const std::bad_alloc& e) {
            throw VectorException();
        }
    }

public:
    Vector(size_t n = 0) : size(0), data(nullptr) {
        if (n > 0) {
            allocateMemory(n);
        }
    }

    Vector(size_t n, double value) : size(0), data(nullptr) {
        if (n > 0) {
            allocateMemory(n);
            std::fill_n(data, n, value);
        }
    }

    Vector(const std::vector<double>& values) : size(0), data(nullptr) {
        if (!values.empty()) {
            allocateMemory(values.size());
            std::copy(values.begin(), values.end(), data);
        }
    }

    ~Vector() {
        delete[] data;
    }

    Vector(const Vector& other) : size(0), data(nullptr) {
        if (other.size > 0) {
            allocateMemory(other.size);
            std::copy(other.data, other.data + other.size, data);
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = 0;
            data = nullptr;

            if (other.size > 0) {
                allocateMemory(other.size);
                std::copy(other.data, other.data + other.size, data);
            }
        }
        return *this;
    }

    size_t getSize() const { return size; }

    double& operator[](size_t index) {
        if (index >= size) {
            throw VectorInvalidIndexException();
        }
        return data[index];
    }

    const double& operator[](size_t index) const {
        if (index >= size) {
            throw VectorInvalidIndexException();
        }
        return data[index];
    }

    void setElement(size_t index, double value) {
        if (index >= size) {
            throw VectorInvalidIndexException();
        }
        data[index] = value;
    }

    void fillFromConsole() {
        std::cout << "Enter " << size << " vector elements:\n";
        for (size_t i = 0; i < size; ++i) {
            std::cin >> data[i];
            if (std::cin.fail()) {
                throw std::invalid_argument("Invalid input for vector element");
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        os << "[";
        for (size_t i = 0; i < vec.size; ++i) {
            os << vec.data[i];
            if (i < vec.size - 1) os << ", ";
        }
        os << "]";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector& vec) {
        size_t n;
        is >> n;
        if (is.fail()) {
            throw InvalidSizeException();
        }

        Vector temp(n);
        for (size_t i = 0; i < n; ++i) {
            is >> temp.data[i];
            if (is.fail()) {
                throw std::invalid_argument("Invalid input for vector element");
            }
        }

        vec = temp;
        return is;
    }

    void writeToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) {
            throw FileOperationException();
        }

        file << size << "\n";
        for (size_t i = 0; i < size; ++i) {
            file << data[i] << " ";
        }
        file << "\n";
        file.close();
    }

    void readFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            throw FileOperationException();
        }

        size_t n;
        file >> n;
        if (file.fail()) {
            throw InvalidSizeException();
        }

        Vector temp(n);
        for (size_t i = 0; i < n; ++i) {
            file >> temp.data[i];
            if (file.fail()) {
                throw std::invalid_argument("Invalid data in file");
            }
        }

        *this = temp;
        file.close();
    }

    double dotProduct(const Vector& other) const {
        if (size != other.size) {
            throw DimensionMismatchException();
        }

        double result = 0.0;
        for (size_t i = 0; i < size; ++i) {
            result += data[i] * other.data[i];
        }
        return result;
    }

    Vector crossProduct(const Vector& other) const {
        if (size != 3 || other.size != 3) {
            throw DimensionMismatchException();
        }

        Vector result(3);
        result[0] = data[1] * other.data[2] - data[2] * other.data[1];
        result[1] = data[2] * other.data[0] - data[0] * other.data[2];
        result[2] = data[0] * other.data[1] - data[1] * other.data[0];

        return result;
    }

    Vector operator+(const Vector& other) const {
        if (size != other.size) {
            throw DimensionMismatchException();
        }

        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result[i] = data[i] + other.data[i];
        }
        return result;
    }

    Vector operator-(const Vector& other) const {
        if (size != other.size) {
            throw DimensionMismatchException();
        }

        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result[i] = data[i] - other.data[i];
        }
        return result;
    }
};


void demonstrateTask3() {
    try {
        std::cout << "~~~ Task 3: Number Conversion.\n";
        std::string numStr;
        int base;

        std::cout << "Enter number string: ";
        std::cin >> numStr;
        std::cout << "Enter base (2-16): ";
        std::cin >> base;

        int result = stringToNumber(numStr, base);
        std::cout << "Result: " << result << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void demonstrateTask4() {
    try {
        std::cout << "~~~ Task 4: Complex Numbers.\n";
        Complex z;
        double epsilon;

        std::cout << "Enter complex number (format: real imag): ";
        std::cin >> z;
        std::cout << "Enter epsilon: ";
        std::cin >> epsilon;

        Complex result = arctan(z, epsilon);
        std::cout << "arctan(" << z << ") = " << result << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void demonstrateTask5() {
    try {
        std::cout << "~~~ Task 5: ThreeByte Integers.\n";

        std::vector<ThreeByteInteger> numbers = {
            ThreeByteInteger(100), ThreeByteInteger(200), ThreeByteInteger(300)
        };

        ThreeByteInteger sum = sumThreeByteArray(numbers);
        std::cout << "Sum: " << sum << "\n";

        ThreeByteInteger x(2);
        ThreeByteInteger power = x.power(5);
        std::cout << "2^5 = " << power << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void demonstrateTask6() {
    try {
        std::cout << "~~~ Task 6: Binary Files.\n";
        BinaryFileHandler handler("test.bin");

        std::vector<int> testData = { 1, 2, 3, 4, 5 };
        handler.createFromArray(testData);
        handler.displayContents();

        std::cout << "Number at index 2: " << handler.getNumber(2) << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void demonstrateTask7() {
    try {
        std::cout << "~~~ Task 7: Text Files.\n";
        TextFileHandler handler("test.txt");

        std::vector<std::vector<double>> testData = {
            {1.1, 2.2, 3.3},
            {4.4, 5.5},
            {6.6, 7.7, 8.8, 9.9}
        };

        handler.createFrom2DArray(testData);
        handler.displayContents();

        std::cout << "Number at line 1, position 1: " << handler.getNumber(1, 1) << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void demonstrateTask8() {
    try {
        std::cout << "~~~ Task 8: Polynomials.\n";
        Polynomial p1, p2;

        std::cout << "Enter first polynomial:\n";
        p1.inputFromConsole();
        std::cout << "Enter second polynomial:\n";
        p2.inputFromConsole();

        std::cout << "P1: " << p1 << "\n";
        std::cout << "P2: " << p2 << "\n";
        std::cout << "P1 + P2: " << (p1 + p2) << "\n";
        std::cout << "P1 derivative: " << p1.derivative() << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void demonstrateTask9() {
    try {
        std::cout << "~~~ Task 9: Custom Strings.\n";
        std::vector<char> allowed = { 'a', 'b', 'c', '1', '2', '3' };
        CustomString str(allowed);

        std::cout << "Enter string (allowed chars: a,b,c,1,2,3): ";
        std::cin >> str;

        std::cout << "String: " << str << "\n";
        std::cout << "Hash: " << str.hash() << "\n";
        std::cout << "Length: " << str.length() << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void demonstrateTask10() {
    try {
        std::cout << "~~~ Task 10: Vectors.\n";
        Vector v1(3), v2(3);

        std::cout << "Enter first vector (3 elements):\n";
        v1.fillFromConsole();
        std::cout << "Enter second vector (3 elements):\n";
        v2.fillFromConsole();

        std::cout << "V1: " << v1 << "\n";
        std::cout << "V2: " << v2 << "\n";
        std::cout << "Dot product: " << v1.dotProduct(v2) << "\n";
        std::cout << "Cross product: " << v1.crossProduct(v2) << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    int choice;

    do {
        std::cout << "\n~~~ MAIN MENU ~~~\n";
        std::cout << "3. Number Conversion\n";
        std::cout << "4. Complex Numbers and Arctan\n";
        std::cout << "5. ThreeByte Integers\n";
        std::cout << "6. Binary Files\n";
        std::cout << "7. Text Files\n";
        std::cout << "8. Polynomials\n";
        std::cout << "9. Custom Strings\n";
        std::cout << "10. Vectors\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 3: demonstrateTask3(); break;
        case 4: demonstrateTask4(); break;
        case 5: demonstrateTask5(); break;
        case 6: demonstrateTask6(); break;
        case 7: demonstrateTask7(); break;
        case 8: demonstrateTask8(); break;
        case 9: demonstrateTask9(); break;
        case 10: demonstrateTask10(); break;
        case 0: std::cout << "Bye!\n"; break;
        default: std::cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}