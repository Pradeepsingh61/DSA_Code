num = int (input (“Enter the desired number: “)
flag = False
if num > 1:
              for i in range (2, num):
                             if (num % i) == 0:
                                            flag = True
                                            break
if flag:
              print (“The number entered is not a prime number”)
else:
              print (“The number entered is a prime number”)
