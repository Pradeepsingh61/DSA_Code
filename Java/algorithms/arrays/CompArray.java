//Java program to compare two arrays
// Importing required classes
import java.util.*;

// Main class
class CompArray{

	// Main driver method
	public static void main(String[] args)
	{
		// Arrays to be compared
		int arr1[] = { 1, 2, 3 };
		int arr2[] = { 1, 2, 3 };

		// Comparing arrays if equal or not
		if(Arrays.equals(arr1, arr2))
			{System.out.println("Same");}
		else
			System.out.println("Not same");
	}
}
