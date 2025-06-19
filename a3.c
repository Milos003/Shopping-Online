//---------------------------------------------------------------------------------------------------------------------
// <This program simulates a simple electronic shopping process>
// <At the start, the user is asked to input the name of the shopping list>
// <Afterwards, the user inputs item names and their quantities, and the shopping list is printed out>
// <The program ends when the user inputs "done" or "quit">
// <Item names and quantities have specific rules for handling and input validation>
// <The main goal of this assignment is memory allocation with "malloc", "calloc", "realloc", and "free">
//
// Tutor: <Hannah Weberbauer>
//
// Milos Dukaric: <12225387>
//---------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------------------------------------------------------------------
/// Very basic welcome message function
/// @return void function
//---------------------------------------------------------------------------------------------------------------------
void welcomeMessage(void)
{
  printf("\nWelcome to the\nElectronic Shopping Process!\n\n");
}

//---------------------------------------------------------------------------------------------------------------------
/// Function to allow the user to enter the name of the shopping list
/// The name is saved on the heap
/// @return shopping_list_name
//---------------------------------------------------------------------------------------------------------------------
char *shoppingListName(void)
{
  char *shopping_list_name = NULL;
  char buffer[1024];
  size_t length;

  while (1)
  {
    printf("What do you want to name your shopping list?\n > ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
      return NULL;
    }

    length = strlen(buffer);
    if (buffer[length - 1] == '\n')
    {
      buffer[length - 1] = '\0';
      length--;
    }

    if (strcmp(buffer, "") == 0)
    {
      printf("[ERROR] The name cannot be empty!\n\n");
    }
    else if (strcmp(buffer, "quit") == 0)
    {
      return NULL;
    }
    else
    {
      shopping_list_name = malloc(length + 1);
      if (shopping_list_name == NULL)
      {
        printf("[ERROR] Memory allocation failed!\n\n");
        return NULL;
      }
      strcpy(shopping_list_name, buffer);
      break;
    }
  }

  return shopping_list_name;
}

//---------------------------------------------------------------------------------------------------------------------
/// Function to validate the quantity input
/// Ensures the quantity is an integer and prints error messages for invalid inputs
/// @param input Pointer to the string representing the quantity
/// @return value
//---------------------------------------------------------------------------------------------------------------------
int validateQuantity(const char *input)
{
  const char *original_input = input;

  while (*input == ' ' || *input == '\t')
  {
    input++;
  }

  if (input != original_input)
  {
    printf("[ERROR] The quantity must be an integer!\n\n");
    return -1;
  }

  if (*input == '\0')
  {
    printf("[ERROR] The quantity must be an integer!\n\n");
    return -1;
  }

  char *end;
  int value = strtol(input, &end, 10);

  if (*end != '\0' || end == input)
  {
    printf("[ERROR] The quantity must be an integer!\n\n");
    return -1;
  }

  if (value <= 0 || (input[0] == '0' && input[1] != '\0'))
  {
    printf("[ERROR] The quantity must be greater than 0!\n\n");
    return -2;
  }

  return value;
}

//---------------------------------------------------------------------------------------------------------------------
/// Function to add items to the shopping list
/// Dynamically allocates memory for the list and allows user input for item names and quantities
/// @param item_count Pointer to an integer 
/// @return items
//---------------------------------------------------------------------------------------------------------------------
typedef struct {
  char *name;
  int quantity;
} ShoppingItem;

