#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <functional>

namespace FunctionNamespace {

    class Function {
    private:
        std::function<double(double)> func;
        double leftBound;
        double rightBound;

    public:
        Function(std::function<double(double)> f = nullptr, double left = 0.0, double right = 1.0)
            : func(f), leftBound(left), rightBound(right) {
            if (leftBound >= rightBound) {
                throw std::invalid_argument("Left bound must be less than right bound");
            }
        }

        void setFunction(std::function<double(double)> f) {
            func = f;
        }

        void setBounds(double left, double right) {
            if (left >= right) {
                throw std::invalid_argument("Left bound must be less than right bound");
            }
            leftBound = left;
            rightBound = right;
        }

        double getLeftBound() const { return leftBound; }
        double getRightBound() const { return rightBound; }

        double evaluate(double x) const {
            if (!func) {
                throw std::runtime_error("Function is not defined");
            }
            return func(x);
        }

        static Function createPolynomial(const std::vector<double>& coefficients) {
            return Function([coefficients](double x) {
                double result = 0.0;
                double power = 1.0;
                for (double coeff : coefficients) {
                    result += coeff * power;
                    power *= x;
                }
                return result;
                });
        }

        static Function createCosine(double amplitude = 1.0, double frequency = 1.0, double phase = 0.0) {
            return Function([amplitude, frequency, phase](double x) {
                return amplitude * std::cos(frequency * x + phase);
                });
        }

        static Function createSquareRoot(double coefficient = 1.0, double linear = 1.0, double constant = 0.0) {
            return Function([coefficient, linear, constant](double x) {
                double arg = linear * x + constant;
                if (arg < 0) {
                    throw std::domain_error("Square root of negative number");
                }
                return coefficient * std::sqrt(arg);
                });
        }

        static Function createLogarithm(double coefficient = 1.0, double linear = 1.0, double constant = 1.0) {
            return Function([coefficient, linear, constant](double x) {
                double arg = linear * x + constant;
                if (arg <= 0) {
                    throw std::domain_error("Logarithm of non-positive number");
                }
                return coefficient * std::log(arg);
                });
        }

        double leftRectangleMethod(int n) const {
            if (n <= 0) throw std::invalid_argument("Number of intervals must be positive");

            double h = (rightBound - leftBound) / n;
            double sum = 0.0;

            for (int i = 0; i < n; ++i) {
                double x = leftBound + i * h;
                sum += evaluate(x);
            }

            return sum * h;
        }

        double rightRectangleMethod(int n) const {
            if (n <= 0) throw std::invalid_argument("Number of intervals must be positive");

            double h = (rightBound - leftBound) / n;
            double sum = 0.0;

            for (int i = 1; i <= n; ++i) {
                double x = leftBound + i * h;
                sum += evaluate(x);
            }

            return sum * h;
        }

        double midpointRectangleMethod(int n) const {
            if (n <= 0) throw std::invalid_argument("Number of intervals must be positive");

            double h = (rightBound - leftBound) / n;
            double sum = 0.0;

            for (int i = 0; i < n; ++i) {
                double x = leftBound + (i + 0.5) * h;
                sum += evaluate(x);
            }

            return sum * h;
        }

        double trapezoidalMethod(int n) const {
            if (n <= 0) throw std::invalid_argument("Number of intervals must be positive");

            double h = (rightBound - leftBound) / n;
            double sum = 0.5 * (evaluate(leftBound) + evaluate(rightBound));

            for (int i = 1; i < n; ++i) {
                double x = leftBound + i * h;
                sum += evaluate(x);
            }

            return sum * h;
        }

        double simpsonMethod(int n) const {
            if (n <= 0 || n % 2 != 0) {
                throw std::invalid_argument("Number of intervals must be positive and even for Simpson's method");
            }

            double h = (rightBound - leftBound) / n;
            double sum = evaluate(leftBound) + evaluate(rightBound);

            for (int i = 1; i < n; i += 2) {
                double x = leftBound + i * h;
                sum += 4 * evaluate(x);
            }

            for (int i = 2; i < n; i += 2) {
                double x = leftBound + i * h;
                sum += 2 * evaluate(x);
            }

            return sum * h / 3.0;
        }

