import random

def higher_or_lower():
    print("Welcome to Higher or Lower!")
    number = random.randint(1, 100)
    print(f"The starting number is {number}")

    while True:
        guess = input("Will the next number be higher or lower? (h/l): ")
        next_number = random.randint(1, 100)
        print(f"The next number is {next_number}")

        if (guess == "h" and next_number > number) or (guess == 'l' and next_number < number):
            print("Your guess correctly!")
        else:
            print("You guessed worng. Game over!")
            break

        number = next_number

higher_or_lower()