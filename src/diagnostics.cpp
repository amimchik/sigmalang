#include <sigmalang/diagnostics.hpp>
#include <sigmalang/util.hpp>

using namespace org::amimchik::sigmalang::diagnostics;
using namespace org::amimchik::sigmalang::util;

void ConsoleLogHandler::handle(Any obj) {
	std::cerr << std::visit(
	                 overload{[](const Warning& w) {
		                          return std::format("[WARN]: {}", w.message);
	                          },
	                          [](const Error& e) {
		                          return std::format("[ERROR]: {}", e.message);
	                          }},
	                 obj)
	          << std::endl;
}