# Doubly Linked List implementation
class Node:
    def __init__(self, values):
        self.data = values
        self.previous = None
        self.next = None

def insert_at_beginning(head, x):
    node = Node(x)
    node.next = head
    if head:
        head.previous = node
    return node

def insert_at_end(head, x):
    node = Node(x)
    if head is None:
        return node
    temp = head
    while temp.next:
        temp = temp.next 
    temp.next = node
    node.previous = temp
    return head

def insert_after_node(node, x):
    if node is None:
        print("Node cannot be null")
        return
    a = Node(x)
    a.next = node.next 
    a.previous = node
    if node.next:
        node.next.previous = a
    node.next = a

def insert_before_node(head, node, val):
    if node is None:
        print("Node cannot be null")
        return head
    
    new = Node(val)
    new.previous = node.previous
    new.next = node 
    if node.previous:                 # if not the head
        node.previous.next = new
    else:                             # if it was the head, new becomes the head
        head = new
    node.previous = new
    return head

def delete_head(head):
    if head is None:
        return None
    if head.next is None:  # only one element
        return None
    new_head = head.next
    new_head.previous = None
    return new_head

def delete_at_end(head):
    if head is None:
        return None
    if head.next is None:  # only one element
        return None
    temp = head
    while temp.next:
        temp = temp.next
    temp.previous.next = None
    return head

def delete_by_value(head, val):
    if head is None:
        return None
    temp = head

    # if head itself needs to be deleted
    if temp.data == val:
        return delete_head(head)
    
    while temp and temp.data != val:
        temp = temp.next

    if temp is None:
        print(f"Value {val} not found in the list.")
        return head

    if temp.next:  
        temp.next.previous = temp.previous
    if temp.previous:
        temp.previous.next = temp.next
    return head

def print_LL(head):
    temp = head
    while temp:
        print(temp.data, end=" <-> ")
        temp = temp.next
    print("None")

# print the doubly linked list backwards
def print_reverse(head):
    if head is None:
        print("None")
        return
 
    temp = head
    while temp.next:
        temp = temp.next

    # print backwards
    while temp:
        print(temp.data, end=" <-> ")
        temp = temp.previous
    print("None")


if __name__ == '__main__':
    head = None
    head = insert_at_beginning(head, 89)       
    head = insert_at_beginning(head, 63)       
    insert_after_node(head.next, 56)      
    head = insert_before_node(head, head.next, 10)  
    head = insert_at_end(head, 96)  
    head = insert_at_beginning(head, 22)    
    head = insert_at_end(head, 32)  
    print_LL(head)
    head = delete_head(head) 
    head = delete_head(head) 
    head = delete_head(head)   
    print_LL(head)
    head = insert_at_end(head, 88)  
    head = insert_at_end(head, 44)  
    print_LL(head)
    head = delete_at_end(head)
    print_LL(head)
    head = delete_by_value(head, 32)
    print_LL(head)
    print_reverse(head)