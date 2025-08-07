#include <sigmalang/ast.hpp>

using namespace org::amimchik::sigmalang::parser::ast;
using namespace org::amimchik::sigmalang::util;

namespace ast = org::amimchik::sigmalang::parser::ast;

Number::Number(int64_t value) : value(value) {}

std::string ast::toString(const Node &node) {
	return std::visit(
	    overload{
	        [](const Number &num) { return std::format("{}", num.value); },
	        [](const VariableCall &vc) {
		        return std::format("vc:{}", vc.name);
	        },
	        [](const VarDecl &decl) {
		        return std::format("vd:{} = {}", decl.name,
		                           toString(*decl.value));
	        },
	        [](const UnExpr &expr) {
		        switch (expr.type) {
		        case UnExprType::Neg:
			        return std::format("-{}", toString(*expr.value));
		        default:
			        return std::format("UNKONOWN_UN_EXP({})",
			                           toString(*expr.value));
		        }
	        },
	        [](const BinExpr &expr) {
		        switch (expr.type) {
		        case BinExprType::Add:
			        return std::format("({} + {})", toString(*expr.left),
			                           toString(*expr.right));
		        case BinExprType::Min:
			        return std::format("({} - {})", toString(*expr.left),
			                           toString(*expr.right));
		        case BinExprType::Mul:
			        return std::format("({} * {})", toString(*expr.left),
			                           toString(*expr.right));
		        case BinExprType::Div:
			        return std::format("({} / {})", toString(*expr.left),
			                           toString(*expr.right));
		        default:
			        return std::format("UNKNOWN_BIN_EXP({}, {})",
			                           toString(*expr.left),
			                           toString(*expr.right));
		        }
	        },
	        [](auto &&) { return "UNKNOWN"; },
	    },
	    node);
}