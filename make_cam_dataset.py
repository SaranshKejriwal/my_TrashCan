import cv2
import cv
cap = cv2.VideoCapture(0)
ret,img=cap.read()
height , width , layers =  img.shape     
fps=20
video = cv2.VideoWriter("rec_out.avi", cv.CV_FOURCC(*'DIVX'), fps, (img.shape[1], img.shape[0]))
while True: 
	
	ret,img=cap.read()
	height , width , layers =  img.shape
        video.write(img)
	cv2.imshow('Video', img)
	#video.write(img)
	if(cv2.waitKey(10) & 0xFF == ord('b')):
        	break
	


cv2.destroyAllWindows()
video.release()
