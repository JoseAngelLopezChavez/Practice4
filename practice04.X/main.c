////+++++++++++++++++++++++++++++++++++++| LIBRARIES / HEADERS |+++++++++++++++
#include "device_config.h"   //Primero se indica que se usará el header file 
//"device_config" que fue importado a la carpeta del proyecto
//+++++++++++++++++++++++++++++++++++++| DIRECTIVES |++++++++++++++++++++++++++
#define _XTAL_FREQ 1000000 //Valor de frecuencia del oscilador definido en Hz
#define ONE_SECOND 1000 //Variable equivalente a un segundo definida en ms

//+++++++++++++++++++++++++++++++++++++| DATA TYPES |++++++++++++++++++++++++++
// En este apartado utilizamos la declaración enum para definir el valor 
//booleano que representa cada definición. Por ejemplo:
enum por_dir{ output, input }; //Arreglo con valores de entradas y salidas
//output = 0, input = 1
enum por_ACDC { digital, analog };//Arreglo con valores de puertos digitales y
//analogos    // digital = 0, analog = 1
enum resistor_state { set_ON, res_ON };//Arreglo para el estado de resistencia
// set_ON = 0, res_ON = 1
enum led_state { led_OFF, led_ON };//Arreglo para el estado del LED     
// led_OFF = 0, led_ON = 1
enum butto_state { pushed, no_pushed };//Arreglo para el estado del pushbutton 
// pushed = 0, no_pushed = 1

//+++++++++++++++++++++++++++++++++++++| ISRs |++++++++++++++++++++++++++++++++
// En este apartado definiremos las prioridades de las interrupciones que se 
//presenten en nuestro código:

// Definicion de rutina de servicio de interrupcion de alta prioridad 
void __interrupt ( high_priority ) high_isr( void );
// Definicion de rutina de servicio de interrupcion de baja prioridad
void __interrupt ( low_priority ) low_isr( void ); 

//+++++++++++++++++++++++++++++++++++++| FUNCTION DECLARATIONS |+++++++++++++++
void portsInit( void ); // Prototipo de la función.

//+++++++++++++++++++++++++++++++++++++| MAIN |++++++++++++++++++++++++++++++++
void main( void ){
    portsInit();
    while(1){ // Un while infinito que siempre se cumplirá.
        if(PORTBbits.RB4 == pushed)   // Si el boton es precionado, entonces...
            LATAbits.LATA7 = led_OFF;  // Apaga el LED RA4
        else                           // De lo contrario
            LATAbits.LATA7 = led_ON;   // Enciende el LED RA4
        LATAbits.LATA4 = led_ON;       // Enciende el LED RA4
        __delay_ms(ONE_SECOND);        // Funcion de retraso para el compilador
        LATAbits.LATA4 = led_OFF;      // Apaga el LED RA4
        __delay_ms(ONE_SECOND);        // Funcion de retraso para el compilador
    }
}

//+++++++++++++++++++++++++++++++++++++| FUNCTIONS |+++++++++++++++++++++++++++
void portsInit( void ){
    ANSELA = digital;              // Establece el Puerto A como puerto digital
    TRISAbits.TRISA4 = output;     // Establece RA4 como salida
    TRISAbits.TRISA7 = output;     // Establece RA7 como salida
    ANSELB = digital;              // Establece el Puerto B como puerto digital
    TRISBbits.TRISB4 = input;      // Establece RA4 como entrada

}
