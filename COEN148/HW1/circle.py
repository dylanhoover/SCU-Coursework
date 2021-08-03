from PIL import Image
from PIL import ImageDraw
from PIL import ImageColor

def circle(r):
    d = (5/4) - r
    x = 0
    y = r
    points = set()

    while x <= y:
        points.add((x,-y))
        points.add((y,-x))
        points.add((y,x))
        points.add((x,y))
        points.add((-x,y))
        points.add((-y,x))
        points.add((-y,-x))
        points.add((-x,-y))
        if d < 0:
            d = d + (2 * x) + 3
            x = x + 1
        else:
            d = d + (2 * (x - y)) + 5
            x = x + 1
            y = y - 1
    return points

def fill1(x,y): #flood fill is used and broken into two separate functions because too many recusrions cause the program to fail
    pixel = img.load() #creates the pixel
    if pixel[x,y] == (0,255,0) or pixel[x,y] == (0,0,255): #checks for the boundry of the circle or if the pixel color has already been changed
        return
    if pixel[x,y] != (0,0,0): #another way to check if the pixel has already been changed, if its not black then go back up
        return
    
    pixel[x,y] = (0,0,255) #set the pixel color

    fill1(x-1,y) #go north
    fill1(x,y+1) #go east
    fill1(x,y-1) #go west
    return

def fill2(x,y):
    pixel = img.load()
    if pixel[x,y] == (0,255,0) or pixel[x,y] == (0,0,255):
        return
    if pixel[x,y] != (0,0,0):
        return
    
    pixel[x,y] = (0,0,255)

    fill2(x+1,y) #go south
    fill2(x,y+1) #go east
    fill2(x,y-1) #go west
    return    


r = 200
img = Image.new("RGB", (640,480), (0,0,0)) #the image is created at a larger size
draw = ImageDraw.Draw(img)
p = circle(r)
for points in p: #draws the circle in green first so that flood fill will work
    draw.point((640/2+points[0],480/2+points[1]), (0,255,0)) #image drawn larger
fill1(320,240) #fill left half
fill2(321,241) #fill right half
for points in p: #draw the circle in blue 
    draw.point((640/2+points[0],480/2+points[1]), (0,0,255))

scaled = img.resize((320,240)) #this scales the image to supersample it to give the effect of anti aliasing
scaled.show() #show the scaled image
