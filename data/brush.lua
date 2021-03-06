CV:run([[
// this config defines various heightmap brushes

// a brush has two parts: the brushmap and the brushhandle

// the brushmap is a 2D field that defines how the brush affects a heightmap

// the brushhandle is a 2D vertex on the brushmap.
// this handle is a reference point on the brushmap which represents
// where the editing cursor is pointed at.

// clearbrush                   : resets the brushmap
// brushvert <x> <y> <value>    : set a point on the brushmap
// brushx <x>                   : the x coordinate of the brushhandle
// brushy <y>                   : the y coordinate of the brushhandle

// copybrush                    : copies the current heightmap as a brush. cursor location becomes handle
// savebrush <name>             : saves the current brush in script form into mybrushes.cfg

brushhandle = [
  brushx $arg1
  brushy $arg2
]

brushindex = -1
brushmax = -1                // make sure to bump this up if you add more brushes

selectbrush = [
  brushindex = ( + $brushindex $arg1 )
  if (< $brushindex 0) [ brushindex = $brushmax ]
  if (> $brushindex $brushmax) [ brushindex = 0 ]
  do [brush_@brushindex]
  echo $brushname
]

brushverts = [
  loop y (listlen $arg1) [
    bv = (at $arg1 $y)
    loop x (listlen $bv) [
      brushvert $x $y (at $bv $x)
    ]
  ]
]

newbrush = [
  brushmax = (+ $brushmax 1)
  do [ 
    brush_@brushmax = [
      brushname = [@@@arg1]
      clearbrush
      @@(if (> $numargs 1) [result [ brushhandle @arg2 @arg3; brushverts [@@arg4] ] ])
    ]
  ]
]

newbrush "Circle 1-0 Brush" 0 0 [1]
newbrush "Circle 2-1 Brush" 2 2 [
    ""
    "0 0 1 "
    "0 1 2 1 "
    "0 0 1 "
]
newbrush "Circle 4-2-1 Brush" 2 2 [
  "0 0 1 "
  "0 1 2 1 "
  "1 2 4 2 1 "
  "0 1 2 1 "
  "0 0 1 "
]
newbrush "Square 3x3 brush" 1 1 [
  "1 1 1 "
  "1 1 1 "
  "1 1 1 "
]
newbrush "Square 5x5 brush" 2 2 [
  "1 1 1 1 1 "
  "1 1 1 1 1 "
  "1 1 1 1 1 "
  "1 1 1 1 1 "
  "1 1 1 1 1 "
]
newbrush "Square 7x7 brush" 3 3 [
  "1 1 1 1 1 1 1 "
  "1 1 1 1 1 1 1 "
  "1 1 1 1 1 1 1 "
  "1 1 1 1 1 1 1 "
  "1 1 1 1 1 1 1 "
  "1 1 1 1 1 1 1 "
  "1 1 1 1 1 1 1 "
]

newbrush "Smooth 3x3 brush" 1 1 [
  "0 0 0 "
  "0 "
  "0 "
]
newbrush "Smooth 5x5 brush" 2 2 [
  "0 0 0 0 0 "
  "0 "
  "0 "
  "0 "
  "0 "
]
newbrush "Smooth 7x7 brush" 3 3 [
  "0 0 0 0 0 0 0"
  "0 "
  "0 "
  "0 "
  "0 "
  "0 "
  "0 "
]

newbrush "Noise 25x25 Brush" 12 12 [
  "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 "
  ""
  "0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 1 1 0 1 "
  "0 0 0 0 0 1 0 0 0 1 0 0 0 0 1 0 1 0 0 1 0 0 2 2 "
  "0 0 0 0 1 1 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 1 "
  "0 0 0 0 0 1 0 0 0 0 0 2 0 0 0 0 1 0 0 0 1 1 0 0 1 "
  "0 0 1 0 0 0 1 0 1 1 0 0 0 0 1 0 0 1 0 0 0 0 2 "
  "0 0 0 1 0 1 1 0 0 0 0 0 0 0 0 0 0 1 1 1 2 "
  "0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 1 1 "
  "0 0 0 0 1 1 1 0 0 1 0 0 0 0 0 0 0 0 1 0 0 1 0 1 "
  "0 1 0 2 0 1 1 1 1 0 0 1 0 0 0 0 1 "
  "0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 1 1 0 1 1 "
  "1 0 1 0 0 0 0 0 1 0 0 0 1 0 1 "
  "0 0 0 0 0 0 0 1 1 0 1 1 0 0 1 0 0 1 0 0 0 0 1 0 0 1 "
  "0 1 1 1 0 3 0 2 0 0 0 1 1 0 0 0 1 1 "
  "0 0 1 0 0 1 0 0 1 0 1 1 0 1 0 0 0 0 0 1 "
  "0 0 1 1 0 0 0 0 2 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1 1 "
  "0 1 1 0 1 0 0 1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 1 "
  "1 0 0 0 0 0 1 0 0 1 0 0 1 0 0 0 0 0 0 0 1 0 0 1 0 1 "
  "0 0 0 1 0 0 1 0 1 1 0 0 0 0 0 0 0 1 "
  "0 0 0 0 0 0 1 1 1 0 1 1 1 0 0 0 0 0 0 0 0 0 0 1 "
  "0 0 0 0 1 0 1 1 0 2 0 0 0 0 0 1 0 0 0 1 0 0 0 0 1 "
  "0 0 0 0 0 0 0 0 0 1 0 1 "
  "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 "
]

do [ brush_2 ] // 421

]])

