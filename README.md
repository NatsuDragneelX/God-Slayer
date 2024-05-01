# God-Slayer
CSC 3380 Calculator project

* Open the calculator code file in Visual Studio Code.
* Visual Studio Code will automatically create a terminal window at the file's location.
* Use this terminal window to run and test your code.

* This advanced calculator is capable of performing basic arithmetic operations such as addition, subtraction, multiplication, division, and modulus on both positive and negative values.
* It features a table of predefined mathematical constants, including pi, e, i, square root of 2 and 3, tau, phi, and a recursive Fibonacci sequence. These constants can be invoked directly in the calculations.
* To use the calculator, input any valid mathematical expression. For instance, `pi%5;`. The console will then display the result of the provided expression.
* Please note that every equation must be terminated with a semicolon (`;`). Failure to do so will result in a compilation error.

**Test Case 1: Basic Arithmetic Operations**
Input: 3 + 4;
Expected Output: 7
Input: 10 - 2;
Expected Output: 8
Input: 5 * 6;
Expected Output: 30
Input: 20 / 5;
Expected Output: 4

**Test Case 2: Handling Mathematical Constants**
Input: pi;
Expected Output: 3.14159 (approximately)
Input: tau / 2;
Expected Output: 3.14159 (approximately, since tau is 2𝜋2π)

**Test Case 3: Variable Assignment and Retrieval**
Input: x = 5;
Expected Output: 5 (assignment should return the assigned value)
Input: x;
Expected Output: 5 (previously assigned value)

**Test Case 4: Complex Expressions**
Input: 3 + 4 * 5;
Expected Output: 23 (testing order of operations)
Input: (3 + 4) * 5;
Expected Output: 35 (testing parenthesis impact on order of operations)

**Test Case 5: Division by Zero Handling**
Input: 10 / 0;
Expected Output: Runtime error: Divide by zero

**Test Case 6: Modulo Operation**
Input: 10 % 3;
Expected Output: 1
Input: 18 % 4;
Expected Output: 2

**Test Case 7: Error Handling for Uninitialized Variables**
Input: y;
Expected Output: Runtime error: Undefined variable: y

**Test Case 8: Using Constants in Expressions**
Input: pi * 2;
Expected Output: 6.28318 (approximately)

**Test Case 9: Mathematical Functions**
Input: sqrt(16);
Expected Output: 4
Input: exp(1);
Expected Output: 2.71828 (approximately)
Input: log(e);
Expected Output: 1

**Test Case 10: Nested Function Calls**
Input: sqrt(25) + exp(log(4));
Expected Output: 7 (since exp(log(4)) simplifies to 4)

**Test Case 11: Error Handling for Functions**
Input: sqrt(-1);
Expected Output: Runtime error: Square root of negative number
Input: log(0);
Expected Output: Runtime error: Logarithm of non-positive number

**Test Case 12: Quitting the Program**
Input: q;
Expected Output: Quits the program (The program should terminate without outputting additional text after q;)


**OutPut Result:**

Enter expression (add ; to end, q to quit): 3 + 4;
Result: 7
Enter expression (add ; to end, q to quit): 10 - 2;
Result: 8
Enter expression (add ; to end, q to quit): 5 * 6;
Result: 30
Enter expression (add ; to end, q to quit): 20 / 5;
Result: 4
Enter expression (add ; to end, q to quit): pi;
Result: 3.14159
Enter expression (add ; to end, q to quit): tau / 2;
Result: 3.14159
Enter expression (add ; to end, q to quit): x = 5;
Result: 5
Enter expression (add ; to end, q to quit): x;
Result: 5
Enter expression (add ; to end, q to quit): 3 + 4 * 5;
Result: 23
Enter expression (add ; to end, q to quit): (3 + 4) * 5;
Result: 35
Enter expression (add ; to end, q to quit): 10 / 0;
Error: Divide by zero
Enter expression (add ; to end, q to quit): 10 % 3;
Result: 1
Enter expression (add ; to end, q to quit): 18 % 4;
Result: 2
Enter expression (add ; to end, q to quit): y;
Error: Undefined variable: y
Enter expression (add ; to end, q to quit): pi * 2;
Result: 6.28319
Enter expression (add ; to end, q to quit): sqrt(16);
Result: 4
Enter expression (add ; to end, q to quit): exp(1);
Result: 2.71828
Enter expression (add ; to end, q to quit): log(e);
Result: 1
Enter expression (add ; to end, q to quit): sqrt(25) + exp(log(4));
Result: 9
Enter expression (add ; to end, q to quit): sqrt(-1);
Error: Square root of negative number
Enter expression (add ; to end, q to quit): log(0);
Error: Logarithm of non-positive number