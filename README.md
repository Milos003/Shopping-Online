# Electronic Shopping Process (Assignment 3)

This program implements a terminal-based shopping list manager for the ESP course.

## 📋 What the Program Does

- Prompts the user to name a shopping list
- Lets the user add items with names and quantities
- Input continues until `done` is typed
- Allows quitting at any time with the command `quit`
- Finally, prints a sorted shopping list (by name, then quantity)

## ✅ Features

- All strings and data are stored on the heap
- Input is validated:
  - Empty names not allowed
  - Quantity must be a valid integer > 0
- Memory is fully freed before exiting
- Commands are case-sensitive and must be exact (`quit`, `done`)
