# The Easy And Brute Force Way To do it:
#
# We just put all the elements of the stack into a vector then traverse over the vector and put the print the element/push into stack ignoring the mid element for even (n/2) and for odd (ceil(n/2)).
import math 
 
st = []
st.append('1')
st.append('2')
st.append('3')
st.append('4')
st.append('5')
st.append('6')
st.append('7')
 
v = []
 
while(len(st) > 0):
    v.append(st[0])
    del st[0]
     
n = len(v)
 
if n%2==0:
    target = math.floor(n/2)
    for i in range(0, n):
        if i==target:
            continue
        st.append(v[i])
else:
    target = math.floor(n/2) 
    for i in range(0, n):
        if i==target:
            continue
        st.append(v[i])
 
print("Stack after deletion of middle:", end = " ")
 
while (len(st) > 0):
    p = st[0]
    del st[0]
    print(p, end = " ")
