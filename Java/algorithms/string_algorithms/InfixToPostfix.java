//Program in Java to convert Infix Expression into Postfix Expression
import java.util.*; 

public class InfixPostfixConversion { 

	public static String infixToPostfix(String infix) 
	{ 

		// The output will be represented as postfix 
		StringBuilder postfix = new StringBuilder(); 

		// Initialize the stack
		Stack<Character> stk = new Stack<>(); 
		for (char c : infix.toCharArray()) { 

			// if the encountered character is an operand add it to the output i.e postfix 
			if (Character.isLetterOrDigit(c)) { 
				postfix.append(c); 

				// if the encountered character is '(', push it to the stack(stk) 
			} 
			else if (c == '(') { 
				stk.push(c); 
            }

			// if the encountered character is ')' pop the stack(stk) until '(' is encountered  
			else if (c == ')') { 
				while (!stk.isEmpty() 
					&& stk.peek() != '(') { 
					postfix.append(stk.pop()); 
				} 
				stk.pop(); 
            }   

            // discard '(' by popping it from the stack 
			else { 
				while (!stk.isEmpty() 
					&& precedence(stk.peek()) 
							>= precedence(c)) { 
					postfix.append(stk.pop()); 
				} 
				stk.push(c); // push the current operator to stack
							
			} 
		} 

		while (!stk.isEmpty()) { 
			postfix.append(stk.pop()); 
		} 

		return postfix.toString(); 
	} 

	// define a method to check the precedence of operators
	public static int precedence(char operator) 
	{ 
		switch (operator) { 
		case '+': 
		case '-': 
			return 1; 
		case '*': 
		case '/': 
			return 2; 
		default: 
			return 0; 
		} 
	} 

	// main function 
	public static void main(String[] args) 
	{ 
		System.out.println("Enter a Infix expression:"); 
		Scanner sc = new Scanner(System.in); 
		String infix = sc.next(); 

		sc.close(); 
		String postfix = infixToPostfix(infix); 

		System.out.println("Postfix Expression: \n"
						+ postfix); 
	} 
}
