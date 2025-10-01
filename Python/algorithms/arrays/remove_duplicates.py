"""
    Finds duplicates in O(n) time and O(1) extra space.
    
    Note: This method modifies the input list and assumes numbers are > 0.
    """

from collections import Counter
from typing import List

def find_duplicates(arr: List[int]) -> List[int]:

    freq_map = Counter(arr)

    duplicates = [item for item, count in freq_map.items() if count > 1]

    return duplicates

if __name__ == "__main__":

    arr1 = [1, 2, 3, 6, 3, 6, 1]

    arr2 = [2, 1, 5, 4, 1, 3, 5]

    arr3 = [2, 3, 8, 3, 13]
    
    print(f"Original list: {arr1}")

    print(f"Duplicates: {find_duplicates(arr1)}")

    print("-" * 20)
    

    
    print(f"Original list: {arr2}")

    print(f"Duplicates: {find_duplicates(arr2)}")

    print("-" * 20)



    print(f"Original list: {arr3}")

    print(f"Duplicates: {find_duplicates(arr3)}")

    print("-" * 20)