import cv2
import cv
import numpy as np
import freenect

def nothing(x):
    pass

cv2.namedWindow('Video')
cv2.moveWindow('Video',5,5)

kernel = np.ones((5, 5), np.uint8)
print('Press \'b\' in window to stop')

count=0
#cv2.createTrackbar('dilate', 'edge',0,10,nothing)
def pretty_depth(depth):
    np.clip(depth, 0, 2**10 - 1, depth)
    depth >>= 2
    depth = depth.astype(np.uint8)
    return depth


fps=20
video_rgb = cv2.VideoWriter("rec_rgb.avi", cv.CV_FOURCC(*'DIVX'), fps, (640, 480))
video_disp = cv2.VideoWriter("rec_disp.avi", cv.CV_FOURCC(*'DIVX'), fps, (640, 480))
#img gives 640X480 image
while True: 
	

	count=count+1
#get kinect input__________________________________________________________________________
	dst = pretty_depth(freenect.sync_get_depth()[0])#input from kinect
    	orig = freenect.sync_get_video()[0]
    	orig = cv2.cvtColor(orig,cv2.COLOR_BGR2RGB) #to get RGB image, which we don't want
	cv2.flip(orig, 0, orig)#since we keep kinect upside-down
    	cv2.flip(orig, 1,orig)# thus correcting upside-down mirror effect
    	cv2.flip(dst, 0, dst)#since we keep kinect upside-down
	cv2.flip(dst, 1,dst)# thus correcting upside-down mirror effect
    
	#Thresh part if necessary 	
    	dst = (dst/20)*20
    	cv2.threshold(dst,230,255,cv2.THRESH_BINARY_INV,dst)


	dst=cv2.cvtColor(dst,cv2.COLOR_GRAY2BGR)#convert to 3 channel for imwrite

	video_disp.write(dst)
        video_rgb.write(orig)
	
	cv2.imshow('Input',orig)
	cv2.imshow('Video', dst)
	
	if(cv2.waitKey(10) & 0xFF == ord('b')):
        	break
	


cv2.destroyAllWindows()
video.release()
