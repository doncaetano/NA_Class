# Trabalho de Algoritmos Numéricos 
 
### Interpolação polinomial por partes via splines cúbicas
 
#### 1. Objetivos
 
  O objetivo deste trabalho é implementar a interpolação polinomial usando o método de splines cúbicas naturais.
 
#### 2. Interpolação polinomial e a interpolação por partes

  Dado um conjunto de (n+1) pontos no plano C=((x0, y0), (x0, y0), ... (xn, yn)) com x0 < x1 < x2 ... < xn−1 < xn, quer se obter um polinômio que passe pelos pontos (ou seja, tal que p(xi) = yi para todo i).

  Sabe-se que, dado um conjunto de (n+1) pontos no plano, é sempre possível obter um polinômio de grau n que satisfaz às (n+1) restrições de interpolação (pn(x)i = yi). No entanto, se houver uma quantide muito grande de pontos, pode surgir uma instabildade associada ao grau elevado do polinômio e, nestes casos, é preferível trabalhar com interpolaçãao polinomial por partes.

#### 3. Interpolação polinomial por partes

  Na interpolação polinomial por partes, em cada intervalo (xi, xi+1) tem-se um polinômio diferente, ou seja, resolve se um problema de interpolação localmente.

  Este polinômio pode ser de grau 1 (interpolação via retas) ou de grau maior, por exemplo, de grau 3.

  __Splines cúbicas__ É o tipo de interpolação por partes mais utilizada: polinômios de grau 3 são empregados. Os polinômios obtidos são curvas que são concatenadas formando uma função contínua e sem mudanças bruscas de inclinação e de curvatura entre as partes.


  A obtenção das splines cúbicas para um conjunto de pontos no plano pode ser vista com detalhes nas páginas de 149 a 155, do livro Algoritmos Numéricos de Frederico Campos, 2ª edição.

  Pode ser vista também nas páginas de 426 a 435 no livro de Chapara e Canale (na tradução, 5ª edição).
  
