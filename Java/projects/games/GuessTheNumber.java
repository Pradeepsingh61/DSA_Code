import java.util.Scanner;

public class GuessTheNumber {
    public static void main(String[] args)
    {
        System.out.println("Pick a number between 1-100.");
        Scanner sc = new Scanner(System.in);
        int  i = sc.nextInt();
        double j =  Math.random()*100;
        int k= (int) j;

        if(i==k)
            System.out.println("Congratulations,you are Correct");
        else
            System.out.println("Ooops... You Guessed it wrong\nCorrect number is:" + k);
    }
}
