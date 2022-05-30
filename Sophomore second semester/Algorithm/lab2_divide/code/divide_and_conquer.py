import matplotlib.pyplot
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.style as style
import math
import numpy as np

result = [] # every frame of image
frames = [] # a frame stack
min_dis_point_pair = []
ans = 10000000

colors = ['mediumblue', 'mediumorchid', 'mediumvioletred']

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


def cmpx(p1, p2):
    return p1.x < p2.x


def cmpy(p1, p2):
    return p1.y < p2.y


def dist(p1, p2):
    dx = p1.x - p2.x
    dy = p1.y - p2.y
    return math.sqrt(dx * dx + dy * dy)


def sort(Points, cmp):
    n = Points.__len__()
    for i in range(n):
        k = i
        while (k > 0 and cmp(Points[k], Points[k - 1]) == True):
            Points[k], Points[k - 1] = Points[k - 1], Points[k]
            k -= 1

def plotSeg(x1, y1, x2, y2, c):
    return plt.plot([x1, x2], [y1, y2], color = c)

def plotPoints(frame, Points):
    for point in Points:
        frame += plt.plot(point.x, point.y, "ko")
    return frame

def plotRectangle(frame, x1, y1, x2, y2, c):
    frame += plotSeg(x1, y1, x2, y1, c)
    frame += plotSeg(x1, y1, x1, y2, c)
    frame += plotSeg(x2, y1, x2, y2, c)
    frame += plotSeg(x2, y2, x1, y2, c)
    return frame

def divide(Points, l, r, dep):
    global min_dis_point_pair
    global ans
    if (l == r): return 10000000
    if (l + 1 == r):
        t = dist(Points[l], Points[r])
        if (t < ans):
            ans = t
            min_dis_point_pair = []
            min_dis_point_pair = plotSeg(Points[l].x, Points[l].y, Points[r].x, Points[r].y, 'pink')
            min_dis_point_pair += plt.plot(Points[l].x, Points[l].y, "r")
            min_dis_point_pair += plt.plot(Points[r].x, Points[r].y, "r")
        return t

    mid = int((l + r) / 2)
    midx = Points[mid].x

    boundary = (Points[mid].x + Points[mid + 1].x) / 2;

    # the first part of division
    frame = frames[-1].copy()
    frame = plotRectangle(frame, Points[l].x - 1, miny + dep, boundary, maxy - dep, colors[dep])
    result.append(frame + min_dis_point_pair)
    frames.append(frame)
    d1 = divide(Points, l, mid, dep + 1)

    # the second part of division
    frame = frames[-1].copy()
    frame = plotRectangle(frame, boundary + 1, miny + dep, Points[r].x + 1, maxy - dep, colors[dep])
    result.append(frame + min_dis_point_pair)
    frames.append(frame)
    d2 = divide(Points, mid + 1, r, dep + 1)

    frames.pop()
    frames.pop()

    d = min(d1, d2)

    # plot the boundary
    frame = frames[-1].copy()
    frame += plotSeg(midx, miny + dep, midx, maxy - dep, 'red')
    frame += plotSeg(midx - d, miny + dep, midx - d, maxy - dep, 'green')
    frame += plotSeg(midx + d, miny + dep, midx + d, maxy - dep, 'green')
    frame += [plt.annotate('d=%.3f'%d, xy = [midx - 3, maxy - dep + 1])]
    result.append(frame + min_dis_point_pair)

    temp = []
    for i in range(l, r + 1):
        if (midx - d <= Points[i].x and Points[i].x <= midx + d):
            temp.append(Points[i])

    sort(temp, cmpy)

    cnt = temp.__len__()
    for i in range(cnt):
        temp_frame = frame.copy()
        temp_frame += [plt.annotate('i', xy = [temp[i].x - 3, temp[i].y])]
        result.append(temp_frame + min_dis_point_pair)
        for j in range(i + 1, cnt):
            if (temp[j].y - temp[i].y >= d):
                break
            temp_copy = temp_frame.copy()
            temp_copy += [plt.annotate('j', xy = [temp[j].x - 3, temp[j].y])]
            temp_copy += plotSeg(temp[i].x, temp[i].y, temp[j].x, temp[j].y, 'c')
            result.append(temp_copy + min_dis_point_pair)
            if (dist(temp[i], temp[j]) < d):
                d = dist(temp[i], temp[j])
            if (dist(temp[i], temp[j]) < ans):
                ans = dist(temp[i], temp[j])
                min_dis_point_pair = []
                min_dis_point_pair = plotSeg(temp[i].x, temp[i].y, temp[j].x, temp[j].y, 'pink')
                min_dis_point_pair += plt.plot(temp[i].x, temp[i].y, "r")
                min_dis_point_pair += plt.plot(temp[j].x, temp[j].y, "r")


    result.append(frames[-1] + min_dis_point_pair)
    return d

if __name__ == '__main__':
    # style.use('ggplot')
    plt.switch_backend('Tkagg')
    Points = []
    minx = miny = 100000000
    maxx = maxy = -100000000

    n = int(input())
    for i in range(n):
        x, y = map(int, input().split(' '))
        Points.append(Point(x, y));
        minx = min(x, minx)
        miny = min(y, miny)
        maxx = max(x, maxx)
        maxy = max(y, maxy)
    sort(Points, cmpx);

    fig = plt.figure()
    plt.xlim(minx - 20, maxx + 20)
    plt.ylim(miny - 20, maxy + 20)

    # init
    init = []
    init = plotPoints(init, Points)
    result.append(init)

    frame = init.copy()
    frame = plotRectangle(frame, minx - 5, maxy + 5, maxx + 5, miny - 5, 'yellow')
    result.append(frame)
    frames.append(frame)
    print(divide(Points, 0, n - 1, 0))
    tmp = frame.copy()
    tmp += [plt.annotate('ans=%.3f'%ans, xy = [(minx + maxx) / 2, (miny + maxy) / 2])]
    result.append(tmp + min_dis_point_pair)

    ain = animation.ArtistAnimation(fig = fig, artists = result, interval = 500)
    plt.show()

'''
10
0 8
17 80
6 81
26 43
63 14
32 48
41 33
28 70
50 0
68 87
'''

