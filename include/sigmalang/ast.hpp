#pragma once

#include <cstdint>
#include <format>
#include <memory>
#include <print>
#include <sigmalang/util.hpp>
#include <string>
#include <variant>

namespace org::amimchik::sigmalang::parser::ast {

struct Node;

struct Number {
	int64_t value;
	Number(int64_t value);
};

struct VariableCall {
	std::string name;
};

enum class BinExprType { Add, Min, Mul, Div };

struct BinExpr {
	BinExprType type;
	std::shared_ptr<Node> left, right;
};

enum class UnExprType { Neg };

struct UnExpr {
	UnExprType type;
	std::shared_ptr<Node> value;
};

struct VarDecl {
	std::string name;
	std::shared_ptr<Node> value;
};

struct Node : std::variant<Number, VariableCall, BinExpr, UnExpr, VarDecl> {
	using variant::variant;
};

std::string toString(const Node &node);
}  // namespace org::amimchik::sigmalang::parser::ast