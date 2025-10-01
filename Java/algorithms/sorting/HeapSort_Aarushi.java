/**
 * Algorithm: Heap Sort
 * Description: Implementation of Heap Sort algorithm using binary heap
 * Time Complexity: O(n log n) for all cases
 * Space Complexity: O(1) (in-place)
 */
import java.util.Scanner;
public class HeapSort {

    public static int[] arrInput(Scanner sc) {
        System.out.print("Enter the size of the array: ");
        int n = sc.nextInt();
        int[] arr = new int[n];
        System.out.println("Enter the elements of the array: ");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }
        return arr;
    }

    public static void heapSort(int[] arr) {
        int n = arr.length;
        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        // Extract elements from heap
        for (int i = n - 1; i >= 0; i--) {
            // Swap current root with end
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            // Heapify reduced heap
            heapify(arr, i, 0);
        }
    }

    public static void heapify(int[] arr, int n, int i) {
        int largest = i;  
        int left = 2 * i + 1;  
        int right = 2 * i + 2;  
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        if (largest != i) {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;
            heapify(arr, n, largest);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int[] arr = arrInput(sc);
        System.out.print("Array before sorting: ");
        for (int num : arr) {
            System.out.print(num + " ");
        }
        System.out.println();
        heapSort(arr);
        System.out.print("Array after sorting: ");
        for (int num : arr) {
            System.out.print(num + " ");
        }
        System.out.println();
        sc.close();
    }
}
