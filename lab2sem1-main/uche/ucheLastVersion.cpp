#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace chrono;
int binarySearch(int arr[], int value, int start, int end) {
    if (end >= start) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == value) {
            return mid;
        }
        if (arr[mid] > value) {
            return binarySearch(arr, value, start, mid - 1);
        }
        return binarySearch(arr, value, mid + 1, end);
    }
    return -1;
}
void mainMenu() {
    system("cls");
    cout << "Выберите действие: " << endl;
    cout << "1. Создать новый массив" << endl;
    cout << "2. Вывести элементы массива" << endl;
    cout << "3. Сортировка массива, поиск максимального и минимального элементов, поиск индексов и количества элементов, равных среднему значению максимального и минимального" << endl;
    cout << "4. Найти в отсортированном массиве количество элементов, которые меньше введенного вами числа" << endl;
    cout << "5. Найти в отсортированном массиве количество элементов, которые больше введенного вами числа" << endl;
    cout << "6. Бинарный поиск введенного числа в массиве" << endl;
    cout << "7. Поменять элементы массива местами" << endl;
    cout << "8. Уменьшить нечетные элементы на выбранное значение, умножить их на рандомное число, вывести делимость элементов " << endl;
    cout << "9. Выход" << endl;
    cout << "Введите число, соответствующее нужному вам действию: ";
}
void choosingSortMenu() {
    system("cls");
    cout << "Выберите сортировку: " << endl;
    cout << "1. Bubble sort " << endl;
    cout << "2. Shaker sort" << endl;
    cout << "3. Comb sort" << endl;
    cout << "4. Insert sort" << endl;
    cout << "5. Quick sort" << endl;
    cout << "6. Выход" << endl;
    cout << "Введите число, соответствующее нужному вам действию: ";
}
int checkInput(int ceiling = 2147483647, int floor = -2147483647) {
    int num;
    cin >> num;
    while (cin.fail() || cin.peek() != '\n' || num > ceiling || num < floor) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введите корректное значение: ";
        cin >> num;
    }
    return num;
}
void MinMaxAverage(int arr[], int N) {
    int arrMax = 0, arrMin = 10 ^ 10, average = 0, amount = 0;
    auto start = steady_clock::now();
    for (int i = 0; i < N; i++)
    {
        if (arr[i] > arrMax)
            arrMax = arr[i];
        if (arr[i] < arrMin)
            arrMin = arr[i];
    }
    average = (arrMax + arrMin) / 2;
    auto end = steady_clock::now();
    auto result = duration_cast<nanoseconds>(end - start);
    cout << "максимальный элемент: " << arrMax;
    cout << ", минимальный элемент: " << arrMin << endl;
    cout << "Среднее значение максимального и минимального элементов: " << average << endl;
    cout << "Bремя на поиск: " << duration_cast<nanoseconds>(end - start).count() << '\n';
    cout << "Индексы всех элементов, равных среднему значению: ";
    auto start1 = steady_clock::now();
    for (int i = 0; i < N; ++i) {
        if (arr[i] == average) {
            amount = amount + 1;
            cout << i << " ";
        }
    }
    cout << endl;
    auto end1 = steady_clock::now();
    auto result1 = duration_cast<nanoseconds>(end1 - start1);
    cout << "Поиск занял " << duration_cast<nanoseconds>(end1 - start1).count() << " нс" << endl;
    cout << "Всего нашлось подходящих элементов: " << amount << endl;
}
void MinMaxAverageForSorted(int arr[], int N) {
    int amount = 0;
    auto start = steady_clock::now();
    int arrMax = arr[N - 1];
    int arrMin = arr[0];
    int average = (arrMax + arrMin) / 2;
    auto end = steady_clock::now();
    auto result = duration_cast<nanoseconds>(end - start);
    cout << "максимальный элемент: " << arrMax;
    cout << ", минимальный элемент: " << arrMin << endl;
    cout << "Среднее значение максимального и минимального элементов: " << average << endl;
    cout << "Bремя на поиск: " << duration_cast<nanoseconds>(end - start).count() << '\n';   
    cout << "Индексы всех элементов, равных среднему значению: ";
    auto start1 = steady_clock::now();
    int index = binarySearch(arr, average, 0, 99);
    if (index != -1) {
        cout << index << " ";
        amount += 1;
        for (int i = 1; i < N - index; i++) {
            if (arr[index + i] == arr[index]) {
                cout << index + i << " ";
                amount++;
            }
            else
                break;
        }
    }
    auto end1 = steady_clock::now();
    auto result1 = duration_cast<nanoseconds>(end1 - start1);
    cout << endl;
    cout << "Поиск занял " << duration_cast<nanoseconds>(end1 - start1).count() << " нс" << endl;
    cout << "Всего нашлось подходящих элементов: " << amount << endl;
}
void quickSort(int* arr, int  end, int begin){   
    int f = begin, l = end;
    int mid = arr[(f + l) / 2];
    while (f < l)
    {   
        while (arr[f] < mid) f++;
        while (arr[l] > mid) l--;
        if (f <= l)
        {
            swap(arr[f], arr[l]);
            f++;
            l--;
        }     
    }
    if (begin < l) {    
        quickSort(arr, l, begin);     
    }
    if (f < end) {
        quickSort(arr, end, f);
    }
}
void combSort(int arr[], int N) {
    auto start1 = steady_clock::now();
    int swap, count = 0;
    float k = 1.247, S = N - 1;
    while (S >= 1)
    {
        for (int i = 0; i + S < N; i++)
        {
            if (arr[i] > arr[int(i + S)])
            {
                swap = arr[int(i + S)];
                arr[int(i + S)] = arr[i];
                arr[i] = swap;
            }
        }
        S /= k;
    }

    while (true)
    {
        for (int i = 0; i < N - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = swap;
            }
            else count++;
        }
        if (count == N - 1)
            break;
        else
            count = 0;
    }
    auto end1 = steady_clock::now();
    auto result1 = duration_cast<nanoseconds>(end1 - start1);
    cout << "Сортировка заняла " << duration_cast<nanoseconds>(end1 - start1).count() << " нс" << endl;
}
void insertSort(int arr[], int n) {
    auto start1 = steady_clock::now();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    auto end1 = steady_clock::now();
    auto result1 = duration_cast<nanoseconds>(end1 - start1);
    cout << "Сортировка заняла " << duration_cast<nanoseconds>(end1 - start1).count() << " нс" << endl;
}
void ShakerSort(int arr[], int n) {
    auto start1 = steady_clock::now();
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
    auto end1 = steady_clock::now();
    auto result1 = duration_cast<nanoseconds>(end1 - start1);
    cout << "Сортировка заняла " << duration_cast<nanoseconds>(end1 - start1).count() << " нс" << endl;
}
void bubbleSort(int arr[], int n) {
    auto start1 = steady_clock::now();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j+1] < arr[j])
            {
                swap(arr[j], arr[j + 1]);
            }
    }
    auto end1 = steady_clock::now();
    auto result1 = duration_cast<nanoseconds>(end1 - start1);
    cout << "Сортировка заняла " << duration_cast<nanoseconds>(end1 - start1).count() << " нс" << endl;
}

