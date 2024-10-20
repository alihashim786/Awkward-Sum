/*
Name: Ali Hashim
Student-ID: 22i-0554
Assignment: 01
*/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int sumComb(int arr[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        bool isDuplicate = false;
        for (int j = 0; j < i; j++)
        {
            if (arr[i] == arr[j])
            {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate)
        {
            sum += arr[i];
        }
    }
    return sum;
}

// checks the number is prime or not
bool checkPrime(int num)
{
    if (num < 1)
    {
        return false; // considering 1 as prime number too
    }
    // the condition i*i<=num is to reduce the itterations and improving algorithm efficiency. However we can use condition "i < num".
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int findSum(int **grid, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (grid[i][j] != 0)
            { // without this we can calcuate sum but put this to improve efficiency of program
                sum += grid[i][j];
            }
        }
    }
    return sum;
}

int main()
{

    int size;
    cout << "\n( -> Enter size = 7 if you want to read numbers from file <- )\n";
    cout << "Enter the size of the grid ( * size should be between 5 and 9 * ) : ";

    // the "goto" statment also works like this
    while (true)
    {
        cin >> size;
        if ((size >= 5) && (size <= 9))
        {
            break;
        }
        cout << "Size should be in range 5-9. Enter again : ";
    }

    int combinationsum = 0, largestCombSize = 0, largestCombSum = 0, maxRowComb = 0, maxColComb = 0, maxRowConsectivePrime = 0, maxColConsectivePrime = 0;

    // makin 2D pointer array to store the random values and dynamically allocating memory
    int **grid = new int *[size];
    for (int i = 0; i < size; i++)
    {
        grid[i] = new int[size];
    }

    int input;
    cout << "\n\n1. Generate Random Numbers\n2. Read numbers from file\n3. Exit\n\n-> Enter input :  ";

    while (true)
    {
        cin >> input;
        if (input == 1)
        {
            srand(time(0));
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    grid[i][j] = 1 + (rand() % 99);
                }
            }

            break;
        }

        else if (input == 2)
        {

            // Read the numbers from the file
            std::ifstream file("Grid.txt");
            if (file.is_open())
            {
                std::string line;
                int row = 0;
                while (std::getline(file, line))
                {
                    std::istringstream iss(line);
                    int col = 0;
                    int num;
                    while (iss >> num)
                    {
                        grid[row][col] = num;
                        col++;
                    }
                    row++;
                }
                file.close();
            }
            else
            {
                std::cout << "Error: Failed to open the file." << std::endl;
                return 1;
            }

            break;
        }

        if (input == 3)
        {
            exit(0);
            return 0;
        }

        else
        {
            std::cout << "Invalid input. Enter again : ";
        }
    }

    // makin 2D pointer array to store the numbers which are part of any combination and dynamically allocating memory
    int **combinations = new int *[size];
    for (int i = 0; i < size; i++)
    {
        combinations[i] = new int[size];
    }
    // now intializing the indexes of cmbinations array with 0.
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            combinations[i][j] = 0;
        }
    }

    // makin 2D pointer array to store the numbers which are not part of any of combination and dynamically allocating memory
    int **noncombinations = new int *[size];
    for (int i = 0; i < size; i++)
    {
        noncombinations[i] = new int[size];
    }
    // now intializing the indexes of noncombinations array with 0.
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            noncombinations[i][j] = 0;
        }
    }

    cout << "\nThe Grid assigned with Random values : \n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << grid[i][j] << "   ";
        }
        cout << endl;
    }

    // Finding combinations of consecutive prime numbers.

    // Horizontal combinations
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 2; j++)
        {
            int consecutiveCount = 0;
            /*moves like [0][0] then [0][1] then [0][2] then [0][3] and so on until last index.
            "j + consecutiveCount < size" is for when we approac t last index the loop wil be terminated*/
            while ((j + consecutiveCount < size) && (checkPrime(grid[i][j + consecutiveCount])))
            {
                consecutiveCount++;
            }
            if (consecutiveCount >= 3)
            { // we will enter in this statement when at least 3 consecutive prime numbers are identfied

                int *arraycomb = new int[consecutiveCount]; // array to store every combination of every row

                for (int k = j; k < j + consecutiveCount; k++)
                {
                    combinations[i][k] = grid[i][k];

                    // storing the numbers which are in combiation
                    arraycomb[k - j] = grid[i][k];
                }
                /*the numbers in grid[i][k] are those  which are indentified in combination . like if i=1 tha   means
               we are checking 1st rows now and all consecutive prime there will be stored in the same indices in "combinations" array*/
                int temp = sumComb(arraycomb, consecutiveCount);
                combinationsum = combinationsum + temp;

                // Update the largest combination size and sum
                if (consecutiveCount > largestCombSize)
                {
                    largestCombSize = consecutiveCount;
                    maxRowComb = i;                           // Variable to store the row number with the maximum number of combinations
                    maxRowConsectivePrime = consecutiveCount; // this variable will store the maximum number of  combinations in rows
                    largestCombSum = temp;
                }

                delete[] arraycomb;
            }

            j += consecutiveCount;
        }
    }

    //  Vertical combinations
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size - 2; i++)
        {
            int consecutiveCount = 0;
            /*moves like [0][0] then [1][0] then [2][0] then [3][0] and so on until last index.
            "i + consecutiveCount < size" is for when we approach the last index the loop wil be terminated*/
            while ((i + consecutiveCount < size) && (checkPrime(grid[i + consecutiveCount][j])))
            {
                consecutiveCount++;
            }
            if (consecutiveCount >= 3)
            {
                int *arraycomb = new int[consecutiveCount]; // to store every combination of every column
                for (int k = i; k < i + consecutiveCount; k++)
                {

                    combinations[k][j] = grid[k][j];
                    // storing the numbers which are in combiation
                    arraycomb[k - i] = grid[k][j];
                }
                int temp = sumComb(arraycomb, consecutiveCount);
                combinationsum = combinationsum + temp;

                // Update the largest combination size and sum

                /*here i am putting = with > only because if there is any row or column in a grid having same number of consecutive prime numbers
                then it should check has which combination has a greater sum, the combination which has greater sum will be declared as te largest
                combination in the grid */
                if (consecutiveCount >= largestCombSize)
                {
                    largestCombSize = consecutiveCount;
                    maxColComb = j;                           // Variable to store the column number with the maximum number of combinations
                    maxColConsectivePrime = consecutiveCount; // this variable will store the maximum number of  combinations in columns

                    // we will come here only if there is equal or grater   "largeCombSize" as compared to previously checked in rows
                    if (temp > largestCombSum)
                    {
                        largestCombSum = temp; // now the sum stored in temp will be given to largestCombSum
                    }
                }

                delete[] arraycomb;
            }
            i += consecutiveCount;
        }
    }

    // Diagonal combinations (top-left to bottom-right)
    for (int i = 0; i < size - 2; i++)
    {
        for (int j = 0; j < size - 2; j++)
        {
            int consecutiveCount = 0;
            /* moves like [0][0] then [1][1] then [2][2] then [3][3] and so on until last index.
            "i + consecutiveCount < size" is for when we approach the last index the loop wil be terminated */
            while ((i + consecutiveCount < size) && (j + consecutiveCount < size) && (checkPrime(grid[i + consecutiveCount][j + consecutiveCount])))
            {
                consecutiveCount++;
            }
            if (consecutiveCount >= 3)
            {

                int *arraycomb = new int[consecutiveCount]; // to store every combination of every diagonal

                for (int k = 0; k < consecutiveCount; k++)
                {

                    combinations[i + k][j + k] = grid[i + k][j + k];
                    // storing the numbers which are in combination in diagonal
                    arraycomb[k] = grid[i + k][j + k];
                }

                int temp = sumComb(arraycomb, consecutiveCount);
                combinationsum = combinationsum + temp;

                // Update the largest combination size and sum
                if (consecutiveCount >= largestCombSize)
                {
                    largestCombSize = consecutiveCount;
                    // we will come here only if there is equal or grater  "largeCombSize"as compared to previously checked in rows and columns
                    if (temp > largestCombSum)
                    {
                        largestCombSum = temp; // now the sum stored in temp will be given to largestCombSum
                    }
                }

                delete[] arraycomb;
            }
        }
    }

    // Diagonal combinations (bottom-left to top-right) because its same that whether we move from top-right to bottom-left or bottom-left to top-right
    for (int i = size - 1; i >= 2; i--)
    {
        for (int j = 0; j < size - 2; j++)
        {
            int consecutiveCount = 0;
            /* if size =5 it moves like [4][0] then [3][1] then [2][2] then [1][3] and then at last [0][4].
            "i + consecutiveCount < size" is for when we approach the last index the loop wil be terminated */
            while ((i - consecutiveCount >= 0) && (j + consecutiveCount < size) &&
                   (checkPrime(grid[i - consecutiveCount][j + consecutiveCount])))
            {
                consecutiveCount++;
            }
            if (consecutiveCount >= 3)
            {

                int *arraycomb = new int[consecutiveCount]; // to store every combination of every diagonal

                for (int k = 0; k < consecutiveCount; k++)
                {
                    // grid[i - k][j + k] = 0;
                    combinations[i - k][j + k] = grid[i - k][j + k];

                    arraycomb[k] = grid[i - k][j + k];
                }

                int temp = sumComb(arraycomb, consecutiveCount);
                combinationsum = combinationsum + temp;

                // Update the largest combination size and sum
                if (consecutiveCount >= largestCombSize)
                {
                    largestCombSize = consecutiveCount;
                    // we will come here only if there is equal or grater  "largeCombSize" as compared to previously checked in rows and columns
                    if (temp > largestCombSum)
                    {
                        largestCombSum = temp; // now the sum stored in temp will be given to largestCombSum
                    }
                }

                delete[] arraycomb;
            }
        }
    }

    cout << endl
         << endl;

    // The array the contains the numbers which are part of any combination and its remainig indices are filled with zeros.
    cout << "The combinations found in grid : \n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << combinations[i][j] << "   ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Remaining numbers which are not part of any combination : \n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            /*in combinations array if the index =0 that means that index in our origial grid has a number which is not the part
            of any combination so I will store that number in another array on that specific index*/
            if (combinations[i][j] == 0)
            {
                noncombinations[i][j] = grid[i][j];
            }
            cout << noncombinations[i][j] << "   ";
        }
        cout << endl;
    }
    cout << endl;
    int choice;
