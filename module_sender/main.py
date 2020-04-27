import MorseProperties as mp
from Sender import *

TheSender = Sender()
message_to_encode  = "nawf al"

# take the string message and code it to a binary tab
tab =(TheSender.Send(message_to_encode))
print (tab)

