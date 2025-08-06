#include <sigmalang/lexer.hpp>

using namespace org::amimchik::sigmalang::lexer;

Lexer::Lexer(std::string_view input,
             std::shared_ptr<diagnostics::IHandler> handler)
    : handler(handler), input(input), pos(0), line(1) {}

std::vector<token::Any> Lexer::tokenize() {
	std::vector<token::Any> result;
	for (; pos < input.size(); pos++) {
		switch (input[pos]) {
		default: {
			if (std::isalpha(input[pos])) {
				std::string buf;
				for (; pos < input.size() && std::isalnum(input[pos]); pos++) {
					buf += input[pos];
				}
				pos--;
				result.push_back(token::Identifier(buf));
				continue;
			}
			if (std::isdigit(input[pos])) {
				int64_t val = 0;
				for (; pos < input.size() && std::isdigit(input[pos]); pos++) {
					val *= 10;
					val += input[pos] - '0';
				}
				pos--;
				result.push_back(token::Number(val));
				continue;
			}
			handler->handle(diagnostics::Warning(
			    std::format("Unknown char {}; skipping", input[pos])));
		} break;
		case '\n':
			line++;
			break;
		case ' ':
		case '\r':
		case '\t':
			break;
		case ';':
			result.push_back(token::Semicolon());
			break;
		case '(':
			result.push_back(token::RPar());
			break;
		case ')':
			result.push_back(token::RPar());
			break;
		case '{':
			result.push_back(token::LBrace());
			break;
		case '}':
			result.push_back(token::RBrace());
			break;
		case '+':
			result.push_back(token::Plus());
			break;
		case '-':
			result.push_back(token::Minus());
			break;
		case '*':
			result.push_back(token::Star());
			break;
		case '/':
			result.push_back(token::Slash());
			break;
		}
	}
	return result;
}