Tarea Monos 
Sistemas Operativos I Semestre 
30 de junio, 2020
Javier Sandoval Zamora 
B56762

Descripcion de la tarea:
    El programa crea N threads para simular el comportamiento de unos monos que usan una cuerda para
cruzar un barranco. La cuerda tiene una capacidad maxima de MAX_MONKEYS y solo J monos pueden pasar
de un lado a otro sin darle oportunidad a los monos del otro lado para cruzar. Los monos tienen un id
y estan a la izquierda o a la derecha del barranco, 50% de los monos de cada lado. 

Compilacion:
    Usar comando:
    gcc -o main main.cc -lpthread -lrt

Ejecucion:
Opcion 1) Ejecutar en consola ./main
    para usar los valores predeterminados
    N = 10
    MAX_MONKEYS = 2
    J = 4
Opcion 2) Ingresar parametros de la siguiente manera
    ./main N MAX_MONKEYS J
Ejemplo: ./main 50 6 12
Esto crearia 50 monos, la cuerda tendria capacidad para 6 monos y J seria igual a 12. 
