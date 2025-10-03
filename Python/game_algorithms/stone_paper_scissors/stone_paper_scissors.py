import random

def play_game():

    choices = ["rock", "paper", "scissors"]

    player_score = 0

    computer_score = 0

    while True:

        player_choice = input("Enter your choice (rock, paper, scissors) or 'q' to quit: ").lower()

        if player_choice == 'q':

            print("Thanks for playing!")
            break

        if player_choice not in choices:

            print("Invalid choice. Please choose from rock, paper, or scissors.")
            continue

        computer_choice = random.choice(choices)

        print(f"You chose: {player_choice}")

        print(f"Computer chose: {computer_choice}")

        if player_choice == computer_choice:

            print("It's a tie!")
        elif (player_choice == "rock" and computer_choice == "scissors") or \
             (player_choice == "paper" and computer_choice == "rock") or \
             (player_choice == "scissors" and computer_choice == "paper"):
            print("You win!")
            player_score += 1

        else:

            print("You lose!")
            computer_score += 1

        print(f"Score: You {player_score} - {computer_score} Computer\n")

if __name__ == "__main__":

    
    play_game()