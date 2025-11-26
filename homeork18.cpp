#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <queue>
#include <stack>
#include <string>
#include <stdexcept>

namespace SortingAlgorithms {

    template<typename T>
    class Array {
    private:
        size_t arraySize;
        std::unique_ptr<T[]> data;

    public:
        Array(size_t size = 0) : arraySize(size), data(size > 0 ? new T[size] : nullptr) {}

        Array(const std::vector<T>& values) : arraySize(values.size()), data(new T[values.size()]) {
            for (size_t i = 0; i < arraySize; ++i) {
                data[i] = values[i];
            }
        }

        Array(const Array& other) : arraySize(other.arraySize), data(other.arraySize > 0 ? new T[other.arraySize] : nullptr) {
            for (size_t i = 0; i < arraySize; ++i) {
                data[i] = other.data[i];
            }
        }

        Array& operator=(const Array& other) {
            if (this != &other) {
                arraySize = other.arraySize;
                data.reset(other.arraySize > 0 ? new T[other.arraySize] : nullptr);
                for (size_t i = 0; i < arraySize; ++i) {
                    data[i] = other.data[i];
                }
            }
            return *this;
        }

        size_t size() const { return arraySize; }
        T& operator[](size_t index) {
            if (index >= arraySize) throw std::out_of_range("Index out of range");
            return data[index];
        }
        const T& operator[](size_t index) const {
            if (index >= arraySize) throw std::out_of_range("Index out of range");
            return data[index];
        }

        void fill(const std::vector<T>& values) {
            arraySize = values.size();
            data.reset(new T[arraySize]);
            for (size_t i = 0; i < arraySize; ++i) {
                data[i] = values[i];
            }
        }

        void display() const {
            std::cout << "[";
            for (size_t i = 0; i < arraySize; ++i) {
                std::cout << data[i];
                if (i < arraySize - 1) std::cout << ", ";
            }
            std::cout << "]\n";
        }

        // a)
        void bubbleSort() {
            for (size_t i = 0; i < arraySize - 1; ++i) {
                for (size_t j = 0; j < arraySize - i - 1; ++j) {
                    if (data[j] > data[j + 1]) {
                        std::swap(data[j], data[j + 1]);
                    }
                }
            }
        }

        static void bubbleSortStatic(T arr[], size_t size) {
            for (size_t i = 0; i < size - 1; ++i) {
                for (size_t j = 0; j < size - i - 1; ++j) {
                    if (arr[j] > arr[j + 1]) {
                        std::swap(arr[j], arr[j + 1]);
                    }
                }
            }
        }

        // b)
        void shakerSort() {
            bool swapped = true;
            size_t start = 0;
            size_t end = arraySize - 1;

            while (swapped) {
                swapped = false;

                // Left to right
                for (size_t i = start; i < end; ++i) {
                    if (data[i] > data[i + 1]) {
                        std::swap(data[i], data[i + 1]);
                        swapped = true;
                    }
                }

                if (!swapped) break;

                swapped = false;
                --end;

                // Right to left
                for (size_t i = end; i > start; --i) {
                    if (data[i] < data[i - 1]) {
                        std::swap(data[i], data[i - 1]);
                        swapped = true;
                    }
                }

                ++start;
            }
        }

        static void shakerSortStatic(T arr[], size_t size) {
            bool swapped = true;
            size_t start = 0;
            size_t end = size - 1;

            while (swapped) {
                swapped = false;

                for (size_t i = start; i < end; ++i) {
                    if (arr[i] > arr[i + 1]) {
                        std::swap(arr[i], arr[i + 1]);
                        swapped = true;
                    }
                }

                if (!swapped) break;

                swapped = false;
                --end;

                for (size_t i = end; i > start; --i) {
                    if (arr[i] < arr[i - 1]) {
                        std::swap(arr[i], arr[i - 1]);
                        swapped = true;
                    }
                }

                ++start;
            }
        }

