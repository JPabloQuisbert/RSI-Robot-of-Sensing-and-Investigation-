import cv2
import numpy as np

cap = cv2.VideoCapture(1)
cv2.namedWindow('image')
def nothing(x):
    pass
# create trackbars for color change
cv2.createTrackbar('R','image',0,255,nothing)
cv2.createTrackbar('G','image',0,255,nothing)
cv2.createTrackbar('B','image',0,255,nothing)

cv2.createTrackbar('R2','image',0,255,nothing)
cv2.createTrackbar('G2','image',0,255,nothing)
cv2.createTrackbar('B2','image',0,255,nothing)
    
while(1):

    # Take each frame
    _, frame = cap.read()

    # Convert BGR to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    r = cv2.getTrackbarPos('R','image')
    g = cv2.getTrackbarPos('G','image')
    b = cv2.getTrackbarPos('B','image')

    r2 = cv2.getTrackbarPos('R2','image')
    g2 = cv2.getTrackbarPos('G2','image')
    b2 = cv2.getTrackbarPos('B2','image')
    
    # define range of blue color in HSV
    lower_blue = np.array([r,g,b])
    upper_blue = np.array([r2,g2,b2])

    # Threshold the HSV image to get only blue colors
    mask = cv2.inRange(hsv, lower_blue, upper_blue)
    cv2.adaptiveThreshold(mask,255,cv2.ADAPTIVE_THRESH_MEAN_C,cv2.THRESH_BINARY,11,2)
    # Bitwise-AND mask and original image
    res = cv2.bitwise_and(frame,frame, mask= mask)

    cv2.imshow('frame',frame)
    cv2.imshow('mask',mask)
    cv2.imshow('res',res)
    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

    
cap.release()
cv2.destroyAllWindows()
