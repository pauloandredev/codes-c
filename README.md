## TÍTULO DO PROJETO

ROUBA MONTE - JOGO DE CARTAS EM C

## DESCRIÇÃO

Este projeto implementa o jogo de cartas "Rouba Monte" em linguagem C. O jogo é baseado em pilhas e envolve estratégia e sorte. O código está estruturado de forma modular, facilitando a leitura e a manutenção. 

## COMO JOGAR

### PRÉ-REQUISITOS

- Compilador C (ex: Devc++)
- Sistema operacional compatível com os comandos `system("cls")` e `system("clear")`

### EXECUÇÃO

1. Compile o código-fonte utilizando um compilador C.
    ```bash
    gcc main.c -o rouba_monte
    ```

2. Execute o programa resultante.
    ```bash
    ./rouba_monte
    ```

3. Siga as instruções exibidas no console para interagir com o jogo.

## FUNCIONALIDADES

- **MENU INTERATIVO:** O programa apresenta um menu de opções interativas para o usuário.
- **JOGO ROUBA MONTE:** Implementação do jogo de cartas "Rouba Monte" com regras definidas.
- **CRIAÇÃO DE ARQUIVO:** Permite a criação de um arquivo de configuração para o jogo.

## ESTRUTURA DO PROJETO

- **Modularidade:** O código está dividido em funções, cada uma responsável por uma tarefa específica. Isso facilita a leitura, manutenção e reutilização do código.
- **Estruturas de Dados:** O uso de estruturas de dados, como pilhas (**´PILHA**´), é central para o funcionamento do jogo. As funções **push** e **pop** são utilizadas para manipular essas estruturas.
- **Manipulação de Arquivos:** O programa lê e escreve em arquivos para configurar o jogo. A função **criarArq** cria um arquivo com parâmetros definidos pelo usuário, e a função **inicio** lê as configurações de um arquivo existente.
- **Controle de Fluxo:** A função **main** utiliza um loop **do-while** para apresentar um menu de opções ao usuário. O controle de fluxo (**switch**) permite que o programa execute diferentes ações com base na escolha do usuário.
- **Geração de Números Aleatórios:** A função **carta** utiliza a função **rand** para gerar números aleatórios representando cartas do jogo.
- **Utilização de Ponteiros:** O código faz uso de ponteiros em algumas funções, como aquelas que recebem estruturas do tipo **PILHA** por referência.

## CONTRIBUIÇÃO

Sinta-se à vontade para contribuir para este projeto. Abra uma issue para discutir mudanças importantes antes de fazer um pull request.

1. Faça um fork do projeto.
2. Crie uma branch para a sua feature (`git checkout -b feature/NomeDaSuaFeature`).
3. Faça commit das suas mudanças (`git commit -m 'Adiciona nova funcionalidade'`).
4. Faça push para a branch (`git push origin feature/NomeDaSuaFeature`).
5. Abra um pull request.

## AUTORES

- Paulo André de Oliveira Félix