-- Texture blending

Blend.brush.add("Circle, 16px, soft", "packages/brushes/circle_16_soft.png")
Blend.brush.add("Circle, 16px, hard", "packages/brushes/circle_16_hard.png")
Blend.brush.add("Circle, 16px, solid", "packages/brushes/circle_16_solid.png")
Blend.brush.add("Circle, 32px, soft", "packages/brushes/circle_32_soft.png")
Blend.brush.add("Circle, 32px, hard", "packages/brushes/circle_32_hard.png")
Blend.brush.add("Circle, 32px, solid", "packages/brushes/circle_32_solid.png")
Blend.brush.add("Circle, 64px, soft", "packages/brushes/circle_64_soft.png")
Blend.brush.add("Circle, 64px, hard", "packages/brushes/circle_64_hard.png")
Blend.brush.add("Circle, 64px, solid", "packages/brushes/circle_64_solid.png")
Blend.brush.add("Circle, 128px, soft", "packages/brushes/circle_128_soft.png")
Blend.brush.add("Circle, 128px, hard", "packages/brushes/circle_128_hard.png")
Blend.brush.add("Circle, 128px, solid", "packages/brushes/circle_128_solid.png")
Blend.brush.add("Noise, 64px", "packages/brushes/noise_64.png")
Blend.brush.add("Noise, 128px", "packages/brushes/noise_128.png")
Blend.brush.add("Square, 16px, hard", "packages/brushes/square_16_hard.png")
Blend.brush.add("Square, 16px, solid", "packages/brushes/square_16_solid.png")
Blend.brush.add("Square, 32px, hard", "packages/brushes/square_32_hard.png")
Blend.brush.add("Square, 32px, solid", "packages/brushes/square_32_solid.png")
Blend.brush.add("Square, 64px, hard", "packages/brushes/square_64_hard.png")
Blend.brush.add("Square, 64px, solid", "packages/brushes/square_64_solid.png")
Blend.brush.add("Gradient, 16px", "packages/brushes/gradient_16.png")
Blend.brush.add("Gradient, 32px", "packages/brushes/gradient_32.png")
Blend.brush.add("Gradient, 64px", "packages/brushes/gradient_64.png")
Blend.brush.add("Gradient, 128px", "packages/brushes/gradient_128.png")
