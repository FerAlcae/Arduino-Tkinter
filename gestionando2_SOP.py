from tkinter import ttk
from tkinter import *
import serial
import threading

arduino = serial.Serial("/dev/ttyUSB0")

raiz = Tk()
raiz.title("Gestionando dispositivo 2")

raiz.geometry("230x210")
raiz.resizable(False, False)

value_pot1 = StringVar()
value_pot2 = StringVar()
value_btn1 = StringVar()
value_btn2 = StringVar()
value_led1 = IntVar()
value_led2 = IntVar()

#Funciones asociadas a los elementos en la ventana.
def val_elementos():
    while True:
        cad = arduino.readline().decode('ascii').strip()
        print(cad)
        val_pot1, val_pot2, val_btn1, val_btn2 = cad.split(",")
        value_pot1.set(val_pot1)
        value_pot2.set(val_pot2)
        value_btn1.set(val_btn1)
        value_btn2.set(val_btn2)

def fEnviaLed1():
    cad='led1:' + str(value_led1.get())
    arduino.write(cad.encode('ascii'))
    print(cad)

def fEnviaLed2():
    cad='led2:' + str(value_led2.get())
    arduino.write(cad.encode('ascii'))
    print(cad)

#Elementos que se utilizaran en la ventana.
#Para señales analogicas, 2 potenciometros.
Label(raiz,text="Potenciometro 1: ").place(x=30,y=20)
Label(raiz,width=6,textvariable=value_pot1).place(x=150,y=20)

Label(raiz,text="Potenciometro 2: ").place(x=30,y=50)
Label(raiz,width=6,textvariable=value_pot2).place(x=150,y=50)


#Para pulsadores, 2 pulsadores.
Label(raiz,text="Pulsador 1: ").place(x=30,y=80)
Label(raiz,width=6,textvariable=value_btn1).place(x=120,y=80)

Label(raiz,text="Pulsador 2: ").place(x=30,y=110)
Label(raiz,width=6,textvariable=value_btn2).place(x=120,y=110)

#Para LEDs.
Checkbutton(raiz, text="Encender/Apagar Led 1", variable=value_led1,
onvalue=1, offvalue=0,command=fEnviaLed1).place(x=30, y=140)

Checkbutton(raiz, text="Encender/Apagar Led 2", variable=value_led2,
onvalue=1, offvalue=0,command=fEnviaLed2).place(x=30, y=170)

#Utilizo un hilo para que el programa no se cicle y que se pueda
#estar leyendo el valor de los potenciometros/pulsadores siempre.
hilo=threading.Thread(target=val_elementos, daemon=True)
hilo.start()
hilo.join(0.1)
raiz.mainloop()
