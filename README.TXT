Projeto de Sistemas Operativos 2018/2019

Simulação de uma loja (de café)

-> Compilação do projeto <-

Assumindo que está a usar uma distribuição Linux, utilize o terminal e entre na diretoria com o conteúdo do projeto:

$ cd /path/to/project/

Para certificar que compilamos o programa de maneira correta:

$ make clean

Agora podemos compilar:

$ make

Caso seja necessário, pode editar o ficheiro de configuração (config.conf) para ajustar a simulação.
Para iniciarmos a simulação, executamos o monitor primeiro:

$ ./monitor

Depois, iniciamos o simulador, noutra instância do terminal:

$ ./simulador

Se tudo correu bem, pode utilizar o programa.