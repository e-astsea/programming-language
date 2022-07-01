#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char token;
int expr(void);                 // <expr> -> <term> {+ <term> | - <term>}
int term(void);                 // <term> -> <factor> {* <factor> | / <factor>}
int factor(void);               // <factor> -> [ - ]( <number> | (<expr>) )
int number(void);               // <number> -> <digit> {<digit>}
int digit(void);                // 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 


void error(void)                //에러를 표시해주는 함수
{
    fprintf(stderr, "Syntax error!!\n");
    exit(1);
}

void token_match(char Token)    //입력받은 token이 제대로된 토큰인지 확인
{                               //제대로된 토큰이면 getchar로 다음 단어를 token으로 만듬
    if (token == Token) {
        token = getchar();
    }
    else {
        error();
    }
}

void del_space() {              //공백, \t 를 제거해주는 함수
    while (1) {
        if (token == ' ' || token == '\t')
            token = getchar();
        else
            break;
    }
}
int main()
{
    int result;
    while (1) {
        printf(">> ");
        token = getchar();
        result = expr();
        if (token == '\n')      //token이 개행(마지막)이 된다면 result로 결과출력
            printf("%d\n", result);
        else
            error();
    }
}


// <expr> -> <term> {+ <term> | - <term>}
int expr(void)
{
    del_space();            //앞 뒤 개행 제거
    int temp = term();      // <expr> -> <term> 부분
    del_space();
    while ((token == '+') || (token == '-'))    //< expr > ->{+<term> | -<term>} 부분
        switch (token)
        {
        case '+':
            token_match('+');
            temp += term();
            break;

        case '-':
            token_match('-');
            temp -= term();
            break;
        }

    return temp;
}

//<term> -> <factor> {* <factor> | / <factor>}
int term(void)
{
    del_space();
    int temp = factor();    //<term> -> <factor> 부분
    del_space();
    while ((token == '*') || (token == '/')) //<term> ->{* <factor> | / <factor>} 부분
        switch (token)
        {
        case '*':
            token_match('*');
            temp *= factor();
            break;

        case '/':
            token_match('/');
            temp /= term();
            break;
        }
    return temp;
}

//<factor> -> [ - ]( <number> | (<expr>) )
int factor(void)
{
    del_space();
    int temp;
    int flag = 0;
    if (token == '-') {     //<factor> -> [ - ] -일경우 flag를 1값으로 해서 추후 -값 만듬
        token_match('-');
        flag = 1;
    }   
    if (token == '(') {     //<factor> -> ( <number> | (<expr>) )
        token_match('(');
        temp = expr();
        if (flag == 1) {    //위에서 [-] 였을 경우 -값을 붙임
            temp = (-temp);
        }
        token_match(')');
    }
    else if (isdigit(token)) {  // 정수일경우
        temp = number();
        if (flag == 1) {    //위에서 [-] 였을 경우 -값을 붙임
            temp = (-temp);
        }
    }
    else error();

    return temp;
}

// <number> -> <digit> {<digit>}
int number(void) {
    del_space();
    int temp = digit();     // <number> -> <digit> 부분
    while (isdigit(token)) {    // <number> ->{<digit>} 부분 
        temp *= 10;             // 자릿수를 늘려가면서 계속 곱하고 더함
        int tmp = digit();
        temp += tmp;
    }
    return temp;
}

// 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
int digit(void) {
    int temp = 0;

    switch (token)
    {
    case '0':
        token_match('0');
        temp += 0;
        break;

    case '1':
        token_match('1');
        temp += 1;
        break;
    case '2':
        token_match('2');
        temp += 2;
        break;

    case '3':
        token_match('3');
        temp += 3;
        break;
    case '4':
        token_match('4');
        temp += 4;
        break;

    case '5':
        token_match('5');
        temp += 5;
        break;
    case '6':
        token_match('6');
        temp += 6;
        break;

    case '7':
        token_match('7');
        temp += 7;
        break;
    case '8':
        token_match('8');
        temp += 8;
        break;

    case '9':
        token_match('9');
        temp += 9;
        break;
    }
    return temp;
}
