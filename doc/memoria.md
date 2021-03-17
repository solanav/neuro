# Práctica 1
Autores: Pablo Sánchez Redondo y Antonio Solana Vera

## McCulloch-Pitts

Esta red tiene un diseño simple de tres capas, para simular el circuito lógico dado, las tres neuronas de entrada, las tres neuronas que representan las puertas AND, y la neurona de la puerta OR.

![image](mp.png)

Dado que esta red no es de autoaprendizaje, conectamos las neuronas manualmente y ejecutamos el bucle (disparar &rightarrow; inicializar &rightarrow; propagar) tantas veces como entradas tengamos, y luego otras dos veces, ya que tienen que disparar y propagar la capa a y la capa y para procesar la entrada.

Respecto al diseño hemos decidido, para simular el comportamiento de la puerta AND, poner el umbral a 2, así, sólo cuando reciba un 1 de ambas conexiones se activará. La puerta OR es similar, el umbral está a 1 para que en cuanto cualquiera de las conexiones entrantes de una salida activa, se active. Por ello, los pesos de todas las conexiones es 1.

La función f(t+2) se comporta de manera que si hay al menos dos entradas activas, la salida estará activa.

## Implementación de las redes Perceptrón y Adaline

Usando las clases para redes neuronales, creadas en el primer punto de la practica, creamos dos capas, una de entrada y una de salida. 