        void sampleFunction(int numSamples) const {
            if (numSamples <= 0) {
                throw std::invalid_argument("Number of samples must be positive");
            }

            std::cout << "\n~~~ Function sampling table ~~~\n";
            std::cout << "Function sampled from " << leftBound << " to " << rightBound << "\n";
            std::cout << "Number of samples: " << numSamples << "\n\n";

            std::cout << std::setw(12) << "Point x" << std::setw(15) << "Value f(x)" << "\n";
            std::cout << std::string(30, '-') << "\n";

            double step = (rightBound - leftBound) / (numSamples - 1);

            for (int i = 0; i < numSamples; ++i) {
                double x = leftBound + i * step;
                try {
                    double y = evaluate(x);
                    std::cout << std::setw(12) << std::fixed << std::setprecision(4) << x
                        << std::setw(15) << std::fixed << std::setprecision(6) << y << "\n";
                }
                catch (const std::exception& e) {
                    std::cout << std::setw(12) << std::fixed << std::setprecision(4) << x
                        << std::setw(15) << "undefined" << "\n";
                }
            }
        }

        void displayInfo() const {
            std::cout << "Function bounds: [" << leftBound << ", " << rightBound << "]\n";
        }
    };

}

void demonstrateFunctionClass() {
    using namespace FunctionNamespace;

    std::cout << "~~~ Function class demonstration ~~~\n\n";

    try {
        // 1. Polynomial function: f(x) = x^2 + 2x + 1
        std::cout << "1. Polynomial: f(x) = x^2 + 2x + 1\n";
        Function poly = Function::createPolynomial({ 1.0, 2.0, 1.0 });
        poly.setBounds(0.0, 2.0);
        poly.displayInfo();

        std::cout << "Testing at x = 1.0: " << poly.evaluate(1.0) << " (expected: 4.0)\n";
        std::cout << "Testing at x = 2.0: " << poly.evaluate(2.0) << " (expected: 9.0)\n\n";

        int intervals = 100;
        std::cout << "Integration methods (n = " << intervals << "):\n";
        std::cout << "Left Rectangles: " << poly.leftRectangleMethod(intervals) << "\n";
        std::cout << "Right Rectangles: " << poly.rightRectangleMethod(intervals) << "\n";
        std::cout << "Midpoint Rectangles: " << poly.midpointRectangleMethod(intervals) << "\n";
        std::cout << "Trapezoidal: " << poly.trapezoidalMethod(intervals) << "\n";
        std::cout << "Simpson's: " << poly.simpsonMethod(intervals) << "\n";
        std::cout << "Exact value: 8.6667\n\n";

        poly.sampleFunction(5);

        // 2. f(x) = cos(x)
        std::cout << "\n\n2. Cosine: f(x) = cos(x)\n";
        Function cosFunc = Function::createCosine(1.0, 1.0, 0.0); // cos(x)
        cosFunc.setBounds(0.0, M_PI);
        cosFunc.displayInfo();

        std::cout << "Testing at x = 0.0: " << cosFunc.evaluate(0.0) << " (expected: 1.0)\n";
        std::cout << "Testing at x = 1.57: " << cosFunc.evaluate(1.57) << " (expected: ~0.0)\n\n";

        std::cout << "Integration methods (n = " << intervals << "):\n";
        std::cout << "Left Rectangles: " << cosFunc.leftRectangleMethod(intervals) << "\n";
        std::cout << "Right Rectangles: " << cosFunc.rightRectangleMethod(intervals) << "\n";
        std::cout << "Midpoint Rectangles: " << cosFunc.midpointRectangleMethod(intervals) << "\n";
        std::cout << "Trapezoidal: " << cosFunc.trapezoidalMethod(intervals) << "\n";
        std::cout << "Simpson's: " << cosFunc.simpsonMethod(intervals) << "\n";
        std::cout << "Exact value: ~0.0\n\n";

        // 3. f(x) = sqrt(x)
        std::cout << "\n\n3. Square Root: f(x) = sqrt(x)\n";
        Function sqrtFunc = Function::createSquareRoot(1.0, 1.0, 0.0); // sqrt(x)
        sqrtFunc.setBounds(0.0, 4.0);
        sqrtFunc.displayInfo();

        std::cout << "Testing at x = 1.0: " << sqrtFunc.evaluate(1.0) << " (expected: 1.0)\n";
        std::cout << "Testing at x = 4.0: " << sqrtFunc.evaluate(4.0) << " (expected: 2.0)\n\n";

        std::cout << "Integration methods (n = " << intervals << "):\n";
        std::cout << "Left Rectangles: " << sqrtFunc.leftRectangleMethod(intervals) << "\n";
        std::cout << "Right Rectangles: " << sqrtFunc.rightRectangleMethod(intervals) << "\n";
        std::cout << "Midpoint Rectangles: " << sqrtFunc.midpointRectangleMethod(intervals) << "\n";
        std::cout << "Trapezoidal: " << sqrtFunc.trapezoidalMethod(intervals) << "\n";
        std::cout << "Simpson's: " << sqrtFunc.simpsonMethod(intervals) << "\n";
        std::cout << "Exact value: 5.3333\n\n";

        // 4. f(x) = ln(x)
        std::cout << "\n\n4. Natural Logarithm: f(x) = ln(x)\n";
        Function logFunc = Function::createLogarithm(1.0, 1.0, 0.0); // ln(x)
        logFunc.setBounds(1.0, 3.0);
        logFunc.displayInfo();

        std::cout << "Testing at x = 1.0: " << logFunc.evaluate(1.0) << " (expected: 0.0)\n";
        std::cout << "Testing at x = 2.0: " << logFunc.evaluate(2.0) << " (expected: 0.6931)\n\n";

        std::cout << "Integration methods (n = " << intervals << "):\n";
        std::cout << "Left Rectangles: " << logFunc.leftRectangleMethod(intervals) << "\n";
        std::cout << "Right Rectangles: " << logFunc.rightRectangleMethod(intervals) << "\n";
        std::cout << "Midpoint Rectangles: " << logFunc.midpointRectangleMethod(intervals) << "\n";
        std::cout << "Trapezoidal: " << logFunc.trapezoidalMethod(intervals) << "\n";
        std::cout << "Simpson's: " << logFunc.simpsonMethod(intervals) << "\n";
        std::cout << "Exact value: " << (3 * std::log(3) - 2) << "\n\n";

        logFunc.sampleFunction(6);

        // 5. f(x) = x^2 + sin(x)
        std::cout << "\n\n5. Complex Function: f(x) = x^2 + sin(x)\n";
        Function complexFunc([](double x) { return x * x + std::sin(x); });
        complexFunc.setBounds(0.0, 2.0);
        complexFunc.displayInfo();

        std::cout << "Testing at x = 1.0: " << complexFunc.evaluate(1.0) << "\n";
        std::cout << "Testing at x = 1.5: " << complexFunc.evaluate(1.5) << "\n\n";

        std::cout << "Integration methods (n = " << intervals << "):\n";
        std::cout << "Left Rectangles: " << complexFunc.leftRectangleMethod(intervals) << "\n";
        std::cout << "Right Rectangles: " << complexFunc.rightRectangleMethod(intervals) << "\n";
        std::cout << "Midpoint Rectangles: " << complexFunc.midpointRectangleMethod(intervals) << "\n";
        std::cout << "Trapezoidal: " << complexFunc.trapezoidalMethod(intervals) << "\n";
        std::cout << "Simpson's: " << complexFunc.simpsonMethod(intervals) << "\n\n";

        complexFunc.sampleFunction(8);

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    demonstrateFunctionClass();
    return 0;
}