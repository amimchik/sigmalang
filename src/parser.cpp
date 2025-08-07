#include <sigmalang/parser.hpp>

using namespace org::amimchik::sigmalang::parser;
using namespace org::amimchik::sigmalang::lexer;
using namespace org::amimchik::sigmalang::diagnostics;

Parser::Parser(std::vector<token::Any> tokens,
               std::shared_ptr<IHandler> handler)
    : tokens(tokens), pos(0), handler(handler) {}

std::shared_ptr<ast::Node> Parser::parse() {
	// Pratt parsing
	return parseExpression(0);
}

token::Any Parser::peek() {
	/* std::println("GETTING {} token: {}", pos,
	             pos < tokens.size() ? tokens[pos] : token::EndOfFile());
	*/
	if (pos < tokens.size())
		return tokens[pos];
	else
		return token::EndOfFile();
}
token::Any Parser::take() {
	token::Any tok = peek();
	if (pos < tokens.size())
		pos++;
	return tok;
}

std::shared_ptr<ast::Node> Parser::parseExpression(int min_bp) {
	auto tok = take();
	std::shared_ptr<ast::Node> lhs;
	std::shared_ptr<ast::Node> rhs;

	// std::println("tok is {}", tok);
	if (std::holds_alternative<token::Number>(tok)) {
		lhs = std::make_shared<ast::Node>(
		    ast::Number(std::get<token::Number>(tok).value));
	} else if (std::holds_alternative<token::Minus>(tok)) {
		lhs = parseExpression(100);
		if (!lhs)
			return nullptr;
		lhs =
		    std::make_shared<ast::Node>(ast::UnExpr{ast::UnExprType::Neg, lhs});
	} else if (std::holds_alternative<token::LPar>(tok)) {
		//	std::println("Lpar captured");
		lhs = parseExpression(0);
		if (!std::holds_alternative<token::RPar>(take())) {
			handler->handle(Error("Expected ')' at the end of par expression"));
			return nullptr;
		}
	} else {
		handler->handle(Error(std::format("Unexpected token: {}", tok)));
	}

	for (;;) {
		tok = peek();

		if (std::holds_alternative<token::RPar>(tok) ||
		    std::holds_alternative<token::EndOfFile>(tok)) {
			break;
		}

		int lbp = getBp(tok);
		// std::println("Token = {}, LBP = {}, min_bp = {}", tok, lbp, min_bp);

		int rbp = lbp + 1;

		if (lbp < min_bp)
			break;

		take();
		rhs = parseExpression(rbp);
		if (!rhs)
			return nullptr;
		ast::BinExprType type;
		if (!std::visit(util::overload{
		                    [&](token::Plus) {
			                    type = ast::BinExprType::Add;
			                    return true;
		                    },
		                    [&](token::Minus) {
			                    type = ast::BinExprType::Min;
			                    return true;
		                    },
		                    [&](token::Star) {
			                    type = ast::BinExprType::Mul;
			                    return true;
		                    },
		                    [&](token::Slash) {
			                    type = ast::BinExprType::Div;
			                    return true;
		                    },
		                    [&](auto) {
			                    handler->handle(Error(std::format(
			                        "Unexpected token: {} 2", tok)));
			                    return false;
		                    },
		                },
		                tok)) {
			return nullptr;
		}
		lhs = std::make_shared<ast::Node>(ast::BinExpr{type, lhs, rhs});
	}
	return lhs;
}

int Parser::getBp(const token::Any &op) {
	return std::visit(util::overload{[](const token::Plus &) { return 10; },
	                                 [](const token::Minus &) { return 10; },
	                                 [](const token::Star &) { return 20; },
	                                 [](const token::Slash &) { return 20; },
	                                 [](auto &&) { return -1; }},
	                  op);
}