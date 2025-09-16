import math

# Stack initialization
st = []
st.append('1')
st.append('2')
st.append('3')
st.append('4')
st.append('5')
st.append('6')
st.append('7')

# Calculate the target middle element index
n = len(st)
target = n // 2  # middle element index for both even and odd cases

# Temporary stack to hold elements while skipping the middle one
temp_stack = []

# Pop elements until we reach the middle one
for i in range(n):
    element = st.pop()
    if i == target:
        continue  # Skip the middle element
    temp_stack.append(element)

# Rebuild the original stack (pushing elements back from temp_stack)
while temp_stack:
    st.append(temp_stack.pop())

# Print the stack in correct order
print("Stack after deletion of middle:", end=" ")
while st:
    print(st.pop(), end=" ")
