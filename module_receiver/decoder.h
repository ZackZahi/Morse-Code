#ifndef DECODER_H
#define DECODER_H
#define Low 0
#define High 1
#define Period 10 // en ms

// Tableau de test

static char [][20] ={"=.===","a","===.=.=.=","b","===.=.===.=","c","===.=.=","d","=","e",
         "=.=.===.=","f", "===.===.=","g","=.=.=.=","h","=.=","i","=.===.===.===","j",
         "===.=.===","k", "=.===.=.=","l","===.===","m","===.=","n","===.===.===","o","=.===.===.=","p",
         "===.===.=.===","q","=.===.=","r","=.=.=","s","===","t","=.=.===","u","=.=.=.===","v","=.===.===","w",
         "===.=.=.===","x","===.=.===.===","y","===.===.=.=","z","=.===.===.===.===","1","=.=.===.===.===","2","=.=.=.===.===","3",
         "=.=.=.=.===","4","=.=.=.=.=","5","===.=.=.=.=","6","===.===.=.=.=","7","===.===.===.=.=","8","===.===.===.===.=","9","===.===.===.===.===","0","...","","......."," "};




// get an array of strings example ["." , "= ", "... ", "=== ", ".......""]
void GetSymbolCode(char*arg_morse, int *signal);
// {{High,10},{Low,10} } ==> ["=","."] this methods uses the  GetSymbolCode method 
void FromBinary_TabToMorse_Tab(char (*arg_Morse_Tab)[8],int (*arg_signal_Tab)[2],unsigned int arg_taille);
//from morse code detected in the Ref_Tab it returns the appropriate caracter  , example :"=.===" --> "a"
char* TransformCodeToChar (char * arg_morse_code);
// take a morse tab ["=",".","===",.......] ==> return the decoded message
void decode(char (*arg_morse_tab)[8], unsigned int arg_taille);

#endif // DECODER_H
