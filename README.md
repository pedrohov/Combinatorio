# Pattern Recognition

Trabalho Prático da disciplina de Matemática
Computacional que trata do tema de construção de um reconhecedor de
padrões simples que usa conceitos básicos de Algebra Linear, mais especificamente
inversa de matrizes. O termo pattern recognition ou reconhecimento de padrões é
usado para designar um ramo da área denominada aprendizado de máquina que tem
por objetivo reconhecer ‘padrões’ ou ‘regularidades’ em dados. Portanto o reconhecimento
de padrões tem por objetivo atribuir um ‘rótulo’ para um dado valor de
entrada informado.

# Execução
Pelo terminal, vá para a pasta do repositório e execute o comando make:

```
cd combinatorio
make
```

Execute o arquivo 'pattern' e passe como parâmetros o arquivo de treinamento e o arquivo de verificação:

```
// Terminal linux:
./pattern treinamento/seeds-treinamento.dat verificacao/seeds-verificacao.dat

// Cmd do windows:
cmd /K pattern treinamento/seeds-treinamento.dat verificacao/seeds-verificacao.dat
```

# Testes sobre outros dados:
Para utilizar este trabalho em outros dados, deve-se criar um arquivo de treinamento e um arquivo de
verificação de acordo com o formato apresentado em 'treinamento/formato.txt' ou 'verificacao/formato.txt'.
