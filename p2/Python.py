import re
import sys

class Num:
    def __init__(self, val):
        self.value = float(val) if '.' in val else int(val)

# <expr> -> <term> {+ <term> | - <term>}
def expr():
    result = term() # <expr> -> <term> 부분
    while True:     # < expr > ->{+<term> | -<term>} 부분
        if token == '+':
            token_match('+')
            result += term()
        elif token == '-':
            token_match('-')
            result -= term()
        else:
            break
    return result

# <term> -> <factor> {* <factor> | / <factor>}
def term():
    result = factor()   #<term> -> <factor> 부분
    while True:     #<term> ->{* <factor> | / <factor>} 부분
        if token == '*':
            token_match('*')
            result *= factor()
        elif token == '/':
            token_match('/')
            try:
                result /= factor()
            except:
                print("Syntax error!!")
                sys.exit(1)
        else:
            break
    return result

#<factor> -> [ - ]( <number> | (<expr>) )
def factor():
    flag=0
    result=0
    result =0
    if token =='-':  #<factor> -> [ - ] -일경우 flag를 1값으로 해서 추후 -값 만듬
        token_match('-')
        flag = 1
    
    if token == '(':    # <factor> -> ( <number> | (<expr>) )
        token_match('(')
        result = expr()
        if flag==1:     #위에서 [-] 였을 경우 -값을 붙임
            result =(-result)
        token_match(')')
    
    elif True:
        result = number();      #정수일경우
        if flag == 1:
            result =(-result)   #위에서 [-] 였을 경우 -값을 붙임	

    return result

#<number> -> <digit> {<digit>}
def number():

    result =digit() #<number> -> <digit> 부분

    if isinstance(token, Num):  #<number> ->{<digit>} 부분
        result = token.value
        token_match(token)
    else:
        digit()

    return result 

#0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
def digit():
    temp=0;
    if token == '0':
        token_match('0');
        temp += 0;

    elif token == '1':
        token_match('1');
        temp += 1;

    elif token == '2':
        token_match('2');
        temp += 2;
        
    elif token == '3':
        token_match('3');
        temp += 3;

    elif token == '4':
        token_match('4');
        temp += 4;

    elif token == '5':
        token_match('5');
        temp += 5;

    elif token == '6':
        token_match('6');
        temp += 6;

    elif token == '7':
        token_match('7');
        temp += 7;
    elif token == '8':
        token_match('8');
        temp += 8;

    elif token == '9':
        token_match('9');
        temp += 9;
        
    return temp;

def token_match(t):     #입력받은 token 확인 제대로된 토큰이면 next로 다음 단어를 token으로 만듬
    global token
    if t == token:
        try:
            token = next(token_gen)
        except:
            token =''
    else:
        raise RuntimeError(f'Syntax error!!')
        
        
def lexan():
    inp = input('>> ')
    i = 0
    while i < len(inp):
        c = inp[i]
        if c.isdigit() or c == '.':
            val = re.match(r'[.0-9]+', inp[i:])[0]
            yield Num(val)
            i += len(val)
        else:
            if c != ' ' and c !='\t':       #공백,\t 제거
                yield c
            i += 1
  
def main():

    global token_gen, token
    while True:
        token_gen = lexan()     # 토큰을 확인
        try:
            token = next(token_gen)     # 토큰은 다음 토큰으로
        except:
            print("Syntax error!!")
            sys.exit(1)
        result = expr()
        token_match('')
        print(result)

if __name__ == '__main__':
    main()