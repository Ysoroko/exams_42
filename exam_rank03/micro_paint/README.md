### Micro Paint ⏹️ ###

We have a point *P*, and a rectangle R with top left corner *TL*, and a bottom right corner *BR*

`P = (x ; y)`

`TL = (xtl ; ytl)`

`BR = (xbr ; ybr)`

The point P belongs to the rectangle R if:
- '*S*' type (entire square): 
  * `(x >= xtl && x <= xbr && y >= ytl && y <= ybr)` 
- '*s*' type (border only): 
  * '*S*' condition is met (the point's x and y coordinates are inside the rectangle limits)
  * `(x - xtl < 1 || xbr - x < 1 || y - ytl < 1 || ybr - y < 1)` 
