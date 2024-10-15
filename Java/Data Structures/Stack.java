import java.util.Arrays;
import java.util.EmptyStackException;

public class Stack<E> {
    private E[] elements;
    private int top;

    @SuppressWarnings("unchecked")
    public Stack(int initialCapacity) {
        elements = (E[]) new Object[initialCapacity];
        top = -1;
    }

    public Stack() {
        this(10); // Default initial capacity
    }

    public boolean isEmpty() {
        return top == -1;
    }

    public int size() {
        return top + 1;
    }

    public E peek() {
        if (isEmpty()) {
            throw new EmptyStackException();
        }
        return elements[top];
    }

    public E pop() {
        if (isEmpty()) {
            throw new EmptyStackException();
        }
        E item = elements[top];
        elements[top] = null; // Clear the reference to avoid memory leaks
        top--;
        return item;
    }

    public void push(E item) {
        if (size() == elements.length) {
            // Resize the array if it's full
            elements = Arrays.copyOf(elements, elements.length * 2);
        }
        elements[++top] = item;
    }
}