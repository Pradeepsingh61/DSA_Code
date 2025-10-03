"""
 * Finite Automata Algorithm for Pattern Searching
 * 
 * This algorithm constructs a Deterministic Finite Automaton (DFA) from a pattern
 * and uses it to efficiently search for the pattern in a text string.
 * The time complexity is O(m*k + n) where:
 * - m is the length of the pattern
 * - k is the size of the alphabet (number of possible characters)
 * - n is the length of the text
 * 
 * The key components of the algorithm are:
 * 1. A transition function that maps (state, character) to next state
 * 2. Efficient computation of this function using pattern preprocessing
 * 3. Linear-time text search using the automaton
 * 
 * Author: Abhiram
 * Date: October 3, 2025
"""

class FiniteAutomaton:
    def __init__(self, pattern, alphabet=None):
        """
        Initialize the Finite Automaton for pattern searching.
        
        Args:
            pattern: The pattern to search for.
            alphabet: The set of characters to consider. If None, it's derived from the pattern.
        """
        self.pattern = pattern
        self.m = len(pattern)
        
        # If alphabet is not provided, derive it from the pattern
        if alphabet is None:
            self.alphabet = set(pattern)
        else:
            self.alphabet = alphabet
            
        # Build the transition function (the automaton)
        self.transition_function = self._build_transition_function()
    
    def _build_transition_function(self):
        """
        Builds the transition function for the finite automaton.
        
        Returns:
            A dictionary mapping (state, char) to next_state
        """
        transition = {}
        
        # For each state and each character in the alphabet
        for state in range(self.m + 1):
            for char in self.alphabet:
                # Calculate the length of the longest prefix of pattern
                # that is also a suffix of (current_prefix + char)
                next_state = self._get_next_state(state, char)
                transition[(state, char)] = next_state
                
        return transition
    
    def _get_next_state(self, state, char):
        """
        Computes the next state based on the current state and character.
        
        Args:
            state: Current state (length of matched prefix so far).
            char: Next character to process.
            
        Returns:
            Next state after processing the character.
        """
        # If the character matches the next character in pattern
        if state < self.m and char == self.pattern[state]:
            return state + 1
            
        # Otherwise, find the longest prefix that is also a suffix
        next_state = 0
        
        # Start from the largest possible prefix
        for ns in range(state, 0, -1):
            # Check if there's a valid prefix
            if self.pattern[ns-1] == char:
                # Check if the prefix of pattern[0...ns-2] is also 
                # a suffix of pattern[0...state-1]
                i = 0
                while i < ns - 1:
                    if self.pattern[i] != self.pattern[state - ns + 1 + i]:
                        break
                    i += 1
                    
                if i == ns - 1:
                    next_state = ns
                    break
                    
        return next_state
    
    def search(self, text):
        """
        Search for occurrences of the pattern in the text.
        
        Args:
            text: The text to search in.
            
        Returns:
            A list of starting positions where the pattern is found.
        """
        n = len(text)
        positions = []
        
        # Start from initial state 0
        state = 0
        
        # Process each character of text
        for i in range(n):
            # If the character is not in the alphabet, assume no transition
            if text[i] in self.alphabet:
                state = self.transition_function.get((state, text[i]), 0)
            else:
                state = 0
                
            # If we reached the final state, pattern is found
            if state == self.m:
                positions.append(i - self.m + 1)
                
        return positions


def build_optimized_transition_function(pattern, alphabet):
    """
    Optimized version of the transition function construction.
    This implementation is more efficient for large alphabets.
    
    Args:
        pattern: The pattern to search for.
        alphabet: The set of characters to consider.
        
    Returns:
        A dictionary mapping (state, char) to next_state
    """
    m = len(pattern)
    transition = {}
    
    # Compute the longest proper suffix that is also a prefix
    # for the pattern (similar to KMP preprocessing)
    lps = [0] * m
    length = 0
    i = 1
    
    while i < m:
        if pattern[i] == pattern[length]:
            length += 1
            lps[i] = length
            i += 1
        else:
            if length != 0:
                length = lps[length - 1]
            else:
                lps[i] = 0
                i += 1
    
    # For each state and character, compute the next state
    for state in range(m + 1):
        for char in alphabet:
            if state < m and char == pattern[state]:
                transition[(state, char)] = state + 1
            elif state > 0:
                # Use the lps values to find the next state
                transition[(state, char)] = transition[(lps[state - 1], char)]
            else:
                transition[(state, char)] = 0
                
    return transition


def finite_automaton_search(text, pattern):
    """
    Convenience function to search for a pattern in text using the Finite Automaton.
    
    Args:
        text: The text to search in.
        pattern: The pattern to search for.
        
    Returns:
        A list of starting positions where the pattern is found.
    """
    # Create alphabet from both text and pattern for completeness
    alphabet = set(text) | set(pattern)
    
    # Use the optimized transition function for better performance
    automaton = FiniteAutomaton(pattern, alphabet)
    return automaton.search(text)


# Example usage
if __name__ == "__main__":
    # Example 1: Basic pattern searching
    text1 = "ABABDABACDABABCABAB"
    pattern1 = "ABABCABAB"
    
    print(f"Example 1: Searching for '{pattern1}' in '{text1}'")
    positions1 = finite_automaton_search(text1, pattern1)
    
    if positions1:
        print(f"Pattern found at positions: {positions1}")
    else:
        print("Pattern not found")
    
    # Example 2: Multiple occurrences
    text2 = "AAAABAAAAABBBAAAAB"
    pattern2 = "AAA"
    
    print(f"\nExample 2: Searching for '{pattern2}' in '{text2}'")
    positions2 = finite_automaton_search(text2, pattern2)
    
    if positions2:
        print(f"Pattern found at positions: {positions2}")
    else:
        print("Pattern not found")
    
    # Example 3: No match
    text3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    pattern3 = "XYZ123"
    
    print(f"\nExample 3: Searching for '{pattern3}' in '{text3}'")
    positions3 = finite_automaton_search(text3, pattern3)
    
    if positions3:
        print(f"Pattern found at positions: {positions3}")
    else:
        print("Pattern not found")
    
    # Example 4: DNA pattern matching
    text4 = "ACGTACGTACGTTACGTACGTACGTACGTACGT"
    pattern4 = "TACGTAC"
    
    print(f"\nExample 4: Searching for '{pattern4}' in '{text4}'")
    positions4 = finite_automaton_search(text4, pattern4)
    
    if positions4:
        print(f"Pattern found at positions: {positions4}")
    else:
        print("Pattern not found")
