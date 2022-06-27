# Gennaro Punzo CS-210 Project 3

import re
import string

# Defaults from starter code
def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

# Print list of all grocery items and how many times they appear
def PrintList():
    # open file
    file = open('CS210_Project_Three_Input_File.txt', 'r')
    # Read all items to list
    grocery_list = file.readlines()
    grocery_dict = {}

    # Iterate through list and add each occurance to dict
    for i in grocery_list:
        if i.strip() in grocery_dict:
            grocery_dict[i.strip()] += 1
        else:
            grocery_dict[i.strip()] = 1

    # Output each item in dict and their number of occurances
    print("********************")
    for i in grocery_dict:
        print(i, ":", grocery_dict[i])
    print("********************")

    file.close()

# Print number of occurrances for one item
def PrintItem(item):
    # Open file
    file = open('CS210_Project_Three_Input_File.txt', 'r')
    # Read all items to list
    grocery_list = file.readlines()
    grocery_dict = {}

    # Iterate through list and add each occurance to dict
    for i in grocery_list:
        if i.strip() in grocery_dict:
            grocery_dict[i.strip()] += 1
        else:
            grocery_dict[i.strip()] = 1
    
    # Output item and occurrances if they exist
    if item in grocery_dict:
        if (grocery_dict[item] == 1):
            print("There was", grocery_dict[item], item, "purchased")
        else:
            print("There were", grocery_dict[item], item, "purchased.")

    # If no such item exists, output
    else:
        print("There were no", item, "purchased.")

    file.close()

    return 100;
    
def GenerateFile():
    # Open file
    file = open('CS210_Project_Three_Input_File.txt', 'r')
    # Read all items to list
    grocery_list = file.readlines()
    grocery_dict = {}

    # Iterate through list and add each occurance to dict
    for i in grocery_list:
        if i.strip() in grocery_dict:
            grocery_dict[i.strip()] += 1
        else:
            grocery_dict[i.strip()] = 1

    # Create frequency.dat, go through grocery_dict and add each element to file
    with open('frequency.dat', 'w') as f:
        for k, v in grocery_dict.items():
            f.write('%s %s\n' % (k,v))