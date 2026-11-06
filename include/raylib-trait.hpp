#pragma once

#include <raylib.h>

#include <jank/runtime/context.hpp>
#include <jank/runtime/convert.hpp>
#include <jank/runtime/core/make_box.hpp>
#include <jank/runtime/obj/persistent_array_map.hpp>

namespace jank::runtime
{
  template <>
  struct convert<Color>
  {
    static obj::persistent_array_map_ref into_object(Color const &v)
    {
      static auto const r(__rt_ctx->intern_keyword("r").expect_ok());
      static auto const g(__rt_ctx->intern_keyword("g").expect_ok());
      static auto const b(__rt_ctx->intern_keyword("b").expect_ok());
      static auto const a(__rt_ctx->intern_keyword("a").expect_ok());

      return obj::persistent_array_map::create_unique(
        r, make_box(v.r),
        g, make_box(v.g),
        b, make_box(v.b),
        a, make_box(v.a)
      );
    }

    static Color from_object(object_ref const o)
    {
      static auto const r(__rt_ctx->intern_keyword("r").expect_ok());
      static auto const g(__rt_ctx->intern_keyword("g").expect_ok());
      static auto const b(__rt_ctx->intern_keyword("b").expect_ok());
      static auto const a(__rt_ctx->intern_keyword("a").expect_ok());
      return Color(
        o.get(r).to_integer(),
        o.get(g).to_integer(),
        o.get(b).to_integer(),
        o.get(a).to_integer()
      );
    }
  };
}
