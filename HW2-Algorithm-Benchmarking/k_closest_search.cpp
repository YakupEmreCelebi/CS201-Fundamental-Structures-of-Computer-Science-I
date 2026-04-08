#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <ctime>

int *jumpSearchFindClosest(int *arr, int size, int k, int value)
{
    int targetIndex = 0;
    int m = sqrt(size);
    bool endOfBlock = true;
    for (int i = 0; i < size; i += m)
    {

        if (value < arr[i])
        {
            endOfBlock = false;
            bool atEnd = true;

            if (i < m)
            {
                targetIndex = 0;
                break;
            }
            for (int j = i - m; j < i; j++)
            {
                if (arr[j] == value)
                {
                    int *foundIndex = new int[1];
                    foundIndex[0] = j;
                    return foundIndex;
                }
                else if (arr[j] > value)
                {
                    targetIndex = j;
                    atEnd = false;
                    break;
                }
            }
            if (atEnd)
            {
                targetIndex = i;
            }
            break;
        }
        else if (value == arr[i])
        {
            int *foundIndex = new int[1];
            foundIndex[0] = i;
            return foundIndex;
        }
    }
    if (endOfBlock)
    {
        targetIndex = size;
    }
    int *closestValues = new int[k];

    int leftIndex = 0;
    int rightIndex = 0;
    if (targetIndex == size)
    {
        for (int i = 0; i < k; i++)
        {
            closestValues[i] = arr[targetIndex - 1 - i];
        }
    }
    else if (targetIndex == 0)
    {
        for (int i = 0; i < k; i++)
        {
            closestValues[i] = arr[i];
        }
    }
    else
    {
        leftIndex = targetIndex - 1;
        rightIndex = targetIndex;

        for (int i = 0; i < k; i++)
        {
            if (rightIndex >= size)
            {
                closestValues[i] = arr[leftIndex];
                leftIndex--;
            }
            else if (leftIndex < 0)
            {
                closestValues[i] = arr[rightIndex];
                rightIndex++;
            }
            else
            {
                if (abs(value - arr[leftIndex]) <= abs(value - arr[rightIndex]))
                {
                    closestValues[i] = arr[leftIndex];
                    leftIndex--;
                }
                else
                {
                    closestValues[i] = arr[rightIndex];
                    rightIndex++;
                }
            }
        }
    }
    return closestValues;
}

int *binarySearchFindClosest(int *arr, int size, int k, int value)
{
    int targetIndex = -1;

    int low = 0, high = size - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] < value)
        {
            low = mid + 1;
        }
        else if (arr[mid] > value)
        {
            high = mid - 1;
        }
        else
        {
            int *foundIndex = new int[1];
            foundIndex[0] = mid;
            return foundIndex;
        }
    }
    targetIndex = low;

    int *closestValues = new int[k];

    int leftIndex = 0;
    int rightIndex = 0;
    if (targetIndex == size)
    {
        for (int i = 0; i < k; i++)
        {
            closestValues[i] = arr[targetIndex - 1 - i];
        }
    }
    else if (targetIndex == 0)
    {
        for (int i = 0; i < k; i++)
        {
            closestValues[i] = arr[i];
        }
    }
    else
    {
        leftIndex = targetIndex - 1;
        rightIndex = targetIndex;

        for (int i = 0; i < k; i++)
        {
            if (rightIndex >= size)
            {
                closestValues[i] = arr[leftIndex];
                leftIndex--;
            }
            else if (leftIndex < 0)
            {
                closestValues[i] = arr[rightIndex];
                rightIndex++;
            }
            else
            {
                if (abs(value - arr[leftIndex]) <= abs(value - arr[rightIndex]))
                {
                    closestValues[i] = arr[leftIndex];
                    leftIndex--;
                }
                else
                {
                    closestValues[i] = arr[rightIndex];
                    rightIndex++;
                }
            }
        }
    }
    return closestValues;
}

