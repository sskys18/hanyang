#!/usr/bin/env python3
# -*- coding: utf-8 -*
# see examples below
# also read all the comments below.
import glfw
from OpenGL.GL import *

import os
import sys
import pdb  # use pdb.set_trace() for debugging
import code  # or use code.interact(local=dict(globals(), **locals()))  for debugging.
import xml.etree.ElementTree as ET
import numpy as np
from PIL import Image
import math


def unitV(V):
    v = np.sqrt(V[1] * V[1] + V[2] * V[2] + V[0] * V[0])
    return (1. / v) * V


class Color:
    def __init__(self, R, G, B):
        self.color = np.array([R, G, B]).astype(np.float64)

    # Gamma corrects this color.
    # @param gamma the gamma value to use (2.2 is generally used).
    def gammaCorrect(self, gamma):
        inverseGamma = 1.0 / gamma;
        self.color = np.power(self.color, inverseGamma)

    def toUINT8(self):
        return (np.clip(self.color, 0, 1) * 255).astype(np.uint8)


class Box:
    def __init__(self, min, max, shader_name):
        self.min = min
        self.max = max
        self.shader_name = shader_name
        self.center = (1. / 2.) * (min + max)

    def get_box(self, udv, b):
        if (udv[0] == 0. or udv[1] == 0. or udv[2] == 0.): return np.Infinity
        tmax = (self.max[0] - b[0]) / udv[0]
        tmin = (self.min[0] - b[0]) / udv[0]

        if (tmin > tmax):
            tmin, tmax = tmax, tmin
        tmaxy = (self.max[1] - b[1]) / udv[1]
        tminy = (self.min[1] - b[1]) / udv[1]

        if (tminy > tmaxy):
            tminy, tmaxy = tmaxy, tminy
        if (tmax < tminy or tmin > tmaxy): return np.Infinity
        if (tmin < tminy): tmin = tminy
        if (tmax > tmaxy): tmax = tmaxy

        tmaxz = (self.max[2] - b[2]) / udv[2]
        tminz = (self.min[2] - b[2]) / udv[2]
        if (tminz > tmaxz):
            tminz, tmaxz = tmaxz, tminz
        if (tmax < tminz or tmin > tmaxz): return np.Infinity
        if (tmin < tminz): tmin = tminz
        if (tmax > tmaxz): tmax = tmaxz
        return tmin

    def surf_norm(self, sp, vp):
        cal = sp - self.center
        if (math.isclose(self.min[0], sp[0])):
            if (np.dot(np.array([-1., 0., 0.]), (cal)) > 0):
                return np.array([-1., 0., 0.])
            else:
                return np.array([1, 0, 0])
        elif (math.isclose(self.max[0], sp[0])):
            if (np.dot(np.array([1., 0., 0.]), (cal)) > 0):
                return np.array([1., 0., 0.])
            else:
                return np.array([-1, 0, 0])
        elif (math.isclose(self.min[1], sp[1])):
            if (np.dot(np.array([0., -1., 0.]), (cal)) > 0):
                return np.array([0., -1., 0.])
            else:
                return np.array([0, 1, 0])
        elif (math.isclose(self.max[1], sp[1])):
            if (np.dot(np.array([0., 1., 0.]), (cal)) > 0):
                return np.array([0., 1., 0.])
            else:
                return np.array([0, -1, 0])
        elif (math.isclose(self.min[2], sp[2])):
            if (np.dot(np.array([0., 0., -1]), (cal)) > 0):
                return np.array([0., 0., -1.])
            else:
                return np.array([0, 0, 1])
        elif (math.isclose(self.max[2], sp[2])):
            if (np.dot(np.array([0., 0., 1.]), (cal)) > 0):
                return np.array([0., 0., 1.])
            else:
                return np.array([0, 0, -1])
        else:
            print("ERROR!", sp)


