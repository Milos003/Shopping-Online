# Assignment 3 - Electronic Shopping Process

## Introduction

In Assignment 3 (A3) of the ESP practicals (KU), you will implement a program that manages and organizes an electronic shopping list.
Please make sure that you follow the assignment description exactly, because even slight differences can cause 
testcases to fail.

This document describes the structure of the assignment and the expected functionality of the program.

## Learning Goals

Memory Management/Heap

## Specifications

Some general specifications must be followed for every assignment in this course. A list of these specifications can be found here:
[Assessment of Assignments - Deductions](https://www.notion.so/coding-tugraz/Assessment-of-Assignments-How-do-you-get-your-points-d7cca6cc89a344e38ad74dd3ccb73cb3?pvs=4#e3203e50b1fc4ba787bdbf5fb46262ae).
Please follow these specifications to avoid point deductions. As **memory management** is a central learning goal of 
this assignment, pay close attention to this section within the specifications.

Additionally, the following specifications must be followed for this assignment (A3) as well:

* **Attention:** `malloc()` (or `calloc()`), `realloc` and `free()` must be used. The shopping list name, the shopping list itself (= list of items), and all item names **must** be stored on the heap. If these strings/list are not stored on the heap, this will result in a deduction of **up to -25 %**.
* **Attention:** Your program must be able to handle inputs of arbitrary length. If this is not the case, this will result in a deduction of **up to -25 %**.

## Grading

Assignment 3 is worth **18 points**.

Information on how your assignment submission will be assessed can be found here: [Assessment of Assignments](https://www.notion.so/coding-tugraz/Assessment-of-Assignments-How-do-you-get-your-points-d7cca6cc89a344e38ad74dd3ccb73cb3).
Please read this carefully, as it also contains guidelines on what your final code should look like (Coding Standard, Style Guide).

Here you can find an overview of how your total grade for the KU will be calculated: [Procedure and Grading](https://www.notion.so/coding-tugraz/Procedure-and-Grading-59975fee4a9c4047867772cd20caf73d)

## Submission

- Deliverables: `a3.c`
- Push to your repository
- **Deadline: 11.12.2024, 23:59 (Austrian time)**

## Weekly Exercises

There are **Weekly Exercises** associated with this assignment. These exercises are provided on the
[onlineGDB](https://www.onlinegdb.com/) website.
These are simple exercises meant to help you practice before starting the assignment, and **must** be solved at least
partially to avoid deductions. Take a look at our [Guide for onlineGDB](https://www.notion.so/coding-tugraz/Guide-for-onlineGDB-c8a3d7e6b5d24b569a6f85593c0c9d75) for information on how to
register and solve the exercises.

**Please pay close attention to the instructions about choosing a username!** If you
do not use the correct username, we won't be able to identify your solutions.

- **Attention**: It is mandatory to correctly solve at least 50 % of the exercises tagged with [A3] before the A3
  deadline. Otherwise, you will receive a **point deduction of -25 % on A3**.

## Assignment Description

This program implements a basic shopping list management system. 
Initially, the user is prompted to enter the name of the shopping list. 
After that, the program waits for input of the name and quantity of each item. 
This process continues until the user terminates the program with a command.

### General Notes

The notes given in this section are important for the entire assignment description:

- `\n` shouldn't be printed as separate characters, instead they represent the newline character.
- Note the leading and trailing spaces in the text fields! You can make them visible by selecting the text field.
- Words in angle brackets (such as `<SHOPPING_LIST_NAME>`) should be replaced by calculated or given data. They are 
  **not** part of the output itself! For a better understanding, you can look at the [example output](#example-output) at the very 
  bottom of this document.
- <code>&nbsp;>&nbsp;</code> (command prompt, always printed with a leading and trailing space) in the output indicates that the program should wait for user input at this point. Execution should only continue after the user has ended their input with `ENTER`.
- Make sure that your program can handle inputs of arbitrary length including empty inputs (see also the 
  specifications).
- If the user's input is invalid, the corresponding error message should be printed. After this, the same question 
  is asked again, the command prompt is printed, and the user can make a new input. This process is repeated as long as the input is invalid.
- Any time the program waits for user input, `quit` should be a valid input. If the user enters `quit`, the program 
  should terminate with the return value `0` without printing anything else. Take care to free all previously allocated 
  memory!
- Whitespaces are always part of the input (<code>&nbsp;quit&nbsp;</code> is not the same as `quit`).
- The user input (including commands) is **case-sensitive**, meaning `quit` is a valid input, but `QUIT` or `qUiT` are not.
- Take care with your memory management! That means that when allocating memory on the heap, you always need to 
  check that the system was able to provide that memory. If the program runs out of memory you should first free all 
  memory previously allocated on the heap, then print the correct error message and terminate the program with the 
  corresponding return value (see [Return Values and Error Messages](#return-values-and-error-messages)).
- **Unlike in Assignment 2, you are allowed to use the `string.h` standard library for Assignment 3.**

## Program Sequence

<details><summary><h3>Welcome Message</h3></summary>

At the beginning of the program, the user is welcomed with the following message:

```
\n
Welcome to the\n
Electronic Shopping Process!\n
\n
```

</details>

<details><summary><h3>Shopping List Name</h3></summary>


After printing the welcome message, the user is asked to input the name of the shopping list, which will be used in 
the final output.
The user should be asked the following question:

```
What do you want to name your shopping list?\n
 > 
```

At this point the user should type in a valid name. The shopping list cannot be called:

- `quit` without any whitespaces — this should terminate the program
- `<EMPTY>` — the name is not allowed to be empty

> **Note:** Keep in mind that all whitespaces are kept as part of the input.

> **Note:** Non-printable characters will not be tested and do not have to be handled.

The name of the shopping list can be any length (except 0) and must be stored on the heap.

If the user enters an empty shopping list name the appropriate error message from the 
[Return Values and Error Messages](#return-values-and-error-messages) section should be printed. After the error message, the question and the command
prompt is printed again and the user can make a new input. This process is repeated as long as the input is invalid.

</details>

<details><summary><h3>Input of the Shopping List Items</h3></summary>

Next, the user can add items to the shopping list. Items are added until one of the following conditions is met:

- the command `quit` without any whitespaces is typed in, in which case the program should be terminated without printing anything
- the command `done` is entered, which then prints the list and terminates the program. `done` can only be entered 
  while entering the item name but **not** while entering the item quantity
- the program encounters a memory allocation error

In this phase, the program prompts the user for an item name and quantity to be added to the list, validates the input, and adds it to the list. This continues until one of the above conditions is met.

For each item the following message is printed:

```
\nItem <COUNTER>:\n
```
`<COUNTER>` indicates which number item will be added, starting with 1 (i.e., Item 1, Item 2, Item 3, ...).

<details><summary><h4>Item Name</h4></summary>

Next the user is asked to enter an item name:
```
What do you want to add?\n
 > 
```

The program reads in a string and checks if the input is empty, in which case it should print 
the appropriate error message from the [Return Values and Error Messages](#return-values-and-error-messages) section.
After the error message, the question and the command prompt is printed again and the user can make a new input.
This process is repeated as long as the input is invalid.

Valid inputs are:
- the command `quit` without any whitespaces, which terminates the program without printing anything
- the command `done` without any whitespaces, which ends the item adding phase of the program and goes into printing 
  the shopping list
- any other input of arbitrary length > 0, which is then used as the name of the next item

> **Attention**: All item names must be stored on the heap.

> **Note:** Non-printable characters will not be tested and do not have to be handled.

</details>

<details><summary><h4>Item Quantity</h4></summary>

After getting a valid item name, the quantity is required. The following question is printed:

```
How many pieces/grams/milliliters of this item do you want to get?\n
 > 
```

Valid inputs are:
- the command `quit` without any whitespaces, which terminates the program without printing anything
- integers larger than `0`
  - An integer in this case is defined as a sequence of only numerical characters with optionally a leading `+` or 
    `-` without whitespaces (e.g. `123`, `+123`, `-123` are integers). 
  - If the input does not match this pattern, the input does not count as an integer for this program, and the 
    corresponding error message `[ERROR] The quantity must be an integer!\n\n` should be printed.
  - If the integer matches this pattern, but is smaller than or equal to `0`, the error message `[ERROR] The quantity 
    must be greater than 0!\n\n` should be printed.

> **Hint:** You can use the `atoi` function to convert a string to an integer, but be aware that you might need to 
> do some checks beforehand.

If the user enters something that is not `quit` or an integer, or the integer is less or equal to `0`, the 
appropriate error message ([Return Values and Error Messages](#return-values-and-error-messages)) should be printed.   
After the error message, the question and the command prompt is printed again and the user can make a new input.
This process is repeated as long as the input is invalid.

</details>

After the user inputs a valid item name and quantity, the program should continue to prompt for the next item until the `done` command is entered at which point the program should print the shopping list.

</details>

<details><summary><h3>Printing the Shopping List</h3></summary>

This phase is reached when `done` is entered. Here the constructed shopping list is printed out, the previously allocated memory is freed and the program should terminate.


The shopping list should be printed in the following format:

```
\n
Shopping list: <SHOPPING_LIST_NAME>\n
 * <QUANTITY> <ITEM_NAME>\n
 * <QUANTITY> <ITEM_NAME>\n
 <...>
```

`<SHOPPING_LIST_NAME>` should be replaced by the name of the shopping list given in the beginning of the execution. 
Next, all items on the list are printed **sorted by the ASCII values of their names in ascending order**. This means 
that first they should be sorted by the first character of the name, then, if that is the same, by the second 
character, and so on. **If two item names are exactly the same, the items should additionally be sorted by their 
quantity in ascending order.**

`<QUANTITY>` should be replaced by quantity the user entered. `<ITEM_NAME>` should be replaced by the item name the user entered.

After printing the list the program should free all resources and terminate with the corresponding exit code.

</details>

### Return Values and Error Messages

The program has to react to errors during the game and print the corresponding error messages and/or return the correct
return values. You can find all error messages that should be printed and all return values in the table below.

Only one error should be printed at once. If multiple errors occur at the same time, only the highest message in the below table should be printed.

| Return Value | Error Message                                      | Meaning                                                             |
|--------------|----------------------------------------------------|---------------------------------------------------------------------|
| 0            | -                                                  | The program terminated successfully (user entered `quit` or `done`) |
| 1            | `[ERROR] Memory allocation failed!\n\n`            | The program was not able to allocate new memory                     |
|              | `[ERROR] The name cannot be empty!\n\n`            | The shopping list name input was empty                              |
|              | `[ERROR] The quantity must be an integer!\n\n`     | The item quantity input was not an integer and not `quit`           |
|              | `[ERROR] The quantity must be greater than 0!\n\n` | The item quantity input was an integer less or equal to `0`         |
|              | `[ERROR] Item name cannot be empty!\n\n`           | The item name input was empty                                       |

## Example Output

<details>
<summary><h4>Example</h4></summary>

```

Welcome to the
Electronic Shopping Process!

What do you want to name your shopping list?
 > Weekly shopping list: 5th December 2024 - 11th December 2024

Item 1:
What do you want to add?
 > apples
How many pieces/grams/milliliters of this item do you want to get?
 > 5

Item 2:
What do you want to add?
 > bananas
How many pieces/grams/milliliters of this item do you want to get?
 > 3

Item 3:
What do you want to add?
 > oranges
How many pieces/grams/milliliters of this item do you want to get?
 > 4

Item 4:
What do you want to add?
 > tomatoes
How many pieces/grams/milliliters of this item do you want to get?
 > 10

Item 5:
What do you want to add?
 > done

Shopping list: Weekly shopping list: 5th December 2024 - 11th December 2024
 * 5 apples
 * 3 bananas
 * 4 oranges
 * 10 tomatoes
```

</details>
