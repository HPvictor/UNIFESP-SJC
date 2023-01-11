    #include <stdio.h>
    #include <math.h>

    //Função adiciona livro usando os vales atuais(agrVales),custo      de troca(valeCusto) e os vales restantes(extras)
    int AdicionaLivro ( int agrVales, int valeCusto, int extras ) {
      int adBonus = agrVales/valeCusto;     
      int valorExtra = (agrVales % valeCusto) + adBonus;
      extras += adBonus;     
      if (valorExtra < valeCusto)
        return extras;
      return AdicionaLivro( valorExtra, valeCusto, extras ) ;
    }
     
    int main(void) {
      int n = 1, dinheiro, preco, troca;
      //pede o numero de entradas a serem testadas
      scanf("%i", &n);
      int i, comprados, vales;
      for (i = 0; i < n; i++) {
        //printf("Insira o dinheiro, preço e vales:(d p v) ");
        scanf("%i %i %i", &dinheiro, &preco, &troca);
        //inclui biblioteca math para usar floor(arrdonda pra baixo)
        comprados = floor(dinheiro/preco);
        //chama função adiciona livro
        vales = AdicionaLivro( comprados, troca, 0);
        comprados += vales;
        //agora imprime o valor do total de comprados, tanto com o          dinheiro como com os vales
        printf("%i\n", comprados);
      }
      return 0;
    }