/*
 * PolishNotation.h
 *
 *  Created on: May 30, 2016
 *      Author: diepbp
 */

#ifndef POLISHNOTATION_H_
#define POLISHNOTATION_H_

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <stack>
#include <list>

const int LEFT_ASSOC  = 0;



// Map the different operators: +, -, *, / etc
typedef std::map< std::string, std::pair< int,int > > OpMap;
typedef std::vector<std::string>::const_iterator cv_iter;
typedef std::string::iterator s_iter;

const OpMap::value_type assocs[] =
{  OpMap::value_type( "+", std::pair<int,int>( 0, LEFT_ASSOC ) ),
    OpMap::value_type( "-", std::pair<int,int>( 0, LEFT_ASSOC ) ),
    OpMap::value_type( "!", std::pair<int,int>( 15, LEFT_ASSOC ) ),
    OpMap::value_type( "&&", std::pair<int,int>( 10, LEFT_ASSOC ) ),
    OpMap::value_type( "||", std::pair<int,int>( 5, LEFT_ASSOC ) ),
    OpMap::value_type( ">", std::pair<int,int>( 0, LEFT_ASSOC ) ),
    OpMap::value_type( ">=", std::pair<int,int>( 0, LEFT_ASSOC ) ),
    OpMap::value_type( "<", std::pair<int,int>( 0, LEFT_ASSOC ) ),
    OpMap::value_type( "<=", std::pair<int,int>( 0, LEFT_ASSOC ) ),
    OpMap::value_type( "==", std::pair<int,int>( 0, LEFT_ASSOC ) ),
    OpMap::value_type( "!=", std::pair<int,int>( 0, LEFT_ASSOC ) ),
    OpMap::value_type( "*", std::pair<int,int>( 5, LEFT_ASSOC ) ),
    OpMap::value_type( "/", std::pair<int,int>( 5, LEFT_ASSOC ) ) };

const OpMap opmap( assocs, assocs + sizeof( assocs ) / sizeof( assocs[ 0 ] ) );

class PolishNotation{
public:
    std::string expression;

    PolishNotation(std::string _expression): expression(_expression){
    }

    PolishNotation(){
        expression = "-100000000";
    }

    std::vector<std::string> parseExpression()
    {
        // Tokenize input expression
        std::vector<std::string> tokens = getExpressionTokens( expression );

        // Evaluate feasible expressions
        std::vector<std::string> ret;
        if ( !infixToRPN( tokens, (int)tokens.size(), ret ) )
        {
            printString("ERROR: Mis-match in parentheses\n");
        }

        return ret;
    }

private:

    // Test if token is a number
    bool isNumber( const std::string& token)
    {
        return token[0] >= '0' && token[0] <= '9';
    }

    // Test if token is an pathensesis
    bool isParenthesis( const std::string& token)
    {
        return token == "(" || token == ")";
    }

    // Test if token is an operator
    bool isOperator( const std::string& token)
    {
        return token == "+" || token == "-" ||
        token == "*" || token == "/" || token == "&&" || token == "||"
        || token == ">" || token == ">=" || token == "<" || token == "<="
        || token == "==" || token == "!=" || token == "&" || token == "|" || token == "=" || token == "!";
    }

    // Test associativity of operator token
    bool isAssociative( const std::string& token, const int& type)
    {
        const std::pair<int,int> p = opmap.find( token )->second;
        return p.second == type;
    }

    // Compare precedence of operators.
    int cmpPrecedence( const std::string& token1, const std::string& token2 )
    {
        const std::pair<int,int> p1 = opmap.find( token1 )->second;
        const std::pair<int,int> p2 = opmap.find( token2 )->second;

        return p1.first - p2.first;
    }