        // c)
        void selectionSort() {
            for (size_t i = 0; i < arraySize - 1; ++i) {
                size_t minIndex = i;
                for (size_t j = i + 1; j < arraySize; ++j) {
                    if (data[j] < data[minIndex]) {
                        minIndex = j;
                    }
                }
                if (minIndex != i) {
                    std::swap(data[i], data[minIndex]);
                }
            }
        }

        static void selectionSortStatic(T arr[], size_t size) {
            for (size_t i = 0; i < size - 1; ++i) {
                size_t minIndex = i;
                for (size_t j = i + 1; j < size; ++j) {
                    if (arr[j] < arr[minIndex]) {
                        minIndex = j;
                    }
                }
                if (minIndex != i) {
                    std::swap(arr[i], arr[minIndex]);
                }
            }
        }

        // d)
        void insertionSort() {
            for (size_t i = 1; i < arraySize; ++i) {
                T key = data[i];
                size_t j = i;
                while (j > 0 && data[j - 1] > key) {
                    data[j] = data[j - 1];
                    --j;
                }
                data[j] = key;
            }
        }

        static void insertionSortStatic(T arr[], size_t size) {
            for (size_t i = 1; i < size; ++i) {
                T key = arr[i];
                size_t j = i;
                while (j > 0 && arr[j - 1] > key) {
                    arr[j] = arr[j - 1];
                    --j;
                }
                arr[j] = key;
            }
        }

        // e)
        void hashSort() {
            if (arraySize == 0) return;

            T minVal = data[0];
            T maxVal = data[0];
            for (size_t i = 1; i < arraySize; ++i) {
                if (data[i] < minVal) minVal = data[i];
                if (data[i] > maxVal) maxVal = data[i];
            }

            size_t range = static_cast<size_t>(maxVal - minVal) + 1;
            std::vector<std::vector<T>> hashTable(range);

            for (size_t i = 0; i < arraySize; ++i) {
                size_t hashIndex = static_cast<size_t>(data[i] - minVal);
                hashTable[hashIndex].push_back(data[i]);
            }

            size_t index = 0;
            for (auto& bucket : hashTable) {
                std::sort(bucket.begin(), bucket.end());
                for (const T& val : bucket) {
                    data[index++] = val;
                }
            }
        }

        static void hashSortStatic(T arr[], size_t size) {
            if (size == 0) return;

            T minVal = arr[0];
            T maxVal = arr[0];
            for (size_t i = 1; i < size; ++i) {
                if (arr[i] < minVal) minVal = arr[i];
                if (arr[i] > maxVal) maxVal = arr[i];
            }

            size_t range = static_cast<size_t>(maxVal - minVal) + 1;
            std::vector<std::vector<T>> hashTable(range);

            for (size_t i = 0; i < size; ++i) {
                size_t hashIndex = static_cast<size_t>(arr[i] - minVal);
                hashTable[hashIndex].push_back(arr[i]);
            }

            size_t index = 0;
            for (auto& bucket : hashTable) {
                std::sort(bucket.begin(), bucket.end());
                for (const T& val : bucket) {
                    arr[index++] = val;
                }
            }
        }

        // f)
        void merge(size_t left, size_t mid, size_t right) {
            size_t n1 = mid - left + 1;
            size_t n2 = right - mid;

            std::vector<T> leftArr(n1), rightArr(n2);

            for (size_t i = 0; i < n1; ++i)
                leftArr[i] = data[left + i];
            for (size_t j = 0; j < n2; ++j)
                rightArr[j] = data[mid + 1 + j];

            size_t i = 0, j = 0, k = left;

            while (i < n1 && j < n2) {
                if (leftArr[i] <= rightArr[j]) {
                    data[k] = leftArr[i];
                    ++i;
                }
                else {
                    data[k] = rightArr[j];
                    ++j;
                }
                ++k;
            }

            while (i < n1) {
                data[k] = leftArr[i];
                ++i;
                ++k;
            }

            while (j < n2) {
                data[k] = rightArr[j];
                ++j;
                ++k;
            }
        }

