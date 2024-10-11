import multiprocessing

def calcular_parte(start, end):
    suma = 0.0
    for i in range(start, end):
        termino = (1.0 if i % 2 == 0 else -1.0) / (2 * i + 1)
        suma += termino
    return suma

def calcular_pi(n, num_procesos):
    chunk_size = n // num_procesos
    pool = multiprocessing.Pool(processes=num_procesos)
    resultados = [
        pool.apply_async(calcular_parte, args=(i * chunk_size, (i + 1) * chunk_size if i < num_procesos - 1 else n))
        for i in range(num_procesos)
    ]
    
    pi = sum(r.get() for r in resultados) * 4
    pool.close()
    pool.join()
    return pi

if __name__ == "__main__":
    n = 1000000 
    num_procesos = 3  
    pi = calcular_pi(n, num_procesos)
    print(f"Valor de pi calculado con {num_procesos} procesos: {pi:.15f}")
