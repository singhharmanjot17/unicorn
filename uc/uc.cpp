#include <iostream>
#include <stdio.h>
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

enum class SyntaxKind
{
    NumberToken,
    PlusToken,
    MinusToken,
    StarToken,
    SlashToken,
    OpenParenthesisToken,
    CloseParenthesisToken,
    BadToken,
    WhitespaceToken,
    EndOfFileToken

};

class SyntaxToken
{
public:
    SyntaxToken(SyntaxKind kind, int position, const string &text, int value)
        : Kind(kind), Position(position), Text(text), value(value)
    {
    }

    SyntaxKind Kind;
    int Position;
    string Text;
    int value;
};

class Lexer
{
private:
    string _text;
    int _position;

public:
    Lexer(const string &text)
        : _text(text), _position(0)
    {
    }

    char Current()
    {

        if (_position >= _text.length())
            return '\0';

        return _text[_position];
    }

    void Next()
    {
        _position++;
    }

    SyntaxToken NextToken()
    {
        if (_position >= _text.length())
        {
            return SyntaxToken(SyntaxKind::EndOfFileToken, _position, "\0", 0);
        }
        if (isdigit(Current()))
        {
            int start = _position;
            while (isdigit(Current()))
            {
                Next();
            }
            int length = _position - start;
            string text = _text.substr(start, length);
            int value = atoi(text.c_str());
            return SyntaxToken(SyntaxKind::NumberToken, start, text, value);
        }

        if (isspace(Current()))
        {
            int start = _position;
            while (isspace(Current()))
            {
                Next();
            }
            int length = _position - start;
            string text = _text.substr(start, length);
            int value = atoi(text.c_str());
            return SyntaxToken(SyntaxKind::WhitespaceToken, start, text, value);
        }

        if (Current() == '+')
        {
            int start = _position;
            Next();
            return SyntaxToken(SyntaxKind::PlusToken, start, "+", 0);
        }
        else if (Current() == '-')
        {
            int start = _position;
            Next();
            return SyntaxToken(SyntaxKind::MinusToken, start, "-", 0);
        }
        else if (Current() == '*')
        {
            int start = _position;
            Next();
            return SyntaxToken(SyntaxKind::StarToken, start, "*", 0);
        }
        else if (Current() == '/')
        {
            int start = _position;
            Next();
            return SyntaxToken(SyntaxKind::SlashToken, start, "/", 0);
        }
        else if (Current() == '(')
        {
            int start = _position;
            Next();
            return SyntaxToken(SyntaxKind::OpenParenthesisToken, start, "(", 0);
        }
        else if (Current() == ')')
        {
            int start = _position;
            Next();
            return SyntaxToken(SyntaxKind::CloseParenthesisToken, start, ")", 0);
        }

        return SyntaxToken(SyntaxKind::BadToken, _position++, _text.substr(_position - 1, 1), 0);
    }
};

class Program
{

public:
    bool IsNullOrWhiteSpace(const std::string &str)
    {
        return str.find_first_not_of(' ') == std::string::npos;
    }

    void Run()
    {
        while (true)
        {
            string line;
            getline(cin, line);
            if (IsNullOrWhiteSpace(line))
                return;

            Lexer lexer(line);
            while (true)
            {
                SyntaxToken token = lexer.NextToken();
                if (token.Kind == SyntaxKind::EndOfFileToken)
                    break;
                cout << static_cast<int>(token.Kind) << ": '" << token.Text << "'";
                if (token.value != 0)
                    cout << " value: " << token.value;
                // cout << " (" + to_string((int)(token->kind)) + ")";
            }
        }
    }
};

int main()
{
    Program p;
    p.Run();
    return 0;
}
