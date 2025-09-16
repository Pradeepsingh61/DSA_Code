public class BruteForceSearch {
    public static int bruteForceSearch(String text, String pattern) {
        int textLength = text.length();
        int patternLength = pattern.length();

        for (int i = 0; i <= textLength - patternLength; i++) {
            int j = 0;
            while (j < patternLength && text.charAt(i + j) == pattern.charAt(j)) {
                j++;
            }
            if (j == patternLength) {
                return i;
            }
        }

        return -1;
    }

    public static void main(String[] args) {
        String text = "This is a simple example";
        String pattern = "simple";
        int result = bruteForceSearch(text, pattern);
        if (result != -1) {
            System.out.println("Pattern found at index: " + result);
        } else {
            System.out.println("Pattern not found.");
        }
    }
}
