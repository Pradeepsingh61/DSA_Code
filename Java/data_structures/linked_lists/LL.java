import java.util.Scanner;

class Node {
    int data;
    Node next;
    Node (int x) {
        data = x;
        next = null;
    }
}

public class LL {
    public static void printLL(Node head) {
        Node current = head;
        while (current!=null) {
            System.out.print(current.data+" -> ");
            current = current.next;
        }
        System.out.println("NULL");
    }

    public Node insertAtBeginning(Node head, int x) {
        Node temp = new Node(x);
        temp.next = head;
        return temp;
    }

    public Node insertAtEnd(Node head, int x){
        Node temp = new Node(x);
        if (head == null) {
            return temp;
        }
        Node current = head;
        while (current.next != null) {
            current = current.next;
        }
        current.next = temp;
        return head;
    }

    public Node insertAtPosition(Node head, int data, int position) {
        Node temp = new Node(data);
        if (position == 1) {
            temp.next = head;
            return temp;
        }

        Node curr = head;
        for (int i = 1; i<=position-2 && curr!=null; i++) {
            curr=curr.next;
        }
        if (curr == null) {
            return head;
        }

        temp.next = curr.next;
        curr.next = temp;
        return head;
    }

    public Node deleteHeadNode(Node head) {
        if (head == null) {
            return null;
        } else {
            return head.next;
        }
    } 

    public Node deleteNodeAtEnd(Node head) {
        if (head == null) return null;
        if (head.next == null) return null;

        Node curr = head;
        while (curr.next.next!=null) {
            curr = curr.next;
        }
        curr.next = null;
        return head;
    }

    public Node deleteNodeAnyPosition(Node head, int position) {
        if (head==null) return null;
        if (position==1) return head.next;

        Node curr = head;
        for (int i=1; i<=position-2 && curr!=null; i++) {
            curr = curr.next;
        }

        if (curr == null || curr.next == null) {
            return head;
        }

        curr.next = curr.next.next;
        return head;
    }

    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);

        LL list = new LL();
        Node head = null;
        int choice = 0;

        while (choice!=8) {
            System.out.println("\n");
            System.out.println("Choose what to do?");
            System.out.println("1. Insert Node at the beginning");
            System.out.println("2. Insert Node at the end");
            System.out.println("3. Insert Node at any position");
            System.out.println("4. Delete Node at the beginning");
            System.out.println("5. Delete Node at the end");
            System.out.println("6. Delete Node at any position");
            System.out.println("7. Print the Linked List");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();

            switch (choice) {
                case 1: // Insert at beginning
                    System.out.print("Enter value: ");
                    int val1 = sc.nextInt();
                    head = list.insertAtBeginning(head, val1);
                    break;
                case 2: // Insert at any end
                    System.out.print("Enter value: ");
                    val1 = sc.nextInt();
                    head = list.insertAtEnd(head, val1);
                    break;
                case 3: // Insert at any position
                    System.out.print("Enter value: ");
                    val1 = sc.nextInt();
                    System.out.print("Enter position: ");
                    int pos = sc.nextInt();
                    head = list.insertAtPosition(head, val1, pos);
                    break;
                case 4: // Delete at the beginning
                    head = list.deleteHeadNode(head);
                    System.out.println("Node deleted at beginning!");
                    break;
                case 5: // Delete at the end
                    head = list.deleteNodeAtEnd(head);
                    System.out.println("Node deleted at end!");
                    break;
                case 6: // Delete at any position
                    System.out.print("Enter position: ");
                    pos = sc.nextInt();
                    head = list.deleteNodeAnyPosition(head, pos);
                    System.out.println("Node deleted at position "+pos);
                    break;
                case 7: // Print List
                    System.out.println("\n");
                    LL.printLL(head);
                    System.out.println("\n");
                    break;
            }
        }

        sc.close();
    }
}
