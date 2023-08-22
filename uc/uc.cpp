#include <iostream>
#include <stdio.h>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
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
    EndOfFileToken,
    UnknownToken,
    NumberExpression,
    BinaryExpression

};

string SyntaxKindToString(SyntaxKind kind)
{
    switch (kind)
    {
    case SyntaxKind::NumberToken:
        return "NumberToken";
    case SyntaxKind::WhitespaceToken:
        return "WhitespaceToken";
    case SyntaxKind::PlusToken:
        return "PlusToken";
    case SyntaxKind::MinusToken:
        return "MinusToken";
    case SyntaxKind::StarToken:
        return "StarToken";
    case SyntaxKind::SlashToken:
        return "SlashToken";
    case SyntaxKind::OpenParenthesisToken:
        return "OpenParenthesisToken";
    case SyntaxKind::CloseParenthesisToken:
        return "CloseParenthesisToken";
    case SyntaxKind::EndOfFileToken:
        return "EndOfFileToken";
    case SyntaxKind::BadToken:
        return "BadToken";
    case SyntaxKind::NumberExpression:
        return "NumberExpression";
    case SyntaxKind::BinaryExpression:
        return "BinaryExpression";
    case SyntaxKind::UnknownToken:
        return "UnknownToken";
    default:
        return "Unknown";
    }
}

string TokenKindToString(SyntaxKind kind)
{
    switch (kind)
    {
    case SyntaxKind::NumberToken:
        return "NumberToken";
    case SyntaxKind::PlusToken:
        return "PlusToken";
    case SyntaxKind::MinusToken:
        return "MinusToken";
    case SyntaxKind::StarToken:
        return "StarToken";
    case SyntaxKind::SlashToken:
        return "SlashToken";
    case SyntaxKind::OpenParenthesisToken:
        return "OpenParenthesisToken";
    case SyntaxKind::CloseParenthesisToken:
        return "CloseParenthesisToken";
    case SyntaxKind::BadToken:
        return "BadToken";
    case SyntaxKind::WhitespaceToken:
        return "WhitespaceToken";
    case SyntaxKind::EndOfFileToken:
        return "EndofFileToken";
    default:
        return "UnknownToken";
    }
}

class SyntaxNode
{
public:
    virtual SyntaxKind GetKind() const = 0;
    virtual vector<SyntaxNode *> GetChildren() = 0;
};

class ExpressionSyntax : public SyntaxNode
{
public:
    virtual SyntaxKind GetKind() const = 0;
    virtual vector<SyntaxNode *> GetChildren() override = 0;
};

class SyntaxToken : public SyntaxNode
{
public:
    SyntaxToken(SyntaxKind kind, int position, const std::string &text, int value)
        : Kind(kind), Position(position), Text(text), Value(value)
    {
    }

    SyntaxKind Kind;
    int Position;
    std::string Text;
    int Value;

    SyntaxKind GetKind() const override
    {
        return Kind;
    }

    std::vector<SyntaxNode *> GetChildren() override
    {
        return {};
    }
};

class NumberExpressionSyntax : public ExpressionSyntax
{
public:
    NumberExpressionSyntax(SyntaxToken *numberToken)
        : NumberToken(numberToken)
    {
    }

    SyntaxKind GetKind() const override
    {
        return SyntaxKind::NumberExpression;
    }

    SyntaxToken *NumberToken;

    vector<SyntaxNode *> GetChildren() override
    {
        return {NumberToken};
    }
};

class BinaryExpressionSyntax : public ExpressionSyntax
{
public:
    BinaryExpressionSyntax(ExpressionSyntax *left, SyntaxToken *operatorToken, ExpressionSyntax *right)
        : Left(left), OperatorToken(operatorToken), Right(right)
    {
    }

    SyntaxKind GetKind() const override
    {
        return SyntaxKind::BinaryExpression;
    }

    ExpressionSyntax *Left;
    SyntaxToken *OperatorToken;
    ExpressionSyntax *Right;

