import Tkinter as tk
import cv2
from PIL import Image, ImageTk
import numpy as np
width, height = 800, 600
cap = cv2.VideoCapture(0)
global sel
sel=1

def cal():
    print "cal"
    global sel
    sel=1

def vs():
    print "vs"
    global sel
    sel=2


def show_frame():

    _, frame = cap.read()

    frame = cv2.flip(frame, 1)
    frame1 = np.array(frame)
###################
    if sel==1:

        res = cv2.cvtColor(frame, cv2.COLOR_BGR2RGBA)
###################

    elif sel==2:

        print "asdadasd"
        cv2image = cv2.cvtColor(frame1, cv2.COLOR_BGR2HSV)
        lower=np.array([w1.get(),w2.get(),w3.get()])
        upper=np.array([w4.get(),w5.get(),w6.get()])
        mask = cv2.inRange(cv2image, lower, upper)

        kernel = np.ones((6,6),np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
        edges = cv2.Canny(mask,1,2)
        res = cv2.bitwise_and(frame,frame, mask= mask)
        #maskf=cv2.add(edges,mask)
        contours, hier = cv2.findContours(edges,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)




    img = Image.fromarray(res)
    #img = Image.fromarray(mask)
    imgtk = ImageTk.PhotoImage(image=img)
    lmain.imgtk = imgtk
    lmain.configure(image=imgtk)
    lmain.after(10, show_frame)



root = tk.Tk()
#root2 = tk.Tk()
lmain = tk.Label(root)
lmain.pack()




w1 = tk.Scale(root, from_=0, to=255, orient="horizontal")
w1.set(10)
w1.pack(side="left")

w2 = tk.Scale(root, from_=0, to=255,orient="horizontal")
w2.set(10)
w2.pack(side="left")

w3= tk.Scale(root, from_=0, to=255,orient="horizontal")
w3.set(10)
w3.pack(side="left")


w4 = tk.Scale(root, from_=0, to=255, orient="horizontal")
w4.set(200)
w4.pack(side="left")

w5 = tk.Scale(root, from_=0, to=255,orient="horizontal")
w5.set(200)
w5.pack(side="left")

w6= tk.Scale(root, from_=0, to=255,orient="horizontal")
w6.set(200)
w6.pack(side="left")

b1 = tk.Button( root, text = "Calibrar",command=cal)
b1.pack()

b2 = tk.Button( root, text = "Video Streaming",command=vs)
b2.pack()


#imshow=("sd",mask)

show_frame()


root.mainloop()
