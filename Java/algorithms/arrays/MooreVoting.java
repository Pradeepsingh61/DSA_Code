public class MooreVoting {

    public static Integer findMajorityElement(int[] nums) {
        // Phase 1: Find candidate
        int candidate = 0, count = 0;

        for (int num : nums) {
            if (count == 0) {
                candidate = num;
            }
            if (num == candidate) {
                count++;
            } else {
                count--;
            }
        }

        // Phase 2: Verify candidate
        count = 0;
        for (int num : nums) {
            if (num == candidate) {
                count++;
            }
        }

        if (count > nums.length / 2) {
            return candidate;
        } else {
            return null; // No majority element
        }
    }

    public static void main(String[] args) {
        int[] nums = {2, 2, 1, 1, 2, 2, 2};
        Integer majority = findMajorityElement(nums);

        if (majority != null) {
            System.out.println("Majority Element: " + majority);
        } else {
            System.out.println("No Majority Element exists");
        }
    }
}
