import glfw
from OpenGL.GL import *
import numpy as np

pl_type = {1: GL_POINTS, 2: GL_LINES, 3: GL_LINE_STRIP, 4: GL_LINE_LOOP, 5: GL_TRIANGLES,
           6: GL_TRIANGLE_STRIP, 7: GL_TRIANGLE_FAN, 8: GL_QUADS, 9: GL_QUAD_STRIP, 0: GL_POLYGON}


def key_callback(window, key, scancode, action, mods):
    global number
    if key == glfw.KEY_1:
        if action == glfw.PRESS:
            number = 1
    elif key == glfw.KEY_2:
        if action == glfw.PRESS:
            number = 2
    elif key == glfw.KEY_3:
        if action == glfw.PRESS:
            number = 3
    elif key == glfw.KEY_4:
        if action == glfw.PRESS:
            number = 4
    elif key == glfw.KEY_5:
        if action == glfw.PRESS:
            number = 5
    elif key == glfw.KEY_6:
        if action == glfw.PRESS:
            number = 6
    elif key == glfw.KEY_7:
        if action == glfw.PRESS:
            number = 7
    elif key == glfw.KEY_8:
        if action == glfw.PRESS:
            number = 8
    elif key == glfw.KEY_9:
        if action == glfw.PRESS:
            number = 9
    elif key == glfw.KEY_0:
        if action == glfw.PRESS:
            number = 0

def render(num):
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()
    glBegin(pl_type[num])
    glColor3ub(255, 255, 255)
    for i in np.linspace(0, 360, 13):
        th = np.radians(i)
        glVertex2fv(np.array([np.cos(th), np.sin(th)]))
    glEnd()

def main():
    global number
    if not glfw.init():
        return
    window = glfw.create_window(480, 480, "2018008040-2-2", None, None)
    if not window:
        glfw.terminate()
        return
    glfw.set_key_callback(window, key_callback)
    glfw.make_context_current(window)
    glfw.swap_interval(1)

    while not glfw.window_should_close(window):
        glfw.poll_events()
        render(number)
        glfw.swap_buffers(window)
    glfw.terminate()


if __name__ == "__main__":
    number = 4
    main()
