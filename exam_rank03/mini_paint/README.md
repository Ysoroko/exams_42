### Mini Paint ⏺️ ###

We have a point *P*, and a circle *Cir* with its center *C* and a radius *radius*

The distance from the point *P* to the center of the circle is defined as *dist*

`P = (x ; y)`

`C = (xc ; yc)`

The point *P* belongs to the circle *Cir* if:
- '*C*' type (entire circle): 
  * `(dist <= radius)` 
- '*c*' type (border only): 
  * '*C*' condition is met (the point's x and y coordinates are inside the circle's limits)
  * `(radius - dist < 1)` 
