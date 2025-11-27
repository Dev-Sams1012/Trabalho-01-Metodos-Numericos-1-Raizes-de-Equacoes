# Oscilação de uma Corda Elástica

Uma corda elástica oscila de acordo com uma função polinomial dada por:

\[f(d) = a_3d^3 \;– \;9a_2d \;+ \;3\]

Onde:

- $a_3$ e $a_2$ são parâmetros que variam dependendo do tipo de corda;  
- $d$ é o deslocamento calculado para a corda, considerando a equação polinomial fornecida.

Caso esse deslocamento ultrapasse $0,3$ cm, a corda sofre uma extensão muito grande e poderá quebrar.

---

## Objetivo

Desenvolver um sistema para calcular o valor de $d$ de uma oscilação da corda, atendendo aos seguintes requisitos:

**a)** Implementar o algoritmo para calcular $d$ pelo **método de Newton original**.  
**b)** Implementar o algoritmo para calcular $d$ pelo **método de Newton com F_L**.  
**c)** Implementar método numérico para achar a derivada de $f(d)$ e refazer o item (a).  
**d)** Testar os resultados usando como padrão:


$a_3 = 1$
$a_2 = 1$
$d_0 = 0,5$
$λ = 0,05$
$ε = 0,001$

**e)** Fornecer um quadro de resposta, com o deslocamento calculado para cada método.  
**f)** Fornecer um quadro comparativo, contendo todos os dados de cada método.  
**g)** Analisar o efeito da variação dos valores de $a_3$ e $a_2$ para cada método.

---

## Dados de Entrada

- $n$: número de opções para $λ$  
- $λ$, $a_3$, $a_2$: para cada opção  
- $ε$: precisão

---

## Dados de Saída

- Quadros de resposta (com $d$ e erro para cada $a_3$, $a_2$, $λ$ e método)  
- Quadro comparativo (com todos os resultados)

---

## Metodologia

- **Tecnologia**: Utilizamos a linguagem **C/C++** para a realização do codigo fonte do trabalho
  
### Método  Newton

#### Formalização

O Método de Newton é um caso particular do método do ponto fixo, Logo, segue os mesmo critérios de convergência do MPF:

- Seja $ξ$ uma raiz da equação $f(x) = 0$, isolada num intervalo $I$, onde $ξ ∈ I$
- Seja $φ(x)$ uma função de iteração para a equação $f(x) = 0$. Então nesse caso se:

  \[\text{-} \;\;φ(x) \;\; \text{e} \;\; φ'(x) \;\; \text{são contínuas em }I \\
    \text{-} \;\; |φ(x)| ≤ M < 1 \;\;, ∀x ∈ I \;\;\;\;\;\;\;\;\;\;\;\;\;\, \\
    \text{-} \;\; x_0 ∈ I \;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\;\; \]