    // Convert infix expression format into reverse Polish notation
    bool infixToRPN( const std::vector<std::string>& inputTokens,
                    const int& size,
                    std::vector<std::string>& strArray )
    {
        bool success = true;

        std::list<std::string> out;
        std::stack<std::string> stack;

        // While there are tokens to be read
        for ( int i = 0; i < size; i++ )
        {
            // Read the token
            const std::string token = inputTokens[ i ];

            // If token is an operator
            if ( isOperator( token ) )
            {
                // While there is an operator token, o2, at the top of the stack AND
                // either o1 is left-associative AND its precedence is equal to that of o2,
                // OR o1 has precedence less than that of o2,
                const std::string o1 = token;

                if ( !stack.empty() )
                {
                    std::string o2 = stack.top();

                    while ( isOperator( o2 ) &&
                           ( ( isAssociative( o1, LEFT_ASSOC ) &&  cmpPrecedence( o1, o2 ) == 0 ) ||
                            ( cmpPrecedence( o1, o2 ) < 0 ) ) )
                    {
                        // pop o2 off the stack, onto the output queue;
                        stack.pop();
                        out.push_back( o2 );

                        if ( !stack.empty() )
                            o2 = stack.top();
                        else
                            break;
                    }
                }

                // push o1 onto the stack.
                stack.push( o1 );
            }
            // If the token is a left parenthesis, then push it onto the stack.
            else if ( token == "(" )
            {
                // Push token to top of the stack
                stack.push( token );
            }
            // If token is a right bracket ')'
            else if ( token == ")" )
            {
                // Until the token at the top of the stack is a left parenthesis,
                // pop operators off the stack onto the output queue.
                std::string topToken  = stack.top();

                while ( topToken != "(" )
                {
                    out.push_back(topToken );
                    stack.pop();

                    if ( stack.empty() ) break;
                    topToken = stack.top();
                }

                // Pop the left parenthesis from the stack, but not onto the output queue.
                if ( !stack.empty() ) stack.pop();

                // If the stack runs out without finding a left parenthesis,
                // then there are mismatched parentheses.
                if ( topToken != "(" )
                {
                    return false;
                }
            }
            // If the token is a number, then add it to the output queue.
            else
            {
                out.push_back( token );
            }
        }

        // While there are still operator tokens in the stack:
        while ( !stack.empty() )
        {
            const std::string stackToken = stack.top();

            // If the operator token on the top of the stack is a parenthesis,
            // then there are mismatched parentheses.
            if ( isParenthesis( stackToken )   )
            {
                return false;
            }

            // Pop the operator onto the output queue./
            out.push_back( stackToken );
            stack.pop();
        }

        strArray.assign( out.begin(), out.end() );

        return success;
    }

    std::string RPNtoString(std::vector<std::string> tokens)
    {
        std::stack<std::string> st;

        // For each token
        for ( int i = 0; i < (int) tokens.size(); ++i )
        {
            const std::string token = tokens[ i ];

            // If the token is a value push it onto the stack
            if ( !isOperator(token) )
            {
                st.push(token);
            }
            else
            {
                std::string result =  "";

                // Token is an operator: pop top two entries
                const std::string val2 = st.top();
                st.pop();

                if ( !st.empty() )
                {
                    if (token.compare("!") != 0) {
                        const std::string val1 = st.top();
                        st.pop();

                        //Get the result
                        result =
                        		token == "+" ? "("  + val1 + " + " + val2 + ")":
                        token == "-" ? "("  + val1 + " - " + val2 + ")":
                        token == "*" ? "("  + val1 + " * " + val2 + ")" :
                        token == "&&" ? "("  + val1 + " && " + val2 + ")":
                        token == "||" ? "("  + val1 + " || " + val2 + ")":
                        token == ">" ? "("  + val1 + " > " + val2 + ")":
                        token == ">=" ? "("  + val1 + " >= " + val2 + ")":
                        token == "<" ? "("  + val1 + " < " + val2 + ")":
                        token == "<=" ? "("  + val1 + " <= " + val2 + ")":
                        token == "==" ? "("  + val1 + " == " + val2 + ")":
                        token == "!=" ? "("  + val1 + " != " + val2 + ")":
                        "("  + val1 + " / " + val2 + ")";
                    }
                    else
                    {
                        result = "(!"  + val2 + ")";
                    }
                }
                else
                {
                    if ( token == "-" )
                        result = "-" + val2;
                    if (token.compare("!") == 0)
                        result = "(!"  + val2 + ")";
                    else
                        result = val2;
                }

                st.push(result);
            }
        }

        return st.top();
    }

