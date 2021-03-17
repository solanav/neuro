# Práctica 1
Autores: Pablo Sánchez Redondo y Antonio Solana Vera

## McCulloch-Pitts

Esta red tiene un diseño simple de tres capas, para simular el circuito lógico dado, las tres neuronas de entrada, las tres neuronas que representan las puertas AND, y la neurona de la puerta OR.

![image](mp.png)

Dado que esta red no es de autoaprendizaje, conectamos las neuronas manualmente y ejecutamos el bucle (disparar &rightarrow; inicializar &rightarrow; propagar) tantas veces como entradas tengamos, y luego otras dos veces, ya que tienen que disparar y propagar la capa a y la capa y para procesar la entrada.

