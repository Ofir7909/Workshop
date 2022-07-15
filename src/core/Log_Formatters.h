#pragma once

#include "Log.h"
#include <glm/detail/qualifier.hpp>
#include <glm/glm.hpp>

// glm Vectors

template<int N, typename T, glm::qualifier Q>
struct fmt::formatter<glm::vec<N, T, Q>>
{
	using Vec = glm::vec<N, T, Q>;
	constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) { return ctx.end(); }

	template<typename FormatContext>
	auto format(const Vec& v, FormatContext& ctx) -> decltype(ctx.out())
	{
		std::stringstream ss;
		ss << "Vec" << N << "<";
		for (int i = 0; i < N; i++) { ss << v[i] << ((i != N - 1) ? "," : ""); }
		ss << ">";

		return std::format_to(ctx.out(), "{}", ss.str());
	}
};