class Sphere:
    def __init__(self, center, radius, shader_name):
        self.center = center
        self.radius = radius
        self.shader_name = shader_name

    def intersect(self, udv, p):
        i = self.center - p
        if (np.dot(i, udv) * np.dot(i, udv) - np.dot(i, i) + math.pow(self.radius, 2) < 0):
            return False
        else:
            return True

    def get_sphere(self, udv, p):
        s = self.center - p
        a = -1
        if (Sphere.intersect(self, udv, p)):
            a = np.dot(s, udv) - np.sqrt(np.dot(s, udv) * np.dot(s, udv) - np.dot(s, s) + math.pow(self.radius, 2))
        return a

    def surf_norm(self, surfacePoint, viewPoint):
        return unitV(surfacePoint - self.center)


class Light:
    def __init__(self, position, intensity):
        self.position = position
        self.intensity = intensity


class Shader:
    def __init__(self, name, type, diffuseColor, specularColor, exponent):
        self.name = name
        self.type = type
        self.diffuseColor = diffuseColor
        self.specularColor = specularColor
        self.exponent = exponent


def pixel_vector(vd, iHeight, iWidth, heightPsize, widthPsize, d, i, j, vUp):
    a = unitV(np.cross(vd, vUp))
    b = unitV(np.cross(vd, a))
    index = (d * vd) + (-(iWidth / 2)) * a + (-(iHeight) / 2) * b + ((iWidth / widthPsize) / 2) * a + (
                (iHeight / heightPsize) / 2) * b + ((iWidth / widthPsize) * j) * a + ((iHeight / heightPsize) * i) * b
    return unitV(index)


