#pragma once

#include <format>
#include <sigmalang/ast.hpp>
#include <sigmalang/diagnostics.hpp>
#include <sigmalang/lexer.hpp>
#include <sigmalang/util.hpp>
#include <stdexcept>

namespace org::amimchik::sigmalang::parser {
class Parser {
   private:
	std::vector<lexer::token::Any> tokens;
	size_t pos;
	std::shared_ptr<diagnostics::IHandler> handler;
	std::shared_ptr<ast::Node> parseExpression(int min_bp);
	int getBp(const lexer::token::Any &op);
	lexer::token::Any take();
	lexer::token::Any peek();

   public:
	Parser(std::vector<lexer::token::Any> tokens,
	       std::shared_ptr<diagnostics::IHandler> handler);
	std::shared_ptr<ast::Node> parse();
};
};  // namespace org::amimchik::sigmalang::parser