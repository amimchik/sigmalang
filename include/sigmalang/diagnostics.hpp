#pragma once

#include <format>
#include <iostream>
#include <string>
#include <variant>

namespace org::amimchik::sigmalang::diagnostics {
struct Warning {
	std::string message;
};
struct Error {
	std::string message;
};
using Any = std::variant<Warning, Error>;

class IHandler {
   public:
	virtual void handle(Any obj) = 0;
	virtual ~IHandler() = default;
};

class ConsoleLogHandler : public IHandler {
   public:
	void handle(Any obj) override;
	~ConsoleLogHandler() override = default;
};
}  // namespace org::amimchik::sigmalang::diagnostics