def main():
    tree = ET.parse(sys.argv[1])
    root = tree.getroot()
    # set default values
    viewDir = np.array([0, 0, -1]).astype(np.float64)
    viewUp = np.array([0, 1, 0]).astype(np.float64)
    ProjNormal = -1 * viewDir  # you can safely assume this. (no examples will use shifted perspective camera)
    viewWidth = 1.0
    viewHeight = 1.0
    projDistance = 1.0
    intensity = np.array([1, 1, 1]).astype(np.float64)  # how bright the light is.
    viewPoint = np.array([0, 0, 0])

    for c in root.findall('camera'):
        viewPoint = np.array(c.findtext('viewPoint').split()).astype(np.float64)
        viewDir = unitV(np.array(c.findtext('viewDir').split()).astype(np.float64))
        projNormal = unitV(np.array(c.findtext('projNormal').split()).astype(np.float64))
        viewUp = unitV(np.array(c.findtext('viewUp').split()).astype(np.float64))
        tmp_viewWidth = np.array(c.findtext('viewWidth').split()).astype(np.float64)
        tmp_viewHeight = np.array(c.findtext('viewHeight').split()).astype(np.float64)

        if (c.findtext('projDistance') != None):
            tmp_pd = np.array(c.findtext('projDistance').split()).astype(np.float64)
            projDistance = tmp_pd[0]
        viewWidth = tmp_viewWidth[0]
        viewHeight = tmp_viewHeight[0]

    imgSize = np.array(root.findtext('image').split()).astype(np.int64)

    shaderarr = {}
    for c in root.findall('shader'):
        shader_n_c = c.get('name')
        shader_t_c = c.get('type')
        diff_c = np.array(c.findtext('diffuseColor').split()).astype(np.float64)
        if (shader_t_c == "Phong"):
            spec_c = np.array(c.findtext('specularColor').split()).astype(np.float64)
            exponent_c = np.array(c.findtext('exponent').split()).astype(np.int64)
        else:
            spec_c = np.array([0, 0, 0])
            exponent_c = np.array([0])
        shaderarr[shader_n_c] = Shader(shader_n_c, shader_t_c, diff_c, spec_c, exponent_c)

    boxarr = []
    spherearr = []

    for c in root.findall('surface'):
        type_c = c.get('type')

        for b in c.iter('shader'):
            ref_c = b.get('ref')

        if (type_c == 'Sphere'):
            center_c = np.array(c.findtext('center').split()).astype(np.float64)
            radius_c = np.array(c.findtext('radius').split()).astype(np.float64)

            spherearr.append(Sphere(center_c, radius_c[0], ref_c))
        elif (type_c == 'Box'):
            minPt_c = np.array(c.findtext('minPt').split()).astype(np.float64)
            maxPt_c = np.array(c.findtext('maxPt').split()).astype(np.float64)
            boxarr.append(Box(minPt_c, maxPt_c, ref_c))

    number_of_sphere = len(spherearr)
    number_of_box = len(boxarr)

    lightarr = []
    for c in root.findall('light'):
        pos_c = np.array(c.findtext('position').split()).astype(np.float64)
        inten_c = np.array(c.findtext('intensity').split()).astype(np.float64)
        lightarr.append(Light(pos_c, inten_c))

    num_light = len(lightarr)

    ch = 3
    img = np.zeros((imgSize[1], imgSize[0], ch), dtype=np.uint8)
    img[:, :] = 0

    for i in np.arange(imgSize[1]):
        for j in np.arange(imgSize[0]):
            randered_surface = None
            pixel_shader = None
            pixel_f_color = None
            surfacePoint = None
            lightVector = None
            surfaceNormal = None

            pixelVector = pixel_vector(viewDir, viewHeight, viewWidth, imgSize[1], imgSize[0], projDistance, i, j,
                                       viewUp)
            infi = np.Infinity

            for k in np.arange(number_of_sphere):
                if (spherearr[k].intersect(pixelVector, viewPoint)):
                    if (infi > spherearr[k].get_sphere(pixelVector, viewPoint)):
                        infi = spherearr[k].get_sphere(pixelVector, viewPoint)
                        surfacePoint = (infi * pixelVector) + viewPoint
                        randered_surface = spherearr[k]
            for l in np.arange(number_of_box):
                if (infi > boxarr[l].get_box(pixelVector, viewPoint)):
                    infi = boxarr[l].get_box(pixelVector, viewPoint)
                    surfacePoint = (infi * pixelVector) + viewPoint
                    randered_surface = boxarr[l]

            if (randered_surface is not None and surfacePoint is not None):
                surfaceNormal = randered_surface.surf_norm(surfacePoint, viewPoint)
                pixel_shader = shaderarr[randered_surface.shader_name]
            else:
                pixel_shader = None

            sum = np.array([0, 0, 0])

            if (infi is not np.Infinity):
                tmp_color = np.array([0, 0, 0])

                for v in np.arange(num_light):
                    Blocked = False
                    lightVector = unitV(lightarr[v].position - surfacePoint)

                    for w in np.arange(number_of_sphere):
                        if (spherearr[w].get_sphere(lightVector, surfacePoint) > 0 and spherearr[w].get_sphere(
                                lightVector, surfacePoint) is not np.Infinity):
                            Blocked = True
                            break
                    if (not Blocked):
                        for y in np.arange(number_of_box):
                            if (boxarr[y].get_box(lightVector, surfacePoint) > 0 and boxarr[y].get_box(lightVector,
                                                                                                       surfacePoint) is not np.Infinity):
                                Blocked = True
                                break

                    if (not Blocked):
                        if (pixel_shader.type == "Phong"):
                            tmp_color = max(0, np.dot(surfaceNormal, lightVector)) * lightarr[
                                v].intensity * pixel_shader.diffuseColor + math.pow(
                                max(0, np.dot(surfaceNormal, unitV(lightVector - viewDir))), pixel_shader.exponent[0]) * \
                                        lightarr[v].intensity * pixel_shader.specularColor
                        elif (pixel_shader.type == "Lambertian"):
                            tmp_color = max(0, np.dot(surfaceNormal, lightVector)) * lightarr[
                                v].intensity * pixel_shader.diffuseColor

                    else:
                        tmp_color = np.array([0, 0, 0])
                    sum = sum + tmp_color

            pixel_f_color = sum
            cc = Color(pixel_f_color[0], pixel_f_color[1], pixel_f_color[2])
            cc.gammaCorrect(2.2)
            img[i][j] = cc.toUINT8()

    print("DONE!!!")
    rawimg = Image.fromarray(img, 'RGB')
    # rawimg.save('out.png')
    rawimg.save(sys.argv[1] + '.png')


if __name__ == "__main__":
    main()
