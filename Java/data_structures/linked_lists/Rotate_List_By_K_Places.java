
class ListNode {
      int val;
      ListNode next;
      ListNode() {}
      ListNode(int val) { this.val = val; }
      ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 }

public class Rotate_List_By_K_Places {
    public ListNode rotateRight(ListNode head, int k) {
        int n=0;
        ListNode curr=head;
        if(head==null || head.next==null)
        {
            return head;
        }

        ListNode first=null, last=null;

        while(curr!=null)
        {
            n++;
            
            curr=curr.next;
        }

        k=k%n;
        
        int i=1;
        curr=head;
        while(i!=n-k)
        {
            curr=curr.next;

            i++;
        }
    
        first=curr;
        for(i=1;i<=k;i++)
        {
            last=first;
            ListNode secondLast=null;
            while(last.next!=null)
            {
                if(last.next.next==null)
                {
                    secondLast=last;
                }
                last=last.next;
            }
            last.next=head;
            secondLast.next=null;
            head=last;
        }
        first.next=null;
        return head;
        
    }
}
    