    vector<SyntaxNode *> GetChildren() override
    {
        return {Left, OperatorToken, Right};
    }
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
            int value = stoi(text);
            Next();
            cout << "Extracted token: " << text << endl; // Add this lin
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
            return SyntaxToken(SyntaxKind::WhitespaceToken, start, text, 0);
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

        int start = _position - 1; // This line needs to be before the substring extraction
        int length = 1;
        string text = _text.substr(start, length);
        cout << "Substring parameters: start=" << start << ", length=" << length << ", text='" << text << "'" << endl;
        return SyntaxToken(SyntaxKind::BadToken, _position++, text, 0);
    }
};

class Parser
{
private:
    vector<SyntaxToken> _tokens;
    int _position;

public:
    Parser(const string &text)
    {
        vector<SyntaxToken> tokens;
        Lexer lexer(text);
        SyntaxToken token(SyntaxKind::UnknownToken, 0, "", 0);
        do
        {
            token = lexer.NextToken();
            if (token.Kind != SyntaxKind::WhitespaceToken &&
                token.Kind != SyntaxKind::BadToken)
            {
                tokens.push_back(token);
            }

        } while (token.Kind != SyntaxKind::EndOfFileToken);

        _tokens = tokens;
        _position = 0;
    }

private:
    SyntaxToken Peek(int offset)
    {
        int index = _position + offset;
        if (index >= static_cast<int>(_tokens.size()))
            return _tokens[_tokens.size() - 1];
        return _tokens[index];
    }

    SyntaxToken Current()
    {
        return Peek(0);
    }

    SyntaxToken NextToken()
    {
        SyntaxToken current = Current();
        _position++;
        return current;
    }

    SyntaxToken Match(SyntaxKind kind)
    {
        if (Current().Kind == kind)
            return NextToken();

        return SyntaxToken(kind, Current().Position, "", 0);
    }

public:
    ExpressionSyntax *Parse()
    {
        ExpressionSyntax *left = ParsePrimaryExpression();

        while (Current().Kind == SyntaxKind::PlusToken ||
               Current().Kind == SyntaxKind::MinusToken)
        {
            SyntaxToken operatorToken = NextToken();
            ExpressionSyntax *right = ParsePrimaryExpression();
            left = new BinaryExpressionSyntax(left, &operatorToken, right);
        }

        return left;
    }

private:
    ExpressionSyntax *ParsePrimaryExpression()
    {
        SyntaxToken numberToken = Match(SyntaxKind::NumberToken);
        return new NumberExpressionSyntax(&numberToken);
    }
};

class Program
{
public:
    static void Main()
    {
        while (true)
        {
            std::cout << "> ";
            std::string line;
            std::getline(std::cin, line);
            if (line.empty() || line.find_first_not_of(" ") == std::string::npos)
                return;
            Parser parser(line);
            ExpressionSyntax *expression = parser.Parse();
            auto color = std::cout.rdbuf()->sgetn(nullptr, 0); // Save current text color
            std::cout << "\x1B[1;30m";                         // Set text color to dark gray

            PrettyPrint(expression);

            std::cout << "\x1B[0m"; // Reset text color to default
            delete expression;
        }
    }

    static void PrettyPrint(SyntaxNode *node, const string &indent = "", bool isLast = true)
    {
        string marker = isLast ? "└──" : "├──";
        cout << indent << marker << SyntaxKindToString(node->GetKind());

        if (SyntaxToken *t = dynamic_cast<SyntaxToken *>(node))
        {
            if (t->Value != 0)
            {
                cout << " " << static_cast<int>(t->Value);
            }
        }

        cout << endl;

        string newIndent = indent + (isLast ? "    " : "│     ");
        auto children = node->GetChildren();
        SyntaxNode *lastChild = children.empty() ? nullptr : children.back();
        for (SyntaxNode *child : children)
        {
            PrettyPrint(child, newIndent, child == lastChild);
        }
    }
};

int main()
{
    Program::Main();
    return 0;
}
