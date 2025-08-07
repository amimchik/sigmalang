#include <print>
#include <sigmalang/diagnostics.hpp>
#include <sigmalang/lexer.hpp>
#include <sigmalang/parser.hpp>

using namespace org::amimchik::sigmalang::lexer;
using namespace org::amimchik::sigmalang::parser;
using namespace org::amimchik::sigmalang::diagnostics;

int main() {
	/*std::println("{}", ast::toString(ast::BinExpr{
	                       ast::BinExprType::Add,
	                       std::make_shared<ast::Node>(ast::Number(2)),
	                       std::make_shared<ast::Node>(ast::Number(2))}));
	 */
	while (true) {
		std::print(">>> ");
		std::string input;
		if (!std::getline(std::cin, input))
			break;
		Lexer lexer(input, std::make_shared<ConsoleLogHandler>());
		auto tokens = lexer.tokenize();
		Parser parser(tokens, std::make_shared<ConsoleLogHandler>());
		auto ast = parser.parse();
		if (!ast)
			continue;
		std::println("{}", ast::toString(*ast));
	}
	std::println();
	return 0;
}