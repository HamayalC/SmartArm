# SmartArm || UoftHacks 2018 Submission
# Uses Microsoft Cognitive Services API
# Author: Choudhry, Hamayal
#	  Khan, Samin
# Date: January 21, 2018			

import httplib, urllib, base64, json

###############################################
#### Update or verify the following values. ###
###############################################

# Replace the subscription_key string value with your valid subscription key.
subscription_key = '214b4ce60b1a4876b32b2d6391e2e0b8'

# Replace or verify the region.
#
# You must use the same region in your REST API call as you used to obtain your subscription keys.
# For example, if you obtained your subscription keys from the westus region, replace 
# "westcentralus" in the URI below with "westus".
#
# NOTE: Free trial subscription keys are generated in the westcentralus region, so if you are using
# a free trial subscription key, you should not need to change this region.
uri_base = 'https://eastus.api.cognitive.microsoft.com/vision/v1.0'

import speech_recognition as sr
import serial
ser = serial.Serial('/dev/ttyUSB0', 9600)
 
# Record Audio
r = sr.Recognizer()
with sr.Microphone() as source:
    print("Say something!")
    audio = r.listen(source)

try:
    # for testing purposes, we're just using the default API key
    # to use another API key, use `r.recognize_google(audio, key="GOOGLE_SPEECH_RECOGNITION_API_KEY")`
    # instead of `r.recognize_google(audio)`
    print("You said: " + r.recognize_google(audio))
    speechText = r.recognize_google(audio)
except sr.UnknownValueError:
    print("Google Speech Recognition could not understand audio")
except sr.RequestError as e:
    print("Could not request results from Google Speech Recognition service; {0}".format(e))

# Prompts camera to turn on, take picture, and save a .jpg file
import cv2

cam = cv2.VideoCapture(0)
frame = cam.read()[1]
cv2.imwrite(filename='img.jpg', img=frame)
cam.release()

headers = {
    # Request headers.
    'Content-Type': 'application/octet-stream',
    'Ocp-Apim-Subscription-Key': subscription_key,
}

params = urllib.urlencode({
    # Request parameters. All of them are optional.
    'visualFeatures': 'Categories,Description,Color',
    'language': 'en',
})

# The URL of a JPEG image to analyze.
req_body = open('img.jpg', 'rb').read()


try:
    # Execute the REST API call and get the response.
    conn = httplib.HTTPSConnection('eastus.api.cognitive.microsoft.com')
    conn.request("POST", "/vision/v1.0/analyze?%s" % params, body=req_body, headers=headers)
    response = conn.getresponse()
    data = response.read()

    # Objects that vary by graspability
    obj1 = "bottle"
    obj2 = "cup"
    obj3 = "key"

    # 'data' contains the JSON data. The following formats the JSON data for display.
    parsed = json.loads(data)
    # list of tags seen in object recognition
    tags = parsed["description"]["tags"]
    
    
    # Determines type of object and sets the type of grasp
    if obj1 in tags:
	ser.write('1')
    elif obj2 in tags:
	ser.write('2')
    elif obj3 in tags:
	ser.write('2')
    
    if "release" in speechText:
	ser.write('0')
    
    conn.close()

except Exception as e:
    print('Error: Ungraspable object has been presented')
    print(e)