    int RPNtoInt( std::vector<std::string> tokens )
    {
        std::stack<std::string> st;

        // For each token
        for ( int i = 0; i < (int) tokens.size(); ++i )
        {
            const std::string token = tokens[ i ];

            // If the token is a value push it onto the stack
            if ( !isOperator(token) )
            {
                st.push(token);
            }
            else
            {
                int result =  0.0;

                // Token is an operator: pop top two entries
                const std::string val2 = st.top();
                st.pop();
                const int d2 = strtod( val2.c_str(), NULL );

                if ( !st.empty() )
                {
                    const std::string val1 = st.top();
                    st.pop();
                    const int d1 = strtod( val1.c_str(), NULL );

                    //Get the result
                    result = token == "+" ? d1 + d2 :
                    token == "-" ? d1 - d2 :
                    token == "*" ? d1 * d2 :
                    token == "&&" ? d1 && d2:
                    token == "||" ? d1 || d2:
                    token == ">" ? d1 > d2:
                    token == ">=" ? d1 >= d2:
                    token == "<" ? d1 < d2:
                    token == "<=" ? d1 <= d2:
                    token == "==" ? d1 == d2:
                    token == "!=" ? d1 != d2:
                    d1 / d2;
                }
                else
                {
                    if ( token == "-" )
                        result = d2 * -1;
                    else
                        result = d2;
                }


                // Push result onto stack
                std::ostringstream s;
                s << result;
                st.push( s.str() );
            }
        }

        return strtod( st.top().c_str(), NULL );
    }

    std::vector<std::string> getExpressionTokens( const std::string& expression )
    {
        std::vector<std::string> tokens;
        std::string str = "";

        for ( int i = 0; i < (int) expression.length(); ++i )
        {
            const std::string token( 1, expression[ i ] );

            if ( !token.empty() && token != " " ){
                if (isNumber(token)) {
                    if (str != "") {
                        if (isNumber(str)) {
                            str.append(token);
                        }
                        else {
                            tokens.push_back( str ) ;
                            str = "";
                            str.append(token);
                        }
                    }
                    else
                        str.append(token);
                }
                else if (isParenthesis(token)){
                    if (str != "") {
                        tokens.push_back( str ) ;
                        str = "";
                    }
                    tokens.push_back( token ) ;
                }
                else if (isOperator(token)){
                    if (str != "") {
                        if (isOperator(str)) {
                            if (token == "+" || token == "-" || token == "*" || token == "/") {
                                tokens.push_back( str ) ;
                                tokens.push_back( token ) ;
                                str = "";
                            }
                            else {
                                str.append(token);
                                tokens.push_back( str ) ;
                                str = "";
                            }
                        }
                        else {
                            tokens.push_back( str ) ;
                            str = "";
                            if (token == "+" || token == "-" || token == "*" || token == "/") {
                                tokens.push_back( token ) ;
                            }
                            else
                                str.append(token);
                        }
                    }
                    else {
                        if (token == "+" || token == "-" || token == "*" || token == "/") {
                            tokens.push_back( token ) ;
                        }
                        else
                            str.append(token);
                    }
                }
            }
            else if ( str != "" )
            {
                tokens.push_back( str );
                str = "";
            }
        }

        if (str != "") {
            tokens.push_back(str);
        }

        return tokens;
    }

    void printString(std::string s){
        std::cout << s;
    }

    void printNumber(int n){
        std::cout << n;
    }
};

#endif /* POLISHNOTATION_H_ */
