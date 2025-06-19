# trabalhoED
Trabalho da disciplina Estrutura de Dados.

Este programa implementa um algoritmo de ordenação externa para arquivos grandes que não cabem na memória RAM, utilizando o merge multiway (externo)

### Como funciona:
Conversão CSV → Binário: Lê o arquivo CSV e converte para formato binário

Criação de blocos ordenados: Divide os dados em blocos de 1000 registros, ordena cada bloco

Intercalação: Combina todos os arquivos temporários (20) em um arquivo final ordenado

Conversão Binário → CSV: Converte o resultado final de volta para CSV

### Configurações
Tamanho do bloco: 1000 registros (BLOCK_SIZE)

Número de arquivos temporários: 20 (NUM_TEMP_FILES)

Ordem de classificação: Decrescente por ID
