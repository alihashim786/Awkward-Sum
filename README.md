# Awkward-Sum
 working on a programming problem involving pointers and DMAs (Dynamic  Memory Allocation). OOP concepts  C++ Task

## <img src="https://img.icons8.com/ios/50/000000/email-open.png" width="20"/> Contact:
If you have any queries, feel free to email me at [muhammadalihashim514@gmail.com](mailto:muhammadalihashim514@gmail.com) or [i220554@nu.edu.pk](mailto:i220554@nu.edu.pk).

Feel free to connect with me on [LinkedIn](https://www.linkedin.com/in/muhammad-ali-hashim-5115882b4) to stay in touch and network.


 # Find the Awkward Sum

This project tasks you with creating a dynamic 2D grid of variable size (5 to 9) and populating it with random values between 1 and 99. Your primary goal is to identify combinations of consecutive prime numbers (at least three in a row), which can occur **horizontally, vertically, or diagonally**. Additionally, you’ll calculate various statistics based on these combinations and the remaining grid numbers.

## Features
- **Grid Creation**: 
  - User-defined size between 5 to 9.
  - Populated with random values from 1 to 99.
  
- **Combination Identification**: 
  - Detect consecutive prime number sequences in rows, columns, or diagonals.
  - A number can be part of multiple combinations.

- **Statistics**: 
  - Largest combination (size and sum).
  - Row or column with the most combinations.
  - Sum of all combinations and remaining numbers not part of any combination.

## Menu Options
1. **Generate Random Numbers**: Create a random grid with user-specified size.
2. **Read from File (Bonus)**: Load a 7x7 grid from a text file and process it.
3. **View Statistics**:
   - Largest combination (size and sum).
   - Row/Column with the most combinations.
   - Sum of all combinations and remaining numbers.
4. **Exit**: Close the program.

## Example Workflow
- **Grid Example**: Random values are assigned to the grid.
    ```
    52   23   42   11   6   9   98
    99   64   6    7    89  44  15
    13   11   17   20   54  64  89
    ...
    ```

- **Prime Combinations Found**:
    ```
    13   11   17
    ```
  
- **Remaining Numbers**: Numbers not part of any combination:
    ```
    52   23   42   11   6   9   98
    ```

## Bonus Challenge
In case of a **7x7 grid**, the user can choose to read numbers from a file instead of generating random values. This adds an extra layer of complexity and allows testing with pre-defined data.

## How to Use
1. Input the grid size (between 5 and 9).
2. Generate random numbers or read from a file.
3. Use the menu to:
   - View the largest combination.
   - Find the row/column with the most combinations.
   - Calculate the sum of all combinations and non-combination numbers.

## Contributing
Contributions are welcome! Feel free to open issues or submit pull requests to improve the project.

