# Problemas e soluções

Primeiramente, o primeiro problema começou na hora de fazer o tratamento do '/0', comecei o tratando a string dentro do arquivo _client.c_, passando um byte a menos na função send(), i.e. send(s, buf, strlen(buf) - 1, 0);. Contudo, depois da conversa com o monitor vi que era preciso fazer esse tratamento no arquivo _server.c_, uma vez que o nosso cliente não será usado para testar o programa. Assim, no cliente deixei a função send() enviar todos os bytes da string e no _server.c_ criei utilizei duas funções para tratar o '/0'. Na figura abaixo vemos como ficou a estrutura do send() no _client.c_ e como ficou a estrutura do recv() junto com o tratamento da string no _server.c_.

***server.c***

![image-20220521120126655](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521120126655.png)

***client.c***

![image-20220521120209383](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521120209383.png)



Além desses problemas, tive algumas dúvidas na hora da criar minhas structs para fazer as funções propostas pelo projeto, criei duas structs, uma chamada **equipment** e outra chamada **sensor**, a estrutura delas está definida abaixo. Obs: o **id** da struct **equipment** não precisou ser utilizado durante o código, mas resolvi deixar para caso eu precise alterar algo futuramente.

***struct sensor***

![image-20220521121849077](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521121849077.png)

***struct equipments***

![image-20220521121908984](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521121908984.png)



Um dos problemas que tive com essas structs foi a inicialização delas, tive muito retrabalho pois não sabia ao certo o que tinha que fazer para elas serem instanciadas, abaixo está um print do código de inicialização que **não** foi utilizado, uma vez quenão era necessário.

![image-20220521122051657](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521122051657.png)

Já com as funções, tive alguns impecilhos mas que eram erro de lógica. O maior problema, com certeza, foi com a função add(). Foi o meu primeiro contato com a string de entrada, assim, tive que pensar em toda a lógica para separar cada dado importante da string (sensores para serem instalados e equipamento de referencia). Dessa forma, utilizei algumas funções próprias para string (strncpy(), strcpy(), strnchr(), strchr(), entre outras). Toda a função está comentada, acredito que não seja necessário explicar linha a linha do código. Contudo, um problema que tive com essa função foi determinar quantos sensores o cliente gostaria de armazenar e, também, adicionar esses vetores na mesma ordem que o cliente pediu. Desse modo, abaixo vou colocar o print da lógica utilizada em ambos contextos, além de explicar em detalhas o seu funcionamento.

*add()* -> **Determinar quantos sensores o cliente gostaria de adicionar e tratá-los individualmente de acordo com a ordem orginal**

O variável *sensors* recebe a string tratada com os sensores que o client gostaria de adicionar, o tratamento para essa string será detalhada mais para frente na documentação. Assim, de acordo com o tamanho da string sabemos quantos sensores o cliente deseja adicionar e com a variável _max_ iremos saber qual tamanho de vetor auxiliar, detalhado mais a frente, precisará ser alocado.

![image-20220521124322846](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521124322846.png)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

No código abaixo, eu faço a separação de cada um dos sensores presentes na string, faço a conversão da string que contém o sensor em inteiro e o armazeno em um vetor de inteiros. A variável index é responsável por ordenar o vetor de inteiros na mesma ordem em que o usuário mandou o comanda, isso porque a lógica que eu utilizei começa a tratar a string a partir dos últimos caractéres. Nos comentários do código consta alguns exemplos mais práticos da lógica, mas a ideia básica é se na string _sensors_ é igual a "01 02 03 04", a primeira linha do código abaixo copia "04" para a variável chamada *sensor_buffer* e depois elimina a string " 04" de _sensors_, assim a variável _sensors_ fica apenas com "01 02 03". E o _index_ que a string *sensor_buffer* terá no vetor auxiliar, *sensor_id[index]*, será igual a 3, uma vez que precisamos de 4 casas do vetor auxiliar para adicionar os sensores convertidos. 

![image-20220521150317741](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521150317741.png)

![image-20220521150335394](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521150335394.png)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

**Problema secundário com a função add()** -> Ademais, um problema secundário que eu tive com a função add() foi quando já existiam sensores instalados nas máquinas, assim tive de criar mais um vetor auxiliar para guardar a posição vazia do vetor de sensores do equipamento, a lógica está comentada no código, mas vou deixar o print de um exemplo abaixo.

![image-20220521150402102](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521150402102.png)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Terminando a função add() o resto das funções ficaram tranquilas de serem feitas, funções _remove() e list() foram feitas em menos de 10 minutos então acho que não vale comentar sobre problemas que tive com elas, já que não foram muito complexos.

Já na função _read() tive um problema parecido com o que apareceu na função add(), precisei copiar a lógica da função add() que separava os sensores em arrays auxiliares e criar a lógica de verificar se o sensor já existia no vetor de sensores, ele existindo seria necessário salvar ele em um vetor auxíliar, avisar ao programa que já existia um "erro" na requisição do cliente e continuar rodando o array de sensores para encontrar mais alguns que não estavam presentes na lista de sensores. Toda essa lógica está comentada na função, mas colocarei um print mostrando aonde isso ocorre no código.

![image-20220521151052537](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521151052537.png)

![image-20220521151107254](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521151107254.png)

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# Estrutura do projeto

Além dos arquivos _client.c_, _client.h_, _server.c_, _server.h_, _common.c_ e _common.h_, eu crei mais dois arquivos: _f-server.c_ e _f-client.h_. Nesses dois arquivos constam todas as funções necessárias para a lógica do TP, nele existem dois "tipos" de funções: funções tipo *handle_exec* e funções _exec_, onde as funções do tipo *handle_exec* tratam as strings e passam para as funções _exec_, as quais realmente fazem as operações manipulando os arrays das structs. O tratamento de '/0' é feito no arquivo _server.c_, podendo ser verificado na imagem abaixo.

![image-20220521160939524](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521160939524.png)

Todas as funções estão comentadas, caso tenha alguma dúvida do funcionamento basta ler os comentários. A função _kill()_ está no arquivo _common.h_ e a lógica dela é fechar o socket quando o a palavra "kill" é identificada pelo servidor. Caso envie algum comando que não seja os identificados pela função *handle_buffer()*, a string enviada sera substituida pela string "kill" e finalizará o programa quando a função _kill()_ for chamada no arquivo _server.c_.

***f-server.c***: ***handle_buffer()***

![image-20220521162133982](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521162133982.png)

***server.c***

![image-20220521162043385](/home/vitor/snap/typora/57/.config/Typora/typora-user-images/image-20220521162043385.png)



