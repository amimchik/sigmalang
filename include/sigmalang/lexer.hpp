#pragma once

#include <cstdint>
#include <memory>
#include <print>
#include <sigmalang/diagnostics.hpp>
#include <sigmalang/token.hpp>
#include <string_view>
#include <vector>

namespace org::amimchik::sigmalang::lexer {
class Lexer {
   private:
	std::shared_ptr<diagnostics::IHandler> handler;
	std::string_view input;
	size_t pos;
	size_t line;

   public:
	Lexer(std::string_view input,
	      std::shared_ptr<diagnostics::IHandler> handler);
	std::vector<token::Any> tokenize();
};
}  // namespace org::amimchik::sigmalang::lexer