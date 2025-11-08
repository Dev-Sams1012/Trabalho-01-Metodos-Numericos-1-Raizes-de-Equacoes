# Oscilação de uma Corda Elástica

Uma corda elástica oscila de acordo com uma função polinomial dada por:

**f(d) = a₃·d³ – 9·a₂·d + 3**

onde:

- **a₃** e **a₂** são parâmetros que variam dependendo do tipo de corda;  
- **d** é o deslocamento calculado para a corda, considerando a equação polinomial fornecida.

Caso esse deslocamento ultrapasse **0,3 cm**, a corda sofre uma extensão muito grande e **poderá quebrar**.

---

## Método de Newton e Modificação

No método de Newton, podem ocorrer problemas se, para uma aproximação **xₖ**, tivermos:

**f'(xₖ) = 0**

Uma modificação no método original para evitar isso consiste em:

Dado **λ** (número positivo próximo de zero) e supondo que **|f'(x₀)| ≥ λ**,  
a sequência **{xₖ}** é gerada por:

```text
xₖ₊₁ = xₖ - ( f(xₖ) / FL )
```

onde:

```text
FL = f'(xₖ), se |f'(xₖ)| > λ
FL = f'(x_w), caso contrário
```

e

```
x_w é a última aproximação obtida tal que |f'(x_w)| ≥ λ.
```

---

## Objetivo

Desenvolver um sistema para calcular o valor de **d** de uma oscilação da corda, atendendo aos seguintes requisitos:

**a)** Implementar o algoritmo para calcular **d** pelo **método de Newton original**.  
**b)** Implementar o algoritmo para calcular **d** pelo **método de Newton com F_L**.  
**c)** Implementar método numérico para achar a derivada de **f(d)** e refazer o item (a).  
**d)** Testar os resultados usando como padrão:

```text
a₃ = 1
a₂ = 1
d₀ = 0,5
λ = 0,05
ε = 0,001
```

**e)** Fornecer um quadro de resposta, com o deslocamento calculado para cada método.  
**f)** Fornecer um quadro comparativo, contendo todos os dados de cada método.  
**g)** Analisar o efeito da variação dos valores de **a₃** e **a₂** para cada método.

---

## Dados de Entrada

- **n**: número de opções para λ  
- **λ**, **a₃**, **a₂**: para cada opção  
- **ε**: precisão

---

## Dados de Saída

- **Quadros de resposta** (com **d** e erro para cada **a₃**, **a₂**, **λ** e método)  
- **Quadro comparativo** (com todos os resultados)
