import math
import matplotlib.pyplot
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.style as style

result = []
frame = []
min_dis_point_pair = []

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

def dist(p1, p2):
    dx = p1.x - p2.x
    dy = p1.y - p2.y
    return math.sqrt(dx * dx + dy * dy)

def plotPoints(frame, Points):
    for point in Points:
        frame += plt.plot(point.x, point.y, "ko")
    return frame

def plotSeg(x1, y1, x2, y2, c):
    return plt.plot([x1, x2], [y1, y2], color = c)

def brute_force(Points):
    global min_dis_point_pair
    n = Points.__len__()
    ans = 10000000
    for i in range(0, n):
        frame1 = frame.copy()
        frame1 += [plt.annotate('i', xy = [Points[i].x - 3, Points[i].y])]
        result.append(frame1 + min_dis_point_pair)
        for j in range(i + 1, n):
            frame2 = frame1.copy()
            frame2 += [plt.annotate('j', xy = [Points[j].x - 3, Points[j].y])]
            frame2 += plotSeg(Points[i].x, Points[i].y, Points[j].x, Points[j].y, 'c')
            result.append(frame2 + min_dis_point_pair)
            if (dist(Points[i], Points[j]) < ans):
                ans = dist(Points[i], Points[j])
                min_dis_point_pair = []
                min_dis_point_pair = plotSeg(Points[i].x, Points[i].y, Points[j].x, Points[j].y, 'pink')
                min_dis_point_pair += plt.plot(Points[i].x, Points[i].y, 'r')
                min_dis_point_pair += plt.plot(Points[j].x, Points[j].y, 'r')
    return ans

if __name__ == '__main__':
    n = int(input())
    minx = 1000000
    miny = 1000000
    maxx = -1000000
    maxy = -1000000
    Points = []
    for i in range(n):
        x, y = map(int, input().split(' '))
        Points.append(Point(x, y))
        minx = min(x, minx)
        miny = min(y, miny)
        maxx = max(x, maxx)
        maxy = max(y, maxy)

    plt.switch_backend('Tkagg')
    fig = plt.figure()
    plt.xlim(minx - 20, maxx + 20)
    plt.ylim(miny - 20, maxy + 20)

    # init
    frame = []
    frame = plotPoints(frame, Points)
    result.append(frame)

    ans = brute_force(Points)
    print(ans)
    tmp = frame.copy()
    tmp += [plt.annotate('ans=%.3f' % ans, xy=[(minx + maxx) / 2, (miny + maxy) / 2])]
    result.append(tmp + min_dis_point_pair)

    ain = animation.ArtistAnimation(fig=fig, artists=result, interval=500)
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