# Simple To-Do List Manager (20-30 LOC)

tasks = []

def show_menu():
    print("\n1. Add Task\n2. View Tasks\n3. Remove Task\n4. Exit")

while True:
    show_menu()
    choice = input("Choose: ")

    if choice == "1":
        task = input("Enter task: ")
        tasks.append(task)
        print("Task added!")

    elif choice == "2":
        if not tasks:
            print("No tasks yet.")
        else:
            for i, t in enumerate(tasks, 1):
                print(f"{i}. {t}")

    elif choice == "3":
        num = int(input("Task number to remove: "))
        if 1 <= num <= len(tasks):
            tasks.pop(num - 1)
            print("Task removed!")
        else:
            print("Invalid number.")

    elif choice == "4":
        print("Goodbye!")
        break

    else:
        print("Invalid choice, try again.")
