import tkinter as tk
import math
import csv

points = []
triangles = []
wireframe = 1 #changing this to 0 will display only dots
counter = 0


class Engine:
    def __init__(self, points, triangles, height=400, width=600, distance=6, scale=500):
        self.window = tk.Tk()
        self.window.title('Face')
        self.image = tk.Canvas(self.window, width=width, height=height)
        self.image.pack()
        self.height = height
        self.width = width
        self.distance = distance
        self.scale = scale
        self.points = points
        self.triangles = triangles
        self.shapes = []

    def flattenPoint(self, point):
        (x, y, z) = (point[0], point[1], point[2])
        projectedY = int(self.height / 2 + ((y * self.distance) / (z + self.distance)) * self.scale)
        projectedX = int(self.width / 2 + ((x * self.distance) / (z + self.distance)) * self.scale)
        return (projectedX, projectedY)

    def createTriangle(self, points):
        a, b, c = points[0], points[1], points[2]
        coords = [a[0], a[1], b[0], b[1], c[0], c[1]]
        self.shapes.append(self.image.create_polygon(coords, fill="", outline="black"))


    def drawPoint(self, pointX, pointY):
        self.image.create_line(pointX, pointY, pointX+1, pointY, fill = "black")


    def clear(self):
        self.image.delete('all')
    def render(self):
        global counter
        coords = []
        
        for point in self.points:
            #self.rotate('y', 180, point)
            coords.append(self.flattenPoint(self.rotate('y', counter, self.rotate('x', 270, point))))
        for coord in coords:
            self.drawPoint(coord[0],coord[1])
        if(wireframe == 1):
            for triangle in self.triangles:
                self.createTriangle((coords[triangle[0]],coords[triangle[1]], coords[triangle[2]]))
        self.image.update()

    
    def rotate(self, axis, angle, point):
        #rotate point around axis
        (x,y,z) = (point[0], point[1], point[2])
        angle = angle / 450 * 180 / math.pi
        if axis == 'z':
            #rotate aroud Z axis
            newX = x * math.cos(angle) - y * math.sin(angle)
            newY = y * math.cos(angle) + x * math.sin(angle)
            newZ = z
        elif axis == 'x':
            #rotate around X axis
            newY = y * math.cos(angle) - z * math.sin(angle)
            newZ = z * math.cos(angle) + y * math.sin(angle)
            newX = x
        elif axis == 'y':
            #rotate around Y axis
            newX = x * math.cos(angle) - z * math.sin(angle)
            newZ = z * math.cos(angle) + x * math.sin(angle)
            newY = y
        else:
            raise ValueError('invalid rotation axis')
        x = newX
        y = newY
        z = newZ
        return(x, y, z)

    

#gets vertices into list
with open('face-vertices.txt') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:    
        points.append((float(row[0]), float(row[1]), float(row[2])))

with open('face-index.txt') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for index in csv_reader:
        triangles.append((int(index[0]), int(index[1]), int(index[2])))
        


def rotateRight():
    global counter
    counter = counter + 1

def rotateLeft():
    global counter
    counter = counter - 1

test = Engine(points,triangles)

control = tk.Tk()

rotateRight = tk.Button(control, text="Rotate Right", fg = "black", command = rotateRight)
rotateLeft = tk.Button(control, text="Rotate Left", fg = "black", command = rotateLeft)
rotateRight.pack()
rotateLeft.pack()

while True:
    test.clear()
    test.render()

