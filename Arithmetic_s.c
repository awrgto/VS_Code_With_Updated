#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct linkedListArray {     //linkedList Array
    char opr;
    double num;
    struct linkedListArray *next;
    struct linkedListArray *pre;
} LLA;

typedef LLA *LLAPtr;

struct LLAHook {
    int count;
    LLAPtr LLARear;
    LLAPtr LLAFront;
} LLAH[3] = {{0, NULL, NULL}};


const char Nothing = '0';
const int True = 1, False = 0;

const int Stack = 0, Queue4pos = 1, Queue4in = 2;

char *getString ( FILE *, size_t );         //get un_limit string

//linkedList Array Method
int isEmpty ( int );                        //check LLA is empty or not
int size ( int );                           //get size of LLA
void push ( char, double, int );            //insert a element at rear
int pop ( char *, double *, int );          //delete a element at rear
int shift ( char *, double *, int );        //delete a element at front
int peek ( char *, double *, int );         //show last element
void print ( int );     //debug             //print LLA
void clean ( int );                         //make LLA empty

int isAllowedOpr ( char );                  //ident is it char that i allowed

int priority ( char );                      //sort opr by priority

double calculate ( char, double, double );  //calculate the number be inputed with opr

//in total Process
int wordProcess ( char * );                 //deal with string to linked list type
int inToPostfix ( int, int );               //deal with infixExpression to postfixExpression
double eval ( int );                        //calculate postfixExpression

void getAnswer ( char * );                  //for total Process

int main ( ) {
    char pass = 'n' ;
    while ( tolower( pass ) == 'n' ) {
        printf ( "%s", "\nExcept +-*/ ( ) other symbol will be ignored\nput ur question there ( only integer & every item < 2^(31-1) --> " );
        char *infix = getString ( stdin, 8 );
        getAnswer( infix );
        fflush( stdin );
        do{
            printf( "%s", "\nExit ?  (Y)es  /  (N)o --> " );
            scanf ( "%c", &pass );
            fflush( stdin );
        } while ( tolower( pass ) != 'n' && tolower( pass ) != 'y' );
    }
}

void getAnswer ( char * infix ) {
    size_t check = 2;
    check -= wordProcess ( infix );
    //print ( Queue4in );
    check -= inToPostfix ( Queue4in, Queue4pos );
    //print ( Queue4pos );
    if ( check ) puts ( "\nur input maybe have something wrong!" );
    else printf ( "\nans : %.3lf\n", eval ( Queue4pos ) );
    for ( size_t iter = 0; iter < 3; iter++ )   //clean all data if their are not be used
        clean ( iter );
}

