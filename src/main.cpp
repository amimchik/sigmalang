#include <print>
#include <sigmalang/diagnostics.hpp>
#include <sigmalang/lexer.hpp>

using namespace org::amimchik::sigmalang::lexer;
using namespace org::amimchik::sigmalang::diagnostics;

int main() {
	std::string input;
	std::print(">>> ");
	std::getline(std::cin, input);
	Lexer lexer(input, std::make_shared<ConsoleLogHandler>());
	auto tokens = lexer.tokenize();
	for (auto &token : tokens) {
		std::println("[{}]", token);
	}
	return 0;
}