int *linearSearchFindClosest(int *arr, int size, int k, int value)
{
    int targetIndex = 0;
    bool atEnd = true;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value)
        {
            int *foundIndex = new int[1];
            foundIndex[0] = i;
            return foundIndex;
        }
        else if (arr[i] > value)
        {
            targetIndex = i;
            atEnd = false;
            break;
        }
    }
    if (atEnd)
    {
        targetIndex = size;
    }

    int *closestValues = new int[k];

    int leftIndex = 0;
    int rightIndex = 0;
    if (targetIndex == size)
    {
        for (int i = 0; i < k; i++)
        {
            closestValues[i] = arr[targetIndex - 1 - i];
        }
    }
    else if (targetIndex == 0)
    {
        for (int i = 0; i < k; i++)
        {
            closestValues[i] = arr[i];
        }
    }
    else
    {
        leftIndex = targetIndex - 1;
        rightIndex = targetIndex;

        for (int i = 0; i < k; i++)
        {
            if (rightIndex >= size)
            {
                closestValues[i] = arr[leftIndex];
                leftIndex--;
            }
            else if (leftIndex < 0)
            {
                closestValues[i] = arr[rightIndex];
                rightIndex++;
            }
            else
            {
                if (abs(value - arr[leftIndex]) <= abs(value - arr[rightIndex]))
                {
                    closestValues[i] = arr[leftIndex];
                    leftIndex--;
                }
                else
                {
                    closestValues[i] = arr[rightIndex];
                    rightIndex++;
                }
            }
        }
    }

    return closestValues;
}

int *createSortedRandomArray(int N)
{
    int *arr = new int[N];

    for (int i = 0; i < N; ++i)
    {
        int baseValue = i * 10;
        int offset = std::rand() % 10;
        arr[i] = baseValue + offset;
    }
    return arr;
}

int selectNonExistingValueFromArray(const int *arr, int size)
{
    if (size < 2)
    {
        return arr[0] + 1;
    }
    else if (size == 2)
    {
        if (abs(arr[0] - arr[1]) > 1)
        {
            return std::min(arr[0], arr[1]) + 1 + (std::rand() % (std::max(arr[0], arr[1]) - std::min(arr[0], arr[1]) - 1));
        }
        else
        {
            return std::max(arr[0], arr[1]) + (std::rand() % 3);
        }
    }

    int randomIndex = std::rand() % (size - 1);
    int smallElement = arr[randomIndex];
    int largeElement = arr[randomIndex + 1];

    if (largeElement - smallElement > 1)
    {
        return smallElement + 1 + (std::rand() % (largeElement - smallElement - 1));
    }
    return arr[size - 1] + (std::rand() % 10) + 1;
}

int main()
{

    const int START_POWER = 3;
    const int END_POWER = 15;
    int REPETITION_COUNT = 50000;

    std::srand(std::time(0));

    std::cout << "Test Results" << std::endl;
    std::cout << "N \t K \t Linear (ms) \t Binary (ms) \t Jump (ms)" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    for (int p = START_POWER; p <= END_POWER; p++)
    {
        int N = std::pow(2, p);

        int *sheepArray = createSortedRandomArray(N);
        int keyValue = selectNonExistingValueFromArray(sheepArray, N);

        int kValues[] = {1, N / 8, N / 4, N / 2};

        for (int K : kValues)
        {
            if (K == 0)
            {
                K = 1;
            }

            double linearDuration = 0.0;
            double binaryDuration = 0.0;
            double jumpDuration = 0.0;

            // Algorithm with Linear Search Test
            clock_t startTime = clock();
            for (int i = 0; i < REPETITION_COUNT; i++)
            {
                int *resultPointer = linearSearchFindClosest(sheepArray, N, K, keyValue);
                delete[] resultPointer;
            }
            linearDuration = 1000.0 * (clock() - startTime) / CLOCKS_PER_SEC / REPETITION_COUNT;

            // Algorithm with Binary Search Test
            startTime = clock();
            for (int i = 0; i < REPETITION_COUNT; i++)
            {
                int *resultPointer = binarySearchFindClosest(sheepArray, N, K, keyValue);
                delete[] resultPointer;
            }
            binaryDuration = 1000.0 * (clock() - startTime) / CLOCKS_PER_SEC / REPETITION_COUNT;

            // Algorithm with Jump Search Test
            startTime = clock();
            for (int m = 0; m < REPETITION_COUNT; ++m)
            {
                int *resultPointer = jumpSearchFindClosest(sheepArray, N, K, keyValue);
                delete[] resultPointer;
            }
            jumpDuration = 1000.0 * (clock() - startTime) / CLOCKS_PER_SEC / REPETITION_COUNT;

            std::cout << N << "\t " << K << "\t "
                      << std::fixed << std::setprecision(6) << linearDuration << "\t "
                      << std::fixed << std::setprecision(6) << binaryDuration << "\t "
                      << std::fixed << std::setprecision(6) << jumpDuration << std::endl;
        }

        delete[] sheepArray;
    }
}