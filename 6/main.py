def fibonacci(n):
    fib = [0, 1]
    
    for i in range(2, n):
        siguiente = fib[i - 1] + fib[i - 2]
        fib.append(siguiente)
    
    return fib

n = 10 
resultado = fibonacci(n)
print(f"Los primeros {n} términos de la serie de Fibonacci son: {resultado}")
