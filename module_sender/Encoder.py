import MorseProperties as MorseProperties
import time


class Encoder():
    def __init__(self):
        pass

    def Encode(self,arg_chaine):
       loc_Morse_Tab= self.FromStringToMorse_Tab(arg_chaine)
       print(loc_Morse_Tab)
       loc_Binary_Tab=self.FromMorse_TabToBinary_Tab(loc_Morse_Tab)
       return loc_Binary_Tab

    def FromMorse_TabToBinary_Tab(self,arg_morse_tab):
        loc_binary_tab = []
        for single_code in arg_morse_tab :
            if single_code == "=":
                loc_binary_tab.append(["High",MorseProperties.duration])
            elif single_code == "===":
                loc_binary_tab.append(["High",(MorseProperties.duration)*3])
            if single_code == ".":
                loc_binary_tab.append(["Low",MorseProperties.duration])
            if single_code == "...":
                loc_binary_tab.append(["Low",(MorseProperties.duration)*3])
            if single_code == ".......":
                loc_binary_tab.append(["Low",(MorseProperties.duration)*7])

        return loc_binary_tab


    def FromStringToMorse_Tab(self,arg_chaine):
        loc_string=""
        index =-1  # start from -1 to test  arg_chaine[index+1] else an out of range problem occurs
        for char_iterator in arg_chaine:
            index = index+1
            if((index == arg_chaine.__len__()-1) or (arg_chaine[index+1] ==" ") or(arg_chaine[index]==" ")):
                loc_string = loc_string + self.TransformToMorseCode(char_iterator)
            else:
                loc_string = loc_string + self.TransformToMorseCode(char_iterator)+"..."
        #print(loc_string)
        loc_morse_Tab = self.ConvertToTab(loc_string)
        return loc_morse_Tab

    def ConvertToTab(self,arg_morseString):
        loc_morse_tab=[]
        ch=arg_morseString[0]
        for index in range(0,len(arg_morseString)-1): # to iterate through the entire string ( if we don't put the -1 ==> overindexing)
            #print(arg_morseString[index])
             if(arg_morseString[index+1]==arg_morseString[index]):
                 ch=ch+arg_morseString[index+1]
                 if(index == (len(arg_morseString)-2)):# because we treat the element index+1 we have to stop at the caracter before the last one
                     loc_morse_tab.append(ch)
             else:
                 loc_morse_tab.append(ch)
                 ch= arg_morseString[index+1]
                 if (index == (len(arg_morseString) - 2)):
                     loc_morse_tab.append(ch)
        return loc_morse_tab


    def TransformToMorseCode(self,arg_char):
        for key in MorseProperties.Ref_Tab.keys():
            if (arg_char == MorseProperties.Ref_Tab[key]):
                return key




#
# e = Encoder()
# print(e.ConvertToTab("=.===...="))
