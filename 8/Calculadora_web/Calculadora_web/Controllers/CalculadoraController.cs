using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;

namespace Calculadora_web.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class CalculadoraController : ControllerBase
    {
        [HttpGet("evaluar")]
        public IActionResult Evaluar([FromQuery] string expresion, [FromQuery] string tipo)
        {
            try
            {
                double resultado = tipo.ToLower() == "infija" ? EvaluarInfija(expresion) : EvaluarPrefija(expresion);
                return Ok(new { Resultado = resultado });
            }
            catch (Exception ex)
            {
                return BadRequest(new { Error = ex.Message });
            }
        }

        private double EvaluarInfija(string expresion)
        {
            var table = new System.Data.DataTable();
            return Convert.ToDouble(table.Compute(expresion, string.Empty));
        }

        private double EvaluarPrefija(string expresion)
        {
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
            return operacion switch
            {
                "+" => operando1 + operando2,
                "-" => operando1 - operando2,
                "*" => operando1 * operando2,
                "/" => operando1 / operando2,
                _ => throw new ArgumentException("Operación no válida")
            };
        }
    }
}
