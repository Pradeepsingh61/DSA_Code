import random

def number_guessing_game():
    print("Welcome to the Number Guessing Game!")
    print("I'm thinking of a number between 1 and 100.")

    secret_number = random.randint(1, 100)
    guesses_taken = 0

    while True:
        try:
            user_guess = int(input("Take a guess: "))
            guesses_taken += 1

            if user_guess < secret_number:
                print("Your guess is too low.")
            elif user_guess > secret_number:
                print("Your guess is too high.")
            else:
                print(f"Good job! You guessed the number in {guesses_taken} guesses!")
                break
        except ValueError:
            print("Invalid input. Please enter an integer.")

number_guessing_game()
