Programming Assignment #2 (Cow roller coaster)
2018008040 김유성
I only changed SimpleScene.py. The rest of the files remain the same.

a) UI
  1) First, just click the cow. When you move the mouse after clicking the cow, the cow will follow the mouse. (horizontal dragging)

  2) Click once when you reach the position you want.

    2-1) When you click and drag the mouse, you can determine the height of the cow. (vertical dragging)

  3) Do 2) 6 times, and then cow will follow the route you determined.

  4) After 3 turns, the cow will be positioned at the first position of the previous circuit.

    4-1) One turn spends 6 seconds.

  All of the above processes can be repeated continuously.

b) 
  Vertical dragging implementation is almost same as horizontal positioning. But, if drag the mouse, coordinate values except height must be fixed.
  So, I added code to fix the value of currentPos[0] and currentPos[2] with pickInfo's coordinate values.

c)
  I implemented B spline curve by referring P.78 of pdf '13 splines'

d, e)
  Direction vector of the current cow can be obtained by differentiating the position vector of the current cow. (w.r.t time)
  So, I multiply [3 * (t ** 2), 2 * t, 1, 0] instead of [t ** 3, t ** 2, t, 1] by differentiating the vector with respect to t.
  The coordinate calculated above should be multiplied to the cow we want to draw(which means, [Result][space] = [cow])
  Therefore, I should put 'cow @ np.linalg.pinv(space)' in drawCow(). ([Result] = [cow][space]^-1)