ShoppingItem *addItemsToShoppingList(int *item_count)
{
  ShoppingItem *items = NULL;
  char buffer[1024];
  int capacity = 10;
  int count = 0;

  items = malloc(capacity * sizeof(ShoppingItem));
  if (items == NULL)
  {
    printf("[ERROR] Memory allocation failed!\n\n");
    return NULL;
  }

  while (1)
  {
    printf("\nItem %d:\n", count + 1);

    printf("What do you want to add?\n > ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
      free(items);
      return NULL;
    }

    size_t length = strlen(buffer);
    if (buffer[length - 1] == '\n')
    {
      buffer[length - 1] = '\0';
      length--;
    }

    if (strcmp(buffer, "done") == 0)
    {
      break;
    }
    else if (strcmp(buffer, "quit") == 0)
    {
      for (int i = 0; i < count; i++)
      {
        free(items[i].name);
      }
      free(items);
      return NULL;
    }
    else if (strcmp(buffer, "") == 0)
    {
      printf("[ERROR] Item name cannot be empty!\n\n");
      continue;
    }

    char *item_name = malloc(length + 1);
    if (item_name == NULL)
    {
      printf("[ERROR] Memory allocation failed!\n\n");
      for (int i = 0; i < count; i++)
      {
        free(items[i].name);
      }
      free(items);
      return NULL;
    }
    strcpy(item_name, buffer);

    int quantity = 0;
    while (quantity <= 0)
    {
      printf("How many pieces/grams/milliliters of this item do you want to get?\n > ");
      if (fgets(buffer, sizeof(buffer), stdin) == NULL)
      {
        free(item_name);
        for (int i = 0; i < count; i++)
        {
          free(items[i].name);
        }
        free(items);
        return NULL;
      }

      size_t length = strlen(buffer);
      if (buffer[length - 1] == '\n')
      {
        buffer[length - 1] = '\0';
      }

      if (strcmp(buffer, "quit") == 0)
      {
        free(item_name);
        for (int i = 0; i < count; i++)
        {
          free(items[i].name);
        }
        free(items);
        return NULL;
      }

      quantity = validateQuantity(buffer);

      if (quantity <= 0)
      {
        continue;
      }
    }

    items[count].name = item_name;
    items[count].quantity = quantity;
    count++;

    if (count >= capacity)
    {
      capacity *= 2;
      ShoppingItem *temp = realloc(items, capacity * sizeof(ShoppingItem));
      if (temp == NULL)
      {
        printf("[ERROR] Memory allocation failed!\n\n");
        free(item_name);
        for (int i = 0; i < count; i++)
        {
          free(items[i].name);
        }
        free(items);
        return NULL;
      }
      items = temp;
    }
  }

  *item_count = count;
  return items;
}

//---------------------------------------------------------------------------------------------------------------------
/// Function to compare shopping items by name and quantity
/// Used for sorting the shopping list
/// @param a Pointer to the first item
/// @param b Pointer to the second item
/// @return name_comparison
//---------------------------------------------------------------------------------------------------------------------
int compareItems(const void *a, const void *b)
{
  ShoppingItem *item1 = (ShoppingItem *)a;
  ShoppingItem *item2 = (ShoppingItem *)b;

  int name_comparison = strcmp(item1->name, item2->name);
  if (name_comparison == 0)
  {
    return item1->quantity - item2->quantity;
  }
  return name_comparison;
}

//---------------------------------------------------------------------------------------------------------------------
/// Function to print the shopping list
/// Sorts the list by name and then prints each item
/// @param shopping_list_name Name of the shopping list
/// @param items Pointer to the array 
/// @param item_count Number of items in the shopping list
/// @return void
//---------------------------------------------------------------------------------------------------------------------
void printShoppingList(const char *shopping_list_name, ShoppingItem *items, int item_count)
{
  printf("\nShopping list: %s\n", shopping_list_name);

  qsort(items, item_count, sizeof(ShoppingItem), compareItems);

  for (int i = 0; i < item_count; i++)
  {
    printf(" * %d %s\n", items[i].quantity, items[i].name);
  }
}

//---------------------------------------------------------------------------------------------------------------------
/// This is the main function of the program,
/// It calls all other functions, manages memory, programm execution happens here
/// @return 0 if the program exits successfully, -1 in case of errors
//---------------------------------------------------------------------------------------------------------------------
int main(void)
{
  char *shopping_list_name;
  ShoppingItem *shopping_list = NULL;
  int item_count = 0;

  welcomeMessage();

  shopping_list_name = shoppingListName();
  if (shopping_list_name == NULL)
  {
    return 0;
  }

  shopping_list = addItemsToShoppingList(&item_count);
  if (shopping_list == NULL)
  {
    free(shopping_list_name);
    return 0;
  }

  printShoppingList(shopping_list_name, shopping_list, item_count);

  for (int i = 0; i < item_count; i++)
  {
    free(shopping_list[i].name);
  }
  free(shopping_list);
  free(shopping_list_name);

  return 0;
}
