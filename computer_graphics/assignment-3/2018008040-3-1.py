import glfw
from OpenGL.GL import *
import numpy as np

def key_callback(window, key, scancode, action, mods):
    global mode
    if key == glfw.KEY_Q:
        if action == glfw.PRESS:
            mode = "Q"
    elif key == glfw.KEY_E:
        if action == glfw.PRESS:
            mode = "E"
    elif key == glfw.KEY_A:
        if action == glfw.PRESS:
            mode = "A"
    elif key == glfw.KEY_D:
        if action == glfw.PRESS:
            mode = "D"
    elif key == glfw.KEY_1:
        if action == glfw.PRESS:
            mode = "1"
    elif key == glfw.KEY_W:
        if action == glfw.PRESS:
            mode = "W"
    elif key == glfw.KEY_S:
        if action == glfw.PRESS:
            mode = "S"

def render(T):
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()
    # draw cooridnate
    glBegin(GL_LINES)

    glColor3ub(255, 0, 0)
    glVertex2fv(np.array([0.,0.]))
    glVertex2fv(np.array([1.,0.]))
    glColor3ub(0, 255, 0)
    glVertex2fv(np.array([0.,0.]))
    glVertex2fv(np.array([0.,1.]))
    glEnd()
    # draw triangle
    glBegin(GL_TRIANGLES)
    glColor3ub(255, 255, 255)
    glVertex2fv( (T @ np.array([.0,.5,1.]))[:-1] )
    glVertex2fv( (T @ np.array([.0,.0,1.]))[:-1] )
    glVertex2fv( (T @ np.array([.5,.0,1.]))[:-1] )
    glEnd()

def main():
    global mode
    global gComposedM
    if not glfw.init():
        return
    window = glfw.create_window(480, 480, "2018008040-3-1", None, None)
    if not window:
        glfw.terminate()
        return
    glfw.set_key_callback(window, key_callback)
    glfw.make_context_current(window)
    glfw.swap_interval(1)

    while not glfw.window_should_close(window):
        glfw.poll_events()
        newM = np.identity(3)
        if mode == "Q":
            newM[0,2] = -.1
            gComposedM = newM @ gComposedM
        elif mode == "E":
            newM[0,2] = .1
            gComposedM = newM @ gComposedM
        elif mode == "A":
            t = np.radians(10)
            newM[:2,:2] = np.array([[np.cos(t), -np.sin(t)], [np.sin(t), np.cos(t)]])
            gComposedM = gComposedM @ newM
        elif mode == "D":
            t = np.radians(-10)
            newM[:2, :2] = np.array([[np.cos(t), -np.sin(t)], [np.sin(t), np.cos(t)]])
            gComposedM = gComposedM @ newM
        elif mode == "1":
            gComposedM = np.identity(3)
        elif mode == "W":
            newM[0,0] = 0.9
            gComposedM = newM @ gComposedM
        elif mode == "S":
            t = np.radians(10)
            newM[:2, :2] = np.array([[np.cos(t), -np.sin(t)], [np.sin(t), np.cos(t)]])
            gComposedM = newM @ gComposedM
        render(gComposedM)
        mode = "0"
        glfw.swap_buffers(window)
    glfw.terminate()


if __name__ == "__main__":
    gComposedM = np.identity(3)
    mode = "0"
    main()