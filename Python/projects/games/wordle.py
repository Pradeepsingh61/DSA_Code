import random

FINAL_WORD_LENGTH = 5
MAX_ATTEMPTS = 6
word_list = []

def load_words(filename):
    try:
        with open(filename, "r") as file:
            for line in file:
                word = line.strip().lower()
                if len(word) == FINAL_WORD_LENGTH:
                    word_list.append(word)
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found.")

def get_feedback(guess, actual_word):
    feedback = []
    for i in range(FINAL_WORD_LENGTH):
        if guess[i] == actual_word[i]:
            feedback.append("O")
        elif guess[i] in actual_word:
            feedback.append("N")
        else:
            feedback.append("*")
    return "".join(feedback)

def display_rules():
    print("Welcome to Wordle!")
    print("--------------------------------------------------------------")
    print("Rules: ")
    print(f"1. Each guess must be a {FINAL_WORD_LENGTH}-letter word.")
    print(f"2. You have {MAX_ATTEMPTS} attempts to guess the word.")
    print("3. After each guess, you will receive feedback on the letters.")
    print("--------------------------------------------------------------")
    print("4. Notations used: ")
    print("O: Correct letter in the correct position")
    print("N: Correct letter in the wrong position")
    print("*: Incorrect letter")
    print("--------------------------------------------------------------")

def main():
    load_words("dictionary.txt")
    
    if not word_list:
        print("No words loaded. Exiting.")
        return

    actual_word = random.choice(word_list)
    attempts = 0

    display_rules()

    while attempts < MAX_ATTEMPTS:
        guess = input("Enter your guess: ").strip().lower()
        if len(guess) != FINAL_WORD_LENGTH:
            print(f"Invalid guess. Please enter a {FINAL_WORD_LENGTH}-letter word.")
            continue

        attempts += 1

        if guess == actual_word:
            print(f"Congratulations! You've guessed the word.")
            print(f"Attempt {attempts}: {guess}")
            break

        feedback = get_feedback(guess, actual_word)
        print(f"Attempt {attempts}: {guess}")
        print(f"Feedback: {feedback}")

        if attempts == MAX_ATTEMPTS:
            print(f"Sorry, you've used all your attempts. The word was: {actual_word}")

if __name__ == "__main__":
    main()
