#pragma once

#include <math.h>
#include <raylib.h>

inline void
DrawRectangleProLinesEx(Rectangle rec, Vector2 origin, float rotation, float lineThick, Color color)
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

inline void DrawCircleLinesEx(Vector2 center, float radius, float lineThick, Color color)
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

inline void DrawTriangleLinesEx(Vector2 v1, Vector2 v2, Vector2 v3, float lineThick, Color color)
{
  if(lineThick <= 0.0f)
  {
    return;
  }

  // DrawTriangle expects a specific winding order (in raylib's y-down screen
  // space, cross < 0 is the accepted one), so normalize the input.
  float cross = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
  if(cross == 0.0f)
  {
    return; // degenerate triangle
  }
  if(cross > 0.0f)
  {
    Vector2 tmp = v2;
    v2 = v3;
    v3 = tmp;
  }

  // Side lengths (a is opposite v1, b opposite v2, c opposite v3)
  float a = hypotf(v3.x - v2.x, v3.y - v2.y);
  float b = hypotf(v3.x - v1.x, v3.y - v1.y);
  float c = hypotf(v2.x - v1.x, v2.y - v1.y);
  float perimeter = a + b + c;

  // Incenter and inradius
  Vector2 incenter = { (a * v1.x + b * v2.x + c * v3.x) / perimeter,
                       (a * v1.y + b * v2.y + c * v3.y) / perimeter };
  float inradius = fabsf(cross) / perimeter; // = 2*area/perimeter

  // Like DrawRectangleLinesEx, thickness grows inward, so the outer edge
  // stays exactly on the given vertices. If the line is at least as thick
  // as the inradius, the result is a filled triangle.
  if(lineThick >= inradius)
  {
    DrawTriangle(v1, v2, v3, color);
    return;
  }

  // Shrinking the triangle toward the incenter by this factor moves every
  // edge inward by exactly lineThick, with clean mitered corners.
  float k = (inradius - lineThick) / inradius;
  Vector2 i1 = { incenter.x + (v1.x - incenter.x) * k, incenter.y + (v1.y - incenter.y) * k };
  Vector2 i2 = { incenter.x + (v2.x - incenter.x) * k, incenter.y + (v2.y - incenter.y) * k };
  Vector2 i3 = { incenter.x + (v3.x - incenter.x) * k, incenter.y + (v3.y - incenter.y) * k };

  // Three trapezoids between the outer and inner triangles, two triangles each
  DrawTriangle(v1, v2, i2, color);
  DrawTriangle(v1, i2, i1, color);
  DrawTriangle(v2, v3, i3, color);
  DrawTriangle(v2, i3, i2, color);
  DrawTriangle(v3, v1, i1, color);
  DrawTriangle(v3, i1, i3, color);
}
