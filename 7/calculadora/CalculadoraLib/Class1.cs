using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalculadoraLib
{
    public class Calculadora
    {
        public double Evaluar(string expresion, string tipo)
        {
            if (tipo.ToLower() == "infija")
            {
                return EvaluarInfija(expresion);
            }
            else if (tipo.ToLower() == "prefija")
            {
                return EvaluarPrefija(expresion);
            }
            else
            {
                throw new ArgumentException("Tipo de expresión no válido. Debe ser 'infija' o 'prefija'.");
            }
        }

        private double EvaluarInfija(string expresion)
        {
            // Implementar evaluación de expresión infija
            // Usamos DataTable para simplificar
            var table = new System.Data.DataTable();
            return Convert.ToDouble(table.Compute(expresion, string.Empty));
        }

        private double EvaluarPrefija(string expresion)
        {
            // Evaluar una expresión prefija utilizando una pila
            string[] tokens = expresion.Split(' ');
            Array.Reverse(tokens);
            Stack<double> stack = new Stack<double>();

            foreach (var token in tokens)
            {
                if (double.TryParse(token, out double num))
                {
                    stack.Push(num);
                }
                else
                {
                    double operando1 = stack.Pop();
                    double operando2 = stack.Pop();
                    stack.Push(EjecutarOperacion(token, operando1, operando2));
                }
            }

            return stack.Pop();
        }

        private double EjecutarOperacion(string operacion, double operando1, double operando2)
        {
            switch (operacion)
            {
                case "+":
                    return operando1 + operando2;
                case "-":
                    return operando1 - operando2;
                case "*":
                    return operando1 * operando2;
                case "/":
                    return operando1 / operando2;
                default:
                    throw new ArgumentException("Operación no válida");
            }
        }
    }
}