        void mergeSortHelper(size_t left, size_t right) {
            if (left >= right) return;

            size_t mid = left + (right - left) / 2;
            mergeSortHelper(left, mid);
            mergeSortHelper(mid + 1, right);
            merge(left, mid, right);
        }

        void binaryMergeSort() {
            if (arraySize > 1) {
                mergeSortHelper(0, arraySize - 1);
            }
        }

        static void mergeStatic(T arr[], size_t left, size_t mid, size_t right) {
            size_t n1 = mid - left + 1;
            size_t n2 = right - mid;

            std::vector<T> leftArr(n1), rightArr(n2);

            for (size_t i = 0; i < n1; ++i)
                leftArr[i] = arr[left + i];
            for (size_t j = 0; j < n2; ++j)
                rightArr[j] = arr[mid + 1 + j];

            size_t i = 0, j = 0, k = left;

            while (i < n1 && j < n2) {
                if (leftArr[i] <= rightArr[j]) {
                    arr[k] = leftArr[i];
                    ++i;
                }
                else {
                    arr[k] = rightArr[j];
                    ++j;
                }
                ++k;
            }

            while (i < n1) {
                arr[k] = leftArr[i];
                ++i;
                ++k;
            }

            while (j < n2) {
                arr[k] = rightArr[j];
                ++j;
                ++k;
            }
        }

        static void binaryMergeSortStatic(T arr[], size_t left, size_t right) {
            if (left >= right) return;

            size_t mid = left + (right - left) / 2;
            binaryMergeSortStatic(arr, left, mid);
            binaryMergeSortStatic(arr, mid + 1, right);
            mergeStatic(arr, left, mid, right);
        }

        static void binaryMergeSortStatic(T arr[], size_t size) {
            if (size > 1) {
                binaryMergeSortStatic(arr, 0, size - 1);
            }
        }

        // g)
        void shellSort() {
            for (size_t gap = arraySize / 2; gap > 0; gap /= 2) {
                for (size_t i = gap; i < arraySize; ++i) {
                    T temp = data[i];
                    size_t j;
                    for (j = i; j >= gap && data[j - gap] > temp; j -= gap) {
                        data[j] = data[j - gap];
                    }
                    data[j] = temp;
                }
            }
        }

        static void shellSortStatic(T arr[], size_t size) {
            for (size_t gap = size / 2; gap > 0; gap /= 2) {
                for (size_t i = gap; i < size; ++i) {
                    T temp = arr[i];
                    size_t j;
                    for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                        arr[j] = arr[j - gap];
                    }
                    arr[j] = temp;
                }
            }
        }

        // h)
        size_t partition(size_t low, size_t high) {
            T pivot = data[high];
            size_t i = low;

            for (size_t j = low; j < high; ++j) {
                if (data[j] <= pivot) {
                    std::swap(data[i], data[j]);
                    ++i;
                }
            }
            std::swap(data[i], data[high]);
            return i;
        }

        void quickSortHelper(size_t low, size_t high) {
            if (low < high) {
                size_t pi = partition(low, high);
                if (pi > 0) quickSortHelper(low, pi - 1);
                quickSortHelper(pi + 1, high);
            }
        }

        void quickSort() {
            if (arraySize > 1) {
                quickSortHelper(0, arraySize - 1);
            }
        }

        static size_t partitionStatic(T arr[], size_t low, size_t high) {
            T pivot = arr[high];
            size_t i = low;

            for (size_t j = low; j < high; ++j) {
                if (arr[j] <= pivot) {
                    std::swap(arr[i], arr[j]);
                    ++i;
                }
            }
            std::swap(arr[i], arr[high]);
            return i;
        }

        static void quickSortStatic(T arr[], size_t low, size_t high) {
            if (low < high) {
                size_t pi = partitionStatic(arr, low, high);
                if (pi > 0) quickSortStatic(arr, low, pi - 1);
                quickSortStatic(arr, pi + 1, high);
            }
        }

