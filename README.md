# Estruturas em Árvores Avançadas - AEDS II

Repositório contendo implementações, testes e análise de performance de cinco estruturas de dados hierárquicas avançadas não-convencionais. Desenvolvido como requisito de trabalho prático para a disciplina de Algoritmos e Estruturas de Dados II.

## 🌳 Árvores Implementadas
O projeto isola cada estrutura em sua própria pasta, de modo encapsulado e modular, garantindo independência no `build`. Foram implementadas:

1. **Trie (Árvore de Prefixos)**
2. **Árvore Patricia (Radix Tree compacta)**
3. **Árvore Splay**
4. **Treap (Tree + Heap)**
5. **KD-Tree**

## 🚀 Como Executar

Cada estrutura conta com o seu próprio `Makefile`. Para compilar e rodar a suíte de benchmarks e extrair os dados visuais de uma estrutura (ex: Splay):

```bash
cd splay/
make clean
make
make run
```
*(O mesmo comando vale para `trie`, `patricia`, `treap` e `kdtree`)*

## 📊 Benchmarks e Resultados
O `main.cpp` de cada estrutura roda um teste automatizado contendo **10.000** e **50.000** nós instanciados aleatoriamente. Foram testados os métodos clássicos: Inserção, Busca e Remoção. 

Resultados notáveis coletados no estudo ($N = 50.000$):
* **Velocidade Bruta:** Treap demonstrou enorme fluidez e estabilidade em tempo de processamento devido ao seu balanceamento probabilístico (aprox. `36ms` para 50k elementos).
* **Pior Caso Clássico:** Testes com dados estritamente *ordenados* em BST (forçando-as a virar uma lista) validaram a Splay Tree e a Treap. A Treap realizou a busca de 50.000 dados ordenados em apenas `11ms`, provando que seus Heaps reagem ativamente protegendo a topologia, e a Splay absorveu o cache perfeitamente com sua operação contínua de elevação.
* **Strings:** A Trie provou ser muito mais rápida na manipulação léxica (aprox `60ms` na busca) contra a Patricia Tree (`190ms`). Apesar da velocidade maior, a Trie sacrifica severamente a memória, de modo que a Patricia compensa através da sua notória aglutinação de arestas contínuas sem ponteiros inertes.

## 🖼️ Geração Visual (Graphviz)
Todas as estruturas implementam métodos internos `generateDOT()`. A cada ciclo de teste nos `mains`, são exportados rastreamentos estruturais nos diretórios `data/*.dot`. 
Usando o formato de grafo DOT, foi possível plotar a topologia e estudar o comportamento do rebalanceamento em tempo real (como o fracionamento das strings na Patricia ou a conversão de eixos na KD-Tree).

O relatório técnico completo (`.tex` e `.pdf` compilado) e todas as métricas tabuladas podem ser encontrados na pasta `relatorio/`.
