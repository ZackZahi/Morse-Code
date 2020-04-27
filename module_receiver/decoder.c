#include "decoder.h"
//#include <stdio.h>
//#include <linux/stdlib.h>
#include <linux/string.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");

void decode(char (*arg_morse_tab)[8], unsigned int arg_taille )
{

   char  loc_code [100]= "";
   char  loc_string [100]= "";
   unsigned int index = 0;
   unsigned int i ;

   for ( i = 0; i < arg_taille ; i++)
   {
       index++;
       if (index == arg_taille)
       {
	   printk( KERN_NOTICE " index == arg_taille" );
           strcat(loc_code,arg_morse_tab[i]);
           strcat(loc_string,TransformCodeToChar(loc_code));
       }
       else if (strcmp(arg_morse_tab[i],"...")==0)
       {   
           strcat(loc_string,TransformCodeToChar(loc_code));
           strcpy(loc_code,"");

       }
              else if (strcmp(arg_morse_tab[i],".......")==0)
       {
            strcat(loc_string,TransformCodeToChar(loc_code));
            strcat(loc_string," ");
            strcpy(loc_code,"");
       }
       else
       {   strcat(loc_code,arg_morse_tab[i]);
       }
   }

     printk (KERN_NOTICE "DECODAGE : La chaine de caractères obtenue est =  %s\n" , loc_string);
    //puts(loc_string);
   
}



char* TransformCodeToChar (char *arg_morse_code)
{
   unsigned char indice_char = 0;
   while(strcmp(Ref_Tab[indice_char],arg_morse_code))
   {
       indice_char++;
   }
   return Ref_Tab[indice_char+1];

}


void FromBinary_TabToMorse_Tab(char (*arg_Morse_Tab)[8],int (*arg_signal_Tab)[2], unsigned int arg_taille)
{

   unsigned int j ;
     for ( j = 0 ; j<arg_taille ;j++)
     {
             GetSymbolCode(arg_Morse_Tab[j],arg_signal_Tab[j]);

     }
}


// this works for example get  = or ...
void GetSymbolCode(char*arg_morse,int *signal)
{
    //char loc_morse [] ="";
    if(signal[0] == High)
    {
        if(signal[1] == Period )
        {
            strcpy(arg_morse,"=");
        }
        else if(signal[1] == 3*Period)
        {
            strcpy(arg_morse,"===");
        }
    }
    else if (signal[0] == Low)
    {
        if(signal[1] == Period )
        {
            strcpy(arg_morse,".");
        }
         if(signal[1] == 3*Period )
        {
            strcpy(arg_morse,"...");
        }
         if(signal[1] == 7*Period )
        {
            strcpy(arg_morse,".......");
        }
    }

}
