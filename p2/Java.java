
import java.util.Scanner;

public class Java20182586
{
     public final static Scanner input= new Scanner(System.in);
     static char token;
     
    public static char gettoken()		//입력받은 token 확인 제대로된 토큰이면 nextchar로 다음 단어를 token으로 만듬
    {
          return token =nextChar(input);        
    }
    public final static char nextChar(Scanner scanner)	//다음 단어를 token으로 만드는 함수
    {
        scanner.useDelimiter("");	// ""딜리미터 단위로 나누어줌
        char t=scanner.next().charAt(0);
        scanner.reset();
        return t;
    }
    public static void del_space() {	//공백, \t 를 제거해주는 함수
        while (true) {
            if (token == ' ' || token == '\t')
                token = gettoken();
            else
                break;
        }
    }
    // <expr> -> <term> {+ <term> | - <term>}
    public static int expr()
    {
    	del_space();	//앞 뒤 개행 제거
       int result = term();		// <expr> -> <term> 부분
       del_space();
   	while ((token == '+') || (token == '-')) {		// < expr > ->{+<term> | -<term>} 부분
       switch (token) {
           case '+':
               gettoken();
               result += term();
               break;
           case '-':
               gettoken();
               result -= term();
               break;
           		
       }
   	}
       return result;
    }
    
    // <term> -> <factor> {* <factor> | / <factor>}
    public static int term() {
    	del_space();
    	int result = factor();	//<term> -> <factor> 부분
    	del_space();
    	while ((token == '*') || (token == '/')) {	 //<term> ->{* <factor> | / <factor>} 부분
        switch (token) {
            case '*':
                gettoken();
                result *= factor();
                break;
            case '/':
                gettoken();
                result /= factor();
                break;
        	}
    	}
		return result;
	}
    
    //<factor> -> [ - ]( <number> | (<expr>) )
	public static int factor() {
		del_space();
		int result=0;
		int flag =0;

		if(token == '-') {	//<factor> -> [ - ] -일경우 flag를 1값으로 해서 추후 -값 만듬
			gettoken();
			flag=1;
		}
		if(token =='(') {	//<factor> -> ( <number> | (<expr>) )
			gettoken();
			result = expr();
			if(flag==1) {		//위에서 [-] 였을 경우 -값을 붙임
				result =(-result);
			}
			if(token==')'){
				gettoken();
			}
			else {
				System.out.printf("Syntax error!!");
	       	 	System.exit(1);
			}
				
		}
		else if(Character.isDigit(token)==true) {	// 정수일경우

			result = number();
			if(flag==1) {			//위에서 [-] 였을 경우 -값을 붙임	
				result =(-result);	
			}
		}
		else {
			System.out.printf("Syntax error!!");
       	 	System.exit(1);
		}
		return result;
	}
	
	// <number> -> <digit> {<digit>}
	public static int number() {
		del_space();
		int result = digit();		// <number> -> <digit> 부분
		while(Character.isDigit(token)) {		// <number> ->{<digit>} 부분 
			result *=10;			// 자릿수를 늘려가면서 계속 곱하고 더함
			int tmp = digit();
			result += tmp;
		}
		return result;
	}
	
	// 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
	public static int digit() {
		int result=0;

		switch (token) {
        case '0':
            gettoken();
            result+=0;
            break;
        case '1':
            gettoken();

            result+=1;
            break;
        case '2':
            gettoken();
            result+=2;
            break;
        case '3':
            gettoken();
            result+=3;
            break;
        case '4':
            gettoken();
            result+=4;
            break;
        case '5':
            gettoken();
            result+=5;
            break;
        case '6':
            gettoken();
            result+=6;
            break;
        case '7':
            gettoken();
            result+=7;
            break;
        case '8':
            gettoken();
            result+=8;
            break;
        case '9':
            gettoken();
            result+=9;
            break;
            
           default:
                 System.err.println("Syntax error!!");
               break;
    }
		return result;
	}
	
	
	public static void main(String[] args)
    {
       while(true)
       {
          System.out.print(">> ");
          System.out.flush();
          gettoken();
          int result = expr();
          gettoken();
          
          if(token == '\n') {		//개행 올시 result 출력
        	  System.out.printf("%d\n",result);
          }
          else {
        	 System.out.printf("Syntax error!!");		//아니면 error출력
        	 System.exit(1);
          }
          
          
       	}
        
    }
    
}
