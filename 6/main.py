def fibonacci(n):
    # Inicializamos el vector con los dos primeros términos de Fibonacci
    fib = [0, 1]
    
    # Calculamos los términos de Fibonacci hasta n
    for i in range(2, n):
        # Agregamos el siguiente término usando solo los valores iniciales de la lista
        siguiente = fib[i - 1] + fib[i - 2]
        fib.append(siguiente)
    
    return fib

# Ejemplo de uso
n = 10  # Número de términos deseados
resultado = fibonacci(n)
print(f"Los primeros {n} términos de la serie de Fibonacci son: {resultado}")
