#include <iostream>
#include <random>
using namespace std;

void swapElements(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swapElements(arr[i], arr[j]);
        }
    }

    swapElements(arr[i + 1], arr[high]);
    return i + 1;
}

int randomizedPartition(int arr[], int low, int high, mt19937& gen) {
    uniform_int_distribution<int> dist(low, high);

    int randomIndex = dist(gen);
    swapElements(arr[randomIndex], arr[high]);

    return partition(arr, low, high);
}

int randomizedSelect(int arr[], int low, int high, int i, mt19937& gen) {
    if (low == high) {
        return arr[low];
    }

    int pivotIndex = randomizedPartition(arr, low, high, gen);
    int k = pivotIndex - low + 1;

    if (i == k) {
        return arr[pivotIndex];
    }
    else if (i < k) {
        return randomizedSelect(arr, low, pivotIndex - 1, i, gen);
    }
    else {
        return randomizedSelect(arr, pivotIndex + 1, high, i - k, gen);
    }
}

int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 3;

    random_device rd;
    mt19937 gen(rd());

    if (i > 0 && i <= n) {
        int result = randomizedSelect(arr, 0, n - 1, i, gen);
        cout << "The " << i << "rd smallest element is: "
             << result << endl;
    }
    else {
        cout << "Invalid value of i." << endl;
    }

    return 0;
}