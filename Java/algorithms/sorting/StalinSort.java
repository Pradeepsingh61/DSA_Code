public class StalinSort {

    public static void stalinSort(int[] nums) {
        int index = 0;
        for (int i = 1; i < nums.length; i++) {
            if (nums[i] >= nums[index]) {
                index++; 
                nums[index] = nums[i];
            }
        }
        System.out.print("Sorted array: ");
        for (int i = 0; i <= index; i++) {
            System.out.print(nums[i] + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        int[] nums = {3, 1, 4, 2, 5, 6, 3, 8};
        stalinSort(nums);
    }
}
