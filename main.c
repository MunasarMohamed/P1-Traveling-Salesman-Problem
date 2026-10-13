/*
    Recommend running the exe file instead of running in a code editor,
    due to code editors not keeping up with printf outputs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "header.h"

void clear_terminal()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/*
    intro() is used for showing the "banner" or fancy menu screen
*/
void intro()
{
    clear_terminal();
    fflush(stdout);
    printf("\n    === Solving The Traveling Salesman Problem ===\n");
    printf("\n    Navigate the menu using up and down arrow keys or use the number associated.\n\n");
}

/*
    print_options() is used to print the available commands / the options the user has,
    it also highlights the currently selected option
*/
void print_options(int count, const char* options[], int current)
{
    intro(); // show menu banner

    // print options
    for (int i = 0; i < count; i++)
    {
        if (i == current)
        {
            printf(" >  %d. \x1B[7m%s\x1B[0m\n", i+1, options[i]); // Highlight selected option
        }
        else
        {
            printf("    %d. %s\n", i+1, options[i]);
        }
    }
}

/*
    menu() is a function that listens to user input,
    if down arrow key is pressed the next option will be highlighted,
    also allows user to simply write the number of the option they want
*/
int menu(const char* options[], int count)
{
    int current = 0;
    int loop = 1;

    while (loop)
    {
        print_options(count, options, current);

        int choice = _getch(); // get key
        switch (choice)
        {
        case 13: // Enter key
            loop = 0;
            break;
        case 80: // Down arrow
            current = (current + 1) % count; // % count, is used in case, the user goes below the options, so it just goes back to the top
            break;
        case 72: // Up arrow
            current = (current - 1 + count) % count;
            break;
        default:
            if (choice >= '1' && choice <= '9') // if it is a number (so letters don't work)
            {
                int selected = choice - '1'; // the index is starting from 0, and user writes 1 to get option 0, (so -1 is needed)
                if (selected < count) // in case user writes 7 when there only is 4 options
                {
                    current = selected;
                    loop = 0;
                }
            }
            break;
        }
    }

    return current;
}

void print_result(int number_of_coordinates, Coordinate* solution[number_of_coordinates], double total_cost);

int main(void)
{
    const char* inputOptions[] = {
        "Get Input from Terminal",
        "Read Input from File",
        "Generate N Random Data Points",
        "Help"
    };

    const char* algorithmOptions[] = {
        "Nearest Neighbor",
        "Two Opt",
        "Redo Input / Back",
        "Help",
    };

    while (1)
    {
        int option = -1;
        Coordinate* coordinates = NULL;
        int lengthOfInput = 0;
        while (option == -1)
        {
            option = menu(inputOptions, sizeof(inputOptions) / sizeof(const char*));

            clear_terminal();

            switch (option)
            {
            case 0:
                coordinates = get_coordinates_from_terminal(&lengthOfInput);
                break;
            case 1:
                coordinates = read_from_file(&lengthOfInput);
                break;
            case 2:
                coordinates = random_coordinate_generator(&lengthOfInput);
                break;
            case 3:
                help_input();
                option = -1;
                break;
            default:
                printf("Invalid option\n");
                break;
            }

            if (coordinates == NULL)
                option = -1;
        }

        fflush(stdout);

        double cost;
        option = -1;
        Coordinate** solution = malloc((lengthOfInput + 1) * sizeof(Coordinate*));
        while (option == -1)
        {
            option = menu(algorithmOptions, sizeof(algorithmOptions) / sizeof(const char*));
            switch (option)
            {
            case 0:
                cost = nearest_neighbor(coordinates, lengthOfInput, 0, solution);
                if (solution != NULL)
                {
                    print_result(lengthOfInput, solution, cost);
                }
                option = -1;
                break;
            case 1:
                cost = two_opt(coordinates, lengthOfInput, solution);
                if (solution != NULL)
                {
                    print_result(lengthOfInput, solution, cost);
                }
                option = -1;
                break;
            case 2:
                continue;
            case 3:
                clear_terminal();
                help_algorithm();
                option = -1;
                break;
            default:
                printf("Invalid option\n");
                break;
            }
        }

        if (option != 2)
        {
            printf("Press enter to continue");
            fflush(stdin);
            getchar();
        }
    }

    return 0;
}

void print_result(int number_of_coordinates, Coordinate* solution[number_of_coordinates], double total_cost)
{
    printf("\nTotal Cost: %.2lf DKK\n\n", total_cost);

    printf("Tour:\n");

    for (int i = 0; i < number_of_coordinates + 1; ++i)
    {
        printf("(%d, %d)\n", solution[i % number_of_coordinates]->x, solution[i % number_of_coordinates]->y);
    }

    fflush(stdin);
    printf("\nPress enter to continue...");
    getchar();
}
