

import time

while 1:
    print(">> Input the number of numbers to process:")
    try:
        N = int(input())
        if 2<=N and N<=30:
            break;
    except ValueError:
        print("재입력 하세요.")
        continue;
    print("재입력 하세요.")
    
arr = []
print(">> Input the numbers to be processed:\n")

while(1):
    ii = 0
    try:
        arr = list(map(int, input().split()))
        for i in range(N):
            if arr[i] > 100000:
                print("재입력 하세요.")
                ii=1
                continue;

    except ValueError:
        print("재입력 하세요.")
        continue;
    except IndexError:
        print("재입력 하세요.")
        continue;
    if ii==1 :
        continue;
    break;
   

start = time.time()
    
    

for i in range(len(arr)):
        for j in range(0, len(arr) - i - 1):
            if arr[j] > arr[j + 1]: 
                arr[j], arr[j + 1] = arr[j + 1], arr[j] 

for i in range(1,arr[0]+1):
    for j in range(0,N):
        if (arr[j] % i) !=0 :
            break
        if j == (N-1):
            result = i
    
print("GCD of input numbers is",result)

x=0
y=1



for a in range(0,N-1):
    prime=0
    
    if arr[x]==arr[y]:
        x+=1
        y+=1
        continue
        
    for i in range(arr[x],arr[y]+1):
        for j in range(2,i+1):
            if i==2:
                prime+=1
            if (i%j) !=0 and j==(i-1):
                prime+=1
            elif i%j !=0:
                continue
            else:
                break
    print("Number of prime numbers between ",arr[x],",",arr[y],":",prime)
    x+=1
    y+=1
    
    
print("Total execution time using Python is:", time.time() - start)