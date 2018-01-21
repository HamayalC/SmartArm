SmartArm is our submission to UofTHacks 2018. 

SmartArm uses Microsoft Cognitive Services, namely the Computer Vision API and Text to Speech API. We designed and rapid prototyped a prosthetic hand model, and embedded a Raspberry PI modular camera on to it. There are servo motors attached to each digit of the hand, powered by an Arduino Uno. The camera feeds image frames to the Analyze.py script, in which objects in the frame are recognzied against Microsoft's pretrained model. Based on the shape of the object, the arduino issues the optimal grasp to hold the identified object.

The SmartArm is a revolutionary step in prosthetics. Because it is completley 3D pritned apart form the circuitry, it is meant to be a more cost-friendly and efficient method for amputees and those with congenital defects to gain access to fully functional prosthetics.