        static void quickSortStatic(T arr[], size_t size) {
            if (size > 1) {
                quickSortStatic(arr, 0, size - 1);
            }
        }

        // i)
        void heapify(size_t n, size_t i) {
            size_t largest = i;
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;

            if (left < n && data[left] > data[largest])
                largest = left;

            if (right < n && data[right] > data[largest])
                largest = right;

            if (largest != i) {
                std::swap(data[i], data[largest]);
                heapify(n, largest);
            }
        }

        void heapSort() {
            for (int i = arraySize / 2 - 1; i >= 0; --i)
                heapify(arraySize, i);

            for (int i = arraySize - 1; i > 0; --i) {
                std::swap(data[0], data[i]);
                heapify(i, 0);
            }
        }

        static void heapifyStatic(T arr[], size_t n, size_t i) {
            size_t largest = i;
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;

            if (left < n && arr[left] > arr[largest])
                largest = left;

            if (right < n && arr[right] > arr[largest])
                largest = right;

            if (largest != i) {
                std::swap(arr[i], arr[largest]);
                heapifyStatic(arr, n, largest);
            }
        }

        static void heapSortStatic(T arr[], size_t size) {

            for (int i = size / 2 - 1; i >= 0; --i)
                heapifyStatic(arr, size, i);

            for (int i = size - 1; i > 0; --i) {
                std::swap(arr[0], arr[i]);
                heapifyStatic(arr, i, 0);
            }
        }
    };

}

void demonstrateSortingAlgorithms() {
    using namespace SortingAlgorithms;

    std::cout << "~~~ sorting algorithms demonstration ~~~\n\n";

    std::vector<int> testData = { 64, 34, 25, 12, 22, 11, 90, 5, 77, 30 };

    std::cout << "Original array: ";
    for (int val : testData) std::cout << val << " ";
    std::cout << "\n\n";

    Array<int> arr1(testData);
    std::cout << "a) Bubble Sort: ";
    arr1.bubbleSort();
    arr1.display();

    Array<int> arr2(testData);
    std::cout << "b) Shaker Sort: ";
    arr2.shakerSort();
    arr2.display();

    Array<int> arr3(testData);
    std::cout << "c) Selection Sort: ";
    arr3.selectionSort();
    arr3.display();

    Array<int> arr4(testData);
    std::cout << "d) Insertion Sort: ";
    arr4.insertionSort();
    arr4.display();

    Array<int> arr5(testData);
    std::cout << "e) Hash Sort: ";
    arr5.hashSort();
    arr5.display();

    Array<int> arr6(testData);
    std::cout << "f) Binary Merge Sort: ";
    arr6.binaryMergeSort();
    arr6.display();

    Array<int> arr7(testData);
    std::cout << "g) Shell Sort: ";
    arr7.shellSort();
    arr7.display();

    Array<int> arr8(testData);
    std::cout << "h) Quick Sort: ";
    arr8.quickSort();
    arr8.display();

    Array<int> arr9(testData);
    std::cout << "i) Heap Sort: ";
    arr9.heapSort();
    arr9.display();


    std::cout << "\n~~~ testing static methods ~~~\n";
    int staticArray[] = { 64, 34, 25, 12, 22, 11, 90, 5, 77, 30 };
    size_t staticSize = sizeof(staticArray) / sizeof(staticArray[0]);

    std::cout << "Original static array: ";
    for (size_t i = 0; i < staticSize; ++i) std::cout << staticArray[i] << " ";
    std::cout << "\n";

    Array<int>::quickSortStatic(staticArray, staticSize);
    std::cout << "After Quick Sort (static): ";
    for (size_t i = 0; i < staticSize; ++i) std::cout << staticArray[i] << " ";
    std::cout << "\n";
}

int main() {
    try {
        demonstrateSortingAlgorithms();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}