char *getString ( FILE* fp, size_t size ) {
    char *str;
    int ch;
    size_t len = 0;
    str = realloc ( NULL, sizeof ( char ) * size );
    if ( !str ) return str;
    while ( EOF!= ( ch = fgetc ( fp ) ) && ch != '\n' ) {
        str[len++] = ch;
        if ( len == size ) {
            str = realloc ( str, sizeof ( char ) * ( size += 16 ) );
            if ( !str ) return str;
        }
    }
    str[len++] = '\0';
    return realloc ( str, sizeof ( char ) * len );  //re-sized string
}
int isEmpty ( int controller ) { return LLAH[controller].count ? 0 : 1;}
int size ( int controller ) { return LLAH[controller].count; }
void print ( int controller ) { //debug
    LLAPtr current = LLAH[controller].LLAFront;
    if ( isEmpty ( controller ) ) puts ( "List is empty!" );
	else
		while ( current != NULL ) {
            if ( current ->opr != Nothing ) printf ( " %c", current ->opr );
            else printf ( " %.3lf", current ->num );
			current = current -> next;
		}
    puts ( "\nprint end" );
}
void push ( char c_in, double d_in, int controller ) {
    LLAPtr ptr = malloc ( sizeof ( *ptr ) );
    ptr->num = d_in;
    ptr->opr = c_in;
    
    if ( isEmpty ( controller ) ) {
        LLAH[controller].LLAFront = ptr; //debug
        ptr->pre = NULL;
    }else {
        LLAH[controller].LLARear -> next = ptr; //debug
        ptr->pre = LLAH[controller].LLARear;
    }
    LLAH[controller].LLARear = ptr;
    ptr -> next = NULL; //debug
    LLAH[controller].count++;
}
int pop ( char * c_out, double * d_out, int controller ) {
    LLAPtr beban = LLAH[controller].LLARear;
    if ( isEmpty ( controller ) ) return False;

    LLAH[controller].LLARear = LLAH[controller].LLARear->pre;
    *d_out = beban->num;
    *c_out = beban->opr;

    free ( beban );
    LLAH[controller].count --;

    if ( isEmpty ( controller ) ) LLAH[controller].LLAFront = NULL; //debug
    else LLAH[controller].LLARear->next = NULL;
    return True;
}
int peek ( char * c_out, double * d_out, int controller ) {
    if ( isEmpty ( controller ) ) return False;
    *d_out = LLAH[controller].LLARear->num;
    *c_out = LLAH[controller].LLARear->opr;
    return True;
}
int shift ( char * c_out, double * d_out, int controller ) {
    LLAPtr beban = LLAH[controller].LLAFront;
    if ( isEmpty ( controller ) ) return False;

    LLAH[controller].LLAFront = LLAH[controller].LLAFront->next;
    *d_out = beban->num;
    *c_out = beban->opr;

    free ( beban );
    LLAH[controller].count --;

    if ( isEmpty ( controller ) ) LLAH[controller].LLARear = NULL; //debug
    else LLAH[controller].LLAFront->pre = NULL;
    return True;
}
void clean ( int controller ) {
    LLAPtr beban = LLAH[controller].LLARear;
    while ( beban ) {
        LLAH[controller].LLARear = LLAH[controller].LLARear->pre;
        free ( beban );
        beban = LLAH[controller].LLARear;
    }
    LLAH[controller].count = 0;
    LLAH[controller].LLARear = NULL;
}
int wordProcess ( char * infix ) {
    size_t tok = 0, isHead = True;
    int tmp = 0,sign = 0;
    double  d_last;
    char sTmp[2] = {'\0'}, c_last = 'N';
    //printf ( "%s", infix );//debug
    while ( infix[tok] != '\0' ) {
        isHead = 1 - peek ( &c_last, &d_last, Queue4in );
        switch ( infix[tok] ) {
            case '+': case '-': 
                if ( isHead || ( ( !isdigit ( c_last ) ) && c_last != ')' ) ) {
                    sign = ( sign == 0 ) ? 1 : sign;
                    sign *= ( infix[tok++] == '+' ) ? 1 : -1;
                }else {
                    push ( infix[tok++], 0, Queue4in );
                }
                break;
            case '*': case '/': 
                if ( ( ( !isdigit ( c_last ) ) && c_last != ')' )  || isHead )
                    return False;
                push ( infix[tok++], 0, Queue4in );
                isHead = False;
                break;
            case '(': 
                if ( sign != 0 ) {
                    push ( Nothing, sign, Queue4in );
                    push ( '*', 0, Queue4in );
                    sign = 0;
                }
                push ( infix[tok++], 0, Queue4in );
                break;
            case ')':
                if ( !isdigit ( c_last ) && c_last != ')' )
                    return False;
                push ( infix[tok++], 0, Queue4in );
                isHead = False;
                break;
            case '1':case '2':case '3':case '4':case '5':
            case '6':case '7':case '8':case '9':case '0':
                do {
                    sTmp[0] = infix[tok];
                    if ( isdigit ( infix[tok] ) )
                        tmp = tmp * 10 + atoi ( sTmp );
                } while ( isAllowedOpr ( infix[++tok] ) == False && infix[tok] != '\0' );
                push ( Nothing, sign == 0 ? tmp : sign * tmp, Queue4in );
                if ( infix[tok] == '(' ) push ( '*', 0, Queue4in );
                tmp = 0;
                sign = 0;
                break;
            default : tok++;
        }
    }
    return True;
}
int isAllowedOpr ( char c ) {
    char opr[] = {'+', '-', '*', '/', '(', ')'};
    size_t iter = 0;
        while ( iter < sizeof ( opr ) ) if ( c == opr[iter++] ) return True;
    return False;
}
int inToPostfix ( int infix, int postfix ) {
    char c_infix, c_last, c_pop, check_ok = '1';
    double d_infix, d_last, i_pop;
    while ( shift ( &c_infix, &d_infix, infix ) ) {
        switch ( c_infix ) {
            case '(':              // 運算子堆疊
                push ( c_infix, d_infix, Stack );
                break; 
            case '+': case '-': case '*': case '/':
                while ( !isEmpty ( Stack ) ) {
                    peek ( &c_last, &d_last, Stack );
                    if ( priority ( c_last ) < priority ( c_infix ) ) break;
                    pop ( &c_pop, &i_pop, Stack );
                    push ( c_pop, i_pop, postfix );
                }
                push ( c_infix, d_infix, Stack ); // 存入堆疊
                break; 
            case ')': 
                while ( !isEmpty ( Stack ) ) { // 遇 ) 輸出至 ( 
                    peek ( &c_last, &d_last, Stack );
                    if ( c_last == '(' ) break;
                    pop ( &c_pop, &i_pop, Stack );
                    push ( c_pop, i_pop, postfix );
                } 
                pop ( &c_pop, &i_pop, Stack );  // 不輸出 ( 
                break; 
            default:  // 運算元直接輸出
                push ( c_infix, d_infix, postfix );
        }
    }
    if(c_infix != Nothing) check_ok = '0';
    while ( !isEmpty ( Stack ) ) {
        pop ( &c_pop, &i_pop, Stack );
        if ( c_pop == '(' ) check_ok = '0';
        push ( c_pop, i_pop, postfix );
    }
    return check_ok == '1' ? 1 : 0;
} 
int priority ( char op ) { 
    switch ( op ) { 
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    } 
} 
double eval ( int postfix ) {  
    char c_infix, c_pop1, c_pop2;
    double d_infix, i_pop1, i_pop2;
    while ( shift ( &c_infix, &d_infix, postfix ) ) {
        switch ( c_infix ) {
            case '+': case '-': case '*': case '/':
                pop ( &c_pop1, &i_pop1, Stack );
                pop ( &c_pop2, &i_pop2, Stack );
                push ( Nothing, calculate ( c_infix, i_pop2, i_pop1 ), Stack );
                break; 
            default: 
                push ( Nothing, d_infix, Stack );
        }
    }          
    pop ( &c_pop1, &i_pop1, Stack ); 
    return i_pop1;
}
double calculate ( char opr, double pop2, double pop1 ) { 
    switch ( opr ) { 
        case '+': return pop2 + pop1; 
        case '-': return pop2 - pop1; 
        case '*': return pop2 * pop1; 
        case '/': return pop2 / pop1; 
    }
    return False;
}