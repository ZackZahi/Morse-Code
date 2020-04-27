
//==========================================================================================//
//******************************************************************************************//
// Nom : 
// Fichier : interruption.c
// Réaliser par : Nawfal BOUGHTI & Zakaria ZAHI
// Sous la direction de : Nicolas DOSME & Patrick Le Jeannic
// Date : 06-02-2020
// Version : 1.0
// Formation : M2 E3A SETI
//******************************************************************************************//
//==========================================================================================//

#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/string.h>
#include "decoder.h"
 /**********
  ************** VARAIBLE DECLARATION  **********************
  ***********/
#define IRQ_TEST_GPIO_IN 23
#define Binary_Tab_length 100
#define Morse_Tab_length 100
static unsigned int GPIO = 23;
static uint16_t r=0 , i =0;
static unsigned int last_interrupt_time = 0;
static uint64_t epochMilli;
static int Binary_Tab[Binary_Tab_length][2];
static struct timer_list my_timer;
static uint16_t time_from_last_interruption = 0;
static char Morse_Tab[Morse_Tab_length][8];

/************************************************* CALCULATE DELAY BETWEEN 2 INTERRUPTIONS **************************************/
unsigned int millis (void)
{ struct timeval tv ;
  uint64_t now ;
  do_gettimeofday(&tv) ;
  now  = (uint64_t)tv.tv_sec * (uint64_t)1000 + (uint64_t)(tv.tv_usec / 1000) ;
  return (uint32_t)(now - epochMilli) ;
}


/***************************************************** DETECT THE END OF THE SIGNAL *********************************************/
void my_timer_callback(struct timer_list *timer) {
unsigned int TabLength;
mod_timer(&my_timer, jiffies + msecs_to_jiffies(30));
time_from_last_interruption =  time_from_last_interruption + 30 ;
if (( time_from_last_interruption >=1000 ) && (i!=0))
 {    
    /**********
	************** DECODE THE MESSAGE AFTER SIGNAL RECEPTION : CALLING THE DECODER METHODS , SEE DECODER.H *********************
	***********/
	TabLength = sizeof(Binary_Tab) / (2*sizeof(int))-1;
        printk(KERN_NOTICE "Calculate length: OK ! \n");
	FromBinary_TabToMorse_Tab(Morse_Tab,Binary_Tab,TabLength);
        printk(KERN_NOTICE "From binary to morse: OK ! \n");
	decode(Morse_Tab,50);
        printk(KERN_NOTICE "Decode: OK ! \n");
	i=0;
}
//Re-initialisation des tableaux
for ( r=0;r<TabLength ; r++)
    {
    	Binary_Tab[i][0]=0;
	    Binary_Tab[i][1]=0;
    }

   for ( r = 0;r<Morse_Tab_length ; r++)
     {
       strcpy(Morse_Tab[r],"");
     }
}


/********************************************** SIGNAL TABLE(Binary_Tab) ACQUIRING WITH IRQ************************************************/
static irqreturn_t irq_test_handler(int irq, void * ident) {
unsigned long flags;
unsigned int interrupt_time = millis();
time_from_last_interruption = 0;
if (interrupt_time - last_interrupt_time < 8) {
	printk(KERN_NOTICE "Ignored Interrupt!!");
	return IRQ_HANDLED;
}
local_irq_save(flags);
printk(KERN_NOTICE "Interrupt [%d] was triggered !.\n", irq);
if ( i>0) {
	Binary_Tab[i-1][1] = interrupt_time - last_interrupt_time  ;
	Binary_Tab[i-1][1] = Binary_Tab[i-1][1] - Binary_Tab[i-1][1]%10 ;// if 1001 ms ==> take only the 1000 ms 
	if (gpio_get_value(GPIO)==1)
		Binary_Tab[i-1][0]= 0;
	else
		Binary_Tab[i-1][0] =  1;
	pr_info(" Tab[%d]=(%d , %d)\n", i-1, Binary_Tab[i-1][0], Binary_Tab[i-1][1]);
	}
i++ ;
last_interrupt_time= interrupt_time;
local_irq_restore(flags);
return IRQ_HANDLED;
}

/*************************************************** CONFIGURE INPUT INTERRUPTION ON GPIO**************************************/
static int __init irq_test_init (void) {
int err;
printk ( KERN_INFO "CHARGING MODULexport.koE");
// Allocate GPIO before use
if ((err = gpio_request(IRQ_TEST_GPIO_IN,THIS_MODULE->name)) != 0) {
        return err;}
// Definir le port (IRQ_TEST_GPIO_IN) en INPUT
if ((err = gpio_direction_input(IRQ_TEST_GPIO_IN)) != 0) {
        printk(KERN_ERR "%s: unable to set GPIO as input\n", THIS_MODULE->name);
        gpio_free(IRQ_TEST_GPIO_IN);
        return err;}
//Set up the handling of the interrupt
if ((err = request_irq(gpio_to_irq(IRQ_TEST_GPIO_IN), irq_test_handler, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING ,THIS_MODULE->name, THIS_MODULE->name)) !=0) {
        gpio_free(IRQ_TEST_GPIO_IN);
        return err;
}
/* setup your timer to call my_timer_callback */
//setup_timer(&my_timer, my_timer_callback, 0);
timer_setup(&my_timer, my_timer_callback, 0);
/* setup timer interval to 30 msecs */
mod_timer(&my_timer, jiffies + msecs_to_jiffies(30));
return 0;
}

/******************************************************* CLEAR INTERRUPTION ***************************************************/
static void __exit irq_test_exit (void)
{ls
free_irq(gpio_to_irq(IRQ_TEST_GPIO_IN), THIS_MODULE->name);
gpio_free(IRQ_TEST_GPIO_IN);
printk ( KERN_INFO "OUT OF MODULE");
/* remove kernel timer when unloading module */
del_timer(&my_timer);
}


/****************************************************** LOAD AND EXIT THE MODULE **********************************************/
module_init(irq_test_init);
module_exit(irq_test_exit);

/********************************************************* MODULE DESCRIPTION *************************************************/
MODULE_DESCRIPTION("Interrupt handler");
MODULE_AUTHOR("BoughtiZahi");
MODULE_LICENSE("GPL");

