#pragma once

#include <box2d/box2d.h>

#include <jank/runtime/context.hpp>
#include <jank/runtime/convert.hpp>
#include <jank/runtime/core/make_box.hpp>
#include <jank/runtime/obj/persistent_array_map.hpp>

namespace jank::runtime
{
  template <>
  struct convert<b2Vec2>
  {
    static obj::persistent_array_map_ref into_object(b2Vec2 const &v)
    {
      static auto const x(__rt_ctx->intern_keyword("x").expect_ok());
      static auto const y(__rt_ctx->intern_keyword("y").expect_ok());

      return obj::persistent_array_map::create_unique(x, make_box(v.x), y, make_box(v.y));
    }

    static b2Vec2 from_object(object_ref const o)
    {
      static auto const x(__rt_ctx->intern_keyword("x").expect_ok());
      static auto const y(__rt_ctx->intern_keyword("y").expect_ok());
      return b2Vec2(o.get(x).to_real(), o.get(y).to_real());
    }
  };

  template <>
  struct convert<b2BodyId>
  {
    static obj::persistent_array_map_ref into_object(b2BodyId const &v)
    {
      static auto const generation(__rt_ctx->intern_keyword("generation").expect_ok());
      static auto const index1(__rt_ctx->intern_keyword("index1").expect_ok());
      static auto const world0(__rt_ctx->intern_keyword("world0").expect_ok());

      return obj::persistent_array_map::create_unique(
        generation, make_box(v.generation),
        index1, make_box(v.index1),
        world0, make_box(v.world0)
      );
    }

    static b2BodyId from_object(object_ref const o)
    {
      static auto const generation(__rt_ctx->intern_keyword("generation").expect_ok());
      static auto const index1(__rt_ctx->intern_keyword("index1").expect_ok());
      static auto const world0(__rt_ctx->intern_keyword("world0").expect_ok());

      return b2BodyId(
        o.get(generation).to_integer(),
        o.get(index1).to_integer(),
        o.get(world0).to_integer()
      );
    }
  };
}
