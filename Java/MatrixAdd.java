//Java program to add two matrix of Nth order
import java.util.Scanner;

public class MatrixAdd{
        public static void main(String []args)
        {
                if(args.length!=1)
                {
                        System.out.println("Please provide the value of N as a command line argument.");
                }
                int N = Integer.parseInt(args[0]);
                int [][] matrix1 = new int [N][N];
                int [][] matrix2 = new int [N][N];

                Scanner o = new Scanner(System.in);

                //Read matrix 1
                System.out.println("Enter the elements of Matrix 1:");
                for(int i=0;i<N;i++)
                {
                        for(int j=0;j<N;j++)
                        {
                                matrix1[i][j] = o.nextInt();
                        }
                }

                //Read matrix 2
                System.out.println("Enter the elements of Matrix 2:");
                for(int i=0;i<N;i++)
                {
                        for(int j=0;j<N;j++)
                        {
                                matrix2[i][j] = o.nextInt();
                        }
                }

                //Perform addition
                int [][] result = new int [N][N];
                for(int i=0;i<N;i++)
                {
                        for(int j=0;j<N;j++)
                        {
                                result[i][j] = matrix1[i][j] + matrix2[i][j];
                        }
                }
                //Display the matrices and the sum
                printMatrix(matrix1); System.out.print("+"); printMatrix(matrix2); System.out.print("="); printMatrix(result);
        }

        //Function Definition
        private static void printMatrix(int [][] matrix)
        {
                for(int [] row : matrix)
                {
                        for(int num : row)
                        {
                                System.out.print(num + "\t");
                        }
                        System.out.println();
                }
                System.out.println();
        }

}
