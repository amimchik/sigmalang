#pragma once

namespace org::amimchik::sigmalang::util {
template <class... Ts>
struct overload : Ts... {
	using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;
}  // namespace org::amimchik::sigmalang::util