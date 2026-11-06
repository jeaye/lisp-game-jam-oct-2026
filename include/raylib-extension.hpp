#pragma once

#include <raylib.h>

void DrawRectangleProLinesEx(Rectangle rec,
                             Vector2 origin,
                             float rotation,
                             float lineThick,
                             Color color)
{
  if((lineThick > rec.width) || (lineThick > rec.height))
  {
    if(rec.width >= rec.height)
    {
      lineThick = rec.height / 2;
    }
    else
    {
      lineThick = rec.width / 2;
    }
  }

  // Edge layout in the rectangle's local (unrotated) space,
  // for rec = { x, y, 8, 6 } and lineThick = 2:
  //
  //   TTTTTTTT
  //   TTTTTTTT
  //   LL    RR
  //   LL    RR
  //   BBBBBBBB
  //   BBBBBBBB
  //
  // Each edge has a local offset (ox, oy) from the rectangle's top-left corner.
  // To draw an edge with DrawRectanglePro so it stays attached to the same pivot,
  // we keep rec.x/rec.y as the pivot's world position and shift the origin by
  // the edge's local offset: origin' = origin - offset.

  float innerHeight = rec.height - lineThick * 2.0f;

  // Top
  DrawRectanglePro((Rectangle){ rec.x, rec.y, rec.width, lineThick },
                   (Vector2){ origin.x, origin.y },
                   rotation,
                   color);

  // Bottom
  DrawRectanglePro((Rectangle){ rec.x, rec.y, rec.width, lineThick },
                   (Vector2){ origin.x, origin.y - (rec.height - lineThick) },
                   rotation,
                   color);

  // Left
  DrawRectanglePro((Rectangle){ rec.x, rec.y, lineThick, innerHeight },
                   (Vector2){ origin.x, origin.y - lineThick },
                   rotation,
                   color);

  // Right
  DrawRectanglePro((Rectangle){ rec.x, rec.y, lineThick, innerHeight },
                   (Vector2){ origin.x - (rec.width - lineThick), origin.y - lineThick },
                   rotation,
                   color);
}

void DrawCircleLinesEx(Vector2 center, float radius, float lineThick, Color color)
{
  if(lineThick <= 0.0f || radius <= 0.0f)
  {
    return;
  }

  // Like DrawRectangleLinesEx, the thickness grows inward from the given
  // radius, so the outer edge stays at `radius`. If the line is thicker
  // than the radius, this degrades to a filled circle.
  if(lineThick > radius)
  {
    lineThick = radius;
  }

  // segments = 0 lets raylib pick a smooth segment count from the radius
  DrawRing(center, radius - lineThick, radius, 0.0f, 360.0f, 0, color);
}
