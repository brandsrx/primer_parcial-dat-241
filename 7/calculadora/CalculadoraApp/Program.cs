using System;
using CalculadoraLib;

// See https://aka.ms/new-console-template for more information
 Calculadora calc = new Calculadora();

Console.WriteLine("Ingrese la expresión:");
string expresion = Console.ReadLine();

Console.WriteLine("Ingrese el tipo de expresión (infija/prefija):");
string tipo = Console.ReadLine();

try
{
    double resultado = calc.Evaluar(expresion, tipo);
    Console.WriteLine($"Resultado: {resultado}");
}
catch (Exception ex)
{
    Console.WriteLine($"Error: {ex.Message}");
}

Console.ReadLine();