int main() {
    setlocale(0, "");
    srand(time(NULL));
    const int n = 100;
    int A[n];
    int size = sizeof(A) / sizeof(A[0]);  
    for (int i = 0; i < n; ++i)
        A[i] = rand()%198 - 99;
    cin.sync();
    int choice;
    do {
        mainMenu();
        choice = checkInput(9, 1);
        int endSort = n - 1, beginSort = 0;
        switch (choice) {
        case 1:
            cout << "Вот новый массив: ";
            for (int i = 0; i < n; ++i) {
                A[i] = rand() % 198 - 99;
                cout << A[i] << ' ';
            }
            cout << endl;
            break;

        case 2:
            cout << "Вот все элементы массива: ";
            for (int i = 0; i < n; ++i)
                cout << A[i] << " ";
            cout << endl;
            break;
        case 3:    
            int choice2;
            do {
                choosingSortMenu();
                choice2 = checkInput(6, 1);
                switch (choice2) {
                case 1:
                    cout << "Без сортировки: " << endl;
                    MinMaxAverage(A, n);
                    bubbleSort(A, n);
                    cout << "\nС сортировкой: " << endl;
                    MinMaxAverageForSorted(A, n);
                    break;
                case 2:  
                    cout << "Без сортировки: " << endl;
                    MinMaxAverage(A, n);
                    ShakerSort(A, n);
                    cout << "\nС сортировкой: " << endl;
                    MinMaxAverageForSorted(A, n);
                    break;
                case 3:
                    cout << "Без сортировки: " << endl;
                    MinMaxAverage(A, n);
                    combSort(A, n);
                    cout << "\nС сортировкой: " << endl;
                    MinMaxAverageForSorted(A, n);
                    break;
                case 4:
                    cout << "Без сортировки: " << endl;
                    MinMaxAverage(A, n);
                    insertSort(A, n);
                    cout << "\nС сортировкой: " << endl;
                    MinMaxAverageForSorted(A, n);
                    break;
                case 5:
                {
                    cout << "Без сортировки: " << endl;
                    MinMaxAverage(A, n);           
                    auto start1 = steady_clock::now();
                    quickSort(A, endSort, beginSort);
                    auto end1 = steady_clock::now();
                    auto result1 = duration_cast<nanoseconds>(end1 - start1);
                    cout << "Сортировка заняла " << duration_cast<nanoseconds>(end1 - start1).count() << " нс" << endl;
                    cout << "\nС сортировкой: " << endl;
                    MinMaxAverageForSorted(A, n);
                    break;
                }
                }
                if (choice2 != 6)
                    system("pause");

            }while (choice2 != 6);
            if (choice2 == 6)
                continue;
        case 4:
        {
            cout << "Введите число: ";
            int num = checkInput();
            quickSort(A, endSort, beginSort);
            int count = 0;
            for (int i = 0; i < n; ++i) {
                if (A[i] < num)
                    count += 1;
                else
                    break;
            }
            cout << "Чисел, меньше вашего: " << count << endl;
            break;
        }
        case 5:
        {
            cout << "Введите число: ";
            int num = checkInput();
            quickSort(A, endSort, beginSort);
            int count = 0;
            for (int i = n-1; i >= 0; --i) {
                if (A[i] > num)
                    count += 1;
                else
                    break;
            }
            cout << "Чисел, больше вашего: " << count << endl;
            break;
        }
        case 6:
        {            
            cout << "Введите число, которое вы ищите: ";
            int value = checkInput();
            cout << "Поиск перебором: " << endl;
            int flag = 0;
            auto start = steady_clock::now();         
            for (int i = 0; i < n; i++) {
                if (A[i] == value) {
                    flag = 1;
                    break;
                }         
            }            
            auto end = steady_clock::now();
            auto result = duration_cast<nanoseconds>(end - start);
            if (flag) {
                cout << "Элемент был найден " << endl;
            }
            else{
                cout << "Элемент не найден" << endl;
            }
            cout << "Поиск занял " << duration_cast<nanoseconds>(end - start).count() << " нс" << endl; 
            quickSort(A, endSort, beginSort);
            cout << "Бинарный поиск: " << endl;
            auto startB = steady_clock::now();
            int reply = binarySearch(A, value, 0, size - 1);
            auto endB = steady_clock::now();
            auto resultB = duration_cast<nanoseconds>(endB - startB);
            if (reply == -1) {
                cout << "Элемент не найден" << endl;
            }
            else {
                cout << "Элемент был найден " << endl;
            }
            cout << "Поиск занял " << duration_cast<nanoseconds>(endB - startB).count() << " нс" << endl;
            break;
        }
        case 7:
        {
            int index1, index2;
            cout << "Введите индексы элементов массива, которые вы хотите поменять местами" << endl;
            cout << "Первый индекс: ";
            index1 = checkInput();
            cout << "Второй индекс: ";
            index2 = checkInput();
            auto start1 = steady_clock::now();
            swap(A[index1], A[index2]);
            auto end1 = steady_clock::now();
            auto result1 = duration_cast<nanoseconds>(end1 - start1);
            cout << "Перестановка заняла " << duration_cast<nanoseconds>(end1 - start1).count() << " нс" << endl;
            cout << "Измененный массив выглядит так: " << endl;
            for (int i = 0; i < n; ++i)
                cout << A[i] << "; ";
            cout << endl;
            break;

        }
        case 8:
        {
            cout << "Введите на какое значение уменьшить нечетные элементы массива: ";
            int num = checkInput();
            int randNum = ((rand() % 9) + 1);
            cout << "Рандомное число: " << randNum << endl;
            for (int i = 1; i < n; i+=2) {
                A[i] = (A[i] - num) * randNum;
            }
            cout << "Измененный массив выглядит так: ";
            for (int i = 0; i < n; ++i)
                cout << A[i] << "; ";
            cout << endl;
            cout << "Количество элементов, которые нацело делятся на " << endl;
            int count = 0;
            cout << "1: " << n << endl;
            for (int i = 2; i < 9; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (A[j] % i == 0)
                        count += 1;
                }
                cout << i << ": " << count << endl;
                count = 0;
            }
            break;
        }
        }
        if (choice != 9)
            system("pause");
    }while (choice != 9);
    return 0;
}
