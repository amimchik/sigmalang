#pragma once
#include <format>
#include <sigmalang/util.hpp>
#include <string>
#include <variant>

namespace org::amimchik::sigmalang::lexer::token {
enum class Keyword {
	RETURN,
	FUNC,
};
struct Identifier {
	std::string value;
};
struct Number {
	int64_t value;
};
struct LPar {};
struct RPar {};
struct LBrace {};
struct RBrace {};
struct Semicolon {};
struct Plus {};
struct Minus {};
struct Star {};
struct Slash {};
struct EndOfFile {};
using Any =
    std ::variant<Keyword, Identifier, LPar, RPar, LBrace, RBrace, Semicolon,
                  Number, Plus, Minus, Star, Slash, EndOfFile>;
}  // namespace org::amimchik::sigmalang::lexer::token

namespace token = org::amimchik::sigmalang::lexer::token;

namespace std {
template <>
struct formatter<token::Any> {
	constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

	template <typename FormatContext>
	auto format(const token::Any& tok, FormatContext& ctx) const {
		using namespace token;

		std::string s = std::visit(
		    org::amimchik::sigmalang::util::overload{
		        [](const Keyword& kw) -> std::string {
			        switch (kw) {
			        case Keyword::RETURN:
				        return "kw::return";
			        case Keyword::FUNC:
				        return "kw::func";
			        }
			        return "kw::???";
		        },
		        [](const Identifier& id) {
			        return std::format("id:{}", id.value);
		        },
		        [](const Number& num) {
			        return std::format("num:{}", num.value);
		        },
		        [](const LPar&) { return std::string("lpar"); },
		        [](const RPar&) { return std::string("rpar"); },
		        [](const LBrace&) { return std::string("lbrace"); },
		        [](const RBrace&) { return std::string("rbrace"); },
		        [](const Semicolon&) { return std::string("semicolon"); },
		        [](const Plus&) { return std::string("plus"); },
		        [](const Minus&) { return std::string("minus"); },
		        [](const Star&) { return std::string("star"); },
		        [](const Slash&) { return std::string("slash"); },
		        [](const EndOfFile&) { return std::string("EOF"); },
		    },
		    tok);

		return std::format_to(ctx.out(), "{}", s);
	}
};
}  // namespace std