mainmenu:
    cout << "\n        Main Menu\n\nWhich information you would like to retrieve:\n1. largest combination\n2. Row or Column with the most combinations\n";
    cout << "3. Sum of all combinations and the remaining non-combination numbers\n4. Exit\n\n-> Enter choice : ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "\n\" The Largest Combination is based on the number of consecutive prime numbers \"\n\n";
        cout << "| If the largest number of consecutive prime numbers in any row or column or diagonal is same then the  Combination |\n";
        cout << "| which has greater sum amongst the Largest combinations found is considerd as the Final Largest Combiation.        |\n\n";
        cout << "-> The size of the largest combination is : " << largestCombSize << endl;
        cout << "-> The sum of the values in largest combination  is : " << largestCombSum << endl;
        cout << "\nPress 0 to go back to main menu : ";
        int inp; // this inp has a scope in "if" only
        cin >> inp;
        if (inp == 0)
        {
            goto mainmenu;
        }
        else
        {
            cout << "INVALID INPUT\n";
            goto mainmenu;
        }
    }

    else if (choice == 2)
    {

        int maxRowCombinations = 0;
        /* like if there are 5 consecutive prime numbers in a row that there are 6 combinations of prime numbers found because there will be
        three combinations of three consecutive prime numbers two combinations of four consecutive prime numbers and one combination of five
        consecutive prime numbers. The same like if there are 7 sonsecutive prime numbers that means there are 15 combinations of prime numbers */
        for (int i = maxRowConsectivePrime - 2; i >= 1; i--)
        {
            maxRowCombinations += i;
        }

        int maxColCombinations = 0;
        for (int i = maxColConsectivePrime - 2; i >= 1; i--)
        {
            maxColCombinations += i;
        }

        if (maxRowCombinations > maxColCombinations)
        {
            cout << "\nRow with the most combinations: Row " << maxRowComb + 1 << " with " << maxRowCombinations << " combinations." << endl;
        }
        else if (maxRowConsectivePrime == maxColConsectivePrime)
        {
            cout << "\nRow with the most combinations: Row " << maxRowComb + 1 << " with " << maxRowCombinations << " combinations." << endl;
            cout << "Column with the most combinations: Column " << maxColComb + 1 << " with " << maxColCombinations << " combinations." << endl;
        }
        else
        {
            cout << "\nColumn with the most combinations: Column " << maxColComb + 1 << " with " << maxColCombinations << " combinations." << endl;
        }

        cout << "\nPress 0 to go back to the main menu : ";
        int inp;
        cin >> inp;
        if (inp == 0)
        {
            goto mainmenu;
        }
        else
        {
            cout << "INVALID INPUT\n";
            goto mainmenu;
        }
    }

    else if (choice == 3)
    {
        /*
In "cominationsum"there is a sum of all the combinations. Like if there are five combinatios identified then I have calculated the sum of the
values in each combinations and if any value is repeating in any combination it is not added twice. Then i added the sum of the values of all
combibations in one variable
*/
        cout << "\n-> The sum of all the values in the identified combinations (same numbers in combination are not added twice) : " << combinationsum << endl;

        int sum = findSum(noncombinations, size);
        cout << "-> The sum of all the values which ae not in any combination : " << sum << endl;
        cout << "\nPress 0 to go back to main menu : ";
        int inp;
        cin >> inp;
        if (inp == 0)
        {
            goto mainmenu;
        }
        else
        {
            cout << "INVALID INPUT\n";
            goto mainmenu;
        }
    }

    else if (choice == 4)
    {
        cout << "\nExiting the Portal...\n\n";

        exit(0); // will terminate the program
    }

    else
    {
        cout << "\nInvalid Input\n";
        goto mainmenu;
    }

    // Deallocate memory
    for (int i = 0; i < size; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;

    for (int i = 0; i < size; i++)
    {
        delete[] combinations[i];
    }
    delete[] combinations;

    for (int i = 0; i < size; i++)
    {
        delete[] noncombinations[i];
    }
    delete[] noncombinations;

    return 0;
}