Então a sequência considerada $\{x_k\}$ gerada por:  
\[x_{k+1} = φ(x_k)\]
Converge para $ξ$, com:
\[ 
  φ(x) = x - (f(x) / f'(x))
\]

Método de Newton converge desde que $x_0$ seja escolhido suficientemente próximo da raiz $ξ$, pois para pontos suficientemente próximos de $ξ$, as hipóteses do teorema da convergência do MPF estão satisfeitas.

#### Algoritmo Newton

```cpp
  double executaMetodo() override
    {
        double fx = p.f(d);
        if (abs(fx) < eps)
            return d;
        int k = 1;
        while (k < itermax)
        {
            if (abs(p.df(d)) < 1e-6)
            {
                cout << "Derivada proxima de 0, Metodo falhou!!\n";
                return d;
            }
            double dk = d - (fx / p.df(d));
            fx = p.f(dk);
            if (criterioParada(dk, d))
                return dk;
            d = dk;
            k++;
        }
        cout << "Limite maximo de Iteraçoes ultrapassado!!\n";
        return d;
    }
```
---
### Método  Newton com derivada numérica

De forma alternativa ao cálculo da derivada por meio da aplicação direta  em $f’(x)$, iremos utilizar uma estratégia iterativa para cálculo de derivada de polinômios.

#### Formalização

Você pode utilizar o seguinte método iterativo (método de Horner) para calcular um polinômio.

Dado:
\[
P(x) = a_n x^n + a_{n-1}x^{n-1} + \cdots + a_1x + a_0
\]

O método de horner aninha o polinômio para:

\[
P(x) = (...((a_n x + a_{n-1})x + a_{n-2})x + \cdots + a_0)
\]

De modo que o polinômio é calculado de maneira iterativa, dado:
\[ B_n = a_n\]

Calcula-se:
\[ B_i =  B_{i + 1}x + a_i \]

\[∀i ∈ \{0, 1, \cdots, n-1\} \]

Segue o exemplo com um polinômio de grau 3:
\[P(x) = a_3x^3 + a_2x^2 + a_1x + a_0\]
Logo:
\[B_3 = a_3 \\
  B_2 = B_3x + a_2 \\
  B_1 = B_2x + a_1 \\
  B_0 = B_1x + a_0  \\
  B_0 = P(x)\]

Para o cálculo de $f’(x)$, temos na definição de derivada os mesmos coeficientes de $f(x)$ (dado f igual a um polinômio P):

\[
P'(x) = a_33x^2 + a_22x  + a_1
\]
Logo, podemos obter os coeficientes por meio do método de horner:

\[a_3 = B_3 \\
  a_2 = B_2 - B_3x\\
  a_1 = B_1 - B_2x \\
  a_0 = B_0 - B_1x \]

Se substituirmos em $P'(x)$, podemos obter o cálculo da derivada por um método iterativo:

\[
P'(x) = B_3x^2 + B_2x  + B_1
\]
\[
  C_3 = B_3 \\
  C_2 = C_3x + B_2 \\
  C_1 = C_2 + B_1 \\
  C_1 = P'(x)
\]

Logo, a generalizaçao para calcular a derivada, dado:
\[
P(x) = a_n x^n + a_{n-1}x^{n-1} + \cdots + a_1x + a_0
\]

\[
P'(x) = a_nnx^{n-1} + a_{n-1}(n-1)x^{n-2} + \cdots + a_2x + a_1
\]

O cálculo dos coeficientes fica:

\[ C_n = B_n\]

\[ C_i =  C_{i + 1}x + B_i \]

\[∀i ∈ \{1, \cdots, n-1\} \]

\[ C_1 = P'(x)\]

#### Algoritmo derivada numérica

```cpp
double df_num(double d) const{
        double b = coeficientes[3];
        double c = b;
        for(long unsigned int i = 2; i > 0; i--){
            b = b*d + coeficientes[i]; 
            c = c*d + b;
        }
        return c;
    }

```

#### Algoritmo Newton com derivada numérica

```cpp
    double executaMetodo() override
    {
        double fx = p.f(d);
        if (abs(fx) < eps)
            return d;
        int k = 1;
        while (k < itermax)
        {
            if (abs(p.df_num(d)) < 1e-6)
            {
                cout << "Derivada proxima de 0, Metodo falhou!!\n";
                return d;
            }
            double dk = d - (fx / p.df_num(d));
            fx = p.f(dk);
            if (criterioParada(dk, d))
                return dk;
            d = dk;
            k++;
        }
        cout << "Limite maximo de Iteraçoes ultrapassado!!\n";
        return d;
    }
```

---

## Método de Newton com FL

No método de Newton, podem ocorrer problemas se, para uma aproximação $x_k$, tivermos:

\[f'(xₖ) = 0\]

Logo, existe uma modificação no método original para evitar isso.

#### Formalização

Dado $λ$ (número positivo próximo de zero) e supondo que $|f'(x₀)| ≥ λ$,  
a sequência $\{xₖ\}$ é gerada por:

\[ 
x_{k+1} = x_k - ( f(x_k) / FL )
\]


Onde:


\[FL = f'(x_k), \;\; \text{se   } |f'(xₖ)| > λ \]

\[FL = f'(x_w), \;\; \text{caso contrário}\]


Na qual $x_w$ é a última aproximação obtida tal que $|f'(x_w)| ≥ λ$.

#### Algoritmo Newton com FL

```cpp
 double executaMetodo() override
    {
        double fx = p.f(d);
        if (abs(fx) < eps)
            return d;
        int k = 1;
        double FL = p.df(d);
        while (k < itermax)
        {
            double dk = d - (fx / FL);
            fx = p.f(dk);
            if (criterioParada(dk, d))
                return dk;
            d = dk;
            if (abs(p.df(d)) >= lbd)
                FL = p.df(d);
            k++;
        }
        cout << "Limite maximo de Iteraçoes ultrapassado!!\n";
        return d;
    }
```
---

### Critérios de parada

Dado um $ε$(epsilon) definido na entrada, os critérios de parada para todos os métodos serão:

\[ |x_k - x_{k-1}| < ε \;\; \text{ou} \;\; |f(x_k)|<ε \]

Onde $x_k$ é o $x$ calculado no passo $k$.

#### Algoritmo Critérios de parada

```cpp
  virtual bool criterioParada(double atual, double anterior) const
    {
        return abs(atual - anterior) < eps or abs(p.f(atual)) < eps;
    }
```

---

## Como Rodar?



















