# FollowLine PID
O nosso projeto engloba o uso de robôs seguidores de linha, cuja operação é embasada em um sofisticado sistema de controle PID. Essa abordagem garante a capacidade de realizar movimentos precisos e meticulosamente controlados. Além dessa notável característica, o robô é compatível com a tecnologia Bluetooth, o que possibilita o controle em tempo real dos valores do PID, proporcionando um ajuste instantâneo e eficaz.

# Hardwares utilizados no robô:
<ul>
	<li>Ardu&iacute;no Uno/Nano - ATMEGA de 16Mhz</li>
	<li>Vespa - ESP32 de 240Mhz, com uma motor shield embutida para 2 motores DC, wireless e produzida no Brasil</li>
	<li>QTR-8RC, array de 8 sensores digitais, produzida pela Pololu, cuja range varia entre 0 e 2500 para cada sensor individual</li>
	<li>Motor shield L298N, conhecida tamb&eacute;m por ponte H</li>
	<li>Ball caster</li>
	<li>Chassi feito em impressora 3D</li>
	<li>Baterias Li-Po e pilhas recarreg&aacute;veis de 3.7V, com suporte para duas pilhas.</li>
	<li>Motores DC de 6V/12V, 500RPM</li>
	<li>Interruptor</li>
</ul>

# Comunicação Bluetooth:
Por se tratar da utilização de um módulo Bluetooth(HC-06 ou HC-05) ou de um Bluetooth embutido no microcontrolador, o processo de comunicação com o robô poderá ser feito remotamente pelo PC/Smartphone, por qualquer plataforma/app que permita o envio de Strings(textos) correspondentes, conforme os parâmetros abaixo e com o caractere "\n"(nova linha, ou Enter) ao final do envio do texto.<br />

A comunicação com o computador é viabilizado através da utilização da IDE do Arduino, por meio de um correto emparelhamento com o módulo Bluetooth no Arduíno, levando em consideração também a presença dessa tecnologia no computador. Adicionalmente, a correta seleção da porta é fundamental nesse contexto. Os parâmetros pertinentes podem ser inseridos remotamente através do Monitor Serial, utilizando o computador como interface.<br />

Já nos Smartphones, há várias opções de apps que realizam essa tarefa de se comunicar, via Bluetooth, com o Arduíno. Para tal, basta acessar a loja de apps de seu OS correspondente e baixe uma das opções disponíveis nessa plataforma. Esse app deverá suportar características descritas acima.

### Os parâmetros a seguir são recebidos pela comunicação Bluetooth, na qual o robô desempenha o papel de destinatário:
<table border="0" cellpadding="0" cellspacing="0" style="width:500px">
	<tbody>
		<tr>
			<td style="width:88px">run&nbsp;</td>
			<td style="width:398px">-&gt; Igni&ccedil;&atilde;o do rob&ocirc;</td>
		</tr>
		<tr>
			<td style="width:88px">stop&nbsp;</td>
			<td style="width:398px">-&gt; Parar o rob&ocirc;</td>
		</tr>
		<tr>
			<td style="width:88px">p = 2.5&nbsp;</td>
			<td style="width:398px">-&gt; Controle da proporcional</td>
		</tr>
		<tr>
			<td style="width:88px">i = 0.002</td>
			<td style="width:398px">-&gt; Controle da integrativa</td>
		</tr>
		<tr>
			<td style="width:88px">d = 5&nbsp;</td>
			<td style="width:398px">-&gt; Controle da derivativa</td>
		</tr>
		<tr>
			<td style="width:88px">speed = 255</td>
			<td style="width:398px">-&gt; Controle da velocidade</td>
		</tr>
		<tr>
			<td style="width:88px">line&nbsp;&nbsp;&nbsp;</td>
			<td style="width:398px">-&gt; Alternar entre seguir linha branca ou seguir linha preta. O padr&atilde;o &eacute; a linha preta, podendo ser alterada na programa&ccedil;&atilde;o.</td>
		</tr>
	</tbody>
</table>

Note que há parâmetros que devem possuir valores e outros parâmetros que não devem possuir valores.<br />
Os valores citados acima pelos parâmetros individuais do PID e speed são exemplos e cabe ao usuário fazer o uso correto dos valores baseado nas necessidades individuais de cada robô.<br />

O usuário poderá enviar caracteres maiúsculos, minúsculos ou espaços sem menores prolemas, pois por conveniência, o código aceita variações desta natureza.<br />

Se, por ventura, os parâmetros e valores não coincidirem com os citados acima, o usuário será informado sobre eventuais erros de digitação.<br />
Após o envio da informação, o robô enviará confirmações de que o parâmetro procedeu ou não.<br />

### Parâmetros enviados pelo robô a um dispositivo de controle que confirmam a entrega dos parâmetros:
Ao mudar qualquer um dos parâmetros do PID, que, por padrão, cada valor está com a precisão de 5 casas decimais, o robô retorna o seguinte texto, baseado nos valores atuais da memória e incluindo o valor recentemente inserido: PID(P=2.00000, I=0.00200, D=5.00000).<br />
Os parâmetros "run" e "stop" retornam: "Run robot.", "Stop robot.", respectivamente.<br />
O parâmetro "line" retorna: "Following BLACK line." ou "Following WHITE line."<br />
O parâmetro speed retorna o valor da velocidade máxima do robô <br />

## Sobre a Vespa:
A vespa é um microcontrolador baseado na ESP32 de 240Mhz, produzido no Brasil, cujo tamanho é quase igual ao de um Arduíno Uno, porém com um processador bem mais rápido e com a adição de um motor shield e comunicação Bluetooth e Wifi, já embutidos na placa, não necessitando de um hardware externo para tal e diminuindo a quantidade fios. A fabricante dispõe de uma biblioteca própria, o que permite controlar os motores e a comunicação wireless. Essa placa utiliza a mesma programação utilizada em Arduínos convencionais, portanto há compatibilidade tanto com o código, bem como a IDE do Arduíno.<br />

Para o correto funcionamento desta placa, são necessários os devidos drivers e a biblioteca. Sendo assim, disponibilizamos o link que direciona ao processo de obtenção e instalação dos referidos drivers e da biblioteca:
https://www.robocore.net/tutoriais/instalacao-driver-da-blackboard

Adicionalmente, segue o link fornecido pela fabricante, contendo tutoriais que demonstram de forma abrangente o uso dos recursos disponíveis, incluindo instruções detalhadas sobre como controlar os motores:
https://www.robocore.net/tutoriais/vespa/
