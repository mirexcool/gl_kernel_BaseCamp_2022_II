// SPDX-License-Identifier: GPL-2.0-or-later
/* Simple Guess a number program.
 *
 * Written by Yevhen Yefimov (mirexcool@gmail.com)
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_GUESSED_NUMBER_THRESHOLD 42
#define NUMERIC_BASE 10
#define USER_INPUT_BUFFER_SIZE_MAX 7
#define USER_INPUT_BUFFER_SIZE (USER_INPUT_BUFFER_SIZE_MAX - 1)

#define EXIT_CODE_USER_WON 0
#define EXIT_CODE_PC_WON 1
#define EXIT_INVALID_INPUT (-1)
#define EXIT_NAUGHTY_PLAYER (-2)
/**
 * Initiate random number generation. Run once per lifecycle.
 * @return void
 */
static inline void setup_random_number_generator(void)
{
    srand(time(NULL)); // Seed
}
/**
 * Makes random number in range [1, MAX_GUESSED_NUMBER_THRESHOLD]
 * @return random number in range [1, MAX_GUESSED_NUMBER_THRESHOLD]
 */
unsigned short get_random_number(void)
{
	return (rand() % MAX_GUESSED_NUMBER_THRESHOLD) + 1; // Generate random number form 1 to MAX_GUESSED_NUMBER_THRESHOLD
}

int main(void)
{
	unsigned short randomNumber;
	unsigned short userNumber;
    char user_input[USER_INPUT_BUFFER_SIZE_MAX] = {0};
    char* endPtr;

    setup_random_number_generator();
	randomNumber = get_random_number();

	printf("Try to guess my number between 1 and %hu:\n", MAX_GUESSED_NUMBER_THRESHOLD);
    fgets(user_input, USER_INPUT_BUFFER_SIZE, stdin);

    int result = EXIT_CODE_USER_WON;

    userNumber = strtoul(user_input, &endPtr, NUMERIC_BASE);

    if (errno == ERANGE) {
        result = EXIT_INVALID_INPUT;
    } else if (userNumber > MAX_GUESSED_NUMBER_THRESHOLD) {
        printf("Oh my, you are such a rebel.\n");
        result = EXIT_NAUGHTY_PLAYER;
    } else if (endPtr == user_input) {
        printf("Hmm, I am not sure you gave me a number.\n");
        result = EXIT_INVALID_INPUT;
    }


    if (result >= 0) {
        if (userNumber != randomNumber) {
            printf("Sorry, you loose. I was thinking of the number %hu.\n", randomNumber);
            result = EXIT_CODE_PC_WON;
        } else {
            printf("You win\n");
        }
    }

	return result;
}
