
import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.Scanner;

public class pl1java {
	public static void main(String[] args) {
	int N;
	long start;
	Scanner sc = new Scanner(System.in);
	while(true) {
		try {
		System.out.print(">>Input the number of numbers to proecess:");
		N = sc.nextInt();
		
		if(N>=2 && N<=30) {
			break;
		}
		}
		catch(InputMismatchException e){
             System.out.println("재입력 하세요.");
             sc.nextLine();

             continue;
            }

		System.out.println("재입력 하세요.");
	}
	
	int[] arr = new int[N];
	int ii=0;
	System.out.println(">>Input the numbers to be processed:");
	while(true) {
		try {
		arr[ii]=sc.nextInt();
		
		if(arr[ii]>100000) {
			sc.nextLine();
			for(int i=0; i<N; i++) {
				arr[i]=0;
			}
			ii=0;
			System.out.println("재입력 하세요.");
			continue;
		}
		if(ii==N-1) {
			break;
		}
		
		}
		catch(InputMismatchException e){
			System.out.println("재입력 하세요.");
			sc.nextLine();
			ii=0;
			continue;
		}
		ii++;
	}
	start = System.currentTimeMillis();
	
	
	
	int temp=0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	
	
	
	int result = 0;
	int flag = 0;
	
	for(int i=1; i<=arr[0];i++) {
		
		for(int j=0; j<N; j++) {

			if(arr[j]%i !=0) {
				break;
			}
			if(j==N-1) {
				result = i;
			}
		}
		
	}
	
	System.out.printf("GCD of input numbers is %d\n",result);
	
	int x=0, y=1;
	for(int a=0; a<N-1; a++) {
		int prime = 0;
		if(arr[x]==arr[y]) {
			x++;
			y++;
			a++;
		}
		for(int i= arr[x]; i<=arr[y]; i++) {
			for(int j=2; j<=i; j++) {
				if(i==2) {
					prime++;
				}
				if((i%j!=0 && j==(i-1))) {
					prime++;
				}
				else if(i%j!=0) {
					continue;
				}
				else
					break;
			}
		}
		System.out.printf("Number of prime numbers between %d , %d : %d\n",arr[x],arr[y],prime);
		x++;
		y++;
	}
	long end = System.currentTimeMillis();

	System.out.println("Total execution time using Java is " + (end - start)/1000.0 + " seconds!");

	
	
	
	
	
	}
}
