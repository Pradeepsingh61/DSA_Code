import random
import time

def memory_game():
    print("Welcome to the Memory Game!")
    sequence = []
    level = 1

    while True:
        sequence.append(random.randint(1, 9))
        print(f"Level {level}")
        print(sequence)
        time.sleep(3)
        print("\n" * 50)

        guess = input("Enter the sequence: ")
        guess_sequence = [int(num) for num in guess]

        if guess_sequence == sequence:
            print("Correct!")
            level += 1

        else:
            print(f"Wrong! the correct sequence was {sequence}. Game Over!")
            break
        
memory_game()

    