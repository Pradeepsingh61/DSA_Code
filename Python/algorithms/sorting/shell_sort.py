"""  Shell Sort is an advanced version of the insertion sort algorithm that improves
 its efficiency by comparing and sorting elements that are far apart. The idea behind Shell Sort is
  to break the original list into smaller sublists,
 sort these sublists, and gradually reduce the gap between the sublist 
 elements until the list is sorted. """
  
def shellSort(arr):

    n = len(arr)

    gap = n // 2

    while gap > 0:

        for i in range(gap, n):

            temp = arr[i]

            j = i
            while j >= gap and arr[j - gap] > temp:

                arr[j] = arr[j - gap]

                j -= gap

            arr[j] = temp

        gap //= 2

if __name__ == "__main__":
    arr = [12, 34, 54, 2, 3]

    print("Array before sorting:")

    print(arr)

    shellSort(arr)
    

    print("\nArray after sorting:")

    print(arr)